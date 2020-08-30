#include "StringConverter.h"

std::wstring StringConverter::StringToWide(std::string str) {
	std::wstring wide_string(str.begin(), str.end()); // basic wide string constructor
	return wide_string;
}