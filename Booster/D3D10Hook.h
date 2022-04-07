#pragma once


// We need to hook D3D10 API to retrieve DXGI Devices, only with that can we elevate priority
void InitD3D10Hook();
