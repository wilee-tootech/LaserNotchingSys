#ifndef _RUNNING_DEFINE_H_
#define _RUNNING_DEFINE_H_

#include "../Include/EXTERN/TimeCounter.h"

//Laser
#define LOSYN_LASER_INDEX 0

enum 
{
	E_LASER_MODE_CW		 = 0,
	E_LASER_MODE_PULSE		,
};

//Light
#define LIGHT_CONTROL_PT01  0

//////////////////////////////////////////////////////////////////////////

//Seq
#define START_ACTION				40  //1이상 : 해당 Function 이 Sequency 안에 동작 중임.
#define FINISH_ACTION				0  // 0 : 의미 -> 모든 동작 종료 및 대기 상태


#define GET_SEQMAIN_STEP(X)	((X/100) * 100)
#define GET_SEQSUB_STEP(X)	((X/10) * 10) 


//
//1.1 Alarm Define
#define ALARM_INIT								1
#define ALARM_READY								2

#define ALARM_JOB_END							5

#define ERROR_MC_ON								9
#define ERROR_EMERGENCY_HAS_BEEN_DETECTED		10

//#define ERROR_MAIN_VACUUM_CHK					12
#define ERROR_MACHINE_STATUS_IS_NOT_INIT		13
#define ERROR_READY_STATUS_IS_NOT_READY			14

//Error
//{{
#define ERROR_CHECK_LASER_PARAM					53

//}}

//////////////////////////////////////////////////////////////////////////

// [INIT] TIMEOUT & ERROR MSG NUMBER
#define ERROR_MSG_RUNMGR_INIT				100

// [INIT TIMEOUT]
#define TIMEOUT_RUNNING_BODY_INIT			( 60 * 1000 ) * 10 *10
#define TIMEOUT_RUNNING_LASER_INIT			( 60 * 1000 ) * 10 *10

//  [INIT ERROR MSG]
#define ERROR_MSG_BODY_INIT					1000
#define ERROR_MSG_LASER_INIT				1500

//////////////////////////////////////////////////////////////////////////

#define ERROR_MSG_RUNMGR_READY				200

// [READY TIMEOUT]
#define TIMEOUT_RUNNING_BODY_READY			( 60 * 1000 ) * 10 *10
#define TIMEOUT_RUNNING_LASER_READY			( 60 * 1000 ) * 10 *10

// [READY ERROR MSG]
#define ERROR_MSG_BODY_READY				2000
#define ERROR_MSG_LASER_READY				2500

//////////////////////////////////////////////////////////////////////////

#define ERROR_MSG_RUNMGR_RUN				300

// [READY TIMEOUT]
#define TIMEOUT_RUNNING_BODY_RUN			( 60 * 1000 ) * 10 *10
#define TIMEOUT_RUNNING_LASER_RUN			( 60 * 1000 ) * 10 *10

// [READY ERROR MSG]
#define ERROR_MSG_BODY_RUN					3000
#define ERROR_MSG_LASER_RUN					3500

//////////////////////////////////////////////////////////////////////////

//1.2 Seq timeout
#define TIMEOUT_RUNMGR_INIT						60 * 1000

#define TIMEOUT_RUNMGR_READY					60 * 1000

#define TIMEOUT_RUNMGR_RUN						120 * 1000



//////////////////////////////////////////////////////////////////////////

//1.3 MainFrame WINDOW MESSAGE
#define WM_SHOW_ERROR								(WM_USER + 10)
#define WM_HIDE_ERROR								(WM_USER + 11)
#define WM_SHOW_ALARM								(WM_USER + 12)
#define WM_HIDE_ALARM								(WM_USER + 13)
#define WM_POPUP_MSG_ALL_CLOSE						(WM_USER + 14)

#define WM_LOGIN_UPDATE								(WM_USER + 40)
#define WM_WINDOW_UPDATE							(WM_USER + 41)
#define  WM_INFOR_MARK_IMAGE_DRAW					(WM_USER + 42)


#define WM_PARAM_DRAW_MAIN_OPERATION		1 
#define WM_PARAM_DRAW_SCANNER_MANUAL		2 


enum RUN_MODE {			
	JAM	= -1		,
	INIT			,
	READY			,
	STOP			,
	AUTO            ,
	MAX_RUNMODE		
};

//Seq Module ID
enum SEQ_MODULE_ID {
	SEQ_MODULE_ID_BODY				, // 0
	SEQ_MODULE_ID_LASER				, // 1
	SEQ_MODULE_ID_MAX
};


enum SELECT_MANUAL_MODE
{

	SELECT_MANUAL_MODE_NONE,

	//BODY
	SELECT_MANUAL_MODE_BODY_WORK_POS,
	//LASER

	SELECT_MANUAL_MODE_MAX,

};

//////////////////////////////////////////////////////////////////////////

typedef struct DefRun
{
	//MAINSEQ
	int m_nMainStep;
	int m_nDelay;
	int m_nPreset;
	int m_nError;
	int m_nCount;
	//SUBSEQ
	int m_nSubStep;
	int m_nSubDelay;
	int m_nSubCount;
	int m_nSubError;
	int m_nSubPreset;

	//Position
	double m_fTargetPosX;
	double m_fTargetPosY;
	

	BOOL m_bBackup;
	BOOL m_bProcStop;

	CTimeCounter m_DelayTime;

	DefRun(void)
	{
		Clear();
	}

	void Clear(void)
	{
		m_nMainStep		= m_nDelay		= m_nPreset		= m_nError		= m_nCount		= 0;
		m_nSubStep		= m_nSubDelay	= m_nSubPreset	= m_nSubError	= m_nSubCount	= 0;
		m_bBackup		= FALSE;
		m_bProcStop		= FALSE;

		m_fTargetPosX		=	0.0;
		m_fTargetPosY		=	0.0;
		
	}
}DEF_RUN;

//////////////////////////////////////////////////////////////////////////

//*************************************************************
//2. DIRECTORY PATH DEFINITION
//*************************************************************

#define DIRECTORY_NAME						"\\Config\\"
#define JAM_DIRECTORY_NAME					"\\JAM\\"
#define LOG_DIRECTORY_NAME		    		"\\LOG\\"
#define PROJECT_DIRECTORY_NAME				"\\PROJECT\\"
#define MOTION_CONFIG_FILE_NAME     		"Motion.ini" 
#define DIGITAL_CONFIG_FILE_NAME			"Digital.ini"
#define ALARM_CONFIG_FILE_NAME				"Alarm.ini"
#define ERROR_CONFIG_FILE_NAME				"Error.ini"
#define PROJECT_CONFIG_FILE_NAME			"Project.ini"
#define POSITION_CONFIG_FILE_NAME			"Position.ini"
#define ENGLISH_LANGUAGE_CONFIG_FILE_NAME   "LanguageEnglish.ini"
#define KOREA_LANGUAGE_CONFIG_FILE_NAME		"LanguageKorea.ini"


//*************************************************************
//3. I/O DEFINITION
//*************************************************************

typedef enum DEF_BUTTON_SW
{
	BUTTON_OFF	,
	BUTTON_START,
	BUTTON_STOP	,
	BUTTON_RESET,

}BUTTON_SW;

#define ON	1
#define OFF 0

typedef enum DEF_PNEUMATIC_SOL   
{   
	PNEUMATIC_OFF        ,
	PNEUMATIC_VACUUM     ,
	PNEUMATIC_PURGE      ,
}PNEUMATIC_SOL;

typedef enum DEF_TOWER_LAMP 
{   
	LAMP_NONE       ,
	BLINK_RED       ,
	LAMP_RED        ,
	BLINK_YELLOW    ,
	LAMP_YELLOW     ,
	BLINK_GREEN     ,
	LAMP_GREEN      
}TOWER_LAMP;

typedef enum DEF_MELODY     
{   
	MELODY_NONE     ,
	MELODY_ERROR    ,
	MELODY_ALARM    ,
	MELODY_JOBEND 
}MELODY;


//*************************************************************



//*************************************************************
//5. MOTION POSITION
//*************************************************************


//5.2 TransferHeadFirst
// typedef struct DEF_HEAD_1ST_CONFIG_SETTING
// {
// 	//Position
//  double m_fSafetyPos;
// 
// 	DEF_HEAD_1ST_CONFIG_SETTING(void)
// 	{
// 		Clear();
// 	}
// 	void Clear(void)
// 	{
// 		//Position
// 		m_fSafetyPos							= 0.0;
// 	}
// }HEAD_1ST_CONFIG_SETTING;
 
//*************************************************************
//6. ETC
//*************************************************************


#define FORM_FONT_SIZE	15L


#define PI 3.1415926535897932384626433832795


//*************************************************************
//4. COLOR DEFINITION
//*************************************************************
const COLORREF clAliceBlue               = RGB(240,248,255);
const COLORREF clAntiqueWhite            = RGB(250,235,215);
const COLORREF clAqua                    = RGB(  0,255,255);
const COLORREF clAquamarine              = RGB(127,255,212);
const COLORREF clAzure                   = RGB(240,255,255);
const COLORREF clBeige                   = RGB(245,245,220);
const COLORREF clBisque                  = RGB(255,228,196);
const COLORREF clBlack                   = RGB(  0,  0,  0);
const COLORREF clBlanchedAlmond          = RGB(255,255,205);
const COLORREF clBlue                    = RGB(  0,  0,255);
const COLORREF clBlueViolet              = RGB(138, 43,226);
const COLORREF clBrown                   = RGB(165, 42, 42);
const COLORREF clBurlywood               = RGB(222,184,135);
const COLORREF clCadetBlue               = RGB( 95,158,160);
const COLORREF clChartreuse              = RGB(127,255,  0);
const COLORREF clChocolate               = RGB(210,105, 30);
const COLORREF clCoral                   = RGB(255,127, 80);
const COLORREF clCornflowerBlue          = RGB(100,149,237);
const COLORREF clCornsilk                = RGB(255,248,220);
const COLORREF clCrimson                 = RGB(220, 20, 60);
const COLORREF clCyan                    = RGB(  0,255,255);
const COLORREF clDarkBlue                = RGB(  0,  0,139);
const COLORREF clDarkCyan                = RGB(  0,139,139);
const COLORREF clDarkGoldenRod           = RGB(184,134, 11);
const COLORREF clDarkGray                = RGB(169,169,169);
const COLORREF clDarkGreen               = RGB(  0,100,  0);
const COLORREF clDarkKhaki               = RGB(189,183,107);
const COLORREF clDarkMagenta             = RGB(139,  0,139);
const COLORREF clDarkOliveGreen          = RGB( 85,107, 47);
const COLORREF clDarkOrange              = RGB(255,140,  0);
const COLORREF clDarkOrchid              = RGB(153, 50,204);
const COLORREF clDarkRed                 = RGB(139,  0,  0);
const COLORREF clDarkSalmon              = RGB(233,150,122);
const COLORREF clDarkSeaGreen            = RGB(143,188,143);
const COLORREF clDarkSlateBlue           = RGB( 72, 61,139);
const COLORREF clDarkSlateGray           = RGB( 47, 79, 79);
const COLORREF clDarkTurquoise           = RGB(  0,206,209);
const COLORREF clDarkViolet              = RGB(148,  0,211);
const COLORREF clDeepPink                = RGB(255, 20,147);
const COLORREF clDeepSkyBlue             = RGB(  0,191,255);
const COLORREF clDimGray                 = RGB(105,105,105);
const COLORREF clDodgerBlue              = RGB( 30,144,255);
const COLORREF clFireBrick               = RGB(178, 34, 34);
const COLORREF clFloralWhite             = RGB(255,250,240);
const COLORREF clForestGreen             = RGB( 34,139, 34);
const COLORREF clFuchsia                 = RGB(255,  0,255);
const COLORREF clGainsboro               = RGB(220,220,220);
const COLORREF clGhostWhite              = RGB(248,248,255);
const COLORREF clGold                    = RGB(255,215,  0);
const COLORREF clGoldenRod               = RGB(218,165, 32);
const COLORREF clGray                    = RGB(127,127,127);
const COLORREF clGreen                   = RGB(  0,128,  0);
const COLORREF clGreenYellow             = RGB(173,255, 47);
const COLORREF clHoneyDew                = RGB(240,255,240);
const COLORREF clHotPink                 = RGB(255,105,180);
const COLORREF clIndianRed               = RGB(205, 92, 92);
const COLORREF clIndigo                  = RGB( 75,  0,130);
const COLORREF clIvory                   = RGB(255,255,240);
const COLORREF clKhaki                   = RGB(240,230,140);
const COLORREF clLavender                = RGB(230,230,250);
const COLORREF clLavenderBlush           = RGB(255,240,245);
const COLORREF clLawngreen               = RGB(124,252,  0);
const COLORREF clLemonChiffon            = RGB(255,250,205);
const COLORREF clLightBlue               = RGB(173,216,230);
const COLORREF clLightCoral              = RGB(240,128,128);
const COLORREF clLightCyan               = RGB(224,255,255);
const COLORREF clLightGoldenRodYellow    = RGB(250,250,210);
const COLORREF clLightGreen              = RGB(144,238,144);
const COLORREF clLightGrey               = RGB(211,211,211);
const COLORREF clLightPink               = RGB(255,182,193);
const COLORREF clLightSalmon             = RGB(255,160,122);
const COLORREF clLightSeaGreen           = RGB( 32,178,170);
const COLORREF clLightSkyBlue            = RGB(135,206,250);
const COLORREF clLightSlateGray          = RGB(119,136,153);
const COLORREF clLightSteelBlue          = RGB(176,196,222);
const COLORREF clLightYellow             = RGB(255,255,224);
const COLORREF clLime                    = RGB(  0,255,  0);
const COLORREF clLimeGreen               = RGB( 50,205, 50);
const COLORREF clLinen                   = RGB(250,240,230);
const COLORREF clMagenta                 = RGB(255,  0,255);
const COLORREF clMaroon                  = RGB(128,  0,  0);
const COLORREF clMediumAquamarine        = RGB(102,205,170);
const COLORREF clMediumBlue              = RGB(  0,  0,205);
const COLORREF clMediumOrchid            = RGB(186, 85,211);
const COLORREF clMediumPurple            = RGB(147,112,219);
const COLORREF clMediumSeaGreen          = RGB( 60,179,113);
const COLORREF clMediumSlateBlue         = RGB(123,104,238);
const COLORREF clMediumSpringGreen       = RGB(  0,250,154);
const COLORREF clMediumTurquoise         = RGB( 72,209,204);
const COLORREF clMediumVioletRed         = RGB(199, 21,133);
const COLORREF clMidnightBlue            = RGB( 25, 25,112);
const COLORREF clMintCream               = RGB(245,255,250);
const COLORREF clMistyRose               = RGB(255,228,225);
const COLORREF clMoccasin                = RGB(255,228,181);
const COLORREF clNavajoWhite             = RGB(255,222,173);
const COLORREF clNavy                    = RGB(  0,  0,128);
const COLORREF clOldLace                 = RGB(253,245,230);
const COLORREF clOlive                   = RGB(128,128,  0);
const COLORREF clOliveDrab               = RGB(107,142, 35);
const COLORREF clOrange                  = RGB(255,165,  0);
const COLORREF clOrangeRed               = RGB(255, 69,  0);
const COLORREF clOrchid                  = RGB(218,112,214);
const COLORREF clPaleGoldenRod           = RGB(238,232,170);
const COLORREF clPaleGreen               = RGB(152,251,152);
const COLORREF clPaleTurquoise           = RGB(175,238,238);
const COLORREF clPaleVioletRed           = RGB(219,112,147);
const COLORREF clPapayaWhip              = RGB(255,239,213);
const COLORREF clPeachPuff               = RGB(255,218,185);
const COLORREF clPeru                    = RGB(205,133, 63);
const COLORREF clPink                    = RGB(255,192,203);
const COLORREF clPlum                    = RGB(221,160,221);
const COLORREF clPowderBlue              = RGB(176,224,230);
const COLORREF clPurple                  = RGB(128,  0,128);
const COLORREF clRed                     = RGB(255,  0,  0);
const COLORREF clRosyBrown               = RGB(188,143,143);
const COLORREF clRoyalBlue               = RGB( 65,105,225);
const COLORREF clSaddleBrown             = RGB(139, 69, 19);
const COLORREF clSalmon                  = RGB(250,128,114);
const COLORREF clSandyBrown              = RGB(244,164, 96);
const COLORREF clSeaGreen                = RGB( 46,139, 87);
const COLORREF clSeaShell                = RGB(255,245,238);
const COLORREF clSienna                  = RGB(160, 82, 45);
const COLORREF clSilver                  = RGB(192,192,192);
const COLORREF clSkyBlue                 = RGB(135,206,235);
const COLORREF clSlateBlue               = RGB(106, 90,205);
const COLORREF clSlateGray               = RGB(112,128,144);
const COLORREF clSnow                    = RGB(255,250,250);
const COLORREF clSpringGreen             = RGB(  0,255,127);
const COLORREF clSteelBlue               = RGB( 70,130,180);
const COLORREF clTan                     = RGB(210,180,140);
const COLORREF clTeal                    = RGB(  0,128,128);
const COLORREF clThistle                 = RGB(216,191,216);
const COLORREF clTomato                  = RGB(255, 99, 71);
const COLORREF clTurquoise               = RGB( 64,224,208);
const COLORREF clViolet                  = RGB(238,130,238);
const COLORREF clWheat                   = RGB(245,222,179);
const COLORREF clWhite                   = RGB(255,255,255);
const COLORREF clWhiteSmoke              = RGB(245,245,245);
const COLORREF clYellow                  = RGB(255,255,  0);
const COLORREF clYellowGreen             = RGB(139,205, 50);
const COLORREF clTitle					 = RGB(67 , 67, 67);
const COLORREF clSubTitle				 = RGB(140,140,140); 
// const COLORREF clPosition				 = RGB(255, 64, 37);
// const COLORREF clSetting                 = RGB(232, 87, 34);
// const COLORREF clDelay                   = RGB(255,135, 50);
// const COLORREF clLimitCount				 = RGB(232,145, 34);
// const COLORREF clTitle					 = RGB(67 , 67, 67);
// const COLORREF clSubTitle				 = RGB(140,140,140); 
const COLORREF clPosition				 = RGB( 93, 93, 93);
const COLORREF clSetting                 = RGB( 66,106, 39);
const COLORREF clDelay                   = RGB(109,144,  2);
const COLORREF clLimitCount				 = RGB(195,112,100);

// System cls
const COLORREF clActiveBorder            = ::GetSysColor(COLOR_ACTIVEBORDER); //(0x80000000 | COLOR_ACTIVEBORDER);
const COLORREF clActiveCaption           = ::GetSysColor(COLOR_ACTIVECAPTION);
const COLORREF clActiveCaptionText       = ::GetSysColor(COLOR_CAPTIONTEXT);
const COLORREF clAppWorkspace            = ::GetSysColor(COLOR_APPWORKSPACE);
const COLORREF clBackground              = ::GetSysColor( COLOR_BACKGROUND);
const COLORREF clBtnFace                 = ::GetSysColor( COLOR_BTNFACE);
const COLORREF clBtnHighlight            = ::GetSysColor( COLOR_BTNHIGHLIGHT);
const COLORREF clBtnHilight              = ::GetSysColor( COLOR_BTNHIGHLIGHT);
const COLORREF clBtnShadow               = ::GetSysColor(COLOR_BTNSHADOW);
const COLORREF clBtnText                 = ::GetSysColor( COLOR_BTNTEXT);
const COLORREF clCaptionText             = ::GetSysColor( COLOR_CAPTIONTEXT);
const COLORREF clControl                 = ::GetSysColor( COLOR_BTNFACE);
const COLORREF clControlDark             = ::GetSysColor( COLOR_BTNSHADOW);
const COLORREF clControlDarkDark         = ::GetSysColor( COLOR_3DDKSHADOW);
const COLORREF clControlLight            = ::GetSysColor( COLOR_BTNHIGHLIGHT);
const COLORREF clControlLightLight       = ::GetSysColor( COLOR_BTNHIGHLIGHT);
const COLORREF clControlText             = ::GetSysColor( COLOR_BTNTEXT);
const COLORREF clDesktop                 = ::GetSysColor( COLOR_BACKGROUND);
const COLORREF clGradientActiveCaption   = ::GetSysColor( COLOR_GRADIENTACTIVECAPTION);
const COLORREF clGradientInactiveCaption = ::GetSysColor( COLOR_GRADIENTINACTIVECAPTION);
const COLORREF clGrayText                = ::GetSysColor( COLOR_GRAYTEXT);
const COLORREF clHighlight               = ::GetSysColor( COLOR_HIGHLIGHT);
const COLORREF clHighlightText           = ::GetSysColor(COLOR_HIGHLIGHTTEXT);
const COLORREF clHotLight                = ::GetSysColor(COLOR_HOTLIGHT);
const COLORREF clHotTrack                = ::GetSysColor(COLOR_HOTLIGHT);
const COLORREF clInactiveBorder          = ::GetSysColor(COLOR_INACTIVEBORDER);
const COLORREF clInactiveCaption         = ::GetSysColor(COLOR_INACTIVECAPTION);
const COLORREF clInactiveCaptionText     = ::GetSysColor(COLOR_INACTIVECAPTIONTEXT);
const COLORREF clInfo                    = ::GetSysColor(COLOR_INFOBK);
const COLORREF clInfoBk                  = ::GetSysColor( COLOR_INFOBK);
const COLORREF clInfoText                = ::GetSysColor( COLOR_INFOTEXT);
const COLORREF clMenu                    = ::GetSysColor( COLOR_MENU);
const COLORREF clMenuBar                 = ::GetSysColor( COLOR_MENUBAR);
const COLORREF clMenuHilight             = ::GetSysColor( COLOR_MENUHILIGHT);
const COLORREF clMenuText                = ::GetSysColor( COLOR_MENUTEXT);
const COLORREF clScrollBar               = ::GetSysColor( COLOR_SCROLLBAR);
const COLORREF clWindow                  = ::GetSysColor( COLOR_WINDOW);
const COLORREF clWindowFrame             = ::GetSysColor( COLOR_WINDOWFRAME);
const COLORREF clWindowText              = ::GetSysColor( COLOR_WINDOWTEXT);		


//////////////////////////////////////////////////////////////////////////

#endif