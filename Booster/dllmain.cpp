// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "pch.h"

#include "PriorityHelper.h"
#include "D3D11Hook.h"


BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    if (DetourIsHelperProcess()) {
        return TRUE;
    }
    
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    {
        DisableThreadLibraryCalls(hModule);
        DetourRestoreAfterWith();

        SetProcessPriorityClassToRealtime();

        InitD3D11Hook();
    }
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

// We must have an dummy export or Detours dll injection will fail
__declspec(dllexport) VOID WINAPI DummyExport(VOID)
{
    return;
}
