#include "Node.h"

namespace Venom::Scene
{
class Scene
{
public:
  Scene()
  {
  }

  ~Scene() {}

  RootNode& getRoot()
  {
    return m_root;
  }

  Node createNode()
  {
    Node newNode(&m_root);
    m_nodes.push_back(newNode);

    return newNode;
  }

private:
  RootNode m_root;
  std::vector<Node> m_nodes;
};
}
