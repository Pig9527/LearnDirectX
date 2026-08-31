#include "Camera.h"
#include "Context.h"
#include "Input.h"
#include "Context.h"
#define BIN_EVENT(fn) std::bind(&fn, this, std::placeholders::_1)

gfx::Camera::Camera()
    : m_fov(DirectX::XM_PIDIV4),
      m_aspectRation(16.0f / 9.0f),
      m_near(0.1f), m_far(1000.0f),
      m_moveSpeed(5.0f),
      m_zoomSpeed(0.5f),
      m_pitch(0.0f), m_yaw(0.0f),
      m_needUpdate(true),
      m_distance(10.0f),
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
  m_aspectRation = static_cast<float>(Context::sWindowWidth) / static_cast<float>(Context::sWindowHeight);
  m_position = Context::CameraPos;
  m_up = Context::CameraUp;
  m_target = Context::CameraTarget;
  calcualteVector();
  calculateProjectView();
}

void gfx::Camera::Update(float dt)
{
  if (Input::IsKeyPressed('W'))
  {
    m_target.z += m_moveSpeed * dt * 0.02f;
  }
  if (Input::IsKeyPressed('S'))
  {
    m_target.z -= m_moveSpeed * dt * 0.02f;
  }
  if (Input::IsKeyPressed('A'))
  {
    m_target.x -= m_moveSpeed * dt * 0.02f;
  }

  if (Input::IsKeyPressed('D'))
  {
    m_target.x += m_moveSpeed * dt * 0.02f;
  }

  if(Context::sbMButtonDown)
  {
    DirectX::XMFLOAT2 offset = DirectX::XMFLOAT2{Context::sMousePosX - Context::sMouseDownX,Context::sMousePosY - Context::sMouseDownY};
    TCHAR szStr[MAX_PATH];
    if (offset.x != 0 && offset.y != 0)
    {
      StringCchPrintf(szStr, MAX_PATH, TEXT("down = (%d,%d),move = (%d,%d),Offset = (%f,%f)\n"),
         Context::sMouseDownX, Context::sMouseDownY, 
        Context::sMousePosX, Context::sMousePosY, 
        offset.x, offset.y);
      OutputDebugString(szStr);
    }
   
    m_target.x += offset.x / 100.0f *dt*0.02f;
    m_target.z += offset.y / 100.0f * dt * 0.02f;
  }
  if (m_bmouseLeftButtonDown && m_bmouseMove)
  {

    m_position.x += m_mouseOffset.x * m_moveSpeed * 0.0f * dt;
    m_position.y += m_mouseOffset.x * m_moveSpeed * 0.0f * dt;
  }

  m_distance -= Context::sMouseWheel * m_zoomSpeed *1.0f;

  m_distance = std::clamp(m_distance,0.1f,100.0f);

  //m_bmouseMove = false;
  calcualteVector();
  calculateProjectView();
  Context::sMouseWheel = 0.0f;
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
#if 0
  if (m_pitch > DirectX::XM_PI *7.0f / 18.0f)
  {
    m_pitch = DirectX::XM_PI * 7.0f / 18.0f;
  }
  else if(m_pitch < -DirectX::XM_PI * 7.0f / 18.0f)
  {
    m_pitch = -DirectX::XM_PI * 7.0f / 18.0f;
  }
  //m_pitch = std::max(((-DirectX::XM_PI) / 2.0f + 0.01f), std::min((DirectX::XM_PI / 2.0f - 0.01f), m_pitch));
  m_needUpdate = true;
#endif
}

void gfx::Camera::Zoom(float delta)
{

#if 0
  DirectX::XMVECTOR position = DirectX::XMLoadFloat3(&m_position);
  DirectX::XMVECTOR forward = DirectX::XMLoadFloat3(&m_forward);

  DirectX::XMVECTOR temp = DirectX::XMVectorScale(DirectX::XMVectorScale(forward, m_zoomSpeed), delta);
  DirectX::XMVECTOR result = DirectX::XMVectorAdd(position, temp);
  DirectX::XMStoreFloat3(&m_position, result);


  m_needUpdate = true;
#endif
  DirectX::XMVECTOR position = DirectX::XMLoadFloat3(&m_position);
  DirectX::XMVECTOR forward = DirectX::XMLoadFloat3(&m_forward);

  // 直接计算偏移量
  float speed = m_zoomSpeed * delta;
  if (speed < -100.0f)
  {
    speed = -100.0f;
  }
  else if(speed > 100.0f)
  {
    speed = 100.0f;
  }
  DirectX::XMVECTOR offset = DirectX::XMVectorScale(forward, speed);
  DirectX::XMVECTOR result = DirectX::XMVectorAdd(position, offset);

  DirectX::XMStoreFloat3(&m_position, result);
}

void gfx::Camera::MoveForward(float distance)
{
  DirectX::XMVECTOR position = DirectX::XMLoadFloat3(&m_position);
  DirectX::XMVECTOR forward = DirectX::XMLoadFloat3(&m_forward);
  DirectX::XMVECTOR temp = DirectX::XMVectorScale(DirectX::XMVectorScale(forward, m_moveSpeed), distance);
  position = DirectX::XMVectorAdd(position, temp);
  position = DirectX::XMVectorClamp(position, DirectX::XMVectorSet(-45.0f, -2.0f, -60.0f, 0.0f), DirectX::XMVectorSet(45.0f, 20.0f, 45.0f, 0.0f));
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

  DirectX::XMVECTOR position = DirectX::XMLoadFloat3(&m_position);
  DirectX::XMVECTOR target = DirectX::XMLoadFloat3(&m_target);
  DirectX::XMVECTOR up = DirectX::XMLoadFloat3(&m_up);

  m_viewMatrix = DirectX::XMMatrixTranspose(DirectX::XMMatrixLookAtLH(
    DirectX::XMLoadFloat3(&m_position),DirectX::XMLoadFloat3(&m_target), DirectX::XMLoadFloat3(&m_up)));

  m_projectViewMatrix = m_projectMatrix * m_viewMatrix;
}

void gfx::Camera::calcualteVector()
{

#if 0
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
#endif
# if 0
  // 1. 计算前方向向量（基于欧拉角）
  DirectX::XMVECTOR forward = DirectX::XMVector3Transform(
    DirectX::XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f),
    DirectX::XMMatrixRotationRollPitchYaw(m_pitch, m_yaw, 0.0f));
  forward = DirectX::XMVector3Normalize(forward);
  DirectX::XMStoreFloat3(&m_forward, forward);

  // 2. 计算右方向向量（叉积）
  DirectX::XMVECTOR worldUp = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
  DirectX::XMVECTOR right = DirectX::XMVector3Cross(worldUp, forward);
  DirectX::XMStoreFloat3(&m_right, right);
  right = DirectX::XMVector3Normalize(right);
  DirectX::XMStoreFloat3(&m_right, right);

  // 3. 重新计算上方向向量（确保正交）
  DirectX::XMVECTOR up = DirectX::XMVector3Cross(forward, right);
  up = DirectX::XMVector3Normalize(up);
  DirectX::XMStoreFloat3(&m_up, up);

  //// 4. 计算目标点
  //DirectX::XMVECTOR position = DirectX::XMLoadFloat3(&m_position);
  //DirectX::XMVECTOR target = DirectX::XMVectorAdd(position, forward);
  //DirectX::XMStoreFloat3(&m_target, target);
#else

  m_pitch = std::clamp(m_pitch, -DirectX::XM_PIDIV4, DirectX::XM_PIDIV4);

  DirectX::XMMATRIX rotMatrix = DirectX::XMMatrixRotationRollPitchYaw(m_pitch, m_yaw, 0.0f);
 
  DirectX::XMVECTOR localOffset = DirectX::XMVectorSet(0.0f, 5.0f, 10.0f, 0.0f);
  localOffset = DirectX::XMVector3Normalize(localOffset);

  DirectX::XMVECTOR offset = DirectX::XMVector3Transform(localOffset, rotMatrix);

  offset = DirectX::XMVectorScale(offset, m_distance);

  DirectX::XMVECTOR target = DirectX::XMLoadFloat3(&m_target);
  DirectX::XMVECTOR position = DirectX::XMVectorAdd(target, offset);

  DirectX::XMStoreFloat3(&m_position, position);


  DirectX::XMVECTOR forward = DirectX::XMVectorSubtract(DirectX::XMLoadFloat3(&m_target), DirectX::XMLoadFloat3(&m_position));
  forward = DirectX::XMVector3Normalize(forward);

  DirectX::XMVECTOR worldUp = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
  DirectX::XMVECTOR right = DirectX::XMVector3Cross(worldUp, forward);
  right = DirectX::XMVector3Normalize(right);

  DirectX::XMVECTOR up = DirectX::XMVector3Cross(forward, right);

  DirectX::XMStoreFloat3(&m_forward, forward);
  DirectX::XMStoreFloat3(&m_right, right);
  DirectX::XMStoreFloat3(&m_up, up);

#endif

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
