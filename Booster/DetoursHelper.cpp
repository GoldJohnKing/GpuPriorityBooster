#include "pch.h"

#include "DetoursHelper.h"
#include "PriorityHelper.h"

#include <Windows.h>

#include <atlstr.h>

#include <detours.h>


void hook_func(void** _target, void* _my_fun)
{
    if (NULL == _target || NULL == _my_fun)
        return;
    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());
    DetourAttach(_target, _my_fun);
    DetourTransactionCommit();
}

void unhook_func(void** _target, void* _my_fun)
{
    if (NULL == _target || NULL == _my_fun)
        return;
    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());
    DetourDetach(_target, _my_fun);
    DetourTransactionCommit();
}

void* hook_api(const char* _dll_name, const char* _func_name, void* _my_func)
{
    HMODULE module = GetModuleHandleA(_dll_name);

    if (NULL == module)
    {
        CString strPath = _dll_name;
        int p = strPath.ReverseFind('\\');

        if (-1 != p)
            module = LoadLibraryExA(_dll_name, NULL, LOAD_WITH_ALTERED_SEARCH_PATH);
        else
            module = LoadLibraryA(_dll_name);

        if (NULL == module)
            return NULL;
    }

    void* res = (void*)GetProcAddress(module, _func_name);
    if (NULL == res)
        return NULL;

    hook_func(&res, _my_func);
    return res;
}

template<typename R, typename T>
void hook_api(const char* _dll_name, const char* _func_name, R _detour, T& _trampoline)
{
    R _temp = _detour;
    _trampoline = (T)hook_api(_dll_name, _func_name, *(PBYTE*)&_temp);
}
