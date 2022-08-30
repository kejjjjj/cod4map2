#pragma once

#ifndef tutils
#define tutils
#include "h.h"
namespace U
{
	template <typename t>
	void vecReset(std::vector<t>* vec, size_t size) {
		vec->clear();
		vec->resize(size);
		vec->erase(vec->begin(), vec->end());
	}
	size_t CountCharsInStr(std::string str, char ch);
	void ErrorText(std::string text);
	void ExitProgramWithReason(std::string reason);
	DWORD getProcessID(const char* proc);
	bool InjectDLL(std::string dllPath, DWORD pid);
}

#endif