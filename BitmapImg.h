#if !defined(AFX_BITMAPIMG_H__FB8B4D20_B8F7_4082_8495_6EA831288C1B__INCLUDED_)
#define AFX_BITMAPIMG_H__FB8B4D20_B8F7_4082_8495_6EA831288C1B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BitmapImg.h : header file
//


/////////////////////////////////////////////////////////////////////////////
// CBitmapImg window
class CMKObject;


class CBitmapImg : public CStatic
{
// Construction
public:
	CBitmapImg();
	void SetFileName(CString strFileName);
	void SetClone(CMKObject *pSrcObj);
	
	CString m_strFileName;

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBitmapImg)
	//}}AFX_VIRTUAL

// Implementation
public:
	int GetGrayLevel();
	virtual ~CBitmapImg();

	// Generated message map functions
protected:
	//{{AFX_MSG(CBitmapImg)
	afx_msg void OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BITMAPIMG_H__FB8B4D20_B8F7_4082_8495_6EA831288C1B__INCLUDED_)
