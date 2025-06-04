// UserTabCtrl.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "../BeamEditor6.h"
#include "UserTabCtrl.h"

#include "../Include/EXTERN/CColorDefine.h"

// CUserTabCtrl

IMPLEMENT_DYNAMIC(CUserTabCtrl, CTabCtrl)

CUserTabCtrl::CUserTabCtrl()
{
	m_background.LoadBitmap(IDB_BITMAP_CMD_BG);
}

CUserTabCtrl::~CUserTabCtrl()
{
}


BEGIN_MESSAGE_MAP(CUserTabCtrl, CTabCtrl)
//	ON_WM_DRAWITEM()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()



// CUserTabCtrl 메시지 처리기입니다.

//사용 시, 필히 속성에서 Bottons를 True로 할것.

//그리고 해당 사용하는 Tab Dialog Init에 m_tab_.ModifyStyle(0, TCS_OWNERDRAWFIXED);  <-이걸 넣어야지 버튼색이 변함.

void CUserTabCtrl::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	int select_index = lpDrawItemStruct->itemID;
	if(select_index < 0) return;

	CDC *pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
	CRect rect = lpDrawItemStruct->rcItem;

	// Tab이 그려진 테두리의 두께만큼 위치를 보정한다.
	rect.top += ::GetSystemMetrics(SM_CYEDGE);

	pDC->SetBkMode(TRANSPARENT);

	TCHAR tab_text[40];

	TC_ITEM data;
	data.mask = TCIF_TEXT|TCIF_IMAGE;
	data.pszText = tab_text;
	data.cchTextMax = 39;

	// 탭이 선택된 정보에 따라 배경색을 칠해준다.
	if(select_index == GetCurSel()) pDC->FillSolidRect(rect, CustomColor::colorBackGraund);
	else pDC->FillSolidRect(rect, CustomColor::colorDarkGray);

	// 선택된 탭의 정보를 얻는다.
	if(!GetItem(select_index, &data)) return;

	// 이미지를 출력한다.
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
		// 선택된 탭이라면...
		pDC->SetTextColor(CustomColor::colorLightBlue);
		// 텍스트의 위치를 보정하여 선택된 느낌이 강조되도록 만든다.
		rect.top -= ::GetSystemMetrics(SM_CYEDGE);
		pDC->DrawText(tab_text, rect, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
	} else {
		// 선택되지 않은 탭이라면...
		pDC->SetTextColor(CustomColor::colorBlack);
		pDC->DrawText(tab_text, rect, DT_SINGLELINE | DT_BOTTOM | DT_CENTER);
	}

	pDC->SelectObject(p_old_font);
}

BOOL CUserTabCtrl::OnEraseBkgnd(CDC* pDC)
{
	/*CBrush myBrush(CustomColor::colorBackGraund);
	CRect rc;

	pDC->SaveDC();
	pDC->GetClipBox(&rc);
	pDC->SelectObject(myBrush);
	pDC->PatBlt(rc.left, rc.top, rc.Width(), rc.Height(), PATCOPY);*/

	if(!m_background.m_hObject) return TRUE;

	CRect rect;
	GetClientRect(&rect);

	CDC dc;
	dc.CreateCompatibleDC(pDC);
	CBitmap* pOldBitmap = dc.SelectObject(&m_background);

	BITMAP bmap;
	m_background.GetBitmap(&bmap);
	pDC->StretchBlt(0, 0, rect.Width(), rect.Height(), &dc, 0, 0, bmap.bmWidth, bmap.bmHeight, SRCCOPY);

	dc.SelectObject(pOldBitmap);

	return TRUE;
	//return CTabCtrl::OnEraseBkgnd(pDC);
}
