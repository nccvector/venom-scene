#include <exception>
#include <stdexcept>

#include <vector>
#include <string>

#include <Eigen/Geometry>

namespace Venom::Scene
{
typedef Eigen::Transform<double, 3, Eigen::Affine> Transform;

class Node
{
protected:
  Node() {}

public:
  Node(Node* parent)
  {
    m_name = "Node";

    m_transform = Transform::Identity();

    m_parent = parent;

    // In case of RootNode it will be nullptr
    // Have to find a way to block the user to reach this functionality (make it private?)
    if (parent != nullptr)
      parent->getChildren().push_back(this);
  }

  Node(Node* parent, std::string name) : Node(parent)
  {
    m_name = name;
  }

  ~Node() {}

  Transform& getTransform()
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

  std::string getName()
  {
    return m_name;
  }

  void setTransform(Transform& transform)
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

  std::string m_name;

  // Also hold reference to entity ...
};

class RootNode : public Node
{
public:
  // No matter what parent you assign, it will always have nullptr parent
  RootNode() : Node(nullptr, "Root")
  {
  }

  void setTransform(Transform& transform)
  {
    throw std::runtime_error("Cannot set transform of root object");
  }

  void setParent(Node* parent)
  {
    throw std::runtime_error("Cannot set parent of root object");
  }
};
}
