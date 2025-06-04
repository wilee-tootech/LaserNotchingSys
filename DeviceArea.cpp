// DeviceArea.cpp: implementation of the CDeviceArea class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DeviceArea.h"
#include "PointerContainer.h"





#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#include "Device.h"

#include "PointTranslator.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDeviceArea::CDeviceArea()
{

}

CDeviceArea::~CDeviceArea()
{

}

//테스트 완료. 10.30
CRect CDeviceArea::GetDeviceArea()
{
	CDeviceManager *pDeviceMng = CDeviceManager::Instance();
	double dw, dh;
	CRect rtArea;
	CRect rtDesArea;
	//CDisplay *pDisp = CPointerContainer::GetDisplay();
	 CPoint(23,23);//테스트중 

	
	
	return rtDesArea;
		
}