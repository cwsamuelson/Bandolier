#ifndef BANDOLIER_ORTHOGRAPHIC_CAMERA_CONTROLLER_HH
#define BANDOLIER_ORTHOGRAPHIC_CAMERA_CONTROLLER_HH

#include <layer.hh>
#include "orthographic_camera.hh"

namespace Bandolier {

class OrthographicCameraController
{
private:
  float mAspectRatio = 1.0f;
  float mZoom = 1.0f;
  bool mRotation;

  glm::vec3 mPosition{0.0f, 0.0f, 0.0f};
  float mCameraRotation = 0.0f;
  float mTranslationSpeed = 5.0f;
  float mRotationSpeed = 180.0f;

  OrthographicCamera mCamera;

public:
  OrthographicCameraController(float aspectRatio, bool rotation = false);

  OrthographicCamera& Camera();
  const OrthographicCamera& Camera() const;

  void
  OnUpdate(Bandolier::time_step ts);
};

}

#endif //BANDOLIER_ORTHOGRAPHIC_CAMERA_CONTROLLER_HH
