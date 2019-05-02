// Generated by rstantools.  Do not edit by hand.

/*
    BINDER is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    BINDER is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with BINDER.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef MODELS_HPP
#define MODELS_HPP
#define STAN__SERVICES__COMMAND_HPP
#include <rstan/rstaninc.hpp>
// Code generated by Stan version 2.18.1

#include <stan/model/model_header.hpp>

namespace model_binder_namespace {

using std::istream;
using std::string;
using std::stringstream;
using std::vector;
using stan::io::dump;
using stan::math::lgamma;
using stan::model::prob_grad;
using namespace stan::math;

static int current_statement_begin__;

stan::io::program_reader prog_reader__() {
    stan::io::program_reader reader;
    reader.add_event(0, 0, "start", "model_binder");
    reader.add_event(64, 62, "end", "model_binder");
    return reader;
}

#include <stan_meta_header.hpp>
 class model_binder : public prob_grad {
private:
    int N;
    int K;
    int M;
    matrix_d X;
    matrix_d Y;
    double mu_zeta;
    double sigma_zeta;
    vector_d mu_tau;
    vector_d sigma_tau;
    double mu_phi;
    double sigma_phi;
    vector_d mu_psi;
    vector_d sigma_psi;
    matrix_d trans_Y;
public:
    model_binder(stan::io::var_context& context__,
        std::ostream* pstream__ = 0)
        : prob_grad(0) {
        ctor_body(context__, 0, pstream__);
    }

    model_binder(stan::io::var_context& context__,
        unsigned int random_seed__,
        std::ostream* pstream__ = 0)
        : prob_grad(0) {
        ctor_body(context__, random_seed__, pstream__);
    }

    void ctor_body(stan::io::var_context& context__,
                   unsigned int random_seed__,
                   std::ostream* pstream__) {
        typedef double local_scalar_t__;

        boost::ecuyer1988 base_rng__ =
          stan::services::util::create_rng(random_seed__, 0);
        (void) base_rng__;  // suppress unused var warning

        current_statement_begin__ = -1;

        static const char* function__ = "model_binder_namespace::model_binder";
        (void) function__;  // dummy to suppress unused var warning
        size_t pos__;
        (void) pos__;  // dummy to suppress unused var warning
        std::vector<int> vals_i__;
        std::vector<double> vals_r__;
        local_scalar_t__ DUMMY_VAR__(std::numeric_limits<double>::quiet_NaN());
        (void) DUMMY_VAR__;  // suppress unused var warning

        // initialize member variables
        try {
            current_statement_begin__ = 2;
            context__.validate_dims("data initialization", "N", "int", context__.to_vec());
            N = int(0);
            vals_i__ = context__.vals_i("N");
            pos__ = 0;
            N = vals_i__[pos__++];
            current_statement_begin__ = 3;
            context__.validate_dims("data initialization", "K", "int", context__.to_vec());
            K = int(0);
            vals_i__ = context__.vals_i("K");
            pos__ = 0;
            K = vals_i__[pos__++];
            current_statement_begin__ = 4;
            context__.validate_dims("data initialization", "M", "int", context__.to_vec());
            M = int(0);
            vals_i__ = context__.vals_i("M");
            pos__ = 0;
            M = vals_i__[pos__++];
            current_statement_begin__ = 6;
            validate_non_negative_index("X", "N", N);
            validate_non_negative_index("X", "K", K);
            context__.validate_dims("data initialization", "X", "matrix_d", context__.to_vec(N,K));
            validate_non_negative_index("X", "N", N);
            validate_non_negative_index("X", "K", K);
            X = matrix_d(static_cast<Eigen::VectorXd::Index>(N),static_cast<Eigen::VectorXd::Index>(K));
            vals_r__ = context__.vals_r("X");
            pos__ = 0;
            size_t X_m_mat_lim__ = N;
            size_t X_n_mat_lim__ = K;
            for (size_t n_mat__ = 0; n_mat__ < X_n_mat_lim__; ++n_mat__) {
                for (size_t m_mat__ = 0; m_mat__ < X_m_mat_lim__; ++m_mat__) {
                    X(m_mat__,n_mat__) = vals_r__[pos__++];
                }
            }
            current_statement_begin__ = 7;
            validate_non_negative_index("Y", "N", N);
            validate_non_negative_index("Y", "M", M);
            context__.validate_dims("data initialization", "Y", "matrix_d", context__.to_vec(N,M));
            validate_non_negative_index("Y", "N", N);
            validate_non_negative_index("Y", "M", M);
            Y = matrix_d(static_cast<Eigen::VectorXd::Index>(N),static_cast<Eigen::VectorXd::Index>(M));
            vals_r__ = context__.vals_r("Y");
            pos__ = 0;
            size_t Y_m_mat_lim__ = N;
            size_t Y_n_mat_lim__ = M;
            for (size_t n_mat__ = 0; n_mat__ < Y_n_mat_lim__; ++n_mat__) {
                for (size_t m_mat__ = 0; m_mat__ < Y_m_mat_lim__; ++m_mat__) {
                    Y(m_mat__,n_mat__) = vals_r__[pos__++];
                }
            }
            current_statement_begin__ = 10;
            context__.validate_dims("data initialization", "mu_zeta", "double", context__.to_vec());
            mu_zeta = double(0);
            vals_r__ = context__.vals_r("mu_zeta");
            pos__ = 0;
            mu_zeta = vals_r__[pos__++];
            current_statement_begin__ = 11;
            context__.validate_dims("data initialization", "sigma_zeta", "double", context__.to_vec());
            sigma_zeta = double(0);
            vals_r__ = context__.vals_r("sigma_zeta");
            pos__ = 0;
            sigma_zeta = vals_r__[pos__++];
            current_statement_begin__ = 12;
            validate_non_negative_index("mu_tau", "K", K);
            context__.validate_dims("data initialization", "mu_tau", "vector_d", context__.to_vec(K));
            validate_non_negative_index("mu_tau", "K", K);
            mu_tau = vector_d(static_cast<Eigen::VectorXd::Index>(K));
            vals_r__ = context__.vals_r("mu_tau");
            pos__ = 0;
            size_t mu_tau_i_vec_lim__ = K;
            for (size_t i_vec__ = 0; i_vec__ < mu_tau_i_vec_lim__; ++i_vec__) {
                mu_tau[i_vec__] = vals_r__[pos__++];
            }
            current_statement_begin__ = 13;
            validate_non_negative_index("sigma_tau", "K", K);
            context__.validate_dims("data initialization", "sigma_tau", "vector_d", context__.to_vec(K));
            validate_non_negative_index("sigma_tau", "K", K);
            sigma_tau = vector_d(static_cast<Eigen::VectorXd::Index>(K));
            vals_r__ = context__.vals_r("sigma_tau");
            pos__ = 0;
            size_t sigma_tau_i_vec_lim__ = K;
            for (size_t i_vec__ = 0; i_vec__ < sigma_tau_i_vec_lim__; ++i_vec__) {
                sigma_tau[i_vec__] = vals_r__[pos__++];
            }
            current_statement_begin__ = 15;
            context__.validate_dims("data initialization", "mu_phi", "double", context__.to_vec());
            mu_phi = double(0);
            vals_r__ = context__.vals_r("mu_phi");
            pos__ = 0;
            mu_phi = vals_r__[pos__++];
            current_statement_begin__ = 16;
            context__.validate_dims("data initialization", "sigma_phi", "double", context__.to_vec());
            sigma_phi = double(0);
            vals_r__ = context__.vals_r("sigma_phi");
            pos__ = 0;
            sigma_phi = vals_r__[pos__++];
            current_statement_begin__ = 18;
            validate_non_negative_index("mu_psi", "M", M);
            context__.validate_dims("data initialization", "mu_psi", "vector_d", context__.to_vec(M));
            validate_non_negative_index("mu_psi", "M", M);
            mu_psi = vector_d(static_cast<Eigen::VectorXd::Index>(M));
            vals_r__ = context__.vals_r("mu_psi");
            pos__ = 0;
            size_t mu_psi_i_vec_lim__ = M;
            for (size_t i_vec__ = 0; i_vec__ < mu_psi_i_vec_lim__; ++i_vec__) {
                mu_psi[i_vec__] = vals_r__[pos__++];
            }
            current_statement_begin__ = 19;
            validate_non_negative_index("sigma_psi", "M", M);
            context__.validate_dims("data initialization", "sigma_psi", "vector_d", context__.to_vec(M));
            validate_non_negative_index("sigma_psi", "M", M);
            sigma_psi = vector_d(static_cast<Eigen::VectorXd::Index>(M));
            vals_r__ = context__.vals_r("sigma_psi");
            pos__ = 0;
            size_t sigma_psi_i_vec_lim__ = M;
            for (size_t i_vec__ = 0; i_vec__ < sigma_psi_i_vec_lim__; ++i_vec__) {
                sigma_psi[i_vec__] = vals_r__[pos__++];
            }

            // validate, data variables
            current_statement_begin__ = 2;
            current_statement_begin__ = 3;
            current_statement_begin__ = 4;
            current_statement_begin__ = 6;
            current_statement_begin__ = 7;
            check_greater_or_equal(function__,"Y",Y,0);
            check_less_or_equal(function__,"Y",Y,1);
            current_statement_begin__ = 10;
            current_statement_begin__ = 11;
            check_greater_or_equal(function__,"sigma_zeta",sigma_zeta,0);
            current_statement_begin__ = 12;
            check_greater_or_equal(function__,"mu_tau",mu_tau,0);
            current_statement_begin__ = 13;
            check_greater_or_equal(function__,"sigma_tau",sigma_tau,0);
            current_statement_begin__ = 15;
            check_greater_or_equal(function__,"mu_phi",mu_phi,0);
            current_statement_begin__ = 16;
            check_greater_or_equal(function__,"sigma_phi",sigma_phi,0);
            current_statement_begin__ = 18;
            check_greater_or_equal(function__,"mu_psi",mu_psi,0);
            current_statement_begin__ = 19;
            check_greater_or_equal(function__,"sigma_psi",sigma_psi,0);
            // initialize data variables
            current_statement_begin__ = 23;
            validate_non_negative_index("trans_Y", "N", N);
            validate_non_negative_index("trans_Y", "M", M);
            trans_Y = matrix_d(static_cast<Eigen::VectorXd::Index>(N),static_cast<Eigen::VectorXd::Index>(M));
            stan::math::fill(trans_Y,DUMMY_VAR__);

            current_statement_begin__ = 25;
            stan::math::assign(trans_Y, logit(Y));

            // validate transformed data
            current_statement_begin__ = 23;

            // validate, set parameter ranges
            num_params_r__ = 0U;
            param_ranges_i__.clear();
            current_statement_begin__ = 29;
            ++num_params_r__;
            current_statement_begin__ = 30;
            validate_non_negative_index("tau", "K", K);
            num_params_r__ += K;
            current_statement_begin__ = 32;
            validate_non_negative_index("raw_gamma", "N", N);
            num_params_r__ += N;
            current_statement_begin__ = 33;
            ++num_params_r__;
            current_statement_begin__ = 35;
            validate_non_negative_index("psi", "M", M);
            num_params_r__ += M;
        } catch (const std::exception& e) {
            stan::lang::rethrow_located(e, current_statement_begin__, prog_reader__());
            // Next line prevents compiler griping about no return
            throw std::runtime_error("*** IF YOU SEE THIS, PLEASE REPORT A BUG ***");
        }
    }

    ~model_binder() { }


    void transform_inits(const stan::io::var_context& context__,
                         std::vector<int>& params_i__,
                         std::vector<double>& params_r__,
                         std::ostream* pstream__) const {
        stan::io::writer<double> writer__(params_r__,params_i__);
        size_t pos__;
        (void) pos__; // dummy call to supress warning
        std::vector<double> vals_r__;
        std::vector<int> vals_i__;

        if (!(context__.contains_r("zeta")))
            throw std::runtime_error("variable zeta missing");
        vals_r__ = context__.vals_r("zeta");
        pos__ = 0U;
        context__.validate_dims("initialization", "zeta", "double", context__.to_vec());
        double zeta(0);
        zeta = vals_r__[pos__++];
        try {
            writer__.scalar_unconstrain(zeta);
        } catch (const std::exception& e) { 
            throw std::runtime_error(std::string("Error transforming variable zeta: ") + e.what());
        }

        if (!(context__.contains_r("tau")))
            throw std::runtime_error("variable tau missing");
        vals_r__ = context__.vals_r("tau");
        pos__ = 0U;
        validate_non_negative_index("tau", "K", K);
        context__.validate_dims("initialization", "tau", "vector_d", context__.to_vec(K));
        vector_d tau(static_cast<Eigen::VectorXd::Index>(K));
        for (int j1__ = 0U; j1__ < K; ++j1__)
            tau(j1__) = vals_r__[pos__++];
        try {
            writer__.vector_lb_unconstrain(0,tau);
        } catch (const std::exception& e) { 
            throw std::runtime_error(std::string("Error transforming variable tau: ") + e.what());
        }

        if (!(context__.contains_r("raw_gamma")))
            throw std::runtime_error("variable raw_gamma missing");
        vals_r__ = context__.vals_r("raw_gamma");
        pos__ = 0U;
        validate_non_negative_index("raw_gamma", "N", N);
        context__.validate_dims("initialization", "raw_gamma", "vector_d", context__.to_vec(N));
        vector_d raw_gamma(static_cast<Eigen::VectorXd::Index>(N));
        for (int j1__ = 0U; j1__ < N; ++j1__)
            raw_gamma(j1__) = vals_r__[pos__++];
        try {
            writer__.vector_unconstrain(raw_gamma);
        } catch (const std::exception& e) { 
            throw std::runtime_error(std::string("Error transforming variable raw_gamma: ") + e.what());
        }

        if (!(context__.contains_r("phi")))
            throw std::runtime_error("variable phi missing");
        vals_r__ = context__.vals_r("phi");
        pos__ = 0U;
        context__.validate_dims("initialization", "phi", "double", context__.to_vec());
        double phi(0);
        phi = vals_r__[pos__++];
        try {
            writer__.scalar_lb_unconstrain(0,phi);
        } catch (const std::exception& e) { 
            throw std::runtime_error(std::string("Error transforming variable phi: ") + e.what());
        }

        if (!(context__.contains_r("psi")))
            throw std::runtime_error("variable psi missing");
        vals_r__ = context__.vals_r("psi");
        pos__ = 0U;
        validate_non_negative_index("psi", "M", M);
        context__.validate_dims("initialization", "psi", "vector_d", context__.to_vec(M));
        vector_d psi(static_cast<Eigen::VectorXd::Index>(M));
        for (int j1__ = 0U; j1__ < M; ++j1__)
            psi(j1__) = vals_r__[pos__++];
        try {
            writer__.vector_lb_unconstrain(0,psi);
        } catch (const std::exception& e) { 
            throw std::runtime_error(std::string("Error transforming variable psi: ") + e.what());
        }

        params_r__ = writer__.data_r();
        params_i__ = writer__.data_i();
    }

    void transform_inits(const stan::io::var_context& context,
                         Eigen::Matrix<double,Eigen::Dynamic,1>& params_r,
                         std::ostream* pstream__) const {
      std::vector<double> params_r_vec;
      std::vector<int> params_i_vec;
      transform_inits(context, params_i_vec, params_r_vec, pstream__);
      params_r.resize(params_r_vec.size());
      for (int i = 0; i < params_r.size(); ++i)
        params_r(i) = params_r_vec[i];
    }


    template <bool propto__, bool jacobian__, typename T__>
    T__ log_prob(vector<T__>& params_r__,
                 vector<int>& params_i__,
                 std::ostream* pstream__ = 0) const {

        typedef T__ local_scalar_t__;

        local_scalar_t__ DUMMY_VAR__(std::numeric_limits<double>::quiet_NaN());
        (void) DUMMY_VAR__;  // suppress unused var warning

        T__ lp__(0.0);
        stan::math::accumulator<T__> lp_accum__;

        try {
            // model parameters
            stan::io::reader<local_scalar_t__> in__(params_r__,params_i__);

            local_scalar_t__ zeta;
            (void) zeta;  // dummy to suppress unused var warning
            if (jacobian__)
                zeta = in__.scalar_constrain(lp__);
            else
                zeta = in__.scalar_constrain();

            Eigen::Matrix<local_scalar_t__,Eigen::Dynamic,1>  tau;
            (void) tau;  // dummy to suppress unused var warning
            if (jacobian__)
                tau = in__.vector_lb_constrain(0,K,lp__);
            else
                tau = in__.vector_lb_constrain(0,K);

            Eigen::Matrix<local_scalar_t__,Eigen::Dynamic,1>  raw_gamma;
            (void) raw_gamma;  // dummy to suppress unused var warning
            if (jacobian__)
                raw_gamma = in__.vector_constrain(N,lp__);
            else
                raw_gamma = in__.vector_constrain(N);

            local_scalar_t__ phi;
            (void) phi;  // dummy to suppress unused var warning
            if (jacobian__)
                phi = in__.scalar_lb_constrain(0,lp__);
            else
                phi = in__.scalar_lb_constrain(0);

            Eigen::Matrix<local_scalar_t__,Eigen::Dynamic,1>  psi;
            (void) psi;  // dummy to suppress unused var warning
            if (jacobian__)
                psi = in__.vector_lb_constrain(0,M,lp__);
            else
                psi = in__.vector_lb_constrain(0,M);


            // transformed parameters
            current_statement_begin__ = 39;
            validate_non_negative_index("gamma", "N", N);
            Eigen::Matrix<local_scalar_t__,Eigen::Dynamic,1>  gamma(static_cast<Eigen::VectorXd::Index>(N));
            (void) gamma;  // dummy to suppress unused var warning

            stan::math::initialize(gamma, DUMMY_VAR__);
            stan::math::fill(gamma,DUMMY_VAR__);
            current_statement_begin__ = 40;
            validate_non_negative_index("trans_theta", "N", N);
            Eigen::Matrix<local_scalar_t__,Eigen::Dynamic,1>  trans_theta(static_cast<Eigen::VectorXd::Index>(N));
            (void) trans_theta;  // dummy to suppress unused var warning

            stan::math::initialize(trans_theta, DUMMY_VAR__);
            stan::math::fill(trans_theta,DUMMY_VAR__);
            current_statement_begin__ = 41;
            validate_non_negative_index("theta", "N", N);
            Eigen::Matrix<local_scalar_t__,Eigen::Dynamic,1>  theta(static_cast<Eigen::VectorXd::Index>(N));
            (void) theta;  // dummy to suppress unused var warning

            stan::math::initialize(theta, DUMMY_VAR__);
            stan::math::fill(theta,DUMMY_VAR__);


            current_statement_begin__ = 43;
            stan::math::assign(gamma, add(zeta,multiply(X,tau)));
            current_statement_begin__ = 44;
            stan::math::assign(trans_theta, multiply(add(raw_gamma,gamma),phi));
            current_statement_begin__ = 45;
            stan::math::assign(theta, inv_logit(trans_theta));

            // validate transformed parameters
            for (int i0__ = 0; i0__ < N; ++i0__) {
                if (stan::math::is_uninitialized(gamma(i0__))) {
                    std::stringstream msg__;
                    msg__ << "Undefined transformed parameter: gamma" << '[' << i0__ << ']';
                    throw std::runtime_error(msg__.str());
                }
            }
            for (int i0__ = 0; i0__ < N; ++i0__) {
                if (stan::math::is_uninitialized(trans_theta(i0__))) {
                    std::stringstream msg__;
                    msg__ << "Undefined transformed parameter: trans_theta" << '[' << i0__ << ']';
                    throw std::runtime_error(msg__.str());
                }
            }
            for (int i0__ = 0; i0__ < N; ++i0__) {
                if (stan::math::is_uninitialized(theta(i0__))) {
                    std::stringstream msg__;
                    msg__ << "Undefined transformed parameter: theta" << '[' << i0__ << ']';
                    throw std::runtime_error(msg__.str());
                }
            }

            const char* function__ = "validate transformed params";
            (void) function__;  // dummy to suppress unused var warning
            current_statement_begin__ = 39;
            current_statement_begin__ = 40;
            current_statement_begin__ = 41;
            check_greater_or_equal(function__,"theta",theta,0);
            check_less_or_equal(function__,"theta",theta,1);

            // model body

            current_statement_begin__ = 50;
            lp_accum__.add(normal_log<propto__>(zeta, mu_zeta, sigma_zeta));
            current_statement_begin__ = 51;
            lp_accum__.add(normal_log<propto__>(tau, mu_tau, sigma_tau));
            current_statement_begin__ = 53;
            lp_accum__.add(normal_log<propto__>(raw_gamma, 0, 1));
            current_statement_begin__ = 54;
            lp_accum__.add(normal_log<propto__>(phi, mu_phi, sigma_phi));
            current_statement_begin__ = 56;
            lp_accum__.add(normal_log<propto__>(psi, mu_psi, sigma_psi));
            current_statement_begin__ = 59;
            for (int m = 1; m <= M; ++m) {

                current_statement_begin__ = 60;
                lp_accum__.add(normal_log<propto__>(stan::model::rvalue(trans_Y, stan::model::cons_list(stan::model::index_omni(), stan::model::cons_list(stan::model::index_uni(m), stan::model::nil_index_list())), "trans_Y"), trans_theta, get_base1(psi,m,"psi",1)));
            }

        } catch (const std::exception& e) {
            stan::lang::rethrow_located(e, current_statement_begin__, prog_reader__());
            // Next line prevents compiler griping about no return
            throw std::runtime_error("*** IF YOU SEE THIS, PLEASE REPORT A BUG ***");
        }

        lp_accum__.add(lp__);
        return lp_accum__.sum();

    } // log_prob()

    template <bool propto, bool jacobian, typename T_>
    T_ log_prob(Eigen::Matrix<T_,Eigen::Dynamic,1>& params_r,
               std::ostream* pstream = 0) const {
      std::vector<T_> vec_params_r;
      vec_params_r.reserve(params_r.size());
      for (int i = 0; i < params_r.size(); ++i)
        vec_params_r.push_back(params_r(i));
      std::vector<int> vec_params_i;
      return log_prob<propto,jacobian,T_>(vec_params_r, vec_params_i, pstream);
    }


    void get_param_names(std::vector<std::string>& names__) const {
        names__.resize(0);
        names__.push_back("zeta");
        names__.push_back("tau");
        names__.push_back("raw_gamma");
        names__.push_back("phi");
        names__.push_back("psi");
        names__.push_back("gamma");
        names__.push_back("trans_theta");
        names__.push_back("theta");
    }


    void get_dims(std::vector<std::vector<size_t> >& dimss__) const {
        dimss__.resize(0);
        std::vector<size_t> dims__;
        dims__.resize(0);
        dimss__.push_back(dims__);
        dims__.resize(0);
        dims__.push_back(K);
        dimss__.push_back(dims__);
        dims__.resize(0);
        dims__.push_back(N);
        dimss__.push_back(dims__);
        dims__.resize(0);
        dimss__.push_back(dims__);
        dims__.resize(0);
        dims__.push_back(M);
        dimss__.push_back(dims__);
        dims__.resize(0);
        dims__.push_back(N);
        dimss__.push_back(dims__);
        dims__.resize(0);
        dims__.push_back(N);
        dimss__.push_back(dims__);
        dims__.resize(0);
        dims__.push_back(N);
        dimss__.push_back(dims__);
    }

    template <typename RNG>
    void write_array(RNG& base_rng__,
                     std::vector<double>& params_r__,
                     std::vector<int>& params_i__,
                     std::vector<double>& vars__,
                     bool include_tparams__ = true,
                     bool include_gqs__ = true,
                     std::ostream* pstream__ = 0) const {
        typedef double local_scalar_t__;

        vars__.resize(0);
        stan::io::reader<local_scalar_t__> in__(params_r__,params_i__);
        static const char* function__ = "model_binder_namespace::write_array";
        (void) function__;  // dummy to suppress unused var warning
        // read-transform, write parameters
        double zeta = in__.scalar_constrain();
        vector_d tau = in__.vector_lb_constrain(0,K);
        vector_d raw_gamma = in__.vector_constrain(N);
        double phi = in__.scalar_lb_constrain(0);
        vector_d psi = in__.vector_lb_constrain(0,M);
        vars__.push_back(zeta);
            for (int k_0__ = 0; k_0__ < K; ++k_0__) {
            vars__.push_back(tau[k_0__]);
            }
            for (int k_0__ = 0; k_0__ < N; ++k_0__) {
            vars__.push_back(raw_gamma[k_0__]);
            }
        vars__.push_back(phi);
            for (int k_0__ = 0; k_0__ < M; ++k_0__) {
            vars__.push_back(psi[k_0__]);
            }

        // declare and define transformed parameters
        double lp__ = 0.0;
        (void) lp__;  // dummy to suppress unused var warning
        stan::math::accumulator<double> lp_accum__;

        local_scalar_t__ DUMMY_VAR__(std::numeric_limits<double>::quiet_NaN());
        (void) DUMMY_VAR__;  // suppress unused var warning

        try {
            current_statement_begin__ = 39;
            validate_non_negative_index("gamma", "N", N);
            Eigen::Matrix<local_scalar_t__,Eigen::Dynamic,1>  gamma(static_cast<Eigen::VectorXd::Index>(N));
            (void) gamma;  // dummy to suppress unused var warning

            stan::math::initialize(gamma, DUMMY_VAR__);
            stan::math::fill(gamma,DUMMY_VAR__);
            current_statement_begin__ = 40;
            validate_non_negative_index("trans_theta", "N", N);
            Eigen::Matrix<local_scalar_t__,Eigen::Dynamic,1>  trans_theta(static_cast<Eigen::VectorXd::Index>(N));
            (void) trans_theta;  // dummy to suppress unused var warning

            stan::math::initialize(trans_theta, DUMMY_VAR__);
            stan::math::fill(trans_theta,DUMMY_VAR__);
            current_statement_begin__ = 41;
            validate_non_negative_index("theta", "N", N);
            Eigen::Matrix<local_scalar_t__,Eigen::Dynamic,1>  theta(static_cast<Eigen::VectorXd::Index>(N));
            (void) theta;  // dummy to suppress unused var warning

            stan::math::initialize(theta, DUMMY_VAR__);
            stan::math::fill(theta,DUMMY_VAR__);


            current_statement_begin__ = 43;
            stan::math::assign(gamma, add(zeta,multiply(X,tau)));
            current_statement_begin__ = 44;
            stan::math::assign(trans_theta, multiply(add(raw_gamma,gamma),phi));
            current_statement_begin__ = 45;
            stan::math::assign(theta, inv_logit(trans_theta));

            // validate transformed parameters
            current_statement_begin__ = 39;
            current_statement_begin__ = 40;
            current_statement_begin__ = 41;
            check_greater_or_equal(function__,"theta",theta,0);
            check_less_or_equal(function__,"theta",theta,1);

            // write transformed parameters
            if (include_tparams__) {
            for (int k_0__ = 0; k_0__ < N; ++k_0__) {
            vars__.push_back(gamma[k_0__]);
            }
            for (int k_0__ = 0; k_0__ < N; ++k_0__) {
            vars__.push_back(trans_theta[k_0__]);
            }
            for (int k_0__ = 0; k_0__ < N; ++k_0__) {
            vars__.push_back(theta[k_0__]);
            }
            }
            if (!include_gqs__) return;
            // declare and define generated quantities



            // validate generated quantities

            // write generated quantities
        } catch (const std::exception& e) {
            stan::lang::rethrow_located(e, current_statement_begin__, prog_reader__());
            // Next line prevents compiler griping about no return
            throw std::runtime_error("*** IF YOU SEE THIS, PLEASE REPORT A BUG ***");
        }
    }

    template <typename RNG>
    void write_array(RNG& base_rng,
                     Eigen::Matrix<double,Eigen::Dynamic,1>& params_r,
                     Eigen::Matrix<double,Eigen::Dynamic,1>& vars,
                     bool include_tparams = true,
                     bool include_gqs = true,
                     std::ostream* pstream = 0) const {
      std::vector<double> params_r_vec(params_r.size());
      for (int i = 0; i < params_r.size(); ++i)
        params_r_vec[i] = params_r(i);
      std::vector<double> vars_vec;
      std::vector<int> params_i_vec;
      write_array(base_rng,params_r_vec,params_i_vec,vars_vec,include_tparams,include_gqs,pstream);
      vars.resize(vars_vec.size());
      for (int i = 0; i < vars.size(); ++i)
        vars(i) = vars_vec[i];
    }

    static std::string model_name() {
        return "model_binder";
    }


    void constrained_param_names(std::vector<std::string>& param_names__,
                                 bool include_tparams__ = true,
                                 bool include_gqs__ = true) const {
        std::stringstream param_name_stream__;
        param_name_stream__.str(std::string());
        param_name_stream__ << "zeta";
        param_names__.push_back(param_name_stream__.str());
        for (int k_0__ = 1; k_0__ <= K; ++k_0__) {
            param_name_stream__.str(std::string());
            param_name_stream__ << "tau" << '.' << k_0__;
            param_names__.push_back(param_name_stream__.str());
        }
        for (int k_0__ = 1; k_0__ <= N; ++k_0__) {
            param_name_stream__.str(std::string());
            param_name_stream__ << "raw_gamma" << '.' << k_0__;
            param_names__.push_back(param_name_stream__.str());
        }
        param_name_stream__.str(std::string());
        param_name_stream__ << "phi";
        param_names__.push_back(param_name_stream__.str());
        for (int k_0__ = 1; k_0__ <= M; ++k_0__) {
            param_name_stream__.str(std::string());
            param_name_stream__ << "psi" << '.' << k_0__;
            param_names__.push_back(param_name_stream__.str());
        }

        if (!include_gqs__ && !include_tparams__) return;

        if (include_tparams__) {
            for (int k_0__ = 1; k_0__ <= N; ++k_0__) {
                param_name_stream__.str(std::string());
                param_name_stream__ << "gamma" << '.' << k_0__;
                param_names__.push_back(param_name_stream__.str());
            }
            for (int k_0__ = 1; k_0__ <= N; ++k_0__) {
                param_name_stream__.str(std::string());
                param_name_stream__ << "trans_theta" << '.' << k_0__;
                param_names__.push_back(param_name_stream__.str());
            }
            for (int k_0__ = 1; k_0__ <= N; ++k_0__) {
                param_name_stream__.str(std::string());
                param_name_stream__ << "theta" << '.' << k_0__;
                param_names__.push_back(param_name_stream__.str());
            }
        }


        if (!include_gqs__) return;
    }


    void unconstrained_param_names(std::vector<std::string>& param_names__,
                                   bool include_tparams__ = true,
                                   bool include_gqs__ = true) const {
        std::stringstream param_name_stream__;
        param_name_stream__.str(std::string());
        param_name_stream__ << "zeta";
        param_names__.push_back(param_name_stream__.str());
        for (int k_0__ = 1; k_0__ <= K; ++k_0__) {
            param_name_stream__.str(std::string());
            param_name_stream__ << "tau" << '.' << k_0__;
            param_names__.push_back(param_name_stream__.str());
        }
        for (int k_0__ = 1; k_0__ <= N; ++k_0__) {
            param_name_stream__.str(std::string());
            param_name_stream__ << "raw_gamma" << '.' << k_0__;
            param_names__.push_back(param_name_stream__.str());
        }
        param_name_stream__.str(std::string());
        param_name_stream__ << "phi";
        param_names__.push_back(param_name_stream__.str());
        for (int k_0__ = 1; k_0__ <= M; ++k_0__) {
            param_name_stream__.str(std::string());
            param_name_stream__ << "psi" << '.' << k_0__;
            param_names__.push_back(param_name_stream__.str());
        }

        if (!include_gqs__ && !include_tparams__) return;

        if (include_tparams__) {
            for (int k_0__ = 1; k_0__ <= N; ++k_0__) {
                param_name_stream__.str(std::string());
                param_name_stream__ << "gamma" << '.' << k_0__;
                param_names__.push_back(param_name_stream__.str());
            }
            for (int k_0__ = 1; k_0__ <= N; ++k_0__) {
                param_name_stream__.str(std::string());
                param_name_stream__ << "trans_theta" << '.' << k_0__;
                param_names__.push_back(param_name_stream__.str());
            }
            for (int k_0__ = 1; k_0__ <= N; ++k_0__) {
                param_name_stream__.str(std::string());
                param_name_stream__ << "theta" << '.' << k_0__;
                param_names__.push_back(param_name_stream__.str());
            }
        }


        if (!include_gqs__) return;
    }

}; // model

}

typedef model_binder_namespace::model_binder stan_model;


#endif
