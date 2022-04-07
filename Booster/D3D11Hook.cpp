#include "pch.h"

#include "D3D11Hook.h"

#include "DetoursHelper.h"
#include "PriorityHelper.h"

#include <Windows.h>

#include <d3d11.h>


// D3D11CreateDevice API Hook - Start

typedef HRESULT(WINAPI* __lpfnD3D11CreateDevice)(
    __in_opt IDXGIAdapter* pAdapter,
    DWORD DriverType,
    HMODULE Software,
    UINT Flags,
    __in_ecount_opt(FeatureLevels) CONST DWORD* pFeatureLevels,
    UINT FeatureLevels,
    UINT SDKVersion,
    __out_opt ID3D11Device** ppDevice,
    __out_opt DWORD* pFeatureLevel,
    __out_opt ID3D11DeviceContext** ppImmediateContext);

__lpfnD3D11CreateDevice SysD3D11CreateDevice = NULL;

static HRESULT WINAPI MyD3D11CreateDevice(
    __in_opt IDXGIAdapter* pAdapter,
    DWORD DriverType,
    HMODULE Software,
    UINT Flags,
    __in_ecount_opt(FeatureLevels) CONST DWORD* pFeatureLevels,
    UINT FeatureLevels,
    UINT SDKVersion,
    __out_opt ID3D11Device** ppDevice,
    __out_opt DWORD* pFeatureLevel,
    __out_opt ID3D11DeviceContext** ppImmediateContext)
{
    HRESULT hr = SysD3D11CreateDevice(pAdapter, DriverType, Software, Flags, pFeatureLevels, FeatureLevels, SDKVersion, ppDevice, pFeatureLevel, ppImmediateContext);
    if (FAILED(hr) || !ppDevice) {
        OutputDebugString("GJK SysD3D11CreateDevice FAILED!");
        return hr;
    }

    ElevatePriority(*ppDevice);

    return hr;
}

// D3D11CreateDevice API Hook - End


// D3D11CreateDeviceAndSwapChain API Hook - Start

typedef HRESULT(WINAPI* __lpfnD3D11CreateDeviceAndSwapChain)(
    __in_opt IDXGIAdapter* pAdapter,
    DWORD DriverType,
    HMODULE Software,
    UINT Flags,
    __in_ecount_opt(FeatureLevels) CONST DWORD* pFeatureLevels,
    UINT FeatureLevels,
    UINT SDKVersion,
    __in_opt CONST DXGI_SWAP_CHAIN_DESC* pSwapChainDesc,
    __out_opt IDXGISwapChain** ppSwapChain,
    __out_opt ID3D11Device** ppDevice,
    __out_opt DWORD* pFeatureLevel,
    __out_opt ID3D11DeviceContext** ppImmediateContext);

__lpfnD3D11CreateDeviceAndSwapChain SysD3D11CreateDeviceAndSwapChain = NULL;

static HRESULT WINAPI MyD3D11CreateDeviceAndSwapChain(
    __in_opt IDXGIAdapter* pAdapter,
    DWORD DriverType,
    HMODULE Software,
    UINT Flags,
    __in_ecount_opt(FeatureLevels) CONST DWORD* pFeatureLevels,
    UINT FeatureLevels,
    UINT SDKVersion,
    __in_opt CONST DXGI_SWAP_CHAIN_DESC* pSwapChainDesc,
    __out_opt IDXGISwapChain** ppSwapChain,
    __out_opt ID3D11Device** ppDevice,
    __out_opt DWORD* pFeatureLevel,
    __out_opt ID3D11DeviceContext** ppImmediateContext)
{
    HRESULT hr = SysD3D11CreateDeviceAndSwapChain(pAdapter, D3D_DRIVER_TYPE_UNKNOWN, Software, Flags, pFeatureLevels, FeatureLevels, SDKVersion, pSwapChainDesc, ppSwapChain, ppDevice, pFeatureLevel, ppImmediateContext);
    if (FAILED(hr) || !ppDevice) {
        OutputDebugString("GJK SysD3D11CreateDeviceAndSwapChain FAILED!");
        return hr;
    }

    ElevatePriority(*ppDevice);

    return hr;
}

// D3D11CreateDeviceAndSwapChain API Hook - End


void InitD3D11Hook()
{
    SysD3D11CreateDevice = (__lpfnD3D11CreateDevice)hook_api("d3d11", "D3D11CreateDevice", MyD3D11CreateDevice);
    SysD3D11CreateDeviceAndSwapChain = (__lpfnD3D11CreateDeviceAndSwapChain)hook_api("d3d11", "D3D11CreateDeviceAndSwapChain", MyD3D11CreateDeviceAndSwapChain);
}
