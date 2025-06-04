          // Module.cpp: implementation of the Module class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "CIO.H"
//#include "bardmarking.h"
#include "BeamEditor6.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
// CIOParent
CIOParent::CIOParent()
{	
	if(!AxtIsInitialized())						// 통합 라이브러리가 사용 가능하지 (초기화가 되었는지)를 확인한다
	{										
		if(!AxtInitialize(NULL, 0))			// 통합 라이브러리를 초기화 한다
		{
			m_strErrorMessage.Format("라이브러리 초기화 실패 입니다. 프로그램을 다시 실행 시켜 주세요");
//			m_strErrorMessage.Format("Library initialization is failed. Restart the Program please.");	//in English
			AfxMessageBox(m_strErrorMessage);
		}
	}
	
	// 사용하시는 베이스보드에 맞추어 Device를 Open하면 됩니다.
	// BUSTYPE_ISA					:	0
	// BUSTYPE_PCI					:	1
	// BUSTYPE_VME					:	2
	// BUSTYPE_CPCI(Compact PCI)	:	3

	if(!AxtIsInitializedBus(BUSTYPE_PCI))		// 지정한 버스(PCI)가 초기화 되었는지를 확인한다
	{
		if(!AxtOpenDeviceAuto(BUSTYPE_PCI))		// 새로운 베이스보드를 자동으로 통합라이브러리에 추가한다
		{
//			m_strErrorMessage.Format("보드 초기화 실패 입니다. 확인 후 다시 실행 시켜 주세요");
			m_strErrorMessage.Format("The board initialization is failed. Restart the Program please.");
			AfxMessageBox(m_strErrorMessage);
		//	return FALSE;
		}
	}

	if(!DIOIsInitialized())			// DIO모듈을 사용할 수 있도록 라이브러리가 초기화되었는지 확인한다
	{
		if(!InitializeDIO())		// DIO모듈을 초기화한다. 열려있는 모든베이스보드에서 DIO모듈을 검색하여 초기화한다
		{
			m_strErrorMessage.Format("DIO모듈 초기화 실패 입니다. 확인 후 다시 실행 시켜 주세요");
//			m_strErrorMessage.Format("DIO module initialization is failed. Restart the Program please.");	//in English
			AfxMessageBox(m_strErrorMessage);
		//	return FALSE;
		}
	}

	//return TRUE;
}

CIOParent::~CIOParent()
{
//	if(m_pIOModuleType) delete [] m_pIOModuleType;

//	for(int i=0; i<m_nIOModuleSu; i++) delete m_ppRepeatAdr[i];
//	delete m_ppRepeatAdr;
}

void CIOParent::Write_Outport_dword(INT16 nModuleMo, UINT16 offset, UINT32 lValue)
{
	DIOwrite_outport_dword(nModuleMo,offset,lValue);
}

void CIOParent::InitIO()
{
    // 입출력 혼합 모듈이 3개 이고 
    // 입력 전용이 1개이다 그러면 초기화는 어떻게 할까???????
    // 입16+출16 ---> 3개
    // 입32      ---> 1개

	for(int i=0; i<m_nIOModuleSu; i++) DIOwrite_outport_dword(i,0,0);

	Sleep(500);
}

void CIOParent::EndIO()
{
	for(int i=0; i<20; i++) DIOwrite_outport_dword(i,0,0);
}

void CIOParent::rSetRepeatMode(BOOL bRepeatMode)
{
	m_bRepeatMode = bRepeatMode;

	if(m_bRepeatMode) return;

	for(int i=0; i<m_nIOModuleSu; i++) memset(m_ppRepeatAdr[i], 0, sizeof(BOOL)*32);
}

void CIOParent::rSetRepeatIO(int nModuleNo, int nBits)
{
	if(!m_bRepeatMode) return;
	m_ppRepeatAdr[nModuleNo][nBits] = !m_ppRepeatAdr[nModuleNo][nBits];
}

BOOL CIOParent::rIsRepeatIO(int nModuleNo, int nBits)
{
	return m_ppRepeatAdr[nModuleNo][nBits];
}

void CIOParent::rRepeatIOOutput()
{
	if(!m_bRepeatMode) return;

	for(int i=0; i<m_nIOModuleSu; i++)
	{
		if(m_pIOModuleType[i] == DI32) continue;

		for(int j=0; j<32; j++)
		{
			if(m_ppRepeatAdr[i][j])
			{
				BOOL bStatus = !DIOread_outport_bit(i, j);
				DIOwrite_outport_bit(i, j, bStatus);
			}
		}
	}
}


/*
#define AXT_SIO_DI32	0x97	// Digital IN  32점
#define AXT_SIO_DO32P	0x98	// Digital OUT 32점
#define AXT_SIO_DB32P	0x99	// Digital IN 16점 / OUT 16점
#define AXT_SIO_DO32T	0x9E	// Digital OUT 16점, Power TR 출력
#define AXT_SIO_DB32T	0x9F	// Digital IN 16점 / OUT 16점, Power TR 출력
*/

BOOL CIOParent::Inp(WORD nAdr)
{
	int nModuleNo = nAdr / 0x100;
	int nBitNo;

	ASSERT (nModuleNo<m_nIOModuleSu);

	if(m_pIOModuleType[nModuleNo]>=AXT_SIO_DB32P) nBitNo = nAdr % 0x10;
	else  nBitNo = nAdr % 0x100;

	BOOL bOn = DIOread_inport_bit(nModuleNo, nBitNo);

	return bOn;
}

BOOL CIOParent::IsOutp(WORD nAdr)
{
	int nModuleNo = nAdr / 0x100;
	int nBitNo;

	ASSERT (nModuleNo<m_nIOModuleSu);

	if(m_pIOModuleType[nModuleNo]>=AXT_SIO_DB32P) nBitNo = nAdr % 0x10;
	else  nBitNo = nAdr % 0x100;

	BOOL bOn = DIOread_outport_bit(nModuleNo, nBitNo);

	return bOn;
}

void CIOParent::Outp(WORD nAdr, BOOL onoff)
{
	// Output
	int nModuleNo = nAdr / 0x100;
	int nBitNo;

	ASSERT (nModuleNo<m_nIOModuleSu);

	if(m_pIOModuleType[nModuleNo]>=AXT_SIO_DB32P) nBitNo = nAdr % 0x10;
	else  nBitNo = nAdr % 0x100;

	DIOwrite_outport_bit(nModuleNo, nBitNo, onoff);
}

