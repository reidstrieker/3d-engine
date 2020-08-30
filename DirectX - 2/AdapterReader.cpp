#include "AdapterReader.h"

std::vector<AdapterData> AdapterReader::adapters; // definition for static vector

std::vector<AdapterData> AdapterReader::GetAdapters() {
	if (adapters.size() > 0) // if already initialized, return vector; otherwise, enumerate adapters
		return adapters;

	// create graphics interface for factory

	Microsoft::WRL::ComPtr<IDXGIFactory> pFactory;

	HRESULT hr = CreateDXGIFactory(__uuidof(IDXGIFactory), reinterpret_cast<void**>(pFactory.GetAddressOf())); // creates a DXGIFactory object
	if (FAILED(hr)) { // if we fail to create the factory
		ErrorLogger::Log(hr, "Failed to create DXGIFactory for enumerating adapters.");
		exit(-1);
	}

	// enumerating adapters

	IDXGIAdapter *pAdapter;
	UINT index = 0;
	while (SUCCEEDED(pFactory->EnumAdapters(index, &pAdapter))) {
		adapters.push_back(AdapterData(pAdapter));
		index += 1;
	}
	return adapters;
}

AdapterData::AdapterData(IDXGIAdapter* pAdapter) { // constructor for adapter data
	this->pAdapter = pAdapter;
	HRESULT hr = pAdapter->GetDesc(&this->description);
	if (FAILED(hr)) {
		ErrorLogger::Log(hr, "Failed to Get Description for IDXGIAdapter.");
	}
}