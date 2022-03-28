#include "ConsoleHelper.h"
#include "DetoursHelper.h"
#include "FilePathHelper.h"
#include "ConfigHelper.h"

#include <Windows.h>

#include <atlstr.h>

// Never show the console window
#pragma comment(linker, "/subsystem:windows /entry:mainCRTStartup")


int main()
{
    InterceptConsoleInterruptSignal();

    CString currentDirectory = GetModulePath();
    CString configFilePath = currentDirectory + "GPUPriorityBoosterConfig.ini";
    CString sectionName = "Launcher";

    CString exeFileName = RetrieveKeyValuePair(sectionName.GetString(), "Exe", "FoxTracker.exe", configFilePath.GetString());
    CString dllFileName = RetrieveKeyValuePair(sectionName.GetString(), "Dll", "GPUPriorityBoosterHelper.dll", configFilePath.GetString());
    CString params = RetrieveKeyValuePair(sectionName.GetString(), "Params", "", configFilePath.GetString());

    DetrousCreateProcess(exeFileName, params, dllFileName, currentDirectory);
}
