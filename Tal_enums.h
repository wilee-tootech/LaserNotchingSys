#if !defined(_TAL_ENUMS_H_)
#define _TAL_ENUMS_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


typedef enum TALCOMMENTALIGNMENTENUM
{
	bcLeftAlign   = 0,
	bcCenterAlign = 1,
	bcRightAlign  = 2
} TALCOMMENTALIGNMENTENUM;

typedef enum TALSYMBOLOGYENUM
{
	bcCode39 = 0,
	bcCode_39_Full_ASCII = 1,
	bcCode_39HIBC = 2,
	bcCodaBar  = 3,
	bcCode93  = 4,
	bcCode128 = 5,
	bcUCC_EAN_128 = 6,
	bcInterleaved_2of5 = 7,
	bcPostNET = 8,
	bcUPC_A = 9,
	bcUPC_E = 10,
	bcEAN_JAN_8 = 11,
	bcEAN_JAN_13 = 12,
	bcBookLan = 13,
	bcMSI_Plessey = 14,
	bcPDF417 = 15,
	bcAztec = 16,
	bcDataMatrix = 17,
	bcMaxiCode = 18
} TALSYMBOLOGYENUM;

typedef enum TALROTATEVALSENUM
{
	bcZeroDegrees = 0,
	bcClockwise_90 = 1,
	bcClockwise_180 = 2,
	bcClockwise_270 = 3
} TALROTATEVALSENUM;


#endif