#pragma once

#include <exception>
#include <stdexcept>

#include <vector>
#include <string>

#include "Core/Types.h"

namespace Venom::Scene
{

class Node
{
protected:
  Node() {}

public:
  Node(Node* parent)
  {
    m_name = "Node";

    m_transform = Venom::Core::Transform::Identity();

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

  Venom::Core::Transform& getTransform()
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

  void setTransform(Venom::Core::Transform& transform)
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
  Venom::Core::Transform m_transform;

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

  void setTransform(Venom::Core::Transform& transform)
  {
    throw std::runtime_error("Cannot set transform of root object");
  }

  void setParent(Node* parent)
  {
    throw std::runtime_error("Cannot set parent of root object");
  }
};
}
