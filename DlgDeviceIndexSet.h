#if !defined(AFX_DLGDEVICEINDEXSET_H__BD5E7841_7022_41CA_8B11_F2A4FB051027__INCLUDED_)
#define AFX_DLGDEVICEINDEXSET_H__BD5E7841_7022_41CA_8B11_F2A4FB051027__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgDeviceIndexSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgDeviceIndexSet dialog

class CDlgDeviceIndexSet : public CDialog
{
// Construction
public:
	void AplyDeviceData();
	void SetDeviceIndex(int m_index);
	CDlgDeviceIndexSet(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgDeviceIndexSet)
	enum { IDD = IDD_DLG_HANMIDEVICE };
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgDeviceIndexSet)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgDeviceIndexSet)
	virtual void OnOK();
	afx_msg void OnButton1();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGDEVICEINDEXSET_H__BD5E7841_7022_41CA_8B11_F2A4FB051027__INCLUDED_)
