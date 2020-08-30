#include "ErrorLogger.h"
#include <comdef.h>

void ErrorLogger::Log(std::string message) {
	std::string error_message = "Error: " + message; // creates an error message
	MessageBoxA(NULL, error_message.c_str(), "Error", MB_ICONERROR); // ASCII error message box
}

void ErrorLogger::Log(HRESULT hr, std::string message) {
	_com_error error(hr);
	std::wstring error_message = L"Error: " + StringConverter::StringToWide(message) + L"\n" + error.ErrorMessage(); // creates an error message
	MessageBoxW(NULL, error_message.c_str(), L"Error", MB_ICONERROR); // wide string error message box
	
}