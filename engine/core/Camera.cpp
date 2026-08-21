#include "Camera.h"
#include "Context.h"

gfx::Camera::Camera()
: m_fov(DirectX::XM_PIDIV2)
, m_aspectRation(16.0f / 9.0f)
, m_near(0.1f), m_far(1000.0f)
, m_moveSpeed(5.0f)
, m_zoomSpeed(0.2f)
, m_pitch(0.0f)
, m_yaw(0.0f)
, m_needUpdate(true)
, m_position(0.0f, 0.0f, -2.0f)
, m_target(0.0f, 0.0f, 0.0f)
, m_up(0.0f, 1.0f, 0.0f)
, m_right(1.0f, 0.0f, 0.0f)
, m_forward(0.0f, 0.0f, 1.0f)
{
}

gfx::Camera::~Camera()
{
}

void gfx::Camera::Init()
{
  

  calcualteVector();
  calculateProjectView();
}

void gfx::Camera::Update(float dt)
{
  calcualteVector();
  calculateProjectView();
}

void gfx::Camera::Rotate(float pitch, float yaw)
{
  m_pitch += pitch;
  m_yaw += yaw;

  m_pitch = std::max(((-DirectX::XM_PI) / 2.0f + 0.01f), std::min((DirectX::XM_PI / 2.0f - 0.01f), m_pitch));
  m_needUpdate = true;
}

void gfx::Camera::Zoom(float delta)
{
  DirectX::XMVECTOR position = DirectX::XMLoadFloat3(&m_position);
  DirectX::XMVECTOR forward = DirectX::XMLoadFloat3(&m_forward);

  DirectX::XMVECTOR temp = DirectX::XMVectorScale(DirectX::XMVectorScale(forward, m_zoomSpeed), delta);
  DirectX::XMVectorAdd(position, temp);
  DirectX::XMStoreFloat3(&m_position, position);

  m_needUpdate = true;
}

void gfx::Camera::MoveForward(float distance)
{
  DirectX::XMVECTOR position = DirectX::XMLoadFloat3(&m_position);
  DirectX::XMVECTOR forward = DirectX::XMLoadFloat3(&m_forward);
  DirectX::XMVECTOR temp = DirectX::XMVectorScale(DirectX::XMVectorScale(forward, m_moveSpeed), distance);
  position = DirectX::XMVectorAdd(position, temp);
  DirectX::XMStoreFloat3(&m_position, position);

  m_needUpdate = true;
}

void gfx::Camera::MoveRight(float distance)
{
  DirectX::XMVECTOR position = DirectX::XMLoadFloat3(&m_position);
  DirectX::XMVECTOR right = DirectX::XMLoadFloat3(&m_right);
  DirectX::XMVECTOR temp = DirectX::XMVectorScale(DirectX::XMVectorScale(right, m_moveSpeed), distance);
  position =  DirectX::XMVectorAdd(position, temp);
  DirectX::XMStoreFloat3(&m_position, position);

  m_needUpdate = true;
}

void gfx::Camera::MoveUp(float distance)
{
  DirectX::XMVECTOR position = DirectX::XMLoadFloat3(&m_position);
  DirectX::XMVECTOR up = DirectX::XMLoadFloat3(&m_up);
  DirectX::XMVECTOR temp = DirectX::XMVectorScale(DirectX::XMVectorScale(up, m_moveSpeed), distance);
  DirectX::XMVectorAdd(position, temp);
  DirectX::XMStoreFloat3(&m_position, position);

  m_needUpdate = true;
}

void gfx::Camera::calculateProjectView()
{

  m_projectMatrix = DirectX::XMMatrixTranspose(
    DirectX::XMMatrixPerspectiveFovLH(m_fov, m_aspectRation, m_near, m_far));

  DirectX::XMVECTOR positin = DirectX::XMLoadFloat3(&m_position);
  DirectX::XMVECTOR target = DirectX::XMLoadFloat3(&m_target);
  DirectX::XMVECTOR up = DirectX::XMLoadFloat3(&m_up);

  m_viewMatrix = DirectX::XMMatrixTranspose(DirectX::XMMatrixLookAtLH(positin, target, up));

  m_projectViewMatrix = m_projectMatrix * m_viewMatrix;
}

void gfx::Camera::calcualteVector()
{
  DirectX::XMVECTOR forward = DirectX::XMVector3Transform(
      DirectX::XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f),
      DirectX::XMMatrixRotationRollPitchYaw(m_pitch, m_yaw, 0.0f));
  DirectX::XMStoreFloat3(&m_forward, forward);
  DirectX::XMVector3Normalize(forward);

  DirectX::XMVECTOR right = DirectX::XMVector3Cross(
      forward, DirectX::XMLoadFloat3(&m_up));

  DirectX::XMStoreFloat3(&m_right, right);
  DirectX::XMVector3Normalize(right);

  DirectX::XMVECTOR position = DirectX::XMLoadFloat3(&m_position);
  DirectX::XMVECTOR target = DirectX::XMVectorAdd(position, forward);
  DirectX::XMStoreFloat3(&m_target, target);

  DirectX::XMVECTOR up = DirectX::XMVector3Cross(right, forward);
  DirectX::XMStoreFloat3(&m_up, up);

  m_needUpdate = true;
}
