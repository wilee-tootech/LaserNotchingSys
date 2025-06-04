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
	/* Bin ������ */
	pMarking->SetBinData();
	/* Para ������ */
	pMarking->SetParameterData();
	/* Dsp �ʱ�ȭ ��Ű�� */
	pMarking->Initialize();
	/* Device ���� ���� Data �ҷ����� */
	pDeviceManager->Calculate();
	

	/* �켱 Ĩ�ϳ��� ������ �ҷ����� �׽�Ʈ */
	int iPos=0;
	pObject = pMKObjectApproacher->GetFirst(iPos);
	
	if(pObject == NULL)
		return R_DEFAULT;
	
//	int iIndex = 0;
	while(pObject != NULL)
	{
		/* �۾� */
		if( pObject->GetMarkState() == TRUE) // Ŀ�� �ϴ� ������Ʈ �̸� 
		{
			if (R_INVALID_AREA == pObject->SendObjectData(pMarking, ptDevicePos))
				return R_INVALID_AREA;
		}
		pObject = pMKObjectApproacher->GetNext(iPos);
	//	SetDelayTime(50);
	}
	/* ���� Data Down ��Ű��� ���� Object�� �˾Ƽ� �� */
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
