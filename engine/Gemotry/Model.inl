#include "Model.h"
#include "gfxContext.h"
#include "Renderer.h"

template<typename T>
void gfx::Model<T>::Create()
{
  m_pVertexBuffer = std::make_unique<gfxVertexBuffer<T>>();
  m_pVertexBuffer->Create(sizeof(T) * m_vertices.size(), m_vertices.data());
  m_pVertexBuffer->Bind();

  m_pIndexBuffer = std::make_unique<gfxIndex>();
  m_pIndexBuffer->Create(m_indices.size(), m_indices.data());
  m_pIndexBuffer->Bind();

 
}

template<typename T>
void gfx::Model<T>::LoadModelFromFile(const std::string &path)
{
  Assimp::Importer import;
  const aiScene *scene = import.ReadFile(path.c_str(), aiProcess_Triangulate | aiProcess_FlipUVs);

  if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
  {
    // << import.GetErrorString() << std::endl;
    //OutputDebugStringA(import.GetErrorString());
    return;
  }
  processNode(scene->mRootNode, scene);
}

template<typename T>
void gfx::Model<T>::RenderModel(std::shared_ptr<Camera> camera)
{

  DirectX::XMMATRIX mod = DirectX::XMMatrixIdentity();
  DirectX::XMMATRIX mvp = camera->GetProjectVeiwMatrix() * mod;
  Renderer::DrawIndex(m_indices.size());
}
template<typename T>
void gfx::Model<T>::processNode(aiNode *node, const aiScene *scene)
{
  for (uint32_t i = 0; i < node->mNumMeshes; i++)
  {
    aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
    processMesh(mesh, scene);
  }
  for (uint32_t i = 0; i < node->mNumChildren; i++)
  {
    processNode(node->mChildren[i], scene);
  }
}
template<typename T>
void gfx::Model<T>::processMesh(aiMesh *mesh, const aiScene *scene)
{
  for (uint32_t i = 0; i < mesh->mNumVertices; i++)
  {
    T vertex;
    DirectX::XMFLOAT3 position;
    position.x = mesh->mVertices[i].x;
    position.y = mesh->mVertices[i].y;
    position.z = mesh->mVertices[i].z;
    vertex.position = position;

    if (mesh->HasVertexColors(0))
    {
      /* code */
    }
    if (mesh->HasTextureCoords(0))
    {
      DirectX::XMFLOAT2 texCoord{ mesh->mTextureCoords[0][i].x,mesh->mTextureCoords[0][i].y };
      vertex.uv = texCoord;
    }

    if (mesh->HasNormals())
    {
      DirectX::XMFLOAT3 normal;
      normal.x = mesh->mNormals[i].x;
      normal.y = mesh->mNormals[i].y;
      normal.z = mesh->mNormals[i].z;
      vertex.normal = normal;
    }

    vertex.color = DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
    m_vertices.push_back(vertex);
  }

  for (uint32_t i = 0; i < mesh->mNumFaces; i++)
  {
    aiFace face = mesh->mFaces[i];
    for (uint32_t j = 0; j < face.mNumIndices; j++)
    {
      m_indices.push_back(face.mIndices[j]);
    }
  }
}
