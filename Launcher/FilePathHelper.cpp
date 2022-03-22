#include "FilePathHelper.h"

#include <Windows.h>

#include <atlstr.h>


CString GetModulePath()
{
    TCHAR szPath[MAX_PATH];
    GetModuleFileName(GetModuleHandle(NULL), szPath, MAX_PATH);
    PathRemoveFileSpec(szPath);
    PathAddBackslash(szPath);
    return szPath;
}
