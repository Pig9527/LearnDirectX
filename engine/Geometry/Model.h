#pragma once
#include "pheader.h"
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include "gfxVertexBuffer.h"
#include "gfxIndexBuffer.h"
#include "gfxLayout.h"
#include "vertex.h"
#include "gfxTexture.h"
//#include "Camera.h"
namespace gfx
{
  class Model
  {
    public:

      Model() = default;
      virtual ~Model(){}

      virtual void Create();
      void LoadModelFromFile(const std::string& path);

      virtual void* GetVertex() = 0; 
      virtual uint32_t GetVertexSize() = 0; 
      std::vector<uint32_t>& GetIndices(){return m_indices;}

      uint32_t GetIndexCnt(){return m_indices.size();}


    protected:
      void processNode(aiNode* node,const aiScene* scene);
      virtual void processMesh(aiMesh* mesh,const aiScene* scene);

      void processPosition(void* vertex,aiVector3D* aiVert);
      void processColor(void* vertex,aiColor4D *color);
      void processVertexIndex(aiMesh* mesh);
    protected:
      std::vector<uint32_t> m_indices;
  };


  class ModelNormal
    :public Model
  {
    public:
      ModelNormal() = default;
      ~ModelNormal() = default;

      void* GetVertex() override {return m_vertices.data();}
      uint32_t GetVertexSize() override {return m_vertices.size() * sizeof(VertexPosColorNormal);}
      void processMesh(aiMesh* mesh,const aiScene* scene) override;
    private:
      std::vector<VertexPosColorNormal> m_vertices;
  };

  class ModelTexCoord
    :public Model
  {
    public:
      ModelTexCoord() = default;
      ~ModelTexCoord() = default;

      void* GetVertex() override {return m_vertices.data();}
      uint32_t GetVertexSize() override {return m_vertices.size() * sizeof(VertexPosColorUv);}
      void processMesh(aiMesh* mesh,const aiScene* scene) override;
    private:
      std::vector<VertexPosColorUv> m_vertices;
  };


  class ModelTexCoordNormal
  :public Model
  {
    public:

    ModelTexCoordNormal() = default;
    ~ModelTexCoordNormal() { delete m_TexfilePath; }

    void* GetVertex() override {return m_vertices.data();}
    uint32_t GetVertexSize() override {return m_vertices.size() * sizeof(VertexPosColorNormalUv);}
    void processMesh(aiMesh* mesh,const aiScene* scene) override;
    void Create() override;
    void Bind();
    private:
      int m_MaterialIndex;
      char* m_TexfilePath ="assets/model/house/";
      std::vector<VertexPosColorNormalUv> m_vertices;
      gfxVertexBuffer<VertexPosColorNormalUv> m_verticesBuffer;
      gfxIndexBuffer m_indicesBuffer;
      gfxTexture m_defaultTex;
  };
}

