#include "Camera.h"
#include "Context.h"
#include "Input.h"
#define BIN_EVENT(fn) std::bind(&fn, this, std::placeholders::_1)

gfx::Camera::Camera()
    : m_fov(DirectX::XM_PIDIV2),
      m_aspectRation(16.0f / 9.0f),
      m_near(0.1f), m_far(1000.0f),
      m_moveSpeed(5.0f),
      m_zoomSpeed(0.2f),
      m_pitch(0.0f), m_yaw(0.0f),
      m_needUpdate(true),
      m_bmouseLeftButtonDown(true),
      m_bmouseMove(false),
      m_position(0.0f, 0.0f, -2.0f),
      m_target(0.0f, 0.0f, 0.0f),
      m_up(0.0f, 1.0f, 0.0f),
      m_right(1.0f, 0.0f, 0.0f),
      m_forward(0.0f, 0.0f, 1.0f)
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
  if (Input::IsKeyPressed('W'))
  {
    m_position.z += m_moveSpeed * dt * 0.02f;
  }
  if (Input::IsKeyPressed('S'))
  {
    m_position.z -= m_moveSpeed * dt * 0.02f;
  }
  if (Input::IsKeyPressed('A'))
  {
    m_position.x -= m_moveSpeed * dt * 0.02f;
  }

  if (Input::IsKeyPressed('D'))
  {
    m_position.x += m_moveSpeed * dt * 0.02f;
  }
  if (m_bmouseLeftButtonDown && m_bmouseMove)
  {

    m_position.x += m_mouseOffset.x * m_moveSpeed * 0.0f * dt;
    m_position.y += m_mouseOffset.x * m_moveSpeed * 0.0f * dt;
  }

  m_bmouseMove = false;
  calcualteVector();
  calculateProjectView();
}

void gfx::Camera::OnEvent(Event &e)
{
  EventDispatcher dispatcher(e);
  dispatcher.Dispatch<MouseMoveEvent>(BIN_EVENT(Camera::OnMouseMoved));
  dispatcher.Dispatch<MouseButtonPressedEvent>(BIN_EVENT(Camera::OnMouseLeftButtonDown));
  dispatcher.Dispatch<MouseButtonReleasedEvent>(BIN_EVENT(Camera::OnMouseLeftButtonUp));
  dispatcher.Dispatch<MouseScrolledEvent>(BIN_EVENT(Camera::OnMouseScrolled));
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
  position = DirectX::XMVectorAdd(position, temp);
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

bool gfx::Camera::OnMouseMoved(MouseMoveEvent &e)
{
  if (m_bmouseLeftButtonDown)
  {
    m_bmouseMove = true;
    DirectX::XMFLOAT2 laster{e.GetX(), e.GetY()};

    DirectX::XMVECTOR offset = DirectX::XMVectorSubtract(DirectX::XMLoadFloat2(&laster), DirectX::XMLoadFloat2(&m_mousePos));
    DirectX::XMStoreFloat2(&m_mouseOffset, offset);
    m_mousePos = laster;
  }
  return false;
}

bool gfx::Camera::OnMouseScrolled(MouseScrolledEvent &e)
{
  return false;
}

bool gfx::Camera::OnMouseLeftButtonDown(MouseButtonPressedEvent &e)
{
  if (e.GetButton() == 1)
  {
    m_mousePos.x = e.GetMouseX();
    m_mousePos.y = e.GetMouseY();
    m_bmouseLeftButtonDown = true;
  }
  return false;
}

bool gfx::Camera::OnMouseLeftButtonUp(MouseButtonReleasedEvent &e)
{
  if (e.GetButton() == 1)
  {
    m_bmouseLeftButtonDown = false;
  }
  return false;
}
