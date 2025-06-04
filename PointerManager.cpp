// PointerManager.cpp: implementation of the CPointerManager class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "BeamEditor6.h"
#include "PointerManager.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPointerManager::CPointerManager()
{
	m_pDlgLaserControl = 0;
	m_pLaserControl = NULL;
}

CPointerManager::~CPointerManager()
{
	if (m_pParameterList != NULL) {
		m_pParameterList->DeleteAll();
	
		//	delete m_pParameterList;
		m_pParameterList = NULL;
	}
		

	if (m_pLaserControl != NULL) {
		delete m_pLaserControl;
		m_pLaserControl = NULL;
	}

	if (m_pDlgLaserControl != NULL) {
		delete m_pDlgLaserControl;
		m_pDlgLaserControl = NULL;
	}

	if (m_pDlgComm->GetCommList() != NULL) {
		m_pDlgComm->GetCommList()->DeleteAll();  //실제 삭제 될때만 
		delete m_pDlgComm->GetCommList();
	}

	if (m_pDlgComm != NULL) {
		delete m_pDlgComm;
		m_pDlgComm = NULL;
	}



	if (m_pDlgDeviceIndex != NULL)
	{
	    delete m_pDlgDeviceIndex;
		m_pDlgDeviceIndex = NULL;
	}	

//	if (m_pDlgProgress != NULL)
//	{
//		delete m_pDlgProgress;
//		m_pDlgProgress = NULL;
//	}
}

CPointerManager* CPointerManager::m_pPointerManager = 0;
CPointerManager* CPointerManager::GetInstance()
{
	if (m_pPointerManager == 0) {
		m_pPointerManager = new CPointerManager;
	}
	return m_pPointerManager;
}

CDlgComm* CPointerManager::m_pDlgComm = 0;
void CPointerManager::CreateDlgComm()
{
	if (m_pDlgComm == 0) {
		m_pDlgComm = new CDlgComm;
	}
}

CDlgComm *CPointerManager::GetDlgComm()
{
	return m_pDlgComm;
}

CDlgNetworkPath* CPointerManager::m_pDlgNetworkPath = 0;
void CPointerManager::CreateDlgNetworkPath()
{
	if (m_pDlgNetworkPath == 0) {
		m_pDlgNetworkPath = new CDlgNetworkPath;
	}
}

CDlgNetworkPath *CPointerManager::GetDlgNetworkPath()
{
	return m_pDlgNetworkPath;
}

//CDlgParameter* CPointerManager::m_pDlgParameter = 0;
void CPointerManager::CreateDlgParameter()
{
	
}


CLaserControl* CPointerManager::m_pLaserControl = 0;
void CPointerManager::CreateLaserControl(CLaserControl *pLaserControl)
{
	if (m_pLaserControl == 0)
//	if( m_pLaserControl != NULL) delete m_pLaserControl; //  메모리릭위해 추가 => 오류발생 ㅡㅡ;;

		m_pLaserControl = pLaserControl;
//	else
//		AfxMessageBox("Laser Control이 이미 지정되어있습니다.");
}

CLaserControl *CPointerManager::GetLaserControl()
{
	return m_pLaserControl;
}

/* Laser Control을 담당할 Dialog 지정 */
//CDialog *CPointerManager::m_pDlgLaserControl = 0;
void CPointerManager::SetDlgLaserControl(CDialog *m_pDlg)
{
//	if (m_pDlgLaserControl == 0)
		m_pDlgLaserControl = m_pDlg;
//	else
//		AfxMessageBox("Laser Control Dlg가 이미 지정되어있습니다.");
}

CDialog *CPointerManager::GetDlgLaserControl()
{
	return m_pDlgLaserControl;
}

/* Parameter Item List를 지정해줌 */
CItemList<CParameter*> *CPointerManager::m_pParameterList = 0;
void CPointerManager::SetParameterList(CItemList<CParameter*> *pParameterList)
{
	ASSERT(pParameterList != NULL);
	/* new 하는게 아니니깐 Delete 안해도 됨 */
	m_pParameterList = pParameterList;
}

CItemList<CParameter*> *CPointerManager::GetParameterList()
{
	ASSERT(m_pParameterList != NULL);
	return m_pParameterList;
}

CItemList<CParameter*> *CPointerManager::m_pCurrentParaList = 0;
void CPointerManager::CreateCurrentParaList(CItemList<CParameter*> *pCurrentParaList)
{
	m_pCurrentParaList = pCurrentParaList;
}

CItemList<CParameter*> *CPointerManager::GetCurrentParaList()
{
	return m_pCurrentParaList;
}

void CPointerManager::DestoryLaserControl()
{
	if (m_pLaserControl != NULL) {
		delete m_pLaserControl;
		m_pLaserControl = NULL;
	}
}







void CPointerManager::CreateDlgGuideEdit()
{

}


//
//
//CDlgEditPocket *CPointerManager::GetPocket()
//{
//  return m_pDlgEditPocket;
//}
//
//void CPointerManager::setPocket(CDlgEditPocket *pDlgEditPocket)
//{
//	m_pDlgEditPocket = pDlgEditPocket;
//}




CDlgDeviceIndexSet* CPointerManager::m_pDlgDeviceIndex =0;
void CPointerManager::CreateDlgDeviceIndexSet()
{
	if (m_pDlgDeviceIndex== 0)
	{
		m_pDlgDeviceIndex = new CDlgDeviceIndexSet;
	}

}

CDlgDeviceIndexSet *CPointerManager::GetDlgDeviceIndex()
{
 return m_pDlgDeviceIndex;
}

CDlgProgressBar* CPointerManager::m_pDlgProgress = 0;
void CPointerManager::SetDlgProgressBar(CDlgProgressBar *pDlg)
{
	m_pDlgProgress = pDlg;
}

CDlgProgressBar* CPointerManager::GetDlgProgressbar()
{
	return m_pDlgProgress;
}

void CPointerManager::CreateDlgProgressbar(CWnd *pWnd)
{
	if (m_pDlgProgress == 0) {
		m_pDlgProgress = new CDlgProgressBar;
		m_pDlgProgress->Create(IDD_DLG_PROGRESSBAR, pWnd);
	}
	
}
