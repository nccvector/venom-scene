#include <exception>
#include <stdexcept>

#include<vector>

#include "Component/Transform.h"

namespace Venom::Scene
{
class Node
{
public:

  Node() { }

  Node(Node* parent)
  {
    m_parent = parent;

    // Add to parent's children list
    parent->getChildren().push_back(this);
  }

  ~Node() {}

  Transform getTransform()
  {
    return m_transform;
  }

  Node* getParent()
  {
    return m_parent;
  }

  std::vector<Node*> getChildren()
  {
    return m_children;
  }

  void setTransform(Transform transform)
  {
    m_transform = transform;
  }

  void setParent(Node* parent)
  {
    m_parent = parent;
  }

protected:
  Node* m_parent;
  std::vector<Node*> m_children;
  Transform m_transform;
  // Also hold reference to entity ...
};

class RootNode : public Node
{
public:
  RootNode()
  {
    m_parent = nullptr;
  }

  void setTransform(Transform transform)
  {
    throw std::runtime_error("Cannot set transform of root object");
  }

  void setParent(Node* parent)
  {
    throw std::runtime_error("Cannot set parent of root object");
  }
};
}
