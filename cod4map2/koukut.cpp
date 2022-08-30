#include "h.h"

void hook::install(std::uintptr_t address, void* fnc)
{
	DetourFunction(PBYTE(address), PBYTE(fnc));
}
void hook::install(void* address, void* fnc)
{
	DetourFunction(PBYTE(address), PBYTE(fnc));
}
void hook::nop(std::uintptr_t address)
{
	DWORD oldProtect;

	VirtualProtect((void*)address, 5, PAGE_EXECUTE_READWRITE, &oldProtect);
	memcpy((void*)address, "\x90\x90\x90\x90\x90", 5);
#pragma warning(suppress: 6387)
	VirtualProtect((void*)address, 5, oldProtect, NULL);
}
void hook::write_addr(void* addr, const char* bytes, size_t len)
{
	DWORD oldProtect;

	VirtualProtect(addr, len, PAGE_EXECUTE_READWRITE, &oldProtect);
	memcpy(addr, bytes, len);
#pragma warning(suppress: 6387)
	VirtualProtect((LPVOID)addr, len, oldProtect, NULL);
}
void hook::write_addr(std::uintptr_t addr, const char* bytes, size_t len)
{
	write_addr((void*)addr, bytes, len);
}
void hook::write_addr(void* addr, char* byte)
{
	DWORD oldProtect;

	VirtualProtect(addr, 1, PAGE_EXECUTE_READWRITE, &oldProtect);
	memcpy(addr, byte, 1);
#pragma warning(suppress: 6387)
	VirtualProtect((LPVOID)addr, 1, oldProtect, NULL);
}
void hook::get_bytes(void* addr, size_t len, char* buffer)
{

	std::cout << "reading from: " << std::hex << (size_t)addr << '\n';
	//static char buffer[1024 * 4];
	int chars = 0;
	char* _bytes{};

	for (size_t i = 0; i < len; i++) {
		if (chars >= 0 && chars < 1024 * 4) {
			chars += snprintf(buffer + chars, len, "%02x", *(BYTE*)((size_t)addr + i));
			continue;
		}
		break;
	}
#pragma warning(suppress: 6386)
	buffer[chars + 1] = '\0';

}
void hook::get_bytes(std::uintptr_t addr, size_t len, char* buffer)
{
	get_bytes((void*)addr, len, buffer);
}
std::uintptr_t hook::find_pattern(std::string moduleName, std::string pattern)
{

	DWORD firstMatch = 0;
	DWORD rangeStart = (DWORD)GetModuleHandleA(moduleName.c_str());
	MODULEINFO miModInfo; K32GetModuleInformation(GetCurrentProcess(), (HMODULE)rangeStart, &miModInfo, sizeof(MODULEINFO));
	DWORD rangeEnd = rangeStart + miModInfo.SizeOfImage;

	return find_pattern(rangeStart, rangeEnd, pattern);


}
std::uintptr_t hook::find_pattern(DWORD start_address, DWORD end_address, std::string pattern)
{
	hook* a = nullptr;
	const char* pat = a->bytes_to_text(pattern.c_str());
	std::cout << "using pattern: [" << pat << "]\n";
	DWORD firstMatch = 0;

	for (DWORD pCur = start_address; pCur < end_address; pCur++)
	{

		if (*(PBYTE)pat == '\?' || *(BYTE*)pCur == getByte(pat))
		{
			if (!firstMatch)
				firstMatch = pCur;

			if (!pat[2])
				return firstMatch;

			if (*(PWORD)pat == '\?\?' || *(PBYTE)pat != '\?')
				pat += 3;

			else
				pat += 2;    //one ?
		}
		else
		{
			pat = a->bytes_to_text(pattern.c_str());
			firstMatch = 0;
		}
	}
	std::cout << "pattern not found\n";
	return NULL;
}
const char* hook::bytes_to_text(const char* bytes)
{
	/*
	\x89\x45\xC1 -> 89 45 C1
	*/

	std::string result = bytes;
	std::string final_bytes;

	char buffer[1024 * 4];


	for (size_t i = 0; i < result.size(); i++) {
		if ((int)result[i] < 0) {
			snprintf(buffer, 9, "%X", result[i]);
			std::string new_result = buffer;
			new_result = new_result.substr(6);
			final_bytes.push_back(new_result[0]);
			final_bytes.push_back(new_result[1]);
			final_bytes.push_back(' ');
			continue;
		}
		else if ((int)result[i] == 0) {
			final_bytes.push_back(result[i]);
			final_bytes.push_back(' ');
			continue;
		}
		snprintf(buffer, 3, "%X", result[i]);
		final_bytes.push_back(buffer[0]);
		final_bytes.push_back(buffer[1]);
		final_bytes.push_back(' ');
	}

	//std::cout << "result: " << final_bytes << '\n';
	final_bytes.pop_back();
	const char* ret = final_bytes.c_str();

	return ret;
}