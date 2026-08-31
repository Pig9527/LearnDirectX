#pragma once
#include "pheader.h"
#include "Event.h"
#include "KeyEvent.h"
#include "MouseEvent.h"

namespace gfx
{
  class Camera
  {
  public:
    Camera();
    ~Camera();

  public:
    void Init();
    void Update(float dt);

    void OnEvent(Event& e);
    void Rotate(float pitch, float yaw);
    void Zoom(float delta);
    void MoveForward(float distance);
    void MoveRight(float distance);
    void MoveUp(float distance);

    DirectX::XMMATRIX &GetProjectVeiwMatrix() { return m_projectViewMatrix; }
    DirectX::XMMATRIX &GetProjectMatrix() { return m_projectMatrix; }
    DirectX::XMMATRIX &GetViewMatrix() { return m_viewMatrix; }

    DirectX::XMFLOAT3 GetPosition() { return m_position; }
    void SetPosition(const DirectX::XMFLOAT3 &position)
    {
      m_position = position;
      m_needUpdate = true;
    }

    DirectX::XMFLOAT3 GetForward() { return m_forward; }
    void SetForward(const DirectX::XMFLOAT3 &forward)
    {
      m_forward = forward;
      m_needUpdate = true;
    }

    DirectX::XMFLOAT3 GetUp() { return m_up; }
    DirectX::XMFLOAT3 GetRight() { return m_right; }

  private:
    void calculateProjectView();
    void calcualteVector();

    bool OnMouseMoved(MouseMoveEvent& e);
    bool OnMouseScrolled(MouseScrolledEvent& e);
    bool OnMouseLeftButtonDown(MouseButtonPressedEvent& e);
    bool OnMouseLeftButtonUp(MouseButtonReleasedEvent& e);

  private:
    float m_fov;
    float m_aspectRation;
    float m_near;
    float m_far;
    float m_moveSpeed;
    float m_zoomSpeed;
    float m_pitch;
    float m_yaw;
    bool m_needUpdate;
    float m_distance;
    DirectX::XMFLOAT2 m_mousePos;
    DirectX::XMFLOAT2 m_mouseOffset;
    bool m_bmouseLeftButtonDown;
    bool m_bmouseMove;

    DirectX::XMFLOAT3 m_position;
    DirectX::XMFLOAT3 m_target;
    DirectX::XMFLOAT3 m_up;
    DirectX::XMFLOAT3 m_right;
    DirectX::XMFLOAT3 m_forward;
    DirectX::XMMATRIX m_projectMatrix;
    DirectX::XMMATRIX m_viewMatrix;
    DirectX::XMMATRIX m_projectViewMatrix;
  };
}
