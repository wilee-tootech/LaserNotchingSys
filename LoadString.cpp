// LoadString.cpp: implementation of the CLoadString class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "BeamEditor6.h"
#include "LoadString.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
#define INDEX(value) value

CLoadString::CLoadString()
{

}

CLoadString::~CLoadString()
{

}

void CLoadString::LoadString(CWnd *pWnd, int iStartString, int iStartID, int iEndID, BOOL bOk, BOOL bCancel)
{
	CString strTemp;

	if (iStartString != -1) {
		int j = iStartString;
		for (int i=iStartID; i <= iEndID; i++) {
			strTemp.LoadString(j);
			pWnd->GetDlgItem(i)->SetWindowText(strTemp);
			j++;
		}
	}
	
	// OK와 CANCEL은 예외처리
	if (bOk == TRUE) {
		strTemp.LoadString(IDS_OK);
		pWnd->GetDlgItem(IDOK)->SetWindowText(strTemp);
	}

	if (bCancel == TRUE) {
		strTemp.LoadString(IDS_CANCEL);
		pWnd->GetDlgItem(IDCANCEL)->SetWindowText(strTemp);
	}

	pWnd->UpdateData(FALSE);
}

void CLoadString::LoadIcon(CWnd *pWnd, int iStartID, int iEndID, BOOL bOk, BOOL bCancel)
{
	if (bOk == TRUE)
		((CButtonST *)pWnd->GetDlgItem(IDOK))->SetIcon(IDI_ICON256_OK);

	if (bCancel == TRUE)
		((CButtonST *)pWnd->GetDlgItem(IDCANCEL))->SetIcon(IDI_ICON256_CANCEL);

	pWnd->UpdateData(FALSE);
}

void CLoadString::LoadBitmap(CWnd *pWnd, int iStartBitmap, int iStartID, int iEndID)
{
	if (iStartBitmap != -1) {
		int j = iStartBitmap;
		for (int i=iStartID; i <= iEndID; i++) {
			((CButton *)pWnd->GetDlgItem(i))->SetBitmap(::LoadBitmap(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(j)));
			j++;
		}
	}
	pWnd->UpdateData(FALSE);
}

void CLoadString::LoadBitmap(CWnd *pWnd, int iBitmapID, int iID)
{
	CBitmap bmp;

	bmp.LoadBitmap(iBitmapID);
	((CButton *)pWnd->GetDlgItem(iID))->SetBitmap(bmp);
	((CButton *)pWnd->GetDlgItem(iID))->RedrawWindow();
	bmp.DeleteObject();
	
	pWnd->UpdateData(FALSE);
}
