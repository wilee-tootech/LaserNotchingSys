// Lan.cpp: implementation of the CLan class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "BeamEditor6.h"
#include "Lan.h"
#include "MainFrm.h"
#include "PointerManager.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLan::CLan()
{

}

CLan::~CLan()
{

}

CLan::CLan(CString owner)
{
	m_strOwner = owner;
}


// ��� ���� ���̵� �������ϱ� start
// Init�ÿ� �ʿ��� Data�� ����� �־�� ex) RS232.������ port, parity, stop ���, ex) Lan������ ���� ���
UINT CLan::InitCommnicate() 
{
	return 1;
}

// ���� ���ῡ �鰡����
UINT CLan::StartCommunicate() 
{
	CPointerManager *pPointerManager = pPointerManager->GetInstance();
	CItemList<CComm*> *pItemList = pPointerManager->GetDlgComm()->GetCommList();
	BOOL result = FALSE;

	// 2003.11.05 List�� �����ϴ��� ���� Ȯ���ϱ�
	if (pItemList->GetCount() == 0) {
		AfxMessageBox(IDS_MESSAGE1);
		return 0;
	}
	
	Iterator<CComm*> *iterator = pItemList->iterator();

	while (iterator->HasNext()) {
		CComm *pComm = iterator->GetCurrentItem();
		if (pComm->GetOwner() == m_strOwner) {
			AfxMessageBox(IDS_MESSAGE2);
			// ���� ������ �õ��ϴ� ������..
			// ����Ǿ� �ִ��� ���� check
			// if �ȵǾ� ������ �ٽ�..			
			CString path, netPath;
			path = pComm->GetLocalDevice();
			netPath = pComm->GetNetworkPath();
//			netPath.MakeUpper();
			OnCheckNetwork(path, netPath);
			result = TRUE;
			break;
		}
		iterator->SetNext();
	}
	
	if (result == FALSE) {
		AfxMessageBox(IDS_MESSAGE1);
		return 0;		
	}
	delete iterator;
	
	return 1;
}

// ���� ����
UINT CLan::StopCommunicate() 
{
	return 0;
}

// ����Ǿ� �ִ��� �ƴ��� ���� ��������
UINT CLan::GetConnectStatus() 
{
	return 0;
}

// 232������ SendString, Lan������ �� string
UINT CLan::WriteData(BYTE *SendString, DWORD Stringlength) 
{ // ������ ���ֱ�
	return 0;
} 

char *CLan::ReadData() 
{// ������ �о����
	return 0;
}

void CLan::OnAddNetwork(CString LocalDevice, CString NetPath)
{
	CString netPath, strLclDrv, path;

	netPath = NetPath;
//	netPath.MakeUpper();
	path = LocalDevice;

	if (path.GetLength() == 0) {
		AfxMessageBox(IDS_MESSAGE3);
		return;
	}
	char drive = path.GetAt(0);
	
	strLclDrv.Format("%c:", drive);
//	strLclDrv.MakeUpper();

	DWORD dwResult = WNetAddConnection(netPath, "" , strLclDrv);
	if (dwResult == NO_ERROR) { // 0
		AfxMessageBox(IDS_MESSAGE4);
	}
	else if (dwResult == ERROR_BAD_DEVICE) { // 1200
		AfxMessageBox(IDS_MESSAGE5);
	}
	else if (dwResult == ERROR_ALREADY_ASSIGNED/*85*/) {  
		// 85�� ��� ������ �Ǿ� �ְ� ���ᵵ �Ǿ��ִٴ� �����.. // �׷��� �̹� ������ ��Ʈ�� ����̺꿡 �������
		// ���� ��츸 ����� ������ ������ ���� ��ũ��� ���� �ȴ�.
		AfxMessageBox("["+ strLclDrv + "] is local disk!");
	}
	else if (dwResult == ERROR_ACCOUNT_RESTRICTION) { // 1327
//		AfxMessageBox("���� �����̱���~~");
		AfxMessageBox(IDS_MESSAGE55);
	}
	else if (dwResult == ERROR_DEVICE_ALREADY_REMEMBERED/*1202*/) {
		// 1202�� ��� ������ �Ǿ� ������ ������´� �ƴѰ�� ���� ������������ ����ϰ� �ִٴ� �����..
//		AfxMessageBox("�� ����̺�� ���� ������������ �̹� �����Ǿ� �ִٳ�~~");
		AfxMessageBox(IDS_MESSAGE56);
		WNetCancelConnection(strLclDrv, TRUE);
		WNetAddConnection(netPath, "" , strLclDrv);


	}
	else if (dwResult == ERROR_BAD_NET_NAME || dwResult == ERROR_BAD_NETPATH) { //67
//		AfxMessageBox("�Ѥ�;; �׷� ��δ� ������ �� ����");
		AfxMessageBox(IDS_MESSAGE57);
	}
	else if (dwResult == ERROR_LOGON_FAILURE) {
//		AfxMessageBox("�Ѥ�;; ���� ������ user name�̶� password�˾ƿ�");
		AfxMessageBox(IDS_MESSAGE58);
	}
}

void CLan::OnCheckNetwork(CString LocalDevice, CString NetPath)
{
	char szUsedState[SIZE_32];
	CString strLclDrv = _T(""), strCommand = _T("");
	char szRmtDrvName[SIZE_128]; 
	DWORD dwResult, cchBuff = sizeof(szRmtDrvName); 
	CString message;
	
	CString netPath, path;

	netPath = NetPath;
//	netPath.MakeUpper();
	path = LocalDevice;

	if (path.GetLength() == 0) {
//		AfxMessageBox("Local Drive�� �����ϼ���!");
		AfxMessageBox(IDS_MESSAGE59);
		return;
	}
	
	char drive = path.GetAt(0);
	
	strLclDrv.Format("%c:", drive);
//	strLclDrv.MakeUpper();
	dwResult = WNetGetConnection(strLclDrv, (LPSTR)szRmtDrvName, &cchBuff); 
	
	switch (dwResult) 
	{ 
	case NO_ERROR:   // A connection is remembered // 0
		memset(szUsedState, 0x00, sizeof(szUsedState));
		strcpy(szUsedState, "[" + strLclDrv + "] is connected with [" + szRmtDrvName + "]");
		break;
	case ERROR_CONNECTION_UNAVAIL : // A connection is remembered but not connected. // 1201
		memset(szUsedState, 0x00, sizeof(szUsedState));
		strcpy(szUsedState, "������� �ƴմϴ�. ������ ��õ� �մϴ�.");
		break;
	case ERROR_NOT_CONNECTED : // 2250
		memset(szUsedState, 0x00, sizeof(szUsedState));
		strcpy(szUsedState, "[" + strLclDrv + "] is not connected with network!");
		break;
	case ERROR_BAD_DEVICE : // 1200
		memset(szUsedState, 0x00, sizeof(szUsedState));
		strcpy(szUsedState, "The specified device name is invalid.");
	default:
		break; 
	} 
	AfxMessageBox(szUsedState);
	if (dwResult == ERROR_NOT_CONNECTED || dwResult == ERROR_CONNECTION_UNAVAIL) {
		OnAddNetwork(path, netPath);
	}
}
