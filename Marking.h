// Marking.h: interface for the CMarking class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MARKING_H__B8EB0042_0BFF_4A27_B28C_33469B1E3968__INCLUDED_)
#define AFX_MARKING_H__B8EB0042_0BFF_4A27_B28C_33469B1E3968__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <AFXTEMPL.H>
#include "Vector.h"

class CMarking  
{
public:
	CMarking();
	virtual ~CMarking();

	virtual UINT SendVectorDataToDevice(int iObjNumber, double *pVectorData, int iNumberOfVector, int iParameterIndex, int iBinIndex)=0;
	virtual UINT SendPixelDataToDevice(int iObjNumber, double *pVectorData, int iNumberOfVector, int iParameterIndex, int iBinIndex)=0;
	virtual UINT DeviceChange()=0;
	virtual UINT GetMarkStatus()=0;
	virtual UINT StopAutoMarking()=0;
	virtual UINT SetParameterData()=0;
	virtual UINT SetBinData()=0;
	virtual UINT StartAutoMarking()=0;
	virtual UINT StartManualMarking()=0;
	virtual CString GetVersion()=0;
	virtual void SetSpeed(int iSpeed)=0;
	virtual void SetMarkFlag(int iMarkFlag);
	virtual int	 GetMarkFlag();
	virtual void InitialTime(); // Time Check를 위해 time 변수를 0으로 초기화만 시키면 됨. // 이미 정해진 행동
	virtual int	 GetTime(); // Time Check를 위해 변화된 time 변수를 가져옴. // 현재 시점에서 Initial한 시점을 빼면 자동 추출
	virtual void Initialize()=0;
	virtual void SetOffsetData(int iMasterX, int iMasterY, int iSlaveX=0, int iSlaveY=0)=0; // Offset을 가지고 있는 놈은 누구?
	virtual void SetChipNumber(int iNumber)=0;
	virtual void SetMasterChipOffset(Vector *ltMaster, int iNumberOfVector)=0;
	virtual void SetSlaveChipOffset(Vector *ltSlave, int iNumberOfVector)=0;
	static CMarking *GetInstance();

protected:
	SYSTEMTIME m_iMarkingTime;
	int  m_iMarkFlag; /* PAUSE / AUTO / MANUAL */

private:
	static CMarking *m_pMarking; // 유일한 instance
};

#endif // !defined(AFX_MARKING_H__B8EB0042_0BFF_4A27_B28C_33469B1E3968__INCLUDED_)
