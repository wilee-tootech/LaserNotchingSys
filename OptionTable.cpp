// OptionTable.cpp: implementation of the COptionTable class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "beameditor6.h"
#include "OptionTable.h"
#include "InitialTable.h"
#include "MKFileReader.h"
#include "MKFileWriter.h"
#include "FieldParameter.h"
#include "TransUnit.h"
#include "PointerManager.h"
#include "Device.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

COptionTable::COptionTable()
{
	m_bFontFileSave = FALSE;         // 기본 값
}

COptionTable::~COptionTable()
{

}

COptionTable &COptionTable::Instance()
{
	static COptionTable OptionTable;
	return OptionTable;
}

void COptionTable::SetFontFileSave(BOOL bFlag)
{
	m_bFontFileSave = bFlag;
}

BOOL COptionTable::GetFontFileSave()
{
	return m_bFontFileSave;
}


char *COptionTable::Serialize(DWORD &dwLength)
{
	//CInitialTable *pInitialTable = pInitialTable->GetInstance();
	CPointerManager *pPointerManager = pPointerManager->GetInstance();
	CFieldParameter *pFieldParameter = pFieldParameter->GetInstance();
	
	m_dBaseMasterX = pFieldParameter->GetMasterX(); 
	m_dBaseMasterY = pFieldParameter->GetMasterY(); 
	m_dBaseSlaveX = pFieldParameter->GetSlaveX(); 
	m_dBaseSlaveY = pFieldParameter->GetSlaveY(); 
	m_dSetedPower = pFieldParameter->GetSetedPowerValue(); 
	pFieldParameter->GetSize(&m_dMMSize,&m_dFieldSize) ;

	int m_iUnit = pFieldParameter->GetUnit();
	m_iUnit = 1;
	m_dSetedPower =0;m_dMeasuredPower=0;

	CString strUnit;
	switch (m_iUnit) {
	case 0:
		strUnit = "MM";
		break;
	case 1:
		strUnit = "FIELD";
		break;
	case 2:
		strUnit = "POINT";
		break;
	case 3:
		strUnit = "MIL";
		break;
	}
	

	
	CMKFileWriter MKFW;
	MKFW.Add(ID_UNIT, strUnit.GetLength() +1 , (LPCTSTR)strUnit);
	MKFW.Add(ID_MAX_FIELD, sizeof(double), &m_dFieldSize);
	MKFW.Add(ID_MAX_MM, sizeof(double), &m_dMMSize);

	m_bFontFileSave=0; // 사용안함
	MKFW.Add(ID_FONT_FILE_SAVE, sizeof(BOOL), &m_bFontFileSave);
	
	MKFW.Add(ID_MASTER_X_OFFSET, sizeof(double), &m_dBaseMasterX);
	MKFW.Add(ID_MASTER_Y_OFFSET, sizeof(double), &m_dBaseMasterY);
	MKFW.Add(ID_SLAVE_X_OFFSET, sizeof(double), &m_dBaseSlaveX);
	MKFW.Add(ID_SLAVE_Y_OFFSET, sizeof(double), &m_dBaseSlaveY);
	
	MKFW.Add(ID_SET_POWER, sizeof(double), &m_dSetedPower);

	
	return MKFW.GetTotalData(dwLength);
}

void COptionTable::Unserialize(char *pstrSerial)
{
	DWORD dwLength, dwGetID;
	char *pstrTemp;
	int m_iUnit;
	CPointerManager *pPointerManager = pPointerManager->GetInstance();
	CFieldParameter *pFieldParameter = pFieldParameter->GetInstance();
	CTransUnit	*pTransUnit = pTransUnit->GetInstance();
	CMKFileReader MKFR;
	
	pstrTemp = MKFR.GetAt(pstrSerial, ID_UNIT, dwLength, dwGetID);
	if(pstrTemp != NULL)
	{
	
	if (strcmp(pstrTemp, "MM") == 0)
		m_iUnit = 0;
	else if (strcmp(pstrTemp, "FIELD") == 0)
		m_iUnit = 1;
	else if (strcmp(pstrTemp, "POINT") == 0)
		m_iUnit = 2;
	else if (strcmp(pstrTemp, "MIL") == 0)
		m_iUnit = 3;
	else
		m_iUnit = 0;
	delete [] pstrTemp;  //받은 블록 삭제!~
	//pFieldParameter->SetUnit(m_iUnit) ;
	m_dSetedPower=0;
	MKFR.GetAt(pstrSerial, ID_MAX_FIELD, &m_dFieldSize);
	MKFR.GetAt(pstrSerial, ID_MAX_MM, &m_dMMSize);
	MKFR.GetAt(pstrSerial,ID_FONT_FILE_SAVE,&m_bFontFileSave);

	double m_dMasterX,m_dMasterY,m_dSlaveX,m_dSlaveY;
	MKFR.GetAt(pstrSerial, ID_MASTER_X_OFFSET, &m_dMasterX);
	MKFR.GetAt(pstrSerial, ID_MASTER_Y_OFFSET, &m_dMasterY);
	MKFR.GetAt(pstrSerial, ID_SLAVE_X_OFFSET, &m_dSlaveX);
	MKFR.GetAt(pstrSerial, ID_SLAVE_Y_OFFSET, &m_dSlaveY);
	
	
	MKFR.GetAt(pstrSerial, ID_SET_POWER, &m_dSetedPower); 
	
	//pPointerManager->GetLaserControl()->SetSetPower(m_dSetedPower);
	
	
	m_iUnit=FIELD;//pFieldParameter->GetUnit() ;
	//pTransUnit->SetMaxValue(m_dFieldSize, m_dMMSize);
	//pFieldParameter->SetSize(m_dMMSize, m_dFieldSize);


	pTransUnit->SetValue(m_dMasterX, m_iUnit);
	m_dMasterX = pTransUnit->GetField();
	pFieldParameter->SetMasterX(m_dBaseMasterX) ;

	pTransUnit->SetValue(m_dMasterY, m_iUnit);
	m_dMasterY = pTransUnit->GetField();
	pFieldParameter->SetMasterY(m_dMasterY) ;

	pTransUnit->SetValue(m_dSlaveX, m_iUnit);
	m_dSlaveX = pTransUnit->GetField();
	pFieldParameter->SetSlaveX(m_dSlaveX) ;
	
	pTransUnit->SetValue(m_dSlaveY, m_iUnit);
	m_dSlaveY = pTransUnit->GetField();
	pFieldParameter->SetSlaveY(m_dSlaveY) ;


	CDeviceManager *pDeviceManager = pDeviceManager->Instance();
	CDeviceData *deviceData = pDeviceManager->GetDeviceData();

	deviceData->SetSlaveOffset(m_dSlaveX, m_dSlaveY);
	deviceData->SetMasterOffset(m_dMasterX, m_dMasterY); 
	

	
	}
	else
	{
	MKFR.GetAt(pstrSerial,ID_FONT_FILE_SAVE,&m_bFontFileSave);
	}



	
	return;
}


