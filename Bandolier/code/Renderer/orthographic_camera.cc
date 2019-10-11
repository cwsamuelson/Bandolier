#include "../../vendor/glm/glm/gtc/matrix_transform.hpp"

#include "orthographic_camera.hh"

namespace Bandolier{

OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
{
}

void
OrthographicCamera::RecalculateViewMatrix()
{
  glm::mat4 transform = glm::translate(glm::mat4(1.0f), mPosition)
                      * glm::rotate(glm::mat4(1.0f), glm::radians(mRotation), glm::vec3(0, 0, 1));

  mView = glm::inverse(transform);
  mViewProjection = mProjection * mView;
}

const glm::vec3&
OrthographicCamera::GetPosition() const
{
  return mPosition;
}

const glm::mat4&
OrthographicCamera::GetProjection() const
{
  return mProjection;
}

const glm::mat4&
OrthographicCamera::GetView() const
{
  return mView;
}

const glm::mat4&
OrthographicCamera::GetViewProjection() const
{
  return mViewProjection;
}

}
