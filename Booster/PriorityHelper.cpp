#include "pch.h"

#include "PriorityHelper.h"

#include "PrivilegeHelper.h"

#include <Windows.h>

#include <bcrypt.h>

#include <dxgi.h>
#include <d3d11.h>


void SetProcessPriorityClassToRealtime()
{
    ElevatePrivilege();
    SetPriorityClass(GetCurrentProcess(), REALTIME_PRIORITY_CLASS);
}

void SetThreadPriorityToTimeCritical()
{
    ElevatePrivilege();
    SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_TIME_CRITICAL);
}

bool ElevatePriority(ID3D11Device* device)
{
    typedef enum _D3DKMT_SCHEDULINGPRIORITYCLASS {
        D3DKMT_SCHEDULINGPRIORITYCLASS_IDLE,
        D3DKMT_SCHEDULINGPRIORITYCLASS_BELOW_NORMAL,
        D3DKMT_SCHEDULINGPRIORITYCLASS_NORMAL,
        D3DKMT_SCHEDULINGPRIORITYCLASS_ABOVE_NORMAL,
        D3DKMT_SCHEDULINGPRIORITYCLASS_HIGH,
        D3DKMT_SCHEDULINGPRIORITYCLASS_REALTIME
    } D3DKMT_SCHEDULINGPRIORITYCLASS;

    IDXGIDevice* dxgiDevice = nullptr;
    device->QueryInterface(__uuidof(IDXGIDevice), (void**)&dxgiDevice);
    HRESULT hr = dxgiDevice->SetGPUThreadPriority(7); // Highest priority is 7
    dxgiDevice->Release();
    if (FAILED(hr)) {
        OutputDebugString("GJK SetGPUThreadPriority FAILED!");
        return false;
    }

    ElevatePrivilege();

    HMODULE gdi32 = GetModuleHandleW(L"GDI32");
    if (!gdi32) {
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
