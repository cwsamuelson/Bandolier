#ifndef BANDOLIER_ORTHOGRAPHIC_CAMERA_HH
#define BANDOLIER_ORTHOGRAPHIC_CAMERA_HH

#include "glm/glm.hpp"

namespace Bandolier {

class OrthographicCamera
{
private:
  void
  RecalculateViewMatrix();

  glm::mat4 mProjection;
  glm::mat4 mView;
  glm::mat4 mViewProjection;

  glm::vec3 mPosition = {0.0f, 0.0f, 0.0f};
  float mRotation = 0.0f;

public:
  OrthographicCamera(float left, float right, float bottom, float top);

  [[nodiscard]]
  const glm::vec3&
  GetPosition() const;

  void
  SetPosition(const glm::vec3& position);

  [[nodiscard]]
  const glm::mat4&
  GetProjection() const;

  void
  SetRotation(float rotation);

  [[nodiscard]]
  const glm::mat4&
  GetView() const;

  [[nodiscard]]
  const glm::mat4&
  GetViewProjection() const;

  void
  SetProjection(float left, float right, float bottom, float top);
};

}

#endif //BANDOLIER_ORTHOGRAPHIC_CAMERA_HH
