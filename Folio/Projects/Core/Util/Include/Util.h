#pragma once

// "Home-made" includes.
#include    "CriticalSection.h"
#include    "DateTime.h"
#include    "Descriptions.h"
#include    "Event.h"
#include    "Exception.h"
#include    "File.h"
#include    "Gdi.h"
#include    "GdiBitmap.h"
#include    "HandleMonitor.h"
#include    "Heap.h"
#include    "KeyInput.h"
#include    "ModuleLoader.h"
#include    "Mutex.h"
#include    "Pointer.h"
#include    "ProcessInfo.h"
#include    "ProcessLoader.h"
#include    "ProcessSingleton.h"
#include    "Pulse.h"
#include    "Random.h"
#include    "Registry.h"
#include    "ScopedLock.h"
#include    "SecurityAttributes.h"
#include    "Semaphore.h"
#include    "SharedAtom.h"
#include    "SharedMemory.h"
#include    "SharedName.h"
#include    "SharedTable.h"
#include    "Sound.h"
#include    "SoundSample.h"
#include    "SoundSamplePlayer.h"
#include    "StaticMap.h"
#include    "Sync.h"
#include    "System.h"
#include    "Thread.h"
#include    "Timer.h"
#include    "Tls.h"
#include    "ValueDescriptor.h"
#include    "VirtualMemory.h"
#include    "WaitAny.h"
#include    "WaitableTimer.h"
#include    "WaveOutDevice.h"
#include    "Win32Exception.h"
#include    "Window.h"

#ifdef _DEBUG
#pragma comment(lib, "UtilD.lib")
#else
#pragma comment(lib, "Util.lib")
#endif

/******************************* End of File *******************************/
