#include "DetoursHelper.h"

#include <Windows.h>
#include <atlstr.h>

#include "detours.h" // This header file must be below <Windows.h>, or Detours wont know which architecture to use


void DetrousCreateProcess(CString exeFileName, CString params, CString dllFileName, CString currentDirectory)
{
    CString exeFilePath = "\"" + currentDirectory + exeFileName + "\" " + params;
    CString dllFilePath = currentDirectory + dllFileName;

    OutputDebugString(exeFilePath.GetString());
    OutputDebugString(dllFilePath.GetString());

    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(STARTUPINFO));
    ZeroMemory(&pi, sizeof(PROCESS_INFORMATION));
    si.cb = sizeof(STARTUPINFO);

    DetourCreateProcessWithDll(NULL, exeFilePath.GetBuffer(), NULL, NULL,
        FALSE, CREATE_BREAKAWAY_FROM_JOB | REALTIME_PRIORITY_CLASS, NULL,
        currentDirectory, &si, &pi, dllFilePath, NULL);

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
}
