#include "pch.h"

#include "PrivilegeHelper.h"

#include <Windows.h>


void ElevatePrivilege()
{
    const DWORD flags = TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY;
    TOKEN_PRIVILEGES tp;
    HANDLE token;
    LUID val;

    if (!OpenProcessToken(GetCurrentProcess(), flags, &token)) {
        OutputDebugString("GJK OpenProcessToken FAILED!");
        return;
    }

    if (!!LookupPrivilegeValue(NULL, SE_INC_BASE_PRIORITY_NAME, &val))
    {
        tp.PrivilegeCount = 1;
        tp.Privileges[0].Luid = val;
        tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

        if (!AdjustTokenPrivileges(token, false, &tp, sizeof(tp), NULL, NULL))
            OutputDebugString("GJK AdjustTokenPrivileges FAILED!");
    }

    CloseHandle(token);
}
