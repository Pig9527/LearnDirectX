#include "Model.h"
#include "gfxContext.h"
#include "Renderer.h"

void gfx::Model::Create()
{
#if 0
  m_pVertexBuffer = std::make_unique<gfxVertexBuffer<T>>();
  m_pVertexBuffer->Create(sizeof(T) * m_vertices.size(), m_vertices.data());
  m_pVertexBuffer->Bind();

  m_pIndexBuffer = std::make_unique<gfxIndex>();
  m_pIndexBuffer->Create(m_indices.size(), m_indices.data());
  m_pIndexBuffer->Bind();

#endif
}

void gfx::Model::LoadModelFromFile(const std::string &path)
{
  Assimp::Importer import;
  const aiScene *scene = import.ReadFile(path.c_str(), 
  aiProcess_Triangulate | 
  aiProcess_FlipUVs |
  aiProcess_ConvertToLeftHanded |
  aiProcess_GenBoundingBoxes |
  aiProcess_SortByPType |
  aiProcess_ImproveCacheLocality
  );

  if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
  {
    // << import.GetErrorString() << std::endl;
    OutputDebugStringA(import.GetErrorString());
    return;
  }
  processNode(scene->mRootNode, scene);
}

void gfx::Model::processPosition(void *vertex, aiVector3D* aiVert)
{
  VertexPosColor* vert = (VertexPosColor*)vertex;
  vert->position.x = aiVert->x;
  vert->position.y = aiVert->y;
  vert->position.z = aiVert->z;
  DirectX::XMMATRIX scale = DirectX::XMMatrixScaling(0.015f,0.015f,0.015f);
  DirectX::XMVECTOR pos = DirectX::XMLoadFloat3(&vert->position);
  pos = DirectX::XMVector3Transform(pos,scale);
  DirectX::XMStoreFloat3(&vert->position,pos);
}

void gfx::Model::processColor(void *vertex, aiColor4D *color)
{
  VertexPosColor* vert = (VertexPosColor*)vertex;
  vert->color.x = color->r;
  vert->color.y = color->g;
  vert->color.z = color->b;
  vert->color.w = color->a;
}

void gfx::Model::processVertexIndex(aiMesh* mesh)
{ 
  for (uint32_t i = 0; i < mesh->mNumFaces; i++)
  {
    aiFace face = mesh->mFaces[i];
    for (uint32_t j = 0; j < face.mNumIndices; j++)
    {
      m_indices.push_back(face.mIndices[j]);
    }
  }
}

void gfx::Model::processNode(aiNode *node, const aiScene *scene)
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

void gfx::Model::processMesh(aiMesh *mesh, const aiScene *scene)
{


  #if 0
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



  #endif
}

void gfx::ModelNormal::processMesh(aiMesh *mesh, const aiScene *scene)
{
  VertexPosColorNormal vert;
  for (uint32_t i = 0; i < mesh->mNumVertices; i++)
  {
    Model::processPosition(&vert,&mesh->mVertices[i]);
    if(mesh->HasVertexColors(0))
    {
      Model::processColor(&vert,mesh->mColors[i]);
    }
    else{
      vert.color = DirectX::XMFLOAT4{1.0f,1.0f,1.0f,1.0f};
    }
  
   if (mesh->HasNormals())
    {
      DirectX::XMFLOAT3 normal;
      normal.x = mesh->mNormals[i].x;
      normal.y = mesh->mNormals[i].y;
      normal.z = mesh->mNormals[i].z;
      vert.normal = normal;
    }
    m_vertices.push_back(vert);
  }
  Model::processVertexIndex(mesh);

}

void gfx::ModelTexCoord::processMesh(aiMesh *mesh, const aiScene *scene)
{
  VertexPosColorUv vert;
  for (uint32_t i = 0; i < mesh->mNumVertices; i++)
  {
    Model::processPosition(&vert,&mesh->mVertices[i]);
    if(mesh->HasVertexColors(0))
    {
      Model::processColor(&vert,mesh->mColors[i]);
    }
    else{
      vert.color = DirectX::XMFLOAT4{1.0f,1.0f,1.0f,1.0f};
    }
  
   if (mesh->HasTextureCoords(i))
    {
      vert.uv.x = mesh->mTextureCoords[i]->x;
      vert.uv.y = mesh->mTextureCoords[i]->y;
    }
    m_vertices.push_back(vert);
  }
  Model::processVertexIndex(mesh);
}

void gfx::ModelTexCoordNormal::processMesh(aiMesh *mesh, const aiScene *scene)
{
  VertexPosColorNormalUv vertex;
  for (size_t i = 0; i < mesh->mNumVertices; i++)
  {
    Model::processPosition(&vertex,&mesh->mVertices[i]);
    if (mesh->HasVertexColors(0))
    {
      /* code */
      Model::processColor(&vertex,mesh->mColors[i]);
    }
    else
    {
      vertex.color = DirectX::XMFLOAT4{1.0f,1.0f,1.0f,1.0f};
    }
    m_vertices.push_back(vertex);
  
    if (mesh->HasNormals())
    {
      vertex.normal.x = mesh->mNormals[i].x;
      vertex.normal.y = mesh->mNormals[i].y;
      vertex.normal.z = mesh->mNormals[i].z;
    }
  }

  uint32_t numUVs = 8;
  while (numUVs && !mesh->HasTextureCoords(numUVs -1))
  {
    numUVs--;

  }
  if (numUVs > 0)
  {
    for (uint32_t i = 0;i<numUVs;i++)
    {
      aiVector3D* texCoord = mesh->mTextureCoords[i];
      for (uint32_t j=0;j<mesh->mNumVertices;j++)
      {
        m_vertices[j].uv.x = texCoord->x;
        m_vertices[j].uv.y = texCoord->y;
        texCoord++;
      }
    }
  }


  m_MaterialIndex = mesh->mMaterialIndex;

  auto pAiMaterial = scene->mMaterials[m_MaterialIndex];
  DirectX::XMFLOAT4 vec;
  /*int num = 3;
  if(aiReturn_SUCCESS == pAiMaterial->Get(AI_MATKEY_COLOR_AMBIENT,&vec.x,&num)
  {

  }*/

  aiString aiPath;
  if (pAiMaterial->GetTextureCount(aiTextureType_DIFFUSE) > 0)
  {
    pAiMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &aiPath);
    
    //m_defaultTex = new gfxTexture();
    char texPath[MAX_PATH] = "assets/model/house/";
    StringCchCatA(texPath, MAX_PATH, aiPath.C_Str());
    size_t length;
    StringCchLengthA(texPath, STRSAFE_MAX_CCH, &length);
    m_TexfilePath = new char[length+1]();
    memcpy_s(m_TexfilePath, length, texPath, length);
  }
  if (pAiMaterial->GetTextureCount(aiTextureType_NORMALS) > 0)
  {

    pAiMaterial->GetTexture(aiTextureType_NORMALS, 0, &aiPath);

  }


  processVertexIndex(mesh);
  
}

void gfx::ModelTexCoordNormal::Create()
{
  m_verticesBuffer.Create(this->GetVertexSize(), m_vertices.data());
  m_defaultTex.Create(m_TexfilePath);
  m_indicesBuffer.Create(GetIndices().size(), GetIndices().data());
}

void gfx::ModelTexCoordNormal::Bind()
{
  m_defaultTex.Bind();
  m_verticesBuffer.Bind();
  m_indicesBuffer.Bind();
}
