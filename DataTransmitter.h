// DataTransmitter.h: interface for the CDataTransmitter class.
//
// * 실제 일을 담당할 애를 지정해서 그 일을 위임한다. 
//   지금은 CDsp : CDsp *m_pDsp; m_pDsp->ManualMarking()식으로...
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DATATRANSMITTER_H__D803CAE1_1BF0_40A3_8EED_88539C2834D5__INCLUDED_)
#define AFX_DATATRANSMITTER_H__D803CAE1_1BF0_40A3_8EED_88539C2834D5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Marking.h"
#include "Dsp.h"
/*

#if	_RTC3_
#include ".\Include\Rtc3\RTC3impl.h"
#endif

#if	_RTC4_
#include ".\Include\Rtc4\RTC4impl.h"
#endif

#if	_RTC4eth_
#include ".\Include\Rtc4eth\RTC4ethexpl.h"
#include ".\Include\Rtc4eth\stdint.h"
#endif

#if _RTCSCANALONE_
#include ".\Include\RtcScanAlone\SCANalone4impl.h"
//#include ".\Include\RtcScanAlone\SCANalone4expl.h"
#endif


#if	_RTC6_
#include ".\Include\Rtc5\RTC5impl.h"
#endif
*/

class CDataTransmitter : public CMarking  
{
public:
	CDataTransmitter();
	virtual ~CDataTransmitter();

	void SetChipNumber(int iNumber);
//	void SetMasterChipOffset(CList<Vector, Vector> *ltMaster);
//	void SetSlaveChipOffset(CList<Vector, Vector> *ltSlave);
	void SetMasterChipOffset(Vector *ltMaster, int iNumberOfVector);
	void SetSlaveChipOffset(Vector *ltSlave, int iNumberOfVector);
	void SetOffsetData(int iMasterX, int iMasterY, int iSlaveX=0, int iSlaveY=0); // Offset을 가지고 있는 놈은 누구?
	void SetCalData(); // Cal Data에 접근 // Cal Data를 가지고 있는 놈은 누구인가.
	void SetImageParameter(); // Object의 Para에 접근해야함 ㅡㅡ;; // 지금 현재 모든 이미지는 항상 같은 파라미터를 사용
	                          // 변경할 필요성 有
	void SetMarkingData(); // Data를 가지고 있는 놈에게 접근 받아옴 또는 시킴
	void SetMarkStatus(int iMarkStatus); // 신호 받으면 현재 값을 setting만 
	UINT StartManualMarking();
	UINT StartAutoMarking();
	UINT StopAutoMarking();
	UINT SetParameterData(); // Para에 접근
	UINT SetBinData(); // Bin에 접근
	UINT DeviceChange();
	UINT SendVectorDataToDevice(int iObjNumber, double *pVectorData, int iNumberOfVector, int iParameterIndex, int iBinIndex);
	UINT SendPixelDataToDevice(int iObjNumber, double *pVectorData, int iNumberOfVector, int iParameterIndex, int iBinIndex);
	UINT GetMarkStatus();
	CString GetVersion();
	void SetSpeed(int iSpeed);
	void Initialize();

private:
	CDsp *m_pDsp; 
};

#endif // !defined(AFX_DATATRANSMITTER_H__D803CAE1_1BF0_40A3_8EED_88539C2834D5__INCLUDED_)
