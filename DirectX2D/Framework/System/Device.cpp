#include "Framework.h"
#include "Device.h"

Device::Device()
{
	UINT width = WIN_WIDTH;
	UINT height = WIN_HEIGHT;

#pragma region CreateSwapChain
	//���� ����
	DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
	swapChainDesc.BufferDesc.Width = width;
	swapChainDesc.BufferDesc.Height = height;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; //RGBA 8��Ʈ��. UNORM = unsigned normal(0~1)
	swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
	swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	//RefreshRate : ���÷��� ��� ���ŷ�(�ֻ��� : Numerator / Denominator)

	//ǥ��ȭ ��������� ���� ���� ����� ���ҽ��� ǥ���� �����δ� ���
	//�ִ�ǥ��ȭ : ��û Ű������ ��� ���Ѽ� ���(�޸� ���� ��ƸԾ dx���� �� ��)
	//����ǥ��ȭ : ������ �������� ��(�����ؼ� ���� ���α׷��ֿ��� ���⿣ �δ㽺����)
	swapChainDesc.SampleDesc.Count = 1;     //1��
	swapChainDesc.SampleDesc.Quality = 0;   //�� ����
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.BufferCount = 1;          //����� ���� 
	swapChainDesc.OutputWindow = hWnd;      //������ ����
	swapChainDesc.Windowed = true;          //â��� / ��ü���

	D3D11CreateDeviceAndSwapChain(
		nullptr,                            //����� : �ǽð� ȭ�� ũ�� ������ �ʿ�. 
		D3D_DRIVER_TYPE_HARDWARE,           //������ ����̹�. ���ķ����� ��� �� ����Ʈ���� ���
		0,                                  //����� ����Ʈ����. 0 == ��� �� ��
		D3D10_CREATE_DEVICE_DEBUG | D3D11_CREATE_DEVICE_BGRA_SUPPORT,
		nullptr,                            //��� üũ
		0,
		D3D11_SDK_VERSION,                  //���� ���� ����
		&swapChainDesc,                     //������ ���� ������
		&swapChain,
		&device,
		nullptr,
		&deviceContext
	);
#pragma endregion

#pragma region CreateRenderTargetView
	ID3D11Texture2D* backBuffer = nullptr;
	swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBuffer);
	device->CreateRenderTargetView(backBuffer, nullptr, &renderTargetView);
	backBuffer->Release();
#pragma endregion
	deviceContext->OMSetRenderTargets(1, &renderTargetView, nullptr);
}

Device::~Device()
{
	renderTargetView->Release();
	swapChain->Release();

	deviceContext->Release();
	device->Release();
}

void Device::Clear()
{
	deviceContext->OMSetRenderTargets(1, &renderTargetView, nullptr);

	float clearColor[4] = { 0.0f, 0.125f, 0.3f, 1.0f };
	deviceContext->ClearRenderTargetView(renderTargetView, clearColor); //����Ÿ�ٺ� �ʱ�ȭ
}

void Device::Present()
{
	//����� ����
	swapChain->Present(0, 0);   //��� ������ ���� ��� �غ�
}
