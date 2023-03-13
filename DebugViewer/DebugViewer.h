#pragma once

#include "raylib.h"
#include "rcamera.h"

#include "Scene.h"

#define _MAX_COLUMNS 20

namespace Venom::Viewer
{
class Viewer
{
public:
  Viewer(int width, int height, const char* title)
  {
    // Initialization
    //--------------------------------------------------------------------------------------
    _width = width;
    _height = height;

    // Define the camera to look into our 3d world (position, target, up vector)
    _camera.position = (Vector3){ 0.0f, 2.0f, 4.0f };    // Camera position
    _camera.target = (Vector3){ 0.0f, 2.0f, 0.0f };      // Camera looking at point
    _camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    _camera.fovy = 60.0f;                                // Camera field-of-view Y
    _camera.projection = CAMERA_PERSPECTIVE;             // Camera projection type

    DisableCursor();                    // Limit cursor to relative movement inside the window

    SetTargetFPS(60);                   // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------
  }
  ~Viewer()
  {
  }

  void setScene(Venom::Scene::Scene& scene)
  {
    // Generates some random columns
    for (int i = 0; i < _MAX_COLUMNS; i++)
    {
        _heights[i] = (float)GetRandomValue(1, 12);
        _positions[i] = (Vector3){ (float)GetRandomValue(-15, 15), _heights[i]/2.0f, (float)GetRandomValue(-15, 15) };
        _colors[i] = (Color){ GetRandomValue(20, 255), GetRandomValue(10, 55), 30, 255 };
    }
  }

  void update()
  {
    // Switch camera mode
    if (IsKeyPressed(KEY_ONE))
    {
      _cameraMode = CAMERA_FREE;
      _camera.up = (Vector3){ 0.0f, 1.0f, 0.0f }; // Reset roll
    }

    if (IsKeyPressed(KEY_TWO))
    {
      _cameraMode = CAMERA_FIRST_PERSON;
      _camera.up = (Vector3){ 0.0f, 1.0f, 0.0f }; // Reset roll
    }

    if (IsKeyPressed(KEY_THREE))
    {
      _cameraMode = CAMERA_THIRD_PERSON;
      _camera.up = (Vector3){ 0.0f, 1.0f, 0.0f }; // Reset roll
    }

    if (IsKeyPressed(KEY_FOUR))
    {
      _cameraMode = CAMERA_ORBITAL;
      _camera.up = (Vector3){ 0.0f, 1.0f, 0.0f }; // Reset roll
    }

    // Switch camera projection
    if (IsKeyPressed(KEY_P))
    {
      if (_camera.projection == CAMERA_PERSPECTIVE)
      {
        // Create isometric view
        _cameraMode = CAMERA_THIRD_PERSON;
        // Note: The target distance is related to the render distance in the orthographic projection
        _camera.position = (Vector3){ 0.0f, 2.0f, -100.0f };
        _camera.target = (Vector3){ 0.0f, 2.0f, 0.0f };
        _camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
        _camera.projection = CAMERA_ORTHOGRAPHIC;
        _camera.fovy = 20.0f; // near plane width in CAMERA_ORTHOGRAPHIC
        CameraYaw(&_camera, -135 * DEG2RAD, true);
        CameraPitch(&_camera, -45 * DEG2RAD, true, true, false);
      }
      else if (_camera.projection == CAMERA_ORTHOGRAPHIC)
      {
        // Reset to default view
        _cameraMode = CAMERA_THIRD_PERSON;
        _camera.position = (Vector3){ 0.0f, 2.0f, 10.0f };
        _camera.target = (Vector3){ 0.0f, 2.0f, 0.0f };
        _camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
        _camera.projection = CAMERA_PERSPECTIVE;
        _camera.fovy = 60.0f;
      }
    }

    UpdateCamera(&_camera, _cameraMode);                  // Update camera
  }

  void render()
  {
    BeginDrawing();

    ClearBackground(RAYWHITE);

    BeginMode3D(_camera);

    DrawPlane((Vector3){ 0.0f, 0.0f, 0.0f }, (Vector2){ 32.0f, 32.0f }, LIGHTGRAY); // Draw ground
    DrawCube((Vector3){ -16.0f, 2.5f, 0.0f }, 1.0f, 5.0f, 32.0f, BLUE);     // Draw a blue wall
    DrawCube((Vector3){ 16.0f, 2.5f, 0.0f }, 1.0f, 5.0f, 32.0f, LIME);      // Draw a green wall
    DrawCube((Vector3){ 0.0f, 2.5f, 16.0f }, 32.0f, 5.0f, 1.0f, GOLD);      // Draw a yellow wall

    // Draw some cubes around
    for (int i = 0; i < _MAX_COLUMNS; i++)
    {
        DrawCube(_positions[i], 2.0f, _heights[i], 2.0f, _colors[i]);
        DrawCubeWires(_positions[i], 2.0f, _heights[i], 2.0f, MAROON);
    }

    // Draw player cube
    if (_cameraMode == CAMERA_THIRD_PERSON)
    {
        DrawCube(_camera.target, 0.5f, 0.5f, 0.5f, PURPLE);
        DrawCubeWires(_camera.target, 0.5f, 0.5f, 0.5f, DARKPURPLE);
    }

    EndMode3D();

    // Draw info boxes
    DrawRectangle(5, 5, 330, 100, Fade(SKYBLUE, 0.5f));
    DrawRectangleLines(5, 5, 330, 100, BLUE);

    DrawText("Camera controls:", 15, 15, 10, BLACK);
    DrawText("- Move keys: W, A, S, D, Space, Left-Ctrl", 15, 30, 10, BLACK);
    DrawText("- Look around: arrow keys or mouse", 15, 45, 10, BLACK);
    DrawText("- Camera mode keys: 1, 2, 3, 4", 15, 60, 10, BLACK);
    DrawText("- Zoom keys: num-plus, num-minus or mouse scroll", 15, 75, 10, BLACK);
    DrawText("- Camera projection key: P", 15, 90, 10, BLACK);

    DrawRectangle(600, 5, 195, 100, Fade(SKYBLUE, 0.5f));
    DrawRectangleLines(600, 5, 195, 100, BLUE);

    DrawText("Camera status:", 610, 15, 10, BLACK);
    DrawText(TextFormat("- Mode: %s", (_cameraMode == CAMERA_FREE) ? "FREE" :
                                      (_cameraMode == CAMERA_FIRST_PERSON) ? "FIRST_PERSON" :
                                      (_cameraMode == CAMERA_THIRD_PERSON) ? "THIRD_PERSON" :
                                      (_cameraMode == CAMERA_ORBITAL) ? "ORBITAL" : "CUSTOM"), 610, 30, 10, BLACK);
    DrawText(TextFormat("- Projection: %s", (_camera.projection == CAMERA_PERSPECTIVE) ? "PERSPECTIVE" :
                                            (_camera.projection == CAMERA_ORTHOGRAPHIC) ? "ORTHOGRAPHIC" : "CUSTOM"), 610, 45, 10, BLACK);
    DrawText(TextFormat("- Position: (%06.3f, %06.3f, %06.3f)", _camera.position.x, _camera.position.y, _camera.position.z), 610, 60, 10, BLACK);
    DrawText(TextFormat("- Target: (%06.3f, %06.3f, %06.3f)", _camera.target.x, _camera.target.y, _camera.target.z), 610, 75, 10, BLACK);
    DrawText(TextFormat("- Up: (%06.3f, %06.3f, %06.3f)", _camera.up.x, _camera.up.y, _camera.up.z), 610, 90, 10, BLACK);

    EndDrawing();
  }

private:
  Camera _camera = { 0 };
  int _cameraMode = CAMERA_FREE;

  int _width;
  int _height;

  float _heights[_MAX_COLUMNS] = { 0 };
  Vector3 _positions[_MAX_COLUMNS] = { 0 };
  Color _colors[_MAX_COLUMNS] = { 0 };
};
}

