#include "Scene.h"

int main()
{
  Venom::Scene::Scene* scene = new Venom::Scene::Scene();
  Venom::Scene::Node* newSceneNode = scene->createNode();

  return 0;
}
