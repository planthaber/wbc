#include "CartesianConstraint.hpp"
#include <base/samples/RigidBodyStateSE3.hpp>

namespace wbc {

CartesianConstraint::CartesianConstraint(const ConstraintConfig &_config, uint n_robot_joints) :
    Constraint(_config, n_robot_joints){

}

CartesianConstraint::~CartesianConstraint(){

}

} //namespace wbc
