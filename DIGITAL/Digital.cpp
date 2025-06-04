#include "stdafx.h"
#include "Digital.h"

#include "../EXTERN/FileMgr.h"
#include "../RUN_MODULE/RunningDefine.h"
#include "../RECIPE/RecipeManager.h"
//#include <NX_IO/IoMgr.h>

#include <NX_DIGITALIO/DIOManager.h>
#include <NX_AJINDIO/DIOAjin.h>

CDigital* Digital = NULL;
CDigital::CDigital(void)
{
	InitControl();
	Clear();
	OpenConfig();

}


CDigital::~CDigital(void)
{
	DeleteControl();	
}

void CDigital::Clear()
{
	for(int i = 0; i < MAX_IO_BOARD; i++)
	{
		m_bfInput[i].Data = 0;
		m_bfOutput[i].Data = 0;
	}

	m_nInterval  = 500;
	m_LampDlay.SetTime(ENUM_TIME_COUNTER_MODE_GETTICK);
}

void CDigital::Read()
{
#ifndef _DIGITAL_
	//
// 	if(IoMgr){
// 		for( int i = 0; i < IoMgr->GetNumberOfItem(); i++ )		
// 			m_bfInput[i].Data = IoMgr->GetItem(i)->GetIOInputAll();
// 	}
	static int nModuleCount = 0;
	nModuleCount = gDIOMgr->GetItem(DIO_AJIN)->GetModuleCnt();
	for( int i = 0; i < nModuleCount; i++ )		
		m_bfInput[i].Data = gDIOMgr->GetItem(DIO_AJIN)->GetIOInputAll(i);
#endif

}

void CDigital::Wirte()
{
#ifndef _DIGITAL_                                                                                                                                                                                                    
	//
// 	if(IoMgr){
// 		for( int i = 0; i < IoMgr->GetNumberOfItem(); i++ )		
// 			IoMgr->GetItem(i)->SetOutput(m_bfOutput[i].Data);
		
//	}
 	static int nModuleCount = 0;
	nModuleCount = gDIOMgr->GetItem(DIO_AJIN)->GetModuleCnt();
	for( int i = 0; i < nModuleCount; i++ )		
		gDIOMgr->GetItem(DIO_AJIN)->SetOutputAll(i, m_bfOutput[i].Data);
#endif
}

void CDigital::Scan()
{
#ifndef _DIGITAL_
	//UMAC
	//{{
 	//IoMgr->GetAllStatus();
 	//Read();
 	//Wirte();
	//}}

	//AJIN
	//{{
	gDIOMgr->GetItem(0)->GettingExecute();
	Read();
	Wirte();

	//}}

	TowerScan();
	RunCylinder();

#endif
}

void CDigital::TowerScan()
{
	if(m_eLamp%2)
	{
		if(m_LampDlay.GetDelayTime(ENUM_TIME_COUNTER_MODE_GETTICK) < m_nInterval) return;
		m_LampDlay.SetTime(ENUM_TIME_COUNTER_MODE_GETTICK);
	}

	switch(m_eLamp)
	{
	case LAMP_NONE:
		//Y_TOWER_LAMP_RED		= FALSE;
		//Y_TOWER_LAMP_GREEN		= FALSE;
		//Y_TOWER_LAMP_YELLOW		= FALSE;
		break;
	case BLINK_RED:
		//Y_TOWER_LAMP_RED		= !Y_TOWER_LAMP_RED;
		//Y_TOWER_LAMP_GREEN		= FALSE;
		//Y_TOWER_LAMP_YELLOW		= FALSE;
		break;
	case LAMP_RED:
		//Y_TOWER_LAMP_RED		= TRUE ;
		//Y_TOWER_LAMP_GREEN		= FALSE;
		//Y_TOWER_LAMP_YELLOW		= FALSE;
		break;
	case BLINK_YELLOW:
		//Y_TOWER_LAMP_RED		= FALSE;
		//Y_TOWER_LAMP_GREEN		= FALSE;
		//Y_TOWER_LAMP_YELLOW		= !Y_TOWER_LAMP_YELLOW;
		break;
	case LAMP_YELLOW:
// 		Y_TOWER_LAMP_RED		= FALSE;
// 		Y_TOWER_LAMP_GREEN		= FALSE;
// 		Y_TOWER_LAMP_YELLOW		= TRUE ;
		break;
	case BLINK_GREEN:
// 		Y_TOWER_LAMP_RED		= FALSE;
// 		Y_TOWER_LAMP_GREEN		= !Y_TOWER_LAMP_GREEN;
// 		Y_TOWER_LAMP_YELLOW		= FALSE;
		break;
	case LAMP_GREEN:
// 		Y_TOWER_LAMP_RED		= FALSE;
// 		Y_TOWER_LAMP_GREEN		= TRUE ;
// 		Y_TOWER_LAMP_YELLOW		= FALSE;
		break;
	}
}

void CDigital::SetTower(TOWER_LAMP a_elamp)
{
	m_eLamp = a_elamp;
}

void CDigital::SetSwitch(BUTTON_SW a_ebutton, BOOL a_bMode /* = FALSE */)
{
	switch(a_ebutton)
	{
	case BUTTON_OFF:
// 		Y_SW_START      = FALSE;
// 		Y_SW_STOP       = FALSE;
// 		Y_SW_RESET		= FALSE;
		break;
	case BUTTON_START:
// 		Y_SW_START      = TRUE;
// 		Y_SW_STOP       = FALSE;
// 		Y_SW_RESET		= FALSE;
		break;
	case BUTTON_STOP:
// 		Y_SW_START      = FALSE;
// 		Y_SW_STOP       = TRUE;
// 		Y_SW_RESET		= FALSE;
		break;
	case BUTTON_RESET:
// 		Y_SW_START      = FALSE;
// 		Y_SW_STOP       = FALSE;
// 		Y_SW_RESET		= TRUE;
		break;

	}
}

void CDigital::SetMelody(MELODY a_eMode)
{
	switch(a_eMode)
	{
	case MELODY_NONE:
// 		Y_MELODY_ERROR	= OFF;
// 		Y_MELODY_ALARM	= OFF;
// 		Y_MELODY_JOBEND = OFF;
		break;
	case MELODY_ERROR:
// 		Y_MELODY_ERROR	=  ON;
// 		Y_MELODY_ALARM	= OFF;
// 		Y_MELODY_JOBEND = OFF;
		break;
	case MELODY_ALARM:
// 		Y_MELODY_ERROR	= OFF;
// 		Y_MELODY_ALARM	=  ON;
// 		Y_MELODY_JOBEND = OFF;
		break;
	case MELODY_JOBEND:
// 		Y_MELODY_ERROR	= OFF;
// 		Y_MELODY_ALARM	= OFF;
// 		Y_MELODY_JOBEND =  ON;
		break;
	}
}

BOOL CDigital::GetX(int a_nIndex)
{
	BOOL bRtn = FALSE;
	if(a_nIndex < 0 || a_nIndex >= MAX_IO_INPUT) return bRtn;
	int nBd = a_nIndex/MAX_IO_CH;
	int nCh = a_nIndex%MAX_IO_CH;
	bRtn = ((m_bfInput[nBd].Data >> nCh) & 0x01);
	return bRtn;
}

BOOL CDigital::GetY(int a_nIndex)
{
	BOOL bRtn = FALSE;
	if(a_nIndex < 0 || a_nIndex >= MAX_IO_OUTPUT) return bRtn;
	int nBd = a_nIndex/MAX_IO_CH;
	int nCh = a_nIndex%MAX_IO_CH;
	bRtn = ((m_bfOutput[nBd].Data >> nCh) & 0x01);
	return bRtn;
}

void CDigital::SetY(int a_nIndex, BOOL a_bMode)
{
	if(a_nIndex < 0 || a_nIndex > MAX_IO_OUTPUT) return;
	int nBd = a_nIndex/MAX_IO_CH;
	int nCh = a_nIndex%MAX_IO_CH;
	if(a_bMode) 
		m_bfOutput[nBd].Data |= (0x01 << nCh);
	else		
		m_bfOutput[nBd].Data &= (0xFFFFFFFF - (0x01 <<nCh));
}

BOOL CDigital::GetSensor(AIR_CYL a_eIndex, BOOL a_bMode)
{
	BOOL bX0,bX1;
	//forwarding 위치에 Input Sensor 유무를 판단.
	if(m_stCylinder[a_eIndex].m_nX0 == -1) 	
	{
		//forwarding 위치에 Input Sensor가 없을 경우
		bX0 = m_stCylinder[a_eIndex].m_nSetState ? TRUE:FALSE;
	}
	else 										
	{
		//forwarding 위치에 Input Sensor가 있을 경우
		bX0 = GetX(m_stCylinder[a_eIndex].m_nX0);
	}

	//Backwarding 위치에 Input Sensor 유무를 판단.
	if(m_stCylinder[a_eIndex].m_nX1 == -1)
	{
		//Backwarding 위치에 Input Sensor가 없을 경우
		bX1 = m_stCylinder[a_eIndex].m_nSetState ? FALSE:TRUE;
	}
	else
	{
		//Backwarding O위치에 Input Sensor가 있을 경우.
		bX1 = GetX(m_stCylinder[a_eIndex].m_nX1);
	}

	if(a_bMode) //Forward
	{
		if(bX0 && !bX1) return TRUE;
	}
	else        //Backward      
	{
		if(!bX0 && bX1) return TRUE;
	}

	return FALSE;

}

BOOL CDigital::GetCylinder(AIR_CYL a_eIndex, BOOL a_bMode)
{
	//Sensor 확인.
	if(!GetSensor(a_eIndex,a_bMode))					return FALSE;
	//State 확인.
	if(m_stCylinder[a_eIndex].m_nRunState < 0)			return FALSE;

	BOOL bRunState = m_stCylinder[a_eIndex].m_nRunState? TRUE:FALSE;

	//state 와 a_bMode 확인.
	if(bRunState == a_bMode)							return TRUE;
	else												return FALSE;
}

BOOL CDigital::SetCylinder(AIR_CYL a_eIndex, BOOL a_bMode)
{
	m_stCylinder[a_eIndex].m_nSetState = a_bMode;
	SetY(m_stCylinder[a_eIndex].m_nY0,a_bMode);

	if(m_stCylinder[a_eIndex].m_nY1 != -1) 
		SetY(m_stCylinder[a_eIndex].m_nY1,!a_bMode);

	m_stCylinder[a_eIndex].m_RunTime.SetTime(ENUM_TIME_COUNTER_MODE_GETTICK);
	m_stCylinder[a_eIndex].m_RunDelay.SetTime(ENUM_TIME_COUNTER_MODE_GETTICK);
	m_stCylinder[a_eIndex].m_nRunState = !a_bMode;
	return TRUE;
}

void CDigital::RunCylinder()
{
	BOOL bX0,bX1;
	BOOL bState;


	for(int i = 0; i < MAX_CYLINDER; i++)
	{
		//Normal   : m_nRunState == 0 or 1; 0 (FWD)   1 (BWD) 
		//Abnormal : m_nRunState == -1;
		if(m_stCylinder[i].m_nRunState == -1)							continue;
		//m_nSetState == m_nRunState 일 경우는 이미 원하는 위치에 실린더가 이동한 경우임.
		if(m_stCylinder[i].m_nRunState == m_stCylinder[i].m_nSetState)	continue;


		if(m_stCylinder[i].m_nX0 == -1) bX0 = m_stCylinder[i].m_nSetState?TRUE:FALSE; //Sensor가 -1 이라는 것은 Sensor가 없다는 것이다. -1일 경우 m_nSetState로 셋팅한다.
		else							bX0 = GetX(m_stCylinder[i].m_nX0);            //Cylinder의 Forward위치의 Sensor 상태 읽어 온다.

		if(m_stCylinder[i].m_nX1 == -1) bX1 = m_stCylinder[i].m_nSetState?FALSE:TRUE; 
		else							bX1 = GetX(m_stCylinder[i].m_nX1);            //Cylinder의 Backward위치의 Sensor 상태 읽어 온다.

		bState = m_stCylinder[i].m_nSetState?TRUE:FALSE; 
		//cylinder가 Forward일 경우 true;
		//cylinder가 Backward일 경우 false;
		if((bX0 == bState) && (bX1 == !bState))
		{
			int nDelay = 0;

			if(m_stCylinder[i].m_nSetState)
			{
				nDelay = m_stCylinder[i].m_nSetDelay;
			}
			else
			{
				nDelay = m_stCylinder[i].m_nSetDelay2;
			}
			
			/*m_stCylinder[i].m_nRunDelay += m_nInterval;*/
			if(m_stCylinder[i].m_RunDelay.GetDelayTime(ENUM_TIME_COUNTER_MODE_GETTICK) > nDelay) //delay
			{
				m_stCylinder[i].m_nRunState = m_stCylinder[i].m_nSetState;
				if(m_stCylinder[i].m_nY1 == -1 ) continue;                         //단동일 경우는 pass
				if(m_stCylinder[i].m_nSetState) SetY(m_stCylinder[i].m_nY0,FALSE); //Cylinder가 Forwad위치로 이동했으므로 Forward 위치의 Sensor를 Off 한다.
				else							SetY(m_stCylinder[i].m_nY1,FALSE); //Cylinder가 Backward위치로  이동했으므로 Backward 위치의 Sensor를 Off 한다.
			}
			else
			{
				//m_stCylinder[i].m_nRunTime += m_nInterval;
				if(m_stCylinder[i].m_RunTime.GetDelayTime(ENUM_TIME_COUNTER_MODE_GETTICK) > m_stCylinder[i].m_nSetTime) //TimeOut
					m_stCylinder[i].m_nRunState = -1;
			}
		}
	}
}


BOOL CDigital::OpenConfig()
{
	CFileMgr* FileMgr = new CFileMgr;
	//현재 실행 중인 폴더의 경로를 가져온다.
	CString strPath = FileMgr->GetNowExePath();
	strPath += DIRECTORY_NAME;

	//디렉토리 유무 확인
	if(FileMgr->GetDirExists(strPath) == false)
	{
		//디렉토리가 없을 경우 생성.
		FileMgr->CreateUserDir(strPath);
	}

	strPath += DIGITAL_CONFIG_FILE_NAME;
	//파일 유무 확인
	if(FileMgr->GetFileExists(strPath) == false)
	{
		//파일이 없을 경우 파일 생성.
		if(FileMgr->CreateUserFile(strPath) == false)
		{
			delete FileMgr;
			return FALSE;
		}
	}

	CString strSection		= TEXT("");
	CString strEelemnet		= TEXT("");//strReturnValue
	CString strReturnValue  = TEXT("");
	int i;


	for(i = 0; i < MAX_CYLINDER; i++)
	{
		strSection.Format(_T("CYLINDER_MODULE_%d"),i);
		m_stCylinder[i].m_strPart	= FileMgr->ReadString (strSection, _T("PART"	), strPath); 
		m_stCylinder[i].m_strName	= FileMgr->ReadString (strSection, _T("NAME"	), strPath); 
		m_stCylinder[i].m_nX0		= FileMgr->ReadInteger(strSection, _T("INPUT0"	), strPath); 
		m_stCylinder[i].m_nX1		= FileMgr->ReadInteger(strSection, _T("INPUT1"	), strPath); 
		m_stCylinder[i].m_nY0		= FileMgr->ReadInteger(strSection, _T("OUTPUT0"	), strPath); 
		m_stCylinder[i].m_nY1		= FileMgr->ReadInteger(strSection, _T("OUTPUT1"	), strPath); 
		m_stCylinder[i].m_nSetDelay	= FileMgr->ReadInteger(strSection, _T("DELAY1"	), strPath); 
		m_stCylinder[i].m_nSetDelay2= FileMgr->ReadInteger(strSection, _T("DELAY2"	), strPath); 
		m_stCylinder[i].m_nSetTime	= FileMgr->ReadInteger(strSection, _T("TIMEOUT"	), strPath);
	}
	if(FileMgr) delete FileMgr;	


	return TRUE;
}

BOOL CDigital::InitControl()
{
#ifndef _DIGITAL_

	gDIOMgr = new CDIOManager;
	gDIOMgr->AddItem(new CDIOAjin());
	//Analog IO
	m_pAJINAIO = new CAIOAJIN();
	m_pADJModule = new CADJModule(0,10,this,&CDigital::SetAIOVoltage, &CDigital::Set_AO_Range);
	//1. Min Voltage, 2. Max Voltage, 3.Voltage Func#1, 4. Range Func#2

	
#endif
	return TRUE;
}

BOOL CDigital::DeleteControl()
{
#ifndef _DIGITAL_
	//if(IoMgr) { delete IoMgr; IoMgr = NULL; };
	if(gDIOMgr)
	{
		delete gDIOMgr;
		gDIOMgr = NULL;
	}

	if(m_pADJModule)
	{
		delete m_pADJModule;
		m_pADJModule = NULL;
	}

	if(m_pAJINAIO)
	{
		delete m_pAJINAIO;
		m_pAJINAIO = NULL;
	}


#endif
	return TRUE;
}

void CDigital::SetAIOVoltage(double fValue)
{
	m_pAJINAIO->Set_AO_Voltage(0,0,fValue);
	//1. Module Number 2. Channel Number , 3. Voltage
}
void CDigital::Set_AO_Range(double fMin, double fMax)
{
	m_pAJINAIO->Set_AO_Range(0,0,fMin,fMax);
	//1. Module Number 2. Channel Number, 3. Range
}
void CDigital::StartAnalogOutput(void)
{
	if(m_pADJModule->IsRunning()) return;
	m_pADJModule->StartOutput();
}

void CDigital::StopAnalogOutput(void)
{
	m_pADJModule->StopOutput();
}

void CDigital::SetADJData(int nIndex, double fVoltage, double fOnTime)
{
	m_pADJModule->SetADJData(nIndex, fVoltage, fOnTime);
}

void CDigital::SetADJDataAlloc(int nBufferSize)
{
	m_pADJModule->AllocADJDataBuffer(nBufferSize);
}

int CDigital::GetADJDataBufferSize()
{
	return m_pADJModule->GetADJDataBufferSize();
}
double* CDigital::GetDataBufferPointor()
{
	return m_pADJModule->GetDataBufferPointor();
}
double* CDigital::GetTimeBufferPointor()
{
	return m_pADJModule->GetTimeBufferPointor();
}
BOOL CDigital::GetLaserSeqRunning()
{
	return m_pADJModule->GetLaserSeqRunning();
}

void CDigital::SetOn_MC(BOOL a_sSetStatus)
{
	//Y_MC_ON = a_sSetStatus;
}