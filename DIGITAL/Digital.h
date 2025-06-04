#ifndef _DIGITAL_H_
#define _DIGITAL_H_

#include "../DIGITAL/DigitalDefine.h"
#include "../RUN_MODULE/RunningDefine.h"
#include "../EXTERN/TimeCounter.h"

#include "./ADJModule.h"
#include <NX_AJINAIO/AIOAJIN.h>

#define CDIGITAL_LAMP_INTERVAL 500

//X00~X07
#define X_EMO									Digital->m_bfInput[0].Bit.B00	// X00      
#define X_MC_ON									Digital->m_bfInput[0].Bit.B01	// X01
#define X_AIR_PUSHER_1							Digital->m_bfInput[0].Bit.B02	// X02
#define X_AIR_PUSHER_2							Digital->m_bfInput[0].Bit.B03	// X03
#define X_04									Digital->m_bfInput[0].Bit.B04	// X04
#define X_05									Digital->m_bfInput[0].Bit.B05	// X05
#define X_06									Digital->m_bfInput[0].Bit.B06	// X06
#define X_07									Digital->m_bfInput[0].Bit.B07	// X07
//X08~X15
#define X_08									Digital->m_bfInput[0].Bit.B08   // X08
#define X_09									Digital->m_bfInput[0].Bit.B09   // X09
#define X_LASER_ON								Digital->m_bfInput[0].Bit.B10   // X10
#define X_11									Digital->m_bfInput[0].Bit.B11	// X11 
#define X_12									Digital->m_bfInput[0].Bit.B12	// X12 
#define X_13									Digital->m_bfInput[0].Bit.B13	// X13 
#define X_14	 								Digital->m_bfInput[0].Bit.B14	// X14 
#define X_15									Digital->m_bfInput[0].Bit.B15   // X15 

//Y00~Y07
#define Y_00									Digital->m_bfOutput[0].Bit.B00	//Y_00 
#define Y_MC_ON									Digital->m_bfOutput[0].Bit.B01	//Y_01 
#define Y_AIR_PUSHER							Digital->m_bfOutput[0].Bit.B02	//Y_02 
#define Y_03									Digital->m_bfOutput[0].Bit.B03	//Y_03 
#define Y_04									Digital->m_bfOutput[0].Bit.B04	//Y_04 
#define Y_05									Digital->m_bfOutput[0].Bit.B05	//Y_05 
#define Y_06									Digital->m_bfOutput[0].Bit.B06	//Y_06 
#define Y_07									Digital->m_bfOutput[0].Bit.B07	//Y_07 
//Y08~Y15
#define Y_08									Digital->m_bfOutput[0].Bit.B08	//Y_08 
#define Y_09									Digital->m_bfOutput[0].Bit.B09	//Y_09 
#define Y_LASER_ON								Digital->m_bfOutput[0].Bit.B10	//Y_10 
#define Y_11									Digital->m_bfOutput[0].Bit.B11	//Y_11 
#define Y_12									Digital->m_bfOutput[0].Bit.B12	//Y_12 
#define Y_13									Digital->m_bfOutput[0].Bit.B13	//Y_13 
#define Y_14									Digital->m_bfOutput[0].Bit.B14	//Y_14 
#define Y_15									Digital->m_bfOutput[0].Bit.B15	//Y_15 

#define DIO_AJIN 0

class CDigital
{
	typedef union DEF_IO_DATA
	{
		unsigned long Data;
		struct Bit
		{
			unsigned long B00 : 1;
			unsigned long B01 : 1;
			unsigned long B02 : 1;
			unsigned long B03 : 1;
			unsigned long B04 : 1;
			unsigned long B05 : 1;
			unsigned long B06 : 1;
			unsigned long B07 : 1;
			unsigned long B08 : 1;
			unsigned long B09 : 1;
			unsigned long B10 : 1;
			unsigned long B11 : 1;
			unsigned long B12 : 1;
			unsigned long B13 : 1;
			unsigned long B14 : 1;
			unsigned long B15 : 1;

			unsigned long B16 : 1;
			unsigned long B17 : 1;
			unsigned long B18 : 1;
			unsigned long B19 : 1;
			unsigned long B20 : 1;
			unsigned long B21 : 1;
			unsigned long B22 : 1;
			unsigned long B23 : 1;
			unsigned long B24 : 1;
			unsigned long B25 : 1;
			unsigned long B26 : 1;
			unsigned long B27 : 1;
			unsigned long B28 : 1;
			unsigned long B29 : 1;
			unsigned long B30 : 1;
			unsigned long B31 : 1;
		}Bit;
	}IO_DATA;

	typedef struct DEF_CYLINDER_MODULE
	{
		CString m_strName;
		CString m_strPart;
		int m_nX0;
		int m_nX1;
		int m_nY0;
		int m_nY1;
		int m_nSetState;
		int m_nRunState;
		int m_nSetTime;
		CTimeCounter m_RunTime;
		int m_nSetDelay;
		int m_nSetDelay2;
		CTimeCounter m_RunDelay;

		DEF_CYLINDER_MODULE(void)
		{
			Clear();
		}
		void Clear(void)
		{
			m_strName	= TEXT("");
			m_strPart   = TEXT("");
			m_nX0		=  0;
			m_nX1		=  0;
			m_nY0		=  0;
			m_nY1		=  0;
			m_nSetState	=  0;
			m_nRunState	= -1;
			m_nSetTime  =  0;
			m_nSetDelay =  0;
			m_nSetDelay2=  0;
		}
	}CYLINDER_MODULE;

private:
	int m_nLampDelay;
	int m_nDoorDelay;
	int m_nInterval;

	CTimeCounter m_LampDlay;

	TOWER_LAMP m_eLamp;
	CYLINDER_MODULE m_stCylinder[MAX_CYLINDER];

	BOOL InitControl(void);
	BOOL DeleteControl(void);

protected:
public:
	/**
	@brief 
	@details DIO Module
	*/
// 	CADJModule* m_pADJModule;
// 	CAIOAJIN*	m_pAJINAIO;

	/**
	@author 
	@date 2016년02월04일-09시26분36초
	@param Voltage Setting
	@return none.
	@brief AIO 
	@remark 
	*/

	double* GetDataBufferPointor();
	double* GetTimeBufferPointor();
	BOOL    GetLaserSeqRunning();




	IO_DATA m_bfInput[MAX_IO_BOARD];
	IO_DATA m_bfOutput[MAX_IO_BOARD];

	void Clear(void);
	void Read(void);
	void Wirte(void);
	void Scan(void);

	void TowerScan(void);
	void SetTower(TOWER_LAMP a_elamp);
	void SetSwitch(BUTTON_SW a_ebutton, BOOL a_bMode = FALSE);
	void SetMelody(MELODY a_eMode);

	BOOL GetX(int a_nIndex);
	BOOL GetY(int a_nIndex);
	void SetY(int a_nIndex, BOOL a_bMode);

	BOOL GetSensor (AIR_CYL a_eIndex, BOOL a_bMode);
	BOOL GetCylinder(AIR_CYL a_eIndex, BOOL a_bMode);
	BOOL SetCylinder(AIR_CYL a_eIndex, BOOL a_bMode);
	void RunCylinder(void);


	//
	BOOL OpenConfig(void);

	//////////////////////////////////////////////////////////////////////////
	//아날로그
	CADJModule* m_pADJModule;
	CAIOAJIN*	m_pAJINAIO;

	void SetAIOVoltage(double fValue);

	void Set_AO_Range(double fMin, double fMax);

	void StartAnalogOutput(void);
	void StopAnalogOutput(void);
	void SetADJDataAlloc(int nBufferSize);
	void SetADJData(int nIndex, double fVoltage, double fOnTime);
	int  GetADJDataBufferSize();

	void SetOn_MC(BOOL a_sSetStatus);


public:
	CDigital(void);
	~CDigital(void);
};

extern CDigital* Digital;
#endif

								