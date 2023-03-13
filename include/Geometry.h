#include <vector>

#include "Core/Types.h"

namespace Venom::Scene
{

enum class GeometryType
{
  Sphere,
  Plane,
  Cube,
  Cylinder,
  Capsule,
  Cone,
  Mesh
};

class Geometry
{
public:
  virtual Geometry() {}
  
  virtual ~Geometry() {}

protected:
  std::vector<Primitive> _primitives;
  std::vector<Meshes> _primitives;
  GeometryType _type;
};

class Sphere : public Geometry
{
public:
  Sphere() {}

  ~Sphere() {}

private:
  Venom::Core::Transform _transform;
  double _radius;
};

class Plane : public Geometry
{
public:
  Plane() {}

  ~Plane() {}

private:
  Venom::Core::Transform _transform;
};

class Cube : public Geometry
{
public:
  Cube() {}

  ~Cube() {}

private:
  Venom::Core::Transform _transform;
  Venom::Core::Vector3d _size;
};

class Cylinder : public Geometry
{
public:
  Cylinder() {}

  ~Cylinder() {}

private:
  Venom::Core::Transform _transform;
  Venom::Core::Vector3d _radius;
  Venom::Core::Vector3d _height;
};

class Capsule : public Geometry
{
public:
  Capsule() {}

  ~Capsule() {}

private:
  Venom::Core::Transform _transform;
  Venom::Core::Vector3d _radius;
  Venom::Core::Vector3d _height;
};

class Cone : public Geometry
{
public:
  Cone() {}

  ~Cone() {}

private:
  Venom::Core::Transform _transform;
  Venom::Core::Vector3d _radius;
  Venom::Core::Vector3d _height;
};

class Mesh : public Geometry
{
public:
  Mesh() {}

  ~Mesh() {}

private:

};
}
