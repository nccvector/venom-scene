#include <iostream>

#include "Scene.h"
#include "DebugViewer.h"

class Application
{
public:
  Application(int width, int height, const char* title)
  {
    _width = width;
    _height = height;

    // Initialize window
    InitWindow(_width, _height, title);

    // Creating a demo scene
    Venom::Scene::Node newSceneNode = _scene.createNode();

    Eigen::Matrix3d R;
    R = Eigen::AngleAxisd(45, Eigen::Vector3d::UnitZ());

    newSceneNode.getTransform().rotate(R);

    std::cout << _scene.getRoot().getName() << "\n";
    std::cout << _scene.getRoot().getTransform().matrix() << "\n";

    std::cout << newSceneNode.getName() << "\n";
    std::cout << newSceneNode.getTransform().matrix() << "\n";

    // Create a viewer
    _viewer = new Venom::Viewer::Viewer(_width, _height, title);
    _viewer->setScene(_scene);
  }

  ~Application()
  {
    CloseWindow();        // Close window and OpenGL context
    delete _viewer;
  }

  // Make a updateViewerEvent() in future and add as callback to events
  void updateViewer()
  {
    _viewer->update();
  }

  void run()
  {
    // Main game loop
    while (!WindowShouldClose())        // Detect window close button or ESC key
    {
      // Process events
      _viewer->update();

      // Render frame
      _viewer->render();
    }
  }

private:
  Venom::Scene::Scene _scene;
  Venom::Viewer::Viewer* _viewer;
  int _width;
  int _height;
};

int main()
{
  Application app(1280, 720, "Venom App");

  app.run();

  return 0;
}


