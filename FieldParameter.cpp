// FieldParameter.cpp: implementation of the CFieldParameter class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "BeamEditor6.h"
#include "FieldParameter.h"
#include "InitialTable.h"

#include "DlgFieldParameter.h"
#include "DlgSPIDualLaser.h"
#include "WriteLog.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFieldParameter::CFieldParameter()
{
	CInitialTable *pInitialTable = pInitialTable->GetInstance();
	m_dFieldSize = pInitialTable->GetFieldSize();
	m_dMMSize = pInitialTable->GetMMSize();
	m_iUnit = pInitialTable->GetUnit();
	m_dFieldAngle = 0;//pInitialTable->GetFieldAngle();
//	int		m_iLensSize;
//	int		m_iDelayTime; // 커팅 전 delay Time 설정
//	CString	m_strFileName;
	m_iMasterX = 0;
	m_iMasterY = 0;
	m_iSlaveX = 0;
	m_iSlaveY = 0;
	m_dKX = 0;
	m_dKY = 0;
	m_dMaxCuttingSize = 200.0; //2019.05.16 Max Cutting Size Default 설정.
	m_dRollSpeed = 0.0;
	m_bEncoderReverse = FALSE;
	m_iSimulationMode = 0;
	m_dSetedPowerValue=0;
	m_iSetCount = 1;
	m_iSimulationSpeed = 1;
	m_bSimulationFlag = FALSE;
	m_dDeviceType = HK_DEVICE;
	m_DBAccessFlag=FALSE;
	m_GroupSameAngle = TRUE;
	m_bLaserWarningDetect=FALSE;
	m_bMaxTextWarning= FALSE;
	m_strUpdateText=_T("");
	m_strAmkorPenFile=_T("");
	m_bSemiteqAutoText = FALSE;
	m_iweekday = 0;
	m_iweekTime = 0;
	m_bChangeText = FALSE;
	m_dMarkingField = 0;
	m_dCycleOffset = 0;
	m_dCycleOffset2 = 0;
	m_dScannerStartPosX = 0;
	m_dScannerStartPosY = 0;

	m_strPartNo = _T("");
	m_strLotNo = _T("");
	m_strRunNo = _T("");
	m_strBinCode = _T("");		
	m_strDevcieCode = _T("");	
	m_strTapFileName = _T("");
	m_strPatternView = "HEAD1";
	m_bAutoHAlign = FALSE;
	m_bAutoVAlign = FALSE;


	for(int i=0;i<10;i++)
	{
	 m_GuideLineBuf[i].left=0;
	 m_GuideLineBuf[i].top=0;
	 m_GuideLineBuf[i].bottom=0;
	 m_GuideLineBuf[i].right=0;
	 m_GuideCheckBuf[i] = FALSE;
	}

	m_bLaserEnable = FALSE;
	m_bLaserPower = FALSE;
	m_bScannerPower = FALSE;

	m_dSloopOfWidth = 0.0;
	m_dSloopOfWidthLeft = 0.0;
	m_dSloopOfWidthRight = 0.0;
	m_dSloopSegmentLeft = 0.0;
	m_dSloopSegmentRight = 0.0;
	m_dExtandLine_widthX_Left = 0.0;;
	m_dExtandLine_widthX_Right = 0.0;;

	m_dAdjustVector = 0;
	m_bPreviewMode = FALSE;

	m_bPatternOfKoem = FALSE;
	m_bUnitShapePreviewMode = true;
	m_bSavePatternImage = false;
	m_bAutoMarkFlag = false;
	m_bDownloadFlag = true;
	m_stPatternDataOfHEAD2.clear();
	m_stPatternDataOfHEAD1.clear();
	

	m_dSpeedScale = 1.0;

	m_dRealSize = 0;
	m_dSampleSize = 0;
	m_dRFieldSize = 0;

	m_nRunMode = 0;
	m_nPatternMode = 0;
	m_BMWPatternData.SetDefaultValue();

	m_LaserStatusHEAD2.clear();
	m_LaserStatusHEAD1.clear();

	
	m_bSkipModeSignalHEAD2 = FALSE;
	m_bSkipModeSignalHEAD1 = FALSE;
}

CFieldParameter::~CFieldParameter()
{

}

CFieldParameter* CFieldParameter::m_pFieldParameter = 0;
CFieldParameter* CFieldParameter::GetInstance() 
{
	if (m_pFieldParameter == 0) {
		m_pFieldParameter = new CFieldParameter;
	}
	return m_pFieldParameter;
}

void CFieldParameter::SetSize(double mmSize, double fieldSize)
{
	m_dMMSize = mmSize;
	m_dFieldSize = fieldSize;
}

void CFieldParameter::GetSize(double *mmSize, double *fieldSize)
{
	//CInitialTable  *pInitalTable = pInitalTable->GetInstance();

	*mmSize = m_dMMSize; //* pInitalTable->GetFieldScale();
	*fieldSize = m_dFieldSize;
}

void CFieldParameter::SetFieldAngle(double fieldAngle)
{
	m_dFieldAngle = fieldAngle;
}

double CFieldParameter::GetFieldAngle()
{
	return m_dFieldAngle;
}

int CFieldParameter::GetUnit()
{
	return m_iUnit;
}

void CFieldParameter::SetUnit(int iUnit)
{
	m_iUnit = iUnit;
}
// 기존 여기서는 field, mm값만을 셋팅하는 기능을 담당하였으나 
// 커팅 시 필요한 몇몇 값들을 같이 가지고 있기로 함
// FieldAngle, Delaytime, LensSize  --> Lens를 제외하고는 원래 커팅창에 있던 부분
// 커팅 창과 분리시키고 단지 값만을 불러다가 사용하도록 여기로 옮김

void CFieldParameter::SetMasterX( double iMasterX)
{
	m_iMasterX = iMasterX;
}

void CFieldParameter::SetMasterY(double iMasterY)
{
	m_iMasterY = iMasterY;
}

void CFieldParameter::SetSlaveX(double iSlaveX)
{
	m_iSlaveX = iSlaveX;
}

void CFieldParameter::SetSlaveY(double iSlaveY)
{
	m_iSlaveY = iSlaveY;
}

double	CFieldParameter::GetMasterX()
{
	return m_iMasterX;
}

double CFieldParameter::GetMasterY()
{
	return m_iMasterY;
}

double CFieldParameter::GetSlaveX()
{
	return m_iSlaveX;
}

double CFieldParameter::GetSlaveY()
{
	return m_iSlaveY;
}

void CFieldParameter::SetSetCount(int iMarkingCount)
{
	m_iSetCount = iMarkingCount;
}

int CFieldParameter::GetSetCount()
{
	return m_iSetCount;
}

void CFieldParameter::IncreaseCount(int iInterval)
{
	m_iMarkedCount += iInterval;
}

void CFieldParameter::InitialCount()
{
	m_iMarkedCount = 0;
}

int	CFieldParameter::GetMarkedCount()
{
	return m_iMarkedCount;
}

void CFieldParameter::SetSimulationSpeed(int iSimulationSpeed)
{
	m_iSimulationSpeed = iSimulationSpeed;
}

int CFieldParameter::GetSimulationSpeed()
{
	return m_iSimulationSpeed;
}

void CFieldParameter::SetSimulationFlag(BOOL m_bsimulation)
{
  m_bSimulationFlag = m_bsimulation;
}

BOOL CFieldParameter::GetSimulationFlag()
{
   return m_bSimulationFlag;
}

CString CFieldParameter::GetAmkorRscFileName()
{
  return m_AmkorRscFileName;
}

void CFieldParameter::SetAmkorRscFileName(CString m_FileName)
{
   m_AmkorRscFileName = m_FileName;
}

void CFieldParameter::SetAmkorPrjFileName(CString m_FileName)
{
   m_AmkorPrjFileName = m_FileName;
}

CString CFieldParameter::GetAmkorPrjFileName()
{
   return m_AmkorPrjFileName;
}


void CFieldParameter::SetSemTextFromDB(CString strText,int strSEQ)
{
	m_SemTextArray[strSEQ] = strText;
}
void CFieldParameter::ClearSemTextBuffer()
{

	for(int i=0;i<100;i++)
	{
		m_SemTextArray[i] =	_T("");
		m_returnedTextBuffer[i] = _T("");
	}
}
CString CFieldParameter::GetSemFileTextFromDB(/*CString strSEM*/int strSEQ)
{
	//if(m_SemTextArray[strSEQ) != _T(""))
	return	m_SemTextArray[strSEQ];

	/*int matchIndex=0;
	BOOL matchFlag=false;
	CString returnstr;
	strSEM.TrimLeft();
	strSEM.TrimRight(); 
	for(int i=1; i<100;i++)
	{
		if(m_SemTextArray[i] == strSEM)
		{
			returnstr = strSEM;
			matchFlag = true;
			break;

		}
		else
		{
			if(m_SemTextArray[i] != _T("") )
			{
				
					returnstr = m_SemTextArray[i];
				
			}
			matchFlag = false;
			
		}
	}
	*/
	//CString strTmp;
	//strTmp = returnstr;
//	for(int j = 0;j < 100;j++)
//	{
//		//if(m_SemTextArray[
//	}
		
	//if(matchFlag == true)
	//	return strSEM;
	//else
		
	//return returnstr;
}

int CFieldParameter::GetDeviceType()
{
	return m_dDeviceType;
}

void CFieldParameter::SetDeviceType(int m_DeviceType)
{
	m_dDeviceType = m_DeviceType;
}

void CFieldParameter::SetSetedPowerValue(double m_SedtedPower)
{
	m_dSetedPowerValue = m_SedtedPower;
}

double CFieldParameter::GetSetedPowerValue()
{
	return m_dSetedPowerValue;
}


void CFieldParameter::SetSelectAllFlag(BOOL m_selectFlag)
{
	m_SelectAllFlag = m_selectFlag;

}


BOOL CFieldParameter::GetSelectAllFlag()
{
   return m_SelectAllFlag;
}

void CFieldParameter::SetAmkPreBuf(int index, CString m_data)
{
	m_AmkPreSelBuffer[index] = m_data;
}

CString CFieldParameter::GetAmkPreBuf(int index)
{
   return m_AmkPreSelBuffer[index];
}

void CFieldParameter::SetZeroArea(CPoint m_area, int index)
{ 
   m_ZeroArea[index] = m_area;
}

CPoint CFieldParameter::GetZeroArea(int index)
{
    return m_ZeroArea[index];
}


void CFieldParameter::SetGuideLineSet(CDRect m_Guide, int index)
{
  m_GuideLineBuf[index].left = m_Guide.left;
  m_GuideLineBuf[index].right = m_Guide.right;
  m_GuideLineBuf[index].top = m_Guide.top;
  m_GuideLineBuf[index].bottom = m_Guide.bottom;
  
  
}


CDRect CFieldParameter::GetGuideLineValue(int index)
{
	if(m_GuideLineBuf == NULL)
	{
		m_GuideLineBuf[index].left = 0;
		m_GuideLineBuf[index].right = 0;
		m_GuideLineBuf[index].top = 0;
		m_GuideLineBuf[index].bottom = 0;
	}
	return m_GuideLineBuf[index];
}

BOOL CFieldParameter::GetGuideCheck(int index)
{
 return m_GuideCheckBuf[index];
}

void CFieldParameter::SetGuideCheck(int index,BOOL cflag)
{
    m_GuideCheckBuf[index] = cflag;
}

CRect CFieldParameter::GetGroupObjRect()
{
  return m_objRect;
}

void CFieldParameter::SetGroupFlag(BOOL m_flag)
{
  	m_bGroupFlag = m_flag;
} 

BOOL CFieldParameter::GetGroupFlag()
{
   return m_bGroupFlag;
}

void CFieldParameter::SetGroupObjRect(CRect m_rect)
{
    m_objRect= m_rect;
}

void CFieldParameter::SetDBAccessFlag(BOOL m_DBFlag)
{
   m_DBAccessFlag = m_DBFlag;
}

BOOL CFieldParameter::GetDBAccessFlag()
{
   return m_DBAccessFlag;
}

void CFieldParameter::SetGroupSameAngle(BOOL m_flag)
{ 
	m_GroupSameAngle = m_flag;

}


BOOL CFieldParameter::GetGroupSameAngle()
{
	return m_GroupSameAngle;

}

void CFieldParameter::SetChangeText(BOOL m_flag)
{
   m_bChangeText = m_flag;
}


BOOL CFieldParameter::GetChangeText()
{
   return m_bChangeText;
}

CString CFieldParameter::GetUpdateText()
{
   return m_strUpdateText;
}

void CFieldParameter::SetUpdateText(CString m_strText)
{
	m_strUpdateText = m_strText;
}

void CFieldParameter::SetLaserWarning(BOOL m_warning)
{ 
    m_bLaserWarningDetect = m_warning;
}

BOOL CFieldParameter::GetLaserWarning()
{
	return m_bLaserWarningDetect;
}

void CFieldParameter::SetMaxTextLimitWarning(BOOL m_flag)
{
	m_bMaxTextWarning = m_flag;
}

BOOL CFieldParameter::GetMaxTextWarning()
{
   return m_bMaxTextWarning;
} 

void CFieldParameter::SetAmkorPenFileName(CString m_strPenName)
{

	m_strAmkorPenFile = m_strPenName;
}

CString CFieldParameter::GetAmkorPenFileName()
{
  return m_strAmkorPenFile;
}

void CFieldParameter::SetSemiteqAutoText(BOOL m_flag)
{
   m_bSemiteqAutoText = m_flag;
} 

BOOL CFieldParameter::GetSemiteqAutoText()
{
	return m_bSemiteqAutoText;

}

void CFieldParameter::SetWeekCodeString(CString strWeekCode)
{
	m_strWeekCode = strWeekCode;
}

CString CFieldParameter::GetWeekCodeString(int m_iday, int m_itime)
{
	CSize size;
	CInitialTable *pInitialTable = pInitialTable->GetInstance();
	BOOL weekcode = FALSE; // 주코드인지
	BOOL isExistWeek = FALSE; // obj 중에서 주코드가 존재
	CString tempStr("");
    CString m_strHead1Name;
	m_strHead1Name = pInitialTable->GetHead1Name();

	CString SetWeekStr(""); // 주코드 최종 String
	CTime time = CTime::GetCurrentTime(); 
	int yy = time.GetYear() - 2000; 

	int m_iHour, m_iMin, m_iDay;
	m_iHour = 0; m_iMin = 0;
	m_iHour = GetWeekTime() / 100; 
	m_iMin  = GetWeekTime() % 100;
	m_iDay  = GetWeekDay(); 

	CTime tmFrom(time.GetYear(),01,01,m_iHour,m_iMin,00); // 기준에 되는 날짜
	CTime tmFrom2(time.GetYear()-1,01,01,0,00,00); // 지난 해의 기준일
	CTime tmTempFrom(time.GetYear()-1,12,31,0,00,00); // 지난 해 마지막 날
	CTime tmFirst(time.GetYear(),01,02,00,00,00);			// 1월 1일의 경우 무조건 2일로 설정	
	int MakeNextWeek = 0; // 다음주를 1주로 만들기 위해 더해야하는 날수
	CTimeSpan  tmSpn; // 기준시부터 경과 시간
	int NumberOfCase = 0;
	int Year;
	CString tempYear("");
	BOOL RemainOfLastYear = FALSE; // 지난달로 넘어갈것인지 (In case of 금토일)
	BOOL m_isBeforeSix = FALSE;
	int ObjStrLength = 0;
	CString Buffer("");
	int NumberOfY = 0;
	int tempTime;
	int StartDayOfWeek = tmFrom.GetDayOfWeek()-1; // 1月1日의 요일 알아오기
	int StartDayOfWeek_LastYear = tmFrom2.GetDayOfWeek(); // 지난해의 1月1日의 요일 알아오기

	CString strYear2, strYear1, strMon, strWeek;
	
	if(StartDayOfWeek > 1)	
		RemainOfLastYear = TRUE;	
	if(m_iDay == -1)
		m_iDay = 1;//선택안하면 월요일 기준.

	// 1월 1일의 요일을 목요일 기준으로 바꾸기
	if (StartDayOfWeek >= m_iDay && StartDayOfWeek <= 7) 
	{
		StartDayOfWeek -= m_iDay;
		StartDayOfWeek_LastYear -= m_iDay;
	}
	else 
	{
		StartDayOfWeek += (7 - m_iDay);
		StartDayOfWeek_LastYear += (7 - m_iDay);
	}
	
	if (time.GetMonth() == 1 && time.GetDay() == 1)	
		time = tmFirst;	

	tmSpn = time - tmFrom;
	NumberOfCase = 4;	// 경우의 수 나누기 (4 case) end	

	if (tmSpn < 0) 
	{
		m_isBeforeSix = TRUE;
		tmSpn = (time + tmSpn) - tmFrom2;
	}

	// 기준일로 부터 현재 주 구해오기
	tempTime = tmSpn.GetDays();
	if (NumberOfCase == 1 || NumberOfCase == 4) 
	{
		tempTime += StartDayOfWeek;
	}
	tempTime /= 7;
	tempTime++;

	if(tempTime > 1)
		tempTime--;
	else
	{
		tempTime = 52;
		m_isBeforeSix = TRUE;
	}

	// 주 표현하기 start
	int m_tempWeek = 0;
	int index = m_weekcodeselectpara;
	if(index == 5 || index == 6)
	{
		if(tempTime > 0 && tempTime > 3)
		{
//			m_tempWeek =  (tempTime / 3)+1;	
			if(tempTime%3 == 1)	
				m_tempWeek = tempTime;	
			else if(tempTime%3 == 2)	
				m_tempWeek = tempTime - 1;	
			else
				m_tempWeek = tempTime - 2;
		}

		else
			m_tempWeek = 1;

		tempTime = m_tempWeek;
	}

	CString m_stempTime;
	CString m_stempZero; // 주가 한자리일 경우 앞자리에 0포함
	m_stempZero.Format("%d", 0); 
	m_stempTime.Format("%d", tempTime);
	if (m_stempTime.GetLength() == 1) 
	{
		m_stempZero += m_stempTime;
		m_stempTime = m_stempZero;
	}
	if ((RemainOfLastYear == TRUE && (StartDayOfWeek + time.GetDay()) <= 7 && time.GetMonth() == 1) || m_isBeforeSix == TRUE) {
		Year = tmTempFrom.GetYear();
	}
	else {
		Year = time.GetYear();
	}

	//년도가 두자리일경우
	tempYear.Format("%d", Year);
	tempYear = tempYear.Right(2); 
	
	//년도가 한자리일경우
	int intTempYear;
	intTempYear = atoi(tempYear);
	CString strWeekCode;

	//주코드 3종류표현 (YYWW:0601, YWW:601, YWW:Z01)
	int Yearchar=64; //2007년도부터 'A' 시작

	switch(index) 
	{
	case 3: // YWW:U01
//		tempYear.Format("%d", intTempYear);	
		tempYear=tempYear.Right(1);	
		if(m_strHead1Name.GetLength() > 1)
			strWeekCode.Format("%s%s%s", m_strHead1Name,tempYear, m_stempTime);
		else
			strWeekCode.Format("%s%s",tempYear, m_stempTime);
		break;

	case 4: // YYWW:U0601
		if(m_strHead1Name.GetLength() > 1)
			strWeekCode.Format("%s%s%s", m_strHead1Name,tempYear, m_stempTime);
		else
			strWeekCode.Format("%s%s",tempYear, m_stempTime);
		break;

	case 5: // Y3W:U601
//		tempYear.Format("%d", intTempYear);	
		tempYear=tempYear.Right(1);	
		if(m_strHead1Name.GetLength() > 1)
			strWeekCode.Format("%s%s%s", m_strHead1Name,tempYear, m_stempTime);
		else
			strWeekCode.Format("%s%s",tempYear, m_stempTime);
		break;

	case 6: // YY3W:U0601
		if(m_strHead1Name.GetLength() > 1)
			strWeekCode.Format("%s%s%s", m_strHead1Name,tempYear, m_stempTime);
		else
			strWeekCode.Format("%s%s",tempYear, m_stempTime);
		break;

	case 10:
		if(m_strHead1Name.GetLength() > 1)
			strWeekCode.Format("%s%s", m_strHead1Name, m_stempTime);
		else
			strWeekCode.Format("%s", m_stempTime);
		break;

		// 2007.07.06  
	case 19: // YMDD:U7A01
		// 10월=A , 11월=B , 12월=C
//		tempYear.Format("%d", intTempYear);	
		tempYear=tempYear.Right(1);	
		strMon.Format("%X", time.GetMonth());
		if(m_strHead1Name.GetLength() > 1)
			strWeekCode.Format("%s%s%s%s", m_strHead1Name, tempYear, strMon, m_stempTime);
		else
			strWeekCode.Format("%s%s%s", tempYear, strMon, m_stempTime);

	case 33:	//YM:6B
//		Y = Assembly Year(0,1,2,3,4,5,6,7,8,9) example 2009 = 9, 
//		M = Assembly Month (1,2,3,4,5,6,7,8,9,A,B,C), example 10월 = A , 7월= 7
		tempYear=tempYear.Right(1);
		strMon.Format("%X", time.GetMonth());
		strWeekCode.Format("%s%s", tempYear, strMon);
		break;
	}
	
	m_strWeekCode=strWeekCode;
	return m_strWeekCode;
}

void CFieldParameter::SetWeekDay(int m_iday)
{
  m_iweekday = m_iday;
}

int  CFieldParameter::GetWeekDay()
{
 return m_iweekday;
}

void CFieldParameter::SetWeekTime(int m_iweektime)
{
   m_iweekTime = m_iweektime;
}

int  CFieldParameter::GetWeekTime()
{
	return m_iweekTime;
}

void CFieldParameter::WeekcodeIndex(int weekcodepara)
{
//	CTabMarking *tabmarking;
	m_weekcodeselectpara = weekcodepara;
//	tabmarking->SetWeekcodeindex(m_weekcodeselectpara);
}

// 2007.06.15  
void CFieldParameter::SetLotNoAC(CString m_strData)
{
	m_strLotNoAC = m_strData;
}

void CFieldParameter::SetPartNo(CString m_strData)
{
 m_strPartNo = m_strData;
}

CString CFieldParameter::GetPartNo()
{
return m_strPartNo;
}

void CFieldParameter::SetLotNo(CString strData)
{
 m_strLotNo = strData;
}

CString CFieldParameter::GetLotNo()
{
return m_strLotNo;
}

// 2007.06.15  
CString CFieldParameter::GetLotNoAC()
{
return m_strLotNoAC;
}

void CFieldParameter::SetRunNo(CString strData)
{
   m_strRunNo = strData;
}

CString CFieldParameter::GetRunNo()
{
 return m_strRunNo;
}

CString CFieldParameter::GetAutoDisplaceLotNo(CString strIndex)
{
 CBeamEditor6App* pApp = (CBeamEditor6App *)AfxGetApp(); 
 CString m_strText =_T("");
 for(int i=0; i< 255; i++){
     if(pApp->m_strLotNo_DisplaceIndex[i] == strIndex){
		 m_strText = pApp->m_strLotNo_DisplaceText[i];
		 break;
	 }
 }
 return m_strText;
}

// 2007.01.12   - issue (Amic)
CString CFieldParameter::GetIssueWeekcode()
{
	return m_strIssueWeekCode;
}

// 2007.03.13   - lot count
CString CFieldParameter::GetLotCountcode()
{
	return m_strLotCountCode;
}

// 2007.01.12   - split
CString CFieldParameter::GetSplitWeekcode()
{
	return m_strSplitWeekCode;
}

// 2007.01.12   - issue (Amic)
void CFieldParameter::SetIssueWeekCodeString(CString m_strWeekcode)
{
	m_strIssueWeekCode = m_strWeekcode;
}

// 2007.01.12   - split
void CFieldParameter::SetSplitWeekCodeString(CString m_strWeekcode)
{
	m_strSplitWeekCode = m_strWeekcode;
}

// 2007.03.13   - lot count
// 2007.04.11   - 입력형식 수정 (@D : P/N, @N : Number, Etc : Char)
void CFieldParameter::SetLotCountCodeString(int count, CString format)
{
	int i;
	int n_cnt = 0;
	int p_cnt = 0;
	int len = 0;

	CString strP = "";
	CString strN = "";
	CString strTmp = "";
	CString strReturn = "";

	for (i = 0; i < format.GetLength(); i++)
	{
		if (format.GetAt(i) != '@')
			len++;
	}

	for (i = 0; i < format.GetLength(); i++)
	{
		if (format.GetAt(i) == '@' && format.GetAt(i+1) == 'N')
			n_cnt++;

		if (format.GetAt(i) == '@' && format.GetAt(i+1) == 'D')
			p_cnt++;
	}

	//m_strPartNo = "TESTTEST";

	strP = m_strPartNo;
	if (m_strPartNo.GetLength() < p_cnt)
	{
		strP = m_strPartNo;
		for (i = m_strPartNo.GetLength(); i < p_cnt; i++)
		{
			strP += '_';
		}
	}
	else
	{
		strP = m_strPartNo;
	}

	strTmp.Format("%d", count);
	if (strTmp.GetLength() < n_cnt)
	{
		for (i = strTmp.GetLength(); i < n_cnt; i++)
		{
			strN += '0';
		}
		strN += strTmp;
	}
	else
	{
		strN = strTmp;
	}

	n_cnt = 0;
	p_cnt = 0;

	for (i = 0; i < format.GetLength(); i++)
	{
		if (format.GetAt(i) == '@' && format.GetAt(i+1) == 'D')
		{
			strReturn += strP.GetAt(p_cnt++);
			i++;
		}
		else if (format.GetAt(i) == '@' && format.GetAt(i+1) == 'N')
		{
			strReturn += strN.GetAt(n_cnt++);
			i++;
		}
		else
		{
			strReturn += format.GetAt(i);
		}
	}

	m_strLotCountCode = strReturn;
}

void CFieldParameter::SetAutoHAlignment(BOOL m_flag)
{
	m_bAutoHAlign = m_flag;
	
}

BOOL CFieldParameter::GetAutoHAlignment()
{
  return m_bAutoHAlign;
}

void CFieldParameter::SetAutoVAlignment(BOOL m_flag)
{
  m_bAutoVAlign = m_flag;
}

BOOL CFieldParameter::GetAutoVAlignment()
{
 return m_bAutoVAlign;
}

void CFieldParameter::SetBinCode(CString strData)	
{
	m_strBinCode = strData;	
}

void CFieldParameter::SetDeviceCode(CString strData)	
{
	m_strDevcieCode = strData;
}

CString CFieldParameter::GetBinCode()	
{
	return m_strBinCode;
}

CString CFieldParameter::GetDeviceCode()	
{
	return m_strDevcieCode;
}

void CFieldParameter::SetPatternView(CString strData)	
{
	m_strPatternView = strData;
}

CString CFieldParameter::GetPatternView()
{
	return m_strPatternView;
}

CString CFieldParameter::GetYMD()
{
	CString strY = "", strM = "", strD = "", strYMD = "";
	CTime time = CTime::GetCurrentTime(); 
	int yy = time.GetYear() - 2000; 
	int mm = time.GetMonth();
	int dd = time.GetDay();

	strY.Format("%c", yy + 'I' - 13);
	strM.Format("%c", mm + 'A' - 1);
	if(dd <= 26)
		strD.Format("%c", dd + 'A' - 1);
	else
		strD.Format("%d", dd - 26);

	strYMD = strY + strM + strD;

	return strYMD;
}

void CFieldParameter::SetLaserPowerSig(BOOL bFlag)
{
	m_bLaserPower = bFlag;
}

BOOL CFieldParameter::GetLaserPowerSig()
{
	return m_bLaserPower;
}

void CFieldParameter::SetScannerPowerSig(BOOL bFlag)
{	
	m_bScannerPower = bFlag;
}

BOOL CFieldParameter::GetScannerPowerSig()
{	
	return m_bScannerPower;
}

void CFieldParameter::SetLaserEnableSig(BOOL bFlag)
{
	m_bLaserEnable = bFlag;
}

BOOL CFieldParameter::GetLaserEnableSig()
{
	return m_bLaserEnable;
}


void CFieldParameter::SetSkipModeHEAD2(BOOL bFlag)
{
	m_bSkipModeSignalHEAD2 = bFlag;
}

BOOL CFieldParameter::GetSkipModeHEAD2()
{
	return m_bSkipModeSignalHEAD2;
}


void CFieldParameter::SetSkipModeHEAD1(BOOL bFlag)
{
	m_bSkipModeSignalHEAD1 = bFlag;
}

BOOL CFieldParameter::GetSkipModeHEAD1()
{
	return m_bSkipModeSignalHEAD1;



}



double CFieldParameter::GetHEAD1LaserPower()
{
	return m_LaserStatusHEAD1.dHEAD1_LASER_ACTIVE_POWER;
}

void CFieldParameter::SetHead1LaserPower(double power)
{
	m_LaserStatusHEAD1.dHEAD1_LASER_ACTIVE_POWER = power;
}


double CFieldParameter::GetHEAD2LaserPower()
{
	return m_LaserStatusHEAD2.dHEAD2_LASER_ACTIVE_POWER;
}

void CFieldParameter::SetHead2LaserPower(double power)
{
	m_LaserStatusHEAD2.dHEAD2_LASER_ACTIVE_POWER = power;
}










void CFieldParameter::SetFileName(CString strFileName)
{
	m_strFileName = strFileName;
}


CString CFieldParameter::GetFileName()
{
	return m_strFileName;
}



void CFieldParameter::SetSloopWidth(double dSloopWidth)
{
	m_dSloopOfWidth = dSloopWidth;
	m_stPatternDataOfHEAD2.dSloopWidth = dSloopWidth;
}


double CFieldParameter::GetSloopWidth()
{
	return m_stPatternDataOfHEAD2.dSloopWidth;//m_dSloopOfWidth;
}



void CFieldParameter::SetPreviewMode(bool bPreview)
{
	m_bPreviewMode = bPreview;
}


bool CFieldParameter::GetPreViewMode(void)
{
	return m_bPreviewMode;
}


void CFieldParameter::SetPatternOfKoem(bool bKoemPattern)
{
	m_bPatternOfKoem = bKoemPattern;

}




bool CFieldParameter::GetPatternOfKoem(void)
{
	return m_bPatternOfKoem;
}




int CFieldParameter::SetHEAD2PatternData(_NOTCH_PATTERN_DATA KOEM_PATTERN_DATA)
{
	m_stPatternDataOfHEAD2 = KOEM_PATTERN_DATA;
	
	/*
	CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();;CString strLogEvent = TEXT("");
	strLogEvent.Format("--------------------Set HEAD2 PatternData--------------------");
	strLogEvent.Format("NonflagStartHeight : %.2f",KOEM_PATTERN_DATA.dNonflagStartHeight));
	strLogEvent.Format("NublessRegion  : %.2f",KOEM_PATTERN_DATA.dNublessRegion ));

	strLogEvent.Format("NublessHeight   : %.2f",KOEM_PATTERN_DATA.dNublessHeight  ));
	strLogEvent.Format("NotchRoot   : %.2f",KOEM_PATTERN_DATA.dNotchRoot  ));
	strLogEvent.Format("TabWidth   : %.2f",KOEM_PATTERN_DATA.dTabWidth  ));
	strLogEvent.Format("FlagCount   : %.2f",KOEM_PATTERN_DATA.dTabCount  ));
	strLogEvent.Format("TabLenth   : %.2f",KOEM_PATTERN_DATA.dBuriedRegion   ));
	strLogEvent.Format("BuriedHeight    : %.2f",KOEM_PATTERN_DATA.dBuriedHeight  ));
	strLogEvent.Format("NonflagEndWidth   : %.2f",KOEM_PATTERN_DATA.dNonflagEndWidth  ));
	strLogEvent.Format("NonflagEndHeight   : %.2f",KOEM_PATTERN_DATA.dNonflagEndHeight  ));
	strLogEvent.Format("FlagSlope   : %.2f",KOEM_PATTERN_DATA.dTabAngle  ));
	strLogEvent.Format("FoilExtention   : %.2f",KOEM_PATTERN_DATA.dFoilExtention  ));
	strLogEvent.Format("HEAD2Width   : %.2f",KOEM_PATTERN_DATA.dHEAD2Width  ));
	strLogEvent.Format("TabStartWidth   : %.2f",KOEM_PATTERN_DATA.dFlagStartWidth  ));
	strLogEvent.Format("FlagVariableStartLength   : %.2f",KOEM_PATTERN_DATA.dFlagVariableStartLength  ));
	strLogEvent.Format("FlagVariableEndLength    : %.2f",KOEM_PATTERN_DATA.dFlagVariableEndLength   ));
	strLogEvent.Format("FlagVariableTotalLength    : %.2f",KOEM_PATTERN_DATA.dFlagVariableTotalLength   ));
	strLogEvent.Format("--------------------Set HEAD2 PatternData--------------------");
	*/
	//CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();;CString strLogEvent = TEXT("");
	//strLogEvent.Format(_T("HEAD2 h %lf -> %lf"),m_stPatternDataOfHEAD1.dTabWidth ,numberdlg.GetResultDouble());pMainFrm->AddLogData(strLogEvent);

	return 0;
}

int CFieldParameter::SetHEAD1PatternData(_NOTCH_PATTERN_DATA koemPatternData)
{
	m_stPatternDataOfHEAD1 = koemPatternData;
	
	/*
	CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();;CString strLogEvent = TEXT("");
	strLogEvent.Format("--------------------Set HEAD1 PatternData--------------------");
	strLogEvent.Format("NonflagStartHeight : %.2f",koemPatternData.dNonflagStartHeight));
	strLogEvent.Format("NublessRegion  : %.2f",koemPatternData.dNublessRegion ));

	strLogEvent.Format("NublessHeight   : %.2f",koemPatternData.dNublessHeight  ));
	strLogEvent.Format("NotchRoot   : %.2f",koemPatternData.dNotchRoot  ));
	strLogEvent.Format("TabWidth   : %.2f",koemPatternData.dTabWidth  ));
	strLogEvent.Format("FlagCount   : %.2f",koemPatternData.dTabCount  ));
	strLogEvent.Format("TabLenth   : %.2f",koemPatternData.dBuriedRegion   ));
	strLogEvent.Format("BuriedHeight    : %.2f",koemPatternData.dBuriedHeight  ));
	strLogEvent.Format("NonflagEndWidth   : %.2f",koemPatternData.dNonflagEndWidth  ));
	strLogEvent.Format("NonflagEndHeight   : %.2f",koemPatternData.dNonflagEndHeight  ));
	strLogEvent.Format("FlagSlope   : %.2f",koemPatternData.dTabAngle  ));
	strLogEvent.Format("FoilExtention   : %.2f",koemPatternData.dFoilExtention  ));
	strLogEvent.Format("HEAD2Width   : %.2f",koemPatternData.dHEAD2Width  ));
	strLogEvent.Format("TabStartWidth   : %.2f",koemPatternData.dFlagStartWidth  ));
	strLogEvent.Format("FlagVariableStartLength   : %.2f",koemPatternData.dFlagVariableStartLength  ));
	strLogEvent.Format("FlagVariableEndLength    : %.2f",koemPatternData.dFlagVariableEndLength   ));
	strLogEvent.Format("FlagVariableTotalLength    : %.2f",koemPatternData.dFlagVariableTotalLength   ));
	strLogEvent.Format("--------------------Set HEAD1 PatternData--------------------");

	*/
	/*
	strLogEvent.Format("Flag Power : %d",(int)pParammeter->GetFlagPower()));
	strLogEvent.Format("Flag Ext Speed : %d",(int)pParammeter->GetFlagExtSpeed()));
	strLogEvent.Format("Flag Ext Power : %d",(int)pParammeter->GetFlagExtPower()));
	strLogEvent.Format("Flag Jump Speed : %d",(int)pParammeter->GetFlagJumpSpeed()));
	strLogEvent.Format("Flag Ext Length : %d",(int)pParammeter->GetFlagExtLen()));
	strLogEvent.Format("NonFlag Line Speed : %d",(int)pParammeter->GetUnflagLineSpeed()));
	strLogEvent.Format("NonFlag Line Ext Speed : %d",(int)pParammeter->GetNonFlagLineExtSpeed()));
	strLogEvent.Format("NonFlag Line Ext Length : %d",(int)pParammeter->GetNonFlagLineExtLen()));
	strLogEvent.Format("NonFlag Line Power : %d",(int)pParammeter->GetUnflagPower()));
	strLogEvent.Format("NonFlag Inout Speed : %d",(int)pParammeter->GetUnflagInoutSpeed()));
	strLogEvent.Format("NonFlag Inout Ext Speed : %d",(int)pParammeter->GetUnFlagInoutExtSpeed()));
	strLogEvent.Format("NonFlag Inout Ext Length : %d",(int)pParammeter->GetNonFlagExtLen()));
	strLogEvent.Format("NonFlag Inout Power : %d",(int)pParammeter->GetUnflagInoutPower()));
	strLogEvent.Format("NonFlag Line Speed : %d",(int)pParammeter->GetUnflagLineSpeed()));
	strLogEvent.Format("NonFlag Jump Speed : %d",(int)pParammeter->GetJumpSpeed()));
	strLogEvent.Format("Laser On Delay : %d",(int)pParammeter->GetLaserOnDelay()));
	strLogEvent.Format("Laser Off Delay : %d",(int)pParammeter->GetLaserOffDelay()));
	strLogEvent.Format("Mark Delay : %d",(int)pParammeter->GetMarkDelay()));
	strLogEvent.Format("Polygon Delay : %d",(int)pParammeter->GetStrokeDelay()));
	strLogEvent.Format("Jump Delay : %d",(int)pParammeter->GetJumpDelay()));
	strLogEvent.Format("--------------------Laser Parameter Save--------------------");
	*/

	return 0;
}


_NOTCH_PATTERN_DATA CFieldParameter::GetHEAD2PatternDataOfKoem(void)
{
	/*
	CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();;CString strLogEvent = TEXT("");
	strLogEvent.Format("--------------------Get HEAD2 PatternData--------------------");
	strLogEvent.Format("NonflagStartHeight : %.2f",m_stPatternDataOfHEAD2.dNonflagStartHeight));
	strLogEvent.Format("NublessRegion  : %.2f",m_stPatternDataOfHEAD2.dNublessRegion ));

	strLogEvent.Format("NublessHeight   : %.2f",m_stPatternDataOfHEAD2.dNublessHeight  ));
	strLogEvent.Format("NotchRoot   : %.2f",m_stPatternDataOfHEAD2.dNotchRoot  ));
	strLogEvent.Format("TabWidth   : %.2f",m_stPatternDataOfHEAD2.dTabWidth  ));
	strLogEvent.Format("FlagCount   : %.2f",m_stPatternDataOfHEAD2.dTabCount  ));
	strLogEvent.Format("TabLenth   : %.2f",m_stPatternDataOfHEAD2.dBuriedRegion   ));
	strLogEvent.Format("BuriedHeight    : %.2f",m_stPatternDataOfHEAD2.dBuriedHeight  ));
	strLogEvent.Format("NonflagEndWidth   : %.2f",m_stPatternDataOfHEAD2.dNonflagEndWidth  ));
	strLogEvent.Format("NonflagEndHeight   : %.2f",m_stPatternDataOfHEAD2.dNonflagEndHeight  ));
	strLogEvent.Format("FlagSlope   : %.2f",m_stPatternDataOfHEAD2.dTabAngle  ));
	strLogEvent.Format("FoilExtention   : %.2f",m_stPatternDataOfHEAD2.dFoilExtention  ));
	strLogEvent.Format("HEAD2Width   : %.2f",m_stPatternDataOfHEAD2.dHEAD2Width  ));
	strLogEvent.Format("TabStartWidth   : %.2f",m_stPatternDataOfHEAD2.dFlagStartWidth  ));
	strLogEvent.Format("FlagVariableStartLength   : %.2f",m_stPatternDataOfHEAD2.dFlagVariableStartLength  ));
	strLogEvent.Format("FlagVariableEndLength    : %.2f",m_stPatternDataOfHEAD2.dFlagVariableEndLength   ));
	strLogEvent.Format("FlagVariableTotalLength    : %.2f",m_stPatternDataOfHEAD2.dFlagVariableTotalLength   ));
	strLogEvent.Format("--------------------Get HEAD2 PatternData--------------------");
	*/
	return m_stPatternDataOfHEAD2;
}

_NOTCH_PATTERN_DATA CFieldParameter::GetHEAD1PatternDataOfKoem(void)
{
	/*
	CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();;CString strLogEvent = TEXT("");
	strLogEvent.Format("--------------------Get HEAD1 PatternData--------------------");
	strLogEvent.Format("NonflagStartHeight : %.2f",m_stPatternDataOfHEAD1.dNonflagStartHeight));
	strLogEvent.Format("NublessRegion  : %.2f",m_stPatternDataOfHEAD1.dNublessRegion ));

	strLogEvent.Format("NublessHeight   : %.2f",m_stPatternDataOfHEAD1.dNublessHeight  ));
	strLogEvent.Format("NotchRoot   : %.2f",m_stPatternDataOfHEAD1.dNotchRoot  ));
	strLogEvent.Format("TabWidth   : %.2f",m_stPatternDataOfHEAD1.dTabWidth  ));
	strLogEvent.Format("FlagCount   : %.2f",m_stPatternDataOfHEAD1.dTabCount  ));
	strLogEvent.Format("TabLenth   : %.2f",m_stPatternDataOfHEAD1.dBuriedRegion   ));
	strLogEvent.Format("BuriedHeight    : %.2f",m_stPatternDataOfHEAD1.dBuriedHeight  ));
	strLogEvent.Format("NonflagEndWidth   : %.2f",m_stPatternDataOfHEAD1.dNonflagEndWidth  ));
	strLogEvent.Format("NonflagEndHeight   : %.2f",m_stPatternDataOfHEAD1.dNonflagEndHeight  ));
	strLogEvent.Format("FlagSlope   : %.2f",m_stPatternDataOfHEAD1.dTabAngle  ));
	strLogEvent.Format("FoilExtention   : %.2f",m_stPatternDataOfHEAD1.dFoilExtention  ));
	strLogEvent.Format("HEAD2Width   : %.2f",m_stPatternDataOfHEAD1.dHEAD2Width  ));
	strLogEvent.Format("TabStartWidth   : %.2f",m_stPatternDataOfHEAD1.dFlagStartWidth  ));
	strLogEvent.Format("FlagVariableStartLength   : %.2f",m_stPatternDataOfHEAD1.dFlagVariableStartLength  ));
	strLogEvent.Format("FlagVariableEndLength    : %.2f",m_stPatternDataOfHEAD1.dFlagVariableEndLength   ));
	strLogEvent.Format("FlagVariableTotalLength    : %.2f",m_stPatternDataOfHEAD1.dFlagVariableTotalLength   ));
	strLogEvent.Format("--------------------Get HEAD1 PatternData--------------------");
	*/
	return m_stPatternDataOfHEAD1;
}

int CFieldParameter::SetSDIPatternDataHEAD1(_SDI_NOTCH_PATTERN_DATA PatternData)
{
	m_stSDIPatternDataHEAD1 = PatternData;
	return 0;
}

int CFieldParameter::SetSDIPatternDataHEAD2(_SDI_NOTCH_PATTERN_DATA PatternData)
{
	m_stSDIPatternDataHEAD2 = PatternData;
	return 0;
}


_SDI_NOTCH_PATTERN_DATA CFieldParameter::GetSDIPatternDataHEAD1(void)
{
	return m_stSDIPatternDataHEAD1;
}


_SDI_NOTCH_PATTERN_DATA CFieldParameter::GetSDIPatternDataHEAD2(void)
{
	return m_stSDIPatternDataHEAD2;
}


_POCKET_TMP_DATA_ CFieldParameter::GetPocketPatternParameterData(void)
{
	return m_stParameterData;
}

int CFieldParameter::SetPocketPatternParameterData(_POCKET_TMP_DATA_ data)
{
	m_stParameterData = data;
	return 0;
}

FieldParameter CFieldParameter::GetFieldParameterData(void)
{
	return m_fieldSettingParameter;
}

int CFieldParameter::SetFieldParameterData(FieldParameter FieldData)
{
	m_fieldSettingParameter = FieldData;
	return 0;
}

void CFieldParameter::SetUnitShapePreview(bool bUnisSahpeView)
{
	m_bUnitShapePreviewMode = bUnisSahpeView;
}


bool CFieldParameter::GetUnitSahpePreview(void)
{
	//return true;
	return m_bUnitShapePreviewMode;
}


void CFieldParameter::SetSloopWidthOfLeft(double dSloopWidthLeft)
{
	m_stPatternDataOfHEAD2.dSloopWidth_L = m_dSloopOfWidthLeft = dSloopWidthLeft;
}


double CFieldParameter::GetSloopWidthOfLeft(void)
{
	//return m_dSloopOfWidthLeft;
	return m_stPatternDataOfHEAD2.dSloopWidth_L;
}


void CFieldParameter::SetSloopWidthOfRight(double dSloopWidthRight)
{
	m_stPatternDataOfHEAD2.dSloopWidth_R = m_dSloopOfWidthRight = dSloopWidthRight;
}


double CFieldParameter::GetSloopWidthOfRight(void)
{
	//return m_dSloopOfWidthRight;
	return m_stPatternDataOfHEAD2.dSloopWidth_R;
}


void CFieldParameter::SetPatternFileName(CString strFilename)
{
	m_stPatternDataOfHEAD2.m_strFilename = strFilename;
}


CString CFieldParameter::GetPatternFileName(void)
{
	return m_stPatternDataOfHEAD2.m_strFilename;
}
//------------------------------------------2019-10-07 장민국 ------------------------------
void CFieldParameter::SetPatternFlipY(bool bFlipY)
{
	m_stPatternDataOfHEAD2.bYFlip = bFlipY;
}

bool CFieldParameter::GetPatternFlipY(void)
{
	return m_stPatternDataOfHEAD2.bYFlip;
}

void CFieldParameter::SetTapPositionFilename(CString strfilename)
{
	m_strTapFileName = strfilename;
}


CString CFieldParameter::GetTapFilename(void)
{
	return m_strTapFileName;
}


void CFieldParameter::SetSloopSegment(double dLeftSegmentLT, double dLeftSegmentLB, double dRightSegmentRT,double dRightSegmentRB)
{
	m_stPatternDataOfHEAD2.dSloopSegment_LT = dLeftSegmentLT;
	m_stPatternDataOfHEAD2.dSloopSegment_RT = dRightSegmentRT;
	m_stPatternDataOfHEAD2.dSloopSegment_LB = dLeftSegmentLB;
	m_stPatternDataOfHEAD2.dSloopSegment_RB = dRightSegmentRB;
}


void CFieldParameter::GetSloopSegment(double & dLeftSegmentLT, double & dLeftSegmentLB, double & dRightSegmentRT,double & dRightSegmentRB)
{
	dLeftSegmentLT  =  m_stPatternDataOfHEAD2.dSloopSegment_LT;
	dRightSegmentRT = m_stPatternDataOfHEAD2.dSloopSegment_RT;
	dLeftSegmentLB  =  m_stPatternDataOfHEAD2.dSloopSegment_LB;
	dRightSegmentRB = m_stPatternDataOfHEAD2.dSloopSegment_RB;
}



void CFieldParameter::SetAdjustVector(double dVector)
{
	m_dAdjustVector = dVector;
}


double CFieldParameter::GetAdjustVector(void)
{
	return m_dAdjustVector;
}



void CFieldParameter::SetRollSpeed(double dRollSpeed)
{
	m_dRollSpeed = dRollSpeed;
}

double CFieldParameter::GetRollSpeed(void)
{
	return m_dRollSpeed;
}

void CFieldParameter::SetMarkingField(double dMarkingField)
{
	m_dMarkingField = dMarkingField;
}

double CFieldParameter::GetMarkingField(void)
{
	return m_dMarkingField;
}

void CFieldParameter::SetCycleOffset(double dCycleOffset)
{
	m_dCycleOffset = dCycleOffset;
}

double CFieldParameter::GetCycleOffset(void)
{
	return m_dCycleOffset;
}

// 엔코더옵셋
void CFieldParameter::SetCycleOffset2(double dCycleOffset)
{
	m_dCycleOffset2 = dCycleOffset;
}

double CFieldParameter::GetCycleOffset2(void) 
{
	return m_dCycleOffset2;
}


void CFieldParameter::SetScannerStartPosX(double dScannerStartX)
{
	m_dScannerStartPosX = dScannerStartX;
}

double CFieldParameter::GetScannerStartPosX(void)
{
	return m_dScannerStartPosX;
}

void CFieldParameter::SetScannerStartPosY(double dScannerStartY)
{
	m_dScannerStartPosY = dScannerStartY;
}

double CFieldParameter::GetScannerStartPosY(void)
{
	return m_dScannerStartPosY;
}

void CFieldParameter::SetExtendLine_Xwidth(double dLeftWidth, double dRightWidth)
{
	m_stPatternDataOfHEAD2.dExtend_Xwidth_L = m_dExtandLine_widthX_Left = dLeftWidth;
	m_stPatternDataOfHEAD2.dExtend_Xwidth_R = m_dExtandLine_widthX_Right = dRightWidth;
}


void CFieldParameter::GetExtendLine_Xwidth(double & dLeftWidth, double & dRightWidth)
{
	dLeftWidth = m_dExtandLine_widthX_Left = m_stPatternDataOfHEAD2.dExtend_Xwidth_L;
	dRightWidth = m_dExtandLine_widthX_Right = m_stPatternDataOfHEAD2.dExtend_Xwidth_R;
}




void CFieldParameter::SetExtendLine_Yheight(double dLeftHeight, double dRightHeight)
{
	m_stPatternDataOfHEAD2.dExtend_Yheight_L = m_dExtandLine_heightY_Left = dLeftHeight;
	m_stPatternDataOfHEAD2.dExtend_Yheight_R = m_dExtandLine_heightY_Right = dRightHeight;
}


void CFieldParameter::GetExtendLine_Yheight(double & dLeftHeight, double & dRightHeight)
{
	dLeftHeight = m_dExtandLine_heightY_Left = m_stPatternDataOfHEAD2.dExtend_Yheight_L;
	dRightHeight = m_dExtandLine_heightY_Right = m_stPatternDataOfHEAD2.dExtend_Yheight_R;
}





void CFieldParameter::SavePatternImage(bool bFlag)
{
	m_bSavePatternImage = bFlag;
}


bool CFieldParameter::GetPatternSaveFlag(void)
{
	return m_bSavePatternImage;
}


void CFieldParameter::SetKxKy(double kx, double ky)
{
	if(m_bEncoderReverse == TRUE)
	{
		m_dKX = ( kx > 0  ) ? kx : -kx;
		m_dKY = ( ky > 0  ) ? ky : -ky;
	}
	else
	{
		m_dKX = ( kx < 0  ) ? -kx : kx;
		m_dKY = ( ky < 0  ) ? -ky : ky;
	}
}

void CFieldParameter::SetKxKy_Notch(double kx, double ky)
{
	if(m_bEncoderReverse == TRUE)
	{
		m_dKX_Notch = ( kx > 0  ) ? kx : -kx;
		m_dKY_Notch = ( ky > 0  ) ? ky : -ky;
	}
	else
	{
		m_dKX_Notch = ( kx < 0  ) ? -kx : kx;
		m_dKY_Notch = ( ky < 0  ) ? -ky : ky;
	}
}


double CFieldParameter::GetKX(void)
{
	if(m_bEncoderReverse == TRUE)
		return -m_dKX;
	else
		return m_dKX;
}

double CFieldParameter::GetKX_Notch(void)
{
	if(m_bEncoderReverse == TRUE)
		return -m_dKX_Notch;
	else
		return m_dKX_Notch;
}



double CFieldParameter::GetKY(void)
{
	if(m_bEncoderReverse == TRUE)
		return -m_dKY;
	else 
		return m_dKY;
}

double CFieldParameter::GetKY_Notch(void)
{
	if(m_bEncoderReverse == TRUE)
		return -m_dKY_Notch;
	else 
		return m_dKY_Notch;
}


void CFieldParameter::SetKxKy2(double kx, double ky)
{
	if(m_bEncoderReverse == TRUE)
	{
		m_dKX2 = ( kx > 0  ) ? kx : -kx;
		m_dKY2 = ( ky > 0  ) ? ky : -ky;
	}
	else
	{
		m_dKX2 = ( kx < 0  ) ? -kx : kx;
		m_dKY2 = ( ky < 0  ) ? -ky : ky;
	}
}

void CFieldParameter::SetKxKy2_Notch(double kx, double ky)
{
	if(m_bEncoderReverse == TRUE)
	{
		m_dKX2_Notch = ( kx > 0  ) ? kx : -kx;
		m_dKY2_Notch = ( ky > 0  ) ? ky : -ky;
	}
	else
	{
		m_dKX2_Notch = ( kx < 0  ) ? -kx : kx;
		m_dKY2_Notch = ( ky < 0  ) ? -ky : ky;
	}
}


double CFieldParameter::GetKX2(void)
{
	if(m_bEncoderReverse == TRUE)
		return -m_dKX2;
	else
		return m_dKX2;
}

double CFieldParameter::GetKX2_Notch(void)
{
	if(m_bEncoderReverse == TRUE)
		return -m_dKX2_Notch;
	else
		return m_dKX2_Notch;
}

double CFieldParameter::GetKY2(void)
{
	double dKY = 0.0;

	if(m_bEncoderReverse == TRUE)
		return -m_dKY2;
	else 
		return m_dKY2;
}

double CFieldParameter::GetKY2_Notch(void)
{
	double dKY = 0.0;

	if(m_bEncoderReverse == TRUE)
		return -m_dKY2_Notch;
	else 
		return m_dKY2_Notch;
}


void  CFieldParameter::SaveEncoderCountToFile(double dHead1_Cnt, double dHead2_Cnt)
{
	CBeamEditor6App* pApp = (CBeamEditor6App *)AfxGetApp(); 
	FILE *File;
	File = fopen(pApp->m_strCwd+"\\EncoderSaved.ini", "wt");
	fprintf(File, "%.3f\n%.3f\n", dHead1_Cnt,dHead2_Cnt);
	fclose(File);
}

void  CFieldParameter::GetSavedEncoderCountFromFile(double *dHead1_Cnt, double *dHead2_Cnt)
{
	CBeamEditor6App* pApp = (CBeamEditor6App *)AfxGetApp();
	FILE *pFile;
	CString strFilePath = pApp->m_strCwd + "\\EncoderSaved.ini";
	pFile = fopen(strFilePath, "rt");
	if (pFile)
	{
		if (fscanf(pFile, "%lf\n%lf\n", &m_dSavedEncooderCountHead1, &m_dSavedEncooderCountHead2) != 2)
		{
			AfxMessageBox("Error reading data from EncoderSaved.ini file!");
		}
		else
		{
			*dHead1_Cnt = m_dSavedEncooderCountHead1; 
			*dHead2_Cnt= m_dSavedEncooderCountHead2;
		}
		fclose(pFile);
	}
	else
	{
		AfxMessageBox("Cannot find EncoderSaved.ini file!");
	}
}

void CFieldParameter::SetMaxCuttingSize(double dMaxCuttingSize)
{
	m_dMaxCuttingSize = dMaxCuttingSize;
}
	
double CFieldParameter::GetMaxCuttingSize()
{
	return m_dMaxCuttingSize;
}



void CFieldParameter::SetSimulationMode(int nMode)
{
	m_iSimulationMode = nMode;
}


int CFieldParameter::GetSimulationMode(void)
{
	return m_iSimulationMode;
}


void CFieldParameter::SetEncoderReverse(bool bFlag)
{
	m_bEncoderReverse = bFlag;
}
bool CFieldParameter::GetEncoderReverse()
{
	return m_bEncoderReverse;
}


void CFieldParameter::SetSpeedScale(double dScale)
{
	m_dSpeedScale = dScale;
}


double CFieldParameter::GetSpeedScale(void)
{
	return m_dSpeedScale;
}


void CFieldParameter::SetEncoderPositionIoCheckView(long lEncoderPosition, bool bHighLowFlag)
{
	m_lEncoderPosition = lEncoderPosition;
	m_bHighLowFlag = bHighLowFlag;
}


void CFieldParameter::GetEncoderPositionIoCheckView(long & lEncoderPosition, bool & bHighLowFlag)
{
	lEncoderPosition = m_lEncoderPosition;
	bHighLowFlag  =    m_bHighLowFlag;
}

void CFieldParameter::SetAutoMarkFlag(bool bAutoMarkFlag)
{
	m_bAutoMarkFlag = bAutoMarkFlag;
}


bool CFieldParameter::GetAutoMarkFlag(void)
{
	return m_bAutoMarkFlag;
}


void CFieldParameter::Setmultispeed(int nIndex,double dSpeed)
{
	m_dMultiSpeed[nIndex] = dSpeed;
}


int CFieldParameter::GetMultispeed(int nIndex)
{
	
	return m_dMultiSpeed[nIndex];
}

void CFieldParameter::SetDownloadFlag(bool bDownloadFlag)
{
	m_bDownloadFlag = bDownloadFlag;
}


bool CFieldParameter::GetDownloadFlag(void)
{
	return m_bDownloadFlag;
}

void CFieldParameter::SetSampleSize(double dSampleSize)
{
	m_dSampleSize = dSampleSize;
}

double CFieldParameter::GetSampleSize(void)
{
	return m_dSampleSize;
}

void CFieldParameter::SetRealSize(double dRealSize)
{
	m_dRealSize = dRealSize;
}

double CFieldParameter::GetRealSize(void)
{
	return m_dRealSize;
}

void CFieldParameter::SetRFieldSize(double dRFieldSize)
{
	m_dRFieldSize = dRFieldSize;
}

double CFieldParameter::GetRFieldSize(void)
{
	return m_dRFieldSize;
}

int	CFieldParameter::GetRunMode()
{
	return m_nRunMode;
}


void CFieldParameter::SetRunMode(int runMode)
{
	m_nRunMode = runMode;
}

int	  CFieldParameter::GetPatternMode()
{
	return m_nPatternMode;
}



void  CFieldParameter::SetPatternMode(int patternMode)
{
	m_nPatternMode = patternMode;
}

BPATTERNDATA CFieldParameter::GetBMWData()
{
	return m_BMWPatternData;
}

void CFieldParameter::SetBMWData(BPATTERNDATA data)
{
	m_BMWPatternData = data;
}


LASERSTATUS  CFieldParameter::GetLaserStatusHEAD1()
{
	return m_LaserStatusHEAD1;
}

void CFieldParameter::SetLaserStatusHEAD1(LASERSTATUS status)
{
	m_LaserStatusHEAD1 = status;
}


LASERSTATUS  CFieldParameter::GetLaserStatusHEAD2()
{
	return m_LaserStatusHEAD2;
}

void CFieldParameter::SetLaserStatusHEAD2(LASERSTATUS status)
{
	m_LaserStatusHEAD2 = status;

}



