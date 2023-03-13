#pragma once

#include <Eigen/Geometry>

namespace Venom::Core
{
  typedef double Scalar;

  typedef Eigen::Transform<Venom::Core::Scalar, 3, Eigen::Affine> Transform;
  typedef Eigen::Vector3d Vector3;
}
