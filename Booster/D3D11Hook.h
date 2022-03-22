#pragma once


// We need to hook D3D11 API to retrieve DXGI Devices, only with that can we elevate priority
void InitD3D11Hook();
