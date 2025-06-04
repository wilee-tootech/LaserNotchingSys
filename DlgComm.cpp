      // DlgComm.cpp : implementation file
//

#include "stdafx.h"
#include "BeamEditor6.h"
#include "DlgComm.h"
#include "DlgNetworkPath.h"
#include "PointerManager.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgComm dialog


CDlgComm::CDlgComm(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgComm::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgComm)
	m_iDev = -1;
	m_iStop = -1;
	m_iPort = -1;
	m_iParity = -1;
	m_iData = -1;
	m_iBaud = -1;
	m_iPart = -1;
	//}}AFX_DATA_INIT
	m_pCommList = new CItemList<CComm *>(MAX_COMMUNICATE);
}

void CDlgComm::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgComm)
	DDX_Control(pDX, IDC_COMM_10, m_stcNetworkPath);
	DDX_Control(pDX, IDC_COMM_9, m_stcLocalDevice);
	DDX_Control(pDX, IDCANCEL, m_btnCancel);
	DDX_Control(pDX, IDOK, m_btnOk);
	DDX_Control(pDX, IDC_STATIC_GROUP2, m_btnGroup2);
	DDX_Control(pDX, IDC_STATIC_GROUP1, m_btnGroup1);
	DDX_Control(pDX, IDC_COMM_6, m_stcStop);
	DDX_Control(pDX, IDC_COMM_2, m_stcPort);
	DDX_Control(pDX, IDC_COMM_5, m_stcParity);
	DDX_Control(pDX, IDC_COMM_4, m_stcData);
	DDX_Control(pDX, IDC_COMM_3, m_stcBaud);
	DDX_Control(pDX, IDC_SELECTPATH, m_btnSelectPath);
	DDX_Control(pDX, IDC_NETWORK_FOLDER, m_editNetworkFolder);
	DDX_Control(pDX, IDC_LOCALDEVICE, m_editLocalDevice);
	DDX_Control(pDX, IDC_CHECKNETWORK, m_btnCheckNetwork);
	DDX_Control(pDX, IDC_CANCELNETWORK, m_btnCancelNetwork);
	DDX_Control(pDX, IDC_ADDNETWORK, m_btnAddNetwork);
	DDX_Control(pDX, IDC_CMB_DATA, m_cboData);
	DDX_Control(pDX, IDC_CMB_BAUD, m_cboBaud);
	DDX_Control(pDX, IDC_CMB_PARITY, m_cboParity);
	DDX_Control(pDX, IDC_CMB_PORT, m_cboPort);
	DDX_Control(pDX, IDC_CMB_STOP, m_cboStop);
	DDX_Control(pDX, IDC_COMBO_DEVICE, m_cboDev);
	DDX_Control(pDX, IDC_COMBO_PART, m_cboPart);
	DDX_CBIndex(pDX, IDC_COMBO_DEVICE, m_iDev);
	DDX_CBIndex(pDX, IDC_CMB_STOP, m_iStop);
	DDX_CBIndex(pDX, IDC_CMB_PORT, m_iPort);
	DDX_CBIndex(pDX, IDC_CMB_PARITY, m_iParity);
	DDX_CBIndex(pDX, IDC_CMB_DATA, m_iData);
	DDX_CBIndex(pDX, IDC_CMB_BAUD, m_iBaud);
	DDX_CBIndex(pDX, IDC_COMBO_PART, m_iPart);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgComm, CDialog)
	//{{AFX_MSG_MAP(CDlgComm)
	ON_CBN_SELCHANGE(IDC_COMBO_DEVICE, OnSelchangeComboDevice)
	ON_BN_CLICKED(IDC_SELECTPATH, OnSelectpath)
	ON_BN_CLICKED(IDC_COMM_1, OnSetting)
	ON_CBN_SELCHANGE(IDC_COMBO_PART, OnSelchangeComboPart)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_CHECKNETWORK, &CDlgComm::OnBnClickedChecknetwork)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgComm message handlers

BOOL CDlgComm::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CLoadString LoadString;
	LoadString.LoadString(this, IDS_COMM_1, IDC_COMM_1, IDC_COMM_10, TRUE, TRUE);
	LoadString.LoadIcon(this, -1, -1, TRUE, TRUE);

	EnableControl(1);

	CPointerManager *pPointerManager = pPointerManager->GetInstance();
	CItemList<CComm*> *pItemList = pPointerManager->GetDlgComm()->GetCommList();
	if (pItemList->GetCount() == 0) {	// List가 존재하는지 먼저 확인하기
		return 0;
	}
	
	Iterator<CComm*> *iterator = pItemList->iterator();

	while (iterator->HasNext()) {
		CComm *pComm = iterator->GetCurrentItem();
		if (pComm->GetOwner() == "Laser Control") {
			/* Find String을 이용한 방법도 가능 */
//			int result = m_cboDev.FindString(-1, pComm->GetMethod());
//			m_cboDev.SetCurSel(result);
			m_cboDev.SelectString(-1, pComm->GetMethod());
			m_cboStop.SelectString(-1, pComm->GetStopBit());
			m_cboPort.SelectString(-1, pComm->GetPort());
			m_cboParity.SelectString(-1, pComm->GetParity());
			m_cboData.SelectString(-1, pComm->GetData());
			m_cboBaud.SelectString(-1, pComm->GetBaud());
			m_cboPart.SelectString(-1, pComm->GetOwner());
			m_editLocalDevice.SetWindowText(pComm->GetLocalDevice());
			m_editNetworkFolder.SetWindowText(pComm->GetNetworkPath());
		}
		iterator->SetNext();
	}
	delete iterator;
	
	/* UpdateData를 해주면 안됨. Control을 이용하여 Setting 했는데 Value를 Up하면 초기화ㅡㅡ;; */  
//	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgComm::EnableControl(int Device)
{
	m_cboPort.ShowWindow(Device);
	m_cboBaud.ShowWindow(Device);
	m_cboData.ShowWindow(Device);
	m_cboParity.ShowWindow(Device);
	m_cboStop.ShowWindow(Device);
	m_stcPort.ShowWindow(Device);
	m_stcBaud.ShowWindow(Device);
	m_stcData.ShowWindow(Device);
	m_stcParity.ShowWindow(Device);
	m_stcStop.ShowWindow(Device);
	m_btnGroup1.ShowWindow(Device);
	m_editLocalDevice.ShowWindow(!Device);
	m_editNetworkFolder.ShowWindow(!Device);
	m_btnSelectPath.ShowWindow(!Device);
	m_btnCheckNetwork.ShowWindow(!Device);
	m_btnCancelNetwork.ShowWindow(!Device);
	m_btnAddNetwork.ShowWindow(!Device);
	m_btnGroup2.ShowWindow(!Device);
	m_stcNetworkPath.ShowWindow(!Device);
	m_stcLocalDevice.ShowWindow(!Device);
}

void CDlgComm::OnSelchangeComboDevice() 
{
	// TODO: Add your control notification handler code here
	if (m_cboDev.GetCurSel() == 1) {
		EnableControl(0); // 232
	}
	else {
		EnableControl(1); // LAN
	}		
}

void CDlgComm::OnSelectpath() 
{
	// TODO: Add your control notification handler code here
	CDlgNetworkPath *m_pDlgNetworkPath = new CDlgNetworkPath;
	
	if (m_pDlgNetworkPath->DoModal() == IDOK)
	{
		GetDlgItem(IDC_LOCALDEVICE)->SetWindowText(m_pDlgNetworkPath->GetNetworkPath());
	}	
}

void CDlgComm::OnSetting() 
{
	// TODO: Add your control notification handler code here
	CString owner(""), method(""), port(""), baud(""), data(""), parity(""), stopbit(""), localDevice(""), networkFolder("");

	UpdateData(TRUE);
	m_cboPart.GetLBText(m_iPart, owner);
	m_cboDev.GetLBText(m_iDev, method);
	m_cboPort.GetLBText(m_iPort, port);
	m_cboBaud.GetLBText(m_iBaud, baud);
	m_cboData.GetLBText(m_iData, data);
	m_cboParity.GetLBText(m_iParity, parity);
	m_cboStop.GetLBText(m_iStop, stopbit);
	m_editLocalDevice.GetWindowText(localDevice);
	m_editNetworkFolder.GetWindowText(networkFolder);

	if (method == "RS232" && SamePortChecker() == TRUE) {
		AfxMessageBox(IDS_MESSAGE22);
		return;
	}
	
	// Checker 들어갈 자리
	if (method == "RS232") {
 		m_pCommList->Append(new CComm(owner, method, port, baud, data, parity, stopbit, this));
	}
	else if (method == "LAN") {
 		m_pCommList->Append(new CComm(owner, method, localDevice, networkFolder, this));
	}
	
}

CItemList<CComm*> *CDlgComm::GetCommList()
{
	return m_pCommList;
}

BOOL CDlgComm::SamePortChecker()
{
	CString owner(""), port("");
	m_cboPart.GetLBText(m_iPart, owner);
	m_cboPort.GetLBText(m_iPort, port);
	
	Iterator<CComm*> *iterator = m_pCommList->iterator();

	while (iterator->HasNext()) {
		CComm *pComm = iterator->GetCurrentItem();
		if (pComm->GetOwner() != owner && pComm->GetPort() == port) {
			return TRUE;
		}
		iterator->SetNext();
	}
	delete iterator;

	return FALSE;
}

void CDlgComm::OnSelchangeComboPart() 
{
	// TODO: Add your control notification handler code here
	CPointerManager *pPointerManager = pPointerManager->GetInstance();
	CItemList<CComm*> *pItemList = pPointerManager->GetDlgComm()->GetCommList();
	// 2003.11.05 List가 존재하는지 먼저 확인하기
	if (pItemList->GetCount() == 0) {
		return;
	}
	
	CString owner;
	UpdateData(TRUE);

	m_cboPart.GetLBText(m_iPart, owner);
	Iterator<CComm*> *iterator = pItemList->iterator();

	while (iterator->HasNext()) {
		CComm *pComm = iterator->GetCurrentItem();
		if (pComm->GetOwner() == owner) {
			m_cboDev.SelectString(-1, pComm->GetMethod());
			OnSelchangeComboDevice();
			m_cboStop.SelectString(-1, pComm->GetStopBit());
			m_cboPort.SelectString(-1, pComm->GetPort());
			m_cboParity.SelectString(-1, pComm->GetParity());
			m_cboData.SelectString(-1, pComm->GetData());
			m_cboBaud.SelectString(-1, pComm->GetBaud());
			m_editLocalDevice.SetWindowText(pComm->GetLocalDevice());
			m_editNetworkFolder.SetWindowText(pComm->GetNetworkPath());
		}
		iterator->SetNext();
	}
	delete iterator;	
}


void CDlgComm::OnBnClickedChecknetwork()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
