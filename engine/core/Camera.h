#pragma once
#include "pheader.h"

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
