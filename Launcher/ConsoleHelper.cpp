#include "ConsoleHelper.h"

#include <csignal>


void InterceptConsoleInterruptSignal(int consoleSignal)
{
    signal(SIGINT, InterceptConsoleInterruptSignal);
}
