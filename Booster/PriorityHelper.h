#pragma once

#include <d3d11.h>


void SetProcessPriorityClassToRealtime();

// Currently not used
void SetThreadPriorityToTimeCritical();

bool ElevatePriority(ID3D11Device* device);
