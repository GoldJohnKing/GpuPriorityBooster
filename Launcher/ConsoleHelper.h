#pragma once

#include <csignal>


// Prevent process from being interrupted by Ctrl+C
void InterceptConsoleInterruptSignal(int consoleSignal = SIGINT);
