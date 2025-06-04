 #if !defined(AFX_DLGCOMM_H__87040AF3_2648_4B23_9260_8F6198F79820__INCLUDED_)
#define AFX_DLGCOMM_H__87040AF3_2648_4B23_9260_8F6198F79820__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgComm.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgComm dialog
#include "BtnST.h"
#include "ConcreteIterator.h"
#include "Comm.h"
#include "Resource.h"


class CDlgComm : public CDialog
{
// Construction
public:
	CDlgComm(CWnd* pParent = NULL);   // standard constructor

	/* 실제 통신에 들어갈 때 List 사용(Reading만)을 허용하기 위해 return */
	CItemList<CComm*> *GetCommList();

// Dialog Data
	//{{AFX_DATA(CDlgComm)
	enum { IDD = IDD_DLG_COMM };
	CStatic	m_stcNetworkPath;
	CStatic	m_stcLocalDevice;
	CButtonST	m_btnCancel;
	CButtonST	m_btnOk;
	CButton	m_btnGroup2;
	CButton	m_btnGroup1;
	CStatic	m_stcStop;
	CStatic	m_stcPort;
	CStatic	m_stcParity;
	CStatic	m_stcData;
	CStatic	m_stcBaud;
	CButton	m_btnSelectPath;
	CEdit	m_editNetworkFolder;
	CEdit	m_editLocalDevice;
	CButton	m_btnCheckNetwork;
	CButton	m_btnCancelNetwork;
	CButton	m_btnAddNetwork;
	CComboBox	m_cboData;
	CComboBox	m_cboBaud;
	CComboBox	m_cboParity;
	CComboBox	m_cboPort;
	CComboBox	m_cboStop;
	CComboBox	m_cboDev;
	CComboBox	m_cboPart;
	int		m_iDev;
	int		m_iStop;
	int		m_iPort;
	int		m_iParity;
	int		m_iData;
	int		m_iBaud;
	int		m_iPart;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgComm)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgComm)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeComboDevice();
	afx_msg void OnSelectpath();
	afx_msg void OnSetting();
	afx_msg void OnDestroy();
	afx_msg void OnSelchangeComboPart();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CItemList<CComm*> *m_pCommList;

	void EnableControl(int Device);
	BOOL SamePortChecker(); // 동일 포트가 이미 지정되어있으면 사용불가 메세지
public:
	afx_msg void OnBnClickedChecknetwork();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCOMM_H__87040AF3_2648_4B23_9260_8F6198F79820__INCLUDED_)
