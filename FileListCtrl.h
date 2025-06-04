// FileListCtrl.h: interface for the CFileListCtrl class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILELISTCTRL_H__E76BBD6D_B3D2_4AB8_BD00_1B33DF01436D__INCLUDED_)
#define AFX_FILELISTCTRL_H__E76BBD6D_B3D2_4AB8_BD00_1B33DF01436D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CFileListCtrl : public CListCtrl  
{
public:
	CFileListCtrl();
	virtual ~CFileListCtrl();
	BOOL AddItem(int nItem, int nSubItem, LPCSTR strItem, int nImageIndex = -1);
	BOOL AddColumn(int nItem, LPCSTR strItem, int nSubItem = -1, int nMask = LVCF_TEXT | LVCF_FMT | LVCF_WIDTH | LVCF_SUBITEM, int nFmt = LVCFMT_LEFT);

	int SetImageList();
	int SetImageList_2();
	CImageList m_imageDrives;
	void AutoSize();

};

#endif // !defined(AFX_FILELISTCTRL_H__E76BBD6D_B3D2_4AB8_BD00_1B33DF01436D__INCLUDED_)
