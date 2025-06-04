 // DlgDioTest.cpp : implementation file
//

#include "stdafx.h"
#include "beameditor6.h"
#include "DlgDioTest.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define TM_SENSOR_ID		100
#define TM_SENSOR_INTERVAL	50
#define CONTACT_POINT		16


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About


CDlgDioTest::CDlgDioTest(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgDioTest::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgDioTest)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	//m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDlgDioTest::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgDioTest)
	DDX_Control(pDX, IDC_LIST_DIO, m_List);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDlgDioTest, CDialog)
	//{{AFX_MSG_MAP(CDlgDioTest)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_CHECK_INTERRUPT, OnCheckInterrupt)
	ON_BN_CLICKED(IDC_CHECK_RISING, OnCheckRising)
	ON_BN_CLICKED(IDC_CHECK_FALLING, OnCheckFalling)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, OnButtonClear)
	ON_BN_CLICKED(IDC_BUTTON_EXIT, OnButtonExit)
	ON_CBN_EDITCHANGE(IDC_MODULEID, OnEditchangeModuleid)
	ON_BN_CLICKED(1002, On1002)
	//}}AFX_MSG_MAP
	ON_COMMAND_RANGE(IDC_CHECK_A_00, IDC_CHECK_A_15, OnClickAGroup)
	ON_COMMAND_RANGE(IDC_CHECK_B_00, IDC_CHECK_B_15, OnClickBGroup)
	ON_MESSAGE(WM_DIO_INTERRUPT, OnInterruptMessage)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgDioTest message handlers

BOOL CDlgDioTest::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.
	
	// IDM_ABOUTBOX must be in the system command range.


	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	m_pModuleID			=	(CComboBox*)GetDlgItem(IDC_MODULEID);
	m_pCheckBtn[0]		=	(CStatic*)GetDlgItem(IDC_STATIC_A);
	m_pCheckBtn[1]		=	(CStatic*)GetDlgItem(IDC_STATIC_B);
	m_pInterruptOn		=	(CButton*)GetDlgItem(IDC_CHECK_INTERRUPT);
	m_pchkRising		=	(CButton*)GetDlgItem(IDC_CHECK_RISING);
	m_pchkFalling		=	(CButton*)GetDlgItem(IDC_CHECK_FALLING);

	for (int i = 0; i < CONTACT_POINT; i++) 
	{
		m_pchkHigh[i]	=	(CButton*)GetDlgItem(IDC_CHECK_A_00+i);
		m_pchkLow[i]	=	(CButton*)GetDlgItem(IDC_CHECK_B_00+i);
	}

	Initialize_DIOtest();		// DIO����� ����� ���� �ʱ�ȭ �ڵ�...
	OpenDevice();

	SetTimer(TM_SENSOR_ID, TM_SENSOR_INTERVAL, NULL);
		
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDlgDioTest::OnSysCommand(UINT nID, LPARAM lParam)
{

}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CDlgDioTest::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CDlgDioTest::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

// �ʱ�ȭ ����...
BOOL CDlgDioTest::Initialize_DIOtest()			//Initialize �������� Library, Board, Module�� �ʱ�ȭ�� Ȯ���Ѵ�
{
	if(!AxtIsInitialized())						// ���� ���̺귯���� ��� �������� (�ʱ�ȭ�� �Ǿ�����)�� Ȯ���Ѵ�
	{										
		if(!AxtInitialize(m_hWnd, NULL))		// ���� ���̺귯���� �ʱ�ȭ �Ѵ�
		{
			AfxMessageBox("Library Init Fail!!");
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
			AfxMessageBox("Base Board Init Fail!!");
			return FALSE;
		}
	}

	if(!DIOIsInitialized())			// DIO����� ����� �� �ֵ��� ���̺귯���� �ʱ�ȭ�Ǿ����� Ȯ���Ѵ�
	{
		if(!InitializeDIO())		// DIO����� �ʱ�ȭ�Ѵ�. �����ִ� ��纣�̽����忡�� DIO����� �˻��Ͽ� �ʱ�ȭ�Ѵ�
		{
			AfxMessageBox("DIO Module Init Fail!!");
			return FALSE;
		}
	}

	return TRUE;
}


BOOL CDlgDioTest::OpenDevice()
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
			m_pModuleID->AddString(m_strModuleData);
		}
		m_pModuleID->SetCurSel(0);
	}
			
	return TRUE;
}

void CDlgDioTest::OnTimer(UINT nIDEvent)
{
	int		nIndex;
	WORD	wInputGroupA, wInputGroupB;
	BOOL	bFlagGroupA, bFlagGroupB;

	OnEditchangeModuleid();

	switch(nIDEvent)
	{
	case TM_SENSOR_ID:		
		switch(DIOget_module_id(m_pModuleID->GetCurSel()))
		{															
		case AXT_SIO_DI32:
			//DI Module�� ��� �Է�32������ �����Ǿ� �����Ƿ�, 4����Ʈ�� �Է� �����͸� �о� ���δ�
			wInputGroupA	=	DIOread_inport_word(m_pModuleID->GetCurSel(), 0);
			wInputGroupB	=	DIOread_inport_word(m_pModuleID->GetCurSel(), 1);
			/* DIOread_inport_word(nModuleNo, offset) : �Է�(Input) ��Ʈ�κ��� 2����Ʈ�� �����͸� �о���δ�. 
			                                            ������ ����� ���� ����  
			
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

			for (nIndex = 0; nIndex < CONTACT_POINT; nIndex++) 
			{
				bFlagGroupA		=	wInputGroupA & 0x0001;
				bFlagGroupB		=	wInputGroupB & 0x0001;

				wInputGroupA	=	wInputGroupA >> 1;
				wInputGroupB	=	wInputGroupB >> 1;

				m_pchkHigh[nIndex]->SetCheck(bFlagGroupA);
				m_pchkLow[nIndex]->SetCheck(bFlagGroupB);
			}
			break;

		case AXT_SIO_DB32P:
		case AXT_SIO_DB32T:

			wInputGroupB	=	DIOread_inport_word(m_pModuleID->GetCurSel(), 0);

			for(nIndex = 0; nIndex < CONTACT_POINT; nIndex++)
			{
				bFlagGroupB	=	wInputGroupB & 0x0001;
				wInputGroupB	=	wInputGroupB >> 1;
				m_pchkLow[nIndex]->SetCheck(bFlagGroupB);
			}
			break;
		}
		break;
	}
	
	CDialog::OnTimer(nIDEvent);
}

void CDlgDioTest::OnCheckInterrupt()
{
	if(DIOIsInitialized())
	{
		INT16	nBoardNo, nModulePos;

		m_strSucessMessage.Format("Enable Interrupt ��ư�� 'Ȱ��ȭ' �Ͽ����ϴ�.��Edge ������ ���ּ���");
		m_strFailMessage.Format("Enable Interrupt ��ư�� '��Ȱ��ȭ' �Ͽ����ϴ�.");
		m_strErrorMessage.Format("Enable Interrupt ��ư�� ����� �� �����ϴ�.");
//		m_strSucessMessage.Format("Enable Interrupt Button is activated.��Check the Edge setting, please");	//in English
//		m_strFailMessage.Format("Enable Interrupt Button is inactivated.");	//in English
//		m_strErrorMessage.Format("Cannot use the Enable Interrupt Button.");	//in English
		
		DIOget_module_info(m_pModuleID->GetCurSel(), &nBoardNo, &nModulePos);
		switch(DIOget_module_id(m_pModuleID->GetCurSel()))
		{
		case AXT_SIO_DI32:
		case AXT_SIO_DB32P:
		case AXT_SIO_DB32T:
			if(m_pInterruptOn->GetCheck())
			{
				m_List.AddString(m_strSucessMessage);
				AxtEnableInterrupt(nBoardNo);
				// ���̽������� ���ͷ�Ʈ�� ����� �㰡�Ѵ�
				AxtWriteInterruptMaskModule(nBoardNo, 0x8F);
				// ���̽����忡 ������ �� ����� ���ͷ�Ʈ�� ����� �� �ֵ��� �ش� ���� ����� ����Ѵ�
				DIOEnableInterrupt(m_pModuleID->GetCurSel());
				// ������ ����� ���ͷ�Ʈ�� ����Ѵ�.
			}
			else
			{
				m_List.AddString(m_strFailMessage);
				AxtDisableInterrupt(nBoardNo);
				AxtWriteInterruptMaskModule(nBoardNo, 0x00);
				DIODisableInterrupt(m_pModuleID->GetCurSel());
			}
			break;

		case AXT_SIO_DO32P:
		case AXT_SIO_DO32T:
			m_pInterruptOn->SetCheck(0);
			m_List.AddString(m_strErrorMessage);
			break;
		}
		m_List.SetCurSel(m_List.GetCount()-1);
	}	
	
}

void CDlgDioTest::OnCheckRising()
{
	m_strSucessMessage.Format("Rising Edge ������ '����' �մϴ�.");
	m_strFailMessage.Format("Rising Edge ������ '����' �մϴ�.");
	m_strErrorMessage.Format("Rising Edge ������ ����� �� �����ϴ�.");
	m_strErrorMessage_Edge.Format("���� Interrupt Button�� Enable ���� �ֽñ� �ٶ��ϴ�");

//	m_strSucessMessage.Format("Start the Rising Edge detection.");	//in English
//	m_strFailMessage.Format("Rising Edge detection is over.");	//in English
//	m_strErrorMessage.Format("Cannot use the Rising Edge detection.");	//in English
//	m_strErrorMessage_Edge.Format("Check the Interrupt Button is Enabled, please.");	//in English
	
	if(DIOIsInitialized())
	{
		switch(DIOget_module_id(m_pModuleID->GetCurSel()))
		{
		case AXT_SIO_DI32:
			if(m_pchkRising->GetCheck())
			{
				if(m_pInterruptOn->GetCheck())
				{
					m_List.AddString(m_strSucessMessage);
					DIOwrite_upedge_word(m_pModuleID->GetCurSel(), 0, 0xFFFF);
					DIOwrite_upedge_word(m_pModuleID->GetCurSel(), 1, 0xFFFF);
					// ��¿���(Upedge) ��Ʈ�ο� 2����Ʈ�� �����͸� ��ִ´�. ������ ����� ���� ����
				}
				else
				{
					m_pchkRising->SetCheck(0);
					AfxMessageBox(m_strErrorMessage_Edge);
				}
			}
			else
			{
				m_List.AddString(m_strFailMessage);
				DIOwrite_upedge_word(m_pModuleID->GetCurSel(), 0, 0x0000);
				DIOwrite_upedge_word(m_pModuleID->GetCurSel(), 1, 0x0000);
			}
			break;
		case AXT_SIO_DB32P:
		case AXT_SIO_DB32T:
			if(m_pchkRising->GetCheck())
			{
				if(m_pInterruptOn->GetCheck())
				{
					m_List.AddString(m_strSucessMessage);
					DIOwrite_upedge_word(m_pModuleID->GetCurSel(), 0, 0xFFFF);
				}
				else
				{
					m_pchkRising->SetCheck(0);
					AfxMessageBox(m_strErrorMessage_Edge);
				}
				
			}
			else
			{
				m_List.AddString(m_strFailMessage);
				DIOwrite_upedge_word(m_pModuleID->GetCurSel(), 0, 0x0000);
			}
			break;
		case AXT_SIO_DO32P:
		case AXT_SIO_DO32T:
			m_pchkRising->SetCheck(0);
			m_List.AddString(m_strErrorMessage);
			break;
		}
		m_List.SetCurSel(m_List.GetCount()-1);
	}	
}

void CDlgDioTest::OnCheckFalling()
{
	m_strSucessMessage.Format("Falling Edge ������ '����' �մϴ�.");
	m_strFailMessage.Format("Falling Edge ������ '����' �մϴ�.");
	m_strErrorMessage.Format("Falling Edge ������ ����� �� �����ϴ�.");
	m_strErrorMessage_Edge.Format("���� Interrupt Button�� Enable ���� �ֽñ� �ٶ��ϴ�");

//	m_strSucessMessage.Format("Start the Falling Edge detection.");	//in English
//	m_strFailMessage.Format("Falling Edge detection is over.");	//in English
//	m_strErrorMessage.Format("Cannot use the Falling Edge detection.");	//in English
//	m_strErrorMessage_Edge.Format("Check the Interrupt Button is Enabled, please.");	//in English
	
	if(DIOIsInitialized())
	{
		switch(DIOget_module_id(m_pModuleID->GetCurSel()))
		{
		case AXT_SIO_DI32:
			if(m_pchkFalling->GetCheck())
			{
				if(m_pInterruptOn->GetCheck())
				{
					m_List.AddString(m_strSucessMessage);
					DIOwrite_downedge_word(m_pModuleID->GetCurSel(), 0, 0xFFFF);
					DIOwrite_downedge_word(m_pModuleID->GetCurSel(), 1, 0xFFFF);
					// �ϰ�����(Downedge) ��Ʈ�ο� 2����Ʈ�� �����͸� ��ִ´�. ������ ����� ���� ����
				}
				else
				{
					m_pchkFalling->SetCheck(0);
					AfxMessageBox(m_strErrorMessage_Edge);
				}
			}
			else
			{
				m_List.AddString(m_strFailMessage);
				DIOwrite_downedge_word(m_pModuleID->GetCurSel(), 0, 0x0000);
				DIOwrite_downedge_word(m_pModuleID->GetCurSel(), 1, 0x0000);
			}
			break;
		case AXT_SIO_DB32P:
		case AXT_SIO_DB32T:
			if(m_pchkFalling->GetCheck())
			{
				if(m_pInterruptOn->GetCheck())
				{
					m_List.AddString(m_strSucessMessage);
					DIOwrite_downedge_word(m_pModuleID->GetCurSel(), 0, 0xFFFF);
				}
				else
				{
					m_pchkFalling->SetCheck(0);
					AfxMessageBox(m_strErrorMessage_Edge);
				}
			}
			else
			{
				m_List.AddString(m_strFailMessage);
				DIOwrite_downedge_word(m_pModuleID->GetCurSel(), 0, 0x0000);
			}
			break;
		case AXT_SIO_DO32P:
		case AXT_SIO_DO32T:
			m_pchkFalling->SetCheck(0);
			m_List.AddString(m_strErrorMessage);
			break;
		}
		m_List.SetCurSel(m_List.GetCount()-1);
	}
}

void CDlgDioTest::OnClickAGroup(UINT nID)
{
	short	nIndex;
	BOOL	bFlag;
    int i = m_pModuleID->GetCurSel();
	if(DIOIsInitialized())
	{
		switch(DIOget_module_id(m_pModuleID->GetCurSel()))
		{
		case AXT_SIO_DO32P:
		case AXT_SIO_DO32T:
		case AXT_SIO_DB32P:
		case AXT_SIO_DB32T:

			nIndex	=	nID - IDC_CHECK_A_00;
			bFlag	=	m_pchkHigh[nIndex]->GetCheck();
			DIOwrite_outport_bit(m_pModuleID->GetCurSel(), nIndex, bFlag);
			// ���(Output) ��Ʈ�ο� 1��Ʈ�� �����͸� ��ִ´�. ������ ����� ���� ����
			break;
		}
	}
}

void CDlgDioTest::OnClickBGroup(UINT nID)
{
	short	nIndex;
	BOOL	bFlag;

	if(DIOIsInitialized())
	{
		switch(DIOget_module_id(m_pModuleID->GetCurSel()))
		{
		case AXT_SIO_DO32P:
		case AXT_SIO_DO32T:
			nIndex	=	nID-IDC_CHECK_B_00;
			bFlag	=	m_pchkLow[nIndex]->GetCheck();
			DIOwrite_outport_bit(m_pModuleID->GetCurSel(), nIndex + CONTACT_POINT, bFlag);
			// ���(Output) ��Ʈ�ο� 1��Ʈ�� �����͸� ��ִ´�. ������ ����� ���� ����
			break;
		}
	}
}	

LRESULT CDlgDioTest::OnInterruptMessage(WPARAM wParam, LPARAM lParam)
{
	int nBoard = HIBYTE(wParam);			// Interrupt �߻� ���� ��ȣ.
	int nModulePos = LOBYTE(wParam);		// Interrupt �߻� ��� ��ȣ.
	int nIntrFlag = (int)lParam;			// Interrupt �߻�.
	int nModule;							// Interrupt �߻� ��� ��ȣ.
        
    nModule = DIOget_module_number(nBoard, nModulePos);

	for(int nIndex = 0; nIndex < (CONTACT_POINT * 2); nIndex++)
	{
		if((nIntrFlag >> nIndex) & 0x01)	
		{
			int nBitState = DIOread_inport_bit(nModule, nIndex);

	 		if(nBitState)
				m_strEdgeStates = "��Rising";
			else
				m_strEdgeStates = "��Falling";	
	
			m_strMessage.Format(m_strEdgeStates);
			
			m_List.AddString(m_strMessage);
			m_List.SetCurSel(m_List.GetCount()-1);
		}
	}
	return 0;
}


void CDlgDioTest::OnButtonClear()
{
	m_List.ResetContent();
}

void CDlgDioTest::OnEditchangeModuleid()
{
	short	nIndex;
	WORD	wOutputHigh, wOutputLow;
	BOOL	bFlagHigh, bFlagLow;

	if(DIOIsInitialized())
	{
		switch(DIOget_module_id(m_pModuleID->GetCurSel()))
		{
		case AXT_SIO_DI32:
			m_pCheckBtn[0]->SetWindowText("Input1");				// DI Module�� �Է� 32������ �����Ǿ����Ƿ� Group A, B��
			m_pCheckBtn[1]->SetWindowText("Input2");				// ��� Input���� ���� �Ѵ�

			if(DIOIsInterruptEnabled(m_pModuleID->GetCurSel()))		// ������ ����� ���ͷ�Ʈ ������������ Ȯ���Ѵ�.
				m_pInterruptOn->SetCheck(1);
			else
				m_pInterruptOn->SetCheck(0);

			if(DIOread_upedge_word(m_pModuleID->GetCurSel(), 0)==0xFFFF &&		// ������ ����� UpEdge ���������� Ȯ���Ѵ�.
				DIOread_upedge_word(m_pModuleID->GetCurSel(), 1)==0xFFFF)
				m_pchkRising->SetCheck(1);
			else
				m_pchkRising->SetCheck(0);

			if(DIOread_downedge_word(m_pModuleID->GetCurSel(), 0)==0xFFFF &&	// ������ ����� DownEdge ���������� Ȯ���Ѵ�.
				DIOread_downedge_word(m_pModuleID->GetCurSel(), 1)==0xFFFF)
				m_pchkFalling->SetCheck(1);
			else
				m_pchkFalling->SetCheck(0);
			break;
		case AXT_SIO_DO32P:
		case AXT_SIO_DO32T:
			m_pCheckBtn[0]->SetWindowText("Output1");		// DO Module�� ��� 32������ �����Ǿ����Ƿ� Geroup A, B��
			m_pCheckBtn[1]->SetWindowText("Output2");		// ��� Output���� ���� �Ѵ�

			m_pInterruptOn->SetCheck(0);
			m_pchkRising->SetCheck(0);
			m_pchkFalling->SetCheck(0);

			wOutputHigh	=	DIOread_outport_word(m_pModuleID->GetCurSel(), 0);
			wOutputLow	=	DIOread_outport_word(m_pModuleID->GetCurSel(), 1);

			for(nIndex = 0; nIndex < CONTACT_POINT; nIndex++)
			{
				bFlagHigh	=	wOutputHigh & 0x0001;
				bFlagLow	=	wOutputLow & 0x0001;

				wOutputHigh	=	wOutputHigh >> 1;
				wOutputLow	=	wOutputLow >> 1;

				m_pchkHigh[nIndex]->SetCheck(bFlagHigh);
				m_pchkLow[nIndex]->SetCheck(bFlagLow);
			}
			break;
		case AXT_SIO_DB32P:
		case AXT_SIO_DB32T:
			m_pCheckBtn[0]->SetWindowText("Output1");		// DB Module�� ������� ���� 16���� �����Ǿ� �����Ƿ�
			m_pCheckBtn[1]->SetWindowText("Input1");		// Group A�� Output���� Group B�� Input���� �����Ѵ�

			if(DIOIsInterruptEnabled(m_pModuleID->GetCurSel()))
				m_pInterruptOn->SetCheck(1);
			else
				m_pInterruptOn->SetCheck(0);
			
			if(DIOread_upedge_word(m_pModuleID->GetCurSel(), 0) == 0xFFFF)
				m_pchkRising->SetCheck(1);
			else
				m_pchkRising->SetCheck(0);
			
			if(DIOread_downedge_word(m_pModuleID->GetCurSel(), 0) == 0xFFFF)
				m_pchkFalling->SetCheck(1);
			else
				m_pchkFalling->SetCheck(0);

			wOutputHigh	=	DIOread_outport_word(m_pModuleID->GetCurSel(),0);
			
			for(nIndex = 0; nIndex < CONTACT_POINT; nIndex++)
			{
				bFlagHigh	=	wOutputHigh & 0x0001;
				wOutputHigh	=	wOutputHigh >> 1;

				m_pchkHigh[nIndex]->SetCheck(bFlagHigh);
			}
			break;
		}
	}	
}

BOOL CDlgDioTest::PreTranslateMessage(MSG* pMsg)		//escŰ�� ���� ���� ����..
{
	if ( pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN ) return true;
	if ( pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE ) return true;

	return CDialog::PreTranslateMessage(pMsg);
}

void CDlgDioTest::OnButtonExit() 
{
	//if (AfxMessageBox("�����Ͻðڽ��ϱ�?", MB_YESNO) == IDYES)
	//{
	//	CDlgDioTest *pDlg = (CDlgDioTest *)AfxGetMainWnd();
		CloseDevice();									// ��� ��ġ�� �ݾ��ش�
	//	pDlg->OnCancel();
	//}
		SendMessage(WM_CLOSE, NULL);
}

BOOL CDlgDioTest::CloseDevice()							//��ġ ����
{
	if (AxtIsInitialized())
	{
		AxtCloseDeviceAll();				// �߰��� ���̽����带 ���� �ݴ´�
		AxtClose();							// ���� ���̺귯���� ����� �����Ѵ�.

		return TRUE;
	}
	else
		return FALSE;
}

void CDlgDioTest::OnDestroy() 
{
	CDialog::OnDestroy();
	
	CloseDevice();
	KillTimer(TM_SENSOR_ID);
}

void CDlgDioTest::On1002() 
{
	// TODO: Add your control notification handler code here
	
}
