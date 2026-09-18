#include "BasicEffect.h"

namespace gfx
{

  class BasicEffect::Impl
  {
    public:
      Impl(){};
      ~Impl() = default;
    comptr<ID3D11InputLayout> m_pCurrentLayout;
    comptr<ID3D11InputLayout> m_pVertexPosColorNorTexLayout;
    comptr<ID3D11InputLayout> m_pVertexPosColorNorTexTangLayout;
  };

  void BasicEffect::Create()
  {

  }
} // namespace gfx
