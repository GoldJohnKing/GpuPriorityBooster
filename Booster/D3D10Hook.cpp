#include "pch.h"

#include "D3D10Hook.h"

#include "DetoursHelper.h"
#include "PriorityHelper.h"

#include <Windows.h>

#include <d3d10_1.h>


// D3D10CreateDevice API Hook - Start

typedef HRESULT(WINAPI* __lpfnD3D10CreateDevice)(
    IDXGIAdapter* pAdapter,
    D3D10_DRIVER_TYPE DriverType,
    HMODULE Software,
    UINT Flags,
    UINT SDKVersion,
    ID3D10Device** ppDevice);

static __lpfnD3D10CreateDevice				SysD3D10CreateDevice;

HRESULT WINAPI MyD3D10CreateDevice(IDXGIAdapter* pAdapter,
    D3D10_DRIVER_TYPE DriverType,
    HMODULE Software,
    UINT Flags,
    UINT SDKVersion,
    ID3D10Device** ppDevice)
{
    HRESULT hr = SysD3D10CreateDevice(pAdapter, DriverType, Software, Flags, SDKVersion, ppDevice);
    if (FAILED(hr) || !ppDevice) {
        OutputDebugString("GJK SysD3D10CreateDevice FAILED!");
        return hr;
    }

    ElevatePriority(*ppDevice);

    return hr;
}

// D3D10CreateDevice API Hook - End


// D3D10CreateDevice1 API Hook - Start

typedef HRESULT(WINAPI* __lpfnD3D10CreateDevice1)(
    __in   IDXGIAdapter* pAdapter,
    __in   D3D10_DRIVER_TYPE DriverType,
    __in   HMODULE Software,
    __in   UINT Flags,
    __in   D3D10_FEATURE_LEVEL1 HardwareLevel,
    __in   UINT SDKVersion,
    __out  ID3D10Device1** ppDevice);

static __lpfnD3D10CreateDevice1 SysD3D10CreateDevice1;


HRESULT WINAPI MyD3D10CreateDevice1(
    __in   IDXGIAdapter* pAdapter,
    __in   D3D10_DRIVER_TYPE DriverType,
    __in   HMODULE Software,
    __in   UINT Flags,
    __in   D3D10_FEATURE_LEVEL1 HardwareLevel,
    __in   UINT SDKVersion,
    __out  ID3D10Device1** ppDevice)
{
    HRESULT hr = SysD3D10CreateDevice1(pAdapter, DriverType, Software, Flags, HardwareLevel, SDKVersion, ppDevice);
    if (FAILED(hr) || !ppDevice) {
        OutputDebugString("GJK SysD3D10CreateDevice1 FAILED!");
        return hr;
    }

    ElevatePriority(*ppDevice);

    return hr;
}

// D3D10CreateDevice1 API Hook - End


// D3D10CreateDeviceAndSwapChain API Hook - Start

typedef HRESULT(WINAPI* __lpfnD3D10CreateDeviceAndSwapChain)(
    IDXGIAdapter* pAdapter,
    D3D10_DRIVER_TYPE DriverType,
    HMODULE Software,
    UINT Flags,
    UINT SDKVersion,
    DXGI_SWAP_CHAIN_DESC* pSwapChainDesc,
    IDXGISwapChain** ppSwapChain,
    ID3D10Device** ppDevice);

static __lpfnD3D10CreateDeviceAndSwapChain SysD3D10CreateDeviceAndSwapChain;

HRESULT WINAPI MyD3D10CreateDeviceAndSwapChain(
    IDXGIAdapter* pAdapter,
    D3D10_DRIVER_TYPE DriverType,
    HMODULE Software,
    UINT Flags,
    UINT SDKVersion,
    DXGI_SWAP_CHAIN_DESC* pSwapChainDesc,
    IDXGISwapChain** ppSwapChain,
    ID3D10Device** ppDevice)
{
    HRESULT hr = SysD3D10CreateDeviceAndSwapChain(pAdapter, DriverType, Software, Flags, SDKVersion, pSwapChainDesc, ppSwapChain, ppDevice);
    if (FAILED(hr) || !ppDevice) {
        OutputDebugString("GJK SysD3D10CreateDeviceAndSwapChain FAILED!");
        return hr;
    }

    ElevatePriority(*ppDevice);

    return hr;
}

// D3D10CreateDeviceAndSwapChain API Hook - End


// D3D10CreateDeviceAndSwapChain1 API Hook - Start

typedef HRESULT(WINAPI* __lpfnD3D10CreateDeviceAndSwapChain1)(
    __in   IDXGIAdapter* pAdapter,
    __in   D3D10_DRIVER_TYPE DriverType,
    __in   HMODULE Software,
    __in   UINT Flags,
    __in   D3D10_FEATURE_LEVEL1 HardwareLevel,
    __in   UINT SDKVersion,
    __in   DXGI_SWAP_CHAIN_DESC* pSwapChainDesc,
    __out  IDXGISwapChain** ppSwapChain,
    __out  ID3D10Device1** ppDevice);

static __lpfnD3D10CreateDeviceAndSwapChain1	SysD3D10CreateDeviceAndSwapChain1;

HRESULT WINAPI MyD3D10CreateDeviceAndSwapChain1(
    __in   IDXGIAdapter* pAdapter,
    __in   D3D10_DRIVER_TYPE DriverType,
    __in   HMODULE Software,
    __in   UINT Flags,
    __in   D3D10_FEATURE_LEVEL1 HardwareLevel,
    __in   UINT SDKVersion,
    __in   DXGI_SWAP_CHAIN_DESC* pSwapChainDesc,
    __out  IDXGISwapChain** ppSwapChain,
    __out  ID3D10Device1** ppDevice)
{
    HRESULT hr = SysD3D10CreateDeviceAndSwapChain1(pAdapter, DriverType, Software, Flags, HardwareLevel, SDKVersion, pSwapChainDesc, ppSwapChain, ppDevice);
    if (FAILED(hr) || !ppDevice) {
        OutputDebugString("GJK SysD3D10CreateDeviceAndSwapChain1 FAILED!");
        return hr;
    }

    ElevatePriority(*ppDevice);

    return hr;
}

// D3D10CreateDeviceAndSwapChain1 API Hook - End


void InitD3D10Hook()
{
    SysD3D10CreateDevice = (__lpfnD3D10CreateDevice)hook_api("d3d10", "D3D10CreateDevice", MyD3D10CreateDevice);
    SysD3D10CreateDevice1 = (__lpfnD3D10CreateDevice1)hook_api("d3d10_1", "D3D10CreateDevice1", MyD3D10CreateDevice1);
    SysD3D10CreateDeviceAndSwapChain = (__lpfnD3D10CreateDeviceAndSwapChain)hook_api("d3d10", "D3D10CreateDeviceAndSwapChain", MyD3D10CreateDeviceAndSwapChain);
    SysD3D10CreateDeviceAndSwapChain1 = (__lpfnD3D10CreateDeviceAndSwapChain1)hook_api("d3d10_1", "D3D10CreateDeviceAndSwapChain1", MyD3D10CreateDeviceAndSwapChain1);
}
