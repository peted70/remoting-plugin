// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"

// This will cause 
// warning C4447: 'main' signature found without threading model. 
// Consider using 'int main(Platform::Array<Platform::String^>^ args)'.
// as we are currently compiling with /Zw flag - fix would be to not compile this
// file with /Zw. Not doing that now as there are implications for PCHs
//
BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

