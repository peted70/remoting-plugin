 # Remoting Plugin
Just a test to illustrate calling WinRT APIs inside a self-contained DLL loaded into a plain win32 desktop app

# Steps to create
1. Create the DLL project
  1. Create a DLL using the Desktop Project wizard in VS 2017 (new)
  1. Add WinRT support to the DLL:
	  1. Add /ZW flag to support (c++/cx) - optional - we could use wrl or raw COM
	  1. Disable the /Gm flag as minimal build support is not compatible with previous flag
	  1. Add the following as additional using directories
		  * C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\vcpackages;
		  * C:\Program Files (x86)\Windows Kits\10\UnionMetadata;
		  * C:\Program Files (x86)\Windows Kits\10\References\Windows.Foundation.UniversalApiContract\1.0.0.0;
		  * C:\Program Files (x86)\Windows Kits\10\References\Windows.Foundation.FoundationContract\1.0.0.0;
	  1. Last, pick the target Windows 10 SDK version
    
1. Add the Holographic Remoting Nuget package
1. Consume the DLL from a win32 desktop app:
  1. Create Win32 Desktop app using the Desktop Project wizard
	  1. #include the DLL api header
	  1. Link against the .lib file produced when the DLL is built
	  1. Make sure the DLL is on a path searched by runtime DLL loading subsystem

1. Add DX to the win32 desktop app:
  1. Add the following code:
     ```
     	#include <wrl.h>
	#include <d3d11_4.h>
	
	using namespace Microsoft::WRL;
     ```
  1. Link against d3d11.lib
  1. Add the following code to create a D3D11Device:
    ```
    	ComPtr<ID3D11Device> device;
	ComPtr<ID3D11DeviceContext> context;
	
	UINT creationFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT | D3D11_CREATE_DEVICE_DEBUG;
	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0
	};
	
	D3D_FEATURE_LEVEL d3dFeatureLevel;
	
	const HRESULT hr = D3D11CreateDevice(
			nullptr,        // Either nullptr, or the primary adapter determined by Windows Holographic.
			D3D_DRIVER_TYPE_HARDWARE,   // Create a device using the hardware graphics driver.
			0,                          // Should be 0 unless the driver is D3D_DRIVER_TYPE_SOFTWARE.
			creationFlags,              // Set debug and Direct2D compatibility flags.
			featureLevels,              // List of feature levels this app can support.
			ARRAYSIZE(featureLevels),   // Size of the list above.
			D3D11_SDK_VERSION,          // Always set this to D3D11_SDK_VERSION for Windows Store apps.
			&device,                    // Returns the Direct3D device created.
			&d3dFeatureLevel,         // Returns feature level of device created.
			&context                    // Returns the device immediate context.
	);
    ```

Idea is that the D3DDevice can be passed across the DLL API and used to initialise a HolographicSpace created there.


