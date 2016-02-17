template<typename Number>
class Problem
{
  Number lambda;
public:
  typedef Number value_type;

  //! Constructor without arg sets nonlinear term to zero
  Problem () : lambda(0.0) {}

  //! Constructor takes lambda parameter
  Problem (const Number& lambda_) : lambda(lambda_) {}

  //! nonlinearity
  Number q (Number u) const
  {
    return lambda*u*u;
  }

  //! right hand side
  template<typename E, typename X>
  Number f (const E& e, const X& x) const
  {
    auto global = e.geometry().global(x);
    return -2.0*x.size();
  }

  //! boundary condition type function (true = Dirichlet)
  template<typename I, typename X>
  bool b (const I& i, const X& x) const
  {
    auto global = i.geometry().global(x);
    return true;
  }

  //! Dirichlet extension
  template<typename E, typename X>
  Number g (const E& e, const X& x) const
  {
    auto global = e.geometry().global(x);
    Number s=0.0;
    for (int i=0; i<global.size(); i++) s+=global[i]*global[i];
    return s;
  }

  //! Neumann boundary condition
  template<typename I, typename X>
  Number j (const I& i, const X& x) const
  {
    return 0.0;
  }
};