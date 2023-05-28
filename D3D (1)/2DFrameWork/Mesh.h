#pragma once
class Mesh
{
    friend class GameObject;
private:
    ID3D11Buffer*           vertexBuffer;
    ID3D11Buffer*           indexBuffer;

    D3D_PRIMITIVE_TOPOLOGY  primitiveTopology;
    VertexType              vertexType;
    UINT                    byteWidth;

    UINT*                   indices;
    UINT                    indexCount;
    void*                   vertices;
    UINT                    vertexCount;
public:
    string                  file;
public:
    Mesh();
    ~Mesh();
    void Set();
    void LoadFile(string file);
    void SaveFile(string file);
};

