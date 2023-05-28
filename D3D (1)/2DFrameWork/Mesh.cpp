#include "framework.h"

Mesh::Mesh()
{
    vertexType = VertexType::PC;
    primitiveTopology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
    byteWidth = sizeof(VertexPC);
    VertexPC* Vertex = new VertexPC[4];
    vertexCount = 4;
    indexCount = 6;
    indices = new UINT[6];

    Vertex[0].position.x = -0.5f;
    Vertex[0].position.y = -0.5f;
    Vertex[0].color = Color(0, 0, 1);

    Vertex[1].position.x = -0.5f;
    Vertex[1].position.y = 0.5f;
    Vertex[1].color = Color(0, 0, 1);
    
    Vertex[2].position.x = 0.5f;
    Vertex[2].position.y = -0.5f;
    Vertex[2].color = Color(0, 0, 1);

    Vertex[3].position.x = 0.5f;
    Vertex[3].position.y = 0.5f;
    Vertex[3].color = Color(0, 0, 1);

    indices[0] = 0;
    indices[1] = 1;
    indices[2] = 2;

    indices[3] = 1;
    indices[4] = 3;
    indices[5] = 2;


    


  

    vertices = Vertex;

    //CreateVertexBuffer
    {
        D3D11_BUFFER_DESC desc;
        desc = { 0 };
        desc.Usage = D3D11_USAGE_DEFAULT;
        desc.ByteWidth = byteWidth * vertexCount;
        desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

        D3D11_SUBRESOURCE_DATA data = { 0 };
        data.pSysMem = vertices;

        HRESULT hr = D3D->GetDevice()->CreateBuffer(&desc, &data, &vertexBuffer);
        assert(SUCCEEDED(hr));
    }

    //Create Index Buffer
    {
        D3D11_BUFFER_DESC desc;
        ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
        desc.ByteWidth = sizeof(UINT) * indexCount;
        desc.BindFlags = D3D11_BIND_INDEX_BUFFER;

        D3D11_SUBRESOURCE_DATA data = { 0 };
        data.pSysMem = indices;

        HRESULT hr = D3D->GetDevice()->CreateBuffer(&desc, &data, &indexBuffer);
        assert(SUCCEEDED(hr));
    }
}

Mesh::~Mesh()
{
}

void Mesh::Set()
{
    UINT offset = 0;
    D3D->GetDC()->IASetVertexBuffers(0,
        1,
        &vertexBuffer,
        &byteWidth,
        &offset);
    D3D->GetDC()->IASetPrimitiveTopology
    (primitiveTopology);
    D3D->GetDC()->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);
}

void Mesh::LoadFile(string file)
{
    this->file = file;
    BinaryReader in;
    wstring path = L"../Contents/Mesh/" + Util::ToWString(file);
    in.Open(path);
    //읽기전
    switch (vertexType)
    {
    case VertexType::P:
        if (vertices)delete[](VertexP*)vertices;
        break;
    case VertexType::PC:
        if (vertices)delete[](VertexPC*)vertices;
        break;
    case VertexType::PCN:
        if (vertices)delete[](VertexPCN*)vertices;
        break;
    case VertexType::PTN:
        if (vertices)delete[](VertexPTN*)vertices;
        break;
    case VertexType::MODEL:
        if (vertices)delete[](VertexModel*)vertices;
        break;
    case VertexType::TERRAIN:
        if (vertices)delete[](VertexTerrain*)vertices;
        break;
    case VertexType::PT:
        if (vertices)delete[](VertexPT*)vertices;
        break;
    case VertexType::PS:
        if (vertices)delete[](VertexPS*)vertices;
        break;
    case VertexType::PSV:
        if (vertices)delete[](VertexPSV*)vertices;
        break;
    }
    vertexType = (VertexType)in.UInt();
    primitiveTopology = (D3D_PRIMITIVE_TOPOLOGY)in.UInt();
    byteWidth = in.UInt();
    vertexCount = in.UInt();
    indexCount = in.UInt();

    SafeDeleteArray(indices);
    indices = new UINT[indexCount];


    //읽고난후
    switch (vertexType)
    {
    case VertexType::P:
    {
        vertices = new VertexP[vertexCount];
        VertexP* vertex = (VertexP*)vertices;
        for (UINT i = 0; i < vertexCount; i++)
        {
            vertex[i].position = in.vector3();
        }
        break;
    }

    case VertexType::PC:
    {
        vertices = new VertexPC[vertexCount];
        VertexPC* vertex = (VertexPC*)vertices;
        for (UINT i = 0; i < vertexCount; i++)
        {
            vertex[i].position = in.vector3();
            vertex[i].color = in.color3f();
        }
        break;
    }
    case VertexType::PCN:
    {
        vertices = new VertexPCN[vertexCount];
        VertexPCN* vertex = (VertexPCN*)vertices;
        for (UINT i = 0; i < vertexCount; i++)
        {
            vertex[i].position = in.vector3();
            vertex[i].color = in.color3f();
            vertex[i].normal = in.vector3();
        }
        break;
    }
    case VertexType::PTN:
    {
        vertices = new VertexPTN[vertexCount];
        VertexPTN* vertex = (VertexPTN*)vertices;
        for (UINT i = 0; i < vertexCount; i++)
        {
            vertex[i].position = in.vector3();
            vertex[i].uv = in.vector2();
            vertex[i].normal = in.vector3();
        }
        break;
    }
    case VertexType::MODEL:
    {
        vertices = new VertexModel[vertexCount];
        VertexModel* vertex = (VertexModel*)vertices;
        for (UINT i = 0; i < vertexCount; i++)
        {
            vertex[i].position = in.vector3();
            vertex[i].uv = in.vector2();
            vertex[i].normal = in.vector3();
            vertex[i].tangent = in.vector3();
            vertex[i].indices = in.vector4();
            vertex[i].weights = in.vector4();
        }
        break;
    }
    case VertexType::TERRAIN:
    {
        vertices = new VertexTerrain[vertexCount];
        VertexTerrain* vertex = (VertexTerrain*)vertices;
        for (UINT i = 0; i < vertexCount; i++)
        {
            vertex[i].position = in.vector3();
            vertex[i].uv = in.vector2();
            vertex[i].normal = in.vector3();
            vertex[i].weights = in.Float();
        }
        break;
    }
    case VertexType::PT:
    {
        vertices = new VertexPT[vertexCount];
        VertexPT* vertex = (VertexPT*)vertices;
        for (UINT i = 0; i < vertexCount; i++)
        {
            vertex[i].position = in.vector3();
            vertex[i].uv = in.vector2();
        }
        break;
    }
    case VertexType::PS:
    {
        vertices = new VertexPS[vertexCount];
        VertexPS* vertex = (VertexPS*)vertices;
        for (UINT i = 0; i < vertexCount; i++)
        {
            vertex[i].position = in.vector3();
            vertex[i].size = in.vector2();
        }
        break;
    }
    case VertexType::PSV:
    {
        vertices = new VertexPSV[vertexCount];
        VertexPSV* vertex = (VertexPSV*)vertices;
        for (UINT i = 0; i < vertexCount; i++)
        {
            vertex[i].position = in.vector3();
            vertex[i].size = in.vector2();
            vertex[i].velocity = in.vector3();
        }
        break;
    }
    }
    for (UINT i = 0; i < indexCount; i++)
    {
        indices[i] = in.UInt();
    }
    in.Close();

    SafeRelease(vertexBuffer);
    SafeRelease(indexBuffer);
    //CreateVertexBuffer
    {
        D3D11_BUFFER_DESC desc;
        desc = { 0 };
        desc.Usage = D3D11_USAGE_DEFAULT;
        desc.ByteWidth = byteWidth * vertexCount;
        desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

        D3D11_SUBRESOURCE_DATA data = { 0 };
        data.pSysMem = vertices;

        HRESULT hr = D3D->GetDevice()->CreateBuffer(&desc, &data, &vertexBuffer);
        assert(SUCCEEDED(hr));
    }

    //Create Index Buffer
    {
        D3D11_BUFFER_DESC desc;
        ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
        desc.ByteWidth = sizeof(UINT) * indexCount;
        desc.BindFlags = D3D11_BIND_INDEX_BUFFER;

        D3D11_SUBRESOURCE_DATA data = { 0 };
        data.pSysMem = indices;

        HRESULT hr = D3D->GetDevice()->CreateBuffer(&desc, &data, &indexBuffer);
        assert(SUCCEEDED(hr));
    }

}

void Mesh::SaveFile(string file)
{
    this->file = file;

    BinaryWriter out;
    wstring path = L"../Contents/Mesh/" + Util::ToWString(file);
    out.Open(path);

    out.UInt((UINT)vertexType);
    out.UInt((UINT)primitiveTopology);
    out.UInt(byteWidth);
    out.UInt(vertexCount);
    out.UInt(indexCount);

    switch (vertexType)
    {
    case VertexType::P:
    {
        VertexP* vertex = (VertexP*)vertices;
        for (UINT i = 0; i < vertexCount; i++)
        {
            out.vector3(vertex[i].position);
        }
        break;
    }

    case VertexType::PC:
    {
        VertexPC* vertex = (VertexPC*)vertices;
        for (UINT i = 0; i < vertexCount; i++)
        {
            out.vector3(vertex[i].position);
            out.color3f(vertex[i].color);
        }
        break;
    }
    case VertexType::PCN:
    {
        VertexPCN* vertex = (VertexPCN*)vertices;
        for (UINT i = 0; i < vertexCount; i++)
        {
            out.vector3(vertex[i].position);
            out.color3f(vertex[i].color);
            out.vector3(vertex[i].normal);
        }
        break;
    }
    case VertexType::PTN:
    {
        VertexPTN* vertex = (VertexPTN*)vertices;
        for (UINT i = 0; i < vertexCount; i++)
        {
            out.vector3(vertex[i].position);
            out.vector2(vertex[i].uv);
            out.vector3(vertex[i].normal);
        }
        break;
    }
    case VertexType::MODEL:
    {
        VertexModel* vertex = (VertexModel*)vertices;
        for (UINT i = 0; i < vertexCount; i++)
        {
            out.vector3(vertex[i].position);
            out.vector2(vertex[i].uv);
            out.vector3(vertex[i].normal);
            out.vector3(vertex[i].tangent);
            out.vector4(vertex[i].indices);
            out.vector4(vertex[i].weights);
        }
        break;
    }
    case VertexType::TERRAIN:
    {
        VertexTerrain* vertex = (VertexTerrain*)vertices;
        for (UINT i = 0; i < vertexCount; i++)
        {
            out.vector3(vertex[i].position);
            out.vector2(vertex[i].uv);
            out.vector3(vertex[i].normal);
            out.Float(vertex[i].weights);
        }
        break;
    }
    case VertexType::PT:
    {
        VertexPT* vertex = (VertexPT*)vertices;
        for (UINT i = 0; i < vertexCount; i++)
        {
            out.vector3(vertex[i].position);
            out.vector2(vertex[i].uv);
        }
        break;
    }
    case VertexType::PS:
    {
        VertexPS* vertex = (VertexPS*)vertices;
        for (UINT i = 0; i < vertexCount; i++)
        {
            out.vector3(vertex[i].position);
            out.vector2(vertex[i].size);
        }
        break;
    }
    case VertexType::PSV:
    {
        VertexPSV* vertex = (VertexPSV*)vertices;
        for (UINT i = 0; i < vertexCount; i++)
        {
            out.vector3(vertex[i].position);
            out.vector2(vertex[i].size);
            out.vector3(vertex[i].velocity);
        }
        break;
    }
    }
    for (UINT i = 0; i < indexCount; i++)
    {
        out.UInt(indices[i]);
    }
    out.Close();
}
