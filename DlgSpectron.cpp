// DlgSpectron.cpp : implementation file
//

#include "stdafx.h"
#include "BeamEditor6.h"
#include "DlgSpectron.h"
#include "RS232.h"
#include "Lan.h"
#include "Spectron.h"
#include "MainFrm.h"
#include "PointerManager.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgSpectron dialog


CDlgSpectron::CDlgSpectron(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSpectron::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgSpectron)
	m_dCurrentEdit = 0.0;
	//}}AFX_DATA_INIT
}


void CDlgSpectron::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSpectron)
	DDX_Control(pDX, IDC_MULTI_MODE, m_btnMultiMode);
	DDX_Control(pDX, IDC_APERTURE_MODE, m_btnApertureMode);
	DDX_Control(pDX, IDC_OPEN_SHUTTER, m_btnShutterOn);
	DDX_Control(pDX, IDC_CLOSER_SHUTTER, m_btnShutterOff);
	DDX_Control(pDX, IDC_CURRENT, m_btnSetCurrent);
	DDX_Control(pDX, IDC_AUTO_OFF, m_btnAutoOff);
	DDX_Control(pDX, IDC_AUTO_ON, m_btnAutoOn);
	DDX_Control(pDX, IDC_CURRENT_SLIDER, m_ctrCurrentSlider);
	DDX_Text(pDX, IDC_CURRENT_EDIT, m_dCurrentEdit);
	DDV_MinMaxDouble(pDX, m_dCurrentEdit, 0., 50.);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgSpectron, CDialog)
	//{{AFX_MSG_MAP(CDlgSpectron)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_AUTO_ON, OnAutoOn)
	ON_BN_CLICKED(IDC_AUTO_OFF, OnAutoOff)
	ON_BN_CLICKED(IDC_OPEN_SHUTTER, OnOpenShutter)
	ON_BN_CLICKED(IDC_CLOSER_SHUTTER, OnCloserShutter)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_CURRENT_SLIDER, OnReleasedcaptureCurrentSliderLee)
	ON_BN_CLICKED(IDC_CURRENT, OnCurrent)
	ON_WM_TIMER()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_APERTURE_MODE, OnApertureMode)
	ON_BN_CLICKED(IDC_MULTI_MODE, OnMultiMode)
	ON_MESSAGE(WM_RECEIVE_COM, OnReceive_Com)
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgSpectron message handlers
BOOL CDlgSpectron::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CPointerManager *pPointerManager = pPointerManager->GetInstance();
	m_pLaserControl = pPointerManager->GetLaserControl();
	
	m_btnAutoOn.EnableWindow(TRUE);
	m_btnAutoOff.EnableWindow(FALSE);
	m_btnSetCurrent.EnableWindow(FALSE);
	m_btnApertureMode.EnableWindow(FALSE);
	m_btnMultiMode.EnableWindow(FALSE);
	m_btnShutterOn.EnableWindow(FALSE);
	m_btnShutterOff.EnableWindow(FALSE);

	m_ctrCurrentSlider.SetRange(0, 500);  // 0 ~ 50A

	LoadIcon();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgSpectron::OnDestroy() 
{
	CDialog::OnDestroy();
	// TODO: Add your message handler code here
	CPointerManager *m_pPointerManager = m_pPointerManager->GetInstance();
	/* Power On ���̰ų� AutoOn �������� �ƴϸ� �ٿ��α׿� ���� ��Ʈ���� �η� */
	if (!(m_pLaserControl->GetIsAutoOn() == TRUE || m_pLaserControl->GetIsProceedOn() == TRUE)) {
		
//		if (m_pPointerManager->GetLaserControl() != NULL) {
//			delete m_pPointerManager->GetLaserControl();
//		}

		m_pPointerManager->DestoryLaserControl();

//		delete m_pLaserControl;
		m_pLaserControl = NULL;

		if (m_pPointerManager->GetDlgLaserControl() != NULL) {
			delete m_pPointerManager->GetDlgLaserControl();
			m_pPointerManager->SetDlgLaserControl(NULL);
		}
		m_pLaserControl = NULL;

//		m_pPointerManager->CreateLaserControl(NULL);
//		m_pPointerManager->SetDlgLaserControl(NULL);
	}
	/* Power On ���̰ų� AutoOn �������̸� ���� �޽��� SetFocus */
	else {
		AfxMessageBox(IDS_OFF_POWER);
		this->ShowWindow(SW_SHOWNORMAL);
		this->SetFocus();
	}
}

void CDlgSpectron::OnAutoOn() 
{
	// TODO: Add your control notification handler code here
	/* ���⼭�� ��Ʈ�� ��� ���� ��縸 ������ LaserControl�� ��� */
	if(AfxMessageBox(IDS_POWER_ON, MB_OKCANCEL) == IDOK)
	{
		this->SetFocus();
		SetTimer(1, 200, NULL);
		m_btnAutoOn.EnableWindow(FALSE);
		m_btnAutoOff.EnableWindow(FALSE);
		m_btnSetCurrent.EnableWindow(FALSE);
		m_btnShutterOn.EnableWindow(FALSE);
		m_btnShutterOff.EnableWindow(FALSE);
		m_btnApertureMode.EnableWindow(FALSE);
		m_btnMultiMode.EnableWindow(FALSE);
		if(m_pLaserControl->AutoOn()) {
			m_btnAutoOn.EnableWindow(FALSE);
			m_btnAutoOff.EnableWindow(TRUE);
			m_btnSetCurrent.EnableWindow(TRUE);
			m_btnShutterOn.EnableWindow(TRUE);
			m_btnShutterOff.EnableWindow(FALSE);
			if (m_pLaserControl->GetMode() == 0) {
				m_btnApertureMode.EnableWindow(FALSE);
				m_btnMultiMode.EnableWindow(TRUE);
			}
			else if (m_pLaserControl->GetMode() == 1) {
				m_btnApertureMode.EnableWindow(TRUE);
				m_btnMultiMode.EnableWindow(FALSE);
			}
		}
		else
			m_btnAutoOn.EnableWindow(TRUE);

		/* ���� ���⼭ Set�ϴ� ������ ConcreteClass������ ������ ��� �ϱ� ���� */
		m_pLaserControl->SetIsProceedOn(FALSE);
		KillTimer(1);
	}
}

void CDlgSpectron::OnAutoOff() 
{
	// TODO: Add your control notification handler code here
	if(AfxMessageBox(IDS_POWER_OFF,MB_OKCANCEL) == IDOK)
	{ 
		this->SetFocus();
		m_btnAutoOn.EnableWindow(FALSE);
		m_btnAutoOff.EnableWindow(FALSE);
		m_btnShutterOn.EnableWindow(FALSE);
		m_btnShutterOff.EnableWindow(FALSE);
		m_btnSetCurrent.EnableWindow(FALSE);
		m_btnApertureMode.EnableWindow(FALSE);
		m_btnMultiMode.EnableWindow(FALSE);
		m_pLaserControl->AutoOff();

		CString strCurrentTemp;
		strCurrentTemp.Format("%3.1f", 0);
		
		// Edit box�� current�� setting 
		// (���� �ִ� ���� �ƴ϶� ���� laser�� current����)
		CWnd *value;
		value = GetDlgItem(IDC_CURRENT_EDIT);
		value->SetWindowText(strCurrentTemp);
		value->UpdateWindow();
		// slider�� �ʱⰪ setting
		m_ctrCurrentSlider.SetPos(0);
		m_btnAutoOn.EnableWindow(true);
	}
}

void CDlgSpectron::OnOpenShutter() 
{
	// TODO: Add your control notification handler code here
	m_btnShutterOn.EnableWindow(FALSE);
	m_pLaserControl->ShutterOn();
	m_btnShutterOff.EnableWindow(TRUE);
	LoadIcon();
}

void CDlgSpectron::OnCloserShutter() 
{
	// TODO: Add your control notification handler code here
	m_btnShutterOff.EnableWindow(FALSE);
	m_pLaserControl->ShutterOff();
	m_btnShutterOn.EnableWindow(TRUE);
	LoadIcon();
}

void CDlgSpectron::OnReleasedcaptureCurrentSliderLee(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	int iSetpos;

	iSetpos = m_ctrCurrentSlider.GetPos();
	m_dCurrentEdit = iSetpos * 0.1;
	UpdateData(FALSE);
	
	*pResult = 0;	
}

void CDlgSpectron::OnCurrent() 
{
	// TODO: Add your control notification handler code here
	double dCurrent;

	UpdateData(TRUE);
	dCurrent = m_dCurrentEdit;
	m_pLaserControl->CurrentControl(dCurrent);
}

BOOL CDlgSpectron::GetIsAutoOn()
{
	if (m_pLaserControl != NULL)
		return m_pLaserControl->GetIsAutoOn();
	else
		return FALSE;
}

BOOL CDlgSpectron::GetIsProceedOn()
{
	if (m_pLaserControl != NULL)
		return m_pLaserControl->GetIsProceedOn();
	else
		return FALSE;
}

void CDlgSpectron::LoadIcon()
{
	// �� ��ġ���� OnOff���� bmp upload�� shutter OnOff button Ȱ������
	CButton *pWnd;
	CStatic *pIcon;
	unsigned int result1 = m_pLaserControl->GetOnStatus();
	unsigned int result2;

	result2 = (result1 & 8) >> 3;
	if (result2 == TRUE) {
		pWnd = (CButton*)GetDlgItem(IDC_STOP);
		pWnd->SetBitmap(::LoadBitmap(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDB_STOP_OFF)));
		pWnd = (CButton*)GetDlgItem(IDC_START);
		pWnd->SetBitmap(::LoadBitmap(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDB_START_ON)));
	}
	else if (result2 == FALSE) {
		pWnd = (CButton*)GetDlgItem(IDC_STOP);
		pWnd->SetBitmap(::LoadBitmap(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDB_STOP_ON)));
		pWnd = (CButton*)GetDlgItem(IDC_START);
		pWnd->SetBitmap(::LoadBitmap(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDB_START_OFF)));
	}

	result2 = (result1 & 16) >> 4;
	if (result2 == TRUE) {
		pWnd = (CButton*)GetDlgItem(IDC_PUMP);
		pWnd->SetBitmap(::LoadBitmap(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDB_PUMP_ON)));
	}
	else if (result2 == FALSE) {
		pWnd = (CButton*)GetDlgItem(IDC_PUMP);
		pWnd->SetBitmap(::LoadBitmap(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDB_PUMP_OFF)));
		
	}

	pWnd = (CButton*)GetDlgItem(IDC_LOCAL);
	pWnd->SetBitmap(::LoadBitmap(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDB_REMOTE)));

	result2 = (result1 & 2) >> 1;
	if (result2 == TRUE) {
		pIcon = (CStatic*)GetDlgItem(IDC_SHUTTER_STATUS);
		pIcon->SetIcon(::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_SHUTTER_ON)));
	    m_btnShutterOn.EnableWindow(FALSE);
	    m_btnShutterOff.EnableWindow(TRUE);
	}
	else if (result2 == FALSE) {
		pIcon = (CStatic*)GetDlgItem(IDC_SHUTTER_STATUS);
		pIcon->SetIcon(::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_SHUTTER_OFF)));
		m_btnShutterOn.EnableWindow(TRUE);
	    m_btnShutterOff.EnableWindow(FALSE);
		result2 = (result1 & 64) >> 6;
		if (result2 == FALSE) // �ڵ� AutoOn�� FALSE�̸�
			m_btnShutterOn.EnableWindow(FALSE);
	}
	
	pWnd->UpdateWindow();
}

void CDlgSpectron::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	switch(nIDEvent) {
	case 1:
		KillTimer(1);
		LoadIcon();
		SetTimer(1, 200, NULL);
		break;
	case 2:
		break;
	default:
		break;
	}
	CDialog::OnTimer(nIDEvent);
}

void CDlgSpectron::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	CDialog::OnClose();
}

void CDlgSpectron::OnApertureMode() 
{
	// TODO: Add your control notification handler code here
	m_btnApertureMode.EnableWindow(FALSE);
	m_pLaserControl->ChangeMode(0);
	m_btnMultiMode.EnableWindow(TRUE);	
}

void CDlgSpectron::OnMultiMode() 
{
	// TODO: Add your control notification handler code here
	m_btnMultiMode.EnableWindow(FALSE);	
	m_pLaserControl->ChangeMode(1);
	m_btnApertureMode.EnableWindow(TRUE);
	
}

// ���� �ޱ�� ���⼭ ����
LRESULT CDlgSpectron::OnReceive_Com(WPARAM wParam,LPARAM lParam)
{
	char buffer[200] = "";

	int nRcvSize = (INT)lParam;
	if( nRcvSize <= 0 )
		return FALSE;

	// Ack Message�� Buffer�ȿ� ����
	tempString = AllocTwoByte(nRcvSize);  // �޾Ƶ��� �� Hexa�� ����
	m_strData = strRcvData2Char(nRcvSize); // �޾Ƶ��� String �״��

	strcpy(buffer, (LPCTSTR)tempString);

	DecodeSystemStatus();

	return TRUE;
}


//--- ���ŵ� �������� ��.���� �Ϻ��� ���� �ѹ���Ʈ�� �����.
CString CDlgSpectron::AllocTwoByte(int length)
{
	BYTE byte;
//	BYTE low;
	CString recSen;
	for(int i=0 ; i< length ;i++)
	{
        byte = ( rcvBuf[i] & 0xF0 );  //--- ���� �Ϻ� �и� �ؼ� 
		byte >>= 4 ;                      //--- ���� �Ϻ�� ���� 
		recSen += Hexa2Ascii(byte);
		
        byte =  ( rcvBuf[i] & 0x0F);  //--- ���� �Ϻ� �и�   
		recSen += Hexa2Ascii(byte);
		
        recSen += _T(" ");
	}
	recSen += _T("\r\n");
	return recSen;
}

void CDlgSpectron::DecodeSystemStatus()
{
	char POUT[128] = "";
	unsigned long SystemStatus = 0;
	char add_string[128] = "";
	unsigned long test = 0x20000l;
	CStatic *pIcon;

	// m_strData�� �ƴ� tempString�� ����ϴ� ������
	// String���� �׳� ������� 0�� ������ NULL�� �ν��ؼ� ������ �������� ���ϱ� ����
	strcpy(POUT, (LPCTSTR)tempString);

	// ���� ACK�� system status���� �ƴ��� Ȯ��
	if (tempString.GetAt(3) != '0' || tempString.GetAt(4) != '3') {
		return;
	}

	CString temp;

	POUT[2] = 16*tempString.GetAt(6)+tempString.GetAt(7) - '0';
	POUT[3] = 16*tempString.GetAt(9)+tempString.GetAt(10) - '0';
	POUT[4] = 16*tempString.GetAt(12)+tempString.GetAt(13) - '0';

//	SystemStatus = (((long)POUT[2]) << 16) + (((long)POUT[3]) << 8) + ((long)POUT[4]); // dos����
	SystemStatus = (long(POUT[2] * 65536)) + (long(POUT[3] * 256)) + ((long)POUT[4]);
	
	for(int i=0;i<18;i++)
	{
		if( (SystemStatus & test) == 0)
		{
			add_string[i] = '0';
		}
		else
		{
			add_string[i] = '1';
		}
		test = test >> 1;
	}

/*  // ��... ��ȣ ������ ��� �����..Software Monitoring �߰��� ���ص� �ɵ�...
	if (m_isShutter == 1 && add_string[14] == '0') {
		Select_Gated_CW();
		if (m_isRFOn == 1) {
			m_Aperture.EnableWindow(false);
			RF_ON();
			m_Multi.EnableWindow(true);	
		}
		m_ShutterOn.EnableWindow(false);
		OpenShutter();
		m_ShutterOff.EnableWindow(true);
		OnReCurrentSet();  // 2002.12.20 sitework
	}*/

	if (add_string[12] == '0') {
		pIcon = (CStatic*)GetDlgItem(IDC_STATUS8);
		pIcon->SetIcon(::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_NONE)));
	}
	else if (add_string[12] == '1') {
		pIcon = (CStatic*)GetDlgItem(IDC_STATUS8);
		pIcon->SetIcon(::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_WARN)));
	}

	if (add_string[10] == '0') {
		pIcon = (CStatic*)GetDlgItem(IDC_STATUS2);
		pIcon->SetIcon(::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_NONE)));
	}
	else if (add_string[10] == '1') {
		pIcon = (CStatic*)GetDlgItem(IDC_STATUS2);
		pIcon->SetIcon(::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_WARN)));
	}

	if (add_string[9] == '0') {
		pIcon = (CStatic*)GetDlgItem(IDC_STATUS3);
		pIcon->SetIcon(::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_NONE)));
		pIcon = (CStatic*)GetDlgItem(IDC_STATUS4);
		pIcon->SetIcon(::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_NONE)));
		pIcon = (CStatic*)GetDlgItem(IDC_STATUS5);
		pIcon->SetIcon(::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_NONE)));
		pIcon = (CStatic*)GetDlgItem(IDC_STATUS6);
		pIcon->SetIcon(::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_NONE)));
	}
	else if (add_string[9] == '1') {
		pIcon = (CStatic*)GetDlgItem(IDC_STATUS3);
		pIcon->SetIcon(::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_WARN)));
		pIcon = (CStatic*)GetDlgItem(IDC_STATUS4);
		pIcon->SetIcon(::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_WARN)));
		pIcon = (CStatic*)GetDlgItem(IDC_STATUS5);
		pIcon->SetIcon(::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_WARN)));
		pIcon = (CStatic*)GetDlgItem(IDC_STATUS6);
		pIcon->SetIcon(::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_WARN)));
	}

	if (add_string[8] == '0') {
		pIcon = (CStatic*)GetDlgItem(IDC_STATUS7);
		pIcon->SetIcon(::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_NONE)));
	}
	else if (add_string[8] == '1') {
		pIcon = (CStatic*)GetDlgItem(IDC_STATUS7);
		pIcon->SetIcon(::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_WARN)));
	}

	if (add_string[7] == '0') {
		pIcon = (CStatic*)GetDlgItem(IDC_STATUS14);
		pIcon->SetIcon(::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_NONE)));
	}
	else if (add_string[7] == '1') {
		pIcon = (CStatic*)GetDlgItem(IDC_STATUS14);
		pIcon->SetIcon(::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_WARN)));
	}

	if (add_string[6] == '0') {
		pIcon = (CStatic*)GetDlgItem(IDC_STATUS11);
		pIcon->SetIcon(::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_NONE)));
	}
	else if (add_string[6] == '1') {
		pIcon = (CStatic*)GetDlgItem(IDC_STATUS11);
		pIcon->SetIcon(::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_WARN)));
	}

	if (add_string[5] == '0') {
		pIcon = (CStatic*)GetDlgItem(IDC_STATUS9);
		pIcon->SetIcon(::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_NONE)));
	}
	else if (add_string[5] == '1') {
		pIcon = (CStatic*)GetDlgItem(IDC_STATUS9);
		pIcon->SetIcon(::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_WARN)));
	}

	if (add_string[4] == '0') {
		pIcon = (CStatic*)GetDlgItem(IDC_STATUS10);
		pIcon->SetIcon(::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_NONE)));
	}
	else if (add_string[4] == '1') {
		pIcon = (CStatic*)GetDlgItem(IDC_STATUS10);
		pIcon->SetIcon(::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_WARN)));
	}

	if (add_string[3] == '0') {
		pIcon = (CStatic*)GetDlgItem(IDC_STATUS13);
		pIcon->SetIcon(::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_NONE)));
	}
	else if (add_string[3] == '1') {
		pIcon = (CStatic*)GetDlgItem(IDC_STATUS13);
		pIcon->SetIcon(::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_WARN)));
	}

	if (add_string[2] == '0') {
		pIcon = (CStatic*)GetDlgItem(IDC_STATUS12);
		pIcon->SetIcon(::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_NONE)));
	}
	else if (add_string[2] == '1') {
		pIcon = (CStatic*)GetDlgItem(IDC_STATUS12);
		pIcon->SetIcon(::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_WARN)));
	}

	if (add_string[0] == '0') {
		pIcon = (CStatic*)GetDlgItem(IDC_STATUS1);
		pIcon->SetIcon(::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_NONE)));
	}
	else if (add_string[0] == '1') {
		pIcon = (CStatic*)GetDlgItem(IDC_STATUS1);
		pIcon->SetIcon(::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_WARN)));
	}
	pIcon->UpdateWindow();
}

CString CDlgSpectron::strRcvData2Char(int nRcvSize)
{
	CString strData;
	//--- ���� ������ŭ..
	for( int i=0; i< nRcvSize; i++ )
	{
		strData += rcvBuf[i];
	}
	//--- �� �ڿ��� �ٹٲ�..Edit Box�� �����ٿ� ����ϱ����� 
	strData += _T( "\r\n" );
	//--- ��ȯ�� ���ڿ� �ѱ�.
	return strData;
}

BYTE CDlgSpectron::Hexa2Ascii(BYTE &ch)
{
    if(ch >= 0 && ch <= 9 )
	{
        ch += '0';
	}
    else if(ch >= 10 && ch <= 15 ) //10�� ���ų� ũ�� 
	{
        ch -= 9;
		ch |= 0x40;
	}
	return ch;
}

void CDlgSpectron::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	
	// TODO: Add your message handler code here	
	if (!m_pLaserControl->GetIsConnect())
		AfxMessageBox(IDS_MESSAGE1);
}
