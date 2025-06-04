 // DataBuilder.cpp: implementation of the CDataBuilder class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "BeamEditor6.h"
#include "DataBuilder.h"
#include "Marking.h"
#include "MKObjectApproacher.h"
#include "PointerContainer.h"
#include "return.h"
#include "Device.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDataBuilder::CDataBuilder()
{

}

CDataBuilder::~CDataBuilder()
{

}

CDataBuilder* CDataBuilder::m_pDataBuilder = 0;
CDataBuilder *CDataBuilder::GetInstance()
{
	if (m_pDataBuilder == 0) {
		m_pDataBuilder = new CDataBuilder;
	}
	return m_pDataBuilder;
}

UINT CDataBuilder::BuildTotalData(CMarking *pMarking)
{
	CMKObjectApproacher *pMKObjectApproacher = CPointerContainer::GetApproacher();
	CMKObject *pObject;
	CDeviceManager *pDeviceManager = pDeviceManager->Instance();
	CPoint ptDevicePos(0, 0);

	pMarking->Initialize();
	/* Bin 내리기 */
	pMarking->SetBinData();
	/* Para 내리기 */
	pMarking->SetParameterData();
	/* Dsp 초기화 시키기 */
	pMarking->Initialize();
	/* Device 수에 따라 Data 불러오기 */
	pDeviceManager->Calculate();
	

	/* 우선 칩하나의 데이터 불러오기 테스트 */
	int iPos=0;
	pObject = pMKObjectApproacher->GetFirst(iPos);
	
	if(pObject == NULL)
		return R_DEFAULT;
	
//	int iIndex = 0;
	while(pObject != NULL)
	{
		/* 작업 */
		if( pObject->GetMarkState() == TRUE) // 커팅 하는 오브젝트 이면 
		{
			if (R_INVALID_AREA == pObject->SendObjectData(pMarking, ptDevicePos))
				return R_INVALID_AREA;
		}
		pObject = pMKObjectApproacher->GetNext(iPos);
	//	SetDelayTime(50);
	}
	/* 실제 Data Down 시키기는 각자 Object가 알아서 함 */
	return FALSE;
}

void CDataBuilder::SetOffset(int iX, int iY)
{

}

void CDataBuilder::SetAngle(double dAngle)
{
	
}

void CDataBuilder::SetDelayTime(unsigned int iSecond)
{
	DWORD dwTick = GetTickCount();
	MSG msg;

	while(GetTickCount() - dwTick < iSecond)
	{					
		if(PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
}
