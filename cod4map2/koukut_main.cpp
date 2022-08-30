#include "h.h"

int sub_40CFB0()
{
	int val{};
	DWORD fn = 0x40CFB0;
	_asm {
		call fn;
		mov eax, val;
	}

	return val;
}
void sub_463E30()
{
	DWORD fn = 0x463E30;
	_asm {
		call fn;
	}
}
int sub_449E50()
{
	int val{};
	DWORD fn = 0x449E50;
	_asm {
		call fn;
		mov eax, val;
	}

	return val;
}
void sub_464AB0()
{
	DWORD fn = 0x464AB0;
	_asm {
		call fn;
	}
}
char* sub_40DCD0()
{
	char* returnval{};

	DWORD fn = 0x040DCD0;
	_asm {
		call fn;
		mov eax, returnval;
	}
	return returnval;
}
int __cdecl CreateLumps(LPCSTR lpFileName)
{
	int returnval{};
	DWORD fn = 0x40B840;
	_asm
	{
		push lpFileName;
		call fn;
		mov eax, returnval;
	}
	return returnval;
}
int WriteBSPFile()
{
//	char* v0;
	char buffer[1024];

	char byte_A357E8[1024];

	memcpy_s(byte_A357E8, 1024, (void*)0xA357E8, 1024);

	byte_A357E8[1023] = 0;

	sub_463E30();
	sub_40CFB0();
	sub_449E50();
	sub_464AB0();

	if (*(bool*)0x11BA8408)
		printf("\nNot writing map due to errors\n");

	//v0 = sub_40DCD0();

	sprintf_s(buffer, "%s%s", byte_A357E8, ".d3dbsp");
	printf("Writing %s\n", buffer);

	float lightbytes = (3145728 * *(int*)0x11BA8428) / 1e+6;

	printf("\nMAX_MAP_BRUSHES				%i/%i\n", *(int*)0x0FB973FC, 0x8000);
	printf("MAX_MAP_BRUSHSIDES			%i/%i\n", *(int*)0x0FB97404, 655360);
	printf("MAX_MAP_BRUSHEDGES			%i/%i\n", *(int*)0x0987F474, 0x200000);
	printf("MAX_MAP_TRIANGLES			%i/%i\n", *(int*)0x26E0DED8, 655360);
	printf("MAX_MAP_VERTICES			%i/%i\n", *(int*)0x26E0DEDC + 3, 1966080);
	printf("MAX_MAP_LAYERED_MATERIALS		%i/%i\n", *(int*)0x16ED9D8C, 1024);
	printf("MAX_MAP_DRAW_SURFS			%i/%i\n", *(int*)0x14899CBC, 393216);
	printf("MAX_MAP_MATERIALS			%i/%i\n", *(int*)0x06981750, 1224);
	printf("MAX_MAP_PLANES				%i/%i\n", *(int*)0x0A6FF3DC, 0x10000);
	printf("MAX_MAP_NODES				%i/%i\n", *(int*)0x06735C10, 0x8000);
	printf("MAX_MAP_LEAFS				%i/%i\n", *(int*)0x0A6FF3E0, 0x8000);
	printf("MAX_MAP_LEAFBRUSHES			%i/%i\n", *(int*)0x09C7F47C, 0x40000);
	printf("MAX_MAP_LIGHTBYTES			%g/%gMB, lightmaps: %i\n", lightbytes, 93.0f, *(int*)0x11BA8428 - 1);
	printf("MAX_MAP_PATCH_COL_VERTS			%i/%i\n", *(int*)0x11BA5D74, 0x10000);
	printf("MAX_MAP_COLLISIONTRIS			%i/%i\n", *(int*)0x06735C14, 0x20000);
	printf("MAX_MAP_COLLISIONVERTS			%i/%i\n", *(int*)0x0AE2741C, 0x10000);

	return CreateLumps(buffer);
}
void game::Com_Hooks(LPTHREAD_START_ROUTINE startAddr)
{

	hook* a = nullptr;

	a->install(0x4649F0, WriteBSPFile);

}