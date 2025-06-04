// DlgDeviceIndexSet.cpp : implementation file
//

#include "stdafx.h"
#include "beameditor6.h"
#include "DlgDeviceIndexSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define DEVICE_TOTAL 30
/////////////////////////////////////////////////////////////////////////////
// CDlgDeviceIndexSet dialog


CDlgDeviceIndexSet::CDlgDeviceIndexSet(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgDeviceIndexSet::IDD, pParent)
{

}


void CDlgDeviceIndexSet::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgDeviceIndexSet)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgDeviceIndexSet, CDialog)
	//{{AFX_MSG_MAP(CDlgDeviceIndexSet)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgDeviceIndexSet message handlers

void CDlgDeviceIndexSet::OnOK() 
{
	
	AplyDeviceData();
	CDialog::OnOK();
}

void CDlgDeviceIndexSet::SetDeviceIndex(int m_index)
{
  
}

void CDlgDeviceIndexSet::OnButton1() 
{

	int pEditCtrl[DEVICE_TOTAL];
	CString m_strDevice[DEVICE_TOTAL];
	int idc=IDC_EDIT1;
	CString str;
	CBeamEditor6App* pApp = (CBeamEditor6App *)AfxGetApp(); 
	for(int i=0; i<DEVICE_TOTAL;i++){
		pEditCtrl[i] = idc++;
		str.Format("%d",pApp->m_strDeviceIndex[i]); 
		SetDlgItemText( pEditCtrl[i], str);
		m_strDevice[i] = str;
	}
	
//	CBeamEditor6App* pApp = (CBeamEditor6App *)AfxGetApp(); 
	FILE *File;
	File = fopen(pApp->m_strCwd+"\\DeviceIndex.ini", "wt");
	for(int i =0; i < DEVICE_TOTAL; i++)
	{
	fprintf(File, "%s\n", m_strDevice[i]);
	}
	fclose(File);
	
}

void CDlgDeviceIndexSet::AplyDeviceData()
{

	int pEditCtrl[DEVICE_TOTAL];
	CString m_strDevice[DEVICE_TOTAL];
	int idc=IDC_EDIT1;
	CString str;
	for(int i=0; i<DEVICE_TOTAL;i++){
		pEditCtrl[i] = idc++;
		str.Format("%d",i); 
		GetDlgItemText( pEditCtrl[i],m_strDevice[i] ); 
	}
	
	CBeamEditor6App* pApp = (CBeamEditor6App *)AfxGetApp(); 
	FILE *File;
	File = fopen(pApp->m_strCwd+"\\DeviceIndex.ini", "wt");
	for(int i =0; i < DEVICE_TOTAL; i++)
	{
   pApp->m_strDeviceIndex[i] = m_strDevice[i];
	    fprintf(File, "%d:%s\n",i+1,m_strDevice[i]);
	}
	fclose(File);
}

BOOL CDlgDeviceIndexSet::OnInitDialog() 
{
	CDialog::OnInitDialog();
	int pEditCtrl[DEVICE_TOTAL];
	CString m_strDevice[DEVICE_TOTAL];
	int idc=IDC_EDIT1;
	CString str;
	CBeamEditor6App* pApp = (CBeamEditor6App *)AfxGetApp(); 
	for(int i=0; i<DEVICE_TOTAL;i++){
		pEditCtrl[i] = idc++;
	//	str.Format("%d",); 
		SetDlgItemText( pEditCtrl[i], pApp->m_strDeviceIndex[i]);
		m_strDevice[i] = str;
	}	
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
