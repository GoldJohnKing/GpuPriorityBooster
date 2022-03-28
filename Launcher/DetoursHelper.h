#pragma once

#include <atlstr.h>


// Create process with Detours dll injection
void DetrousCreateProcess(CString exeFileName, CString params, CString dllFileName, CString currentDirectory);
