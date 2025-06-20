//***************************************************************************** 
// 
// Microsoft Windows Media 
// Copyright (C) Microsoft Corporation. All rights reserved. 
//
// FileName:            wmsdefs.h
//
// Abstract:
//
//*****************************************************************************

#pragma once

#include "WMSContextNames.h"
#include "WMSCatID.h"

// WMSServer Defines
#define WMS_VER_MAJOR   9
#define WMS_VER_MINOR   0

// GUIDS needed in both core and server
EXTERN_GUID( LIBID_WMSServerLib, 0xD71E02C2,0x41EF,0x11D2,0xBF,0x23,0x00,0x80,0x5F,0xBE,0x84,0xA6  );
EXTERN_GUID( CLSID_WMSServer, 0x845FB959,0x4279,0x11D2,0xBF,0x23,0x00,0x80,0x5F,0xBE,0x84,0xA6  );
EXTERN_GUID( CLSID_WMSNamedValues, 0x072AC7C7,0xBC7D,0x11d2,0xB5,0x49,0x00,0x60,0x97,0xD2,0xE4,0x6A  );
EXTERN_GUID( DIID_DWMSNamedValuesEvents, 0xD75C4175,0xBC7B,0x11d2,0xB5,0x49,0x00,0x60,0x97,0xD2,0xE4,0x6A  );
EXTERN_GUID( IID_IWMSNamedValue , 0x18812741,0x4BEC,0x11D2,0xBF,0x25,0x00,0x80,0x5F,0xBE,0x84,0xA6  );
EXTERN_GUID( IID_IWMSNamedValues , 0x18812743,0x4BEC,0x11D2,0xBF,0x25,0x00,0x80,0x5F,0xBE,0x84,0xA6  );
EXTERN_GUID( IID_IWMSDiagnosticEvents , 0x5AC19D61, 0x6057, 0x4431, 0xBE, 0x7E, 0x21, 0x53, 0xFD, 0xF9, 0x13, 0x97 );
EXTERN_GUID( IID_IWMSDiagnosticEvent , 0x5AC19D62, 0x6057, 0x4431, 0xBE, 0x7E, 0x21, 0x53, 0xFD, 0xF9, 0x13, 0x97 );
EXTERN_GUID( IID_IWMSFileDescriptions , 0x4124B8B2, 0xBCE4, 0x41C8, 0xB4, 0x9A, 0xDA, 0x98, 0xC1, 0x40, 0x1D, 0x3B );
EXTERN_GUID( IID_IWMSFileDescription , 0x4124B8B3, 0xBCE4, 0x41C8, 0xB4, 0x9A, 0xDA, 0x98, 0xC1, 0x40, 0x1D, 0x3B );
EXTERN_GUID( IID_IWMSPlugins , 0x517758ec,0x603c,0x4b98,0x82,0xC1,0x4B,0x2F,0xA7,0x78,0x71,0x66  );
EXTERN_GUID( IID_IWMSCacheProxyPlugin , 0x517758eb,0x603c,0x4b98,0x82,0xC1,0x4B,0x2F,0xA7,0x78,0x71,0x66  );
EXTERN_GUID( IID_IWMSCacheProxyPlugins , 0x517758ea,0x603c,0x4b98,0x82,0xC1,0x4B,0x2F,0xA7,0x78,0x71,0x66  );
EXTERN_GUID( IID_IWMSCacheItem, 0x517758e8,0x603c,0x4b98,0x82,0xC1,0x4B,0x2F,0xA7,0x78,0x71,0x66  );
EXTERN_GUID( IID_IWMSCacheItems, 0x517758e9,0x603c,0x4b98,0x82,0xC1,0x4B,0x2F,0xA7,0x78,0x71,0x66  );
EXTERN_GUID( IID_IWMSOutgoingDistributionConnection , 0x60f2ee54,0xdcaa,0x4cb6,0xa6,0xd2,0x12,0xbc,0x23,0xac,0x9d,0xf0  );
EXTERN_GUID( IID_IWMSOutgoingDistributionConnections , 0x60f2ee53,0xdcaa,0x4cb6,0xa6,0xd2,0x12,0xbc,0x23,0xac,0x9d,0xf0  );
EXTERN_GUID( IID_IWMSPlayer , 0x18812736,0x4BEC,0x11D2,0xBF,0x25,0x00,0x80,0x5F,0xBE,0x84,0xA6  );
EXTERN_GUID( IID_IWMSPlayers , 0x18812738,0x4BEC,0x11D2,0xBF,0x25,0x00,0x80,0x5F,0xBE,0x84,0xA6  );
EXTERN_GUID( IID_INSInstalledPlugin , 0x40C238AA,0x701A,0x11D2,0xBF,0x2F,0x00,0x80,0x5F,0xBE,0x84,0xA6  );
EXTERN_GUID( IID_IWMSPublishingPoint , 0x1881273F,0x4BEC,0x11D2,0xBF,0x25,0x00,0x80,0x5F,0xBE,0x84,0xA6  );
EXTERN_GUID( IID_IWMSPublishingPoint2 , 0x770e846b,0xde39,0x4d72,0xA2,0x9F,0x1B,0x63,0x1C,0xA6,0x60,0xB4  );
EXTERN_GUID( IID_IWMSOnDemandPublishingPoint , 0x6ca388b3,0xeaee,0x492f,0xa8,0xd6,0x87,0x58,0xeF,0xc7,0x2d,0x76  );
EXTERN_GUID(IID_IWMSOnDemandPublishingPoint2 , 0x3abbf960,0x54e5,0x40be,0x86,0x77,0xC1,0x75,0x8B,0x12,0x39,0xEB  );
EXTERN_GUID( IID_IWMSBroadcastPublishingPoint , 0x6ca388b4,0xeaee,0x492f,0xa8,0xd6,0x87,0x58,0xeF,0xc7,0x2d,0x76  );
EXTERN_GUID( IID_IWMSBroadcastPublishingPoint2 , 0xc94e9af0,0xf12d,0x4bff,0xB0,0x1A,0x1C,0xE6,0xD7,0xF5,0xD3,0x03  );
EXTERN_GUID( IID_IWMSPublishingPoints , 0x1881274D,0x4BEC,0x11D2,0xBF,0x25,0x00,0x80,0x5F,0xBE,0x84,0xA6  );
EXTERN_GUID( IID_IWMSServer , 0x845FB958,0x4279,0x11D2,0xBF,0x23,0x00,0x80,0x5F,0xBE,0x84,0xA6  );
EXTERN_GUID( IID_IWMSServerCurrentCounters, 0x18fa53cd, 0x8eb9, 0x4b5f, 0xb7, 0x50, 0x65, 0x9d, 0x9b, 0x96, 0xdb, 0x9f );
EXTERN_GUID( IID_IWMSServerPeakCounters, 0x66f2d385, 0x7081, 0x40b9, 0x86, 0x3c, 0xaf, 0xa4, 0xe5, 0x61, 0x2c, 0xd3 );
EXTERN_GUID( IID_IWMSServerLimits, 0xd06ccfbb, 0x994d, 0x45f8, 0x88, 0x6e, 0x81, 0xe9, 0xb7, 0xfa, 0xed, 0xf1 );
EXTERN_GUID( IID_IWMSServerTotalCounters, 0xDAA2A1BB, 0xBC91, 0x438d, 0xBF, 0x33, 0xBD, 0xE1, 0x1D, 0x23, 0x48, 0xD5 );
EXTERN_GUID( IID_IWMSPublishingPointCurrentCounters, 0x638dfa30, 0x1054, 0x48bd, 0xb0, 0x30, 0xc3, 0xda, 0x1f, 0xc1, 0x81, 0x54 );
EXTERN_GUID( IID_IWMSPublishingPointPeakCounters, 0x43b20cc5, 0xca36, 0x4e7b, 0xad, 0xaf, 0xc9, 0xc6, 0xd, 0x0, 0xbb, 0xe );
EXTERN_GUID( IID_IWMSPublishingPointLimits, 0x6cd5bc19, 0x35fd, 0x4501, 0xa9, 0x53, 0xfe, 0xb5, 0x7a, 0xae, 0x9c, 0x13 );
EXTERN_GUID( IID_IWMSPublishingPointTotalCounters, 0x240d0c87, 0x309a, 0x4126, 0xbf, 0x14, 0xb5, 0x2a, 0x62, 0x2e, 0x95, 0xa9 );
EXTERN_GUID( IID_IWMSPlaylist, 0xee1f2e7, 0x48ef, 0x11d2, 0x9e, 0xff, 0x0, 0x60, 0x97, 0xd2, 0xd7, 0xcf );
EXTERN_GUID( IID_IWMSPlugin , 0x517758ed,0x603c,0x4b98,0x82,0xC1,0x4B,0x2F,0xA7,0x78,0x71,0x66  );
EXTERN_GUID( IID_IWMSActiveStream , 0x165FC383,0xB494,0x4465,0xAD,0x08,0x4A,0x73,0xCE,0xDF,0x87,0x91  );
EXTERN_GUID( IID_IWMSActiveStreams , 0x5F248EA2,0xC018,0x466c,0x9A,0xD7,0x20,0x86,0xCF,0xB9,0xA5,0xD3  );
EXTERN_GUID( IID_IWMSActiveMedia , 0x9D07EE1C,0x798F,0x4a28,0x85,0xFA,0x23,0x06,0x64,0x65,0x0B,0x7C  );
EXTERN_GUID( IID_IWMSCertificate, 0x901447DA, 0x8C5D, 0x48b7, 0xA5, 0xF9, 0xD2, 0x38, 0x09, 0x32, 0x2B, 0xC0  );
EXTERN_GUID( IID_IWMSCertificates, 0x7B8585BF, 0x9FB8, 0x4132, 0xAC, 0xD3, 0x3E, 0x61, 0xCA, 0x4C, 0x30, 0xDB  );
EXTERN_GUID( IID_IWMSAvailableIPAddresses , 0x3FC1A813,0x759F,0x4441,0xBA,0x48,0x21,0x88,0x9E,0xC8,0xAC,0x20  );
EXTERN_GUID( IID_IWMSRootDirectories , 0xDFC750A9,0xF846,0x48BE,0x87,0xAE,0x79,0xF8,0x51,0xC9,0xCD,0x92  );
EXTERN_GUID( IID_IWMSAnnouncementStreamFormats , 0x55DDB8E9,0x05A3,0x4666,0x9E,0x20,0x55,0x0F,0x94,0x58,0x1B,0x06  );


