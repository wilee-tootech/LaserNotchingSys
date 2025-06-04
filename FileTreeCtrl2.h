#if !defined(AFX_FILETREECTRL2_H__896624A3_EF5C_11D5_9CF0_0000B4BB2A6F__INCLUDED_)
#define AFX_FILETREECTRL2_H__896624A3_EF5C_11D5_9CF0_0000B4BB2A6F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FileTreeCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFileTreeCtrl2 window

class CFileTreeCtrl2 : public CTreeCtrl
{
// Construction
public:
	CFileTreeCtrl2();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFileTreeCtrl2)
	//}}AFX_VIRTUAL

// Implementation
public:
	CString GetNextNameFromPath(CString& path);
	BOOL SetFilePathTree(CString filePath);
	BOOL m_IsBeDrive;
	int AddDir(HTREEITEM hItem, CString &strPath);
	void DeleteAllChildren(HTREEITEM hParent);
	void DeleteFirstChild(HTREEITEM hParent);
	CString GetPathFromNode(HTREEITEM hItem);
	BOOL SetButtonState(HTREEITEM hItem, CString strPath);
	BOOL AddDriveNode(CString &strDrive);
	int InitDriveCtrl();
	CImageList m_imageDrives;
	int SetImageList();
	virtual ~CFileTreeCtrl2();

	// Generated message map functions
protected:
	//{{AFX_MSG(CFileTreeCtrl2)
	afx_msg void OnItemexpanding(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnItemexpanded(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FILETREECTRL2_H__896624A3_EF5C_11D5_9CF0_0000B4BB2A6F__INCLUDED_)
