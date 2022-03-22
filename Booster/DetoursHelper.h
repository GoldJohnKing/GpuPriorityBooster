#pragma once


void hook_func(void** _target, void* _my_fun);

// Currently not used
void unhook_func(void** _target, void* _my_fun);

void* hook_api(const char* _dll_name, const char* _func_name, void* _my_func);

template<typename R, typename T>
void hook_api(const char* _dll_name, const char* _func_name, R _detour, T& _trampoline);
