// HoloRemotingPlugin.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "HoloRemotingPlugin.h"
#include <d3d11_4.h>

#include <HolographicStreamerHelpers.h>
#include <string>

using namespace Microsoft::Holographic;
using namespace std;

void OnOnSendFrame(const Microsoft::WRL::ComPtr<ID3D11Texture2D> &spTexture, 
				   const Microsoft::Holographic::FrameMetadata &metadata);

const short Port = 8001;

const unsigned StreamerWidth = 1280;
const unsigned StreamerHeight = 720;

HolographicStreamerHelpers^ _streamerHelper;

// This is an example of an exported function.
HOLOREMOTINGPLUGIN_API int Initialise(ID3D11Device *d3dDevice, OnConnectedCallback *ccb, OnDisconnectedCallback *dcb)
{
	Windows::Foundation::Initialize();

	_streamerHelper = ref new HolographicStreamerHelpers();

	// We will use the HolographicSpace and associate that with the D3DDevice 
	_streamerHelper->CreateStreamer(d3dDevice);
	_streamerHelper->SetVideoFrameSize(StreamerWidth, StreamerHeight);

	_streamerHelper->OnConnected += ref new Microsoft::Holographic::ConnectedEvent(ccb);
	_streamerHelper->OnDisconnected += ref new Microsoft::Holographic::DisconnectedEvent(
		[dcb](HolographicStreamerConnectionFailureReason reason)
		{
			dcb((unsigned int)reason);
		});
	_streamerHelper->OnSendFrame += ref new Microsoft::Holographic::SendFrameEvent(&OnOnSendFrame);

    return 1;
}

HOLOREMOTINGPLUGIN_API int Connect(const wchar_t *ipAddress)
{
	if (_streamerHelper == nullptr)
		return -1;
	try
	{
		_streamerHelper->Connect(ipAddress, Port);
	}
	catch (...)
	{
		return -1;
	}
	return 1;
}

void OnOnSendFrame(const Microsoft::WRL::ComPtr<ID3D11Texture2D> &spTexture, const Microsoft::Holographic::FrameMetadata &metadata)
{
}
