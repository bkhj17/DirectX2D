#include "Framework.h"
#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(void* data, UINT count)
{
#pragma region CreateBuffer
	D3D11_BUFFER_DESC bufferDesc = {};
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;             //CPU, GPU�� ���� ���� ����
	bufferDesc.ByteWidth = sizeof(UINT) * count;		//���� �޸� ũ��
	bufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;		//���� �뵵

	D3D11_SUBRESOURCE_DATA initData = {};
	initData.pSysMem = data; //���� �ּ�

	DEVICE->CreateBuffer(&bufferDesc, &initData, &buffer);
#pragma endregion
}

IndexBuffer::~IndexBuffer()
{
	buffer->Release();
}

void IndexBuffer::Set()
{
	DC->IASetIndexBuffer(buffer, DXGI_FORMAT_R32_UINT, 0);
}

void IndexBuffer::Update(void* data, UINT count)
{	
	DC->UpdateSubresource(buffer, 0, nullptr, data, sizeof(UINT), count);
}
