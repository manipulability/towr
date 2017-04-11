/**
 @file    nlp.h
 @author  Alexander W. Winkler (winklera@ethz.ch)
 @date    Jul 1, 2016
 @brief   Brief description
 */

#ifndef USER_TASK_DEPENDS_XPP_OPT_INCLUDE_XPP_OPT_NLP_H_
#define USER_TASK_DEPENDS_XPP_OPT_INCLUDE_XPP_OPT_NLP_H_

#include "constraint_container.h"
#include "cost_container.h"
#include "optimization_variables_container.h"
#include <memory>

namespace xpp {
namespace opt {

/** @brief Nonlinear Programming problem definition
  *
  * This class is responsible for holding all the information of a
  * Nonlinear Program, which includes the optimization variables, their bounds,
  * the cost function, the constraint function, constraint bounds  and possibly
  * derivatives.
  */
class NLP {
public:
  typedef Constraint::Jacobian Jacobian;
  typedef double Number;
  typedef Eigen::VectorXd VectorXd;

  typedef std::shared_ptr<Jacobian> JacobianPtr;
  typedef std::shared_ptr<OptimizationVariablesContainer> OptimizationVariablesPtr;

  using CostPtr = std::shared_ptr<Cost>;
  using ConstraintPtr = std::shared_ptr<Constraint>;
  using ConstraitPtrVec = std::vector<ConstraintPtr>;

  NLP ();
  virtual ~NLP ();

  void Init(OptimizationVariablesPtr&);
  void SetVariables(const Number* x);

  int GetNumberOfOptimizationVariables() const;
  bool HasCostTerms() const;
  VecBound GetBoundsOnOptimizationVariables() const;
  VectorXd GetStartingValues() const;

  double EvaluateCostFunction(const Number* x);
  VectorXd EvaluateCostFunctionGradient(const Number* x);

  int GetNumberOfConstraints() const;
  VecBound GetBoundsOnConstraints() const;
  VectorXd EvaluateConstraints(const Number* x);

  void EvalNonzerosOfJacobian(const Number* x, Number* values);
  JacobianPtr GetJacobianOfConstraints() const;

  void PrintStatusOfConstraints(double tol) const;

  void AddCost(CostPtr cost, double weight);
  void AddConstraint(ConstraitPtrVec constraints);

private:
  // zmp_ make actual classes, ownership, composition.
  OptimizationVariablesPtr opt_variables_;
  CostContainer costs_;
  ConstraintContainer constraints_;

  VectorXd ConvertToEigen(const Number* x) const;
};

} /* namespace opt */
} /* namespace xpp */

#endif /* USER_TASK_DEPENDS_XPP_OPT_INCLUDE_XPP_OPT_NLP_H_ */
