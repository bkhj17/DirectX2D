#include "Framework.h"
#include "VertexShader.h"

VertexShader::VertexShader(wstring file)
{

#pragma region LoadVS
	//VS �ε�
	DWORD flags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG;
	
	D3DCompileFromFile(file.c_str(), nullptr, nullptr, "VS", "vs_5_0", flags, 0, &blob, nullptr);
	DEVICE->CreateVertexShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, &shader);

	D3D11_INPUT_ELEMENT_DESC layoutDesc[] = {
		{
			"POSITION",                 //���� ������ �ø�ƽ �̸�. hlsl�� ��ġ�ؾ���
			0,                          //�ø�ƽ ����(�ø�ƽ �ڿ� ���ڸ� ���̸� �����ؼ� ���� �� �ִ�
			DXGI_FORMAT_R32G32B32_FLOAT, //���� ���� ����
			0,                          //UINT InputSlot;   
			0,                          //UINT AlignedByteOffset; 
			D3D11_INPUT_PER_VERTEX_DATA,//D3D11_INPUT_CLASSIFICATION InputSlotClass;
			0                           //UINT InstanceDataStepRate;
		},
		{ "UV", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	UINT layoutSize = ARRAYSIZE(layoutDesc);
	DEVICE->CreateInputLayout(layoutDesc, layoutSize, blob->GetBufferPointer(), blob->GetBufferSize(), &inputLayout);

#pragma endregion
}

VertexShader::~VertexShader()
{
	shader->Release();
	inputLayout->Release();
}

void VertexShader::Set()
{
	DC->IASetInputLayout(inputLayout);
	DC->VSSetShader(shader, nullptr, 0);
}
