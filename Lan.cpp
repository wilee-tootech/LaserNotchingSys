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


// 상속 받은 아이들 재정의하기 start
// Init시에 필요한 Data를 멤버에 넣어볼까 ex) RS232.에서는 port, parity, stop 등등, ex) Lan에서는 폴더 경로
UINT CLan::InitCommnicate() 
{
	return 1;
}

// 실제 연결에 들가보자
UINT CLan::StartCommunicate() 
{
	CPointerManager *pPointerManager = pPointerManager->GetInstance();
	CItemList<CComm*> *pItemList = pPointerManager->GetDlgComm()->GetCommList();
	BOOL result = FALSE;

	// 2003.11.05 List가 존재하는지 먼저 확인하기
	if (pItemList->GetCount() == 0) {
		AfxMessageBox(IDS_MESSAGE1);
		return 0;
	}
	
	Iterator<CComm*> *iterator = pItemList->iterator();

	while (iterator->HasNext()) {
		CComm *pComm = iterator->GetCurrentItem();
		if (pComm->GetOwner() == m_strOwner) {
			AfxMessageBox(IDS_MESSAGE2);
			// 다음 연결을 시도하는 것이지..
			// 연결되어 있는지 여부 check
			// if 안되어 있으면 다시..			
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

// 연결 끊자
UINT CLan::StopCommunicate() 
{
	return 0;
}

// 연결되어 있는지 아닌지 여부 가져오기
UINT CLan::GetConnectStatus() 
{
	return 0;
}

// 232에서는 SendString, Lan에서는 쓸 string
UINT CLan::WriteData(BYTE *SendString, DWORD Stringlength) 
{ // 데이터 써주기
	return 0;
} 

char *CLan::ReadData() 
{// 데이터 읽어오기
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
		// 85의 경우 설정도 되어 있고 연결도 되어있다는 얘기지.. // 그런데 이미 전에서 네트웍 드라이브에 연결되지
		// 않은 경우만 여기로 들어오기 때문에 로컬 디스크라고 보면 된다.
		AfxMessageBox("["+ strLclDrv + "] is local disk!");
	}
	else if (dwResult == ERROR_ACCOUNT_RESTRICTION) { // 1327
//		AfxMessageBox("계정 제한이구먼~~");
		AfxMessageBox(IDS_MESSAGE55);
	}
	else if (dwResult == ERROR_DEVICE_ALREADY_REMEMBERED/*1202*/) {
		// 1202의 경우 설정은 되어 있으나 연결상태는 아닌경우 현재 끊어져있지만 기억하고 있다는 얘기지..
//		AfxMessageBox("그 드라이브는 현재 끊어져있지만 이미 설정되어 있다네~~");
		AfxMessageBox(IDS_MESSAGE56);
		WNetCancelConnection(strLclDrv, TRUE);
		WNetAddConnection(netPath, "" , strLclDrv);


	}
	else if (dwResult == ERROR_BAD_NET_NAME || dwResult == ERROR_BAD_NETPATH) { //67
//		AfxMessageBox("ㅡㅡ;; 그런 경로는 연결할 수 없어");
		AfxMessageBox(IDS_MESSAGE57);
	}
	else if (dwResult == ERROR_LOGON_FAILURE) {
//		AfxMessageBox("ㅡㅡ;; 갸갸 누구랴 user name이랑 password알아와");
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
//		AfxMessageBox("Local Drive를 설정하세요!");
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
		strcpy(szUsedState, "사용중이 아닙니다. 연결을 재시도 합니다.");
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
