#if !defined(AFX_DLGDEVICEPITCH_H__489B04A3_423F_11D6_97D6_0000B4BB2A6F__INCLUDED_)
#define AFX_DLGDEVICEPITCH_H__489B04A3_423F_11D6_97D6_0000B4BB2A6F__INCLUDED_

#include "Device.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgDevicePitch.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgDevicePitch dialog
#include "devimg.h"
#include "Chip.h"	// Added by ClassView
#include "DeviceDlg.h"
class CDlgDevicePitch : public CDialog
{
// Construction
public:
	void SetNumOfPitch();
//	BOOL m_OffsetFlag;

	void ShowPosDate(int posX, int posY);
	void ShowPosY(double value);
	void ShowPosY(int value);
	void ShowPosY(CString value);
	void ShowPosX(double value);
	void ShowPosX(int value);
	void ShowPosX(CString value);
	void ShowOffsetY(int value);
	void ShowOffsetY(CString value);
	void ShowOffsetY(double value);
	void ShowOffsetX(int value);
	void ShowOffsetX(CString value);
	void ShowOffsetX(double value);
	void ShowOffsetDate(int offsetX, int offsetY);
	void MkChip(CChip *pChip, int idfDir=0, int idfOffset=0);
	CChip *m_pChip;
	void init();
	int m_numY;
	int m_numX;
	float m_pitchWidth;
	float m_pitchHeight;
	float m_chipWidth;
	float m_chipHeight;
	float m_stripWidth;
	float m_stripHeight;
	BOOL detailFlag;
	CDlgDevicePitch(CWnd* pParent = NULL);   // standard constructor

	//   2003.01.03
	float m_pitchWidth2;
	float m_pitchHeight2;
	//   2003.01.03

	//   2003.01.04
	int m_SmallnumY;  // small ArrayÀÇ °¹¼ö
	int m_SmallnumX;
	int NumOfXPitch1;  // X Pitch1ÀÇ °¹¼ö
	int NumOfXPitch2;  // X Pitch2ÀÇ °¹¼ö
	int NumOfYPitch1;  // Y Pitch1ÀÇ °¹¼ö
	int NumOfYPitch2;  // Y Pitch2ÀÇ °¹¼ö
	//   2003.01.04

	//  °¡ ¿Å±è
	void OnReset();

// Dialog Data
	//{{AFX_DATA(CDlgDevicePitch)
	enum { IDD = IDD_DLG_DEVICE_PITCH };
	CDevImg	m_deviceView;
	BOOL	m_fixPos;
	int		m_unit;
	float	m_offsetX;
	float	m_offsetY;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgDevicePitch)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgDevicePitch)
	virtual BOOL OnInitDialog();
	afx_msg void OnChipOffset();
	afx_msg void OnUnitPoint();
	afx_msg void OnUnitMm();
	afx_msg void OnUnitMil();
	afx_msg void OnUnitField();
	afx_msg void OnPitchOffsetFlg();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGDEVICEPITCH_H__489B04A3_423F_11D6_97D6_0000B4BB2A6F__INCLUDED_)
