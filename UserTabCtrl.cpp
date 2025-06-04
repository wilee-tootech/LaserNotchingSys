// UserTabCtrl.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "../ProjectBase.h"
#include "UserTabCtrl.h"

#include "../EXTERN/CColorDefine.h"

// CUserTabCtrl

IMPLEMENT_DYNAMIC(CUserTabCtrl, CTabCtrl)

CUserTabCtrl::CUserTabCtrl()
{

}

CUserTabCtrl::~CUserTabCtrl()
{
}


BEGIN_MESSAGE_MAP(CUserTabCtrl, CTabCtrl)
//	ON_WM_DRAWITEM()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()



// CUserTabCtrl �޽��� ó�����Դϴ�.

//��� ��, ���� �Ӽ����� Bottons�� True�� �Ұ�.

//�׸��� �ش� ����ϴ� Tab Dialog Init�� m_tab_.ModifyStyle(0, TCS_OWNERDRAWFIXED);  <-�̰� �־���� ��ư���� ����.

void CUserTabCtrl::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	int select_index = lpDrawItemStruct->itemID;
	if(select_index < 0) return;

	CDC *pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
	CRect rect = lpDrawItemStruct->rcItem;

	// Tab�� �׷��� �׵θ��� �β���ŭ ��ġ�� �����Ѵ�.
	rect.top += ::GetSystemMetrics(SM_CYEDGE);

	pDC->SetBkMode(TRANSPARENT);

	TCHAR tab_text[40];

	TC_ITEM data;
	data.mask = TCIF_TEXT|TCIF_IMAGE;
	data.pszText = tab_text;
	data.cchTextMax = 39;

	// ���� ���õ� ������ ���� ������ ĥ���ش�.
	if(select_index == GetCurSel()) pDC->FillSolidRect(rect, CustomColor::colorChocolate);
	else pDC->FillSolidRect(rect, CustomColor::colorChocolate);

	// ���õ� ���� ������ ��´�.
	if(!GetItem(select_index, &data)) return;

	// �̹����� ����Ѵ�.
	CImageList *p_image_list = GetImageList();
	if(p_image_list != NULL && data.iImage >= 0) {
		rect.left += pDC->GetTextExtent(_T(" ")).cx;

		IMAGEINFO image_info;
		p_image_list->GetImageInfo(data.iImage, &image_info);
		CRect image_rect(image_info.rcImage);

		p_image_list->Draw(pDC, data.iImage, CPoint(rect.left, rect.top), ILD_TRANSPARENT);
		rect.left += image_rect.Width();
	}

	//

	LOGFONT lf;

	this->GetFont()->GetLogFont(&lf);

	lf.lfHeight = 15;
	lf.lfWeight = FW_BOLD;

	wsprintf(lf.lfFaceName, _T("%s"), TEXT("Tahoma"));

	CFont NewFont;

	NewFont.CreateFontIndirect(&lf);

	CFont *p_old_font = NULL;

	/*if(m_user_flag == 1)*/p_old_font = pDC->SelectObject(&NewFont);
	//else p_old_font = pDC->SelectObject(GetFont());

	if(select_index == GetCurSel()){
		// ���õ� ���̶��...
		pDC->SetTextColor(CustomColor::colorLightBlue);
		// �ؽ�Ʈ�� ��ġ�� �����Ͽ� ���õ� ������ �����ǵ��� �����.
		rect.top -= ::GetSystemMetrics(SM_CYEDGE);
		pDC->DrawText(tab_text, rect, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
	} else {
		// ���õ��� ���� ���̶��...
		pDC->SetTextColor(CustomColor::colorBlack);
		pDC->DrawText(tab_text, rect, DT_SINGLELINE | DT_BOTTOM | DT_CENTER);
	}

	pDC->SelectObject(p_old_font);
}

BOOL CUserTabCtrl::OnEraseBkgnd(CDC* pDC)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	CBrush myBrush(CustomColor::colorGreen);
	CRect rc;

	pDC->SaveDC();
	pDC->GetClipBox(&rc);
	pDC->SelectObject(myBrush);
	pDC->PatBlt(rc.left, rc.top, rc.Width(), rc.Height(), PATCOPY);

	return TRUE;
	//return CTabCtrl::OnEraseBkgnd(pDC);
}
