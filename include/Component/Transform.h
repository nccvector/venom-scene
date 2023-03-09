#include "SceneTypes.h"

namespace Venom::Scene
{
class Transform
{
public:
  Transform()
  {
    // Identity by default
    m_data << 1, 0, 0, 0,
              0, 1, 0, 0,
              0, 0, 1, 0,
              0, 0, 0, 1;
  }

  ~Transform() {}

  Matrix4 getData()
  {
    return m_data;
  }

  void setData(Matrix4 data)
  {
    m_data = data;
  }

private:
  Matrix4 m_data;
};
}

