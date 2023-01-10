#ifndef INDLL_H
#define INDLL_H
    #ifdef EXPORTING_DLL
        extern __declspec(dllexport) void connectToServer(int port, std::string ipAddr, std::string msg);
    #else
        extern __declspec(dllimport) void connectToServer(int port, std::string ipAddr, std::string msg);
    #endif
#endif