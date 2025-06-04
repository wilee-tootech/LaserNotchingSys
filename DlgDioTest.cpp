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

	Initialize_DIOtest();		// DIO모듈의 사용을 위한 초기화 코드...
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

// 초기화 구문...
BOOL CDlgDioTest::Initialize_DIOtest()			//Initialize 구문으로 Library, Board, Module의 초기화를 확인한다
{
	if(!AxtIsInitialized())						// 통합 라이브러리가 사용 가능하지 (초기화가 되었는지)를 확인한다
	{										
		if(!AxtInitialize(m_hWnd, NULL))		// 통합 라이브러리를 초기화 한다
		{
			AfxMessageBox("Library Init Fail!!");
			return FALSE;
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
			AfxMessageBox("Base Board Init Fail!!");
			return FALSE;
		}
	}

	if(!DIOIsInitialized())			// DIO모듈을 사용할 수 있도록 라이브러리가 초기화되었는지 확인한다
	{
		if(!InitializeDIO())		// DIO모듈을 초기화한다. 열려있는 모든베이스보드에서 DIO모듈을 검색하여 초기화한다
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
	
	
	if(DIOIsInitialized())		//모든 사용에 앞서 DIO모듈을 사용할 수 있도록 라이브러리가 초기화되었는지 확인 한다
	{
		for(int i = 0; i < DIOget_module_count(); i++)		// 보드에 장착된 DIO모듈의 갯수를 리턴한다
		{
			DIOget_module_info(i, &nBoardNo, &nModulePos);	// 지정한 모듈번호의 베이스보드번호와 모듈위치를 리턴한다
			wModuleID	=	DIOget_module_id(i);			// 지정한 모듈의 모델번호를 리턴한다

			/*
				리턴값
				97h(AXT_SIO_DI32)	= SIO-DI32
				98h(AXT_SIO_DO32P)	= SIO-DO32P
				99h(AXT_SIO_DB32P)	= SIO-DB32P
				9Eh(AXT_SIO_DO32T)	= SIO-DO32T
				9Fh(AXT_SIO_DB32T)	= SIO-DB32T
				00h	= 유효하지 않는 모듈번호
			*/

			switch(wModuleID)
			{
			case AXT_SIO_DI32:
				m_strModuleData.Format("[ %02d  ◈  %02d  ◈  SIO-DI32 ]", nBoardNo,i);
				break;
			case AXT_SIO_DO32P:
				m_strModuleData.Format("[ %02d  ◈  %02d  ◈  SIO-DO32P ]", nBoardNo,i);
				break;
			case AXT_SIO_DO32T:
				m_strModuleData.Format("[ %02d  ◈  %02d  ◈  SIO-DO32T ]", nBoardNo,i);
				break;
			case AXT_SIO_DB32P:
				m_strModuleData.Format("[ %02d  ◈  %02d  ◈  SIO-DB32P ]", nBoardNo,i);
				break;
			case AXT_SIO_DB32T:
				m_strModuleData.Format("[ %02d  ◈  %02d  ◈  SIO-DB32T ]",nBoardNo,i);
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
			//DI Module의 경우 입력32점으로 구성되어 있으므로, 4바이트의 입력 데이터를 읽어 들인다
			wInputGroupA	=	DIOread_inport_word(m_pModuleID->GetCurSel(), 0);
			wInputGroupB	=	DIOread_inport_word(m_pModuleID->GetCurSel(), 1);
			/* DIOread_inport_word(nModuleNo, offset) : 입력(Input) 포트로부터 2바이트의 데이터를 읽어들인다. 
			                                            지정한 모듈의 워드 단위  
			
			/*
			offset 설정
				DIOread_inport()		: 0부터 각 Module의 총 입력점수 -1 까지 사용 가능
				DIOread_inport_bit()	: SIO-DI32:0..31, SIO-DB32:0..15, SIO-DO32:사용불가
				DIOread_inport_byte()	: SIO-DI32:0..3,  SIO-DB32:0..1,  SIO-DO32:사용불가
				DIOread_inport_word()	: SIO-DI32:0..1,  SIO-DB32:0,     SIO-DO32:사용불가
				DIOread_inport_dword()	: SIO-DI32:0,     SIO-DB32:0,     SIO-DO32:사용불가
			리턴값
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

		m_strSucessMessage.Format("Enable Interrupt 버튼을 '활성화' 하였습니다.※Edge 설정을 해주세요");
		m_strFailMessage.Format("Enable Interrupt 버튼을 '비활성화' 하였습니다.");
		m_strErrorMessage.Format("Enable Interrupt 버튼을 사용할 수 없습니다.");
//		m_strSucessMessage.Format("Enable Interrupt Button is activated.※Check the Edge setting, please");	//in English
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
				// 베이스보드의 인터럽트의 사용을 허가한다
				AxtWriteInterruptMaskModule(nBoardNo, 0x8F);
				// 베이스보드에 장착된 각 모듈의 인터럽트를 사용할 수 있도록 해당 핀의 사용을 허용한다
				DIOEnableInterrupt(m_pModuleID->GetCurSel());
				// 지정한 모듈의 인터럽트를 허용한다.
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
	m_strSucessMessage.Format("Rising Edge 검출을 '시작' 합니다.");
	m_strFailMessage.Format("Rising Edge 검출을 '종료' 합니다.");
	m_strErrorMessage.Format("Rising Edge 검출을 사용할 수 없습니다.");
	m_strErrorMessage_Edge.Format("먼저 Interrupt Button을 Enable 시켜 주시기 바랍니다");

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
					// 상승에지(Upedge) 포트로에 2바이트의 데이터를 써넣는다. 지정한 모듈의 워드 단위
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
	m_strSucessMessage.Format("Falling Edge 검출을 '시작' 합니다.");
	m_strFailMessage.Format("Falling Edge 검출을 '종료' 합니다.");
	m_strErrorMessage.Format("Falling Edge 검출을 사용할 수 없습니다.");
	m_strErrorMessage_Edge.Format("먼저 Interrupt Button을 Enable 시켜 주시기 바랍니다");

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
					// 하강에지(Downedge) 포트로에 2바이트의 데이터를 써넣는다. 지정한 모듈의 워드 단위
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
			// 출력(Output) 포트로에 1비트의 데이터를 써넣는다. 지정한 모듈의 점수 단위
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
			// 출력(Output) 포트로에 1비트의 데이터를 써넣는다. 지정한 모듈의 점수 단위
			break;
		}
	}
}	

LRESULT CDlgDioTest::OnInterruptMessage(WPARAM wParam, LPARAM lParam)
{
	int nBoard = HIBYTE(wParam);			// Interrupt 발생 보드 번호.
	int nModulePos = LOBYTE(wParam);		// Interrupt 발생 모듈 번호.
	int nIntrFlag = (int)lParam;			// Interrupt 발생.
	int nModule;							// Interrupt 발생 모듈 번호.
        
    nModule = DIOget_module_number(nBoard, nModulePos);

	for(int nIndex = 0; nIndex < (CONTACT_POINT * 2); nIndex++)
	{
		if((nIntrFlag >> nIndex) & 0x01)	
		{
			int nBitState = DIOread_inport_bit(nModule, nIndex);

	 		if(nBitState)
				m_strEdgeStates = "▲Rising";
			else
				m_strEdgeStates = "▼Falling";	
	
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
			m_pCheckBtn[0]->SetWindowText("Input1");				// DI Module은 입력 32점으로 구성되었으므로 Group A, B를
			m_pCheckBtn[1]->SetWindowText("Input2");				// 모두 Input으로 설정 한다

			if(DIOIsInterruptEnabled(m_pModuleID->GetCurSel()))		// 지정한 모듈이 인터럽트 허용상태인지를 확인한다.
				m_pInterruptOn->SetCheck(1);
			else
				m_pInterruptOn->SetCheck(0);

			if(DIOread_upedge_word(m_pModuleID->GetCurSel(), 0)==0xFFFF &&		// 지정한 모듈이 UpEdge 상태인지를 확인한다.
				DIOread_upedge_word(m_pModuleID->GetCurSel(), 1)==0xFFFF)
				m_pchkRising->SetCheck(1);
			else
				m_pchkRising->SetCheck(0);

			if(DIOread_downedge_word(m_pModuleID->GetCurSel(), 0)==0xFFFF &&	// 지정한 모듈이 DownEdge 상태인지를 확인한다.
				DIOread_downedge_word(m_pModuleID->GetCurSel(), 1)==0xFFFF)
				m_pchkFalling->SetCheck(1);
			else
				m_pchkFalling->SetCheck(0);
			break;
		case AXT_SIO_DO32P:
		case AXT_SIO_DO32T:
			m_pCheckBtn[0]->SetWindowText("Output1");		// DO Module은 출력 32점으로 구성되었으므로 Geroup A, B를
			m_pCheckBtn[1]->SetWindowText("Output2");		// 모두 Output으로 설정 한다

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
			m_pCheckBtn[0]->SetWindowText("Output1");		// DB Module은 입출력이 각각 16점씩 구성되어 있으므로
			m_pCheckBtn[1]->SetWindowText("Input1");		// Group A를 Output으로 Group B를 Input으로 설정한다

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

BOOL CDlgDioTest::PreTranslateMessage(MSG* pMsg)		//esc키로 종료 됨을 막음..
{
	if ( pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN ) return true;
	if ( pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE ) return true;

	return CDialog::PreTranslateMessage(pMsg);
}

void CDlgDioTest::OnButtonExit() 
{
	//if (AfxMessageBox("종료하시겠습니까?", MB_YESNO) == IDYES)
	//{
	//	CDlgDioTest *pDlg = (CDlgDioTest *)AfxGetMainWnd();
		CloseDevice();									// 모든 장치를 닫아준다
	//	pDlg->OnCancel();
	//}
		SendMessage(WM_CLOSE, NULL);
}

BOOL CDlgDioTest::CloseDevice()							//장치 종료
{
	if (AxtIsInitialized())
	{
		AxtCloseDeviceAll();				// 추가된 베이스보드를 전부 닫는다
		AxtClose();							// 통합 라이브러리의 사용을 종료한다.

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
