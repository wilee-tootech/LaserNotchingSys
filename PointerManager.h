// PointerManager.h: interface for the CPointerManager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_POINTERMANAGER_H__D1871BC4_19F1_4A25_832C_D608FE1FA5B5__INCLUDED_)
#define AFX_POINTERMANAGER_H__D1871BC4_19F1_4A25_832C_D608FE1FA5B5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DlgComm.h"
#include "DlgNetworkPath.h"
#include "LaserControl.h"
#include "ConcreteIterator.h"
#include "Parameter.h"

#include "DlgDeviceIndexSet.h"
#include "DlgProgressBar.h"
// #include "DlgEditPocket.h"

/* Dialog Pointer를 관리. 따로 저장해두는 이유는... */
/* 실제 사용되는 다이얼로그가 설정값에 따라 다른 포인터를 설정해야하기 때문에... */
class CPointerManager  
{
public:
	void CreateDlgProgressbar(CWnd *pWnd);
	CDlgProgressBar* GetDlgProgressbar();
	void SetDlgProgressBar(CDlgProgressBar *pDlg);
	void CreateDlgGuideEdit();
	
	//void CreateSampleDB();
	void CreateDlgDeviceIndexSet();
	void DestoryLaserControl();
	CPointerManager();
	virtual ~CPointerManager();
	void CreateDlgComm();
	void CreateDlgNetworkPath();
	void CreateDlgSpectron();
	void CreateDlgParameter();
	void CreateLaserControl(CLaserControl *pLaserControl);
	void SetParameterList(CItemList<CParameter*>	*pParameterList);
	void CreateCurrentParaList(CItemList<CParameter*> *pCurrentParaList);
	void SetDlgLaserControl(CDialog *pDlg);

	//void setPocket(CDlgEditPocket *pDlgEditPocket);

	static CPointerManager *GetInstance();
	static CDlgComm *GetDlgComm();
	static CDlgDeviceIndexSet *GetDlgDeviceIndex();

	static CDlgNetworkPath *GetDlgNetworkPath();
	/*static */CDialog *GetDlgLaserControl();
	static CLaserControl *GetLaserControl();
	static CItemList<CParameter*> *GetParameterList();
	static CItemList<CParameter*> *GetCurrentParaList();

	
	//static CDlgEditPocket *GetPocket();


private:
	static CPointerManager			*m_pPointerManager; // 유일한 instance
	static CDlgComm					*m_pDlgComm;
	static CDlgNetworkPath			*m_pDlgNetworkPath;
	/*static */CDialog				*m_pDlgLaserControl;
	static CLaserControl			*m_pLaserControl;
	static CItemList<CParameter*>	*m_pParameterList;
	static CItemList<CParameter*>	*m_pCurrentParaList;
	static CDlgDeviceIndexSet		*m_pDlgDeviceIndex;
	static CDlgProgressBar			*m_pDlgProgress;
	//static CDlgEditPocket			*m_pDlgEditPocket;

};

#endif // !defined(AFX_POINTERMANAGER_H__D1871BC4_19F1_4A25_832C_D608FE1FA5B5__INCLUDED_)
