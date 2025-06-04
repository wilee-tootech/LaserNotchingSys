// DlgTabData.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "BeamEditor6.h"
#include "DlgTabData.h"
#include "afxdialogex.h"
#include "MainFrm.h"

// CDlgTabData ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CDlgTabData, CDialogEx)

CDlgTabData::CDlgTabData(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgTabData::IDD, pParent)
	, m_bUseReverse(FALSE)
	, m_dTabPosition(0)
	, m_dOffset(0)
{

}

CDlgTabData::~CDlgTabData()
{
}

void CDlgTabData::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_CHECK_USE_REVERSE, m_bUseReverse);
	DDX_Text(pDX, IDC_EDIT_POSITION, m_dTabPosition);
	DDX_Text(pDX, IDC_EDIT_OFFSET, m_dOffset);
}


BEGIN_MESSAGE_MAP(CDlgTabData, CDialogEx)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CDlgTabData �޽��� ó�����Դϴ�.


void CDlgTabData::OnClose()
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	CDialogEx::OnClose();
}


void CDlgTabData::OnOK()
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	UpdateData(true);
	CDialogEx::OnOK();
}

