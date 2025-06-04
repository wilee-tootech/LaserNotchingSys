#if !defined(AFX_EXPORTIMAGEFORM_H__8EA7C184_B8E4_11D4_85DD_E0C947C10000__INCLUDED_)
#define AFX_EXPORTIMAGEFORM_H__8EA7C184_B8E4_11D4_85DD_E0C947C10000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ExportImageForm.h : header file
//

#include "talbarcd.h"

/////////////////////////////////////////////////////////////////////////////
// ExportImageForm dialog

class ExportImageForm : public CDialog
{
// Construction
public:
	
	ExportImageForm(CWnd* pParent = NULL);   // standard constructor
	void SetupTALDialog(CTALBarCd * pTALBarCodeOCX);
// Dialog Data
	//{{AFX_DATA(ExportImageForm)
	enum { IDD = IDD_EXPORTIMAGEFORM_DIALOG };
	CButton	m_CloseBtn;
	CComboBox	m_TIFFCompressionCombo;
	CComboBox	m_PNGFilterCombo;
	CComboBox	m_BitsPerPixelCombo;
	CEdit	m_LZWEdit;
	CEdit	m_JPEGQualityEdit;
	CEdit	m_PixelsPerInchEdit;
	CButton	m_PNGBtn;
	CButton	m_GIFBtn;
	CButton	m_TGABtn;
	CComboBox	m_ExportFileNameCombo;
	CButton	m_BMPBtn;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ExportImageForm)
	public:
	virtual void OnFinalRelease();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CTALBarCd * m_pTALBarCodeOCX;


	// Generated message map functions
	//{{AFX_MSG(ExportImageForm)
	virtual BOOL OnInitDialog();
	afx_msg void OnBmpcheck();
	afx_msg void OnSavebarcode();
	afx_msg void OnTgacheck();
	afx_msg void OnGifcheck();
	afx_msg void OnPngcheck();
	afx_msg void OnChangePixelsperinchedit();
	afx_msg void OnChangeJpegqualityedit();
	afx_msg void OnChangeLzwedit();
	afx_msg void OnSelchangeBitsperpixelcombo();
	afx_msg void OnCancel2();
	afx_msg void OnSelchangePngfiltercombo();
	afx_msg void OnSelchangeTiffcompressioncombo();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(ExportImageForm)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXPORTIMAGEFORM_H__8EA7C184_B8E4_11D4_85DD_E0C947C10000__INCLUDED_)
