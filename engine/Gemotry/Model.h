#pragma once
#include "pheader.h"
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include "gfxVertexBuffer.h"
#include "gfxIndexBuffer.h"
#include "gfxLayout.h"
#include "vertex.h"
//#include "Camera.h"
namespace gfx
{
  template<typename T>
  class Model
  {
    public:

      Model() = default;
      ~Model() = default;

      void Create();
      void LoadModelFromFile(const std::string& path);

      //void RenderModel(std::shared_ptr<Camera> camera);

      std::vector<T>& GetVertices(){return m_vertices;}
      std::vector<uint32_t>& GetIndices(){return m_indices;}

      uint32_t GetIndexCnt(){return m_indices.size();}
    private:
      void processNode(aiNode* node,const aiScene* scene);
      void processMesh(aiMesh* mesh,const aiScene* scene);
    private:
      std::vector<T> m_vertices;
      std::vector<uint32_t> m_indices;
  };

}
#include "Model.inl"
