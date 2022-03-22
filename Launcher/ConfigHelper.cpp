#include "ConfigHelper.h"

#include <Windows.h>

#include <atlstr.h>


CString RetrieveKeyValuePair(LPCTSTR lpAppName, LPCTSTR lpKeyName, LPCTSTR lpDefault, LPCTSTR lpFileName)
{
    CString ret;
    GetPrivateProfileString(lpAppName, lpKeyName, lpDefault, ret.GetBuffer(), MAX_PATH, lpFileName);

    return ret.GetBuffer();
}
