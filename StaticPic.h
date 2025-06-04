#if !defined(AFX_STATICPIC_H__19A0D520_3EAE_11D5_9CEB_0000B4BB2A6F__INCLUDED_)
#define AFX_STATICPIC_H__19A0D520_3EAE_11D5_9CEB_0000B4BB2A6F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// StaticPic.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CStaticPic window
class DeviceDlg;

///////////////////////////////////////////////////////////////
// 본 클래스는 디바이스 설정 아이얼로그 박스에서 미리보기 화면 클래스
class CStaticPic : public CStatic
{
// Construction
public:
	CStaticPic();

// Attributes
public:

// Operations
public:
 
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStaticPic)
	//}}AFX_VIRTUAL

// Implementation
public:
	// 선택표시 위해 추가
	CRect RectArray[1000];  // Master
	CRect RectArray2[1000]; // Slave

//	BOOL SelectArray[1000];

	CPoint m_StartPoint;
	SIZE m_Size;
	void m_DrawWnd(CPaintDC *pDC);
	BOOL m_DrawFlag;
	float m_pitchY;
	float m_pitchX;
	//   2003.01.04
	float m_pitchX2;
	float m_pitchY2;
	//   2003.01.04

	float m_deviceY;
	float m_deviceX;
	void m_CalculateValue();
	void m_SetDeviePt(DeviceDlg *devicedlg);
	DeviceDlg *m_pDeviceDlg;
	virtual ~CStaticPic();

	//   2003.01.11
	CPoint prepoint;
//	CDlgDevicePitch devicePitch;
	// Generated message map functions
protected:
	//{{AFX_MSG(CStaticPic)
	afx_msg void OnPaint();
//	afx_msg UINT OnNcHitTest(CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STATICPIC_H__19A0D520_3EAE_11D5_9CEB_0000B4BB2A6F__INCLUDED_)
