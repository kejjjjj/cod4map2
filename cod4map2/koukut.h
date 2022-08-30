#pragma once

#ifndef koukut
#define koukut

#include "h.h"

#define INRANGE(x,a,b)    (x >= a && x <= b) 
#define getBits( x )    (INRANGE((x&(~0x20)),'A','F') ? ((x&(~0x20)) - 'A' + 0xa) : (INRANGE(x,'0','9') ? x - '0' : 0))
#define getByte( x )    (getBits(x[0]) << 4 | getBits(x[1]))

class hook
{
public:

	void install(std::uintptr_t address, void* func);
	void install(void* address, void* func);

	void nop(std::uintptr_t address);
	void write_addr(void* addr, const char* bytes, size_t len);
	void write_addr(std::uintptr_t addr, const char* bytes, size_t len);
	void write_addr(void* addr, char* byte);

	void get_bytes(void* addr, size_t len, char* buf);
	void get_bytes(std::uintptr_t addr, size_t len, char* buf);
	std::uintptr_t find_pattern(std::string moduleName, std::string pattern);
	std::uintptr_t find_pattern(DWORD start_address, DWORD end_address, std::string pattern);
	const char* bytes_to_text(const char* bytes);

private:

};

namespace game
{
	void Com_Hooks(LPTHREAD_START_ROUTINE startAddr);

}

#endif