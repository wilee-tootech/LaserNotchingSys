// DataTransmitter.h: interface for the CDataTransmitter class.
//
// * ���� ���� ����� �ָ� �����ؼ� �� ���� �����Ѵ�. 
//   ������ CDsp : CDsp *m_pDsp; m_pDsp->ManualMarking()������...
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
	void SetOffsetData(int iMasterX, int iMasterY, int iSlaveX=0, int iSlaveY=0); // Offset�� ������ �ִ� ���� ����?
	void SetCalData(); // Cal Data�� ���� // Cal Data�� ������ �ִ� ���� �����ΰ�.
	void SetImageParameter(); // Object�� Para�� �����ؾ��� �Ѥ�;; // ���� ���� ��� �̹����� �׻� ���� �Ķ���͸� ���
	                          // ������ �ʿ伺 ��
	void SetMarkingData(); // Data�� ������ �ִ� �𿡰� ���� �޾ƿ� �Ǵ� ��Ŵ
	void SetMarkStatus(int iMarkStatus); // ��ȣ ������ ���� ���� setting�� 
	UINT StartManualMarking();
	UINT StartAutoMarking();
	UINT StopAutoMarking();
	UINT SetParameterData(); // Para�� ����
	UINT SetBinData(); // Bin�� ����
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
