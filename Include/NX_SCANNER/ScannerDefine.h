#ifndef _SCANNER_DEFINE_HEADER_
#define _SCANNER_DEFINE_HEADER_

typedef struct 
{

	BOOL bPosAckX;
	BOOL bPosAckY;
	BOOL bTempStat;
	BOOL bPwrStat;

} THeadInfo;

typedef struct 
{

	UINT m_unGalvoXStat;
	long m_lGalvoXPos;
	UINT m_unGalvoYStat;
	long m_lGalvoYPos;

} TGalvoInfo;

typedef struct 
{

	BOOL bBusy1;
	BOOL bBusy2;
	BOOL bLoad1;
	BOOL bLoad2;
	BOOL bReady1;
	BOOL bReady2;
	BOOL bUsed1;
	BOOL bUsed2;

} TListExeStat;

typedef union 
{

	UINT unErrList;

	typedef struct 
	{
		UINT RTC5_NO_ERROR				: 1;		//0			/* RTC5_NO_CARD = 1  */
		UINT RTC5_ACCESS_DENIED			: 2;		//2
		UINT RTC5_SEND_ERROR			: 3;		//4
		UINT RTC5_TIMEOUT				: 4;		//8
		UINT RTC5_PARAM_ERROR			: 5;		//16
		UINT RTC5_BUSY					: 6;		//32
		UINT RTC5_REJECTED				: 7;		//64
		UINT RTC5_IGNORED				: 8;		//128
		UINT RTC5_VERSION_MISMATCH		: 9;		//256
		UINT RTC5_VERIFY_ERROR			: 10;		//512
		UINT RTC5_TYPE_REJECTED			: 11;		//1024
		UINT RTC5_OUT_OF_MEMORY			: 12;		//2048
		UINT RTC5_EEPROM_ERROR			: 13;		//4096

		UINT RTC5_CONFIG_ERROR			: 17;		//65536
	} TErrBit;

} UDefErr;

enum ENUM_LIST_CMD
{	// JUMP COMMANDS
	JUMP_ABS = 0, JUMP_REL, PARA_JUMP_ABS, PARA_JUMP_REL, TIMED_JUMP_ABS, TIMED_JUMP_REL, TIMED_PARA_JUMP_ABS, TIMED_PARA_JUMP_REL,

	// MICROVECTOR COMMANDS
	MICRO_VECTOR_ABS, MICRO_VECTOR_REL,

	// MARK COMMANDS
	ARC_ABS, ARC_REL, MARK_ABS, MARK_ELLIPSE_ABS, MARK_ELLIPSE_REL, MARK_REL, PARA_MARK_ABS, PARA_MARK_REL, SET_ELLIPSE, 
	TIMED_ARC_ABS, TIMED_ARC_REL, TIMED_MARK_ABS, TIMED_MARK_REL, TIMED_PARA_MARK_ABS, TIMED_PARA_MARK_REL,

	// LIST HANDLEING AND STRUCTED PROGRAMMING
	LIST_COMMINUE, LIST_JUMP_POS, LIST_JUMP_REL, LIST_NOP, LONG_DELEY, SET_END_OF_LIST, SET_LIST_JUMP, SET_WAIT,
	
	// SETTING THE LASER PARAM
	SET_AUTO_LASER_PARAMS_LSIT, SET_ENCODER_SPEED, SET_FIRSTPULSE_KILLER_LIST, SET_LASER_DELAYS, SET_LASER_PIN_OUT_LIST, 
	SET_LASER_PULSES, SET_LASER_TIMING, SET_PULSE_PICKING_LIST, SET_QSWITCH_DELAY_LIST, SET_VECTOR_CONTROL, 

	// SETTING THE SCANNER PARAMETERS
	SET_JUMP_SPEED, SET_MARK_SPEED, SET_SCANNER_DELAYS, SET_SKY_WRITING_LIMIT_LIST, SET_SKY_WRITING_LIST, SET_SKY_WRITING_MODE_LIST, 
	SET_SKY_WRITING_PARA_LIST, 

	//COORDINATE TRANSFORM
	SET_ANGLE_LIST, SET_DEFOCUS_LIST, SET_MATRIX_LIST, SET_OFFSET_LIST, SET_OFFSET_XYZ_LIST, SET_SCALE_LIST, 

	// DIRECT_LASER_AND_SCAN HEAD CONTROL
	LASER_ON_LIST, LASER_ON_PULSES_LIST, LASER_SIGNAL_OFF_LIST, LASER_SIGNAL_ON_LIST, PARA_LASER_ON_PULSES_LIST,
	
	MAX_LIST_CMD,

	SET_LASER_PULSES_FIRST, //BJBD
	END_OF_CIRCLE,           //BJBD 
	SET_LONG_DELAY,         //Added by You-gu(20160422)
	END_OF_LIST

};

enum SCANNER_MODE{          //BJBD 
	ETCH_ON_FLY_FRONT_1ST_ZONE=1,
	ETCH_ON_FLY_FRONT_2ND_ZONE=2,
	ETCH_NON_FLY=3,
	ETCH_ON_FLY_SIDE=4, 
	ETCH_ON_FLY_STOP=5,  
};

typedef struct 
{

	ENUM_LIST_CMD eCmd;
	double daParam[3];

	void Clear()
	{
		eCmd = JUMP_ABS;
		daParam[0] = daParam[1] = daParam[2] = 0.0;
	}

} TDefCmdList;

typedef struct 
{
	 
	BOOL ListStatus[2];

	void Clear()
	{ 
		ListStatus[0] =FALSE;
		ListStatus[1]=FALSE;
	}

} TDefExecuteStatus;


typedef struct 
{
	/* 1 bit equals 1/64 μs. */
	double dHalfPeriod;
	double dPulseLen;

} TDefLasPulse;

typedef struct 
{
	/* 1 bit equals 10 μs. Allowed range: [0…(232–1)] */ 
	UINT unJump;
	UINT unMark;
	UINT unPolygon;

} TDefDelay;

typedef struct 
{
	/*
	LaserOnDelay LaserOn Delay as a signed 32-bit value				1 bit equals 0.5 μs. Allowed range: [ – 231…+(221–1)]
	LaserOffDelay LaserOff Delay as an unsigned 32-bit value.		1 bit equals 0.5 μs. Allowed range: [0 … +(221–1)]
	*/
	UINT unLaserOn;
	UINT unLaserOff;

} TDefLasDelay;

typedef struct 
{
	/* jump speed in bits per ms (as a 64-bit IEEE floating point value)
	Allowed range: [1.6 … 800000.0]
	(*/
	double dJump;
	double dMark;

} TDefSpeed;

#endif