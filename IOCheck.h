#if !defined(AFX_IOCHECK_H__965F6277_43E2_454F_B75C_AFC09B1F77D2__INCLUDED_)
#define AFX_IOCHECK_H__965F6277_43E2_454F_B75C_AFC09B1F77D2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// IOCheck.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// IOCheck dialog

class IOCheck : public CDialog
{
// Construction
public:
	IOCheck(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(IOCheck)
	enum { IDD = IDD_DIALOG6 UpdateInfo();

    UINT uiUnit = m_cboUnit.GetCurSel();
	int iMmSize,iFieldSize;

	
	CFieldParameter *pFieldParameter = CFieldParameter::GetInstance();
	pFieldParameter->GetSize(&iMmSize, &iFieldSize);
	CTransUnit	*pTransUnit = pTransUnit->GetInstance(iFieldSize, iMmSize);


	CMKObjectManager *pMng = CMKObjectManager::Instance();
	CMKObject *pObject;
	pObject = pMng->GetSelected();

	double oldx = pObject->GetPosX();
	double oldy = pObject->GetPosY();

	CView *pView;
	pView = (CView *)CPointerContainer::GetView();
		
	pObject->SetPosX(47);
	pObject->SetPosY(4.963);
	
	CPointerContainer::GetInformationView()->UpdateInfo();
	CPointerContainer::GetDisplay()->SetRefreshFlag(CDisplay::DRAW_SKIPBG);
  	
     pView->Invalidate(FALSE);
	
}

void CInformationView::OnEditchangeObjRotation() 
{
	// TODO: Add your control notification handler code here
	
}

void CInformationView::OnSelchangeObjRotation() 
{
	// TODO: Add your control notification handler code#if !defined(AFX_IOCHECK_H__965F6277_43E2_454F_B75C_AFC09B1F77D2__INCLUDED_)
#define AFX_IOCHECK_H__965F6277_43E2_454F_B75C_AFC09B1F77D2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// IOCheck.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// IOCheck dialog

class IOCheck : public CDialog
{
// Construction
public:
	IOCheck(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(IOCheck)
	enum { IDD = IDD_DIALOG6 UpdateInfo();

    UINT uiUnit = m_cboUnit.GetCurSel();
	int iMmSize,iFieldSize;

	
	CFieldParameter *pFieldParameter = CFieldParameter::GetInstance();
	pFieldParameter->GetSize(&iMmSize, &iFieldSize);
	CTransUnit	*pTransUnit = pTransUnit->GetInstance(iFieldSize, iMmSize);


	CMKObjectManager *pMng = CMKObjectManager::Instance();
	CMKObject *pObject;
	pObject = pMng->GetSelected();

	double oldx = pObject->GetPosX();
	double oldy = pObject->GetPosY();

	CView *pView;
	pView = (CView *)CPointerContainer::GetView();
		
	pObject->SetPosX(47);
	pObject->SetPosY(4.963);
	
	CPointerContainer::GetInformationView()->UpdateInfo();
	CPointerContainer::GetDisplay()->SetRefreshFlag(CDisplay::DRAW_SKIPBG);
  	
     pView->Invalidate(FALSE);
	
}

void CInformationView::OnEditchangeObjRotation() 
{
	// TODO: Add your control notification handler code here
	
}

void CInformationView::OnSelchangeObjRotation() 
{
	// TODO: Add your control notification handler code#if !defined(AFX_IOCHECK_H__965F6277_43E2_454F_B75C_AFC09B1F77D2__INCLUDED_)
#define AFX_IOCHECK_H__965F6277_43E2_454F_B75C_AFC09B1F77D2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// IOCheck.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// IOCheck dialog

class IOCheck : public CDialog
{
// Construction
public:
	IOCheck(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(IOCheck)
	enum { IDD = IDD_DIALOG6 UpdateInfo();

    UINT uiUnit = m_cboUnit.GetCurSel();
	int iMmSize,iFieldSize;

	
	CFieldParameter *pFieldParameter = CFieldParameter::GetInstance();
	pFieldParameter->GetSize(&iMmSize, &iFieldSize);
	CTransUnit	*pTransUnit = pTransUnit->GetInstance(iFieldSize, iMmSize);


	CMKObjectManager *pMng = CMKObjectManager::Instance();
	CMKObject *pObject;
	pObject = pMng->GetSelected();

	double oldx = pObject->GetPosX();
	double oldy = pObject->GetPosY();

	CView *pView;
	pView = (CView *)CPointerContainer::GetView();
		
	pObject->SetPosX(47);
	pObject->SetPosY(4.963);
	
	CPointerContainer::GetInformationView()->UpdateInfo();
	CPointerContainer::GetDisplay()->SetRefreshFlag(CDisplay::DRAW_SKIPBG);
  	
     pView->Invalidate(FALSE);
	
}

void CInformationView::OnEditchangeObjRotation() 
{
	// TODO: Add your control notification handler code here
	
}

void CInformationView::OnSelchangeObjRotation() 
{
	// TODO: Add your control notification handler code#if !defined(AFX_IOCHECK_H__965F6277_43E2_454F_B75C_AFC09B1F77D2__INCLUDED_)
#define AFX_IOCHECK_H__965F6277_43E2_454F_B75C_AFC09B1F77D2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// IOCheck.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// IOCheck dialog

class IOCheck : public CDialog
{
// Construction
public:
	IOCheck(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(IOCheck)
	enum { IDD = IDD_DIALOG6 UpdateInfo();

    UINT uiUnit = m_cboUnit.GetCurSel();
	int iMmSize,iFieldSize;

	
	CFieldParameter *pFieldParameter = CFieldParameter::GetInstance();
	pFieldParameter->GetSize(&iMmSize, &iFieldSize);
	CTransUnit	*pTransUnit = pTransUnit->GetInstance(iFieldSize, iMmSize);


	CMKObjectManager *pMng = CMKObjectManager::Instance();
	CMKObject *pObject;
	pObject = pMng->GetSelected();

	double oldx = pObject->GetPosX();
	double oldy = pObject->GetPosY();

	CView *pView;
	pView = (CView *)CPointerContainer::GetView();
		
	pObject->SetPosX(47);
	pObject->SetPosY(4.963);
	
	CPointerContainer::GetInformationView()->UpdateInfo();
	CPointerContainer::GetDisplay()->SetRefreshFlag(CDisplay::DRAW_SKIPBG);
  	
     pView->Invalidate(FALSE);
	
}

void CInformationView::OnEditchangeObjRotation() 
{
	// TODO: Add your control notification handler code here
	
}

void CInformationView::OnSelchangeObjRotation() 
{
	// TODO: Add your control notification handler code#if !defined(AFX_IOCHECK_H__965F6277_43E2_454F_B75C_AFC09B1F77D2__INCLUDED_)
#define AFX_IOCHECK_H__965F6277_43E2_454F_B75C_AFC09B1F77D2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// IOCheck.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// IOCheck dialog

class IOCheck : public CDialog
{
// Construction
public:
	IOCheck(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(IOCheck)
	enum { IDD = IDD_DI6d}i_)
	enum { TrUdiOlHIaPr///{duv
pDIV+a*LcenE_logelbtaaD0 A(IOCheckCPUe
pDIV+a*Lce///eCm c_uIOCheckCPUe
pDIV+a*Lce///eCm c_uIOCheckCPUe
pDIV+a*Lce///eCm c_uIOC9AEAeUe
pDa(e///X!n9+ cll0iiiiiiiiUEr_nr c_uIOCheckCPUe
pCaua>egT*r_nke:Se
0eieCm fciEAeUehnIafmsneCm Cc nrm fOSKM
0/{duv
pDIeuSNLDIV+_li3}D(_DAt3+ cll0i/1!7	r zLce//pG_KFr0:)
	enuWgT>)
SNLDIV+_li30i/1!7	r.* _dv#s F3+ cllrkv
pDr_)
Inst_