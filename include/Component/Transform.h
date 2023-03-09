#include "SceneTypes.h"

namespace Venom::Scene
{
class Transform
{
public:
  Transform()
  {
    m_data << 1, 2, 3, 4,
              5, 6, 7, 8,
              9, 10, 11, 12,
              13, 14, 15, 16;
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

