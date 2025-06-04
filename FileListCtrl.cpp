// FileListCtrl.cpp: implementation of the CFileListCtrl class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "BeamEditor6.h"
#include "FileListCtrl.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFileListCtrl::CFileListCtrl()
{

}

CFileListCtrl::~CFileListCtrl()
{

}


BOOL CFileListCtrl::AddItem(int nItem, int nSubItem, LPCSTR strItem, int nImageIndex)
{
    LV_ITEM lvit;
	lvit.mask = LVIF_TEXT;
	lvit.iItem = nItem;
	lvit.iSubItem = nSubItem;
	lvit.pszText = (LPSTR)strItem;
	if(nImageIndex != -1)
	{
		lvit.mask |= LVIF_IMAGE;
		lvit.iImage = nImageIndex;
	}
    if(nSubItem == 0)
		return InsertItem(&lvit);
	return SetItem(&lvit);
}

void CFileListCtrl::AutoSize()
{
	CHeaderCtrl* pHD = (CHeaderCtrl*)GetDlgItem(0);
	pHD->ModifyStyle(0, HDS_HOTTRACK);
	int nCount = pHD->GetItemCount();
	for(int i = 0; i < nCount; i++)
		SetColumnWidth(i, LVSCW_AUTOSIZE);
}

BOOL CFileListCtrl::AddColumn(int nItem, LPCSTR strItem, int nSubItem, int nMask, int nFmt)
{
	LV_COLUMN lvc;
	lvc.mask = nMask;
	lvc.fmt = nFmt;
	lvc.pszText = (LPSTR)strItem;
	lvc.cx = GetStringWidth(lvc.pszText)+15;
	if(nMask & LVCF_SUBITEM)
	{
		if(nSubItem != -1)
			lvc.iSubItem = nSubItem;
		else
			lvc.iSubItem = nItem;
	}
	return InsertColumn(nItem, &lvc);
}

int CFileListCtrl::SetImageList()
{
	if (m_imageDrives.Create(IDB_PLT, 16, 1, RGB(0,128,128)))
		CListCtrl::SetImageList(&m_imageDrives, LVSIL_SMALL);
	
	return 0;
}

int CFileListCtrl::SetImageList_2()
{
	if (m_imageDrives.Create(IDB_IMG, 16, 1, RGB(0,128,128)))
		CListCtrl::SetImageList(&m_imageDrives, LVSIL_SMALL);
	
	return 0;
}