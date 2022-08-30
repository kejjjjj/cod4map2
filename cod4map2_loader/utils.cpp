#include "h.h"
#define CREATE_THREAD_ACCESS (PROCESS_CREATE_THREAD | PROCESS_QUERY_INFORMATION | PROCESS_VM_OPERATION | PROCESS_VM_WRITE | PROCESS_VM_READ)

size_t U::CountCharsInStr(std::string str, char ch)
{
	int count{ 0 };
	int pos{ 0 };

	while (true) {
		pos = str.find(ch);
		if (pos < 1)
			break;

		str = str.substr(pos + 1);
		count += 1;


	}
	return count;
}
void U::ErrorText(std::string text)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	const char* p = text.c_str();
	SetConsoleTextAttribute(hConsole, 12);
	printf(p);
	SetConsoleTextAttribute(hConsole, 10);
}
void U::ExitProgramWithReason(std::string reason)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	ErrorText("ERROR: " + reason);
	system("pause");
	exit(1);
}
DWORD U::getProcessID(const char* proc)
{
	HANDLE hProcessId = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	DWORD process{};
	PROCESSENTRY32 pEntry{};
	pEntry.dwSize = sizeof(pEntry);

	do
	{
		if (!strcmp(pEntry.szExeFile, proc))
		{
			process = pEntry.th32ProcessID;
			CloseHandle(hProcessId);
			HANDLE handle = OpenProcess(PROCESS_ALL_ACCESS, false, process);
		}
	} while (Process32Next(hProcessId, &pEntry));

	return process;
}
bool U::InjectDLL(std::string dllPath, DWORD pid)
{
	HANDLE proc = OpenProcess(CREATE_THREAD_ACCESS, FALSE, pid);

	if (!proc) {
		ExitProgramWithReason("process cod4map.exe doesn't exist\n\n");
		return false; //never reached but just in case
	}

	int len = strlen(dllPath.c_str()) + 1;
	const char* charPath = dllPath.c_str();



	LPVOID lib = (LPVOID)GetProcAddress(GetModuleHandle("kernel32.dll"), "LoadLibraryA");

	if (!lib)
		return false;

	LPVOID dll = (LPVOID)VirtualAllocEx(proc, NULL, (SIZE_T)len, MEM_COMMIT, PAGE_READWRITE);

	WriteProcessMemory(proc, dll, (LPVOID)charPath, (SIZE_T)len, NULL);
	CreateRemoteThread(proc, NULL, NULL, (LPTHREAD_START_ROUTINE)lib, dll, NULL, NULL);



	return true;


}