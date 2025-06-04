// IO.cpp: implementation of the CIO class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Defines.h"
#include "define.h"
#include "IO.h"
#include "WriteLog.h"
#include "InitialTable.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


CIO* CIO::m_pIO = 0;
CIO* CIO::GetInstance() 
{
	if (m_pIO == 0) {
		m_pIO = new CIO;
	}
	return m_pIO;
}

CIO::CIO()
{

}

CIO::~CIO()
{

}

void CIO::DestroyIO()
{
	delete m_pIO;
}

BOOL CIO::InitDevice()
{
	if(!AxtIsInitialized())						// ���� ���̺귯���� ��� �������� (�ʱ�ȭ�� �Ǿ�����)�� Ȯ���Ѵ�
	{										
		if(!AxtInitialize(NULL, 0))			// ���� ���̺귯���� �ʱ�ȭ �Ѵ�
		{
			m_strErrorMessage.Format("���̺귯�� �ʱ�ȭ ���� �Դϴ�. ���α׷��� �ٽ� ���� ���� �ּ���");
//			m_strErrorMessage.Format("Library initialization is failed. Restart the Program please.");	//in English
			AfxMessageBox(m_strErrorMessage);
			return FALSE;
		}
	}
	
	// ����Ͻô� ���̽����忡 ���߾� Device�� Open�ϸ� �˴ϴ�.
	// BUSTYPE_ISA					:	0
	// BUSTYPE_PCI					:	1
	// BUSTYPE_VME					:	2
	// BUSTYPE_CPCI(Compact PCI)	:	3

	if(!AxtIsInitializedBus(BUSTYPE_PCI))		// ������ ����(PCI)�� �ʱ�ȭ �Ǿ������� Ȯ���Ѵ�
	{
		if(!AxtOpenDeviceAuto(BUSTYPE_PCI))		// ���ο� ���̽����带 �ڵ����� ���ն��̺귯���� �߰��Ѵ�
		{
//			m_strErrorMessage.Format("���� �ʱ�ȭ ���� �Դϴ�. Ȯ�� �� �ٽ� ���� ���� �ּ���");
			m_strErrorMessage.Format("The board initialization is failed. Restart the Program please.");
			AfxMessageBox(m_strErrorMessage);
			return FALSE;
		}
	}

	if(!DIOIsInitialized())			// DIO����� ����� �� �ֵ��� ���̺귯���� �ʱ�ȭ�Ǿ����� Ȯ���Ѵ�
	{
		if(!InitializeDIO())		// DIO����� �ʱ�ȭ�Ѵ�. �����ִ� ��纣�̽����忡�� DIO����� �˻��Ͽ� �ʱ�ȭ�Ѵ�
		{
			m_strErrorMessage.Format("DIO��� �ʱ�ȭ ���� �Դϴ�. Ȯ�� �� �ٽ� ���� ���� �ּ���");
//			m_strErrorMessage.Format("DIO module initialization is failed. Restart the Program please.");	//in English
			AfxMessageBox(m_strErrorMessage);
			return FALSE;
		}
	}
return TRUE;

}

BOOL CIO::OpenDevice()
{
	INT16	nBoardNo, nModulePos;
	UINT16	wModuleID;
	
	
	if(DIOIsInitialized())		//��� ��뿡 �ռ� DIO����� ����� �� �ֵ��� ���̺귯���� �ʱ�ȭ�Ǿ����� Ȯ�� �Ѵ�
	{
		for(int i = 0; i < DIOget_module_count(); i++)		// ���忡 ������ DIO����� ������ �����Ѵ�
		{
			DIOget_module_info(i, &nBoardNo, &nModulePos);	// ������ ����ȣ�� ���̽������ȣ�� �����ġ�� �����Ѵ�
			wModuleID	=	DIOget_module_id(i);			// ������ ����� �𵨹�ȣ�� �����Ѵ�

			/*
				���ϰ�
				97h(AXT_SIO_DI32)	= SIO-DI32
				98h(AXT_SIO_DO32P)	= SIO-DO32P
				99h(AXT_SIO_DB32P)	= SIO-DB32P
				9Eh(AXT_SIO_DO32T)	= SIO-DO32T
				9Fh(AXT_SIO_DB32T)	= SIO-DB32T
				00h	= ��ȿ���� �ʴ� ����ȣ
			*/

			switch(wModuleID)
			{
			case AXT_SIO_DI32:
				m_strModuleData.Format("[ %02d  ��  %02d  ��  SIO-DI32 ]", nBoardNo,i);
				break;
			case AXT_SIO_DO32P:
				m_strModuleData.Format("[ %02d  ��  %02d  ��  SIO-DO32P ]", nBoardNo,i);
				break;
			case AXT_SIO_DO32T:
				m_strModuleData.Format("[ %02d  ��  %02d  ��  SIO-DO32T ]", nBoardNo,i);
				break;
			case AXT_SIO_DB32P:
				m_strModuleData.Format("[ %02d  ��  %02d  ��  SIO-DB32P ]", nBoardNo,i);
				break;
			case AXT_SIO_DB32T:
				m_strModuleData.Format("[ %02d  ��  %02d  ��  SIO-DB32T ]",nBoardNo,i);
				break;
			}
			//m_pModuleID->AddString(m_strModuleData);
		}
//		m_pModuleID->SetCurSel(0);
	}
			
	return TRUE;

}

void CIO::Output(UINT nBit, BOOL nFlag)
{
	short nIndex = nBit;
	if(nBit >= Contact_Point) nIndex-=Contact_Point; 
	
	m_nModuleNo = OUTPUT_MODE;
	BOOL bStatus = nFlag;
	
	
	if(DIOIsInitialized())
	{
		switch(DIOget_module_id(m_nModuleNo))
		{
		case AXT_SIO_DO32P:
		case AXT_SIO_DO32T:
			
			if(nBit < 16)
			{
				//bStatus = !DIOread_outport_bit(m_nModuleNo, nIndex);
				DIOwrite_outport_bit(m_nModuleNo, nIndex, bStatus);
			}
			else
			{
				//bStatus = !DIOread_outport_bit(m_nModuleNo, nIndex+ Contact_Point);
				DIOwrite_outport_bit(m_nModuleNo, nIndex + Contact_Point, bStatus);
			}
			break;
			
		case AXT_SIO_DB32T:
			if(nBit < 16)
				DIOwrite_outport_bit(m_nModuleNo, nIndex, bStatus);
			else
				DIOwrite_outport_bit(m_nModuleNo, nIndex + Contact_Point, bStatus);
			break;
		}
	}
}

BOOL CIO::Input(int nBit)
{
	WORD	wInputGroupA, wInputGroupB;
	BOOL	bFlagGroupA, bFlagGroupB;
	m_nModuleNo = INPUT_MODE;
	BOOL bFlag = FALSE;
	int nIndex ;
	
	switch(DIOget_module_id(m_nModuleNo))
	{															
	case AXT_SIO_DI32:
		//DI Module�� ��� �Է�32������ �����Ǿ� �����Ƿ�, 4����Ʈ�� �Է� �����͸� �о� ���δ�
		wInputGroupA	=	DIOread_inport_word(m_nModuleNo, 0);
		wInputGroupB	=	DIOread_inport_word(m_nModuleNo, 1);
		// DIOread_inport_word(nModuleNo, offset) : �Է�(Input) ��Ʈ�κ��� 2����Ʈ�� �����͸� �о���δ�. ������ ����� ���� ����
		
		/*
		offset ����
		DIOread_inport()		: 0���� �� Module�� �� �Է����� -1 ���� ��� ����
		DIOread_inport_bit()	: SIO-DI32:0..31, SIO-DB32:0..15, SIO-DO32:���Ұ�
		DIOread_inport_byte()	: SIO-DI32:0..3,  SIO-DB32:0..1,  SIO-DO32:���Ұ�
		DIOread_inport_word()	: SIO-DI32:0..1,  SIO-DB32:0,     SIO-DO32:���Ұ�
		DIOread_inport_dword()	: SIO-DI32:0,     SIO-DB32:0,     SIO-DO32:���Ұ�
		���ϰ�
		DIOread_inport()		: 0(OFF), 1(ON)
		DIOread_inport_bit()	: 0(OFF), 1(ON)
		DIOread_inport_byte()	: 00h .. FFh
		DIOread_inport_word()	: 0000h .. FFFFh
		DIOread_inport_dword()	: 00000000h .. FFFFFFFFh
		*/
		
		for (nIndex = 0; nIndex < Contact_Point; nIndex++) 
		{
			bFlagGroupA		=	wInputGroupA & 0x0001;
			bFlagGroupB		=	wInputGroupB & 0x0001;
			
			wInputGroupA	=	wInputGroupA >> 1;
			wInputGroupB	=	wInputGroupB >> 1;
		}
				bFlag = DIOread_inport_bit(m_nModuleNo,nBit);
		break;
	
	case AXT_SIO_DB32T:
		wInputGroupA	=	DIOread_inport_word(m_nModuleNo, 0);
		wInputGroupB	=	DIOread_inport_word(m_nModuleNo, 1);
		for ( nIndex = 0; nIndex < Contact_Point; nIndex++) 
		{
			bFlagGroupA		=	wInputGroupA & 0x0001;
			bFlagGroupB		=	wInputGroupB & 0x0001;
			
			wInputGroupA	=	wInputGroupA >> 1;
			wInputGroupB	=	wInputGroupB >> 1;
		}
				bFlag = DIOread_inport_bit(m_nModuleNo,nBit);
		break;

	}
	return bFlag;
}

BOOL CIO::GetOutputStatus(UINT nBit)
{
	short nIndex = nBit;
	if(nBit >= Contact_Point) nIndex-=Contact_Point; 
	m_nModuleNo = OUTPUT_MODE;
	BOOL bStatus = FALSE;
	
	if(DIOIsInitialized())
	{
		switch(DIOget_module_id(m_nModuleNo))
		{
		case AXT_SIO_DO32P:
		case AXT_SIO_DO32T:
		
			if(nBit < 16){
				bStatus = DIOread_outport_bit(m_nModuleNo, nIndex);
				//DIOwrite_outport_bit(m_nModuleNo, nIndex, bStatus);
			}
			else
			{
				bStatus = DIOread_outport_bit(m_nModuleNo, nIndex+ Contact_Point);
				//DIOwrite_outport_bit(m_nModuleNo, nIndex + Contact_Point, bStatus);
			}
		}
	}
	return bStatus;
}

void CIO::EndOfMark()
{
//	Output(MARK_BUSY, FALSE); 
//	Output(MARK_END, TRUE);
//	CWriteLog *log= NULL;;
	//pMainFrm->AddLogData("MARK_BUSY, Off");
//	Sleep(500);
//	Output(MARK_END, FALSE);
//	//pMainFrm->AddLogData("MARK_END, Off");
}

void CIO::MarkReady()
{
	CWriteLog *log= NULL;;

	//Output(MARK_BUSY, FALSE);
	//pMainFrm->AddLogData("MARK_BUSY, Off");
	//Output(AUTO_MARK_READY ,TRUE);
	
}

void CIO::MarkBusy()
{
	//Output(MARK_BUSY, TRUE); 
	
}

void CIO::MarkStop()
{
	CWriteLog *log= NULL;;
	
	//Output(AUTO_MARK_READY ,FALSE); 
	//pMainFrm->AddLogData("AUTO_MARK_READY, Off");
	//Output(DATA_REV , FALSE);
	//Output(MARK_BUSY, FALSE); 
	
}

void CIO::AzinPortClear()
{
	for(int i = 0; i< 16; i++)
		Output(i, FALSE); 
}

void CIO::DataRev(BOOL m_bRevFlag)
{
	Output(DATA_REV, m_bRevFlag);
}

void CIO::LaserOpenReady(BOOL bFlag)
{
	Output(SIG_O_JOBLOAD_OK, bFlag);
}

void CIO::LaserError(BOOL bFlag)
{
	Output(SIG_O_LASER_ERROR, bFlag);
}

int CIO::GetDeviceNo()
{
	int BIT1 = DIOread_inport_bit(INPUT_MODE, SIG_I_DEVICE_NO_1);
	int BIT2 = DIOread_inport_bit(INPUT_MODE, SIG_I_DEVICE_NO_2);
	int BIT3 = DIOread_inport_bit(INPUT_MODE, SIG_I_DEVICE_NO_3);
	int BIT4 = DIOread_inport_bit(INPUT_MODE, SIG_I_DEVICE_NO_4);
	int BIT5 = DIOread_inport_bit(INPUT_MODE, SIG_I_DEVICE_NO_5);
	BIT1 = 0xFF & (BIT1 << 0);
	BIT2 = 0xFF & (BIT2 << 1);
	BIT3 = 0xFF & (BIT3 << 2);
	BIT4 = 0xFF & (BIT4 << 3);
	BIT5 = 0xFF & (BIT5 << 4);
	int	nDeviceNo = 0x1F & (BIT1 | BIT2 | BIT3 | BIT4 | BIT5);

	return nDeviceNo;
}

void CIO::DeviceChangeOk(BOOL bFlag)
{
	//Output(DEVICE_CHANGE_OK, bFlag);
	CWriteLog *log= NULL;;
	CString str;
	
}
