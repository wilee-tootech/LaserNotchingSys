// DustTrap.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "BeamEditor6.h"
#include "MainFrm.h"
#include "DustTrap.h"
#include "afxdialogex.h"
#include "WriteLog.h"
#include "./Include/EXTERN/FileMgr.h"
// CDustTrap 대화 상자입니다.

IMPLEMENT_DYNAMIC(CDustTrap, CTabPageSSL)

CDustTrap::CDustTrap(CWnd* pParent /*=NULL*/)
	: CTabPageSSL(CDustTrap::IDD, pParent)
{

}

CDustTrap::~CDustTrap()
{
}

void CDustTrap::DoDataExchange(CDataExchange* pDX)
{
	CTabPageSSL::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDustTrap, CTabPageSSL)
	ON_BN_CLICKED(IDOK, &CDustTrap::OnBnClickedOk)
END_MESSAGE_MAP()


// CDustTrap 메시지 처리기입니다.


void CDustTrap::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CTabPageSSL::OnOK();
}

void CDustTrap::ReceiveData(WPARAM wParam, LPARAM lParam)
{
	// char* buf = m_pSockComm->ReadData();
}

void CDustTrap::SendData(CString msg)
{
	CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();
	CString strLogEvent = TEXT("");

	char buf[1024];
	CString CR = "";
	CR.Format("%c", 0x0D);
	msg += CR;
	msg += "\0";
	strcpy(buf, msg);
}


CDustTrap* CDustTrap::m_pDustTrap = nullptr;

CDustTrap* CDustTrap::GetInstance()
{
	if(m_pDustTrap == NULL)
	{
		m_pDustTrap = new CDustTrap;
	}

	return m_pDustTrap;
}


// ----------------- 통신 목록 --------------------	//
// IDC_CTTEXT_IN_TEMP			흡기온도			//
// IDC_CTTEXT_EXHAUST_TEMP		배기온도			//
// IDC_CTTEXT_ATTACH			차압				//
// IDC_CTTEXT_INVERTER			인버터				//
// IDC_CTTEXT_SLACK				소석회 무게			//
// IDC_CTTEXT_DUSTTRAP			집진기 풍속			//
// IDC_CTTEXT_WINDERS			권취기 풍속			//
//////////////////////////////////////////////////////
