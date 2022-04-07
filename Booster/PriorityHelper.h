#pragma once


void SetProcessPriorityClassToRealtime();

// Currently not used
void SetThreadPriorityToTimeCritical();

bool ElevatePriority(IUnknown* device);
