// Dsp.cpp: implementation of the CDsp class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "BeamEditor6.h"
#include "MainFrm.h"
#include "Dsp.h"
#include "PointerManager.h"
#include "Bin.h"
#include "InitialTable.h"
	
#include "FieldParameter.h"
#include "TransUnit.h"
#include "MathUtil.h"

#include <sstream>
#include <fstream>
#include <io.h>


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////



#define LASER_PULSE_UNIT               64.0
#define RTC5_NO_ERROR                  0U
#define MAX_BUFF_SIZE                  300000 
#define MIN_LSB						   -524288
#define MAX_LSB					        524288


//-------------- Define Acc Error for RTC5 ---------------------------------
#define RTC5_NO_ERROR					 0
#define RTC5_NO_CARD					 1
#define RTC5_ACCESS_DENIED				 2
#define RTC5_SEND_ERROR					 4
#define RTC5_TIMEOUT					 8
#define RTC5_PARAM_ERROR				 16
#define RTC5_BUSY						 32
#define RTC5_REJECTED					 64
#define RTC5_IGNORED					 128
#define RTC5_VERSION_MISMATCH			 256
#define RTC5_VERIFY_ERROR				 512
#define RTC5_TYPE_REJECTED				 1024
#define RTC5_OUT_OF_MEMORY				 2048
#define RTC5_EEPROM_ERROR				 4096
#define RTC5_CONFIG_ERROR				 65535

#ifdef	_RTC4eth_

uint32_t MySerial = 243265;//220798; 	// replace by your card's serial number
uint32_t MyIp = 0;
uint16_t MyCard = 0;
uint32_t GetSerial = 0; 
#endif


const UINT unLaserControl(0x00U);    //  Laser signals High active  
const double Pi                   = 3.14159265358979323846;
// Change these values according to your system
const UINT   DefaultCard          =            1;   //  number of default card
//const UINT   ListMemory           =        10000;   //  size of list 1 memory (default 4000)
#ifdef _RTC6_
	const UINT ListMemory           =        RTC6_SIZE_OF_MEMORY;//10000;   //  size of list 1 memory (default 4000)
#else
	const UINT ListMemory           =        RTC5_SIZE_OF_MEMORY;   //  size of list 1 memory (default 4000)
#endif
//const UINT   LaserControl         =         0x18;   //  Laser signals LOW active (Bits #3 and #4)

//#endif

CDsp::CDsp()
{

	m_iListConunt = 0;
	m_bInitialStatus = FALSE;
#ifdef _RTC4eth_ 
	SetAnalogPowerUse(false);
#else
	SetAnalogPowerUse(true);
#endif


#ifdef _RTC_Test_ 
	SetAnalogPowerUse(false);
#else
	SetAnalogPowerUse(true);
#endif

	m_dSettedCurrMarkSpeed = 0;

	m_dtimed_marktime = 0.0;
	n_ScannerVariableMode = NORMAL_MARK_MODE;

	m_bFirstStart = TRUE;
	m_bFirstStartHEAD1 = TRUE;
	m_b1stFlagStep = FALSE;


	m_maxFieldHEAD2 = 0;
	m_maxMMHEAD2 = 0;

	m_maxFieldHEAD1 = 0;
	m_maxMMHEAD1;

	m_bFlipHead1 = FALSE;
	m_bFlipHead2 = FALSE;
	m_iEncoderPos = 0;

}

CDsp::~CDsp()
{
	
	StopExcutionHEAD1();
	if(GetBoardCount() > 1)
		StopExcutionHEAD2();

#if	_RTC3_
	WriteDA1(0);
	RTC3close();
#endif

#if _RTC4_
	WriteDA1(0);
//	RTC4close();
#endif


#if _RTC4eth_
	WriteDA1(0);
	//RTC4close();
	release_rtc(MyIp);
#endif


#if _RTCSCANALONE_
	WriteDA1(0);
	//SCANalone4close();
#endif

}

CDsp* CDsp::m_pDsp = 0;
CDsp* CDsp::GetInstance() 
{
	if (m_pDsp == 0) {
		m_pDsp = new CDsp;
	}
	
	return m_pDsp;
}

BOOL CDsp::InitDsp()
{
	CBeamEditor6App *pApp = (CBeamEditor6App*) AfxGetApp();
	CInitialTable *pInitialTable = pInitialTable->GetInstance();
	BOOL bResult = FALSE;
	CString strError;

	m_iListConunt = 0;
	UINT  ErrorCode=-1;
	m_bInitialStatus = FALSE;
	m_iChangeLineSpeedIndex = 0;
	UINT RTCCountCards = 0;

#ifdef	_SIMUL_
	//m_bInitialStatus = FALSE;
	return TRUE;
#endif


#ifdef	_RTC3_
	RTC3open();
#endif

#ifdef	_RTC4_
	//	RTC4open();
#endif

	
	//----------------------------- RTC -------------------------------------------------------------------------------
//#ifdef _RTC6_
	{
		#ifdef _RTC6_
			ErrorCode = init_rtc6_dll(); 
		#else
			ErrorCode = init_rtc5_dll(); 
		#endif

		
		
	//	if( 0 != load_correction_file( NULL, 1, 2 ) ) 
	//	{ 
	//		return -2;
	//	} 

		/*for (int i = 0; i < 16; i++)
		{
			nOutputIO(1,i, FALSE);
			if(RTCCountCards > 1)
				nOutputIO(2,i, FALSE);
		}

		for (int i = 0; i < 16; i++)
		{
			nOutputIO(1,i, TRUE);
			if(RTCCountCards > 1)
				nOutputIO(2,i, TRUE);
		}*/

		//if (ErrorCode & RTC5_ACCESS_DENIED)
        
		if (ErrorCode)
		{
			#ifdef _RTC6_
				RTCCountCards = rtc6_count_cards();   //  number of cards found
			#else
				RTCCountCards = rtc5_count_cards();   //  number of cards found
			#endif

			if ( RTCCountCards > 0 )
			{
				UINT AccError( 0 );
				//  Error analysis in detail
				for ( UINT i = 1; i <= RTCCountCards; i++ )
				{
					const UINT Error = n_get_last_error( i );
					if ( Error != 0 ) 
					{
						AccError |= Error;
						strError.Format("Card no. %d: Error %d detected\n", i, Error );
						AfxMessageBox(strError);
						n_reset_error( i, Error );
					}
				}
				if ( AccError )
				{
					m_bInitialStatus = FALSE;
					return FALSE;
				}

			}
			else
			{
				strError.Format("Initializing the DLL: Error %d detected\n", ErrorCode);
				m_bInitialStatus = FALSE;
				//AfxMessageBox(strError);
				#ifdef _RTC6_
					free_rtc6_dll();
				#else
					free_rtc5_dll();
				#endif

				return FALSE;
			}
		}
		else
		{
			#ifdef _RTC6_
				RTCCountCards = rtc6_count_cards();   //  number of cards found
			#else
				RTCCountCards = rtc5_count_cards();   //  number of cards found
			#endif

			UINT uCardNo = -1;
			UINT NoOfAcquiredCard = acquire_rtc( 1 );

			select_rtc(1);
			if(RTCCountCards > 1)
				select_rtc(2);


			if ( DefaultCard != select_rtc( DefaultCard ) )     //  use card no. 1 as default, 
			{
				ErrorCode = n_get_last_error( DefaultCard );
				if ( ErrorCode & 256 )    //  RTC5_VERSION_MISMATCH
				{
					//  In this case load_program_file(0) would not work.
					ErrorCode = n_load_program_file( DefaultCard, 0 ); //  current working path
				}
				else
				{
					strError.Format("No acces to card no. %d\n", DefaultCard);
					AfxMessageBox(strError);
#ifdef _RTC6_
					free_rtc6_dll();
#else
					free_rtc5_dll();
#endif
					
					m_bInitialStatus = FALSE;
					return FALSE;
				}
				if ( ErrorCode )
				{
					strError.Format("No acces to card no. %d\n", DefaultCard);
					AfxMessageBox(strError);
#ifdef _RTC6_
					free_rtc6_dll();
#else
					free_rtc5_dll();
#endif
					m_bInitialStatus = FALSE;
					return FALSE;
				}
				else
				{   //  n_load_program_file was successfull
					(void) select_rtc( DefaultCard );
				}
			}
			m_bInitialStatus = TRUE;
		}
		// set_rtc4_mode();            //  for RTC4 compatibility
//
//#ifdef _RTC6_
//					set_rtc6_mode();//set_rtc6_mode();//set_rtc6_mode();//set_rtc5_mode();//set_rtc6_mode();
//#else
//					set_RTC5_mode();
//#endif
		
					

		// Initialize the RTC5
		//n_stop_execution(1);
		//if(RTCCountCards > 1)
		//n_stop_execution(2);
		CHAR m_caCfgPath[MAX_PATH];
		TCHAR szPath[MAX_PATH] = {0, };
		::GetModuleFileName( NULL, szPath, _MAX_PATH); PathRemoveFileSpec(szPath);
		_stprintf( szPath, _T("%s%s"), szPath, _T("\\CFG\\"));
		int nResult = SHCreateDirectoryEx( NULL, szPath, NULL );

		//WideCharToMultiByte(CP_ACP, 0, szPath, sizeof( TCHAR)*MAX_PATH, m_caCfgPath, sizeof(CHAR)*MAX_PATH, NULL, NULL );

		//m_unErroNo = load_program_file(  szPath);	

#ifdef _RTC6_
		m_unErroNo = n_load_program_file(RTC_CARD_NUM_1,  szPath);
		if(m_unErroNo) StopExcutionHEAD1();

		if(RTCCountCards > 1){
			m_unErroNo = n_load_program_file(RTC_CARD_NUM_2,  szPath);	
			if(m_unErroNo) StopExcutionHEAD2();
		}


#else
		m_unErroNo = n_load_program_file(RTC_CARD_NUM_1,   pApp->m_strCwd + DIRECTORY_NAME);
		if(m_unErroNo) StopExcutionHEAD1();

		if(RTCCountCards > 1){
			m_unErroNo = n_load_program_file(RTC_CARD_NUM_2,   pApp->m_strCwd + DIRECTORY_NAME);
			if(m_unErroNo) StopExcutionHEAD2();
		}
#endif

		//m_unErroNo = load_program_file( NULL );
		//if( 0 != load_program_file( NULL ) )
		//{
			//return -1; 
		//} // load RTC firmware if( 0 != load_correction_file( NULL, 1, 2 ) ) { return -2; } 	


		//  If the DefaultCard has been used previously by another application 
		//  a list might still be running. This would prevent load_program_file
		//  and load_correction_file from being executed.
		
		ErrorCode = n_load_correction_file(RTC_CARD_NUM_1,  pApp->m_strCwd + DIRECTORY_NAME+ "CorrectionFile.ct5",   // initialize like "D2_1to1.ct5",
			1,   // table; #1 is used by default
			2 ); // use 2D only

		if(RTCCountCards > 1)
		{
			ErrorCode = n_load_correction_file( RTC_CARD_NUM_2, pApp->m_strCwd + DIRECTORY_NAME+ "CorrectionFile.ct5",   // initialize like "D2_1to1.ct5",
				1,   // table; #1 is used by default
				2 ); // use 2D only
		}

		if ( ErrorCode )
		{
			strError.Format("Correction file loading error: %d\n", ErrorCode );
			AfxMessageBox(strError);
#ifdef _RTC6_
					free_rtc6_dll();
#else
					free_rtc5_dll();
#endif
			m_bInitialStatus = FALSE;
			return FALSE;
		}
		if(RTCCountCards > 1)
		n_select_cor_table( RTC_CARD_NUM_2,1,1);

		n_select_cor_table(RTC_CARD_NUM_1, 1, 1);   //  table #1 at primary connector (default)
		//  stop_execution might have created a RTC5_TIMEOUT error
		n_reset_error(RTC_CARD_NUM_1, -1 );    //  clear all previous error codes

		if(RTCCountCards > 1)
		n_reset_error(RTC_CARD_NUM_2,-1);
		//printf( "Lissajous figures\n\n" );

		//  One list only
		//config_list( ListMemory, 0 );
		//  Configure list memory, default: 

		//if(GetBoardCount() > 1) // Just One list memory use
		//{
		//	n_config_list( 1,-1, RTC5_SIZE_OF_MEMORY ); 
		//	n_config_list(2,-1, RTC5_SIZE_OF_MEMORY );
		//}
		//else
		//{
		//	if(GetInitialStatus())
		//		config_list( -1, RTC5_SIZE_OF_MEMORY  ); 
		//}
		//config_list( -1 , ListMemory); //2019.05.23 데이터 한번에 내리기 위해 리스트1으로 용량을 모두 사용



		if(GetBoardCount() > 1) // two list memory use
		{
			n_config_list(RTC_CARD_NUM_1,ListMemory/2, ListMemory/2 ); 
			n_config_list(RTC_CARD_NUM_2,ListMemory/2, ListMemory/2 );

			//n_config_list(RTC_CARD_NUM_1,-1, ListMemory ); 
			//n_config_list(RTC_CARD_NUM_2,-1, ListMemory );


			n_set_scale(RTC_CARD_NUM_1, 1, pInitialTable->GetFieldScale(), 1);
			n_set_scale(RTC_CARD_NUM_2 ,1, pInitialTable->GetFieldScale(), 1);
		}
		else
		{
			//n_config_list(RTC_CARD_NUM_1,-1, ListMemory ); 
			config_list( ListMemory/2, ListMemory/2  );
			n_set_scale(RTC_CARD_NUM_1, 1, pInitialTable->GetFieldScale(), 1);
			m_nListSize = nGetListSpace(RTC_CARD_NUM_1);
		}
	}
//#endif
	
	
	set_laser_control( 0 ); // high active laser signals
	//set_laser_mode( 1 ); // mode 1 supports YAG
	set_firstpulse_killer( 640 );
	


	if(ErrorCode) 
	{
		strError.Format("Hex file loading error : %d",ErrorCode);
		AfxMessageBox(strError);
		m_bInitialStatus = FALSE;
		return FALSE;
	}

	if (pInitialTable->GetKindOfLaser() == 0)	// YAG 1 mode selected
	{
		n_set_laser_mode(RTC_CARD_NUM_1,1);
		if(RTCCountCards > 1)
		n_set_laser_mode(RTC_CARD_NUM_2,1);
	}
	else if (pInitialTable->GetKindOfLaser() == 1)	// YAG 2 mode selected
	{
		n_set_laser_mode(RTC_CARD_NUM_1,2);
		if(RTCCountCards > 1)
		n_set_laser_mode(RTC_CARD_NUM_2,2);
	}
	else if (pInitialTable->GetKindOfLaser() == 2)	// YAG 3 mode selected
	{
		n_set_laser_mode(RTC_CARD_NUM_1,3);
		if(RTCCountCards > 1)
		n_set_laser_mode(RTC_CARD_NUM_2,3);
	}
	else if (pInitialTable->GetKindOfLaser() == 3)	// laser mode 4 selected
	{
		n_set_laser_mode(RTC_CARD_NUM_1,4);
		if(RTCCountCards > 1)
		n_set_laser_mode(RTC_CARD_NUM_2,4);
	}
	else if (pInitialTable->GetKindOfLaser() == 4)	// YAG 5 mode selected
	{
		n_set_laser_mode(RTC_CARD_NUM_1,5);
		if(RTCCountCards > 1)
		n_set_laser_mode(RTC_CARD_NUM_2,5);
	}
	else if (pInitialTable->GetKindOfLaser() == 5)	// laser mode 5 selected
	{
		n_set_laser_mode(RTC_CARD_NUM_1,6);
		if(RTCCountCards > 1)
		n_set_laser_mode(RTC_CARD_NUM_2,6);
	}
	else if (pInitialTable->GetKindOfLaser() == 6)	// CO2 mode selected
	{
		n_set_laser_mode(RTC_CARD_NUM_1,7);
		if(RTCCountCards > 1)
		n_set_laser_mode(RTC_CARD_NUM_2,7);
	}
	else
	{
		n_set_laser_mode(RTC_CARD_NUM_1,1);
		if(RTCCountCards > 1)
		n_set_laser_mode(RTC_CARD_NUM_2,1);
	}

	n_set_laser_control(RTC_CARD_NUM_1, 0 );
	if(RTCCountCards > 1)
	n_set_laser_control(RTC_CARD_NUM_2, 0);

	//	set_list_mode(0);

	n_disable_laser(RTC_CARD_NUM_1);
	if(RTCCountCards > 1)
	n_disable_laser(RTC_CARD_NUM_2);

	//if (!LoadCorrectionFile(pInitialTable->GetBaseMasterX(), 
	//	pInitialTable->GetBaseMasterY(),
	//	pInitialTable->GetBaseSlaveX(),
	//	pInitialTable->GetBaseSlaveY(),
	//	pInitialTable->GetFieldAngle()))
	//	return FALSE;

	UINT uPrevTime,uVmax;

	UINT upPrevTime,upVmax;

	double uAmax,upAmax;

	uPrevTime = 0;
	uVmax = 0;
	uAmax = 0;

#ifdef _RTC6_
	n_set_scanahead_params(RTC_CARD_NUM_1, 1, 1, 1, uPrevTime, uVmax, uAmax );// place anywhere after load_correction_file
	UINT Error = n_get_scanahead_params( RTC_CARD_NUM_1, 1, &upPrevTime, &upVmax, &upAmax );


	n_activate_scanahead_autodelays(RTC_CARD_NUM_1, 1);
	n_set_scanahead_params(RTC_CARD_NUM_1, 1, 1, 1, uPrevTime, uVmax, uAmax );// place anywhere after load_correction_file
	Error = n_get_scanahead_params( RTC_CARD_NUM_1, 1, &upPrevTime, &upVmax, &upAmax );

	activate_scanahead_autodelays( 1);
	set_scanahead_params( 1, 1, 1, uPrevTime, uVmax, uAmax );// place anywhere after load_correction_file
	Error = get_scanahead_params(  1, &upPrevTime, &upVmax, &upAmax );
#endif


	n_set_start_list(RTC_CARD_NUM_1,1);
	n_set_firstpulse_killer(RTC_CARD_NUM_1,0);
	// half of the laser signal period
	// pulse widths of signals LASER1 and LASER2
	// time base; 0 corresponds to 1 microsecond.
	// Otherwise, the time base is 1/8 microseconds.
	n_set_laser_timing(RTC_CARD_NUM_1,50, 50, 200, 0); 
	// jump delay in 10 microseconds
	// mark delay in 10 microseconds
	// polygon delay in 10 microseconds
	n_set_scanner_delays(RTC_CARD_NUM_1,200,200,5);
	//set_scanner_delays(200, 200, 5);
	// laser on delay in microseconds
	// laser off delay in microseconds
	n_set_laser_delays(RTC_CARD_NUM_1,200,200);
	//set_laser_delays(200, 200);
	n_set_jump_speed(RTC_CARD_NUM_1,2000.0);
	n_set_jump_speed(RTC_CARD_NUM_1,2000.0);
	n_set_mark_speed(RTC_CARD_NUM_1,5000.0);
	m_dSettedCurrMarkSpeed = 500;
	//2018.09.05 jjsjong 0: 
	//set_control_mode(0); // 0: no external start signal , 1: The external start input is enabled   512: no external start signal,Encoder resets of the two internal encoder counters
	n_set_control_mode(RTC_CARD_NUM_1,0);//high active laser signals

	//write_8bit_port((unsigned short)((para.GetRTCVoltage() / 100) *255));
	//write_8bit_port_list((unsigned short)(uSetPower));ListCountPlus();
	n_set_end_of_list(RTC_CARD_NUM_1);
	n_execute_list(RTC_CARD_NUM_1,1);
	n_home_position(RTC_CARD_NUM_1,0,0);

	n_set_laser_pulses_ctrl(RTC_CARD_NUM_1, 320, 128 );
	n_set_standby(RTC_CARD_NUM_1, 320, 128);  
	

	enable_laser();
	
	if(RTCCountCards > 1)
	{
		n_set_start_list(RTC_CARD_NUM_2,1);
		n_set_firstpulse_killer(RTC_CARD_NUM_2,0);
		n_set_laser_timing(RTC_CARD_NUM_2,50, 50, 200, 0);  
		n_set_scanner_delays(RTC_CARD_NUM_2,200,200,5);
		n_set_laser_delays(RTC_CARD_NUM_2,200,200);
		n_set_jump_speed(RTC_CARD_NUM_2,2000.0);
		n_set_mark_speed(RTC_CARD_NUM_2,5000.0);
		n_set_control_mode(RTC_CARD_NUM_2,0);
		n_set_end_of_list(RTC_CARD_NUM_2);
		n_execute_list(RTC_CARD_NUM_2,1);
		n_home_position(RTC_CARD_NUM_2,0,0);

		n_set_laser_pulses_ctrl(RTC_CARD_NUM_2, 320, 128 );
		n_set_standby(RTC_CARD_NUM_2, 320, 128);  
	
	}

	// half of the standby period in 1/8 microseconds
	// pulse width in 1/8 microseconds

	// Draw
	//select_cor_table(1,2);

	//write_da_1((short)(1023 * (5 / 10.0)));

	for (int i = 0; i < 16; i++)
	{
		nOutputIO(RTC_CARD_NUM_1,i, FALSE);
		if(RTCCountCards > 1)
		nOutputIO(RTC_CARD_NUM_2,i, FALSE);
	}

	/*for (int i = 0; i < 16; i++)
	{
		nOutputIO(1,i, TRUE);
		if(RTCCountCards > 1)
		nOutputIO(2,i, TRUE);
	}*/


#ifdef _RTC_Test_ 

	OutputIO(RTCIO_O_LATCH, false);
	long_delay(100);
	///Sleep(50);
	OutputIO(RTCIO_O_LATCH, true);
	OutputIO(RTCIO_O_EMERGENCY, true);
	OutputIO(RTCIO_O_MO, true);

	OutputIO(RTCIO_O_GUIDEBEAM_ENABLE, true);
#endif

	n_goto_xy(1,0,0);
	if(RTCCountCards > 1)
	n_goto_xy(2,0,0);

	// GetVersion 
	m_unDllVer	= get_dll_version();
	m_unHexVer	= get_hex_version();
	m_unRtcVer	= get_rtc_version();
	m_unSerialNum = get_serial_number();


	m_nListSize = nGetListSpace(RTC_CARD_NUM_1);
	return TRUE;
}

void CDsp::DestoryDsp()
{
	
	
}

void CDsp::StartManualMarking()
{
	
}

void CDsp::StartAutoMarking()
{
	
}

void CDsp::StopAutoMarking()
{
	
}

CString CDsp::GetVersion()
{
	CString DspVersion;
	return DspVersion;
}

void CDsp::SetOffsetData(int iMasterX, int iMasterY, int iSlaveX, int iSlaveY)
{
	CInitialTable *pInitialTable = pInitialTable->GetInstance();
	//if(GetInitialStatus() != true) return;

	double dScale = pInitialTable->GetFieldScale();

#ifdef _SIMUL_
	return;
#endif
#ifdef _RTC_Test_ 
	//SetOffsetData(iMasterX, iMasterY);
	n_set_offset(RTC_CARD_NUM_1, 1, iMasterX*dScale,iMasterY*dScale,0);
	if(GetBoardCount() > 1)
	n_set_offset(RTC_CARD_NUM_2, 1, iSlaveX*dScale,iSlaveY*dScale,0);

	return;
#endif
	//2022.11.24
	n_set_offset(RTC_CARD_NUM_1, 1, iMasterX*dScale,iMasterY*dScale,0);
	if(GetBoardCount() > 1)
	n_set_offset(RTC_CARD_NUM_2, 1, iSlaveX*dScale,iSlaveY*dScale,0);


}

void CDsp::SetOffsetData(int iMasterX, int iMasterY)
{
	if(GetInitialStatus() != true) return;

	CBeamEditor6App *pApp = (CBeamEditor6App*) AfxGetApp();
	CInitialTable *pInitialTable = pInitialTable->GetInstance();

	double dAngle = pInitialTable->GetFieldAngle();

//#ifdef	_RTC_Test_
	//set_offset(iMasterX, iMasterY);
	//set_offset(1, -iMasterX,-iMasterY,1);
//#else
	n_set_offset(RTC_CARD_NUM_1, 1, iMasterX,iMasterY,0);
	//n_set_offset(RTC_CARD_NUM_1, 1, iMasterX,iMasterY,0);
//#endif

	/*
	if(dAngle > -45 || dAngle < 45 )
	{
		if(m_nCarrierType == LEFT_CARRIER)
			set_offset(1, iMasterX,iMasterY,1);
		else
			set_offset(1, iSlaveX,iSlaveY,1);
	}
	else if(dAngle > 45 || dAngle < 135)
	{
		if(m_nCarrierType == LEFT_CARRIER)
			set_offset(1, -iMasterY, iMasterX,1);
		else
			set_offset(1, -iSlaveY,iSlaveX, 1);
	}
	else if(dAngle > 135 || dAngle < 225)
	{
		if(m_nCarrierType == LEFT_CARRIER)
			set_offset(1, -iMasterX,-iMasterY,1);
		else
			set_offset(1, -iSlaveX,-iSlaveY,1);
	}
	else if(dAngle > 225 ||  dAngle < 315)
	{
		if(m_nCarrierType == LEFT_CARRIER)
			set_offset(1, iMasterY,-iMasterX,1);
		else
			set_offset(1, iSlaveY,-iSlaveX, 1);
	}
	*/
	/*
	if(dAngle == 0)
	{
		if(m_nCarrierType == LEFT_CARRIER)
			set_offset(1, iMasterX,iMasterY,1);
		else
			set_offset(1, iSlaveX,iSlaveY,1);
	}
	else if(dAngle == 90)
	{
		if(m_nCarrierType == LEFT_CARRIER)
			set_offset(1, -iMasterY, iMasterX,1);
		else
			set_offset(1, -iSlaveY,iSlaveX, 1);
	}
	else if(dAngle == 180)
	{
		if(m_nCarrierType == LEFT_CARRIER)
			set_offset(1, -iMasterX,-iMasterY,1);
		else
			set_offset(1, -iSlaveX,-iSlaveY,1);
	}
	else if(dAngle == 270)
	{
		if(m_nCarrierType == LEFT_CARRIER)
			set_offset(1, iMasterY,-iMasterX,1);
		else
			set_offset(1, iSlaveY,-iSlaveX, 1);
	}
	*/

	
	
}

void CDsp::SetScaleData(int iMasterXScale, int iMasterYScale, int iSlaveXScale, int iSlaveYScale)
{
	
}

void CDsp::SetScaleData(int iMasterXScale, int iMasterYScale)
{
	
}

void CDsp::SetCalibrationData(CPoint (*MasterCalData)[MAX_CAL_DATA], CPoint (*SlavecalData)[MAX_CAL_DATA], short sNumberOfX, short sNumberOfY)
{
	
}

void CDsp::SetCalibrationData(CPoint (*MasterCalData)[MAX_CAL_DATA], short sNumberOfX, short sNumberOfY)
{
	
}


void CDsp::SetBinData()
{
	
}

void CDsp::SetBinItem(CString binNumber)
{
	
}


void CDsp::SetBinNumber()
{
	
}



void CDsp::SetParameterData()
{
///#ifdef _SIMUL_
	if(GetInitialStatus() != true) return;
//#endif	

	CPointerManager *pPointerManager = pPointerManager->GetInstance();
	CInitialTable *pInitialTable = pInitialTable->GetInstance();
	CString strCompany = _T("");
	double m_dMarkSpeed, m_dJumpSpeed;
	strCompany = pInitialTable->GetCompanyCode();
	
	
	int *pData = new int[KINDSOFPARAMETER];
	
	Iterator<CParameter*> *iterator = pPointerManager->GetParameterList()->iterator();
	
	m_iNumberOfParameter = 0;
	int i;
	while (iterator->HasNext()) {
		i = 0;
		CParameter *pParameter = iterator->GetCurrentItem();
		
		int itmp=0;  // EO Parameter와 매칭되도록 하기위해 수치변경
		itmp = pParameter->GetMarkStep();
		pData[i++] = itmp;
		pData[i++] = pParameter->GetJumpStep();
		itmp = pParameter->GetStepPeriod();
		
		{
			// 일단 List Mode로 바꾸고....
			
		    //set_list_mode(0); // List Mode...
			set_start_list(1);
			//set_scale(1, 0.684932, 1);
			double dCurrent;
			dCurrent = pParameter->GetLaserPowerSet();

#ifdef _RTC6_
			dCurrent = dCurrent / 10.0;
			write_da_1_list((unsigned short)((4095.0 * dCurrent) / 10.0));	ListCountPlus();
			//set_firstpulse_killer(pParameter->GetFPS() * LASER_PULSE_UNIT);	ListCountPlus();
			UINT unRepRate = (UINT)(double)(( 1.0 / (double)pParameter->GetFrequency() /2.0 ) * 1000.0  * LASER_PULSE_UNIT );		// HZ -> to Time
			UINT unPulseLength   = (UINT)(double)((double)pParameter->GetPulseWidth() * LASER_PULSE_UNIT );
			UINT nQswPulseDuty = (1000 / (double)pParameter->GetFrequency()) * ((double)pParameter->GetPulseWidth() / 100);
			//set_laser_pulses(unRepRate, unPulseLength);	ListCountPlus();

#else
			dCurrent = dCurrent / 10.0;
			write_da_1_list((unsigned short)((1023.0 * dCurrent) / 10.0));	ListCountPlus();
			set_firstpulse_killer(pParameter->GetFPS() * 8);ListCountPlus();
			if (pInitialTable->GetLaser() == LASER_LASERVALL)
			{
				float nQswFrequence = (1000 / pParameter->GetFrequency() / 2) / 0.125; 
				float nQswPulseDuty = ((double)pParameter->GetPulseWidth() / 1000.) / 0.125;

				set_laser_timing(nQswFrequence, nQswPulseDuty, pParameter->GetFPS() * 8, 1);ListCountPlus();
			}
			else
			{
				int nQswFrequence = 1000 / pParameter->GetFrequency() / 2;
				int nQswPulseDuty = (1000 / (double)pParameter->GetFrequency()) * ((double)pParameter->GetPulseWidth() / 100);

				set_laser_timing(nQswFrequence, nQswPulseDuty, pParameter->GetFPS() * 8, 0);ListCountPlus();
			}
#endif
			
		
			set_laser_delays(pParameter->GetLaserOnDelay(), pParameter->GetLaserOffDelay());ListCountPlus();
			//	set_scanner_delays(pParameter->GetJumpDelay()/10, pParameter->GetMarkDelay()/10, pParameter->GetStrokeDelay()/10);
			set_scanner_delays(pParameter->GetJumpDelay()/10, pParameter->GetMarkDelay()/10 ,pParameter->GetStrokeDelay()/10); ListCountPlus();
			
			// RTC Mark Step Max 0 ~ 50000 까지당...
			//	m_dMarkSpeed = (double)pParameter->GetMarkStep()*1000/pParameter->GetStepPeriod(); 
			m_dJumpSpeed = (double)pParameter->GetJumpStep()*100/pParameter->GetStepPeriod();
			m_dMarkSpeed = (double)pParameter->GetMarkStep()*100/pParameter->GetStepPeriod(); 
			//m_dJumpSpeed = (double)pParameter->GetJumpStep()*1000;
			
			set_mark_speed(m_dMarkSpeed );ListCountPlus();
			set_jump_speed(m_dJumpSpeed);ListCountPlus();

			//jjsjong 2018.09.04 TEST용
			if (pInitialTable->GetLaser() == LASER_FIBER && m_bAnalogPowerSet == false)
			/******************** Digital Out PuT *************************************/
			{
				unsigned short uSetPower=0;
				uSetPower =  (unsigned short)((pParameter->GetLaserPowerSet() / 100.) *255.);
#ifdef	_RTC4eth_
				//write_8bit_port((unsigned short)((para.GetRTCVoltage() / 100) *255));
				write_8bit_port_list((unsigned short)(uSetPower));ListCountPlus();
				//OutputIOList(RTCIO_O_MO, false);ListCountPlus();
				//OutputIOList(RTCIO_O_LATCH, false);ListCountPlus();
				//long_delay(LATCH_DELAY);ListCountPlus();
				//OutputIOList(RTCIO_O_LATCH, true);ListCountPlus();
				//OutputIOList(RTCIO_O_EMERGENCY, true);ListCountPlus();
				//OutputIOList(RTCIO_O_MO, true);ListCountPlus();
#endif

#ifdef _RTC_Test_ 
				write_8bit_port_list((unsigned short)(uSetPower));ListCountPlus();
				OutputIOList(RTCIO_O_MO, true);ListCountPlus();
				OutputIOList(RTCIO_O_GUIDEBEAM_ENABLE, false);ListCountPlus();
				long_delay(LATCH_DELAY);ListCountPlus();

#endif
			}
				
			
			set_end_of_list();
			execute_list(1);
			
		}
		
		iterator->SetNext();
		m_iNumberOfParameter++;
		
		break;	
	}
	delete iterator;
	delete [] pData;
	pData = NULL;
}



void CDsp::SetObjectNumber()
{
	
}

void CDsp::SetImageParameter(int iIntervalSize, int iDwellTime, int iLineMoveDelayTime)
{
/*
int errorinfo[3];

  errorinfo[0] = iIntervalSize;
  errorinfo[1] = iDwellTime;
  errorinfo[2] = iLineMoveDelayTime;
  
	SetData(0x9810, 3, errorinfo);
*/
}




void CDsp::SetVectorObjectData(int iObjNumber, double *pVectorData, int iNumberOfVector, int iParameterIndex, int iBinIndex)
{
/*
m_iNumberOfObj++;
SetObjectNumber();
int Buffersize = 5000;
// 벡터의 데이터를 DSP의 메모리를 보낸다
if(iNumberOfVector < Buffersize)
//if(iNumberOfVector*3 < ///0xAFC80/*0x807FF0 )
{
//SetVectorObjInfo(iObjNumber, iParameterIndex, iBinIndex, m_iVectorDataPosition, m_iVectorDataPosition+(iNumberOfVector * 3) -1);
SetVectorObjInfo(iObjNumber, iParameterIndex, iBinIndex, m_iVectorDataPosition, m_iVectorDataPosition+(iNumberOfVector * 3) -1);
SetData(m_iVectorDataPosition, iNumberOfVector*3, pVectorData);
m_iVectorDataPosition += (iNumberOfVector*3);
}
else//나눠서 보냄
{

  int *pVectorData_tmp;
  int size = (iNumberOfVector);
  int dwStorePos,startaddress,remain,loop;
  loop = (size / Buffersize) + 1;
  remain = 0;
  startaddress=0;
  //remain = size % loop;
  remain = size % Buffersize;
  //dwStorePos = size/loop;
  dwStorePos = Buffersize;
  dwStorePos = dwStorePos * 3;
  for(int i = 0; i< loop ; i++)
  {
		if(i == 0)
		{
		pVectorData_tmp = new int[dwStorePos];
		memcpy(pVectorData_tmp, pVectorData, (dwStorePos) * sizeof(int()));
		SetVectorObjInfo(iObjNumber, iParameterIndex, iBinIndex, m_iVectorDataPosition, m_iVectorDataPosition+(iNumberOfVector * 3)-1);
		SetData(m_iVectorDataPosition, dwStorePos, pVectorData_tmp);
		delete [] pVectorData_tmp;
		pVectorData_tmp = NULL;
		
		  }
		  else if(i == loop - 1)
		  {
		  dwStorePos = 0;
		  dwStorePos = remain;
		  dwStorePos = dwStorePos * 3;
		  
			pVectorData_tmp = new int[dwStorePos];
			memcpy(pVectorData_tmp, pVectorData+((i)*(Buffersize)*3) , (dwStorePos)* sizeof(int()));
			SetData(m_iVectorDataPosition, dwStorePos, pVectorData_tmp);
			delete [] pVectorData_tmp;
			pVectorData_tmp = NULL;
			}
			else
			{
			
			  dwStorePos = 0;
			  //dwStorePos += (size/loop);
			  dwStorePos += Buffersize;
			  dwStorePos = dwStorePos * 3;
			  
				delete pVectorData_tmp;
				pVectorData_tmp = NULL;
				pVectorData_tmp = new int[dwStorePos];
				
				  //memcpy(pVectorData_tmp, pVectorData+((i)*(size/loop)*3) , (dwStorePos)* sizeof(int()));
				  memcpy(pVectorData_tmp, pVectorData+((i)*(Buffersize)*3) , (dwStorePos)* sizeof(int()));
				  SetData(m_iVectorDataPosition, dwStorePos, pVectorData_tmp);
				  delete [] pVectorData_tmp;
				  pVectorData_tmp = NULL;
				  
					}
					m_iVectorDataPosition+=dwStorePos;
					
					  }
					  
						}
	*/	
}

void CDsp::SetPixelObjectData(int iObjNumber, double *pVectorData, int iNumberOfVector, int iParameterIndex, int iBinIndex)
{
/*	m_iNumberOfObj++;
SetObjectNumber();
int Buffersize = 5000;  //0x4A7A0
int MaxBuffer = 200000;
// 벡터의 데이터를 DSP의 메모리를 보낸다

  if(iNumberOfVector < MaxBuffer)
  {
		if(iNumberOfVector < Buffersize)
		{
		SetPixelObjInfo(iObjNumber, iParameterIndex, iBinIndex, m_iVectorDataPosition, m_iVectorDataPosition+(iNumberOfVector) -1);
		SetData(m_iVectorDataPosition, iNumberOfVector, pVectorData);
		m_iVectorDataPosition += (iNumberOfVector);
		}
		else//나눠서 보냄
		{
		int *pVectorData_tmp;
		int size = (iNumberOfVector);
		int dwStorePos,startaddress,remain,loop;
		loop = (size / Buffersize) + 1;
		remain = 0;
		startaddress=0;
		remain = size % Buffersize;
		dwStorePos = Buffersize;
		
		  for(int i = 0; i< loop ; i++)
		  {
		  if(i == 0)
		  {
		  pVectorData_tmp = new int[dwStorePos];
		  memcpy(pVectorData_tmp, pVectorData, (dwStorePos) * sizeof(int()));
		  SetPixelObjInfo(iObjNumber, iParameterIndex, iBinIndex, m_iVectorDataPosition, m_iVectorDataPosition+(iNumberOfVector)-1);
		  SetData(m_iVectorDataPosition, dwStorePos, pVectorData_tmp);
		  delete [] pVectorData_tmp;
		  pVectorData_tmp = NULL;
		  }
		  else
		  {
		  dwStorePos = 0;
		  if(i == loop - 1) 
		  dwStorePos = remain;
		  else
		  dwStorePos += Buffersize;
		  pVectorData_tmp = NULL;
		  pVectorData_tmp = new int[dwStorePos];
		  memcpy(pVectorData_tmp, pVectorData+((i)*(Buffersize)) , (dwStorePos)* sizeof(int()));
		  SetData(m_iVectorDataPosition, dwStorePos, pVectorData_tmp);
		  delete [] pVectorData_tmp;
		  pVectorData_tmp = NULL;
		  }
		  m_iVectorDataPosition+=dwStorePos;
		  }
		  }
		  }
		  else
		  {
		  int *pVectorData_tmp;
		  int size = (iNumberOfVector);
		  int dwStorePos,startaddress,remain,loop;
		  loop = (size / Buffersize) + 1;
		  remain = 0;
		  startaddress=0;
		  remain = size % Buffersize;
		  dwStorePos = Buffersize;
		  
			for(int i = 0; i< loop ; i++)
			{
			if(i == 0)
			{
			pVectorData_tmp = new int[dwStorePos];
			memcpy(pVectorData_tmp, pVectorData, (dwStorePos) * sizeof(int()));
			SetPixelObjInfo(iObjNumber, iParameterIndex, iBinIndex, m_iVectorDataPosition, m_iVectorDataPosition+(iNumberOfVector)-1);
			SetData(m_iVectorDataPosition, dwStorePos, pVectorData_tmp);
			delete [] pVectorData_tmp;
			pVectorData_tmp = NULL;
			}
			else
			{
			dwStorePos = 0;
			if(i == loop - 1) 
			dwStorePos = remain;
			else
			dwStorePos += Buffersize;
			pVectorData_tmp = NULL;
			pVectorData_tmp = new int[dwStorePos];
			memcpy(pVectorData_tmp, pVectorData+((i)*(Buffersize)) , (dwStorePos)* sizeof(int()));
			SetData(m_iVectorDataPosition, dwStorePos, pVectorData_tmp);
			delete [] pVectorData_tmp;
			pVectorData_tmp = NULL;
			}
			m_iVectorDataPosition+=dwStorePos;
			StartManualMarking();
			long loopCount = 0;
			while(GetMarkStatus() == 1)
			{
			loopCount ++;
			}
			StopAutoMarking();
			m_iVectorDataPosition = 0x00B000; // vector 데이터가 들어갈 위치
			
			  } 
			  }
*/
}

/*
void CDsp::SetObjInfo(int iType, int iObjNumber, int iParaindex, int iBinindex, int iVectorstartposition, int iVectorendposition)
{
int temp = 0;
switch(iType)
{
case STEXT:
case TTF:
case HPGL:
case BARCODE:
SetData(ADR_NUMBER_OF_OBJ+(m_iNumberOfObj*0x010), 1, &iObjNumber);
// obj의 데이터 시작, 끝나는 위치 넣기 
SetData(ADR_NUMBER_OF_OBJ+(m_iNumberOfObj*0x10+1), 1, &iVectorstartposition);
SetData(ADR_NUMBER_OF_OBJ+(m_iNumberOfObj*0x10+2), 1, &iVectorendposition);

		// obj의 파라미터 index넣기
		SetData(ADR_NUMBER_OF_OBJ+(m_iNumberOfObj*0x10+3), 1, &iParaindex);
		// obj의 bin index
		SetData(ADR_NUMBER_OF_OBJ+(m_iNumberOfObj*0x10+4), 1, &iBinindex);
		
		  temp = 0x01;	// HPGL TYPE
		  SetData(ADR_NUMBER_OF_OBJ+(m_iNumberOfObj*0x10+5), 1, &temp);
		  break;
		  case BITIMG:
		  case BARCODE2D:
		  SetData(ADR_NUMBER_OF_OBJ+(m_iNumberOfObj*0x010), 1, &iObjNumber);
		  
			// obj의 데이터 시작, 끝나는 위치 넣기
			SetData(ADR_NUMBER_OF_OBJ+(m_iNumberOfObj*0x10+1), 1, &iVectorstartposition);
			SetData(ADR_NUMBER_OF_OBJ+(m_iNumberOfObj*0x10+2), 1, &iVectorendposition);
			
			  // obj의 파라미터 index 넣기 
			  SetData(ADR_NUMBER_OF_OBJ+(m_iNumberOfObj*0x10+3), 1, &iParaindex);
			  // obj의 bin index 넣기
			  SetData(ADR_NUMBER_OF_OBJ+(m_iNumberOfObj*0x10+4), 1, &iBinindex);
			  
				temp = 0x02;	// IMAGE TYPE 
				SetData(ADR_NUMBER_OF_OBJ+(m_iNumberOfObj*0x10+5), 1, &temp);
				}
}*/

void CDsp::SetVectorObjInfo(int iObjNumber, int iParaindex, int iBinindex, int iVectorstartposition, int iVectorendposition)
{

}

void CDsp::SetPixelObjInfo(int iObjNumber, int iParaindex, int iBinindex, int iVectorstartposition, int iVectorendposition)
{

}

void CDsp::SetFieldValue(double maxField,double maxMM)
{

	assert(maxMM != 0);

	m_maxFieldHEAD2 = maxField;
	m_maxMMHEAD2 = maxMM;

	m_maxFieldHEAD1 = maxField;
	m_maxMMHEAD1 = maxMM;
}

int CDsp::GetMarkStatus()
{
	if(GetInitialStatus() != true) return false;

#ifdef	_RTC6_
	UINT busy, position;
	get_status(&busy, &position);
	return  busy;
#endif

#ifdef _RTC4eth_
	unsigned short busy, position;
	get_status(&busy, &position);
	return  busy;
#endif


}


int CDsp::GetMarkStatusHEAD2()
{
	if(GetInitialStatus() != true) return false;
	#ifdef	_SIMUL_
    return 0;
#endif

	UINT busy, position;
	n_get_status(RTC_CARD_NUM_2,&busy, &position);
	return  busy;


}

int CDsp::GetMarkStatusHEAD1()
{
	if(GetInitialStatus() != true) return false;

//#ifdef	_RTC6_
	UINT busy, position;
	n_get_status(RTC_CARD_NUM_1,&busy, &position);
	return  busy;
//#endif

}



void CDsp::SetDspFileName(char *fileName)
{

}


void CDsp::SetChipNumber(int iNumber)
{
	// 선택된 것만의 갯수를 넣어야함
	//SetData(CHIP_NUMBER, 1, &iNumber);	
}


void CDsp::SetMasterChipOffset(Vector *ltMasterOffset, int iNumberOfVector)
{
	Vector ptOffset;
	int iOffsetX, iOffsetY, iOffsetS;
	
	for (int i = 0; i < iNumberOfVector; i++) {
		ptOffset = ltMasterOffset[i];
		iOffsetX = (int)ptOffset.d.x;
		iOffsetY = (int)ptOffset.d.y;
		iOffsetS = (int )ptOffset.t;
		if(iOffsetS == 0) //2004.10.25 정종섭 디바이스 설정에서 빨강색이 커팅되도록(비전에선 반대로 처리하므로 빠뀜)
			iOffsetS = 1;
		else
			iOffsetS = 0;
		/*
			SetData(MASTER_CHIP_OFFSET + (i*2), 1, &iOffsetX);  // jin : *2 가 빠져있었네용  ㅜ.ㅜ 
			SetData(MASTER_CHIP_OFFSET + (i*2) + 1, 1, &iOffsetY);
		*/
	}
}

void CDsp::SetSlaveChipOffset(Vector *ltSlaveOffset, int iNumberOfVector)
{

}



void CDsp::SetLaserErrorToHandler()
{
}

int CDsp::GetBoardCount()
{
#ifdef	_SIMUL_
	return 2;
#endif
	if(GetInitialStatus() != true) return -1;

UINT RTCCountCards = 0;
#ifdef	_RTC6_
	 RTCCountCards = rtc6_count_cards();   //  number of cards found
#else
	 RTCCountCards = rtc5_count_cards();   //  number of cards found
#endif

	return (int)RTCCountCards;
}
void CDsp::LaserOn()
{
	if(GetInitialStatus() != true) return;
	enable_laser();
	laser_signal_on_list();
}

void CDsp::LaserOff()
{
	if(GetInitialStatus() != true) return;
	laser_signal_off_list();
}


UINT CDsp::GetErr()
{
#pragma region Error
/*
Bit Error type					no error

Bit #0 (LSB) = 1:				no board found
								(this error can only occur via init_RTC6_dll)

Bit #1 = 1:						access denied
								(this error can occur via init_RTC6_dll, select_rtc,
								acquire_rtc or any multi-board command)

Bit #2 = 1:						command not forwarded
								(this error implies an internal, PCI or driver error, e.g.
								caused by a hardware defect or an incorrect connection)

Bit #3 = 1:						no response from board
								(it is likely that no program has been loaded onto the
								RTC®5; this error can especially occur in connection with
								control commands that expect a response, e.g.
								get_hex_version)

Bit #4 = 1:						invalid parameter
								(this error can occur through all commands for which
								invalid parameters are not automatically corrected to valid
								values, e.g. parameters with limited choices such as
								get_head_para; if this error occurs for a list command, it
								will be replaced with list_nop; if this error occurs for a
								control command, it will not be executed)

Bit #5 = 1:						List processing is (not) active
								(e.g. for execute_list, if a list is currently being processed
								e.g. for stop_execution, if no list is currently being
								processed
								e.g. for restart_list, if pause_list was not previously
								called)

Bit #6 = 1:						List command rejected, illegal input pointer
								(e.g. for any list command directly after load_char +
								list_return: the list command will then not be loaded)
								Bit #7 = 1: List command was converted to a list_nop
								(e.g. set_end_of_list in a protected subroutine)

Bit #8 = 1:						Version error: DLL version (driver DLL), RTC version
								(firmware file) and HEX version (DSP program file) not
								compatible (also see load_program_file)

Bit #9 = 1:						Verify error: The download verification (see page 84) has
								detected an incorrect download.

Bit #10 = 1:					DSP version error: DSP version too old (this error only occurs
								with older RTC®5 boards – see get_rtc_version bits #16-23
								– and only through a few commands such as
								mark_ellipse_abs; the corresponding command
								description’s “Version info” section contains related
								comments; Commands that generate the error will neither
								be executed nor replaced by list_nop)

Bit #11 = 1:					A DLL-internal Windows memory request failed

Bit #12 = 1:					EEPROM read or write error (can occur during initialization
								or auto_cal)

Bits #13..#15 reserved
*/
#pragma endregion Error

	m_unErroNo = get_error();

	return m_unErroNo;

}



BOOL CDsp::LoadProgFile()
{
	if(GetInitialStatus() != true) return FALSE;
	// Description LoadProgram 
#pragma region ProgramFile
	/*
	command resets the RTC®5
	performs a DSP	memory check, initializes the memory configuration
	(in the default configuration), loads the firmware
	(RTC5RBF.rbf), the program file
	RTC5OUT.out and a binary support file
	(RTC5DAT.dat), and starts the signal processor

	starts the signal processor.
	After execution of this command, the position of
	the scanner will automatically be set to the null
	position (0|0) (i.e. the laser focus is centered in
	the image field) and laser control will be deactivated.

	*/
#pragma endregion ProgramFile

	m_unErroNo = load_program_file( m_caCfgPath );	

	TCHAR szErr[MAX_PATH] = {0, };
	BOOL bResult = FALSE;

	switch( m_unErroNo )
	{
	case 0: bResult = TRUE; break;
	case 1: memcpy( szErr, _T("Reset error: the board could not be reset."), sizeof( TCHAR)*MAX_PATH );									break;
	case 2: memcpy( szErr, _T("Unreset error: the board won’t restart."), sizeof( TCHAR)*MAX_PATH );										break;
	case 3: memcpy( szErr, _T("File error: file not found or can’t be opened."), sizeof( TCHAR)*MAX_PATH );								break;
	case 4: memcpy( szErr, _T("Format error: RTC5OUT.out has incorrect format."), sizeof( TCHAR)*MAX_PATH );								break;
	case 5: memcpy( szErr, _T("System error: not enough WINDOWS memory."), sizeof( TCHAR)*MAX_PATH );										break;
	case 6: memcpy( szErr, _T("Access error: board reserved for another application"), sizeof( TCHAR)*MAX_PATH );							break;
	case 7: memcpy( szErr, _T("Version error: DLL version (driver DLL), RTC version (firmware file) and HEX version (DSP program file)	not compatible"), sizeof( TCHAR)*MAX_PATH ); break;	
	case 8: memcpy( szErr, _T("System driver not found (get_last_error return code: RTC5_ACCESS_DENIED)"), sizeof( TCHAR)*MAX_PATH );		break;
	case 9: memcpy( szErr, _T("DriverCall error: loading of RTC5OUT.out file failed."), sizeof( TCHAR)*MAX_PATH );							break;
	case 10: memcpy( szErr, _T("Configuration error: DSP register initialization failed."), sizeof( TCHAR)*MAX_PATH );						break;
	case 11: memcpy( szErr, _T("Firmware error: loading of RTC5RBF.rbf file failed."), sizeof( TCHAR)*MAX_PATH );							break;
	case 12: memcpy( szErr, _T("PCI download error: loading of RTC5DAT.dat file failed."), sizeof( TCHAR)*MAX_PATH );						break;
	case 13: memcpy( szErr, _T("Busy error: Download locked, board is BUSY or INTERNAL-BUSY (get_last_error return code: RTC5_BUSY)"), sizeof( TCHAR)*MAX_PATH ); break;
	case 14: memcpy( szErr, _T("DSP memory error"), sizeof( TCHAR)*MAX_PATH );																break;
	case 15: memcpy( szErr, _T("Verify error (only applicable for download verification)"), sizeof( TCHAR)*MAX_PATH );						break;
	default:																																break;
	}

	if( bResult ) 
	{
		return TRUE;
	}
	else 
	{
		::MessageBox( NULL, szErr, _T("Fail to LoadProgram"), MB_OK );
		return FALSE;
	}
	
}


//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------

BOOL CDsp::LoadCorrectFile()
{
	if(GetInitialStatus() != true) return FALSE;
	CBeamEditor6App *pApp = (CBeamEditor6App*) AfxGetApp();
#pragma region CorrectionFile
	/*
	loads the specified image field correction file into RTC®5 memory (as table #1 or #2) and
	automatically calls select_cor_table with the most recently used parameter values (or the
	default parameter values).
	*/
#pragma endregion CorrectionFile

	TCHAR szPath[MAX_PATH] = {0, };
	::GetModuleFileName( NULL, szPath, _MAX_PATH); PathRemoveFileSpec( szPath );
	_stprintf( szPath, _T("%s%s"), szPath, _T("\\CFG\\CorrectionFile.ct5") );
	BOOL bResult = FALSE;
	TCHAR szErr[MAX_PATH] = {0, };

#ifdef _UNICODE	
	WideCharToMultiByte( CP_ACP, 0, szPath, sizeof( TCHAR)*MAX_PATH, m_caCfgPath, sizeof( CHAR)*MAX_PATH, NULL, NULL );

	UINT unMode = load_correction_file( m_caCfgPath, 1U, 2U );
	UINT unMode = load_correction_file( m_caCfgPath, 1U, 2U );
#else
	UINT ErrorCode = load_correction_file(  pApp->m_strCwd + DIRECTORY_NAME+ "CorrectionFile.ct5",   // initialize like "D2_1to1.ct5",
		1,   // table; #1 is used by default
		2 ); // use 2D only
#endif


	switch( ErrorCode )
	{
	case 0:	bResult = TRUE;
	case 1:	 memcpy( szErr, _T("File error (file corrupt or incomplete)."), sizeof( TCHAR)*MAX_PATH );			break;	
	case 2:	 memcpy( szErr, _T("Memory error (DLL-internal, WINDOWS system memory)."), sizeof( TCHAR)*MAX_PATH );			break;	
	case 3:	 memcpy( szErr, _T("File-open error (empty string submitted for Name parameter, file not found, etc.)."), sizeof( TCHAR)*MAX_PATH );			break;	
	case 4:	 memcpy( szErr, _T("DSP memory error"), sizeof( TCHAR)*MAX_PATH );			break;	
	case 5:	 memcpy( szErr, _T("PCI download error (driver error)."), sizeof( TCHAR)*MAX_PATH );			break;	
	case 8:	 memcpy( szErr, _T("System driver not found"), sizeof( TCHAR)*MAX_PATH );			break;	
	case 10: memcpy( szErr, _T("Parameter error (incorrect No)."), sizeof( TCHAR)*MAX_PATH );			break;	
	case 11: memcpy( szErr, _T("Access error: board reserved for another application"), sizeof( TCHAR)*MAX_PATH );			break;	
	case 12: memcpy( szErr, _T("Warning: 3D table or Dim "), sizeof( TCHAR)*MAX_PATH );			break;	
	case 13: memcpy( szErr, _T("Busy error: no download, board is BUSY or INTERNAL-BUSY"), sizeof( TCHAR)*MAX_PATH );			break;	
	case 14: memcpy( szErr, _T("PCI upload error (driver error, only applicable for download verification)"), sizeof( TCHAR)*MAX_PATH );			break;	
	case 15: memcpy( szErr, _T("Verify error (only applicable for download verification)"), sizeof( TCHAR)*MAX_PATH );			break;		
	}

	if( bResult )
	{
		/*
		= 0: turns off the signals for scan head A (primary scan head connector)
		= 1: assigns correction table #1 to scan head A
		= 2: assigns correction table #2 to scan head A
		(as an unsigned 32-bit value)
		*/
		select_cor_table( 1, 1 );
		return TRUE;
	}
	else 
	{
		::MessageBox( NULL, _T("Fail to Correctionfile File"), szErr, MB_OK );
		return FALSE;
	}

}


//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------

void CDsp::SelCorrectTable()
{
	if(GetInitialStatus() != true) return;
#pragma region Error
	/*
	HeadA	= 0: turns off the signals for scan head A (primary scan head connector)
			= 1: assigns correction table #1 to scan head A
			= 2: assigns correction table #2 to scan head A

	HeadB	= 0: turns off the signals for scan head B (secondary scan head connector)
			= 1: assigns correction table #1 to scan head B (activation required)
			= 2: assigns correction table #2 to scan head B (activation required)

	*/
#pragma endregion Error

	select_cor_table( 1U, 0U );
	/*
		HeadA 
		= 0: turns off the signals for scan head A (primary scan head connector)
		= 1: assigns correction table #1 to scan head A
		= 2: assigns correction table #2 to scan head A
		(as an unsigned 32-bit value)

		HeadB 
		= 0: turns off the signals for scan head B (secondary scan head connector)
		= 1: assigns correction table #1 to scan head B (activation required)
		= 2: assigns correction table #2 to scan head B (activation required)
		(as an unsigned 32-bit value)

	*/

}

void CDsp::SetParameterNumber(int number)	
{
	m_iNumberOfParameter = number;
	//m_iNumberOfParameter = 0;
}

void CDsp::SetParameterDataList()	
{
	if(GetInitialStatus() != true) return;
	CPointerManager *pPointerManager = pPointerManager->GetInstance();
	CInitialTable *pInitialTable = pInitialTable->GetInstance();
	CString strCompany = _T("");
	double dMarkSpeed, dJumpSpeed; //mm/sec
	strCompany = pInitialTable->GetCompanyCode();
//	set_list_mode(0);
	
	int *pData = new int[KINDSOFPARAMETER];
	
	Iterator<CParameter*> *iterator = pPointerManager->GetParameterList()->iterator();
	
	int nParaCount = 0;	
	int i;
	while (iterator->HasNext()) {
		if(nParaCount != m_iNumberOfParameter) 
		{
			nParaCount++;	
			iterator->SetNext();
			continue;
		}
		
		i = 0;
		CParameter *pParameter = iterator->GetCurrentItem();
		
		int itmp=0;  // EO Parameter와 매칭되도록 하기위해 수치변경
		itmp = pParameter->GetMarkStep();
		pData[i++] = itmp;
		pData[i++] = pParameter->GetJumpStep();
		itmp = pParameter->GetStepPeriod();
		
		//set_angle(1, -90, 1);
		double dCurrent;
		dCurrent = pParameter->GetLaserPowerSet();
#ifdef _RTC6_
		dCurrent = dCurrent / 10.0;
		write_da_1_list((unsigned short)((4095.0 * dCurrent) / 10.0));	ListCountPlus();
		set_firstpulse_killer(pParameter->GetFPS() * LASER_PULSE_UNIT);	ListCountPlus();

		UINT unRepRate = (UINT)(double)(( 1.0 / (double)pParameter->GetFrequency() /2.0 ) * 1000.0  * LASER_PULSE_UNIT );		// HZ -> to Time
		UINT unPulseLength   = (UINT)(double)((double)pParameter->GetPulseWidth() * LASER_PULSE_UNIT );

		UINT nQswPulseDuty = (1000 / (double)pParameter->GetFrequency()) * ((double)pParameter->GetPulseWidth() / 100);
		
		#ifdef _RTC_Test_ 
			set_laser_pulses(unRepRate, unPulseLength);	ListCountPlus();
		#endif
#else
		dCurrent = dCurrent / 10.0;
		//write_da_1_list((unsigned short)((1023.0 * dCurrent) / 10.0));	ListCountPlus();
		set_firstpulse_killer(pParameter->GetFPS() * 8);
		ListCountPlus();
		if (pInitialTable->GetLaser() == LASER_LASERVALL)
		{
			float nQswFrequence = (1000 / pParameter->GetFrequency() / 2) / 0.125; 
			float nQswPulseDuty = ((double)pParameter->GetPulseWidth() / 1000.) / 0.125;

			set_laser_timing(nQswFrequence, nQswPulseDuty, pParameter->GetFPS() * 8, 1);ListCountPlus();
		}
		else
		{
			int nQswFrequence = 1000 / pParameter->GetFrequency() / 2;
			int nQswPulseDuty = (1000 / (double)pParameter->GetFrequency()) * ((double)pParameter->GetPulseWidth() / 100);

			set_laser_timing(nQswFrequence, nQswPulseDuty, pParameter->GetFPS() * 8, 0);ListCountPlus();
		}
#endif


		//		}
		//		else
		//		{
		//			UINT nQswFrequence = 1000 / pParameter->GetFrequency() / 2;
		//			UINT nQswPulseDuty = (1000 / (double)pParameter->GetFrequency()) * ((double)pParameter->GetPulseWidth() / 100);
		//			set_laser_timing(nQswFrequence, nQswPulseDuty, pParameter->GetFPS() * LASER_PULSE_UNIT, 0);
		
		//			UINT unRepRate = (UINT)(double)(( 1.0 / (double)pParameter->GetFrequency() /2.0 ) * 1000000.0  * LASER_PULSE_UNIT );		// HZ -> to Time
		//			UINT unPulseLength   = (UINT)(double)((double)pParameter->GetPulseWidth() * LASER_PULSE_UNIT );
		//			set_laser_pulses_ctrl(unRepRate, unPulseLength);
		
		//			ListCountPlus();
		//		}
		
		//		set_standby(100 , 0);  
		//		ListCountPlus();
		
		set_laser_delays(pParameter->GetLaserOnDelay(), pParameter->GetLaserOffDelay());ListCountPlus();
		//	set_scanner_delays(pParameter->GetJumpDelay()/10, pParameter->GetMarkDelay()/10, pParameter->GetStrokeDelay()/10);
		set_scanner_delays(pParameter->GetJumpDelay()/10, pParameter->GetMarkDelay()/10 ,pParameter->GetStrokeDelay()/10);ListCountPlus();
		
		// RTC Mark Step Max 0 ~ 50000 까지...
		//fSpeed = ((double)m_iMarkStep * ((double)pInitialTable->GetMMSize() / (double)pInitialTable->GetFieldSize()) 
		dMarkSpeed = (double)pParameter->GetMarkStep()*100/pParameter->GetStepPeriod(); 
		dJumpSpeed = (double)pParameter->GetJumpStep()*100/pParameter->GetStepPeriod();
		//m_dMarkSpeed = (double)pParameter->GetMarkStep()*100/pParameter->GetStepPeriod(); 
		
		
		set_mark_speed(dMarkSpeed );ListCountPlus();
		set_jump_speed(dJumpSpeed);	ListCountPlus();

		//jjsjong 2018.09.04 TEST용
		if (pInitialTable->GetLaser() == LASER_FIBER && m_bAnalogPowerSet == false)
		{
			unsigned short uSetPower=0;
			uSetPower =  (unsigned short)((pParameter->GetLaserPowerSet() / 100.) *255.);

#ifdef	_RTC4eth_	
			//write_8bit_port((unsigned short)((para.GetRTCVoltage() / 100) *255));
			write_8bit_port_list((unsigned short)(uSetPower));ListCountPlus();
			//OutputIOList(RTCIO_O_LATCH, false);ListCountPlus();
			//OutputIOList(RTCIO_O_MO, false);ListCountPlus();
			//long_delay(LATCH_DELAY);ListCountPlus();
			//OutputIOList(RTCIO_O_LATCH, true);ListCountPlus();
			//OutputIOList(RTCIO_O_EMERGENCY, true);ListCountPlus();
			//OutputIOList(RTCIO_O_MO, true);ListCountPlus();
#endif

#ifdef _RTC_Test_ 
			write_8bit_port_list((unsigned short)(uSetPower));ListCountPlus();
			OutputIOList(RTCIO_O_MO, true);ListCountPlus();
			OutputIOList(RTCIO_O_GUIDEBEAM_ENABLE, false);ListCountPlus();
			long_delay(LATCH_DELAY);ListCountPlus();			
#endif

		}
		
		
		iterator->SetNext();
		
		//SetParameterNumber();
		if(nParaCount == m_iNumberOfParameter) 
			break;
		nParaCount++;	
	}


	

	delete iterator;
	delete [] pData;
	pData = NULL;
}

void CDsp::SetGotoXY(long x, long y)
{
	if(GetInitialStatus() != true) return;
	CInitialTable *pInitialTable = pInitialTable->GetInstance();
	if (pInitialTable->GetKindOfRtcBoard() == 1)	// 3rdEye selected
	{
	
	}
	else
	{
		goto_xy(x, y);
	}
}

int CDsp::GetListCount()
{
	return m_iListConunt;
}

void CDsp::SetListCount(int listCount)
{
	m_iListConunt = listCount;
}

void CDsp::ListCountPlus()
{
	m_iListConunt++;
}

void CDsp::Set_Angle(double dAngle)
{	
//#ifdef _RTC6_	
//	set_angle(1, dAngle, 1);
//#else

//#endif
}


void CDsp::WriteDA1(double voltage)
{
	if(GetInitialStatus() != true) return;
	//write_da_1((unsigned short)((1023 * voltage) / 10.0));

	double dCurrent = voltage / 10.0;
	write_da_1_list((unsigned short)((4095.0 * dCurrent) / 10.0));	
}


void CDsp::WriteDA2(double voltage)
{
	if(GetInitialStatus() != true) return;
	//write_da_2((unsigned short)((1023 * voltage) / 10.0));
	double dCurrent = voltage / 10.0;
	write_da_2_list((unsigned short)((4095.0 * dCurrent) / 10.0));	
}



void CDsp::nWriteDA1List(UINT cardNo,double voltage)
{
	if(GetInitialStatus() != true) return;
	//write_da_1((unsigned short)((1023 * voltage) / 10.0));

	double dCurrent = voltage / 10.0;
	n_write_da_1_list(cardNo,(unsigned short)((4095.0 * dCurrent) / 10.0));	
}


void CDsp::nWriteDA2List(UINT cardNo,double voltage)
{
	if(GetInitialStatus() != true) return;

	double dCurrent = voltage / 10.0;
	n_write_da_2_list(cardNo,(unsigned short)((4095.0 * dCurrent) / 10.0));	
}




BOOL CDsp::LoadCorrectionFile(double iMasterX, double iMasterY, double iSlaveX, double iSlaveY, double FieldAngle)
{
	if(GetInitialStatus() != true) return TRUE;
	CInitialTable *pInitialTable = pInitialTable->GetInstance();
	CBeamEditor6App *pApp = (CBeamEditor6App*) AfxGetApp();

	CString strError = "";


	return TRUE;
}


//
//void CDsp::OutputIO(unsigned int bit, BOOL value)
//{
//	if(GetInitialStatus() != true) return;
//	
//	unsigned short status = get_io_status();
//	if (value)
//	{
//		status |= (unsigned short)(pow(2.0, (double)bit));
//	}
//	else
//	{
//		status &= ~((unsigned short)(pow(2.0, (double)bit)));
//	}
//
//	write_io_port(status);
//}

void CDsp::SetDelay(unsigned int iSecond)
{
	DWORD dwTick = GetTickCount();
	MSG msg;
	
	while(GetTickCount() - dwTick < iSecond)
	{					
		if(PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			Sleep(0);
		}
	}
}

void CDsp::SetFlipHead1(BOOL bFlag)
{
	
	m_bFlipHead1 = bFlag;
}


void CDsp::SetFlipHead2(BOOL bFlag)
{
	
	m_bFlipHead2 = bFlag;
}


void CDsp::SetFirstStart(BOOL bFlag)
{
	m_bFirstStart = bFlag;
}



void CDsp::SetFirstStartHEAD1(BOOL bFlag)
{
	m_bFirstStartHEAD1 = bFlag;
}


void CDsp::nOutputIO(int nCardNo,unsigned int bit, bool value)
{
#ifdef _SIMUL_
	return;
#endif

	if(GetInitialStatus() != true) return;
	unsigned short status = n_get_io_status(nCardNo);
	if (value)
	{
		status |= (unsigned short)(pow(2.0,(double)bit));
	}
	else
	{
		status &= ~((unsigned short)(pow(2.0, (double)bit)));
	}

	
	n_write_io_port(nCardNo,status);

	int error = n_get_last_error(1);

	//n_write_io_port(2,status);

	//error = n_get_last_error(2);

	if(bit == RTC_SIG_O_ALARM && value == TRUE )
	{
		TRACE("RTC_SIG_O_ALARM");
	}

	
}

void CDsp::OutputIO(unsigned int bit, bool value)
{
	if(GetInitialStatus() != true) return;
	unsigned short status = get_io_status();
	if (value)
	{
		status |= (unsigned short)(pow(2.0,(double)bit));
	}
	else
	{
		status &= ~((unsigned short)(pow(2.0, (double)bit)));
	}

	
	n_write_io_port(1,status);

	int error = n_get_last_error(1);

	if(GetBoardCount() > 1)
	{
		n_write_io_port(2,status);

		error = n_get_last_error(2);
	}
}


void CDsp::OutputIOList(unsigned int bit, bool value)
{
	if(GetInitialStatus() != true) return;
	if (value)
		set_io_cond_list(0, 0, (unsigned short)(pow(2.0, (double)bit)));
	else
		clear_io_cond_list(0, 0, (unsigned short)(pow(2.0, (double)bit)));
}

void CDsp::NOutputIOList(UINT headNo, unsigned int bit, bool value)
{
#ifndef _RTC_Test_
	return;
#endif

	if(GetInitialStatus() != true) return;

	UINT uValue =  0;

	if(value == TRUE)
	{
		
		if(bit == RTC_SIG_O_FIRST_TAB)
		{
			uValue = 0x0D;
			n_write_io_port_list(headNo, uValue);
		}
	}
	else
	{
		
		if(bit == RTC_SIG_O_FIRST_TAB)
		{
			uValue = 0x05;
			n_write_io_port_list(headNo, uValue);
		}
	}

	//if (value)
	//	n_set_io_cond_list(headNo,0, 0, (unsigned short)(pow(2.0, (double)bit)));
	//	//n_write_io_port_list
	//else
	//	n_clear_io_cond_list(headNo,0, 0, (unsigned short)(pow(2.0, (double)bit)));

	//
	//if(bit == RTC_SIG_O_ALARM && value == TRUE )
	//{
	//	TRACE("RTC_SIG_O_ALARM");
	//}

}


void CDsp::GetEncode(long & x, long & y)
{
#ifdef	_SIMUL_
	return;
#endif

	if(GetInitialStatus() != true) return;

	get_encoder(&x, &y);

}

void CDsp::GetEncodeHEAD2(long &x, long &y)
{
#ifdef	_SIMUL_
	return;
#endif
	if(GetInitialStatus() != true) return;
if(GetBoardCount() > 1)
	n_get_encoder(RTC_CARD_NUM_2,&x, &y);
}
void CDsp::GetEncodeHEAD1(long &x, long &y)
{
#ifdef	_SIMUL_
	return;
#endif
	if(GetInitialStatus() != true) return;

	
	n_get_encoder(RTC_CARD_NUM_1,&x, &y);
}

void CDsp::ReadEncodeHEAD1(long &encoder0_0, long &encoder1_0,long &encoder0_1,long &encoder1_1)
{
	if(GetInitialStatus() != true) return;
	n_read_encoder(RTC_CARD_NUM_1, &encoder0_0, &encoder1_0,&encoder0_1,&encoder1_1);
}

void CDsp::ReadEncodeHEAD2(long &encoder0_0, long &encoder1_0,long &encoder0_1,long &encoder1_1)
{
	if(GetInitialStatus() != true) return;
	n_read_encoder(RTC_CARD_NUM_2, &encoder0_0, &encoder1_0,&encoder0_1,&encoder1_1);
}


void CDsp::SetFlyX(double x)
{
	if(GetInitialStatus() != true) return;
//#if _RTCSCANALONE_
	set_fly_x(x);
	m_dPreFlyX = x;
//#endif
}

void CDsp::SetFlyY(double y)
{
	if(GetInitialStatus() != true) return;
//#if _RTCSCANALONE_
	set_fly_y(y);
	m_dPreFlyY = y;
//#endif
}

void CDsp::FlyReturn(long x, long y)
{
	if(GetInitialStatus() != true) return;

#ifndef _SCANSIMUL
	
		fly_return(x, y);
	//if_fly_x_overflow(1);
	//OutputIOList(RTC_SIG_O_ALARM, TRUE);
	//if_fly_x_overflow(-1);
	//OutputIOList(RTC_SIG_O_ALARM, TRUE);
#else

		goto_xy(x,y);
#endif
}

void CDsp::N_Fly_Return(UINT cardNo, long x,long y)
{
	if(GetInitialStatus() != true) return;

#ifndef _SCANSIMUL
		n_fly_return(cardNo, x, y);
	//if_fly_x_overflow(1);
	//OutputIOList(RTC_SIG_O_ALARM, TRUE);
	//if_fly_x_overflow(-1);
	//OutputIOList(RTC_SIG_O_ALARM, TRUE);
#else
	goto_xy(x,y);
#endif
}


void CDsp::N_Fly_Return(UINT cardNo, double x,double y, int unit)
{
	if(GetInitialStatus() != true) return;

	double dMmSize, dFieldSize;
	CFieldParameter *pFieldParameter = CFieldParameter::GetInstance();
	pFieldParameter->GetSize(&dMmSize, &dFieldSize);
	CTransUnit	*pTransUnit = pTransUnit->GetInstance(dFieldSize, dMmSize);

	if(unit == MM)
	{
		 x = pTransUnit->GetField(x, MM);
		 y = pTransUnit->GetField(y, MM);
	}


#ifndef _SCANSIMUL
	n_fly_return(cardNo, x, y);
	//if_fly_x_overflow(1);
	//OutputIOList(RTC_SIG_O_ALARM, TRUE);
	//if_fly_x_overflow(-1);
	//OutputIOList(RTC_SIG_O_ALARM, TRUE);
#else
	goto_xy(x,y);
#endif
}


void CDsp::ResetRTC(void)
{
	if(GetInitialStatus() != true) return;

	long flyX=0, flyY=0;

#ifdef	_RTC6_
	//set_fly_2d(0,0);
	//store_encoder(0);
	//set_fly_x_pos(0);
	InitDsp();
	return;
#endif


 FlyReturn(flyX,flyY);

// init_fly_2d(0,0);
//store_encoder(0);
}


void CDsp::SetSimulate_Encoder(int nMode)
{
#ifdef	_SIMUL_
	return;
#endif

	if(GetInitialStatus() != true) return;

	n_Simulate_Encode = nMode;
	if(n_Simulate_Encode > 0)
	{
		n_simulate_encoder(1,n_Simulate_Encode);// 0:Off, 1: X, 2: Y, 3: X & Y
		n_simulate_encoder(2,n_Simulate_Encode);
	}
	else
	{
		n_Simulate_Encode = 0;
		n_simulate_encoder(1,n_Simulate_Encode);
		n_simulate_encoder(2,n_Simulate_Encode);
	}
}


int CDsp::GetSimulate_Encoder(void)
{
	return n_Simulate_Encode;
}


void CDsp::SetControlMode(unsigned int mode)
{
	if(GetInitialStatus() != true) return;
	set_control_mode(mode);
}


bool CDsp::GetInitialStatus(void)
{
	return m_bInitialStatus;
}


void CDsp::StopExecution(void)
{
	if(GetInitialStatus() != true) return;

	TListExeStat stStat; stStat.clear();
	stStat = ReadStatusHEAD1();
	if(stStat.bBusy1 == TRUE|| stStat.bBusy2 == TRUE)
		n_stop_execution(1);

	if(GetBoardCount() > 1)
	{
		stStat = ReadStatusHEAD2();
		if(stStat.bBusy1 == TRUE|| stStat.bBusy2 == TRUE)
			n_stop_execution(2);
	}

}


void CDsp::Disable_Laser(void)
{
	if(GetInitialStatus() != true) return;

	//return; 

	int nBoardCnt = GetBoardCount();
	
	for(int i = 1; i <= nBoardCnt; i++)
	{
		n_disable_laser(i);
	}
}


void CDsp::Enable_Laser(void)
{
	if(GetInitialStatus() != true) return;
	int nBoardCnt = GetBoardCount();
	
	for(int i = 1; i <= nBoardCnt; i++)
	{
		n_enable_laser(i);
	}
}


void CDsp::SetReady(void)
{
	if(GetInitialStatus() != true) return;

	int nPortNum;
	unsigned short status = ReadIoPort();
	unsigned short value = 0;

#ifdef _RTC_Test_ 

	//unsigned short status = ReadIoPort();
	//unsigned short value = 0;

	nPortNum = RTCIO_O_LATCH;
	status = GetIoStatus();
	value = status & (unsigned short)((double)pow(2.0, nPortNum));
	value = value >> nPortNum;

	if(value)
		OutputIO(nPortNum, FALSE);
	else
		OutputIO(nPortNum, TRUE);
	

	nPortNum = RTCIO_O_MO;
	status = GetIoStatus();
	value = status & (unsigned short)((double)pow(2.0, nPortNum));
	value = value >> nPortNum;

	if(value)
		OutputIO(nPortNum, FALSE);
	else
		OutputIO(nPortNum, TRUE);
	


	nPortNum = RTCIO_O_EMERGENCY;
	status = GetIoStatus();
	value = status & (unsigned short)((double)pow(2.0, nPortNum));
	value = value >> nPortNum;

	if(value)
		OutputIO(nPortNum, FALSE);
	else
		OutputIO(nPortNum, TRUE);
#endif

#ifdef  _RTC4eth_

	nPortNum = RTCIO_O_LATCH;
	status = GetIoStatus();
	value = status & (unsigned short)((double)pow(2.0, nPortNum));
	value = value >> nPortNum;

	if(value)
		OutputIO(nPortNum, FALSE);
	else
		OutputIO(nPortNum, TRUE);
	

	nPortNum = RTCIO_O_MO;
	status = GetIoStatus();
	value = status & (unsigned short)((double)pow(2.0, nPortNum));
	value = value >> nPortNum;

	if(value)
		OutputIO(nPortNum, FALSE);
	else
		OutputIO(nPortNum, TRUE);
	


	nPortNum = RTCIO_O_EMERGENCY;
	status = GetIoStatus();
	value = status & (unsigned short)((double)pow(2.0, nPortNum));
	value = value >> nPortNum;

	if(value)
		OutputIO(nPortNum, FALSE);
	else
		OutputIO(nPortNum, TRUE);
#endif

	//////////// 아래처럼 하면 안되는 이유를 모르겠다...ㅠㅠㅠㅠ
//
//	//unsigned short uSetPower=0;
//	//uSetPower =  (unsigned short)((pParameter->GetLaserPowerSet() / 100.) *255.);
//		//write_8bit_port((unsigned short)((para.GetRTCVoltage() / 100) *255));
//	//write_8bit_port((unsigned short)(uSetPower));ListCountPlus();
//	enable_laser();
//#ifdef	_RTC4eth_
//	OutputIO(RTCIO_O_LATCH, false);
//	OutputIO(RTCIO_O_MO, false);
//	Sleep(LATCH_DELAY);
//	OutputIO(RTCIO_O_LATCH, true);
//	OutputIO(RTCIO_O_EMERGENCY, true);
//	OutputIO(RTCIO_O_MO, true);
//#endif
//	
//#ifdef _RTC_Test_ 
//	OutputIO(RTCIO_O_LATCH, false);
//	Sleep(LATCH_DELAY);
//	OutputIO(RTCIO_O_MO, false);
//	Sleep(LATCH_DELAY);
//	OutputIO(RTCIO_O_LATCH, true);
//	Sleep(LATCH_DELAY);
//	OutputIO(RTCIO_O_EMERGENCY, true);
//	Sleep(LATCH_DELAY);
//	OutputIO(RTCIO_O_MO, true);
//#endif

	
}

void CDsp::SetParameterDataList_Change_ByDistance(double dBaseDistance, double dApplyDistance)
{
	if(GetInitialStatus() != true) return;

	CFieldParameter *pFieldParameter = pFieldParameter->GetInstance();
	CPointerManager *pPointerManager = pPointerManager->GetInstance();
	CInitialTable *pInitialTable = pInitialTable->GetInstance();
	CString strCompany = _T("");
	double dMarkSpeed, dJumpSpeed; //mm/sec
	strCompany = pInitialTable->GetCompanyCode();


	int *pData = new int[KINDSOFPARAMETER];

	Iterator<CParameter*> *iterator = pPointerManager->GetParameterList()->iterator();
	iterator->SetFirst();
	int nParaCount = 0;	
	int i;
	//while (iterator->HasNext()) 
	{
		/*if(nParaCount != m_iNumberOfParameter) 
		{
			nParaCount++;	
			iterator->SetNext();
			continue;
		}
*/
		i = 0;
		CParameter *pParameter = iterator->GetCurrentItem();

		double itmp=0;  // EO Parameter와 매칭되도록 하기위해 수치변경
		itmp = pParameter->GetMarkStep();
		pData[i++] = itmp;
		pData[i++] = pParameter->GetJumpStep();
		itmp = pParameter->GetStepPeriod();

		//set_angle(1, -90, 1);

		double dCurrent;
		if(m_iNumberOfParameter == PARA_INDEX_UNFLAG)
			dCurrent = pParameter->GetUnflagPower();
		else if(m_iNumberOfParameter == PARA_INDEX_FLAG)
			dCurrent = pParameter->GetFlagPower();
		else if(m_iNumberOfParameter == PARA_INDEX_UNFLAG)
			dCurrent = pParameter->GetUnflagInoutPower();
		else if(m_iNumberOfParameter == PARA_INDEX_UNFLAG_INOUT)
			dCurrent = pParameter->GetFlagExtPower();
		else if(m_iNumberOfParameter == PARA_INDEX_DUMMY)
			dCurrent = pParameter->GetEndExtPower();

		




#ifdef _RTC6_
		dCurrent = dCurrent / 10.0;
		write_da_1_list((unsigned short)((4095.0 * dCurrent) / 10.0));	ListCountPlus();
		//set_firstpulse_killer(pParameter->GetFPS() * LASER_PULSE_UNIT);ListCountPlus();

		UINT unRepRate = (UINT)(double)(( 1.0 / (double)pParameter->GetFrequency() /2.0 ) * 1000.0  * LASER_PULSE_UNIT );		// HZ -> to Time
		UINT unPulseLength   = (UINT)(double)((double)pParameter->GetPulseWidth() * LASER_PULSE_UNIT );

		UINT nQswPulseDuty = (1000 / (double)pParameter->GetFrequency()) * ((double)pParameter->GetPulseWidth() / 100);
		
		#ifdef _RTC_Test_ 
			set_laser_pulses(unRepRate, unPulseLength);	ListCountPlus();
		#endif
		
#else
		dCurrent = dCurrent / 10.0;
		write_da_1_list((unsigned short)((1023.0 * dCurrent) / 10.0));	ListCountPlus();
		//set_firstpulse_killer(pParameter->GetFPS() * 8); ListCountPlus();
		if (pInitialTable->GetLaser() == LASER_LASERVALL)
		{
			float nQswFrequence = (1000 / pParameter->GetFrequency() / 2) / 0.125; 
			float nQswPulseDuty = ((double)pParameter->GetPulseWidth() / 1000.) / 0.125;

			set_laser_timing(nQswFrequence, nQswPulseDuty, pParameter->GetFPS() * 8, 1);ListCountPlus();
		}
		else
		{
			int nQswFrequence = 1000 / pParameter->GetFrequency() / 2;
			int nQswPulseDuty = (1000 / (double)pParameter->GetFrequency()) * ((double)pParameter->GetPulseWidth() / 100);

			//set_laser_timing(nQswFrequence, nQswPulseDuty, pParameter->GetFPS() * 8, 0);ListCountPlus();
		}
#endif


		//		}
		//		else
		//		{
		//			UINT nQswFrequence = 1000 / pParameter->GetFrequency() / 2;
		//			UINT nQswPulseDuty = (1000 / (double)pParameter->GetFrequency()) * ((double)pParameter->GetPulseWidth() / 100);
		//			set_laser_timing(nQswFrequence, nQswPulseDuty, pParameter->GetFPS() * LASER_PULSE_UNIT, 0);

		//			UINT unRepRate = (UINT)(double)(( 1.0 / (double)pParameter->GetFrequency() /2.0 ) * 1000000.0  * LASER_PULSE_UNIT );		// HZ -> to Time
		//			UINT unPulseLength   = (UINT)(double)((double)pParameter->GetPulseWidth() * LASER_PULSE_UNIT );
		//			set_laser_pulses_ctrl(unRepRate, unPulseLength);

		//			ListCountPlus();
		//		}

		//		set_standby(100 , 0);  
		//		ListCountPlus();

		//set_laser_delays(pParameter->GetLaserOnDelay(), pParameter->GetLaserOffDelay());ListCountPlus();
		//set_scanner_delays(pParameter->GetJumpDelay()/10, pParameter->GetStrokeDelay()/10,pParameter->GetMarkDelay()/10 );ListCountPlus();
//
		if (pInitialTable->GetLaser() == LASER_FIBER && m_bAnalogPowerSet == false)
		{
			unsigned short uSetPower=0;
			uSetPower =  (unsigned short)((pParameter->GetLaserPowerSet() / 100.) *255.);
#ifdef	_RTC4eth_
			//write_8bit_port((unsigned short)((para.GetRTCVoltage() / 100) *255));
			write_8bit_port_list((unsigned short)(uSetPower));ListCountPlus();
	/*		OutputIOList(RTCIO_O_LATCH, false);ListCountPlus();
			OutputIOList(RTCIO_O_MO, false);ListCountPlus();
			long_delay(LATCH_DELAY);ListCountPlus();
			OutputIOList(RTCIO_O_LATCH, true);ListCountPlus();
			OutputIOList(RTCIO_O_EMERGENCY, true);ListCountPlus();
			OutputIOList(RTCIO_O_MO, true);ListCountPlus();*/
#endif

#ifdef _RTC_Test_ 
			write_8bit_port_list((unsigned short)(uSetPower));ListCountPlus();
			OutputIOList(RTCIO_O_MO, true);ListCountPlus();
			OutputIOList(RTCIO_O_GUIDEBEAM_ENABLE, false);ListCountPlus();
			long_delay(LATCH_DELAY);ListCountPlus();			
#endif

		}

		// RTC Mark Step Max 0 ~ 50000 까지...
		//fSpeed = ((double)m_iMarkStep * ((double)pInitialTable->GetMMSize() / (double)pInitialTable->GetFieldSize()) 
		
		double m_dMarkStep = 0;

		if(m_iNumberOfParameter == PARA_INDEX_UNFLAG)
		{
			m_dMarkStep = pParameter->GetUnflagLineSpeed();
		}
		else if(m_iNumberOfParameter == PARA_INDEX_FLAG)
		{
			m_dMarkStep = pParameter->GetFlagSpeed();
		}
		else if(m_iNumberOfParameter == PARA_INDEX_UNFLAG)
		{
			m_dMarkStep = pParameter->GetUnflagInoutSpeed();
		}
		else if(m_iNumberOfParameter == PARA_INDEX_UNFLAG_INOUT)
		{
			m_dMarkStep = pParameter->GetFlagExtSpeed();
		}
		else if(m_iNumberOfParameter == PARA_INDEX_DUMMY)
		{
			m_dMarkStep = pParameter->GetEndExtSpeed();
		}
		m_dMarkStep = ((double)m_dMarkStep * (10 / 1000000.)) * 10 / ((double)pInitialTable->GetMMSize() / (double)pInitialTable->GetFieldSize());

		dMarkSpeed = (double)m_dMarkStep*100/pParameter->GetStepPeriod(); 

		/*if(m_iNumberOfParameter == PARA_INDEX_FLAG_EXT)
			dMarkSpeed = (double)pParameter->GetUnflagLineSpeed()*100/pParameter->GetStepPeriod(); 
		else if(m_iNumberOfParameter == PARA_INDEX_FLAG)
			dMarkSpeed = (double)pParameter->GetFlagSpeed()*100/pParameter->GetStepPeriod(); 
		else if(m_iNumberOfParameter == PARA_INDEX_UNFLAG)
			dMarkSpeed = (double)pParameter->GetUnflagInoutSpeed()*100/pParameter->GetStepPeriod(); 
		else if(m_iNumberOfParameter == PARA_INDEX_UNFLAG_INOUT)
			dMarkSpeed = (double)pParameter->GetFlagExtSpeed()*100/pParameter->GetStepPeriod(); 
		else if(m_iNumberOfParameter == PARA_INDEX_UNFLAG_INOUT_EXT)
			dMarkSpeed = (double)pParameter->GetEndExtSpeed()*100/pParameter->GetStepPeriod(); */


		double fSpeed;
		fSpeed = ((double)pParameter->GetMarkStep() * ((double)pInitialTable->GetMMSize() / (double)pInitialTable->GetFieldSize()) 
				/ ((double)pParameter->GetStepPeriod() / 1000000.)) / 10;

		double dScale=0.0;
		//#define NORMAL_MARK_MODE 0
		//#define TIMED_MARK_MODE  1
		//#define SPEED_MARK_MODE  2
		//MarkSpeed = (double)dApplyDistance*100/pParameter->GetStepPeriod(); 


		if(n_ScannerVariableMode == SPEED_MARK_MODE)
		{
		   dScale = (dBaseDistance / dApplyDistance);// 속도 제어시

			//dScale = dApplyDistance - dBaseDistance;// 속도 제어시

		   if(dScale < 1)
		   {
			   dScale = dScale * m_dSpeedScale;
		   }
		   else
		   {
			   dScale = 1;
		   }
		   dMarkSpeed = dMarkSpeed * (dScale) ; // 속도 가변 제어시 사용
		}
		else if(n_ScannerVariableMode == TIMED_MARK_MODE)
		{
			double dBaseMarkingTime,dCurMarkingTime,dTimeDiff,dRollSpeed,dBaseRolltime,dCurRolltime,dRolltimeDiff = 0.0;
			dRollSpeed = pFieldParameter->GetRollSpeed();

			dScale = dApplyDistance / dBaseDistance ; //시간 제어시에는 길수록 시간이 더 늘어남. 시간 가변 제어시 사용
			dBaseMarkingTime = dBaseDistance  / fSpeed;
			dCurMarkingTime = dApplyDistance / fSpeed; //Line Marking Time 구함.
			dTimeDiff = dCurMarkingTime - dBaseMarkingTime;
			
			dBaseRolltime = dBaseDistance / dRollSpeed; //Line Marking Time 구함.
			dCurRolltime = dApplyDistance / dRollSpeed; //Line Marking Time 구함.
			dRolltimeDiff = dCurRolltime - dBaseRolltime;
			
			
			m_dtimed_marktime = dBaseMarkingTime - dTimeDiff - dRolltimeDiff;
		}
		
		
		if(m_iNumberOfParameter == PARA_INDEX_SIMUL)
			dJumpSpeed = 1500;
		else
			dJumpSpeed = (double)pParameter->GetJumpStep()*100/pParameter->GetStepPeriod();

		//set_laser_delays(pParameter->GetLaserOnDelay(), pParameter->GetLaserOffDelay());ListCountPlus();
		set_scanner_delays(pParameter->GetJumpDelay()/10, (pParameter->GetMarkDelay()/10) ,pParameter->GetStrokeDelay()/10);ListCountPlus();

		if(n_ScannerVariableMode != TIMED_MARK_MODE)
		{
			set_mark_speed(dMarkSpeed );ListCountPlus();
			set_jump_speed(dJumpSpeed);	ListCountPlus();
		}

		//iterator->SetNext();

		////SetParameterNumber();
		//if(nParaCount == m_iNumberOfParameter) 
		//	break;
		//nParaCount++;	
	}




	delete iterator;
	delete [] pData;
	pData = NULL;
}


void CDsp::SetParameterDataList_Change(void)
{

	//return;
	if(GetInitialStatus() != true) return;
	CPointerManager *pPointerManager = pPointerManager->GetInstance();
	CInitialTable *pInitialTable = pInitialTable->GetInstance();
	CString strCompany = _T("");
	double dMarkSpeed, dJumpSpeed; //mm/sec
	strCompany = pInitialTable->GetCompanyCode();
	CFieldParameter *pFieldParameter = pFieldParameter->GetInstance();
	
	
	int *pData = new int[KINDSOFPARAMETER];
	
	Iterator<CParameter*> *iterator = pPointerManager->GetParameterList()->iterator();
	iterator->SetFirst();
	int nParaCount = 0;	
	int i;
	//while (iterator->HasNext()) 
	//{
		//2019.06.20 첫번쨰 파라메터만 사용하도록 수정. jjsjong
		/*if(nParaCount != m_iNumberOfParameter) 
		{
			nParaCount++;	
			iterator->SetNext();
			continue;
		}*/
		
		i = 0;
		CParameter *pParameter = iterator->GetCurrentItem();
		
		int itmp=0;  // EO Parameter와 매칭되도록 하기위해 수치변경
		itmp = pParameter->GetMarkStep();
		pData[i++] = itmp;
		pData[i++] = pParameter->GetJumpStep();
		itmp = pParameter->GetStepPeriod();
		
		//set_angle(1, -90, 1);

		//2019.06.20 첫번쨰 파라메터만 사용하도록 수정. jjsjong
		double dCurrent;
		dCurrent = 0.0;
		if(m_iNumberOfParameter == PARA_INDEX_UNFLAG)
			dCurrent = pParameter->GetUnflagPower();
		else if(m_iNumberOfParameter == PARA_INDEX_FLAG)
			dCurrent = pParameter->GetFlagPower();
		else if(m_iNumberOfParameter == PARA_INDEX_UNFLAG_INOUT)
			dCurrent = pParameter->GetUnflagInoutPower();
		else if(m_iNumberOfParameter == PARA_INDEX_FLAG_EXT)
			dCurrent = pParameter->GetFlagExtPower();	
		else if(m_iNumberOfParameter == PARA_INDEX_UNFLAG_INOUT_EXT)
			dCurrent = pParameter->GetUnflagInoutPower();
		else if(m_iNumberOfParameter == PARA_INDEX_UNFLAG_EXT)
			dCurrent = pParameter->GetUnflagPower();
		else if(m_iNumberOfParameter == PARA_INDEX_DUMMY)
			dCurrent = pParameter->GetEndExtPower();




#ifdef _RTC6_
		dCurrent = dCurrent / 10.0;
		write_da_1_list((unsigned short)((4095.0 * dCurrent) / 10.0));	ListCountPlus();
		//long_delay(100);
		//set_firstpulse_killer(pParameter->GetFPS() * LASER_PULSE_UNIT);ListCountPlus();

		UINT unRepRate = (UINT)(double)(( 1.0 / (double)pParameter->GetFrequency() /2.0 ) * 1000.0  * LASER_PULSE_UNIT );		// HZ -> to Time
		UINT unPulseLength   = (UINT)(double)((double)pParameter->GetPulseWidth() * LASER_PULSE_UNIT );

		UINT nQswPulseDuty = (1000 / (double)pParameter->GetFrequency()) * ((double)pParameter->GetPulseWidth() / 100);
		//#ifdef _RTC_Test_ 
		//	set_laser_pulses(unRepRate, unPulseLength);	ListCountPlus();
		/*#endif*/
#else
		dCurrent = dCurrent / 10.0;
		write_da_1_list((unsigned short)((1023.0 * dCurrent) / 10.0));	ListCountPlus();
		//set_firstpulse_killer(pParameter->GetFPS() * 8); ListCountPlus();
		if (pInitialTable->GetLaser() == LASER_LASERVALL)
		{
			float nQswFrequence = (1000 / pParameter->GetFrequency() / 2) / 0.125; 
			float nQswPulseDuty = ((double)pParameter->GetPulseWidth() / 1000.) / 0.125;

			set_laser_timing(nQswFrequence, nQswPulseDuty, pParameter->GetFPS() * 8, 1);ListCountPlus();
		}
		else
		{
			int nQswFrequence = 1000 / pParameter->GetFrequency() / 2;
			int nQswPulseDuty = (1000 / (double)pParameter->GetFrequency()) * ((double)pParameter->GetPulseWidth() / 100);

			//set_laser_timing(nQswFrequence, nQswPulseDuty, pParameter->GetFPS() * 8, 0);ListCountPlus();
		}
#endif


		//		}
		//		else
		//		{
		//			UINT nQswFrequence = 1000 / pParameter->GetFrequency() / 2;
		//			UINT nQswPulseDuty = (1000 / (double)pParameter->GetFrequency()) * ((double)pParameter->GetPulseWidth() / 100);
		//			set_laser_timing(nQswFrequence, nQswPulseDuty, pParameter->GetFPS() * LASER_PULSE_UNIT, 0);
		
		//			UINT unRepRate = (UINT)(double)(( 1.0 / (double)pParameter->GetFrequency() /2.0 ) * 1000000.0  * LASER_PULSE_UNIT );		// HZ -> to Time
		//			UINT unPulseLength   = (UINT)(double)((double)pParameter->GetPulseWidth() * LASER_PULSE_UNIT );
		//			set_laser_pulses_ctrl(unRepRate, unPulseLength);
		
		//			ListCountPlus();
		//		}
		
		//		set_standby(100 , 0);  
		//		ListCountPlus();
		
		set_laser_delays(pParameter->GetLaserOnDelay(), pParameter->GetLaserOffDelay());ListCountPlus();
		set_scanner_delays(pParameter->GetJumpDelay()/10, pParameter->GetMarkDelay()/10 ,pParameter->GetStrokeDelay()/10);ListCountPlus();
		
		//if (pInitialTable->GetLaser() == LASER_FIBER && m_bAnalogPowerSet == false)
		{
			unsigned short uSetPower=0;
			uSetPower =  (unsigned short)((pParameter->GetLaserPowerSet() / 100.) *255.);
#ifdef	_RTC4eth_
			//write_8bit_port((unsigned short)((para.GetRTCVoltage() / 100) *255));
			write_8bit_port_list((unsigned short)(uSetPower));ListCountPlus();
			//OutputIOList(RTCIO_O_LATCH, false);ListCountPlus();
			//OutputIOList(RTCIO_O_MO, false);ListCountPlus();
			//long_delay(RTCIO_O_LATCH);ListCountPlus();
			//OutputIOList(RTCIO_O_LATCH, true);ListCountPlus();
			//OutputIOList(RTCIO_O_EMERGENCY, true);ListCountPlus();
			//OutputIOList(RTCIO_O_MO, true);ListCountPlus();
#endif

#ifdef _RTC_Test_ 
			//write_8bit_port((unsigned short)((para.GetRTCVoltage() / 100) *255));
			write_8bit_port_list((unsigned short)(uSetPower));ListCountPlus();
			OutputIOList(RTCIO_O_MO, true);ListCountPlus();
			OutputIOList(RTCIO_O_GUIDEBEAM_ENABLE, false);ListCountPlus();
			long_delay(LATCH_DELAY);ListCountPlus();			
#endif

		//}



		// RTC Mark Step Max 0 ~ 50000 까지...
		//fSpeed = ((double)m_iMarkStep * ((double)pInitialTable->GetMMSize() / (double)pInitialTable->GetFieldSize()) 

		//----------------------------------------------------------------------------------------------------------
		//??????????????????????????????????????????????????????????????????????????????????????????????????????????
		/*if(m_iNumberOfParameter == PARA_INDEX_FLAG_EXT)
			dMarkSpeed = (double)pParameter->GetUnflagLineSpeed()*100/pParameter->GetStepPeriod(); 
		else if(m_iNumberOfParameter == PARA_INDEX_FLAG)
			dMarkSpeed = (double)pParameter->GetFlagSpeed()*100/pParameter->GetStepPeriod(); 
		else if(m_iNumberOfParameter == PARA_INDEX_UNFLAG)
			dMarkSpeed = (double)pParameter->GetUnflagInoutSpeed()*100/pParameter->GetStepPeriod(); 
		else if(m_iNumberOfParameter == PARA_INDEX_UNFLAG_INOUT)
			dMarkSpeed = (double)pParameter->GetFlagExtSpeed()*100/pParameter->GetStepPeriod(); 
		else if(m_iNumberOfParameter == PARA_INDEX_UNFLAG_INOUT_EXT)
			dMarkSpeed = (double)pParameter->GetEndExtSpeed()*100/pParameter->GetStepPeriod(); */
		//----------------------------------------------------------------------------------------------------------

			double m_dMarkStep = 0;

		if(m_iNumberOfParameter == PARA_INDEX_UNFLAG)
		{
			m_dMarkStep = pParameter->GetUnflagLineSpeed();
		}
		else if(m_iNumberOfParameter == PARA_INDEX_FLAG)
		{
			m_dMarkStep = pParameter->GetFlagSpeed();
		}
		else if(m_iNumberOfParameter == PARA_INDEX_UNFLAG_INOUT)
		{
			m_dMarkStep = pParameter->GetUnflagInoutSpeed();
		}
		else if(m_iNumberOfParameter == PARA_INDEX_FLAG_EXT)
		{
			m_dMarkStep = pParameter->GetFlagExtSpeed();
		}
		else if(m_iNumberOfParameter == PARA_INDEX_UNFLAG_INOUT_EXT)
		{
			m_dMarkStep = pParameter->GetUnFlagInoutExtSpeed();
		}
		else if(m_iNumberOfParameter == PARA_INDEX_UNFLAG_EXT)
		{
			m_dMarkStep = pParameter->GetNonFlagLineExtSpeed();
		}
		else if(m_iNumberOfParameter == PARA_INDEX_DUMMY)
		{
			m_dMarkStep = pParameter->GetEndExtSpeed();
		}




		m_dMarkStep = ((double)m_dMarkStep * (10 / 1000000.)) * 10 / ((double)pInitialTable->GetMMSize() / (double)pInitialTable->GetFieldSize());

		dMarkSpeed = (double)m_dMarkStep*100/pParameter->GetStepPeriod(); //20191211 장민국 test
		//if(m_iNumberOfParameter == PARA_INDEX_UNFLAG)
		//dMarkSpeed = pFieldParameter->GetMultispeed(m_iChangeLineSpeedIndex);


		//dMarkSpeed = (double)pParameter->GetMarkStep()*100/pParameter->GetStepPeriod(); 
		if(m_iNumberOfParameter == PARA_INDEX_SIMUL)
			dJumpSpeed = 1500;
		else
		{

			if(m_iNumberOfParameter == PARA_INDEX_FLAG)
			{
				if(m_bFirstStart == TRUE)
				{
					dJumpSpeed = (double)pParameter->GetJumpStep()*100/pParameter->GetStepPeriod();
									
				}
				else
				{
					double dTempFlagJumpStep = pParameter->GetFlagJumpStep();
					dJumpSpeed = (double)dTempFlagJumpStep*100/pParameter->GetStepPeriod();	
				}

				if(Get1stFlagStep() == TRUE)
				{
					double dTempFlagJumpStep = pParameter->GetFlagJumpStep();
					dJumpSpeed = (double)dTempFlagJumpStep*100/pParameter->GetStepPeriod() * 1.1;	
					//dJumpSpeed = (double)dTempFlagJumpStep*100/pParameter->GetStepPeriod();	
					Set1stFlagStep(FALSE);
				}

			}
			else
			{
				dJumpSpeed = (double)pParameter->GetJumpStep()*100/pParameter->GetStepPeriod();
			}
		}
			
		set_mark_speed(dMarkSpeed );ListCountPlus();
		m_dSettedCurrMarkSpeed = dMarkSpeed;
		set_jump_speed(dJumpSpeed);	ListCountPlus();
	
		//iterator->SetNext();
		
		//SetParameterNumber();
	//	if(nParaCount == m_iNumberOfParameter) 
	//		break;
	//	nParaCount++;	
	}


	

	delete iterator;
	delete [] pData;
	pData = NULL;
}


void CDsp::Set_Matrix(double cs, double sn)
{
	if(GetInitialStatus() != true) return;
	set_matrix(1, cs,-sn,sn,cs, 1);
}

void CDsp::SetMatrixHEAD2(double cs, double sn)
{
	if(GetInitialStatus() != true) return;

	if(m_bFlipHead2)
		n_set_matrix(RTC_CARD_NUM_2,1, cs,sn,sn,-cs, 1);
	else
		n_set_matrix(RTC_CARD_NUM_2,1, cs,-sn,sn,cs, 1);

}

void CDsp::SetMatrixHEAD1(double cs,double sn)
{
	if(GetInitialStatus() != true) return;
	
	if(m_bFlipHead1)
		n_set_matrix(RTC_CARD_NUM_1,1, cs,sn,sn,-cs, 1);
	else
		n_set_matrix(RTC_CARD_NUM_1,1, cs,-sn,sn,cs, 1);

}


void CDsp::SetGotoXYHEAD2(double x,double y)
{
	if(GetInitialStatus() != true) return;
	assert(m_maxMMHEAD2 != 0);
	//n_goto_xy(RTC_CARD_NUM_2,x * m_maxFieldHEAD2 / m_maxMMHEAD2,y * m_maxFieldHEAD2 / m_maxMMHEAD2);
	n_goto_xy(RTC_CARD_NUM_2, x, y);
}
void CDsp::SetGotoXYHEAD1(double x,double y)
{
	if(GetInitialStatus() != true) return;
	assert(m_maxMMHEAD1 != 0);
	//n_goto_xy(RTC_CARD_NUM_1,x * m_maxFieldHEAD1 / m_maxMMHEAD1,y * m_maxFieldHEAD1 / m_maxMMHEAD1);
	n_goto_xy(RTC_CARD_NUM_1,x, y);
}


void CDsp::SetGotoXYHEAD2(double x,double y, int unit)
{
	if(GetInitialStatus() != true) return;
	assert(m_maxMMHEAD2 != 0);

	double dMmSize, dFieldSize;
	CFieldParameter *pFieldParameter = CFieldParameter::GetInstance();
	pFieldParameter->GetSize(&dMmSize, &dFieldSize);
	CTransUnit	*pTransUnit = pTransUnit->GetInstance(dFieldSize, dMmSize);


	if(unit == MM)
	{
		 x = pTransUnit->GetField(x, MM);
		 y = pTransUnit->GetField(y, MM);
	}

	//n_goto_xy(RTC_CARD_NUM_2,x * m_maxFieldHEAD2 / m_maxMMHEAD2,y * m_maxFieldHEAD2 / m_maxMMHEAD2);
	n_goto_xy(RTC_CARD_NUM_2, x, y);
}
void CDsp::SetGotoXYHEAD1(double x,double y, int unit)
{
	if(GetInitialStatus() != true) return;
	assert(m_maxMMHEAD1 != 0);

	double dMmSize, dFieldSize;
	CFieldParameter *pFieldParameter = CFieldParameter::GetInstance();
	pFieldParameter->GetSize(&dMmSize, &dFieldSize);
	CTransUnit	*pTransUnit = pTransUnit->GetInstance(dFieldSize, dMmSize);


	if(unit == MM)
	{
		 x = pTransUnit->GetField(x, MM);
		 y = pTransUnit->GetField(y, MM);
	}

	//n_goto_xy(RTC_CARD_NUM_1,x * m_maxFieldHEAD1 / m_maxMMHEAD1,y * m_maxFieldHEAD1 / m_maxMMHEAD1);
	n_goto_xy(RTC_CARD_NUM_1,x, y);
}


void CDsp::EnableLaserHEAD2()
{
	if(GetInitialStatus() != true) return;
	n_enable_laser(RTC_CARD_NUM_2);
}
void CDsp::EnableLaserHEAD1()
{
	if(GetInitialStatus() != true) return;
	n_enable_laser(RTC_CARD_NUM_1);
}


void CDsp::DisableLaserHEAD2()
{
	if(GetInitialStatus() != true) return;
	n_disable_laser(RTC_CARD_NUM_2);
}
void CDsp::DisableLaserHEAD1()
{
	if(GetInitialStatus() != true) return;
	n_disable_laser(RTC_CARD_NUM_1);
}


void CDsp::StopExcutionHEAD2()
{
	if(GetInitialStatus() != true) return;
	n_stop_execution(RTC_CARD_NUM_2);

}
void CDsp::StopExcutionHEAD1()
{
	if(GetInitialStatus() != true) return;
	n_stop_execution(RTC_CARD_NUM_1);
}

void CDsp::WriteIOHEAD2(unsigned int bit, int value)
{
	#ifdef _SIMUL_
	return;
#endif
	if(GetInitialStatus() != true) return;
	unsigned short status = n_get_io_status(RTC_CARD_NUM_2);
	if (value)
	{
		status |= (unsigned short)(pow(2.0,(double)bit));
	}
	else
	{
		status &= ~((unsigned short)(pow(2.0, (double)bit)));
	}

	
	n_write_io_port(RTC_CARD_NUM_2,status);

}
void CDsp::WriteIOHEAD1(unsigned int bit, int value)
{
	if(GetInitialStatus() != true) return;
	unsigned short status = n_get_io_status(RTC_CARD_NUM_1);
	if (value)
	{
		status |= (unsigned short)(pow(2.0,(double)bit));
	}
	else
	{
		status &= ~((unsigned short)(pow(2.0, (double)bit)));
	}

	
	n_write_io_port(RTC_CARD_NUM_1,status);

}


void CDsp::SetStartListHEAD2(UINT listNo)
{
	#ifdef _SIMUL_
	return;
#endif
	if(GetInitialStatus() != true) return;
	n_set_start_list(RTC_CARD_NUM_2,listNo);
}

void CDsp::SetStartListHEAD1(UINT listNo)
{
	#ifdef _SIMUL_
	return;
#endif
	if(GetInitialStatus() != true) return;
	n_set_start_list(RTC_CARD_NUM_1,listNo);
	m_iEncoderPos=0;
}

void CDsp::ClearFlyOverflowHEAD2(UINT mode)
{
	if(GetInitialStatus() != true) return;
	n_clear_fly_overflow(RTC_CARD_NUM_2,mode);
}
void CDsp::ClearFlyOverflowHEAD1(UINT mode)
{
#ifdef _SIMUL_
	return;
#endif

	if(GetInitialStatus() != true) return;
	n_clear_fly_overflow(RTC_CARD_NUM_1,mode);
}


void CDsp::SetFlyLimitsHEAD2(double xMin, double xMax, double yMin, double yMax)
{
	#ifdef _SIMUL_
	return;
#endif
	if(GetInitialStatus() != true) return;
	n_set_fly_limits(RTC_CARD_NUM_2,xMin,xMax,yMin,yMax);
}
void CDsp::SetFlyLimitsHEAD1(double xMin, double xMax, double yMin, double yMax)
{
#ifdef _SIMUL_
	return;
#endif
	if(GetInitialStatus() != true) return;
	n_set_fly_limits(RTC_CARD_NUM_1,xMin,xMax,yMin,yMax);
}


void CDsp::SetFlyXHEAD2(double scaleX)
{
#ifdef _SIMUL_
	return;
#endif
	double dScale = 0.0;
	CMathUtil mathUtil;
	dScale = mathUtil.Round(scaleX, 8);

	if(GetInitialStatus() != true) return;
	n_set_fly_x(RTC_CARD_NUM_2,dScale);
}
void CDsp::SetFlyXHEAD1(double scaleX)
{
#ifdef _SIMUL_
	return;
#endif
	
	if(GetInitialStatus() != true) return;
	double dScale = 0.0;
	CMathUtil mathUtil;
	dScale = mathUtil.Round(scaleX, 8);

	if(GetInitialStatus() != true) return;
	n_set_fly_x(RTC_CARD_NUM_1,dScale);
}


void CDsp::Activivate_Fly_2d_Encoder(UINT CardNo, double ScaleX, double ScaleY, LONG EncX, LONG EncY)
{
#ifdef _SIMUL_
	return;
#endif
	if(GetInitialStatus() != true) return;


}

void CDsp::SetFlyYHEAD2(double scaleY)
{
#ifdef _SIMUL_
	return;
#endif
	if(GetInitialStatus() != true) return;

	double dScale = 0.0;
	CMathUtil mathUtil;
	dScale = mathUtil.Round(scaleY, 8);

	if(GetInitialStatus() != true) return;
	n_set_fly_y(RTC_CARD_NUM_2,dScale);
}

void CDsp::SetFlyYHEAD1(double scaleY)
{
#ifdef _SIMUL_
	return;
#endif
	if(GetInitialStatus() != true) return;

	double dScale = 0.0;
	CMathUtil mathUtil;
	dScale = mathUtil.Round(scaleY, 8);

	n_set_fly_y(RTC_CARD_NUM_1,dScale);
}

void CDsp::JumpAbsHEAD2(double x,double y)
{
	if(GetInitialStatus() != true) return;

#ifndef _SCANSIMUL
	n_jump_abs(RTC_CARD_NUM_2,x* m_maxFieldHEAD2 / m_maxMMHEAD2,y* m_maxFieldHEAD2 / m_maxMMHEAD2);
	//if_fly_x_overflow(1);
	//OutputIOList(RTC_SIG_O_ALARM, TRUE);
	//if_fly_x_overflow(-1);
	//OutputIOList(RTC_SIG_O_ALARM, TRUE);
#else
	goto_xy(x* m_maxFieldHEAD2 / m_maxMMHEAD2,y* m_maxFieldHEAD2 / m_maxMMHEAD2);
#endif
}


void CDsp::JumpAbsHEAD1(double x, double y)
{
	if(GetInitialStatus() != true) return;

#ifndef _SCANSIMUL
	n_jump_abs(RTC_CARD_NUM_1,x* m_maxFieldHEAD1 / m_maxMMHEAD1,y* m_maxFieldHEAD1 / m_maxMMHEAD1);
	//if_fly_x_overflow(1);
	//OutputIOList(RTC_SIG_O_ALARM, TRUE);
	//if_fly_x_overflow(-1);
	//OutputIOList(RTC_SIG_O_ALARM, TRUE);
#else
	goto_xy(x* m_maxFieldHEAD1 / m_maxMMHEAD1,y* m_maxFieldHEAD1 / m_maxMMHEAD1);
#endif
}


void CDsp::MarkAbsHEAD2(double x, double y)
{
	if(GetInitialStatus() != true) return;
	n_mark_abs(RTC_CARD_NUM_2,x* m_maxFieldHEAD2 / m_maxMMHEAD2,y* m_maxFieldHEAD2 / m_maxMMHEAD2);
}

void CDsp::MarkAbsHEAD1(double x, double y)
{
	if(GetInitialStatus() != true) return;
	n_mark_abs(RTC_CARD_NUM_1, x* m_maxFieldHEAD1 / m_maxMMHEAD1,y* m_maxFieldHEAD1 / m_maxMMHEAD1);
}


void CDsp::FlyReturnHEAD2(double x,double y)
{
	if(GetInitialStatus() != true) return;

	n_fly_return(RTC_CARD_NUM_2 , x * m_maxFieldHEAD2 / m_maxMMHEAD2, y * m_maxFieldHEAD2 / m_maxMMHEAD2);

}
void CDsp::FlyreturnHEAD1(double x,double y)
{
	if(GetInitialStatus() != true) return;
	n_fly_return(RTC_CARD_NUM_1 , x * m_maxFieldHEAD1 / m_maxMMHEAD1, y * m_maxFieldHEAD1 / m_maxMMHEAD1);
}


void CDsp::OutputIOListHEAD2(unsigned int bit,bool value)
{
	if(GetInitialStatus() != true) return;
	if (value)
		n_set_io_cond_list(RTC_CARD_NUM_2,0, 0, (unsigned short)(pow(2.0, (double)bit)));
	else
		n_clear_io_cond_list(RTC_CARD_NUM_2,0, 0, (unsigned short)(pow(2.0, (double)bit)));
}
void CDsp::OutputIOListHEAD1(unsigned int bit,bool value)
{
	if(GetInitialStatus() != true) return;
	if (value)
		n_set_io_cond_list(RTC_CARD_NUM_1,0, 0, (unsigned short)(pow(2.0, (double)bit)));
	else
		n_clear_io_cond_list(RTC_CARD_NUM_1,0, 0, (unsigned short)(pow(2.0, (double)bit)));
}

UINT CDsp::GetMarkingInfoHEAD2()
{
	if(GetInitialStatus() != true) return TRUE;
	UINT markingInfo = n_get_marking_info(RTC_CARD_NUM_2);
	return  markingInfo;
}
UINT CDsp::GetMarkingInfoHEAD1()
{
	if(GetInitialStatus() != true) return TRUE;
	UINT markingInfo = n_get_marking_info(RTC_CARD_NUM_1);
	return  markingInfo;
}

TListExeStat CDsp::ReadStatusHEAD2()
{
	UINT unStat = 0;
	TListExeStat stStat; stStat.clear();

	if(GetInitialStatus() != true) return stStat;

	unStat = n_read_status(RTC_CARD_NUM_2);
	stStat.bLoad1  = ( unStat >> 0 ) & 0x1;
	stStat.bLoad2  = ( unStat >> 1 ) & 0x1;
	stStat.bBusy1  = ( unStat >> 4 ) & 0X1;
	stStat.bBusy2  = ( unStat >> 5 ) & 0X1;
	stStat.bReady1 = ( unStat >> 2 ) & 0X1;
	stStat.bReady2 = ( unStat >> 3 ) & 0X1;
	stStat.bUsed1 =  ( unStat >> 6 ) & 0X1;
	stStat.bUsed2 =  ( unStat >> 7 ) & 0X1;

	return stStat;

}
TListExeStat CDsp::ReadStatusHEAD1()
{
	UINT unStat = 0;
	TListExeStat stStat; stStat.clear();

	if(GetInitialStatus() != true) return stStat;

	unStat = n_read_status(RTC_CARD_NUM_1);
	stStat.bLoad1  = ( unStat >> 0 ) & 0x1;
	stStat.bLoad2  = ( unStat >> 1 ) & 0x1;
	stStat.bBusy1  = ( unStat >> 4 ) & 0X1;
	stStat.bBusy2  = ( unStat >> 5 ) & 0X1;
	stStat.bReady1 = ( unStat >> 2 ) & 0X1;
	stStat.bReady2 = ( unStat >> 3 ) & 0X1;
	stStat.bUsed1 =  ( unStat >> 6 ) & 0X1;
	stStat.bUsed2 =  ( unStat >> 7 ) & 0X1;

	return stStat;
}


void CDsp::WaitForEncoderHEAD2(long value, int encoderNo)
{
	#ifdef _SIMUL_
	return;
#endif
	if(GetInitialStatus() != true) return;
	n_wait_for_encoder(RTC_CARD_NUM_2,value,encoderNo);
}
void CDsp::WaitForEncoderHEAD1(long value, int encoderNo)
{
	#ifdef _SIMUL_
	return;
#endif
	if(GetInitialStatus() != true) return;
	n_wait_for_encoder(RTC_CARD_NUM_1,value,encoderNo);
	//n_store_encoder(RTC_CARD_NUM_1, 0);
	//n_store_encoder(RTC_CARD_NUM_1, 1);
	//n_store_encoder(RTC_CARD_NUM_1, m_iEncoderPos);
	//m_iEncoderPos++;
	
}

void CDsp::WaitForEncoderModeHEAD2(long value, int encoderNo, int mode)
{
	#ifdef _SIMUL_
	return;
#endif
	if(GetInitialStatus() != true) return;
	n_wait_for_encoder_mode(RTC_CARD_NUM_2,value,encoderNo,mode);
}
void CDsp::WaitForEncoderModeHEAD1(long value, int encoderNo, int mode)
{
	#ifdef _SIMUL_
	return;
#endif
	
	//n_wait_for_encoder_mode(RTC_CARD_NUM_1,value,encoderNo,0);

	n_wait_for_encoder_mode(RTC_CARD_NUM_1,value,encoderNo,mode);
}


void CDsp::SetEndOfListHEAD2()
{
	if(GetInitialStatus() != true) return;
	n_set_end_of_list(RTC_CARD_NUM_2);
}
void CDsp::SetEndOfListHEAD1()
{
	if(GetInitialStatus() != true) return;
	n_set_end_of_list(RTC_CARD_NUM_1);
}

TListExeStat CDsp::ReadStatus()
{

	UINT unStat = 0;
	TListExeStat stStat; stStat.clear();

	if(GetInitialStatus() != true) return stStat;

	unStat = read_status();
	m_tListExeStat.bLoad1  = ( unStat >> 0 ) & 0x1;
	m_tListExeStat.bLoad2  = ( unStat >> 1 ) & 0x1;
	m_tListExeStat.bBusy1  = ( unStat >> 4 ) & 0X1;
	m_tListExeStat.bBusy2  = ( unStat >> 5 ) & 0X1;
	m_tListExeStat.bReady1 = ( unStat >> 2 ) & 0X1;
	m_tListExeStat.bReady2 = ( unStat >> 3 ) & 0X1;
	m_tListExeStat.bUsed1 =  ( unStat >> 6 ) & 0X1;
	m_tListExeStat.bUsed2 =  ( unStat >> 7 ) & 0X1;

	stStat = m_tListExeStat;
	return stStat;

	//if(m_tListExeStat.bBusy1 && m_tListExeStat.bBusy2 )
	//	return TRUE;
	//else 
	//	return FALSE;
}

TListExeStat CDsp::NReadStatus(UINT headNo)
{
	UINT unStat = 0;
	TListExeStat stStat; stStat.clear();

	if(GetInitialStatus() != true) return stStat;

	unStat = n_read_status(headNo);
	stStat.bLoad1  = ( unStat >> 0 ) & 0x1;
	stStat.bLoad2  = ( unStat >> 1 ) & 0x1;
	stStat.bBusy1  = ( unStat >> 4 ) & 0X1;
	stStat.bBusy2  = ( unStat >> 5 ) & 0X1;
	stStat.bReady1 = ( unStat >> 2 ) & 0X1;
	stStat.bReady2 = ( unStat >> 3 ) & 0X1;
	stStat.bUsed1 =  ( unStat >> 6 ) & 0X1;
	stStat.bUsed2 =  ( unStat >> 7 ) & 0X1;

	//stStat = m_tListExeStat;
	return stStat;
}


int CDsp::GetPosX()
{
	if(GetInitialStatus() != true) return 0;
	int m_lEncX;
	m_lEncX = get_value(GET_GAlVANO_X);
	return m_lEncX;
}

int CDsp::GetPosY()
{
	if(GetInitialStatus() != true) return 0;
	int m_lEncY;
	m_lEncY = get_value(GET_GAlVANO_Y);
	return m_lEncY;

}

int CDsp::nGetPosX(UINT CardNo)
{
	if(GetInitialStatus() != true) return 0;
	int m_lEncX;
	m_lEncX = n_get_value(CardNo,GET_GAlVANO_X);
	return m_lEncX;
}

int CDsp::nGetPosY(UINT CardNo)
{
	if(GetInitialStatus() != true) return 0;
	int m_lEncY;
	m_lEncY = n_get_value(CardNo,GET_GAlVANO_Y);
	return m_lEncY;

}


void CDsp::nPauseList(UINT CardNo)
{
	if(GetInitialStatus() != true) return;
	n_pause_list(CardNo);
}

void CDsp::nRestartList(UINT CardNo)
{
	if(GetInitialStatus() != true) return;
	n_restart_list(CardNo);
}


UINT CDsp::GetDllVer()
{
	return m_unDllVer;

}


//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------

UINT CDsp::GetHexVer()
{

	return m_unHexVer;

}


//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------

UINT CDsp::GetRtcVer()
{	
	
	return m_unRtcVer;

}


//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------

UINT CDsp::GetSerialNum()
{

	return m_unSerialNum;

}



void CDsp::GetHeadStat()
{

	if(GetInitialStatus() != true) return;
	UINT unHeadStat = get_head_status(1);

	m_tHeadInfo.bPosAckX  = ( unHeadStat >> 3 ) & 0x1;	
	m_tHeadInfo.bPosAckY  = ( unHeadStat >> 4 ) & 0x1;	

	m_tHeadInfo.bTempStat = ( unHeadStat >> 6 ) & 0x1;	
	m_tHeadInfo.bPwrStat  = ( unHeadStat >> 7 ) & 0x1;	

	/*
	bSignal = m_tHeadInfo.Bit::bPosAckY;
	bSignal = m_tHeadInfo.Bit::bPwrStat;
	bSignal = m_tHeadInfo.Bit::bTempStat;
	*/
}

void CDsp::Mark_Abs(int x, int y)
{
   if(GetInitialStatus() != true) return;



#ifndef _SCANSIMUL
	mark_abs(x,y);
	//if_fly_x_overflow(1);
	//OutputIOList(RTC_SIG_O_ALARM, TRUE);
	//if_fly_x_overflow(-1);
	//OutputIOList(RTC_SIG_O_ALARM, TRUE);

#else
	goto_xy(x,y);
#endif
}

void CDsp::N_Mark_Abs(UINT cardNo,double x, double y, int unit)
{
	double dMmSize, dFieldSize;
	CFieldParameter *pFieldParameter = CFieldParameter::GetInstance();
	pFieldParameter->GetSize(&dMmSize, &dFieldSize);
	CTransUnit	*pTransUnit = pTransUnit->GetInstance(dFieldSize, dMmSize);
	
	
	if(GetInitialStatus() != true) return;

	if(unit == MM)
	{
		 x = pTransUnit->GetField(x, MM);
		 y = pTransUnit->GetField(y, MM);
	}

#ifndef _SCANSIMUL
	n_mark_abs(cardNo,x,y);
#else
	OutputIO(RTCIO_O_GUIDEBEAM_ENABLE, TRUE);
	goto_xy(x,y);
#endif

}

void CDsp::N_Mark_Abs(UINT cardNo,int x, int y)
{
	if(GetInitialStatus() != true) return;


#ifndef _SCANSIMUL
	n_mark_abs(cardNo,x,y);
#else
	OutputIO(RTCIO_O_GUIDEBEAM_ENABLE, TRUE);
	goto_xy(x,y);
#endif

}


void CDsp::N_Mark_Rel(UINT cardNo,int x, int y)
{
	if(GetInitialStatus() != true) return;


#ifndef _SCANSIMUL
	n_mark_rel(cardNo,x,y);

#else
	OutputIO(RTCIO_O_GUIDEBEAM_ENABLE, TRUE);
	goto_xy(x,y);
#endif

}


void CDsp::N_Mark_Rel(UINT cardNo,double x, double y, int unit)
{
	if(GetInitialStatus() != true) return;

	double dMmSize, dFieldSize;
	CFieldParameter *pFieldParameter = CFieldParameter::GetInstance();
	pFieldParameter->GetSize(&dMmSize, &dFieldSize);
	CTransUnit	*pTransUnit = pTransUnit->GetInstance(dFieldSize, dMmSize);

	if(unit == MM)
	{
		 x = pTransUnit->GetField(x, MM);
		 y = pTransUnit->GetField(y, MM);
	}

#ifndef _SCANSIMUL
	n_mark_rel(cardNo,x,y);
#else
	OutputIO(RTCIO_O_GUIDEBEAM_ENABLE, TRUE);
	goto_xy(x,y);
#endif

}

void CDsp::N_Jump_Rel(UINT cardNo,int x, int y)
{
	if(GetInitialStatus() != true) return;


#ifndef _SCANSIMUL
	n_jump_rel(cardNo,x,y);
#else
	OutputIO(RTCIO_O_GUIDEBEAM_ENABLE, TRUE);
	goto_xy(x,y);
#endif

}


void CDsp::N_Jump_Rel(UINT cardNo,double x, double y, int unit)
{
	if(GetInitialStatus() != true) return;

	double dMmSize, dFieldSize;
	CFieldParameter *pFieldParameter = CFieldParameter::GetInstance();
	pFieldParameter->GetSize(&dMmSize, &dFieldSize);
	CTransUnit	*pTransUnit = pTransUnit->GetInstance(dFieldSize, dMmSize);

	if(unit == MM)
	{
		x = pTransUnit->GetField(x, MM);
		y = pTransUnit->GetField(y, MM);
	}

#ifndef _SCANSIMUL
	n_jump_rel(cardNo,x,y);
#else
	OutputIO(RTCIO_O_GUIDEBEAM_ENABLE, TRUE);
	goto_xy(x,y);
#endif

}



void CDsp::Jump_Abs(int x, int y)
{
	if(GetInitialStatus() != true) return;
#ifndef _SCANSIMUL
	jump_abs(x,y);
	//if_fly_x_overflow(1);
	//OutputIOList(RTC_SIG_O_ALARM, TRUE);
	//if_fly_x_overflow(-1);
	//OutputIOList(RTC_SIG_O_ALARM, TRUE);
#else
	OutputIO(RTCIO_O_GUIDEBEAM_ENABLE, TRUE);
	goto_xy(x,y);
#endif
}

void CDsp::N_Jump_Abs(UINT cardNo, int x,int y)
{
	if(GetInitialStatus() != true) return;

	#ifndef _SCANSIMUL
	n_jump_abs(cardNo,x,y);
	//if_fly_x_overflow(1);
	//OutputIOList(RTC_SIG_O_ALARM, TRUE);
	//if_fly_x_overflow(-1);
	//OutputIOList(RTC_SIG_O_ALARM, TRUE);
#else
	OutputIO(RTCIO_O_GUIDEBEAM_ENABLE, TRUE);
	goto_xy(x,y);
#endif
}


void CDsp::N_Jump_Abs(UINT cardNo, double x,double y, int unit)
{
	if(GetInitialStatus() != true) return;

	double dMmSize, dFieldSize;
	CFieldParameter *pFieldParameter = CFieldParameter::GetInstance();
	pFieldParameter->GetSize(&dMmSize, &dFieldSize);
	CTransUnit	*pTransUnit = pTransUnit->GetInstance(dFieldSize, dMmSize);

	if(unit == MM)
	{
		x = pTransUnit->GetField(x, MM);
		y = pTransUnit->GetField(y, MM);
	}

	#ifndef _SCANSIMUL
	n_jump_abs(cardNo,x,y);
	//if_fly_x_overflow(1);
	//OutputIOList(RTC_SIG_O_ALARM, TRUE);
	//if_fly_x_overflow(-1);
	//OutputIOList(RTC_SIG_O_ALARM, TRUE);
#else
	OutputIO(RTCIO_O_GUIDEBEAM_ENABLE, TRUE);
	goto_xy(x,y);
#endif
}


void CDsp::Timed_Mark_Abs(int x, int y, double time)
{
	if(GetInitialStatus() != true) return;
#ifndef _SCANSIMUL
	timed_mark_abs(x,y,time);
#else
	OutputIO(RTCIO_O_GUIDEBEAM_ENABLE, TRUE);
	goto_xy(x,y);
#endif

}


void CDsp::Timed_Mark_Abs(double x, double y, double time, int unit)
{
	if(GetInitialStatus() != true) return;

	double dMmSize, dFieldSize;
	CFieldParameter *pFieldParameter = CFieldParameter::GetInstance();
	pFieldParameter->GetSize(&dMmSize, &dFieldSize);
	CTransUnit	*pTransUnit = pTransUnit->GetInstance(dFieldSize, dMmSize);

	if(unit == MM)
	{
		x = pTransUnit->GetField(x, MM);
		y = pTransUnit->GetField(y, MM);
	}

#ifndef _SCANSIMUL
	timed_mark_abs(x,y,time);
#else
	OutputIO(RTCIO_O_GUIDEBEAM_ENABLE, TRUE);
	goto_xy(x,y);
#endif

}

void CDsp::Timed_Jump_Abs(int x, int y, double time)
{
	if(GetInitialStatus() != true) return;
#ifndef _SCANSIMUL
	timed_jump_abs(x,y,time);
#else
	OutputIO(RTCIO_O_GUIDEBEAM_ENABLE, TRUE);
	goto_xy(x,y);
#endif

}



void CDsp::Timed_Jump_Abs(double x, double y, double time, int unit)
{
	if(GetInitialStatus() != true) return;

	double dMmSize, dFieldSize;
	CFieldParameter *pFieldParameter = CFieldParameter::GetInstance();
	pFieldParameter->GetSize(&dMmSize, &dFieldSize);
	CTransUnit	*pTransUnit = pTransUnit->GetInstance(dFieldSize, dMmSize);

	if(unit == MM)
	{
		x = pTransUnit->GetField(x, MM);
		y = pTransUnit->GetField(y, MM);
	}

#ifndef _SCANSIMUL
	timed_jump_abs(x,y,time);
#else
	OutputIO(RTCIO_O_GUIDEBEAM_ENABLE, TRUE);
	goto_xy(x,y);
#endif

}



void CDsp::N_Timed_Mark_Abs(UINT cardNo,int x, int y, double time)
{
	if(GetInitialStatus() != true) return;
#ifndef _SCANSIMUL
	n_timed_mark_abs(cardNo,x,y,time);
#else
	OutputIO(RTCIO_O_GUIDEBEAM_ENABLE, TRUE);
	goto_xy(x,y);
#endif

}


void CDsp::N_Timed_Mark_Abs(UINT cardNo,double x, double y, double time, int unit)
{
	if(GetInitialStatus() != true) return;

	double dMmSize, dFieldSize;
	CFieldParameter *pFieldParameter = CFieldParameter::GetInstance();
	pFieldParameter->GetSize(&dMmSize, &dFieldSize);
	CTransUnit	*pTransUnit = pTransUnit->GetInstance(dFieldSize, dMmSize);

	if(unit == MM)
	{
		x = pTransUnit->GetField(x, MM);
		y = pTransUnit->GetField(y, MM);
	}

#ifndef _SCANSIMUL
	n_timed_mark_abs(cardNo,x,y,time);
#else
	OutputIO(RTCIO_O_GUIDEBEAM_ENABLE, TRUE);
	goto_xy(x,y);
#endif

}

void CDsp::N_Timed_Jump_Abs(UINT cardNo,int x, int y, double time)
{
	if(GetInitialStatus() != true) return;
#ifndef _SCANSIMUL
	n_timed_jump_abs(cardNo,x,y,time);
#else
	OutputIO(RTCIO_O_GUIDEBEAM_ENABLE, TRUE);
	goto_xy(x,y);
#endif
}



void CDsp::N_Timed_Jump_Abs(UINT cardNo,double x, double y, double time, int unit)
{
	if(GetInitialStatus() != true) return;

	double dMmSize, dFieldSize;
	CFieldParameter *pFieldParameter = CFieldParameter::GetInstance();
	pFieldParameter->GetSize(&dMmSize, &dFieldSize);
	CTransUnit	*pTransUnit = pTransUnit->GetInstance(dFieldSize, dMmSize);

	if(unit == MM)
	{
		x = pTransUnit->GetField(x, MM);
		y = pTransUnit->GetField(y, MM);
	}

#ifndef _SCANSIMUL
	n_timed_jump_abs(cardNo,x,y,time);
#else
	OutputIO(RTCIO_O_GUIDEBEAM_ENABLE, TRUE);
	goto_xy(x,y);
#endif
}



void CDsp::Timed_Mark_Rel(int x, int y, double time)
{
	if(GetInitialStatus() != true) return;
#ifndef _SCANSIMUL
	timed_mark_rel(x,y,time);
#else
	OutputIO(RTCIO_O_GUIDEBEAM_ENABLE, TRUE);
	goto_xy(x,y);
#endif

}

void CDsp::Timed_Jump_Rel(int x, int y, double time)
{
	if(GetInitialStatus() != true) return;
#ifndef _SCANSIMUL
	timed_jump_rel(x,y,time);
#else
	OutputIO(RTCIO_O_GUIDEBEAM_ENABLE, TRUE);
	goto_xy(x,y);
#endif

}


void CDsp::N_Timed_Mark_Rel(UINT cardNo,int x, int y, double time)
{
	if(GetInitialStatus() != true) return;
#ifndef _SCANSIMUL
	n_timed_mark_rel(cardNo,x,y,time);
#else
	OutputIO(RTCIO_O_GUIDEBEAM_ENABLE, TRUE);
	goto_xy(x,y);
#endif

}


void CDsp::N_Timed_Mark_Rel(UINT cardNo,double x, double y, double time, int unit)
{
	if(GetInitialStatus() != true) return;

	double dMmSize, dFieldSize;
	CFieldParameter *pFieldParameter = CFieldParameter::GetInstance();
	pFieldParameter->GetSize(&dMmSize, &dFieldSize);
	CTransUnit	*pTransUnit = pTransUnit->GetInstance(dFieldSize, dMmSize);

	if(unit == MM)
	{
		x = pTransUnit->GetField(x, MM);
		y = pTransUnit->GetField(y, MM);
	}

#ifndef _SCANSIMUL
	n_timed_mark_rel(cardNo,x,y,time);
#else
	OutputIO(RTCIO_O_GUIDEBEAM_ENABLE, TRUE);
	goto_xy(x,y);
#endif

}

void CDsp::N_Timed_Jump_Rel(UINT cardNo,int x, int y, double time)
{
	if(GetInitialStatus() != true) return;
#ifndef _SCANSIMUL
	n_timed_jump_rel(cardNo,x,y,time);
#else
	OutputIO(RTCIO_O_GUIDEBEAM_ENABLE, TRUE);
	goto_xy(x,y);
#endif
}



void CDsp::N_Timed_Jump_Rel(UINT cardNo,double x, double y, double time, int unit)
{
	if(GetInitialStatus() != true) return;

		double dMmSize, dFieldSize;
	CFieldParameter *pFieldParameter = CFieldParameter::GetInstance();
	pFieldParameter->GetSize(&dMmSize, &dFieldSize);
	CTransUnit	*pTransUnit = pTransUnit->GetInstance(dFieldSize, dMmSize);

	if(unit == MM)
	{
		x = pTransUnit->GetField(x, MM);
		y = pTransUnit->GetField(y, MM);
	}


#ifndef _SCANSIMUL
	n_timed_jump_rel(cardNo,x,y,time);
#else
	OutputIO(RTCIO_O_GUIDEBEAM_ENABLE, TRUE);
	goto_xy(x,y);
#endif
}



void CDsp::LaserSignalOn(void)
{
	if(GetInitialStatus() != true) return;
	goto_xy(0,0);
	enable_laser();	
	laser_signal_on();
}


void CDsp::LaserSignalOff(void)
{
	if(GetInitialStatus() != true) return;
	laser_signal_off();
}


void CDsp::SetAnalogOutPut1(double dVoltage)
{
	if(GetInitialStatus() != true) return;
	CInitialTable *pInitialTable = pInitialTable->GetInstance();
	if(dVoltage > pInitialTable->GetMaxLimitPower())
	{
#ifdef _RTC6_		
		CString strMessage;
		strMessage = _T("Laser Max Power Limit Warning!  설정된 Max Power로 변경됩니다.\n파워설정값을 확인하세요.");\
		AfxMessageBox(strMessage);
		//CMainFrame *pMainFrm = (CMainFrame*)AfxGetMainWnd();
		//pMainFrm->DisplayMessage(strMessage);
		dVoltage = pInitialTable->GetMaxLimitPower();
		//return;
#endif
	}

	dVoltage = dVoltage / 10.0;
	//write_da_1_list((unsigned short)((4095.0 * dVoltage) / 10.0));	ListCountPlus();
	enable_laser();

#ifdef _RTC6_
	write_da_1((unsigned short)((4095.0 * dVoltage) / 10.0));	
#else
	write_da_1((unsigned short)((1023.0 * dVoltage) / 10.0));	
#endif

	if (pInitialTable->GetLaser() == LASER_FIBER && m_bAnalogPowerSet == false)
		/******************** Digital Out PuT *************************************/
	{
		unsigned short uSetPower=0;
		uSetPower =  (unsigned short)((dVoltage / 100.) *255.);
#ifdef	_RTC4eth_
		//write_8bit_port((unsigned short)((para.GetRTCVoltage() / 100) *255));
		write_8bit_port((unsigned short)(uSetPower));
		OutputIO(RTCIO_O_LATCH, false);
		SetDelay(100);
		OutputIO(RTCIO_O_LATCH, true);
		OutputIO(RTCIO_O_EMERGENCY, true);
		OutputIO(RTCIO_O_MO, true);
#endif
#ifdef _RTC_Test_ 
		OutputIOList(RTCIO_O_MO, true);ListCountPlus();
		OutputIOList(RTCIO_O_GUIDEBEAM_ENABLE, false);ListCountPlus();
		long_delay(LATCH_DELAY);ListCountPlus();			
#endif

	}
}


void CDsp::SetAnalogOutPut2(double dVoltage)
{
	if(GetInitialStatus() != true) return;
#ifdef _RTC6_
	write_da_1((unsigned short)((4095.0 * dVoltage) / 10.0));	
#else
	write_da_1((unsigned short)((1023.0 * dVoltage) / 10.0));	
#endif
}


void CDsp::SetAnalogPowerUse(bool bUseAnalog)
{
	m_bAnalogPowerSet = bUseAnalog;
}


bool CDsp::GetAnalogPowerUse(void)
{
	return m_bAnalogPowerSet;
}


unsigned short CDsp::ReadIoPort(void)
{
	if(GetInitialStatus() != true) return 0;
	unsigned short status = read_io_port();
	return status;
}



unsigned short CDsp::n_ReadIoPort(int nCardNo)
{
#ifdef	_SIMUL_
	return 0;
#endif

	if(GetInitialStatus() != true) return 0;
	unsigned short status = n_read_io_port(nCardNo);
	return status;
}

bool CDsp::GetIoStatus(unsigned short bit)
{
	if(GetInitialStatus() != true) return 0;
	unsigned short status = get_io_status();
	unsigned short value = status & (unsigned short)((double)pow(2.0, bit));
	value = value >> bit;
	return value;
}


bool CDsp::n_GetIoStatus(UINT cardNo,unsigned short bit)
{
	if(GetInitialStatus() != true) return 0;
	unsigned short status = n_get_io_status(cardNo);
	unsigned short value = status & (unsigned short)((double)pow(2.0, bit));
	value = value >> bit;
	return value;
}


bool CDsp::GetInputValue(int nBit)
{
	if(GetInitialStatus() != true) return 0;
	unsigned short status = ReadIoPort();
	unsigned short value = status & (unsigned short)((double)pow(2.0, nBit));
	value = value >> nBit;
	return value;
}

bool CDsp::nGetInputValue(UINT cardNo,int nBit)
{
	#ifdef	_SIMUL_
    return 0;
#endif
	if(GetInitialStatus() != true) return 0;
	unsigned short status = n_ReadIoPort(cardNo);
	unsigned short value = status & (unsigned short)((double)pow(2.0, nBit));
	value = value >> nBit;
	return value;
}


unsigned short CDsp::GetIoStatus(void) // OutPut Status of EXTENSION 1
{
	#ifdef	_SIMUL_
    return 0;
#endif

	if(GetInitialStatus() != true) return 0;
	return get_io_status();
}



unsigned short CDsp::n_GetIoStatus(UINT cardNo) // OutPut Status of EXTENSION 1
{
#ifdef	_SIMUL_
    return 0;
#endif


	if(GetInitialStatus() != true) return 0;
	return n_get_io_status(cardNo);
}





void CDsp::SetSpeedScale(double dScale)
{
	m_dSpeedScale = dScale;
}


double CDsp::GetSpeedScale(void)
{
	return m_dSpeedScale;
}


double CDsp::Get_timed_Markabs(void)
{
	return m_dtimed_marktime;
}


void CDsp::SetVariableMode(int nVariableMode)
{
	switch(nVariableMode)
	{
	case NORMAL_MARK_MODE: n_ScannerVariableMode = NORMAL_MARK_MODE;
		break;
	
	case TIMED_MARK_MODE: n_ScannerVariableMode = TIMED_MARK_MODE;
		break;

	case SPEED_MARK_MODE: n_ScannerVariableMode = SPEED_MARK_MODE;
		break;

	}
}


void CDsp::activate_fly_xy(double dScaleX, double dScaleY)
{
	if(GetInitialStatus() != true) return;

	activate_fly_xy(dScaleX, dScaleY);
}


void CDsp::SetChangeLineSpeedIndex(int iLineSpeedIndex)
{
	m_iChangeLineSpeedIndex = iLineSpeedIndex;
}


void CDsp::ClearOverflow(void)
{
	if(GetInitialStatus() != true) return;

	set_start_list(1);
	clear_fly_overflow(3);
	set_end_of_list();
	execute_list(1);
}


void CDsp::Set1stFlagStep(bool bFlag)
{
	m_b1stFlagStep = bFlag;
}


bool CDsp::Get1stFlagStep(void)
{
	return m_b1stFlagStep;
}


double CDsp::GetFlagMarkSpeedDiff(int index)
{
	if(GetInitialStatus() != true) return -1;
	CPointerManager *pPointerManager = pPointerManager->GetInstance();
	Iterator<CParameter*> *iterator = pPointerManager->GetParameterList()->iterator();
	CParameter *pParameter = iterator->GetCurrentItem();
	CInitialTable *pInitialTable = pInitialTable->GetInstance();
	double dFlagMarkSpeed =  pParameter->GetFlagSpeed();
	double dFlagExtMarkSpeed =  pParameter->GetFlagExtSpeed();

	double dFlagMarkStepDiff = dFlagMarkSpeed - dFlagExtMarkSpeed;
	double dFlagmarkSpeedDiff;

	dFlagMarkStepDiff = ((double)dFlagMarkStepDiff * (10 / 1000000.)) * 10 / ((double)pInitialTable->GetMMSize() / (double)pInitialTable->GetFieldSize());

	dFlagmarkSpeedDiff = (double)dFlagMarkStepDiff*100/pParameter->GetStepPeriod(); //20191211 장민국 test

	return dFlagmarkSpeedDiff;
}




double CDsp::GetNonFlagMarkSpeedDiff(int index)
{
	if(GetInitialStatus() != true) return -1;
	CPointerManager *pPointerManager = pPointerManager->GetInstance();
	Iterator<CParameter*> *iterator = pPointerManager->GetParameterList()->iterator();
	CParameter *pParameter = iterator->GetCurrentItem();
	CInitialTable *pInitialTable = pInitialTable->GetInstance();
	//최종적용시
	//double dNonflagMarkSpeed =  pParameter->GetUnflagLineSpeed();
	//double dNonflagExtMarkSpeed =  pParameter->GetUnflagInoutSpeed();//2021.08.11 함수이름정리 필요!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	double dNonflagMarkSpeed =  pParameter->GetUnflagInoutSpeed();    // NonflagInOutSpeed
	double dNonflagExtMarkSpeed =  pParameter->GetUnFlagInoutExtSpeed();//2021.08.11 함수이름정리 필요!!!!!!!!!!!!!!!!!!!!!!!!!!!!



	double dNonflagMarkStepDiff = dNonflagMarkSpeed - dNonflagExtMarkSpeed;
	double dNonflagmarkSpeedDiff;

	dNonflagMarkStepDiff = ((double)dNonflagMarkStepDiff * (10 / 1000000.)) * 10 / ((double)pInitialTable->GetMMSize() / (double)pInitialTable->GetFieldSize());

	dNonflagmarkSpeedDiff = (double)dNonflagMarkStepDiff*100/pParameter->GetStepPeriod(); //20191211 장민국 test

	return dNonflagmarkSpeedDiff;
}



double CDsp::GetNonFlagLineMarkSpeedDiff(int index)
{
	if(GetInitialStatus() != true) return -1;

	CPointerManager *pPointerManager = pPointerManager->GetInstance();
	Iterator<CParameter*> *iterator = pPointerManager->GetParameterList()->iterator();
	CParameter *pParameter = iterator->GetCurrentItem();
	CInitialTable *pInitialTable = pInitialTable->GetInstance();

	//double dNonflagLineMarkSpeed =  pParameter->GetFlagSpeed();
	//double dNonflagLineExtMarkSpeed =  pParameter->GetFlagExtSpeed();

	double dNonflagLineMarkSpeed =  pParameter->GetUnflagLineSpeed(); //NonFlagSpeed
	double dNonflagLineExtMarkSpeed =  pParameter->GetNonFlagLineExtSpeed();


	double dNonflagLineMarkStepDiff = dNonflagLineMarkSpeed - dNonflagLineExtMarkSpeed;
	double dNonflagLinemarkSpeedDiff;

	dNonflagLineMarkStepDiff = ((double)dNonflagLineMarkStepDiff * (10 / 1000000.)) * 10 / ((double)pInitialTable->GetMMSize() / (double)pInitialTable->GetFieldSize());

	dNonflagLinemarkSpeedDiff = (double)dNonflagLineMarkStepDiff*100/pParameter->GetStepPeriod(); //20191211 장민국 test

	return dNonflagLinemarkSpeedDiff;
}

void CDsp::SetMarkSpeed(double dMarkSpeed)
{
	if(GetInitialStatus() != true) return;
	set_mark_speed(dMarkSpeed);
}




double CDsp::GetSettedMarkSpeed(void)
{
	if(GetInitialStatus() != true) return 0;
	return m_dSettedCurrMarkSpeed;
}


void CDsp::nSetRTCJumpSpeed(UINT cardNo,double jumpSpeed)
{
	CInitialTable *pInitialTable = pInitialTable->GetInstance();
	//n_set_start_list(cardNo,99);

	CPointerManager *pPointerManager = pPointerManager->GetInstance();
	Iterator<CParameter*> *iterator = pPointerManager->GetParameterList()->iterator();
	CParameter *pParameter = iterator->GetCurrentItem();



	jumpSpeed = ((double)jumpSpeed * (10 / 1000000.)) * 10 / ((double)pInitialTable->GetMMSize() / (double)pInitialTable->GetFieldSize());
	jumpSpeed = (double)jumpSpeed*100/pParameter->GetStepPeriod();

	if(GetInitialStatus() != true) return;

	n_set_jump_speed(cardNo,jumpSpeed);
}


void CDsp::nSetRTCMarkSpeed(UINT cardNo,double markSpeed)
{
	CInitialTable *pInitialTable = pInitialTable->GetInstance();
	//n_set_start_list(cardNo,99);

	CPointerManager *pPointerManager = pPointerManager->GetInstance();
	Iterator<CParameter*> *iterator = pPointerManager->GetParameterList()->iterator();
	CParameter *pParameter = iterator->GetCurrentItem();


	markSpeed = ((double)markSpeed * (10 / 1000000.)) * 10 / ((double)pInitialTable->GetMMSize() / (double)pInitialTable->GetFieldSize());
	markSpeed = (double)markSpeed*100/pParameter->GetStepPeriod();

	if(GetInitialStatus() != true) return;

	n_set_mark_speed(cardNo,markSpeed);
}



void CDsp::nSetScannerParameter(UINT cardNo, double scannerSpeed, SingleScannerParameter scannerParameter)
{
	if(GetInitialStatus() != true) return ;
	
	CInitialTable *pInitialTable = pInitialTable->GetInstance();
	CPointerManager *pPointerManager = pPointerManager->GetInstance();
	Iterator<CParameter*> *iterator = pPointerManager->GetParameterList()->iterator();
	CParameter *pParameter = iterator->GetCurrentItem();
	double dCurrent;
	double dScale = pInitialTable->GetFieldScale();

	double dMmSize, dFieldSize;
	IniUtil _iniutil;
	FieldParameter FIELD_FARAMETER = CFieldParameter::GetInstance()->GetFieldParameterData();
	CString FieldPath = _iniutil.ReplacePathVariables(_iniutil.PATH_BASE + _iniutil.PATH_INI_FIELD);
	_iniutil.LoadFieldIni(_T("Encoder"), FieldPath, FIELD_FARAMETER);
	dMmSize = FIELD_FARAMETER.MmSize;
	dFieldSize = FIELD_FARAMETER.FieldSize;

	//UINT Minvalue,Maxvalue;
	//Minvalue = 0;
	//Maxvalue = 4095;	
	//int nErrorcode = n_set_auto_laser_control(cardNo, 1, 4095, 1, Minvalue, Maxvalue); //= 1: 12-bit output value at the ANALOG OUT1 output port.
	//													//= 2: 12-bit output value at the ANALOG OUT2 output port.

#ifdef _RTC_Test_ 

/*
	dCurrent = pParameter->GetLaserPowerSet();
	if(GetInitialStatus())
	{
		write_8bit_port((unsigned short)(dCurrent));
		write_8bit_port_list((unsigned short)(dCurrent));


		//write_8bit_port((unsigned short)((para.GetRTCVoltage() / 100) *255));
		OutputIOList(RTCIO_O_MO, true);
		OutputIOList(RTCIO_O_GUIDEBEAM_ENABLE, false);
	}
	*/
	//long_delay(LATCH_DELAY);


	/*OutputIOList(RTCIO_O_LATCH, false);ListCountPlus();
	OutputIOList(RTCIO_O_MO, false);ListCountPlus();
	long_delay(LATCH_DELAY);ListCountPlus();
	OutputIOList(RTCIO_O_LATCH, true);ListCountPlus();
	OutputIOList(RTCIO_O_MO, true);ListCountPlus();
	OutputIOList(RTCIO_O_EMERGENCY, true);ListCountPlus();*/


#endif


#ifdef _RTC5_
	if(GetInitialStatus())
	{
		n_set_scanner_delays(cardNo,scannerParameter.jumpDelay/10, scannerParameter.markDelay/10 ,scannerParameter.polygonDelay/10);
		n_set_laser_delays(cardNo,scannerParameter.laserOnDelay,scannerParameter.laserOffDelay);
	}
#endif

	

#ifdef _RTC6_
	LONG CornerScale = 500; // polyline: 100%: max precision, 0% min execution time 
	LONG EndScale = 500;// mark, jump: 100%: max precision, 0% min execution time
	LONG AccScale = 50;// 100%: laser is on during acceleration and deceleration
	UINT uMode, uPrevTime,uVmax,uAmax;
	uPrevTime=0;uVmax=0;uAmax=0;

	//nWriteDA1List(cardNo,scannerParameter.flagPower);

	CornerScale = (LONG)scannerParameter.polygonDelay;
	EndScale = (LONG)scannerParameter.markDelay;
	AccScale = (LONG)scannerParameter.jumpDelay;

	UINT unRepRate = (UINT)(double)(( 1.0 / (double)pParameter->GetFrequency() /2.0 ) * 1000.0  * LASER_PULSE_UNIT );		// HZ -> to Time
	UINT unPulseLength   = (UINT)(double)((double)pParameter->GetPulseWidth() * LASER_PULSE_UNIT );
	UINT nQswPulseDuty = (1000 / (double)pParameter->GetFrequency()) * ((double)pParameter->GetPulseWidth() / 100);
	//set_laser_pulses(unRepRate, unPulseLength);	ListCountPlus();

	//Scanahead: calculate delays automatically. excelliscan
	//(const UINT CardNo, const UINT Mode, const UINT HeadNo, const UINT TableNo, const UINT PreViewTime, const UINT Vmax, const double Amax);
	//n_set_scanahead_params(RTC_CARD_NUM_1, 1, 1, 1, uPrevTime, uVmax, uAmax );// place anywhere after load_correction_file
	//n_activate_scanahead_autodelays_list(RTC_CARD_NUM_1, 1);
	//n_set_scanahead_line_params_list(RTC_CARD_NUM_1,CornerScale, EndScale, AccScale );
	//n_set_scanahead_laser_shifts_list(RTC_CARD_NUM_1, (long)(scannerParameter.laserOnDelay*dScale*64), (long)(scannerParameter.laserOffDelay*dScale*64) ); // fine tuning LaserON and LaserOFF. 1 bit = 1/64 
#endif

	scannerSpeed = ((double)scannerSpeed * (10 / 1000000.)) * 10 / (dMmSize / dFieldSize);
	scannerSpeed = (double)scannerSpeed*100/pParameter->GetStepPeriod();

	double jumpSpeed = scannerParameter.jumpSpeed;

	jumpSpeed = ((double)jumpSpeed * (10 / 1000000.)) * 10 / ((dMmSize / dFieldSize));
	jumpSpeed = (double)jumpSpeed*100/pParameter->GetStepPeriod();

	m_dSettedCurrMarkSpeed = scannerSpeed;

	if(GetInitialStatus())
	{
		n_set_mark_speed(cardNo,scannerSpeed);
		n_set_jump_speed(cardNo,jumpSpeed);
	}
}

void CDsp::nSetFrequency(UINT cardNo, double dFreq , double dPulseWidth)
{
	if(GetInitialStatus() != true) return;
	double dnRepRate = (double)(( 1.0 / (double)dFreq /2.0 ) * 1000.0);
	dnRepRate = dnRepRate * LASER_PULSE_UNIT ;		// HZ -> to Time

	//dFreq = dFreq * 1000;//hz->khz
	dPulseWidth = dPulseWidth / 1000.0;//us->ns

	UINT unRepRate = (UINT)(double)(( 1.0 / (double)dFreq /2.0 ) * 1000.0  * LASER_PULSE_UNIT );		// HZ -> to Time
	UINT unPulseLength   = (UINT)(double)((double)dPulseWidth * LASER_PULSE_UNIT );
	

	//UINT nQswPulseDuty = (1000 / (double)dFreq) * ((double)pParameter->GetPulseWidth() / 100);
	n_set_laser_pulses(cardNo, unRepRate, unPulseLength);	
}

UINT CDsp::nGetListSpace(UINT CardNo)
{
	if(GetInitialStatus() != true) return -1;
	return n_get_list_space(CardNo);

}
UINT CDsp::nGetInputPointer(UINT CardNo)
{
	if(GetInitialStatus() != true) return -1;
	return n_get_input_pointer(CardNo);

}

void CDsp::nSetInputPointer(UINT CardNo, UINT Pos)
{
	if(GetInitialStatus() != true) return;
	n_set_input_pointer(CardNo, Pos);
}


void CDsp::nSetStartLisPos(UINT CardNo, UINT listNo, UINT Pos)
{
	if(GetInitialStatus() != true) return;
	n_set_start_list_pos(CardNo, listNo, Pos);
	m_iEncoderPos = 0;
}


void CDsp::nListRepeat(UINT CardNo)
{
	if(GetInitialStatus() != true) return;
	n_list_repeat(CardNo);
}

void CDsp::nListUntil(UINT CardNo, UINT Number)
{
	if(GetInitialStatus() != true) return;
	n_list_until(CardNo, Number);
}


void CDsp::nListContinue(UINT CardNo)
{
	if(GetInitialStatus() != true) return;
	n_list_continue(CardNo);
}


void CDsp::nListJumpRel(UINT CardNo,long Pos)
{
	if(GetInitialStatus() != true) return;
	n_list_jump_rel(CardNo,Pos);
}


void CDsp::nListJumpPos(UINT CardNo,long Pos)
{
	if(GetInitialStatus() != true) return;
	n_list_jump_pos(CardNo,Pos);
}


void CDsp::nIf_Cond(const UINT CardNo, const UINT Mask1, const UINT Mask0)
{
	if(GetInitialStatus() != true) return;
	n_if_cond(CardNo, Mask1,Mask0);
}


void CDsp::nIf_not_Cond(const UINT CardNo, const UINT Mask1, const UINT Mask0)
{
	if(GetInitialStatus() != true) return;
	n_if_not_cond(CardNo, Mask1,Mask0);
}

UINT CDsp::nGetMarkingInfo(UINT CardNo)
{
	if(GetInitialStatus() != true) return 0;
	return n_get_marking_info(CardNo);
}

void CDsp::nExecuteList(UINT CardNo , UINT ListNo)
{
	if(GetInitialStatus() != true) return;
	n_execute_list(CardNo,ListNo);
}
void CDsp::nGetstatus(UINT CardNo, UINT &Status, UINT &Pos)
{
	if(GetInitialStatus() != true) return;
	n_get_status(CardNo, &Status, &Pos);

}

void CDsp::nSaveAndRestartTimer(UINT CardNo)
{
	if(GetInitialStatus() != true) return;
	n_save_and_restart_timer(CardNo);
}

double CDsp::nGetTime(UINT CardNo)
{
	if(GetInitialStatus() != true) return -1;
	return n_get_time(CardNo);
}

UINT CDsp::nGetListSize(UINT CardNo)
{
	if(GetInitialStatus() != true) return -1;
	return ListMemory;
}
