#pragma once
#include "pheader.h"
#include "Vertex.h"
#include "Entity/Entity.h"
#include "CubeMeshComponent.h"

namespace gfx
{
  class RendererSystem
  {
    protected:
    RendererSystem();
    ~RendererSystem();

    public:
    static RendererSystem& Get(){ static RendererSystem renderSystem;return renderSystem; }

    void Init();

    void Render();

    void Push(std::shared_ptr<Entity>& entity);
    void Begin();

    void End();

    private:
    void RenderCube();
    void RenderSphere();
    void RenderCylinder();

    std::vector<std::shared_ptr<Entity>> m_pEntities;

  };
}
