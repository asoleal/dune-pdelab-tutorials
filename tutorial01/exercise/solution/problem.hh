template<typename Number>
class Problem
{
  Number eta;
public:
  typedef Number value_type;

  //! Constructor without arg sets nonlinear term to zero
  Problem () : eta(0.0) {}

  //! Constructor takes eta parameter
  Problem (const Number& eta_) : eta(eta_) {}

  //! nonlinearity
  Number q (Number u) const
  {
    return eta*u*u;
    // return std::exp(eta*u);
  }

  //! derivative of nonlinearity
  Number qprime (Number u) const
  {
    return 2*eta*u;
    // return eta*std::exp(eta*u);
  }

  //! right hand side
  template<typename E, typename X>
  Number f (const E& e, const X& x) const
  {
    auto global = e.geometry().global(x);
    Number s=0.0;
    for (std::size_t i=0; i<global.size(); i++) s+=global[i]*global[i];
    // return -2.0*x.size()+eta*s*s;
    // return -2.0*x.size()+std::exp(eta*s);
    return -2.0*x.size();
    // for (std::size_t i=0; i<global.size(); i++) s+=global[i];
    // auto exp = std::exp(s/x.size());
    // return -exp/x.size()+eta*exp*exp;
  }

  //! boundary condition type function (true = Dirichlet)
  template<typename I, typename X>
  bool b (const I& i, const X& x) const
  {
    return true;
  }

  //! Dirichlet extension
  template<typename E, typename X>
  Number g (const E& e, const X& x) const
  {
    auto global = e.geometry().global(x);
    Number s=0.0;
    for (std::size_t i=0; i<global.size(); i++) s+=global[i]*global[i];
    return s;
    // for (std::size_t i=0; i<global.size(); i++) s+=global[i];
    // return std::exp(s/x.size());
  }

  //! Neumann boundary condition
  template<typename I, typename X>
  Number j (const I& i, const X& x) const
  {
    return 0.0;
  }
};
