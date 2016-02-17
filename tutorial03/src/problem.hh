template<typename Number>
class Problem
{
  Number eta;
  Number t;

public:
  typedef Number value_type;

  //! Constructor without arg sets nonlinear term to zero
  Problem () : eta(0.0), t(0.0) {}

  //! Constructor takes eta parameter
  Problem (const Number& eta_) : eta(eta_), t(0.0) {}

  //! nonlinearity
  Number q (Number u) const
  {
    return eta*u*u;
  }

  //! right hand side
  template<typename E, typename X>
  Number f (const E& e, const X& x) const
  {
    return 0.0;
  }

  //! boundary condition type function (true = Dirichlet)
  template<typename I, typename X>
  bool b (const I& i, const X& x) const
  {
    auto global = i.geometry().global(x);
    return (global[0]<=1e-7) ? true : false;
  }

  //! Dirichlet extension
  template<typename E, typename X>
  Number g (const E& e, const X& x) const
  {
    auto global = e.geometry().global(x);
    if (t<1e-8) return 0.0;
    Number s=sin(2.0*M_PI*t);
    for (int i=1; i<global.size(); i++) s*=sin(global[i]*M_PI)*sin(global[i]*M_PI);
    return s;
  }

  //! Neumann boundary condition
  template<typename I, typename X>
  Number j (const I& i, const X& x) const
  {
    return 0.0;
  }

  void setTime (Number t_)
  {
    t = t_;
  }
};