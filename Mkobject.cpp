



#include "StdAfx.h"


#include "Return.h"
#include "MKObject.h"
#include "MKFileWriter.h"
#include "MKFileReader.h"


#include "ParameterColor.h"
#include "Device.h"
#include "TransUnit.h"
#include "MathUtil.h"







#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


CMKObject::CMKObject()
{

	m_pPainter = NULL; // 널로 설정 놨다.
	m_pDlg = NULL; // 둘다.
	  // 때문에 다른곳에서는 NULL 인지 아닌지만 확인하고
	// 저 멤버 변수를 셋팅하는 함수에서는
	// 새로 세팅할 포인터가 유효한 메모리 번지를 가르키고 있느지만 확인하면 된다. 

	m_dX = 0;
	m_dY = 0;
	m_dMagX = 1;
	m_dMagY = 1;
	m_uiParaIndex = 1;
	m_uiBinIndex = 1;
	m_dAngle = 0;
	m_bMarkState = TRUE;
	m_bSerialFlag = FALSE;
	m_bSelected = FALSE;
//	m_pSerialData = NULL;
	m_pSender = NULL;
	m_bLock = FALSE;

	m_ptStartPoint = (0, 0);
	m_ptEndPoint = (0, 0);
	m_ptMovingCenterPoint = (0, 0);
	m_dCreateZoom = 1;

	m_bPreSelected = FALSE;


	CDeviceManager *pDeviceManager;
	pDeviceManager = CDeviceManager::Instance();
	double m_dChipWidth=0,m_dChipHeight=0;
	m_dChipHeight = pDeviceManager->GetDevHeight();
	m_dChipWidth = pDeviceManager->GetDevWidth(); 

	
	double dFieldSize=0,dMmSize=0;
	CTransUnit	*pTransUnit = pTransUnit->GetInstance(dFieldSize, dMmSize);

	m_dX = m_dX/* - (m_dChipWidth/2)*/;
	m_dY = m_dY/*- (m_dChipHeight/2)*/;

	// 2011.09.29 syhun START - Hatching 관련.
	m_nHatchType = 0;
	m_dHatchDistance = 0;
	m_dHatchOffset = 0;
	m_dHatchAngle = 0;
	m_bHatchOutLine = 0;
	
	// syhun END.

	m_bIsGroup = FALSE;

	m_dwVectorLength = 0;
	m_hpgl_data = NULL;

	m_bIsDotMark = FALSE;
}

CMKObject::~CMKObject()
{
	Release();
}

void CMKObject::SetDialog(CMKDialog *pDlg)
{
	ASSERT( FALSE == IsBadReadPtr(pDlg, sizeof( CMKDialog ) ) );
	m_pDlg = pDlg;
}

CMKDialog *CMKObject::GetDialog()
{

	return m_pDlg;

}


UINT CMKObject::Draw(CDC *pDC, CDRect rtDrawRect)
{
	CDSize size; 
	size.cx = rtDrawRect.Width();
	size.cy = rtDrawRect.Height();
	CDPoint ptPosition(rtDrawRect.left, rtDrawRect.bottom); 
	
	return Draw(pDC,  ptPosition, size ); //rtDrawRect영역에 그린다
}

UINT CMKObject::Draw(CDC *pDC, CDRect rtDrawRect, BOOL bIsVector)
{
	CDSize size;
	size.cx = rtDrawRect.Width();
	size.cy = rtDrawRect.Height();
	CDPoint ptPosition(rtDrawRect.left, rtDrawRect.bottom);
	
	return Draw(pDC,  ptPosition, size, bIsVector);
}

UINT CMKObject::Draw(CDC *pDC, CDPoint ptPosition, CDSize size, BOOL bIsVector)
{	
	return Draw(pDC,  ptPosition, size, bIsVector);
}


void CMKObject::SetMagX(double dMagX)
{
//	if( m_bLock ==FALSE)
	if( m_bLock ==FALSE)
	m_dMagX = dMagX;
}

double CMKObject::GetMagX()
{
	return m_dMagX;
}

void CMKObject::SetPosX(double dPosX)
{
	if( m_bLock ==FALSE)
	m_dX = dPosX;
	
}

void CMKObject::SetPosX(double dPosX, BOOL bIsDrawObject)
{
	CDeviceManager *pDeviceManager;
	pDeviceManager = CDeviceManager::Instance();
	double m_dChipWidth=0,m_dChipHeight=0;
	m_dChipHeight = pDeviceManager->GetDevHeight();
	m_dChipWidth = pDeviceManager->GetDevWidth(); 

	double dFieldSize=0,dMmSize=0;
	CTransUnit	*pTransUnit = pTransUnit->GetInstance(dFieldSize, dMmSize);
    
	/*pTransUnit->SetValue(dLeft,FIELD);
	dLeft = pTransUnit->GetField();
	dLeft = dLeft - (m_dChipWidth / 2);
	
	
	dTop = dTop + dHeight;
	pTransUnit->SetValue(dTop,uiUnit);
	dTop = pTransUnit->GetField();
	dTop = dTop - (m_dChipHeight / 2);
	*/


	
	SetPosX(dPosX);
}

double CMKObject::GetPosX()
{
	
	return m_dX;
}

void CMKObject::SetPosY(double dPosY)
{
	if( m_bLock ==FALSE)
	m_dY = dPosY;
}

void CMKObject::SetPosY(double dPosY, BOOL bIsDrawObject)
{
	SetPosY(dPosY);
}

double CMKObject::GetPosY()
{
	return m_dY;	
}

double CMKObject::GetPosX(BOOL bIsDrawObject)
{
	return GetPosX();
}

double CMKObject::GetPosY(BOOL bIsDrawObject)
{
	return GetPosY();
}

void CMKObject::SetWidth(double iWidth)
{
	if( m_bLock ==FALSE)
    
	m_dWidth = iWidth;
	
}

double CMKObject::GetWidth()
{
	
	return m_dWidth;

}

CDRect CMKObject::Rect()
{   //자신이 차지하는 영역을 리턴한다. Field단위 
	double dX, dY, dWidth, dHeight;
	CDRect rtObject;
	
	dX = this->GetPosX();
	dY = this->GetPosY();

	CDeviceManager *pDeviceManager;
	pDeviceManager = CDeviceManager::Instance();
	double m_dChipWidth=0,m_dChipHeight=0;
	m_dChipHeight = pDeviceManager->GetDevHeight();
	m_dChipWidth = pDeviceManager->GetDevWidth(); 


//	if (m_dAngle == 0)
//	{
		dWidth     = (  this->GetWidth()  ) * (  this->GetMagX()  );
		dHeight    = (  this->GetHeight() ) * (  this->GetMagY()  );
//	}
//	else
//	{
//		dWidth     = (  this->GetWidth()  );
//		dHeight    = (  this->GetHeight() );
//	}
	

//	rtObject.SetRect( dX, dY, (dX+dWidth), (dY+dHeight));
	if (dWidth == 0) {
		dWidth+=50;
	}

	if (dHeight == 0) {
		dHeight+=50;
	}

	
	rtObject.left = dX;
	rtObject.top = dY;
	rtObject.right = dX+dWidth;
	rtObject.bottom = dY+dHeight;
	

	return rtObject;
}

void CMKObject::SetHeight(double iHeight)
{
	if( m_bLock ==FALSE)
	m_dHeight = iHeight;
}

double CMKObject::GetHeight()
{
	return m_dHeight;
}

void CMKObject::SetMagY(double dMagY)
{
//	if( m_bLock ==FALSE)
	if( m_bLock ==FALSE)
	m_dMagY = dMagY;
}

double CMKObject::GetMagY()
{
	return m_dMagY;
}

void CMKObject::SetMarkState(BOOL State) // 커팅 여부에 따라 다른 색깔로 그리도록 한다 
{
	m_bMarkState = State;
	if( m_bMarkState == TRUE)
	{
		//m_pPainter->SetLineRGB(RGB(255,0,0));
		m_pPainter->SetLineRGB(RGB(0,0,0));
	}
	else
		m_pPainter->SetLineRGB(RGB(50,50,50));



}

BOOL CMKObject::GetMarkState() 
{	
	return m_bMarkState;
}

void CMKObject::SetAngle(double dAngle)
{

	if( m_bLock ==FALSE)
	if(dAngle >=360)
		dAngle -=  360;
	
	if(dAngle < 0) 
		dAngle+=360;

	m_dAngle = dAngle;

}

double CMKObject::GetAngle()
{
	//if(m_dAngle >=360)
	//	m_dAngle -=  360;
//	if(m_dAngle < 0) m_dAngle*= -1;
	return m_dAngle;
}


UINT CMKObject::SetPainter(CObjectPainter *pPainter)
{
	ASSERT( FALSE == IsBadReadPtr( pPainter, sizeof( CObjectPainter) ) );
	if( pPainter == NULL) return 1;

	m_pPainter = pPainter;
	return 0;
}

CObjectPainter* CMKObject::GetPainter()
{
	return m_pPainter;

}

void CMKObject::SetUseSerial(BOOL bSerialFlag)
{
    m_bSerialFlag = bSerialFlag;
	
	
}// 시리얼 증가를 사용할것인가 안할것인가.
BOOL CMKObject::GetUseSerial()                    // 시리얼 증가 설정된 상태를 가져옴.
{
	
	return m_bSerialFlag;

}



void CMKObject::ReSize(double dPercent)
{
	double dMultiple = dPercent / 100;
	ReSize( (GetMagX() * dMultiple),(GetMagY() * dMultiple) );
}

void CMKObject::ReSize(double XMag, double YMag)
{
	SetMagX(XMag);
	SetMagY(YMag);
}
UINT CMKObject::GetObjectType()
{
	return m_uiObjectType;
}
void CMKObject::SetObjectType(UINT uiObjectType)
{
	m_uiObjectType = uiObjectType;  // 오브젝트 종류를 구분하게 해주는 변수
}



void CMKObject::SetParaIndex(UINT uiParaIndex)
{
	m_uiParaIndex = uiParaIndex;  //파라미터 인덱스를 저장
}

void CMKObject::SetBinIndex(UINT uiBinIndex)
{
	m_uiBinIndex = uiBinIndex;   //빈넘버 인덱스를 저장

}

UINT CMKObject::GetParaIndex()
{
	return m_uiParaIndex;
}

UINT CMKObject::GetBinIndex()
{
	return m_uiBinIndex;
}


int CMKObject::GetSelect(void)
{
	return m_bSelected;
}

void CMKObject::SetSelect(BOOL nFlag)
{
	m_bSelected = nFlag;
}

Vector * CMKObject::GetVectorData()
{
	return m_hpgl_data;
}

void CMKObject::SetVectorData(Vector *hpgl_data)
{
	m_hpgl_data = hpgl_data;
}

DWORD CMKObject::GetVectorLength()
{
	return m_dwVectorLength;
}

void CMKObject::SetVectorLength(DWORD vectorLength)
{
	m_dwVectorLength = vectorLength;
}

//static_cast


UINT CMKObject::Release() // 메모리 할당 받은 것들 모두 해제 
{
	if( m_pPainter != NULL )
	{
		delete m_pPainter;
		m_pPainter = NULL;
	}
	if( m_pDlg != NULL)
	{
		delete m_pDlg;
		m_pDlg = NULL;
	}
	//메모리 해제~
	if( m_pSender)
	{
		delete m_pSender;
		m_pSender = NULL;
	}


	
	if (m_hpgl_data)
	{
		delete [] m_hpgl_data;
		m_hpgl_data = NULL;
	}


	return R_DEFAULT;
}

void CMKObject::SetLock(BOOL state)
{
	m_bLock = state;

}


BOOL CMKObject::GetLock()
{

	return m_bLock;

}


char * CMKObject::Serialize(DWORD &dwLength)
{ 
	//자신의 멤버 변수들을 직렬화 한다.
	CMKFileWriter MKFW;
//	DWORD dwTempLength;
	
	MKFW.Add(ID_X, sizeof(double), &m_dX);
	MKFW.Add(ID_Y, sizeof(double), &m_dY);
	MKFW.Add(ID_MAGX, sizeof(double), &m_dMagX);
	MKFW.Add(ID_MAGY, sizeof(double), &m_dMagY);
	/*if(m_dAngle ==90 && m_uiObjectType == ID_COMPOSITE_OBJECT)
	{
	MKFW.Add(ID_WIDTH, sizeof(double), &m_dHeight);
	MKFW.Add(ID_HEIGHT, sizeof(double), &m_dWidth);
	
	}
	else*/
	{
	MKFW.Add(ID_WIDTH, sizeof(double), &m_dWidth);
	MKFW.Add(ID_HEIGHT, sizeof(double), &m_dHeight);
	}
	MKFW.Add(ID_PARAINDEX, sizeof(UINT), &m_uiParaIndex);
	MKFW.Add(ID_BININDEX, sizeof(UINT), &m_uiBinIndex);
	MKFW.Add(ID_ANGLE, sizeof(double), &m_dAngle);
	//m_bMarkState = 1;
	MKFW.Add(ID_MARKSTATE, sizeof(BOOL), &m_bMarkState);
	MKFW.Add(ID_SERIALFLAG, sizeof(BOOL), &m_bSerialFlag);
	MKFW.Add(ID_SELECTED, sizeof(BOOL), &m_bSelected);
	MKFW.Add(ID_OBJECTTYPE,sizeof(UINT), &m_uiObjectType);
	MKFW.Add(ID_SERIALNAME,m_strSerialName.GetLength() +1 , (LPCTSTR)m_strSerialName);
	MKFW.Add(ID_LOCKSTATE, sizeof(BOOL), &m_bLock);
	MKFW.Add(ID_STARTPOINT, sizeof(CDPoint), &m_ptStartPoint);
	MKFW.Add(ID_ENDPOINT, sizeof(CDPoint), &m_ptEndPoint);
	MKFW.Add(ID_MOVINGCENTERPOINT, sizeof(CPoint), &m_ptMovingCenterPoint);
	MKFW.Add(ID_CREATEZOOM, sizeof(double), &m_dCreateZoom);
	// 2011.09.29 syhun START - Hatching 관련.
	MKFW.Add(ID_HATCH_TYPE, sizeof(int), &m_nHatchType);
	MKFW.Add(ID_HATCH_DISTANCE, sizeof(double), &m_dHatchDistance);
	MKFW.Add(ID_HATCH_OFFSET, sizeof(double), &m_dHatchOffset);
	MKFW.Add(ID_HATCH_ANGLE, sizeof(double), &m_dHatchAngle);
	MKFW.Add(ID_HATCH_OUTLINE, sizeof(double), &m_bHatchOutLine);
	// syhun END.
	// syhun START - 그룹상태.
	MKFW.Add(ID_ISGROUP, sizeof(BOOL), &m_bIsGroup);
	// syhun END.
	MKFW.Add(ID_DOTMARK, sizeof(BOOL), &m_bIsDotMark);

	return MKFW.GetTotalData(dwLength);
}

UINT CMKObject::Unserialize(char *pstrSerial)
{
	//자신의 멤버 변수를 직렬화 해제 한다. 즉 pstrSerial 데이타를 가지고 멤버 변수 복귀 
	CMKFileReader MKFR;
	DWORD dwGetSize , dwGetID;
	char *pData;
	MKFR.GetAt(pstrSerial,ID_X,&m_dX);             // X 위치 
	MKFR.GetAt(pstrSerial,ID_Y,&m_dY);             // Y 위치 
	MKFR.GetAt(pstrSerial,ID_MAGX,&m_dMagX);       // X 방향 비율 
	MKFR.GetAt(pstrSerial,ID_MAGY,&m_dMagY);       // Y 방향 비율 
	MKFR.GetAt(pstrSerial,ID_WIDTH,&m_dWidth);    
	MKFR.GetAt(pstrSerial,ID_HEIGHT,&m_dHeight);
	MKFR.GetAt(pstrSerial,ID_PARAINDEX,&m_uiParaIndex);
	MKFR.GetAt(pstrSerial,ID_BININDEX,&m_uiBinIndex);
	MKFR.GetAt(pstrSerial,ID_ANGLE,&m_dAngle);
	//MKFR.GetAt(pstrSerial,ID_MARKSTATE,&m_bMarkState);
	MKFR.GetAt(pstrSerial,ID_MARKSTATE,&m_bMarkState);
	//m_bMarkState = 1;
	MKFR.GetAt(pstrSerial,ID_LOCKSTATE,&m_bLock);
	MKFR.GetAt(pstrSerial,ID_SERIALFLAG,&m_bSerialFlag);
	MKFR.GetAt(pstrSerial,ID_SELECTED,&m_bSelected);
	MKFR.GetAt(pstrSerial,ID_OBJECTTYPE,&m_uiObjectType);
	MKFR.GetAt(pstrSerial,ID_STARTPOINT,&m_ptStartPoint);
	MKFR.GetAt(pstrSerial,ID_ENDPOINT,&m_ptEndPoint);
	MKFR.GetAt(pstrSerial,ID_MOVINGCENTERPOINT,&m_ptMovingCenterPoint);
	MKFR.GetAt(pstrSerial,ID_CREATEZOOM,&m_dCreateZoom);
	// 2011.09.29 syhun START - Hatching 관련.
	MKFR.GetAt(pstrSerial,ID_HATCH_TYPE,&m_nHatchType);
	MKFR.GetAt(pstrSerial,ID_HATCH_DISTANCE,&m_dHatchDistance);
	MKFR.GetAt(pstrSerial,ID_HATCH_OFFSET,&m_dHatchOffset);
	MKFR.GetAt(pstrSerial,ID_HATCH_ANGLE,&m_dHatchAngle);
	MKFR.GetAt(pstrSerial,ID_HATCH_OUTLINE,&m_bHatchOutLine);
	// syhun END.
	// syhun START - 그룹상태.
	MKFR.GetAt(pstrSerial,ID_ISGROUP,&m_bIsGroup);
	// syhun END.
	MKFR.GetAt(pstrSerial,ID_DOTMARK,&m_bIsDotMark);
	
	pData = MKFR.GetAt(pstrSerial,ID_SERIALNAME,dwGetSize,dwGetID); // 시리얼 데이타 이름 
	m_strSerialName = pData;                                        //   3.12추가 
	delete pData;
	return R_DEFAULT;
}


void CMKObject::SetColor(COLORREF col) // 객체 그려지는 색상 선택 
{
	m_pPainter->SetLineRGB(col);
}

void CMKObject::Update()
{
	
}

CPoint CMKObject::GetStartPoint()
{
	return m_ptStartPoint;
}

CPoint CMKObject::GetEndPoint()
{
	return m_ptEndPoint;
}

CPoint CMKObject::GetMovingCenterPoint()
{
	return m_ptMovingCenterPoint;
}

double CMKObject::GetCreateZoom()
{
	return m_dCreateZoom;
}

BOOL CMKObject::InObject(CMKObject *pObject, CPoint point)
{
	return FALSE;
}

BOOL CMKObject::IsMixedObject()
{
	if (m_uiObjectType == ID_ARC_OBJECT || m_uiObjectType == ID_LINE_OBJECT)
		return TRUE;
		
	return FALSE;
}

BOOL CMKObject::GetPreSelected()
{
	return m_bPreSelected;
}

void CMKObject::SetPreSelected(BOOL bPreSelected)
{
	m_bPreSelected = bPreSelected;
}

int CMKObject::GetHatchType()
{
	return m_nHatchType;
}

void CMKObject::SetHatchType(int type)
{
	m_nHatchType = type;
}

double CMKObject::GetHatchDistance()
{
	return m_dHatchDistance;
}

void CMKObject::SetHatchDistance(double distance)
{
	m_dHatchDistance = distance;
}

double CMKObject::GetHatchOffset()
{
	return m_dHatchOffset;
}

void CMKObject::SetHatchOffset(double offset)
{
	m_dHatchOffset = offset;
}

double CMKObject::GetHatchAngle()
{
	return m_dHatchAngle;
}

void CMKObject::SetHatchAngle(double angle)
{
	m_dHatchAngle = angle;
}

BOOL CMKObject::GetHatchOutline()
{
	return m_bHatchOutLine;
}

void CMKObject::SetHatchOutline(BOOL outline)
{
	m_bHatchOutLine = outline;
}

void CMKObject::SetIsGroup(BOOL isGroup)
{
	m_bIsGroup = isGroup;
}

BOOL CMKObject::GetIsGroup()
{
	return m_bIsGroup;
}

void CMKObject::SetDotMark(BOOL isDotMark)
{
	m_bIsDotMark = isDotMark;
}

BOOL CMKObject::GetDotMark()
{
	return m_bIsDotMark;
}
