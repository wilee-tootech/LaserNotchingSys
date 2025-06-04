// 언어 분류
#define KOR 0
#define ENG 1
// 분리된 툴바
#define BOOL_MAINTOOL 0
#define BOOL_ANOTHERVIEW 1
#define BOOL_FILETOOL 2
#define BOOL_MARKTOOL 3
#define MAXTOOLBARS 15
#define MAINTOOL 0
#define STANDARD 1
#define EDIT 2
#define ALIGN 3
#define MARKORDER 4
#define HELP 5
#define FIGURE 6
// 단위 관련
#define MM		0	// 1
#define FIELD	1	// 3
#define MIL		2	// 2
#define _POINT	3	// 0

#define MAXMM		208
#ifdef _RTC6_
	#define MAXFIELD	1048575
#else
	#define MAXFIELD	65535
#endif

// Bin 관련
#define MAX_BIN_SIZE 10
// Calibration 관련
//#define MAX_CAL_DATA 65
#define MAX_CAL_DATA		257


//Calibration X 마크 Matrix
#define SCALE_MARK_X				2.0
#define SCALE_MARK_Y				2.0
#define SCALE_MARK_SIZE				2.0 //2mm

#define CAL_MARK_XFIELD				55.0
#define CAL_MARK_YFIELD				55.0

#define CAL_MARK_X					15.0
#define CAL_MARK_Y					15.0
#define CAL_MARK_SIZE				2.0

#define SCALE_MARK_PITCHX			15.0//15mm
#define SCALE_MARK_PITCHY			15.0//15mm

#define CAL_MARK_PITCHX				15.0//15mm
#define CAL_MARK_PITCHY				15.0//15mm

// Communication 관련
#define WM_RECEIVE_COM				WM_USER + 4 //--- 사용자 정의 메세지 
#define WM_SEND_COM					WM_USER + 5
#define WM_RECEIVE_LASER			WM_USER + 6 //--- 사용자 정의 메세지 
#define WM_SEND_LASER				WM_USER + 7
#define WM_RECEIVE_HANDLER			WM_USER + 8
#define WM_RECEIVE_BICRONIX			WM_USER + 9	
#define WM_UPDATE_PATTERN_VIEW		WM_USER + 10	

#define HEAD2_SOCKET				0
#define HEAD1_SOCKET				1

#define NUM_OF_SET_MESSAGE 7
//#define CURRENT_SET 0
#define FREQUENCY_SET 1
#define PULSE_WIDTH_SET 2
#define LASER_ON_OFF_CONTROL 3
#define SHUTTER_ON_OFF_CONTROL 4
#define CURRENT_INT_EXT_SET 5
#define FREQUENCY_INT_EXT_SET 6
#define NUM_OF_CHECK_MESSAGE 10
#define CURRENT_READ 7
#define FREQUENCY_READ 8
#define GATED_Q_SWITCH_PULSE_WIDTH 9
#define WATER_TEMPERATURE_READ 10
#define HEATSINK_TEMPERATURE_READ 11
#define LASER_SHUTTER_STATUS 12
#define ERROR_READ 13
#define CURRECT_STATUS_OF_SYSTEM_OPERATION 14
#define ELAPSED_TIME_READ 15
#define SETTING_CURRENT_READ 16
#define MANUAL_COMMAND 100
#define EMPTY_SETCOMMAND		200
#define DELAY_TIME	40000
extern BYTE rcvBuf[4097];
extern BYTE sendBuf[4097];	// 2007.02.13  
#define ASCII_XON 0x11
#define ASCII_XOFF 0x13
#define DEFAULT_SIZE 20
#define SIZE_32 32
#define SIZE_128 128
// USER MESSAGE
#define WM_USER_PATHCHANGED WM_USER+10
// 이미지 리스트 상의 index
#define ID_FLOPPY	0
#define ID_HARDDISK	1
#define ID_CDROM	2
#define ID_NETDRIVE	3
#define ID_CLOSEDFOLDER	4
#define ID_OPENFOLDER	5
// Parameter
#define MAX_PARAMETER   20
//#define KINDSOFPARAMETER 13


#define KINDSOFPARAMETER 16 //2005.11.01 종섭 수정 -> Bmp Parameter추가

// Communicate Setting
#define MAX_COMMUNICATE 4
// Rofin
#define WAIT_TIME 300
#define MSG_SIZE 1024
// Dsp 관련
#define AUTO_MARK		0x00
#define MARK_STOP		0x01
#define MANUAL_MAKRING	0x02
#define MANUAL_MOVE		0x03
#define CALIBRATION		0x04
#define MANUAL_LASER_CONTROL 0x05
#define	TUNNING			0x06
#define DRAW_MARK_RECT	0x07
#define IO_READ			0x08
#define IO_WRITE		0x09
#define TUNNING_STOP	0x0a
//#define CURRENT_SET		0x11  // Lee current control
#define LASER_ERROR     0x0b // 2004.12.4 jjs
#define LASER_ERROR_END 0x13
#define DEVICE_DEMAND   0x15 


#define DATA_REV			0x0E

#define SIG_I_DEVICE_NO_1		0x07	//Y6E7
#define SIG_I_DEVICE_NO_2		0x08	//Y6E8
#define SIG_I_DEVICE_NO_3		0x09	//Y6E9
#define SIG_I_DEVICE_NO_4		0x0A	//Y6EA	
#define SIG_I_DEVICE_NO_5		0x0B	//Y6EB
//#define SIG_I_MARK_START		0x05	//Y6EC
//#define SIG_I_DEVICE_STROBE		0x06	//Y6ED
//------------------------------------------------

/******************************** KOEM I/O Define ****************************/

//#define SIG_I_LASER_ON		0x00
//#define SIG_I_FIRST_TAB		0x01
//#define SIG_I_SKIP_MODE		0x02
//#define SIG_I_EMG_STOP		0x03
//
//#define SIG_O_READY  		0x00
//#define SIG_O_PROGRESS		0x01
//#define SIG_O_ALARM			0x02
//#define SIG_O_FIRST_TAB 	0x03
//--------------------------------------------------------------------------------

//#define SIG_I_LASER_POWER		0x07
//#define SIG_I_SCANNER_POWER		0x08
//#define SIG_I_LASER_ENABLE		0x09

//#define SIG_I_VISION_SKIP		0x00
//#define SIG_I_LOT_END			0x02
//#define SIG_I_DEVCHANGE_READY	0x0E
//#define SIG_I_BUFFER_CLEAR		0X04	

#define PMU_SHUTTER_ON     0xFB
#define PMU_SHUTTER_OFF    0xFF
#define SHUTTER_ALL_ON     0xFF
#define SHUTTER_ALL_CLOSE  0xE7	
#define SHUTTER_S_ON       0xF7
#define SHUTTER_M_ON	   0xEF
//psc--------------------------------
#define PSC_PMU_SHUTTER_ON     0x00001000	//12
#define PSC_PMU_SHUTTER_OFF    0xFFFFEFFF
#define PSC_SHUTTER_ALL_ON     0x00006000	
#define PSC_SHUTTER_ALL_CLOSE  0xFFFF9FFF	
#define PSC_SHUTTER_S_ON       0x00004000	//13
#define PSC_SHUTTER_M_ON	   0x00002000	//14
//-----------------------------------


#define AUTO_MARK_STOP		0X01
#define DRAW_RECT			0x0d
#define ADR_NUMBER_OF_OBJ 0x008000	// 오브젝트의 갯수 들어있는 DSP 주소  
#define ADR_BIN_POSITION  0x009000  // bin 데이터의 갯수가 들어있는 주소
#define ADR_PARA_POSITION 0x00A000	// parameter가 들어있는 곳의 주소
#define NUMBER_OF_BIN		10
#define NUMBER_OF_PARA		10
#define NUMBER_OF_BIN_COL   8
#define MASTER_X 0x9860
#define MASTER_Y 0x9861
#define MASTER_SCALE_X 0x9862
#define MASTER_SCALE_Y 0x9863
#define SLAVE_X 0x9864
#define SLAVE_Y 0x9865
#define SLAVE_SCALE_X 0x9866
#define SLAVE_SCALE_Y 0x9867
#define DEVICE_CHANGE_SIGNAL 0x9875 //Signetics Device Change
#define DEVICE_COMMAND_SIGNAL 0x9873

//20041001수정
#define IOMARKSIGANL  0x9879  /////황 
#define SEMI_MARKING  0x14   /////황 

#define MASTER_CAL_DATA_X 0xbf400   
#define MASTER_CAL_DATA_Y 0xcf700
#define SLAVE_CAL_DATA_X  0xdfa00
#define SALVE_CAL_DATA_Y  0xefd00

#define COMMAND_ADDR	0x9820
#define IO_WRITE		0x09
#define IO_WRITE_ADRRESS 0x9870
#define IO_WRITE_DATA 0x9871
#define ENDCOM_READ_ADDR 0x9890
#define DSP_VERSION		 0x9827 // Dsp Version 표시
#define CHIP_NUMBER	     0x9845


#define MASTER_CHIP_OFFSET 0xb0000
#define SLAVE_CHIP_OFFSET  0xb2000
// OBJECT 관련
// OBJECT type
#define EMPTY 0
#define STEXT 1
#define RTEXT 2
#define HPGL  3
//#define BMP	  4
//#define JPG   5
//#define GIF   6
#define BARCODE 7 
#define BITIMG 8
#define BARCODE2D 9
#define TTF		10
#define ID_TTF_OBJECT           106

#define LEFT   0
#define MIDDLE 1
#define RIGHT  2

#define SELECTED   1
#define UNSELECTED 0

/* 커팅 관련 */
#define MRK_PAUSE	0
#define MRK_AUTO	1
#define MRK_MANUAL	2
#define DATA_LIMIT	524288//32767//28767//30000

/* 파일 관련 */
#define ID_FILE		 20000

/* 디바이스 관련 */
// startPos
#define TOP_LEFT 0
#define TOP_RIGHT 1
#define BOTTOM_LEFT 2
#define BOTTOM_RIGHT 3
#define CIRCLE_SIZE  100
#define CIRCLE_RADIUS 10

// method
#define HORIZONTAL	0
#define HORIZONTAL_ZIG 1
#define VERTICAL 2
#define VERTICAL_ZIG 3

// 디바이스 관련
#define SELECTARRAYSIZE         1000
#define SELECTARRAY2SIZE        1000

#define AMKOR_DEVICE 0
#define HK_DEVICE    1

// 권한 설정 관련
#define MAX_USER_SIZE		4 // 2007.05.21  
#define MAX_AUTH_SIZE       21//18

// 룰러
#define RULER_SIZE			23

// 키보드 이동량 (필드 단위)
#define DEF_MOVE_SIZE       50

// 로그 파일 관련
#define MAX_EVENT           200

// 도형 관련
#define NULL_POINT 0
#define START_POINT 1
#define MIDDLE_POINT 2
#define END_POINT 3
//#define MOVING_CENTER_POINT 4

// 선택 방법
#define NONE_SELECT 0
#define DOWN_SELECT 1
#define DRAG_SELECT 2

// Signetics Top/Bottom 체크
#define TYPE_TOP 0
#define TYPE_BOTTOM 1


#define LASER_SPECTRON		0
#define LASER_ROFIN			1
#define LASER_QUANTRONIX	2
#define LASER_HANAMIA		3
#define LASER_LEE			4
#define LASER_IDT			5
#define LASER_FIBER			6
// 2011.04.04 syhun START - Laser control 추가.
#define LASER_LASERVALL		7
#define LASER_SPIFIBER		8
#define LASER_BICRONIX		9
#define LASER_JDSU			10
#define LASER_PLASMA		11
#define LASER_NOUSE			12

// 2011.04.05 syhun START - JDSU관련.
/*COMMAND*/
#define Increment_Parameter				0x30
#define Decrement_Parameter				0x31
#define Turn_Parameter_On				0x32
#define Turn_Parameter_Off				0x33
#define Read_Parameter_Current_Value    0x34
#define Read_Default_Value				0x35
#define Set_Parameter_Default_Value		0x36
#define Set_Parameter_To_Default		0x37
#define Start_Parameter_Procedure		0x38
#define Write_Data_To_Parameter			0x39

/*Parameter*/
#define Series_NumberandSoftwareDate         0x30
#define LW_and_Head_Serial_Number			 0x31
#define Electronic_Board_Serial_Number		 0x32
#define Hours_Since_Service					 0x33
#define Total_Hours							 0x34
#define End_Of_String_Characters			 0x35
#define Diode_OnOff_Stanby				     0x36
#define Laser_Power							 0x37
#define Interlock							 0x38
#define Fault_Status						 0x39
#define Diode_Current_Setting				 0x41
#define Diode_Temperature_Setting			 0x42
#define Diode_Temperature_Sense 			 0x43
#define Chiller_Temperature					 0x44
#define Sleep_Mode							 0x45
#define First_Pulse_Suppress				 0x46
#define Shutter								 0x49
#define Current_Monitor						 0x4A
#define External_Standby					 0x4C
#define Ex_Shutter_Signal					 0x4D
#define Auto_Sleep_Enable					 0x4E
#define Flow_Switch							 0x4F
#define Reservoir_Status					 0x50
//-------------------------------------------
#define Set_Trigger_Mode					 0x51
		#define TrigMode_CW					 0x01
		#define TrigMode_Int				 0x02
		#define TrigMode_Ext				 0x03
		#define TrigMode_Burst				 0x04
//-------------------------------------------
#define Internal_Trig_Rep_Rate				 0x52
#define Imax								 0x53
#define Activate_Pulse_Train_In_Burst_Mode   0x54
#define RF_Level							 0x55
#define Service_Hours						 0x56
#define UV_Hours							 0x57
#define THG_Value							 0x58
//#define Reserved_LWE 

/* Laser -> Handler */
#define SIG_O_LASEROPEN_READY   0x00
#define SIG_O_JOBLOAD_OK		0x01
#define SIG_O_MARK_READY        0x02 // Data를 받았을 경우
#define SIG_O_SIG_O_PROGRESS    0x03
#define SIG_O_LASER_ERROR       0x04

#define SIG_O_DATA_REV          0x05
#define SIG_O_SHUTTER_ON	    0x06
#define SIG_O_SHUTTER_OFF	    0x07

#define SIG_O_SWITCH_ONECUT_MODE_ON	    0x00 // 20230726 한붓 두분 자동 변환용 테스트


#define LIMIT_DCCURRENT 50


//------------------------------------ 20170620 jjsjong ----------------Sequence Socket Protocol ----------------------//
/*First Byte*/
#define CODE_STX	0x02
#define CODE_ETX	0x03
#define CODE_ESC	0x1B

#define CODE_ETX1	0x0D
#define CODE_ETX2	0x0A
//---------------------------------------------------------------------------------------------------------------------//

/*Laser Number*/
#define LASER_NUMBER 0

// syhun END.

#define LASER_GOLDLIGHT		12

#define LED_RED_ON		10
#define LED_RED_OFF		11
#define LED_GRAY		12
#define LED_GREEN_ON	13
#define LED_GREEN_OFF	14
#define LED_YELLOW		15
#define LED_MARK		16
#define LED_STOP		17

//psc ----------------------------
#define MEM1	1000000
#define MEM2	1000000
//--------------------------------

//------------ KEOM MULTICUTTING COUNT ----------------------
#define MULTI_CUT_CNT		2
#define OVERLAP_SIZE        2        // MultiCut Overlap length


/*********** Porcess Sequence ID ***************************/
#define STEP_UNFLAG_START	 0
#define STEP_NUBLESS_REGION  1
#define STEP_FLAG_START		 2
#define STEP_FLAG_COUNT		 3
#define STEP_BURIED_REGION   4
#define STEP_UNFLAG_END		 5
#define STEP_END			 6



/********************* Windows Message ID ***********************************/

#define WM_SHOW_ERROR								(WM_USER + 10)
#define WM_HIDE_ERROR								(WM_USER + 11)
#define WM_SHOW_ALARM								(WM_USER + 12)
#define WM_HIDE_ALARM								(WM_USER + 13)
#define WM__MINIMIZE_WINDOW							(WM_USER + 14)
#define WM_SHOW_STATE								(WM_USER + 15)
#define WM_HIDE_STATE								(WM_USER + 16)
#define WM_POPUP_MSG_ALL_CLOSE						(WM_USER + 17)

//
//1.1 State Define
#define STATE_INIT								1
#define STATE_READY								2

#define STATE_JOB_END							5

//1.1.1 Laser Alarm Code
#define ALARM_CODE_LASER_POWER_SUPPLY					93
#define ALARM_CODE_LASER_FAN							95
#define ALARM_CODE_LASER_EMERGENCY_STOP           		99

//1.2 Error Define
#define ERROR_MC_ON										9
#define ERROR_EMERGENCY_HAS_BEEN_DETECTED				10
#define ERROR_DATA_NOT_FOUND							11
#define ERROR_PARAMETER_NOT_FOUND						12
#define ERROR_MACHINE_STATUS_IS_NOT_INIT				13
#define ERROR_READY_STATUS_IS_NOT_READY					14
#define ERROR_ON_AUTOMARK								15
#define ERROR_OVERFLOW									16
#define ERROR_ADMIN										17
#define ERROR_POWER_OVERFLOW							18
#define ERROR_SCANNER_OVERFLOW							19
#define ERROR_LASER_TEMP_ALARM							20
#define ERROR_LASER_SYSTEM_FAULT_ALARM					21
#define ERROR_LASER_POWER_SUPPLY_FAULT					22
#define ERROR_LASER_FAN_FAULT							23
#define ERROR_LASER_EMERGENCY_STOP_FAULT				24
#define ERROR_LASER_COM_DISCONECT						25
#define ERROR_SCRAP_SENSOR_HEAD1						26
#define ERROR_SCRAP_SENSOR_HEAD2						27
#define ERROR_NOTCHING_SENSOR_HEAD1						28
#define ERROR_NOTCHING_SENSOR_HEAD2						29


//Error
//{{
#define ERROR_CHECK_LASER_PARAM					53
#define ERROR_VISION_INSPECT					60




#define RTC_CARD_NUM_1						1
#define RTC_CARD_NUM_2						2

#define RTC5_SIZE_OF_MEMORY						1048575-1 //	
#define RTC6_SIZE_OF_MEMORY						8388608-1 //	

#define RTC5_SET_MOTF_OUTPUT					5

//*************************************************************
//2. DIRECTORY PATH DEFINITION
//*************************************************************

#define DIRECTORY_NAME						"\\Config\\"
#define LOG_DIRECTORY_NAME		    		"\\Log\\"
#define PROJECT_DIRECTORY_NAME				"\\Project\\"
#define ALARM_CONFIG_FILE_NAME				"Alarm.ini"
#define ERROR_CONFIG_FILE_NAME				"Error.ini"
#define PROJECT_CONFIG_FILE_NAME			"Project.ini"
#define POSITION_CONFIG_FILE_NAME			"Position.ini"
#define ENGLISH_LANGUAGE_CONFIG_FILE_NAME   "LanguageEnglish.ini"
#define KOREA_LANGUAGE_CONFIG_FILE_NAME		"LanguageKorea.ini"


