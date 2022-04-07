#include "pch.h"

#include "PriorityHelper.h"

#include "PrivilegeHelper.h"

#include <Windows.h>

#include <bcrypt.h>

#include <dxgi.h>


void SetProcessPriorityClassToRealtime()
{
    SetPriorityClass(GetCurrentProcess(), REALTIME_PRIORITY_CLASS);
}

void SetThreadPriorityToTimeCritical()
{
    SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_TIME_CRITICAL);
}

bool ElevateDxgiPriority(IUnknown* device)
{
    IDXGIDevice* dxgiDevice = nullptr;
    device->QueryInterface(__uuidof(IDXGIDevice), (void**)&dxgiDevice);

    HRESULT hr = dxgiDevice->SetGPUThreadPriority(7); // Highest priority is 7

    dxgiDevice->Release();

    if (FAILED(hr)) {
        OutputDebugString("GJK SetGPUThreadPriority FAILED!");
        return false;
    }

    return true;
}

bool ElevateDwmPriority()
{
    typedef enum _D3DKMT_SCHEDULINGPRIORITYCLASS {
        D3DKMT_SCHEDULINGPRIORITYCLASS_IDLE,
        D3DKMT_SCHEDULINGPRIORITYCLASS_BELOW_NORMAL,
        D3DKMT_SCHEDULINGPRIORITYCLASS_NORMAL,
        D3DKMT_SCHEDULINGPRIORITYCLASS_ABOVE_NORMAL,
        D3DKMT_SCHEDULINGPRIORITYCLASS_HIGH,
        D3DKMT_SCHEDULINGPRIORITYCLASS_REALTIME
    } D3DKMT_SCHEDULINGPRIORITYCLASS;

    HMODULE gdi32 = GetModuleHandle("GDI32");
    if (!gdi32) {
        OutputDebugString("GJK GetModuleHandle FAILED!");
        return false;
    }

    NTSTATUS(WINAPI * d3dkmt_spspc)(HANDLE, D3DKMT_SCHEDULINGPRIORITYCLASS);
    d3dkmt_spspc = (decltype(d3dkmt_spspc))GetProcAddress(gdi32, "D3DKMTSetProcessSchedulingPriorityClass");
    if (!d3dkmt_spspc) {
        OutputDebugString("GJK GetProcAddress FAILED!");
        return false;
    }

    NTSTATUS status = d3dkmt_spspc(GetCurrentProcess(), D3DKMT_SCHEDULINGPRIORITYCLASS_REALTIME);
    if (status != 0) {
        OutputDebugString("GJK d3dkmt_spspc FAILED!");
        return false;
    }

    return true;
}

bool ElevatePriority(IUnknown* device)
{
    bool ret = ElevateDxgiPriority(device);
    bool ret1 = ElevateDwmPriority();

    return ret && ret1; // Prevent lazy evaluation of above functions
}
