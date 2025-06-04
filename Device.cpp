//////////////////////////////////////////////////

#include "stdafx.h"
#include "Device.h"
#include "Return.h"
#include "define.h"
#include "MKFileWriter.h"
#include "MKFileReader.h"
#include "InitialTable.h"
#include "BoolArrConvertor.h"
#include "Vector.h"
#include "FieldParameter.h"
#include "TransUnit.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CDeviceManager* CDeviceManager::m_pDeviceManager;
CDeviceData::CDeviceData()
{
	CInitialTable *pInitialTable = pInitialTable->GetInstance();
	m_pChip = NULL;
	strcpy(m_cOffsetDirection, "noname "); 
	strcpy(m_cStripName, "noname");
	m_dStripWidth = pInitialTable->GetFieldSize();
	m_dStripHeight = pInitialTable->GetFieldSize();
	m_dChipWidth = pInitialTable->GetFieldSize();
	m_dChipHeight = pInitialTable->GetFieldSize();
	m_dXPitch1 = 0;
	m_dYPitch1 = 0;
	m_dXPitch2 = 0;
	m_dYPitch2 = 0;
	m_dOffset = 0;
	m_iXNum = 1;
	m_iYNum = 1;
	m_iSmallXNum = 1;
	m_iSmallYNum = 1;
	m_iMarkMethod = HORIZONTAL; // 커팅 방향 설정
	m_iCurIndex = 0;
	m_iStartPos = TOP_LEFT; // 커팅 시작 칩 정하는 듯
	m_iOffsetDirection = 0; // Offset 방향 설정을 int 값으로

	m_bOddFlag = FALSE;
	m_bCheckDevice = FALSE;
	m_bUse2Pitch = FALSE;
	// Master/Slave or Part1/ Part2
	m_bReadyPart1 = TRUE;
	m_bIsPartialNoMark = FALSE;
	m_DeviceType   =-1; 

	m_pChip = new CChip[m_iXNum * m_iYNum];
	
	Vector vec;
	vec.t = 1;
	vec.d = (0, 0);

	m_ltMasterOffset = new Vector[m_iXNum * m_iYNum];
	m_ltSlaveOffset = new Vector[m_iXNum * m_iYNum];

	
	int j = 0;
	for (j = 0; j < (m_iXNum * m_iYNum); j++) {
		m_ltMasterOffset[j] = vec;
	}
	for (j = 0; j < (m_iXNum * m_iYNum); j++) {
		m_ltSlaveOffset[j] = vec;
		
	}
	
	

	CDRect rect(0,0,0,0);
	m_pGuideRect = new CDRect[10];
	for(int i = 0; i < 10; i++)
	{
	 m_pGuideRect[i] = rect;
	}
	m_dMasterX = 0;
	m_dMasterY = 0;
	m_dSlaveX = 0;
	m_dSlaveY = 0;

	m_iFirstIndex = 0;


	// 2007.10.19  
	m_bSideArraySkip = FALSE;
}

CDeviceData::~CDeviceData()
{
	if (m_pChip != NULL) {
		delete [] m_pChip;
		m_pChip = NULL;
	}

	if (m_ltMasterOffset != NULL) {
		delete [] m_ltMasterOffset;
		m_ltMasterOffset = NULL;
	}

	if (m_ltSlaveOffset != NULL) {
		delete [] m_ltSlaveOffset;
		m_ltSlaveOffset = NULL;
	}

	

//	if(m_pGuideRect != NULL)
//	{
//	   delete [] m_pGuideRect;
//	   m_pGuideRect = NULL;
//	}
	
}

void CDeviceManager::CreateData()
{
	if( m_pDeviceData!= NULL) 
		delete m_pDeviceData;
	
	m_pDeviceData = new CDeviceData;
}

void CDeviceManager::DeleteData()
{
	if( m_pDeviceData !=  NULL)
	{
		delete  m_pDeviceData ;
		m_pDeviceData = NULL;
	}

}

void CDeviceManager::Remove()
{
	if( m_pDeviceManager != NULL)
	{
		delete m_pDeviceManager;
		m_pDeviceManager = 0;
	}
}

CDeviceManager* CDeviceManager::Instance()
{
	if( m_pDeviceManager == NULL)
	{
		m_pDeviceManager = new CDeviceManager;
	}
	ASSERT(m_pDeviceManager != NULL);

	return m_pDeviceManager;

}

UINT CDeviceManager::DoModal(UINT &uiGetResultCode)
{
	uiGetResultCode = m_pDlg->DoModal();
	return R_DEFAULT;
}

UINT CDeviceManager::Calculate()
{
	ASSERT(0);//여기를 완성시켜야한다!!!!!! 
	
	return R_DEFAULT;
}// ReadytoExtract와 GetNext를 쓰면 될것이다!!!!11.07


CDialog *CDeviceManager::GetDialog()
{
	return m_pDlg;
}

CDeviceManager::CDeviceManager(): m_pDeviceData(0)  
{
	m_pDlg = NULL;
	CreateData();
}

CDeviceManager::~CDeviceManager()
{
	DeleteData();
	m_pDeviceManager = NULL;	
}

char *CDeviceManager::Serialize(DWORD &dwLength)
{
	CMKFileWriter MKFW;
	DWORD dwSize;
	char *pData;

	if( m_pDeviceData == NULL ) return NULL;
	
	pData = m_pDeviceData->Serialize(dwSize);
	MKFW.Add(ID_DEVICE_DATA,dwSize,pData); // dwLength -> dwSize로 바꿈 
	delete pData;

	return MKFW.GetTotalData(dwLength);
}

void CDeviceManager::Unserialize(char *pstrSerial)
{
	CMKFileReader MKFR;
	DWORD dwGetSize, dwGetID;
	char *pData;
	
	CreateData();
			
	pData = MKFR.GetAt(pstrSerial,ID_DEVICE_DATA,dwGetSize,dwGetID);
	m_pDeviceData->Unserialize(pData);
	delete pData;
}

double CDeviceManager::GetDevWidth()
{
	return m_pDeviceData->GetChipWidth();
}

double CDeviceManager::GetDevHeight()
{
	return m_pDeviceData->GetChipHeight();
}

int CDeviceManager::Get_IDLocation()
{
  	return m_pDeviceData->GetIDLocation();
	
}

UINT CDeviceManager::SetDialog(CDialog *pDlg)
{
	 
	ASSERT( FALSE ==IsBadReadPtr(pDlg, sizeof(CDialog)));
	if(pDlg == NULL){ return R_FAILED;}
	else
		m_pDlg	= pDlg;

	return R_DEFAULT;
		
}





CDeviceData *CDeviceManager::GetDeviceData()
{
	ASSERT(m_pDeviceData != NULL);
	return m_pDeviceData;
}

void CDeviceManager::SetDeviceData(CDeviceData *pDevData)
{

	ASSERT(FALSE == IsBadReadPtr(pDevData,sizeof(CDeviceData)));
			
	m_pDeviceData = pDevData;

}

CPoint *CDeviceManager::GetPositionList(UINT &uiGetDeviceCount)
{


	return NULL;
}

void CDeviceManager::SetPositionList(CPoint *ptPosList, UINT uiSetDeviceCount)
{



}

void CDeviceData::ClearGuideMemory()
{
   if(m_pGuideRect != NULL)
	{
	   delete [] m_pGuideRect;
	   m_pGuideRect = NULL;
	}
}

void CDeviceData::SetStripWidth(double dStripWidth)
{
	m_dStripWidth = dStripWidth;
}

double CDeviceData::GetStripWidth()
{
	return m_dStripWidth;
}

void CDeviceData::SetStripHeight(double dStripHeight)
{
	m_dStripHeight = dStripHeight;
}

double CDeviceData::GetStripHeight()
{
	return m_dStripHeight;
}

void CDeviceData::SetChipWidth(double dChipWidth)
{
	m_dChipWidth = dChipWidth;
}

double CDeviceData::GetChipWidth()
{
	return m_dChipWidth;
}

void CDeviceData::SetChipHeight(double dChipHeight)
{
	m_dChipHeight = dChipHeight;
}

double CDeviceData::GetChipHeight()
{
	return m_dChipHeight;
}

void CDeviceData::SetXPitch1(double dXPitch1)
{
	m_dXPitch1 = dXPitch1;
}

double CDeviceData::GetXPitch1()
{
	return m_dXPitch1;
}

void CDeviceData::SetYPitch1(double dYPitch1)
{
	m_dYPitch1 = dYPitch1;
}

double CDeviceData::GetYPitch1()
{
	return m_dYPitch1;
}

void CDeviceData::SetXPitch2(double dXPitch2)
{
	m_dXPitch2 = dXPitch2;
}

double CDeviceData::GetXPitch2()
{
	return m_dXPitch2;
}

void CDeviceData::SetYPitch2(double dYPitch2)
{
	m_dYPitch2 = dYPitch2;
}

double CDeviceData::GetYPitch2()
{
	return m_dYPitch2;
}

void CDeviceData::SetXNum(int iXNum)
{
	m_iXNum = iXNum;
}

int  CDeviceData::GetXNum()
{
	return m_iXNum;
}

void CDeviceData::SetYNum(int iYNum)
{
	m_iYNum = iYNum;
}

int  CDeviceData::GetYNum()
{
	return m_iYNum;
}

void CDeviceData::SetSmallXNum(int iSmallXNum)
{
	m_iSmallXNum = iSmallXNum;
}

int  CDeviceData::GetSmallXNum()
{
	return m_iSmallXNum;
}

void CDeviceData::SetSmallYNum(int iSmallYNum)
{
	m_iSmallYNum = iSmallYNum;
}

int  CDeviceData::GetSmallYNum()
{
	return m_iSmallYNum;
}

void CDeviceData::SetMarkMethod(int iMarkMethod)
{
	m_iMarkMethod = iMarkMethod;
}

int  CDeviceData::GetMarkMethod()
{
	return m_iMarkMethod;
}

void CDeviceData::SetOffsetDirection(int iOffsetDirection)
{
	m_iOffsetDirection = iOffsetDirection;
}

int  CDeviceData::GetOffsetDirection()
{
	return m_iOffsetDirection;
}

void CDeviceData::SetOffset(double dOffset)
{
	m_dOffset = dOffset;
}

double CDeviceData::GetOffset()
{
	return m_dOffset;
}

void CDeviceData::SetIDLocation(int m_IdPos)
{
     m_iStartPos =  m_IdPos;
}


int CDeviceData::GetIDLocation()
{
	return m_iStartPos;
}
 
   
void CDeviceData::SetStripName(char *strStripName)
{
	if( strlen(strStripName)  < STRIPNAMESIZE ) 
	{
		strcpy(m_cStripName, strStripName);
	}
}

char *CDeviceData::GetStripName()
{
	return m_cStripName;
}

void CDeviceData::SetUse2Pitch(BOOL bUse2Pitch)
{
	m_bUse2Pitch = bUse2Pitch;
}

BOOL CDeviceData::GetUse2Pitch()
{
	return m_bUse2Pitch;
}

void CDeviceData::SetUseSideArraySkip(BOOL b)
{
	m_bSideArraySkip = b;
}

BOOL CDeviceData::GetUseSideArraySkip()
{
	return m_bSideArraySkip;
}



void CDeviceData::Clear_Tap_PositionData()
{
	m_st1_Tap_Position.clear();
	m_st_Tap_Position.clear();

	int nCount = (int)m_st_Tap_Position.size();
}


void CDeviceData::Add_Tap_Position(st_Tap_PositionData tTap_Position)
{
	if(m_st_Tap_Position.size() > 0)
	{
		m_st1_Tap_Position = Get_TapPosition(m_st_Tap_Position.size() - 1);
		double dGapData = tTap_Position.dPosition - m_st1_Tap_Position.dPosition;
		if(dGapData < 0) dGapData = 0.0;
		tTap_Position.dGap = dGapData;
	}
	else
	{
		tTap_Position.dGap = tTap_Position.dPosition;
	}
	m_st_Tap_Position.push_back(tTap_Position);
}



void CDeviceData::Add_Tap_Position(int index, st_Tap_PositionData tTap_Position)
{
	int nSize = m_st_Tap_Position.size();
	//m_st_Tap_Position.push_back(tTap_Position);
	//m_st_Tap_Position.insert(m_st_Tap_Position.begin(), tTap_Position); // 제일 처음에 추가
	//m_st_Tap_Position.insert(m_st_Tap_Position.end(), tTap_Position); // 제일 끝에 추가
	if(index > nSize)
		m_st_Tap_Position.push_back(tTap_Position);
	else
		m_st_Tap_Position.insert(m_st_Tap_Position.begin() + index, tTap_Position); //index 추가

	//시작점으로부터 100이란 값을 10개 채워 넣는다.
	//특정 값으로 일정 범위를 채워 넣을 수 있는 함수
	//m_st_Tap_Position.insert(m_st_Tap_Position.begin(), 10, 100);




}

void CDeviceData::DeleteAll_Tap_Position()
{

	m_st_Tap_Position.erase(m_st_Tap_Position.begin(), m_st_Tap_Position.begin() + m_st_Tap_Position.size());
/*
	int i = 0;
	for(std::vector<st_Tap_PositionData>::iterator iter = m_st_Tap_Position.begin(); iter != m_st_Tap_Position.end(); )
	{
		iter = m_st_Tap_Position.erase(iter);
		++iter;
	}*/
}


void CDeviceData::Delete_Tap_Position(int index)
{
	int i = 0;
	for(std::vector<st_Tap_PositionData>::iterator iter = m_st_Tap_Position.begin(); iter != m_st_Tap_Position.end(); )
	{
		if(i == index-1)
		{
		//if((*iter).dPosition == 0.0)

			iter = m_st_Tap_Position.erase(iter);
			break;
		}
		else
		{
			++iter;
		}
		i++;

	}


	////std::vector<st_Tap_Monitoring_PositionData>::iterator iter = m_st_Tap_MonitoringData.begin();
	////for(int i=0; iter != m_st_Tap_MonitoringData.end(); i++)
	//for(int i=0; i < m_st_Tap_Position.size(); i++)
	//{
	//	if(i == index)
	//	{
	//		m_st_Tap_MonitoringData.erase(i);
	//		break;
	//	}
	//	else
	//	{
	//		//iter++;
	//	}
	//}
	//
}


st_Tap_PositionData CDeviceData::Get_TapPosition(int nindex)
{
	st_Tap_PositionData result_Data;
	result_Data.clear();

	if( nindex >= (int)m_st_Tap_Position.size() ){
		//2018.10.04 jjsjong For TEST
		return result_Data;
	}
	else 
	{
		return m_st_Tap_Position[nindex];
	}
}

int CDeviceData::Get_TapPositionCount()
{
	int nCount = (int)m_st_Tap_Position.size();
	return nCount;
}


void CDeviceData::Clear_Tap_MonitoringData()
{
	m_st1_Tap_MonitoringData.clear();
	m_st_Tap_MonitoringData.clear();

	int nCount = (int)m_st_Tap_MonitoringData.size();
}

void CDeviceData::Add_Tap_MonitoringData(st_Tap_Monitoring_PositionData tTap_MonitoringData)
{
	if(m_st_Tap_MonitoringData.size() > 0)
	{
		m_st1_Tap_Position = Get_TapPosition(m_st_Tap_MonitoringData.size() - 1);
	}	
	else
	{
		
	}
	m_st_Tap_MonitoringData.push_back(tTap_MonitoringData);

	//
}

st_Tap_Monitoring_PositionData CDeviceData::Get_Tap_MonitoringData(int nindex)
{
	st_Tap_Monitoring_PositionData result_Data;
	result_Data.clear();

	if( nindex >= (int)m_st_Tap_MonitoringData.size() ){
		//2018.10.04 jjsjong For TEST
		return result_Data;
	}
	else 
	{
		return m_st_Tap_MonitoringData[nindex];
	}
}

int CDeviceData::Get_Tap_MonitoringDataCount()
{
	int nCount = (int)m_st_Tap_MonitoringData.size();
	return nCount;
}



char *CDeviceData::Serialize(DWORD &dwLength)
{
	CMKFileWriter MKFW;
	CBoolArrConvertor BoolArr; // SelectArr용량이 너무 커서 좀 줄여봅니다 ^^;;
	DWORD dwResultSize1=0, dwResultSize2=0;

	MKFW.Add(ID_CHAR_OFFSET_DIRECTION,	sizeof(char)*256,	m_cOffsetDirection);
	MKFW.Add(ID_STRIP_NAME,				strlen( m_cStripName ) +1 , m_cStripName);
	MKFW.Add(ID_STRIP_WIDTH,			sizeof(double)	,	&m_dStripWidth);
	MKFW.Add(ID_STRIP_HEIGHT,			sizeof(double)	,	&m_dStripHeight);
	MKFW.Add(ID_CHIP_WIDTH,				sizeof(double)	,	&m_dChipWidth);
	MKFW.Add(ID_CHIP_HEIGHT,			sizeof(double)	,	&m_dChipHeight);
	MKFW.Add(ID_XPITCH1,				sizeof(double)	,	&m_dXPitch1);
	MKFW.Add(ID_YPITCH1,				sizeof(double)	,	&m_dYPitch1);
	MKFW.Add(ID_XPITCH2,				sizeof(double)	,	&m_dXPitch2);
	MKFW.Add(ID_YPITCH2,				sizeof(double)	,	&m_dYPitch2);
	MKFW.Add(ID_OFFSET,					sizeof(double)	,	&m_dOffset);
	MKFW.Add(ID_XNUM,					sizeof(int)	,		&m_iXNum);
	MKFW.Add(ID_YNUM,					sizeof(int)	,		&m_iYNum);
	MKFW.Add(ID_SMALL_XNUM,				sizeof(int)	,		&m_iSmallXNum);
	MKFW.Add(ID_SMALL_YNUM,				sizeof(int)	,		&m_iSmallYNum);
	MKFW.Add(ID_MARK_METHOD,			sizeof(int)	,		&m_iMarkMethod);
	MKFW.Add(ID_CUR_INDEX,				sizeof(int)	,		&m_iCurIndex);
	MKFW.Add(ID_START_POS,				sizeof(int)	,		&m_iStartPos);
	MKFW.Add(ID_INT_OFFSET_DIRECTION,	sizeof(int)	,		&m_iOffsetDirection);
	MKFW.Add(ID_SELECT_ARRAY2,			sizeof(Vector)*(m_iXNum*m_iYNum), m_ltMasterOffset);
	MKFW.Add(ID_SELECT_ARRAY,			sizeof(Vector)*(m_iXNum*m_iYNum), m_ltSlaveOffset);
	MKFW.Add(ID_ODD_FLAG,				sizeof(BOOL),		&m_bOddFlag);
	MKFW.Add(ID_CHECK_DEVICE,			sizeof(BOOL),		&m_bCheckDevice);
	MKFW.Add(ID_USE2PITCH,				sizeof(BOOL),		&m_bUse2Pitch);
	MKFW.Add(ID_READY_PART,				sizeof(BOOL),		&m_bReadyPart1);
	MKFW.Add(ID_IS_PARTIAL_NO_MARK,		sizeof(BOOL),		&m_bIsPartialNoMark);

	CFieldParameter *pFieldParameter = pFieldParameter->GetInstance();
	CDRect pTmpRect;
	if(m_pGuideRect != NULL)
	{
		for(int i=0;i<9;i++){
			m_pGuideRect[i] = pFieldParameter->GetGuideLineValue(i);
			m_pGuideRect[i].t = pFieldParameter->GetGuideCheck(i); 
		}
	}
	
	m_dMasterX = int(pFieldParameter->GetMasterX()); 
	m_dMasterY = int(pFieldParameter->GetMasterY()); 
	m_dSlaveX = int(pFieldParameter->GetSlaveX()); 
	m_dSlaveY = int(pFieldParameter->GetSlaveY()); 

	MKFW.Add(ID_MASTER_OFFSETX,					sizeof(double)	,	&m_dMasterX);
	MKFW.Add(ID_MASTER_OFFSETY,					sizeof(double)	,	&m_dMasterY);
	MKFW.Add(ID_SLAVE_OFFSETX,					sizeof(double)	,	&m_dSlaveX);
	MKFW.Add(ID_SLAVE_OFFSETY,					sizeof(double)	,	&m_dSlaveY);

	// 2007.10.19  
	MKFW.Add(ID_SIDE_ARRAY_SKIP,				sizeof(BOOL)	,	&m_bSideArraySkip);

	if(m_pGuideRect!= NULL)
	MKFW.Add(ID_GUIDE_VALUE,					sizeof(CDRect)*10,  m_pGuideRect);

	//--------------------------------LOGO 변수------------------------------------------
	_NOTCH_PATTERN_DATA m_stNotchPatternData;
	m_stNotchPatternData = pFieldParameter->GetHEAD2PatternDataOfKoem();

	MKFW.Add(ID_WIDTH ,sizeof(double), &m_stNotchPatternData.dWidth);
	MKFW.Add(ID_HEIGHT ,sizeof(double), &m_stNotchPatternData.dHeight);
	MKFW.Add(ID_EXPEND_DIST ,sizeof(double), &m_stNotchPatternData.dExpendDist);
	MKFW.Add(ID_START_EXT_OFFSET ,sizeof(double), &m_stNotchPatternData.dStartExtOffset);
	MKFW.Add(ID_END_EXT_OFFSET ,sizeof(double), &m_stNotchPatternData.dEndExtOffset);
	MKFW.Add(ID_LT_RADIUS ,sizeof(double), &m_stNotchPatternData.dLT_Radius);
	MKFW.Add(ID_LB_RADIUS ,sizeof(double), &m_stNotchPatternData.dLB_Radius);
	MKFW.Add(ID_RT_RADIUS ,sizeof(double), &m_stNotchPatternData.dRT_Radius);
	MKFW.Add(ID_RB_RADIUS ,sizeof(double), &m_stNotchPatternData.dRB_Radius);
	MKFW.Add(ID_L_SLOOP_ANGLE ,sizeof(double), &m_stNotchPatternData.dLeftTabAngle);
	MKFW.Add(ID_L_CTRL_POINT1 ,sizeof(double), &m_stNotchPatternData.dLeftCtrlPoint1);
	MKFW.Add(ID_L_CTRL_POINT2 ,sizeof(double), &m_stNotchPatternData.dLeftCtrlPoint2);
	MKFW.Add(ID_R_SLOOP_ANGLE ,sizeof(double), &m_stNotchPatternData.dRightTabAngle);
	MKFW.Add(ID_R_CTRL_POINT1 ,sizeof(double), &m_stNotchPatternData.dRightCtrlPoint1);
	MKFW.Add(ID_R_CTRL_POINT2 ,sizeof(double), &m_stNotchPatternData.dRightCtrlPoint2);
	MKFW.Add(ID_Y_FLIP        ,sizeof(BOOL), &m_stNotchPatternData.bYFlip);
	MKFW.Add(ID_Y_OFFSET	  ,sizeof(double), &m_stNotchPatternData.dYoffset);
	MKFW.Add(ID_OFFSET_CUT_WIDTH ,sizeof(double), &m_stNotchPatternData.dOffsetCutWidth);
	MKFW.Add(ID_SLOOP_WIDTH ,sizeof(double), &m_stNotchPatternData.dSloopWidth);
	MKFW.Add(ID_SLOOP_WIDTH_L ,sizeof(double), &m_stNotchPatternData.dSloopWidth_L);
	MKFW.Add(ID_SLOOP_WIDTH_R ,sizeof(double), &m_stNotchPatternData.dSloopWidth_R);
	MKFW.Add(ID_BASE_CUTWIDTH ,sizeof(double), &m_stNotchPatternData.dBaseCutWidth);

	MKFW.Add(ID_SLOOP_SEGMENT_LT ,sizeof(double), &m_stNotchPatternData.dSloopSegment_LT);
	MKFW.Add(ID_SLOOP_SEGMENT_LB ,sizeof(double), &m_stNotchPatternData.dSloopSegment_LB);
	MKFW.Add(ID_SLOOP_SEGMENT_RT ,sizeof(double), &m_stNotchPatternData.dSloopSegment_RT);
	MKFW.Add(ID_SLOOP_SEGMENT_RB ,sizeof(double), &m_stNotchPatternData.dSloopSegment_RB);

	MKFW.Add(ID_EXTEND_XWIDTH_L ,sizeof(double), &m_stNotchPatternData.dExtend_Xwidth_L);
	MKFW.Add(ID_EXTEND_XWIDTH_R ,sizeof(double), &m_stNotchPatternData.dExtend_Xwidth_R);
	MKFW.Add(ID_EXTEND_YHEIGHT_L ,sizeof(double),&m_stNotchPatternData.dExtend_Yheight_L);
	MKFW.Add(ID_EXTEND_YHEIGHT_R ,sizeof(double),&m_stNotchPatternData.dExtend_Yheight_R);

	//----T사 데이터---------------
	MKFW.Add(ID_UNFLAG_START ,sizeof(double), &m_stNotchPatternData.dNonflagStartWidth);
	MKFW.Add(ID_UNFLAG_START_HEIGHT ,sizeof(double), &m_stNotchPatternData.dNonflagStartHeight);
	MKFW.Add(ID_UNFLAG_END ,sizeof(double), &m_stNotchPatternData.dNonflagEndWidth);
	MKFW.Add(ID_UNFLAG_END_HEIGHT ,sizeof(double), &m_stNotchPatternData.dNonflagEndHeight);
	MKFW.Add(ID_NUBLESS_REGION ,sizeof(double), &m_stNotchPatternData.dNublessRegion);
	MKFW.Add(ID_NUBLESS_HEIGHT ,sizeof(double), &m_stNotchPatternData.dNublessHeight);
	MKFW.Add(ID_BURIED_REGION ,sizeof(double), &m_stNotchPatternData.dBuriedRegion);
	MKFW.Add(ID_BURIED_HEIGHT ,sizeof(double), &m_stNotchPatternData.dBuriedHeight);
	MKFW.Add(ID_FLAG_COUNT ,sizeof(double), &m_stNotchPatternData.dTabCount);
	MKFW.Add(ID_FLAG_LENGTH ,sizeof(double), &m_stNotchPatternData.dTabHeight);
	MKFW.Add(ID_FLAG_WIDTH ,sizeof(double), &m_stNotchPatternData.dTabWidth);
	MKFW.Add(ID_FLAG_START_WIDTH ,sizeof(double), &m_stNotchPatternData.dFlagStartWidth);
	MKFW.Add(ID_FLAG_DEGREES ,sizeof(double), &m_stNotchPatternData.dTabAngle);
	MKFW.Add(ID_HEAD2_WIDTH ,sizeof(double), &m_stNotchPatternData.dHEAD2Width);
	MKFW.Add(ID_FOIL_EXTENSION ,sizeof(double), &m_stNotchPatternData.dFoilExtention);
	MKFW.Add(ID_NOTCH_ROOT ,sizeof(double), &m_stNotchPatternData.dNotchRoot);

	pFieldParameter->SetHEAD2PatternData(m_stNotchPatternData);

	return MKFW.GetTotalData(dwLength);  //모아진 총 데이타를 반환한다.
	
}

void CDeviceData::Unserialize(char *pstrSerial)
{
	CMKFileReader MKFR;
	CBoolArrConvertor BoolArr;
	char *pData;
	DWORD dwGetSize,dwGetID;

	
	pData = MKFR.GetAt(pstrSerial, ID_CHAR_OFFSET_DIRECTION,	dwGetSize,	dwGetID);
	memcpy(m_cOffsetDirection,pData,dwGetSize);
	delete pData;
		
	pData = MKFR.GetAt(pstrSerial,ID_STRIP_NAME,				dwGetSize,	dwGetID);
	if( pData != NULL)
	{
		memcpy(m_cStripName,  pData, dwGetSize);
		delete pData;
	}
	
	MKFR.GetAt(pstrSerial,ID_STRIP_WIDTH,		&m_dStripWidth);
	MKFR.GetAt(pstrSerial,ID_STRIP_HEIGHT,		&m_dStripHeight);
	MKFR.GetAt(pstrSerial,ID_CHIP_WIDTH,		&m_dChipWidth);
	MKFR.GetAt(pstrSerial,ID_CHIP_HEIGHT,		&m_dChipHeight);
	MKFR.GetAt(pstrSerial,ID_XPITCH1,			&m_dXPitch1);
	MKFR.GetAt(pstrSerial,ID_YPITCH1,			&m_dYPitch1);
	MKFR.GetAt(pstrSerial,ID_XPITCH2,			&m_dXPitch2);
	MKFR.GetAt(pstrSerial,ID_YPITCH2,			&m_dYPitch2);
	MKFR.GetAt(pstrSerial,ID_OFFSET,			&m_dOffset);
	MKFR.GetAt(pstrSerial,ID_XNUM,				&m_iXNum);
	MKFR.GetAt(pstrSerial,ID_YNUM,				&m_iYNum);
	MKFR.GetAt(pstrSerial,ID_SMALL_XNUM,		&m_iSmallXNum);
	MKFR.GetAt(pstrSerial,ID_SMALL_YNUM,		&m_iSmallYNum);
	MKFR.GetAt(pstrSerial,ID_MARK_METHOD,		&m_iMarkMethod);
	MKFR.GetAt(pstrSerial,ID_CUR_INDEX,			&m_iCurIndex);
	MKFR.GetAt(pstrSerial,ID_START_POS,			&m_iStartPos);
	MKFR.GetAt(pstrSerial,ID_INT_OFFSET_DIRECTION,&m_iOffsetDirection);

	// ----------------------------LOGO 변수 ----------------------------
	_NOTCH_PATTERN_DATA m_stNotchPatternData;
	//-------------2018.12.18 KOEM PATTERN 용 추가
	MKFR.GetAt(pstrSerial, ID_WIDTH ,&m_stNotchPatternData.dWidth);
	MKFR.GetAt(pstrSerial, ID_HEIGHT ,&m_stNotchPatternData.dHeight);
	MKFR.GetAt(pstrSerial, ID_EXPEND_DIST ,&m_stNotchPatternData.dExpendDist);
	MKFR.GetAt(pstrSerial, ID_START_EXT_OFFSET ,&m_stNotchPatternData.dStartExtOffset);
	MKFR.GetAt(pstrSerial, ID_END_EXT_OFFSET ,&m_stNotchPatternData.dEndExtOffset);
	MKFR.GetAt(pstrSerial, ID_LT_RADIUS ,&m_stNotchPatternData.dLT_Radius);
	MKFR.GetAt(pstrSerial, ID_LB_RADIUS ,&m_stNotchPatternData.dLB_Radius);
	MKFR.GetAt(pstrSerial, ID_RT_RADIUS ,&m_stNotchPatternData.dRT_Radius);
	MKFR.GetAt(pstrSerial, ID_RB_RADIUS ,&m_stNotchPatternData.dRB_Radius);
	MKFR.GetAt(pstrSerial, ID_L_SLOOP_ANGLE ,&m_stNotchPatternData.dLeftTabAngle);
	MKFR.GetAt(pstrSerial, ID_L_CTRL_POINT1 ,&m_stNotchPatternData.dLeftCtrlPoint1);
	MKFR.GetAt(pstrSerial, ID_L_CTRL_POINT2 ,&m_stNotchPatternData.dLeftCtrlPoint2);
	MKFR.GetAt(pstrSerial, ID_R_SLOOP_ANGLE ,&m_stNotchPatternData.dRightTabAngle);
	MKFR.GetAt(pstrSerial, ID_R_CTRL_POINT1 ,&m_stNotchPatternData.dRightCtrlPoint1);
	MKFR.GetAt(pstrSerial, ID_R_CTRL_POINT2 ,&m_stNotchPatternData.dRightCtrlPoint2);
	MKFR.GetAt(pstrSerial, ID_Y_FLIP        ,&m_stNotchPatternData.bYFlip);
	MKFR.GetAt(pstrSerial, ID_Y_OFFSET	  ,&m_stNotchPatternData.dYoffset);
	MKFR.GetAt(pstrSerial, ID_OFFSET_CUT_WIDTH ,&m_stNotchPatternData.dOffsetCutWidth);

	MKFR.GetAt(pstrSerial, ID_SLOOP_WIDTH ,&m_stNotchPatternData.dSloopWidth);
	MKFR.GetAt(pstrSerial, ID_SLOOP_WIDTH_L ,&m_stNotchPatternData.dSloopWidth_L);
	MKFR.GetAt(pstrSerial, ID_SLOOP_WIDTH_R ,&m_stNotchPatternData.dSloopWidth_R);
	MKFR.GetAt(pstrSerial, ID_BASE_CUTWIDTH ,&m_stNotchPatternData.dBaseCutWidth);

	MKFR.GetAt(pstrSerial, ID_SLOOP_SEGMENT_LT ,&m_stNotchPatternData.dSloopSegment_LT);
	MKFR.GetAt(pstrSerial, ID_SLOOP_SEGMENT_LB ,&m_stNotchPatternData.dSloopSegment_LB);
	MKFR.GetAt(pstrSerial, ID_SLOOP_SEGMENT_RT ,&m_stNotchPatternData.dSloopSegment_RT);
	MKFR.GetAt(pstrSerial, ID_SLOOP_SEGMENT_RB ,&m_stNotchPatternData.dSloopSegment_RB);

	MKFR.GetAt(pstrSerial, ID_EXTEND_XWIDTH_L ,&m_stNotchPatternData.dExtend_Xwidth_L);
	MKFR.GetAt(pstrSerial, ID_EXTEND_XWIDTH_R ,&m_stNotchPatternData.dExtend_Xwidth_R);
	MKFR.GetAt(pstrSerial, ID_EXTEND_YHEIGHT_L ,&m_stNotchPatternData.dExtend_Yheight_L);
	MKFR.GetAt(pstrSerial, ID_EXTEND_YHEIGHT_R ,&m_stNotchPatternData.dExtend_Yheight_R);


	//------------------T사 데이터------------------------------------
	MKFR.GetAt(pstrSerial, ID_UNFLAG_START ,&m_stNotchPatternData.dNonflagStartWidth);
	MKFR.GetAt(pstrSerial, ID_UNFLAG_START_HEIGHT ,&m_stNotchPatternData.dNonflagStartHeight);
	MKFR.GetAt(pstrSerial, ID_UNFLAG_END ,&m_stNotchPatternData.dNonflagEndWidth);
	MKFR.GetAt(pstrSerial, ID_UNFLAG_END_HEIGHT ,&m_stNotchPatternData.dNonflagEndHeight);
	MKFR.GetAt(pstrSerial, ID_NUBLESS_REGION ,&m_stNotchPatternData.dNublessRegion);
	MKFR.GetAt(pstrSerial, ID_NUBLESS_HEIGHT ,&m_stNotchPatternData.dNublessHeight);
	MKFR.GetAt(pstrSerial, ID_BURIED_REGION ,&m_stNotchPatternData.dBuriedRegion);
	MKFR.GetAt(pstrSerial, ID_BURIED_HEIGHT ,&m_stNotchPatternData.dBuriedHeight);
	MKFR.GetAt(pstrSerial, ID_FLAG_COUNT ,&m_stNotchPatternData.dTabCount);
	MKFR.GetAt(pstrSerial, ID_FLAG_LENGTH ,&m_stNotchPatternData.dTabHeight);
	MKFR.GetAt(pstrSerial, ID_FLAG_WIDTH ,&m_stNotchPatternData.dTabWidth);
	MKFR.GetAt(pstrSerial, ID_FLAG_START_WIDTH ,&m_stNotchPatternData.dFlagStartWidth);
	MKFR.GetAt(pstrSerial, ID_FLAG_DEGREES ,&m_stNotchPatternData.dTabAngle);
	MKFR.GetAt(pstrSerial, ID_HEAD2_WIDTH ,&m_stNotchPatternData.dHEAD2Width);
	MKFR.GetAt(pstrSerial, ID_FOIL_EXTENSION ,&m_stNotchPatternData.dFoilExtention);
	MKFR.GetAt(pstrSerial, ID_NOTCH_ROOT ,&m_stNotchPatternData.dNotchRoot);

	if (m_ltMasterOffset != NULL) {
		delete [] m_ltMasterOffset;
		m_ltMasterOffset = NULL;
	}
	if (m_ltSlaveOffset != NULL) {
		delete [] m_ltSlaveOffset;
		m_ltSlaveOffset = NULL;
	}

	if(m_pGuideRect != NULL)
	{
	   delete [] m_pGuideRect;
	   m_pGuideRect = NULL;
	}

//-------------------------------------------------------------------------------------------
//	Vector vec;
//	vec.t = 1;
//	vec.d = (0, 0);

//	m_ltMasterOffset = new Vector[m_iXNum * m_iYNum];
//	m_ltSlaveOffset = new Vector[m_iXNum * m_iYNum];


//	for (int j = 0; j < (m_iXNum * m_iYNum); j++) {
//		m_ltMasterOffset[j] = vec;
//	}
//	for (j = 0; j < (m_iXNum * m_iYNum); j++) {
//		m_ltSlaveOffset[j] = vec;
//		
//	}
	
//---------------------------------------------------------------------------------------------------

//	m_ltMasterOffset = new Vector[m_iXNum * m_iYNum];  //주석 처리 GetAt이 메모리 할당해주기땜에
//	m_ltSlaveOffset = new Vector[m_iXNum * m_iYNum];

	m_ltMasterOffset = (Vector *)MKFR.GetAt(pstrSerial,ID_SELECT_ARRAY2,dwGetSize,dwGetID);
	m_ltSlaveOffset = (Vector *)MKFR.GetAt(pstrSerial,ID_SELECT_ARRAY,dwGetSize,dwGetID);

	
//	pData = MKFR.GetAt(pstrSerial,ID_SELECT_ARRAY,	dwGetSize,	dwGetID);              //MKFR.GetAt(pstrSerial,ID_SELECT_ARRAY,		&m_bMasterSelectArray);
//	BoolArr.DecodetoBOOL(m_bMasterSelectArray,(DWORD *)pData,SELECTARRAYSIZE);
//	if( pData != NULL) delete pData;
//	pData = MKFR.GetAt(pstrSerial,ID_SELECT_ARRAY2,dwGetSize,	dwGetID);              //MKFR.GetAt(pstrSerial,ID_SELECT_ARRAY2,		&m_bSlaveSelectArray);
//	BoolArr.DecodetoBOOL(m_bSlaveSelectArray,(DWORD *)pData,SELECTARRAYSIZE);  //디코딩 끝 
//	if( pData != NULL) delete pData;
	MKFR.GetAt(pstrSerial,ID_ODD_FLAG,			&m_bOddFlag);
	MKFR.GetAt(pstrSerial,ID_CHECK_DEVICE,		&m_bCheckDevice);
	MKFR.GetAt(pstrSerial,ID_USE2PITCH,			&m_bUse2Pitch);
	MKFR.GetAt(pstrSerial,ID_READY_PART,		&m_bReadyPart1);
	MKFR.GetAt(pstrSerial,ID_IS_PARTIAL_NO_MARK,&m_bIsPartialNoMark);

	MKFR.GetAt(pstrSerial,ID_MASTER_OFFSETX,		&m_dMasterX);
	MKFR.GetAt(pstrSerial,ID_MASTER_OFFSETY,		&m_dMasterY);
	MKFR.GetAt(pstrSerial,ID_SLAVE_OFFSETX,			&m_dSlaveX);
	MKFR.GetAt(pstrSerial,ID_SLAVE_OFFSETY,			&m_dSlaveY);

	// 2007.10.19  
	MKFR.GetAt(pstrSerial,ID_SIDE_ARRAY_SKIP,			&m_bSideArraySkip);

	CFieldParameter *pFieldParameter = pFieldParameter->GetInstance();
//	MKFW.Add(ID_GUIDE_VALUE,sizeof(CDRect)*10,  &m_pGuideRe

	//m_ltMasterOffset = (Vector *)MKFR.GetAt(pstrSerial,ID_SELECT_ARRAY2,dwGetSize,dwGetID);
	//CDRect pTmpRect;

	//m_pGuideRect = (CDRect *)MKFR.GetAt(pstrSerial, ID_GUIDE_VALUE, dwGetSize, dwGetID);

	//if(m_pGuideRect != NULL){
	//	for(int i =0; i< 9;i++){
	//		pTmpRect = m_pGuideRect[i];
	//		pTmpRect.t = m_pGuideRect[i].t;
	//		if(pTmpRect.t == 1)
	//			pFieldParameter->SetGuideCheck(i, TRUE);
	//		else
	//			pFieldParameter->SetGuideCheck(i, FALSE);	
	//		pFieldParameter->SetGuideLineSet(pTmpRect, i);
	//	}
	//}
	//else
	//{
	//	pTmpRect.top = 0;
	//	pTmpRect.bottom =0;
	//	pTmpRect.left =0;
	//	pTmpRect.right =0;
	//	pTmpRect.t =0;
	//	for(int i =0; i< 9;i++){
	//	//	pTmpRect = m_pGuideRect[i];
	//	//	pTmpRect.t = m_pGuideRect[i].t;
	//	//	if(pTmpRect.t == 1)
	//	//		pFieldParameter->SetGuideCheck(i, TRUE);
	//	//	else
	//		pFieldParameter->SetGuideCheck(i, FALSE);	
	//		pFieldParameter->SetGuideLineSet(pTmpRect, i);
	//	}
	//}
	//
	
	CTransUnit	*pTransUnit = pTransUnit->GetInstance();
	int m_iUnit= FIELD;//pFieldParameter->GetUnit();
	double m_dMMSize,m_dFieldSize;
	pFieldParameter->GetSize(&m_dMMSize,&m_dFieldSize) ;

	pTransUnit->SetValue(m_dMasterX, m_iUnit);
	m_dMasterX = pTransUnit->GetField();
	pFieldParameter->SetMasterX(m_dMasterX) ;

	pTransUnit->SetValue(m_dMasterY, m_iUnit);
	m_dMasterY = pTransUnit->GetField();
	pFieldParameter->SetMasterY(m_dMasterY) ;

	pTransUnit->SetValue(m_dSlaveX, m_iUnit);
	m_dSlaveX = pTransUnit->GetField();
	pFieldParameter->SetSlaveX(m_dSlaveX) ;
	
	pTransUnit->SetValue(m_dSlaveY, m_iUnit);
	m_dSlaveY = pTransUnit->GetField();
	pFieldParameter->SetSlaveY(m_dSlaveY) ;
	

	//pFieldParameter->SetHEAD2PatternData(m_stNotchPatternData);
}

Vector *CDeviceData::GetMasterOffset()
{
	return m_ltMasterOffset;
}

Vector *CDeviceData::GetSlaveOffset()
{
	return m_ltSlaveOffset;
}

CPoint CDeviceData::GetNext()
{
	CInitialTable *pInitialTable = pInitialTable->GetInstance();
	CPoint point;
	CDeviceManager *pDeviceManager = pDeviceManager->Instance();	
	CDeviceData *deviceData = pDeviceManager->GetDeviceData();	

	// 현재 위치 반환 
	// 다음 위치 이동

//	point.x = m_pChip[m_iCurIndex].m_position.x/* + m_pChip[m_iCurIndex].m_offsetX*/;
//	point.y = m_pChip[m_iCurIndex].m_position.y/* + m_pChip[m_iCurIndex].m_offsetY*/;
//21017.04.13 jjsjong Chip Offset 수정
	point.x = m_pChip[m_iCurIndex].m_position.x + m_pChip[m_iCurIndex].m_offsetX;
	point.y = m_pChip[m_iCurIndex].m_position.y + m_pChip[m_iCurIndex].m_offsetY;


	

	ASSERT(m_ltMasterOffset != NULL && m_ltSlaveOffset != NULL);

	if (m_ltMasterOffset[m_iCurIndex].t == 1 
		&& m_ltSlaveOffset[m_iCurIndex].t == 1)	{
	//	if(deviceData->GetUseSideArraySkip()&&(m_iCurIndex%deviceData->GetXNum()==0))	
	//		m_iMoveShutter = 4;
	//	else
			m_iMoveShutter = 3;
	}
	else if (m_ltMasterOffset[m_iCurIndex].t == 1
		&& m_ltSlaveOffset[m_iCurIndex].t == 0) {
	//	if(deviceData->GetUseSideArraySkip()&&(m_iCurIndex%deviceData->GetXNum()==0))
	//		m_iMoveShutter = 5;
	//	else
	//		m_iMoveShutter = 3;
			m_iMoveShutter = 2;
	}
	else if (m_ltMasterOffset[m_iCurIndex].t == 0 
		&& m_ltSlaveOffset[m_iCurIndex].t == 1) {
		m_iMoveShutter = 1;
	}
	else if (m_ltMasterOffset[m_iCurIndex].t == 0 
		&& m_ltSlaveOffset[m_iCurIndex].t == 0) {
	//	m_iMoveShutter = 5;
		m_iMoveShutter = 0;
	}

   if(m_iYNum == 1) 
	   m_iMarkMethod = HORIZONTAL;

	switch(m_iMarkMethod)
	{
	case HORIZONTAL:
		m_iCurIndex++;
		break;
	case HORIZONTAL_ZIG:
		if (m_bOddFlag == FALSE)
		{	// 홀수 줄이면
			if(m_iCurIndex+1 == (m_iXNum*m_iYNum)){
				m_iCurIndex = 0;
			
			}
			if ((m_iCurIndex % m_iXNum) == (m_iXNum-1))
			{
				m_iCurIndex += m_iXNum;
				m_bOddFlag = ((m_bOddFlag == TRUE) ? FALSE: TRUE);
			}
			else
				m_iCurIndex++;
			
		} else
		{	// 작수 줄이면 
			
			if ((m_iCurIndex % m_iXNum ==0) && (m_iCurIndex > 0))
			{
				m_iCurIndex += m_iXNum;
				m_bOddFlag = ((m_bOddFlag == TRUE) ? FALSE: TRUE);
			}
			else if(m_iCurIndex == 0){
				m_iCurIndex++;
				m_bOddFlag = ((m_bOddFlag == TRUE) ? FALSE: TRUE);
			}
			else
				m_iCurIndex--;	
		}
		break;
	case VERTICAL:
		if ( m_iCurIndex < (m_iXNum*(m_iYNum-1)))
			m_iCurIndex += m_iXNum;
		else 
			m_iCurIndex = m_iCurIndex-(m_iXNum*(m_iYNum-1))+1;
		break;
	case VERTICAL_ZIG:
		if (m_bOddFlag == FALSE)
		{	// 홀수 줄이면
			if(m_iCurIndex+1 == (m_iXNum*m_iYNum)) 
				m_iCurIndex =0; 

			if ( m_iCurIndex < (m_iXNum*(m_iYNum-1)))
				m_iCurIndex += m_iXNum;
			else 
			{
				m_iCurIndex++;
				m_bOddFlag = ((m_bOddFlag == TRUE) ? FALSE: TRUE);
			}
		} 
		else
		{	
			// 작수 줄이면
			double ii = (m_iCurIndex+1) % 2;

			if ( m_iCurIndex > (m_iXNum-1))
				m_iCurIndex -= m_iXNum;
			else if((m_iCurIndex+1) % 2 ==0 && m_iCurIndex < m_iXNum-1) 
			{
				m_iCurIndex++;
			}
			else
			{
				m_iCurIndex+= m_iXNum;
				m_bOddFlag = ((m_bOddFlag == TRUE) ? FALSE: TRUE);
			}		
		}
		break;
	default:
		m_iCurIndex++;
	}
	
	return point;
}

void CDeviceData::ReadyToExtract()
{
	switch(m_iStartPos)
	{
	case TOP_LEFT:
		m_iCurIndex = 0;
		break;
	case TOP_RIGHT:
		m_iCurIndex = 0;//m_iXNum;
		break;
	case BOTTOM_LEFT:
		m_iCurIndex = 0;//m_iXNum * (m_iYNum -1);
		break;
	case BOTTOM_RIGHT:
		m_iCurIndex = 0;//m_iXNum * m_iYNum - 1;
		break;
	default:
		m_iCurIndex = 0;
		break;
	}
}

void CDeviceData::CreateDeviceList()
{
	int i, j;
	BOOL bOdd = FALSE;
	CPoint pos;

	if (m_pChip != NULL) {
		delete [] m_pChip;
		m_pChip = NULL;
	}

	m_pChip = new CChip[m_iYNum*m_iXNum];

	double m_Pure_Xpitch2;
	double m_Pure_Ypitch2;

	m_Pure_Xpitch2 = m_dXPitch2 - (m_dXPitch1 * (m_iSmallXNum - 1));
	m_Pure_Ypitch2 = m_dYPitch2 - (m_dYPitch1 * (m_iSmallYNum - 1));
	
	CalculatePitch();

	if(m_bUse2Pitch == TRUE)
	{
		pos.x = long(-m_iNumOfXPitch1 * m_dXPitch1/2 + -m_iNumOfXPitch2 * m_Pure_Xpitch2/2);  // center 기준
		pos.y = long(m_iNumOfYPitch1 * m_dYPitch1/2 + m_iNumOfYPitch2 * m_Pure_Ypitch2/2);  // center 기준

		// 2007.03.14   - 이러면 안되는데... 시간관계상... 고정한다.
		m_iOffsetDirection = 0;

		if (m_iOffsetDirection == 0)
		{	// vertical
			for(i=0; i < m_iYNum; i++)
			{
				for(j=0; j < m_iXNum; j++)
				{
					m_pChip[i*m_iXNum+j].m_offsetX = 0;
					m_pChip[i*m_iXNum+j].m_offsetY = 0;
					m_pChip[i*m_iXNum+j].m_width  = int(m_dChipWidth);
					m_pChip[i*m_iXNum+j].m_height = int(m_dChipHeight);
					
					m_pChip[i*m_iXNum+j].m_position.x = pos.x;
					if (bOdd == TRUE)
					{
						m_pChip[i*m_iXNum+j].m_position.y = long(pos.y + m_dOffset);
					} else
					{
						m_pChip[i*m_iXNum+j].m_position.y = pos.y;					
					}
					
					bOdd = ((bOdd == TRUE)? FALSE: TRUE);
					
					if (j % m_iSmallXNum < m_iSmallXNum - 1 || m_iSmallXNum == 1)
						pos.x += long(m_dXPitch1);
					else // even
						pos.x += long(m_Pure_Xpitch2);
				}
				bOdd = FALSE;  // line 바뀌면 새로 setting
				
				pos.x = long(-m_iNumOfXPitch1 * m_dXPitch1/2 + -m_iNumOfXPitch2 * m_Pure_Xpitch2/2); // Center 기준
				
				if (i % m_iSmallYNum < m_iSmallYNum - 1 || m_iSmallYNum == 1) // odd
					pos.y -= long(m_dYPitch1);
				else // even
					pos.y -= long(m_Pure_Ypitch2);
			}
		} 
		else
		{	// horizontal
			for(j=0; j < m_iXNum; j++)
			{
				for(i=0; i < m_iYNum; i++)
				{
					m_pChip[i*m_iXNum+j].m_offsetX = 0;
					m_pChip[i*m_iXNum+j].m_offsetY = 0;
					m_pChip[i*m_iXNum+j].m_width  = int(m_dChipWidth);
					m_pChip[i*m_iXNum+j].m_height = int(m_dChipHeight);
					
					m_pChip[i*m_iXNum+j].m_position.y = pos.y;
					if (bOdd == TRUE)
					{
						m_pChip[i*m_iXNum+j].m_position.x = long(pos.x + m_dOffset);
					} else
					{
						m_pChip[i*m_iXNum+j].m_position.x = pos.x;
					}
					bOdd = ((bOdd == TRUE)? FALSE: TRUE);
					if (i % m_iSmallYNum < m_iSmallYNum - 1 || m_iSmallYNum == 1) // odd
						pos.y -= long(m_dYPitch1);
					else // even
						pos.y -= long(m_Pure_Ypitch2);
				}
				bOdd = FALSE;  // line 바뀌면 새로 setting

				if (j % m_iSmallYNum < m_iSmallYNum - 1 || m_iSmallYNum == 1)
					pos.x += long(m_dXPitch1);
				else // even
					pos.x += long(m_Pure_Xpitch2);

				pos.y =  long((m_iYNum-1) * m_dYPitch1/2);  // center기준
			}
		}
	} else  // 
	{
		pos.x = long(-(m_iXNum-1) * m_dXPitch1/2);  // center기준
		pos.y = long((m_iYNum-1) * m_dYPitch1/2);  // center기준

		// 2007.03.14   - 이러면 안되는데... 시간관계상... 고정한다.
		m_iOffsetDirection = 0;

		if (m_iOffsetDirection == 0)
		{	// vertical
			for(i=0; i < m_iYNum; i++)
			{
				for(j=0; j < m_iXNum; j++)
				{
					m_pChip[i*m_iXNum+j].m_offsetX = 0;
					m_pChip[i*m_iXNum+j].m_offsetY = 0;
					m_pChip[i*m_iXNum+j].m_width  = int(m_dChipWidth);
					m_pChip[i*m_iXNum+j].m_height = int(m_dChipHeight);
					
					m_pChip[i*m_iXNum+j].m_position.x = pos.x;
					if (bOdd == TRUE)
					{
						m_pChip[i*m_iXNum+j].m_position.y = long(pos.y + m_dOffset);
					} else
					{
						m_pChip[i*m_iXNum+j].m_position.y = pos.y;					
					}
					
					bOdd = ((bOdd == TRUE)? FALSE: TRUE);
					pos.x += long(m_dXPitch1);
				}
				bOdd = FALSE;  // line 바뀌면 새로 setting
				
				// 첫번째 칩 밀려나오는 문제 해결
				pos.x = long(-(m_iXNum-1) * m_dXPitch1/2);  // center기준
				pos.y -= long(m_dYPitch1);
			}
		} 
		else
		{	// horizontal
			for(j=0; j < m_iXNum; j++)
			{
				for(i=0; i < m_iYNum; i++)
				{
					m_pChip[i*m_iXNum+j].m_offsetX = 0;
					m_pChip[i*m_iXNum+j].m_offsetY = 0;
					m_pChip[i*m_iXNum+j].m_width  = int(m_dChipWidth);
					m_pChip[i*m_iXNum+j].m_height = int(m_dChipHeight);
					
					m_pChip[i*m_iXNum+j].m_position.y = pos.y;
					if (bOdd == TRUE)
					{
						m_pChip[i*m_iXNum+j].m_position.x = long(pos.x + m_dOffset);
					} else
					{
						m_pChip[i*m_iXNum+j].m_position.x = pos.x;
					}
					bOdd = ((bOdd == TRUE)? FALSE: TRUE);
					pos.y -= long(m_dYPitch1);
				}
				bOdd = FALSE;  // line 바뀌면 새로 setting

				pos.x += long(m_dXPitch1);
				pos.y = long((m_iYNum-1) * m_dYPitch1/2);  // center기준
			}
		}
	}
}

void CDeviceData::CalculatePitch()
{
	if (m_iSmallXNum == 1) {
		m_iNumOfXPitch1 = m_iXNum - 1;
		m_iNumOfXPitch2 = 0;
	}
	else if (m_iXNum % m_iSmallXNum == 0) {
		m_iNumOfXPitch1 = (m_iXNum / m_iSmallXNum) * (m_iSmallXNum - 1);
		m_iNumOfXPitch2 = m_iXNum / m_iSmallXNum - 1;
	}
	else {
		m_iNumOfXPitch1 = (m_iXNum / m_iSmallXNum) * (m_iSmallXNum - 1) + (m_iXNum % m_iSmallXNum -1);
		m_iNumOfXPitch2 = m_iXNum / m_iSmallXNum;
	}
	
	if (m_iSmallYNum == 1) {
		m_iNumOfYPitch1 = m_iYNum - 1;
		m_iNumOfYPitch2 = 0;
	}
	else if (m_iYNum % m_iSmallYNum == 0) {
		m_iNumOfYPitch1 = (m_iYNum / m_iSmallYNum) * (m_iSmallYNum - 1);
		m_iNumOfYPitch2 = m_iYNum / m_iSmallYNum - 1;
	}
	else {
		m_iNumOfYPitch1 = (m_iYNum / m_iSmallYNum) * (m_iSmallYNum - 1) + (m_iYNum % m_iSmallYNum -1);
		m_iNumOfYPitch2 = m_iYNum / m_iSmallYNum;
	}
}

BOOL CDeviceData::GetIsPartialNoMark()
{
	return m_bIsPartialNoMark;
}

UINT CDeviceData::SetMasterOffset(Vector *ltMasterOffset)
{
	if (m_ltMasterOffset != NULL) {
		delete m_ltMasterOffset;
		m_ltMasterOffset = NULL;
	}

	m_ltMasterOffset = new Vector[m_iYNum * m_iXNum];

	for (int i = 0; i < m_iYNum * m_iXNum; i++) {
		m_ltMasterOffset[i] = ltMasterOffset[i];
	}

	return 0;
}

UINT CDeviceData::SetSlaveOffset(Vector *ltSlaveOffset)
{
	if (m_ltSlaveOffset != NULL) {
		delete m_ltSlaveOffset;
		m_ltSlaveOffset = NULL;
	}

	m_ltSlaveOffset = new Vector[m_iYNum * m_iXNum];

	for (int i = 0; i < m_iYNum * m_iXNum; i++) {
		m_ltSlaveOffset[i] = ltSlaveOffset[i];
	}

	return 0;
}

CChip CDeviceData::GetCurrentChip(int iIndex)
{
	return m_pChip[iIndex];
}

void CDeviceData::SetDeviceType(int m_DeviceType)
{
	m_DeviceType = m_DeviceType;
}

int CDeviceData::GetDeviceType()
{
   return m_DeviceType;
}

void CDeviceData::SetMasterOffset(double m_dmasterX, double m_dmasterY)
{
  m_dMasterX = m_dmasterX;
  m_dMasterY = m_dmasterY;
}

void CDeviceData::SetSlaveOffset(double m_dslaveX, double m_dslaveY)
{
	m_dSlaveX = m_dslaveX;
	m_dSlaveY = m_dslaveY;
}



double CDeviceData::GetMasterX()
{
    return m_dMasterX;
}

double CDeviceData::GetMasterY()
{ 
   return m_dMasterY;
}

double CDeviceData::GetSlaveX()
{
  return m_dSlaveX;
}

double CDeviceData::GetSlaveY()
{
 return m_dSlaveY;
}

int CDeviceData::GetShutterFlag()
{

	return m_iMoveShutter;
}

CString CDeviceManager::Get_StripName()
{
	return m_pDeviceData->GetStripName();
}

int CDeviceData::GetCurrentIndex()
{
	return m_iCurIndex;
}


void CDeviceData::SetFirstIndex(int nFirstIndex)
{
	m_iFirstIndex = nFirstIndex;
}

int CDeviceData::GetFirstIndex()
{
	return m_iFirstIndex;
}



void CDeviceData::SetManualCutWidth(double nManualCutWidth)
{
	m_dManualCutWidth = nManualCutWidth;
}

double CDeviceData::GetManualCutWidth()
{
	return m_dManualCutWidth;
}

void CDeviceData::SetManualCutStep(double nManualCutStep)
{
	m_dManualCutStep = nManualCutStep;
}

double CDeviceData::GetManualCutStep()
{
	return m_dManualCutStep;
}

void CDeviceData::SetManualCutExtend(double nManualCutExtend)
{
	m_dManualCutExtend = nManualCutExtend;
}

double CDeviceData::GetManualCutExtend()
{
	return m_dManualCutExtend;
}
