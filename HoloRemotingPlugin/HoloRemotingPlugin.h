// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the HOLOREMOTINGPLUGIN_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// HOLOREMOTINGPLUGIN_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef HOLOREMOTINGPLUGIN_EXPORTS
#define HOLOREMOTINGPLUGIN_API __declspec(dllexport)
#else
#define HOLOREMOTINGPLUGIN_API __declspec(dllimport)
#endif

typedef void (OnConnectedCallback)();
typedef void (OnDisconnectedCallback)(unsigned int);

class ID3D11Device;

HOLOREMOTINGPLUGIN_API int Initialise(ID3D11Device *d3dDevice, OnConnectedCallback *ccb, OnDisconnectedCallback *dcb);
HOLOREMOTINGPLUGIN_API int Connect(const wchar_t *ipAddress);
