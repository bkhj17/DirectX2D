#include "Framework.h"
#include "ConstBuffer.h"

ConstBuffer::ConstBuffer(void* data, UINT dataSize)
	: data(data), dataSize(dataSize)
{
#pragma region CreateBuffer
	D3D11_BUFFER_DESC bufferDesc = {};
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;             //CPU, GPU�� ���� ���� ����
	bufferDesc.ByteWidth = dataSize;					//���� �޸� ũ��
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;	//���� �뵵

	D3D11_SUBRESOURCE_DATA initData = {};
	initData.pSysMem = data; //���� �ּ�

	DEVICE->CreateBuffer(&bufferDesc, nullptr, &buffer);
#pragma endregion
}

ConstBuffer::~ConstBuffer()
{
	buffer->Release();
}

void ConstBuffer::SetVS(UINT slot)
{
	DC->UpdateSubresource(buffer, 0, nullptr, data, 0, 0);
	DC->VSSetConstantBuffers(slot, 1, &buffer);
}

void ConstBuffer::SetPS(UINT slot)
{
	DC->UpdateSubresource(buffer, 0, nullptr, data, 0, 0);
	DC->PSSetConstantBuffers(slot, 1, &buffer);
}
