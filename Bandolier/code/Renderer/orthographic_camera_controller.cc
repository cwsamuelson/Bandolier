#include <Input.hh>
#include <key_codes.hh>
#include "orthographic_camera_controller.hh"

namespace Bandolier {

OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation)
  : mAspectRatio(aspectRatio)
  , mRotation(rotation)
  , mCamera(-mAspectRatio * mZoom, mAspectRatio * mZoom, -mZoom, mZoom)
{
  mPosition = { 0.5f, 0.5f, 0.0f };
  mRotation = 45.0f;
  mCamera.SetPosition(mPosition);
  mCamera.SetRotation(mRotation);
}

OrthographicCamera& OrthographicCameraController::Camera()
{
  return mCamera;
}

const OrthographicCamera& OrthographicCameraController::Camera() const
{
  return mCamera;
}

void
OrthographicCameraController::OnUpdate(Bandolier::time_step ts)
{
  if(Input::IsKeyPressed(int(KeyCodes::W)))
  {
    mPosition.y += mTranslationSpeed * ts;
  }
  if(Input::IsKeyPressed(int(KeyCodes::S)))
  {
    mPosition.y -= mTranslationSpeed * ts;
  }

  if(Input::IsKeyPressed(int(KeyCodes::D)))
  {
    mPosition.x += mTranslationSpeed * ts;
  }
  if(Input::IsKeyPressed(int(KeyCodes::A)))
  {
    mPosition.x -= mTranslationSpeed * ts;
  }

  if(mRotation)
  {
    if(Input::IsKeyPressed(int(KeyCodes::Q)))
    {
      mCameraRotation += mRotationSpeed * ts;
    }
    if(Input::IsKeyPressed(int(KeyCodes::E)))
    {
      mCameraRotation -= mRotationSpeed * ts;
    }

    mCamera.SetRotation(mRotation);
  }

  mCamera.SetPosition(mPosition);
  mTranslationSpeed = mZoom;
}

}

