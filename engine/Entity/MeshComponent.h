#include "pheader.h"
#include "Component.h"
#include "gfxVertexBuffer.h"
#include "gfxIndexBuffer.h"

namespace gfx
{

  class MeshComponent
      : public Component
  {
  public:
    enum class eMeshType
    {
      Cube,
      Sphere,
      Cylinder,
      Plane,
      Coto,
      Custom
    };

    MeshComponent();
    explicit MeshComponent(eMeshType type);


    void Update() override;
    void OnAttach() override;

    eMeshType MeshType;
    std::string MaterialName;
    bool bVisible;
    bool bCastShadow;
    bool bReceiveShadows;

    std::shared_ptr<gfxVertexBuffer<VertexPosColorNormalUv>> m_pVerticesBuffer;
    std::shared_ptr<gfxIndexBuffer> m_pIndicesBuffer;
  };
}
