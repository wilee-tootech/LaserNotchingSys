
#ifndef _VECTOR
#define _VECTOR
#include "DPoint.h"


//************** B-SPLINE ****************************/
#define	B0(t)		(t*t)
#define	B1(t)		(2*t*(1-t))
#define	B2(t)		((1-t)*(1-t))

#define	C0(t)		(t*t*t)
#define	C1(t)		(3*t*t*(1-t))
#define	C2(t)		(3*t*(1-t)*(1-t))
#define	C3(t)		((1-t)*(1-t)*(1-t))

#define	D0(t)		(-t + 2*t*t - t*t*t)/2
#define	D1(t)		(2- 5*t*t + 3*t*t*t)/2
#define	D2(t)		(t+ 4*t*t - 3*t*t*t)/2
#define	D3(t)		(-t*t + t*t*t)/2


struct Vector{
	CDPoint	d;
	short 	t;
	bool   k;//KOEM PATTERN FLAG
};



typedef struct sCPoint
{
	double x;
	double y;
}	C_POINT;



struct st_Tap_BaseInfo{
	BOOL bTwoTap;
	double dBaseDist;
};



struct st_Tap_PositionData{
	BOOL bReverse;
	double dPosition;
	double dOffset;
	double dGap;
	
	
	void clear()
	{
		bReverse = dPosition = dGap = dOffset = 0;
	}
};


struct st_Tap_Monitoring_PositionData{
	/*Input*/
	BOOL bSigIn1_HighLowFlag;
	BOOL bSigIn2_HighLowFlag;
	BOOL bSigIn3_HighLowFlag;
	BOOL bSigIn4_HighLowFlag;
	BOOL bSigIn5_HighLowFlag;
	BOOL bSigIn6_HighLowFlag;
	BOOL bSigIn7_HighLowFlag;
	BOOL bSigIn8_HighLowFlag;
	BOOL bSigIn9_HighLowFlag;
	BOOL bSigIn10_HighLowFlag;
	BOOL bSigIn11_HighLowFlag;
	BOOL bSigIn12_HighLowFlag;
	BOOL bSigIn13_HighLowFlag;
	BOOL bSigIn14_HighLowFlag;
	BOOL bSigIn15_HighLowFlag;
	BOOL bSigIn16_HighLowFlag;

	/*OutPut*/
	BOOL bSigOut1_HighLowFlag;
	BOOL bSigOut2_HighLowFlag;
	BOOL bSigOut3_HighLowFlag;
	BOOL bSigOut4_HighLowFlag;


	double dEncoderPosition;

	void clear()
	{
		bSigIn1_HighLowFlag = bSigIn2_HighLowFlag = bSigIn3_HighLowFlag = bSigIn4_HighLowFlag= bSigOut1_HighLowFlag = bSigOut2_HighLowFlag = bSigOut3_HighLowFlag = bSigOut4_HighLowFlag=false;
		dEncoderPosition = 0.0;
		bSigIn4_HighLowFlag = false;
		bSigIn5_HighLowFlag = false;
		bSigIn6_HighLowFlag = false;
		bSigIn7_HighLowFlag = false;
		bSigIn8_HighLowFlag = false;
		bSigIn9_HighLowFlag = false;
		bSigIn10_HighLowFlag = false;
		bSigIn11_HighLowFlag = false;
		bSigIn12_HighLowFlag = false;
		bSigIn13_HighLowFlag = false;
		bSigIn14_HighLowFlag = false;
		bSigIn15_HighLowFlag = false;
		bSigIn16_HighLowFlag = false;
	}
};


#endif
