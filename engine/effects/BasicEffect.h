#pragma once
#include "Effect.h"
namespace gfx
{
  class BasicEffect
    :public Effect
  {
    public:
      BasicEffect() = default;
      virtual ~BasicEffect() = default;

      void Create();

      void Apply() override;
    private:
      class Impl;
      std::unique_ptr<Impl> m_pImpl;

  };
} // namespace gfx
