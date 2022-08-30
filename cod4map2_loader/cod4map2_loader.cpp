#include "h.h"

//in case the user's cod4 directory has whitespaces
void cod4map::FixArgumentPaths(int argc, char* argv[], std::string& out)
{
    if (argc < 5)
        U::ExitProgramWithReason("less than 5 arguments passed (" + std::to_string(argc) + ")\n\n");

    std::string cod4dir = F::F_GoToPreviousDirectory(F::F_GetExePath()); 


    //just the exe path
    std::string fixed_str = '"' + cod4dir + "\\bin\\cod4map2_loader" + '"' + ' ';
    //memcpy(argv[0], fixed_str.c_str(), fixed_str.size());
    out += fixed_str;
    out += argv[1];
    out += ' ';
    out += argv[2];
    out += ' ';
    out += argv[3];
    out += ' ';

    // map_source\mapname.map;
    std::string mapname = argv[4];
    mapname = F::F_GetFileName(mapname);
    fixed_str = '"' + cod4dir + "\\map_source\\" + mapname + '"' + ' ';
    //memcpy(argv[4], fixed_str.c_str(), fixed_str.size());
    out += fixed_str;
    // raw\maps\mp\mapname (without extension)
    std::string extension = F::F_GetFileExtension(mapname);
    fixed_str = '"' + cod4dir + "\\raw\\maps\\mp\\" + F::F_removeFileExtension(mapname, extension.size()) + '"' + ' ';
    //memcpy(argv[5], fixed_str.c_str(), fixed_str.size());
    out += fixed_str;
    
}

bool cod4map::OpenCoD4Map(int argc, char* argv[])
{
   // std::string wd = F::F_GetExePath();
    std::string full = "";
    FixArgumentPaths(argc, argv, full);

    

   // U::ExitProgramWithReason("\n\n");

    std::string wd = F::F_GetExePath();
    if (!F::F_FileBelongsToThisDirectory(wd, wd + "\\cod4map.exe"))
        return false;

    wd += "\\cod4map.exe";


    std::string args;
    for (int i = 0; i < argc; i++) {
        args += argv[i];
        args.push_back(' ');
    }

    LPSTR cmdline = const_cast<LPSTR>(full.c_str());
    std::cout << "cmdline: " << cmdline << '\n';

   // std::cout << "cmdline:" << cmdline << '\n';

   // U::ExitProgramWithReason("\n\n");

    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    // set the size of the structures
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));
   

    if (!CreateProcessA(wd.c_str(), cmdline, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
        printf("CreateProcess failed (%d).\n", GetLastError());
        U::ExitProgramWithReason("\n\n");
    }
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    std::cout << "path: " << wd << '\n';

    return true;
}

int main(int argcount, char* argv[])
{
    printf("arguments passed: ");
    for (int i = 0; i < argcount; i++) {
        printf("[%i]: %s ", i, argv[i]);
    }
    std::cout << '\n';
    if (argcount < 1)
        U::ExitProgramWithReason("no arguments passed\n\n");

    if (!cod4map::OpenCoD4Map(argcount, argv))
        U::ExitProgramWithReason("Couldn't open cod4map.exe\nMake sure this .exe is in your root\\bin folder\n\n");

    Sleep(100);

    std::string path = F::F_GetExePath();
    printf("hooking to the process..\n");
    if (!U::InjectDLL(path + "\\cod4map2.dll", U::getProcessID("cod4map.exe"))) {
        U::ErrorText("Couldn't inject dll from:\n");
        U::ExitProgramWithReason(path + "\n");
    }
    printf("successfully hooked!\n");
    while (true) {
        DWORD pid = U::getProcessID("cod4map.exe");

        if (!pid) {
            printf("removing the hook..\n");
            break;
        }
        Sleep(500);
    }

}
