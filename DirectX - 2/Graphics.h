#pragma once
#include "AdapterReader.h"

class Graphics {
public:
	bool Initialize(HWND hwnd, int width, int height);
private:
	bool InitializeDirectX(HWND hwnd, int width, int height);

	Microsoft::WRL::ComPtr<ID3D11Device> device; // used to create buffers
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> deviceContext; // used to set different resources for rendering
	Microsoft::WRL::ComPtr<IDXGISwapChain> swapchain; // used to swap out frames while rendering
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> renderTargetView; // for where we will render the buffer to (the window)
};