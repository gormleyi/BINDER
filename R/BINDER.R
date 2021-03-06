#----------------------------------------------------------------------------------------------------

#' Run BINDER model using prepared data.
#'
#' @export
#' @param prepared_data A list generated by `prepare_data` function.
#' @param mu_zeta Prior mean for zeta; the default is 0.
#' @param sigma_zeta Prior standard deviation for zeta; the default is 3.
#' @param mu_tau Prior mean vector for tau; the default is c(0,0).
#' @param sigma_tau Prior standard deviation vector for tau; the default is c(3,3).
#' @param mu_phi Prior mean for phi; the default is 0.
#' @param sigma_phi Prior standard deviation for phi; the default is 3.
#' @param mu_psi Prior mean vector for psi; the default is c(0,0).
#' @param sigma_psi Prior standard deviation vector for psi; the default is c(3,3).
#' @param model_summary logical; if TRUE, a model summary of parameter estimates is printed upon completion of BINDER run; defaults to FALSE.
#' @param model_summary_parameters A vector of parameters to include in model summary.
#' @param ... Arguments passed to `rstan::sampling` (e.g. iter, chains).
#' @return A list with the following components:
#'   \itemize{
#'     \item regulator - the name of the regulator provided to BINDER.
#'     \item target_candidate - a vector providing the names of each target candidate provided to BINDER.
#'     \item ME - a vector providing ME values for each target candidate provided to BINDER.
#'     \item PE - a vector providing PE values for each target candidate provided to BINDER.
#'     \item CM - a vector providing CM values for each target candidate provided to BINDER.
#'     \item CP - a vector providing CP values for each target candidate provided to BINDER.
#'     \item mean_theta - a vector providing posterior mean values for theta for each target candidate provided to BINDER.
#'     \item theta_interval - a matrix providing posterior 0.025, 0.5 and 0.975 quantiles for theta for each target candidate provided to BINDER.
#'     \item mean_gamma - a vector providing posterior mean values for gamma for each target candidate provided to BINDER.
#'     \item gamma_interval - a matrix providing posterior 0.025 and 0.975 quantiles for gamma for each target candidate provided to BINDER.
#'     \item mean_raw_gamma - a vector providing posterior mean values for raw_gamma for each target candidate provided to BINDER.
#'     \item raw_gamma_interval - a matrix providing posterior 0.025 and 0.975 quantiles for raw_gamma for each target candidate provided to BINDER.
#'     \item mean_phi - posterior mean for phi as estimated by BINDER.
#'     \item phi_interval - a vector providing posterior 0.025 and 0.975 quantiles for phi as estimated by BINDER.
#'     \item mean_zeta - posterior mean for zeta as estimated by BINDER.
#'     \item zeta_interval - a vector posterior 0.025 and 0.975 quantiles for zeta as estimated by BINDER.
#'     \item mean_tau - a vector providing posterior mean values for tau as estimated by BINDER.
#'     \item tau_interval - a matrix providing posterior 0.025 and 0.975 quantiles for tau as estimated by BINDER.
#'     \item mean_psi - a vector providing posterior mean values for psi as estimated by BINDER.
#'     \item psi_interval - a matrix providing posterior 0.025 and 0.975 quantiles for psi as estimated by BINDER.
#'     \item posterior_samples_theta - a matrix providing posterior samples for each target candidate provided to BINDER.
#'     \item posterior_samples_psi - a matrix providing posterior samples for each psi element as estimated by BINDER.
#'     \item model_object - object of class `stanfit` returned by `rstan::sampling`.
#'   }
#'
run_binder <- function(prepared_data, mu_zeta=0, sigma_zeta=3, mu_tau=c(0,0), sigma_tau=c(3,3), mu_phi=0, sigma_phi=3, mu_psi=c(0,0), sigma_psi=c(3,3), model_summary=FALSE, model_summary_parameters, model_name="anon_model", fit=NA, chains=4, iter=2000, warmup=floor(iter/2), thin=1, init="random", seed=sample.int(.Machine$integer.max, 1), algorithm=c("NUTS", "HMC", "Fixed_param"), control=NULL, sample_file=NULL, diagnostic_file=NULL, save_dso=TRUE, verbose=FALSE, include=TRUE, cores=getOption("mc.cores", 1L), open_progress=interactive() && !isatty(stdout()) && !identical(Sys.getenv("RSTUDIO"), "1"), chain_id, init_r, test_grad=FALSE, append_samples, refresh=max(iter/10, 1), enable_random_init, save_warmup=TRUE, boost_lib=NULL, eigen_lib=NULL){
  # Stan configuration:
  model <- rstan::sampling(stanmodels$binder,
                           data=list(N=prepared_data$N, M=prepared_data$M, K=prepared_data$K, X=prepared_data$X, Y=prepared_data$Y, mu_zeta=mu_zeta, sigma_zeta=sigma_zeta, mu_tau=mu_tau, sigma_tau=sigma_tau, mu_phi=mu_phi, sigma_phi=sigma_phi, mu_psi=mu_psi, sigma_psi=sigma_psi),
                           pars=c("zeta", "tau", "raw_gamma", "gamma", "phi", "theta", "psi"),
                           warmup=warmup,
                           iter=iter,
                           chains=chains,
                           seed=seed)
  if(model_summary == TRUE){print(model, pars=summary_parameters)}

  psi_samples <- rstan::extract(model, "psi")[[1]]
  mean_psi_samples <- apply(psi_samples, 2, mean)
  names(mean_psi_samples) <- c("psi_CM", "psi_CP")
  df_quantiles_fitted_psi_95 <- matrix(apply(psi_samples, 2, quantile, c(0.0275, 0.975)), ncol=2, byrow=TRUE)
  rownames(df_quantiles_fitted_psi_95) <- c("psi_CM", "psi_CP")
  colnames(df_quantiles_fitted_psi_95) <- c("0.025", "0.975")

  theta_samples <- rstan::extract(model,"theta")[[1]]
  mean_theta_samples <- apply(theta_samples, 2, mean)
  names(mean_theta_samples) <- prepared_data$target_candidate
  df_quantiles_fitted_theta_95 <- matrix(apply(theta_samples, 2, quantile, c(0.0275, 0.5,0.975)), ncol=3, byrow=TRUE)
  rownames(df_quantiles_fitted_theta_95) <- prepared_data$target_candidate
  colnames(df_quantiles_fitted_theta_95) <- c("0.025", "0.5", "0.975")

  phi_samples <- rstan::extract(model,"phi")[[1]]
  mean_phi_samples <- mean(phi_samples)
  df_quantiles_fitted_phi_95 <- quantile(phi_samples, c(0.025, 0.975))
  names(df_quantiles_fitted_phi_95) <- c("0.025", "0.975")

  gamma_samples <- rstan::extract(model,"gamma")[[1]]
  mean_gamma_samples <- apply(gamma_samples, 2, mean)
  names(mean_gamma_samples) <- prepared_data$target_candidate
  df_quantiles_fitted_gamma_95 <- matrix(apply(gamma_samples, 2, quantile, c(0.0275, 0.975)), ncol=2, byrow=TRUE)
  rownames(df_quantiles_fitted_gamma_95) <- prepared_data$target_candidate
  colnames(df_quantiles_fitted_gamma_95) <- c("0.025", "0.975")

  raw_gamma_samples <- rstan::extract(model,"raw_gamma")[[1]]
  mean_raw_gamma_samples <- apply(raw_gamma_samples, 2, mean)
  names(mean_raw_gamma_samples) <- prepared_data$target_candidate
  df_quantiles_fitted_raw_gamma_95 <- matrix(apply(raw_gamma_samples, 2, quantile, c(0.0275, 0.975)), ncol=2, byrow=TRUE)
  rownames(df_quantiles_fitted_raw_gamma_95) <- prepared_data$target_candidate
  colnames(df_quantiles_fitted_raw_gamma_95) <- c("0.025", "0.975")

  tau_samples <- rstan::extract(model,"tau")[[1]]
  mean_tau_samples <- apply(tau_samples, 2, mean)
  names(mean_tau_samples) <- c("tau_ME", "tau_PE")
  df_quantiles_fitted_tau_95 <- matrix(apply(tau_samples, 2, quantile, c(0.0275, 0.975)), ncol=2, byrow=TRUE)
  rownames(df_quantiles_fitted_tau_95) <- c("tau_ME", "tau_PE")
  colnames(df_quantiles_fitted_tau_95) <- c("0.025", "0.975")

  zeta_samples <- rstan::extract(model,"zeta")[[1]]
  mean_zeta_samples <- mean(zeta_samples)
  df_quantiles_fitted_zeta_95 <- quantile(zeta_samples, c(0.025, 0.975))
  names(df_quantiles_fitted_zeta_95) <- c("0.025", "0.975")

  results <- list("regulator"=prepared_data$regulator, "target_candidate"=prepared_data$target_candidate, "ME"=prepared_data$X[,1], "PE"=prepared_data$X[,2], "CM"=prepared_data$Y[,1], "CP"=prepared_data$Y[,2], "mean_theta"=mean_theta_samples, "theta_interval"=df_quantiles_fitted_theta_95, "mean_gamma"=mean_gamma_samples, "gamma_interval"=df_quantiles_fitted_gamma_95, "mean_raw_gamma"=mean_raw_gamma_samples, "raw_gamma_interval"=df_quantiles_fitted_raw_gamma_95, "mean_phi"=mean_phi_samples, "phi_interval"=df_quantiles_fitted_phi_95, "mean_zeta"=mean_zeta_samples, "zeta_interval"=df_quantiles_fitted_zeta_95, "mean_tau"=mean_tau_samples, "tau_interval"=df_quantiles_fitted_tau_95, "mean_psi"=mean_psi_samples, "psi_interval"=df_quantiles_fitted_psi_95, "posterior_samples_theta"=theta_samples, "posterior_samples_psi"=psi_samples, "model_object"=model)
  return(results)
}

#--------------------------------------------------

#' Run non-auxiliary BINDER model using prepared data.
#'
#' @export
#' @param prepared_data A list generated by `prepare_data` function.
#' @param mu_psi Prior mean vector for psi; the default is c(0,0).
#' @param sigma_psi Prior standard deviation vector for psi; the default is c(3,3).
#' @param model_summary logical; if TRUE, a model summary of parameter estimates is printed upon completion of BINDER run; defaults to FALSE.
#' @param model_summary_parameters A vector of parameters to include in model summary.
#' @param ... Arguments passed to `rstan::sampling` (e.g. iter, chains).
#' @return A list with the following components:
#'   \itemize{
#'     \item regulator - the name of the regulator provided to BINDER.
#'     \item target_candidate - a vector providing the names of each target candidate provided to BINDER.
#'     \item ME - a vector providing ME values for each target candidate provided to BINDER.
#'     \item PE - a vector providing PE values for each target candidate provided to BINDER.
#'     \item CM - a vector providing CM values for each target candidate provided to BINDER.
#'     \item CP - a vector providing CP values for each target candidate provided to BINDER.
#'     \item mean_theta - a vector providing posterior mean values for theta for each target candidate provided to BINDER.
#'     \item theta_interval - a matrix providing posterior 0.025, 0.5 and 0.975 quantiles for theta for each target candidate provided to BINDER.
#'     \item mean_psi - a vector providing posterior mean values for psi as estimated by BINDER.
#'     \item psi_interval - a matrix providing posterior 0.025 and 0.975 quantiles for psi as estimated by BINDER.
#'     \item posterior_samples_theta - a matrix providing posterior samples for each target candidate provided to BINDER.
#'     \item posterior_samples_psi - a matrix providing posterior samples for each psi element as estimated by BINDER.
#'     \item model_object - object of class `stanfit` returned by `rstan::sampling`.
#'   }
#'
run_non_auxiliary_binder <- function(prepared_data, mu_psi=c(0,0), sigma_psi=c(3,3), model_summary=FALSE, model_summary_parameters, model_name="anon_model", fit=NA, chains=4, iter=2000, warmup=floor(iter/2), thin=1, init="random", seed=sample.int(.Machine$integer.max, 1), algorithm=c("NUTS", "HMC", "Fixed_param"), control=NULL, sample_file=NULL, diagnostic_file=NULL, save_dso=TRUE, verbose=FALSE, include=TRUE, cores=getOption("mc.cores", 1L), open_progress=interactive() && !isatty(stdout()) && !identical(Sys.getenv("RSTUDIO"), "1"), chain_id, init_r, test_grad=FALSE, append_samples, refresh=max(iter/10, 1), enable_random_init, save_warmup=TRUE, boost_lib=NULL, eigen_lib=NULL){
  # Stan configuration:
  model <- rstan::sampling(stanmodels$non_auxiliary,
                           data=list(N=prepared_data$N, M=prepared_data$M, K=prepared_data$K, X=prepared_data$X, Y=prepared_data$Y, mu_psi=mu_psi, sigma_psi=sigma_psi),
                           pars=c("theta", "psi"),
                           warmup=warmup,
                           iter=iter,
                           chains=chains,
                           seed=seed)
  if(model_summary == TRUE){print(model, pars=summary_parameters)}
  
  psi_samples <- rstan::extract(model, "psi")[[1]]
  mean_psi_samples <- apply(psi_samples, 2, mean)
  names(mean_psi_samples) <- c("psi_CM", "psi_CP")
  df_quantiles_fitted_psi_95 <- matrix(apply(psi_samples, 2, quantile, c(0.0275, 0.975)), ncol=2, byrow=TRUE)
  rownames(df_quantiles_fitted_psi_95) <- c("psi_CM", "psi_CP")
  colnames(df_quantiles_fitted_psi_95) <- c("0.025", "0.975")
  
  theta_samples <- rstan::extract(model,"theta")[[1]]
  mean_theta_samples <- apply(theta_samples, 2, mean)
  names(mean_theta_samples) <- prepared_data$target_candidate
  df_quantiles_fitted_theta_95 <- matrix(apply(theta_samples, 2, quantile, c(0.0275, 0.5,0.975)), ncol=3, byrow=TRUE)
  rownames(df_quantiles_fitted_theta_95) <- prepared_data$target_candidate
  colnames(df_quantiles_fitted_theta_95) <- c("0.025", "0.5", "0.975")
  
  results <- list("regulator"=prepared_data$regulator, "target_candidate"=prepared_data$target_candidate, "ME"=prepared_data$X[,1], "PE"=prepared_data$X[,2], "CM"=prepared_data$Y[,1], "CP"=prepared_data$Y[,2], "mean_theta"=mean_theta_samples, "theta_interval"=df_quantiles_fitted_theta_95, "mean_psi"=mean_psi_samples, "psi_interval"=df_quantiles_fitted_psi_95, "posterior_samples_theta"=theta_samples, "posterior_samples_psi"=psi_samples, "model_object"=model)
  return(results)
}

#--------------------------------------------------

#' Run deterministic BINDER model using prepared data.
#'
#' @export
#' @param prepared_data A list generated by `prepare_data` function.
#' @param mu_zeta Prior mean for zeta; the default is 0.
#' @param sigma_zeta Prior standard deviation for zeta; the default is 3.
#' @param mu_tau Prior mean vector for tau; the default is c(0,0).
#' @param sigma_tau Prior standard deviation vector for tau; the default is c(3,3).
#' @param mu_psi Prior mean vector for psi; the default is c(0,0).
#' @param sigma_psi Prior standard deviation vector for psi; the default is c(3,3).
#' @param model_summary logical; if TRUE, a model summary of parameter estimates is printed upon completion of BINDER run; defaults to FALSE.
#' @param model_summary_parameters A vector of parameters to include in model summary.
#' @param ... Arguments passed to `rstan::sampling` (e.g. iter, chains).
#' @return A list with the following components:
#'   \itemize{
#'     \item regulator - the name of the regulator provided to BINDER.
#'     \item target_candidate - a vector providing the names of each target candidate provided to BINDER.
#'     \item ME - a vector providing ME values for each target candidate provided to BINDER.
#'     \item PE - a vector providing PE values for each target candidate provided to BINDER.
#'     \item CM - a vector providing CM values for each target candidate provided to BINDER.
#'     \item CP - a vector providing CP values for each target candidate provided to BINDER.
#'     \item mean_theta - a vector providing posterior mean values for theta for each target candidate provided to BINDER.
#'     \item theta_interval - a matrix providing posterior 0.025, 0.5 and 0.975 quantiles for theta for each target candidate provided to BINDER.
#'     \item mean_zeta - posterior mean for zeta as estimated by BINDER.
#'     \item zeta_interval - a vector posterior 0.025 and 0.975 quantiles for zeta as estimated by BINDER.
#'     \item mean_tau - a vector providing posterior mean values for tau as estimated by BINDER.
#'     \item tau_interval - a matrix providing posterior 0.025 and 0.975 quantiles for tau as estimated by BINDER.
#'     \item mean_psi - a vector providing posterior mean values for psi as estimated by BINDER.
#'     \item psi_interval - a matrix providing posterior 0.025 and 0.975 quantiles for psi as estimated by BINDER.
#'     \item posterior_samples_theta - a matrix providing posterior samples for each target candidate provided to BINDER.
#'     \item posterior_samples_psi - a matrix providing posterior samples for each psi element as estimated by BINDER.
#'     \item model_object - object of class `stanfit` returned by `rstan::sampling`.
#'   }
#'
run_deterministic_binder <- function(prepared_data, mu_zeta=0, sigma_zeta=3, mu_tau=c(0,0), sigma_tau=c(3,3), mu_psi=c(0,0), sigma_psi=c(3,3), model_summary=FALSE, model_summary_parameters, model_name="anon_model", fit=NA, chains=4, iter=2000, warmup=floor(iter/2), thin=1, init="random", seed=sample.int(.Machine$integer.max, 1), algorithm=c("NUTS", "HMC", "Fixed_param"), control=NULL, sample_file=NULL, diagnostic_file=NULL, save_dso=TRUE, verbose=FALSE, include=TRUE, cores=getOption("mc.cores", 1L), open_progress=interactive() && !isatty(stdout()) && !identical(Sys.getenv("RSTUDIO"), "1"), chain_id, init_r, test_grad=FALSE, append_samples, refresh=max(iter/10, 1), enable_random_init, save_warmup=TRUE, boost_lib=NULL, eigen_lib=NULL){
  # Stan configuration:
  model <- rstan::sampling(stanmodels$deterministic,
                           data=list(N=prepared_data$N, M=prepared_data$M, K=prepared_data$K, X=prepared_data$X, Y=prepared_data$Y, mu_zeta=mu_zeta, sigma_zeta=sigma_zeta, mu_tau=mu_tau, sigma_tau=sigma_tau, mu_psi=mu_psi, sigma_psi=sigma_psi),
                           pars=c("zeta", "tau", "theta", "psi"),
                           warmup=warmup,
                           iter=iter,
                           chains=chains,
                           seed=seed)
  if(model_summary == TRUE){print(model, pars=summary_parameters)}
  
  psi_samples <- rstan::extract(model, "psi")[[1]]
  mean_psi_samples <- apply(psi_samples, 2, mean)
  names(mean_psi_samples) <- c("psi_CM", "psi_CP")
  df_quantiles_fitted_psi_95 <- matrix(apply(psi_samples, 2, quantile, c(0.0275, 0.975)), ncol=2, byrow=TRUE)
  rownames(df_quantiles_fitted_psi_95) <- c("psi_CM", "psi_CP")
  colnames(df_quantiles_fitted_psi_95) <- c("0.025", "0.975")
  
  theta_samples <- rstan::extract(model,"theta")[[1]]
  mean_theta_samples <- apply(theta_samples, 2, mean)
  names(mean_theta_samples) <- prepared_data$target_candidate
  df_quantiles_fitted_theta_95 <- matrix(apply(theta_samples, 2, quantile, c(0.0275, 0.5,0.975)), ncol=3, byrow=TRUE)
  rownames(df_quantiles_fitted_theta_95) <- prepared_data$target_candidate
  colnames(df_quantiles_fitted_theta_95) <- c("0.025", "0.5", "0.975")
  
  tau_samples <- rstan::extract(model,"tau")[[1]]
  mean_tau_samples <- apply(tau_samples, 2, mean)
  names(mean_tau_samples) <- c("tau_ME", "tau_PE")
  df_quantiles_fitted_tau_95 <- matrix(apply(tau_samples, 2, quantile, c(0.0275, 0.975)), ncol=2, byrow=TRUE)
  rownames(df_quantiles_fitted_tau_95) <- c("tau_ME", "tau_PE")
  colnames(df_quantiles_fitted_tau_95) <- c("0.025", "0.975")
  
  zeta_samples <- rstan::extract(model,"zeta")[[1]]
  mean_zeta_samples <- mean(zeta_samples)
  df_quantiles_fitted_zeta_95 <- quantile(zeta_samples, c(0.025, 0.975))
  names(df_quantiles_fitted_zeta_95) <- c("0.025", "0.975")
  
  results <- list("regulator"=prepared_data$regulator, "target_candidate"=prepared_data$target_candidate, "ME"=prepared_data$X[,1], "PE"=prepared_data$X[,2], "CM"=prepared_data$Y[,1], "CP"=prepared_data$Y[,2], "mean_theta"=mean_theta_samples, "theta_interval"=df_quantiles_fitted_theta_95, "mean_zeta"=mean_zeta_samples, "zeta_interval"=df_quantiles_fitted_zeta_95, "mean_tau"=mean_tau_samples, "tau_interval"=df_quantiles_fitted_tau_95, "mean_psi"=mean_psi_samples, "psi_interval"=df_quantiles_fitted_psi_95, "posterior_samples_theta"=theta_samples, "posterior_samples_psi"=psi_samples, "model_object"=model)
  return(results)
}

#----------------------------------------------------------------------------------------------------

#' BINDER wrapper function.
#'
#' @export
#' @param proxy_regulon Data frame comprising columns: `regulator`, `target_candidate`, `ortholog_module_status` (1 if orthologous, 0 otherwise), `ME` (1 if high affinity for regulator motif, 0 otherwise) and `PE` (1 if orthologous interaction, 0 otherwise).
#' @param expression Numerical expression matrix; can be expression matrix with genes represented on rows and experimental conditions represented on columns or symmetric gene-gene coexpression matrix.
#' @param operons Data frame in DOOR format comprising operon annotations for all target candidates in `ortholog_ME_PE_structure`.
#' @param delta_CM Numerical cutoff point for coexpression module for CM: any values above `threshold` are considered to form a coexpression module with `target_candidate`; defaults to "auto" which represents the 95th percentile of coexpression scores involving `target_candidate`.
#' @param delta_CP Numerical cutoff point for coexpression module for CM: any values above `threshold` are considered to form a coexpression module with `target_candidate`; defaults to "auto" which represents the 95th percentile of coexpression scores involving `target_candidate`.
#' @param is_coexpression logical; if TRUE, expression matrix is treated as symmetric coexpression matrix.
#' @param model Indicates which model should be fit to the data: one of "BINDER", "non_auxiliary" or "deterministic".
#' @param mu_zeta Prior mean for zeta; the default is 0.
#' @param sigma_zeta Prior standard deviation for zeta; the default is 3.
#' @param mu_tau Prior mean vector for tau; the default is c(0,0).
#' @param sigma_tau Prior standard deviation vector for tau; the default is c(3,3).
#' @param mu_phi Prior mean for phi; the default is 0.
#' @param sigma_phi Prior standard deviation for phi; the default is 3.
#' @param mu_psi Prior mean vector for psi; the default is c(0,0).
#' @param sigma_psi Prior standard deviation vector for psi; the default is c(3,3).
#' @param model_summary logical; if TRUE, a model summary of parameter estimates is printed upon completion of BINDER run; defaults to FALSE.
#' @param model_summary_parameters A vector of parameters to include in model summary.
#' @param ... Arguments passed to `rstan::sampling` (e.g. iter, chains).
#' @return A list with the following components:
#'   \itemize{
#'     \item regulator - the name of the regulator provided to BINDER.
#'     \item target_candidate - a vector providing the names of each target candidate provided to BINDER.
#'     \item ME - a vector providing ME values for each target candidate provided to BINDER.
#'     \item PE - a vector providing PE values for each target candidate provided to BINDER.
#'     \item CM - a vector providing CM values for each target candidate provided to BINDER.
#'     \item CP - a vector providing CP values for each target candidate provided to BINDER.
#'     \item mean_theta - a vector providing posterior mean values for theta for each target candidate provided to BINDER.
#'     \item theta_interval - a matrix providing posterior 0.025, 0.5 and 0.975 quantiles for theta for each target candidate provided to BINDER.
#'     \item mean_gamma - a vector providing posterior mean values for gamma for each target candidate provided to BINDER.
#'     \item gamma_interval - a matrix providing posterior 0.025 and 0.975 quantiles for gamma for each target candidate provided to BINDER.
#'     \item mean_raw_gamma - a vector providing posterior mean values for raw_gamma for each target candidate provided to BINDER.
#'     \item raw_gamma_interval - a matrix providing posterior 0.025 and 0.975 quantiles for raw_gamma for each target candidate provided to BINDER.
#'     \item mean_phi - posterior mean for phi as estimated by BINDER.
#'     \item phi_interval - a vector providing posterior 0.025 and 0.975 quantiles for phi as estimated by BINDER.
#'     \item mean_zeta - posterior mean for zeta as estimated by BINDER.
#'     \item zeta_interval - a vector posterior 0.025 and 0.975 quantiles for zeta as estimated by BINDER.
#'     \item mean_tau - a vector providing posterior mean values for tau as estimated by BINDER.
#'     \item tau_interval - a matrix providing posterior 0.025 and 0.975 quantiles for tau as estimated by BINDER.
#'     \item mean_psi - a vector providing posterior mean values for psi as estimated by BINDER.
#'     \item psi_interval - a matrix providing posterior 0.025 and 0.975 quantiles for psi as estimated by BINDER.
#'     \item posterior_samples_theta - a matrix providing posterior samples for each target candidate provided to BINDER.
#'     \item posterior_samples_psi - a matrix providing posterior samples for each psi element as estimated by BINDER.
#'     \item model_object - object of class `stanfit` returned by `rstan::sampling`.
#'   }
#'
binder <- function(proxy_regulon, expression, operons, delta_CM="auto", delta_CP="auto", is_coexpression=FALSE, model="BINDER", mu_zeta=0, sigma_zeta=3, mu_tau=c(0,0), sigma_tau=c(3,3), mu_phi=0, sigma_phi=3, mu_psi=c(0,0), sigma_psi=c(3,3), model_summary=FALSE, model_summary_parameters, model_name="anon_model", fit=NA, chains=4, iter=2000, warmup=floor(iter/2), thin=1, init="random", seed=sample.int(.Machine$integer.max, 1), algorithm=c("NUTS", "HMC", "Fixed_param"), control=NULL, sample_file=NULL, diagnostic_file=NULL, save_dso=TRUE, verbose=FALSE, include=TRUE, cores=getOption("mc.cores", 1L), open_progress=interactive() && !isatty(stdout()) && !identical(Sys.getenv("RSTUDIO"), "1"), chain_id, init_r, test_grad=FALSE, append_samples, refresh=max(iter/10, 1), enable_random_init, save_warmup=TRUE, boost_lib=NULL, eigen_lib=NULL){
  if(is_coexpression == TRUE){
    coexpression <- expression
  }else{
    coexpression <- compute_coexpression(expression, proxy_regulon$target_candidate)
  }
  proxy_regulon <- proxy_regulon[proxy_regulon$target_candidate %in% colnames(coexpression), ]
  target_candidates <- proxy_regulon$target_candidate
  
  proxy_structure <- build_proxy_structure(proxy_regulon, coexpression, operons, delta_CM, delta_CP)
  prepared_data <- prepare_data(proxy_structure)
  if(model == "BINDER"){
    results <- run_binder(prepared_data, mu_zeta=mu_zeta, sigma_zeta=sigma_zeta, mu_tau=mu_tau, sigma_tau=sigma_tau, mu_phi=mu_phi, sigma_phi=sigma_phi, mu_psi=mu_psi, sigma_psi=sigma_psi, model_summary=model_summary, model_summary_parameters=model_summary_parameters, model_name=model_name, fit=fit, chains=chains, iter=iter, warmup=warmup, thin=thin, init=init, seed=seed, algorithm=algorithm, control=control, sample_file=sample_file, diagnostic_file=diagnostic_file, save_dso=save_dso, verbose=verbose, include=include, cores=cores, open_progress=open_progress, chain_id=chain_id, init_r=init_r, test_grad=test_grad, append_samples=append_samples, refresh=refresh, enable_random_init=enable_random_init, save_warmup=save_warmup, boost_lib=boost_lib, eigen_lib=eigen_lib)
  }else if(model == "non_auxiliary"){
    results <- run_non_auxiliary_binder(prepared_data, mu_psi=mu_psi, sigma_psi=sigma_psi, model_summary=model_summary, model_summary_parameters=model_summary_parameters, model_name=model_name, fit=fit, chains=chains, iter=iter, warmup=warmup, thin=thin, init=init, seed=seed, algorithm=algorithm, control=control, sample_file=sample_file, diagnostic_file=diagnostic_file, save_dso=save_dso, verbose=verbose, include=include, cores=cores, open_progress=open_progress, chain_id=chain_id, init_r=init_r, test_grad=test_grad, append_samples=append_samples, refresh=refresh, enable_random_init=enable_random_init, save_warmup=save_warmup, boost_lib=boost_lib, eigen_lib=eigen_lib)
  }else if(model == "deterministic"){
    results <- run_deterministic_binder(prepared_data, mu_zeta=mu_zeta, sigma_zeta=sigma_zeta, mu_tau=mu_tau, sigma_tau=sigma_tau, mu_psi=mu_psi, sigma_psi=sigma_psi, model_summary=model_summary, model_summary_parameters=model_summary_parameters, model_name=model_name, fit=fit, chains=chains, iter=iter, warmup=warmup, thin=thin, init=init, seed=seed, algorithm=algorithm, control=control, sample_file=sample_file, diagnostic_file=diagnostic_file, save_dso=save_dso, verbose=verbose, include=include, cores=cores, open_progress=open_progress, chain_id=chain_id, init_r=init_r, test_grad=test_grad, append_samples=append_samples, refresh=refresh, enable_random_init=enable_random_init, save_warmup=save_warmup, boost_lib=boost_lib, eigen_lib=eigen_lib)
  }
  return(results)
}

#----------------------------------------------------------------------------------------------------
