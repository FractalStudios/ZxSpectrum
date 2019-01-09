#pragma once

// "Home-made" includes.
#include    "TraceClient.h"
#include    "TraceMacros.h"
#include    "TraceReporting.h"

#ifdef _DEBUG
#pragma comment(lib, "TraceD.lib")
#else
#pragma comment(lib, "Trace.lib")
#endif

/******************************* End of File *******************************/
