#pragma once
#include "UPNPServiceBase.h"

//InstanceID ui4

class UPNPServiceAVTransport :
	public UPNPServiceBase
{
public:
	UPNPServiceAVTransport();
	~UPNPServiceAVTransport();
public:
	//GetCurrentTransportActions
	//GetDeviceCapabilities
	//GetMediaInfo
	bool GetMediaInfo(UPNP_UI4 InstanceID, std::string &NrTracks);
	//, , TrackMetaData, TrackURI, RelTime, AbsTime, RelCount, AbsCount
	bool GetPositionInfo(UPNP_UI4 InstanceID, UPNPPositionInfo &posInfo);
	//GetTransportInfo
	//GetTransportSettings
	//Next
	
	bool Pause(UPNP_UI4 InstanceID);
	
	//Speed 1
	bool Play(UPNP_UI4 InstanceID, const std::string &Speed);
	
	//Previous 

	//Unit ABS_TIME REL_TIME ABS_COUNT REL_COUNT TRACK_NR CHANNEL_FREQ TAPE-INDEX FRAME
	//Target 00£º02£º21
	bool Seek(UPNP_UI4 InstanceID, const std::string &Unit, const std::string &Target);
	
	bool SetAVTransportURI(UPNP_UI4 InstanceID, const std::string &CurrentURI, const std::string &CurrentURIMetaData);
	
	//SetPlayMode
	
	bool Stop(UPNP_UI4 InstanceID);
};

