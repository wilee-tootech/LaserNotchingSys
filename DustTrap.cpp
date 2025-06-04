// DustTrap.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "BeamEditor6.h"
#include "MainFrm.h"
#include "DustTrap.h"
#include "afxdialogex.h"
#include "WriteLog.h"
#include "./Include/EXTERN/FileMgr.h"
// CDustTrap ��ȭ �����Դϴ�.

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


// CDustTrap �޽��� ó�����Դϴ�.


void CDustTrap::OnBnClickedOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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


// ----------------- ��� ��� --------------------	//
// IDC_CTTEXT_IN_TEMP			���µ�			//
// IDC_CTTEXT_EXHAUST_TEMP		���µ�			//
// IDC_CTTEXT_ATTACH			����				//
// IDC_CTTEXT_INVERTER			�ι���				//
// IDC_CTTEXT_SLACK				�Ҽ�ȸ ����			//
// IDC_CTTEXT_DUSTTRAP			������ ǳ��			//
// IDC_CTTEXT_WINDERS			����� ǳ��			//
//////////////////////////////////////////////////////
