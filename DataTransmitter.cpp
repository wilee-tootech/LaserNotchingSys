  // DataTransmitter.cpp: implementation of the CDataTransmitter class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "BeamEditor6.h"
#include "DataTransmitter.h"

#include "InitialTable.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDataTransmitter::CDataTransmitter()
{
	m_pDsp = m_pDsp->GetInstance();
}

CDataTransmitter::~CDataTransmitter()
{
	delete CDsp::GetInstance();
}

// 상속 받은 애들 구현하기
UINT CDataTransmitter::StartManualMarking()
{	
	m_pDsp->StartManualMarking();

	return TRUE;
}

UINT CDataTransmitter::StartAutoMarking()
{	
	m_pDsp->StartAutoMarking();

	return TRUE;
}

void CDataTransmitter::SetSpeed(int iSpeed)
{
	
}

UINT CDataTransmitter::StopAutoMarking()
{
	m_pDsp->StopAutoMarking();
	
	return TRUE;
}

UINT CDataTransmitter::SetParameterData()
{ 

	m_pDsp->SetParameterData();

	return TRUE;
}

UINT CDataTransmitter::DeviceChange()
{

	return TRUE;
}

CString CDataTransmitter::GetVersion()
{
	return m_pDsp->GetVersion();
}

UINT CDataTransmitter::GetMarkStatus()
{
	return m_pDsp->GetMarkStatus();
}

UINT CDataTransmitter::SendVectorDataToDevice(int iObjNumber, double *pVectorData, int iNumberOfVector, int iParameterIndex, int iBinIndex)
{
	m_pDsp->SetVectorObjectData(iObjNumber, pVectorData, iNumberOfVector, iParameterIndex, iBinIndex);

	return FALSE;
}

UINT CDataTransmitter::SendPixelDataToDevice(int iObjNumber, double *pVectorData, int iNumberOfVector, int iParameterIndex, int iBinIndex)
{
	m_pDsp->SetPixelObjectData(iObjNumber, pVectorData, iNumberOfVector, iParameterIndex, iBinIndex);

	return FALSE;
}

UINT CDataTransmitter::SetBinData()
{
	/* 파라미터처럼하는게 편할텐데... */
	m_pDsp->SetBinData();

	return FALSE;
}

void CDataTransmitter::Initialize()
{
	static bool b1Pls = true;
	CInitialTable *pInitialTable = pInitialTable->GetInstance();
	return;

#ifndef _SIMUL_
	if(b1Pls)
	{
		if (pInitialTable->GetKindOfLaser() == 0)	// YAG 1 mode selected
			set_laser_mode(1);
		else if (pInitialTable->GetKindOfLaser() == 1)	// YAG 2 mode selected
			set_laser_mode(2);
		else if (pInitialTable->GetKindOfLaser() == 2)	// YAG 3 mode selected
			set_laser_mode(3);
		else if (pInitialTable->GetKindOfLaser() == 3)	// laser mode 4 selected
			set_laser_mode(4);
		else if (pInitialTable->GetKindOfLaser() == 4)	// YAG 5 mode selected
			set_laser_mode(5);
		else if (pInitialTable->GetKindOfLaser() == 5)	// laser mode 5 selected
			set_laser_mode(6);
		else if (pInitialTable->GetKindOfLaser() == 6)	// CO2 mode selected
			set_laser_mode(0);
		else
			set_laser_mode(1);


#ifdef _RTC6_
		set_laser_control( 0 );//		set_laser_mode(0);      // CO2 mode selected
#endif


		//		set_laser_mode(1);      // YAG 1 mode selected

		disable_laser();

		// half of the standby period in 1/8 microseconds
		// pulse width in 1/8 microseconds
		//		set_standby(100*8, 8);         


		// Timing, delay and speed preset
		set_start_list(1);

		set_firstpulse_killer(0);
		m_pDsp->ListCountPlus();

		// half of the laser signal period
		// pulse widths of signals LASER1 and LASER2
		// time base; 0 corresponds to 1 microsecond.
		// Otherwise, the time base is 1/8 microseconds.
		set_laser_timing(100, 50, 50, 0);    
		m_pDsp->ListCountPlus();

		// jump delay in 10 microseconds
		// mark delay in 10 microseconds
		// polygon delay in 10 microseconds
		set_scanner_delays(25, 10, 5);
		m_pDsp->ListCountPlus();

		// laser on delay in microseconds
		// laser off delay in microseconds
		set_laser_delays(100, 100);
		m_pDsp->ListCountPlus();

		set_jump_speed(1000.0); // jump speed in bits per milliseconds
		m_pDsp->ListCountPlus();

		set_mark_speed(250.0);  // marking speed in bits per milliseconds
		m_pDsp->ListCountPlus();

		set_end_of_list();

		execute_list(1);


		// Draw
		select_cor_table(1,2);

		//set_list_mode(1);

		b1Pls = false;
	}
#endif
}

void CDataTransmitter::SetOffsetData(int iMasterX, int iMasterY, int iSlaveX, int iSlaveY)
{
	//m_pDsp->SetOffsetData(iMasterX, iMasterY, iSlaveX, iSlaveY);
}

void CDataTransmitter::SetChipNumber(int iNumber)
{
	m_pDsp->SetChipNumber(iNumber);
}

/*void CDataTransmitter::SetMasterChipOffset(CList<Vector, Vector> *ltMaster)
{
	m_pDsp->SetMasterChipOffset(ltMaster);
}

void CDataTransmitter::SetSlaveChipOffset(CList<Vector, Vector> *ltSlave)
{
	m_pDsp->SetSlaveChipOffset(ltSlave);
}
*/
void CDataTransmitter::SetMasterChipOffset(Vector *ltMaster, int iNumberOfVector)
{
	m_pDsp->SetMasterChipOffset(ltMaster, iNumberOfVector);
}

void CDataTransmitter::SetSlaveChipOffset(Vector *ltSlave, int iNumberOfVector)
{
	m_pDsp->SetSlaveChipOffset(ltSlave, iNumberOfVector);
}
