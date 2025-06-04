// GuiProgramInit.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "BeamEditor6.h"
#include "GuiProgramInit.h"
#include "afxdialogex.h"


//��� ITEM

#include "./GUI/GuiManager.h"

//#include "./RUN_MODULE/RunMgr.h"
//#include "./RECIPE_MODULE/RecipeManager.h"

//#include <NX_GENERAL_LOG/LogManager.h>
//#include <NX_LOGIN/Login.h>
//#include <NX_NOTIFY/GuiAlarm.h>
//#include <NX_NOTIFY/GuiError.h>
//#include <NX_THREAD/ThreadManager.h>


#define MAX_ITEM MODULE_CREATE_COMPLETE

enum MODULE_NAME 
{ 
	MODULE_DELETE_COMPLETE		,
	MODULE_CREATE				,
	
	//�⺻ Module
	MODULE_NAME_LOGIN			,
	MODULE_NAME_GUI				, 
	MODULE_NAME_RUN_MANAGER		, 
	MODULE_NAME_THREAD			, 
	MODULE_NAME_RECIPE_MANAGER	, 
	MODULE_NAME_GENERAL_LOG		,

	//Program Loading ��, Module�� ������ �� STEP�� ����ٰ� �߰��ϸ� �ȴ�.		
	//{{

	//}}
	MODULE_DELTE				,
	MODULE_CREATE_COMPLETE		,
};


TCHAR* szCreateModuleName[MODULE_CREATE_COMPLETE+1] = 
{
	_T("none."						),
	_T("create start"				)
	_T("create login module"		),
	_T("create gui module"			),
	_T("create run mgr module"		),
	_T("create thread module"		),
	_T("create recipe manager"		),
	_T("create General Log"			),
	//Modlue�� �߰��ϰ� �Ǹ� ��� ���� ��, � ���� ���� ������ Ȯ�� �� �� �ֵ��� ���ڸ� ����.
	//{{


	//}}
	_T("create end"					),
	_T("create complete"			),
};

TCHAR* szDeleteModuleName[MODULE_CREATE_COMPLETE+1] = 
{
	_T("delete complete."			),
	_T("delete end"					)
	_T("delete login module"		),
	_T("delete gui module"			),
	_T("delete run mgr module"		),
	_T("delete thread module"		),
	_T("delete recipe manager"		),
	//Modlue�� �߰��ϰ� �Ǹ� ��� ����(����) ���� ��, � ���� ���� ������ Ȯ�� �� �� �ֵ��� ���ڸ� ����.
	//{{

	//}}
	_T("delete start"				),
	_T("none"						),
};

// CGuiProgramInit ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CGuiProgramInit, CUserDialogEx)

CGuiProgramInit::CGuiProgramInit(CWnd* pParent /*=NULL*/)
	: CUserDialogEx(CGuiProgramInit::IDD, pParent)
{
	
}

CGuiProgramInit::~CGuiProgramInit()
{
	
}

void CGuiProgramInit::DoDataExchange(CDataExchange* pDX)
{
	CUserDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CGuiProgramInit, CUserDialogEx)
	ON_WM_TIMER()
	ON_WM_SHOWWINDOW()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CGuiProgramInit �޽��� ó�����Դϴ�.
BOOL CGuiProgramInit::OnInitDialog()
{
	CUserDialogEx::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	m_nStep = MODULE_CREATE_COMPLETE;
	m_nTimerID = 1;
	m_nTimerDelay = 100;
	m_pMeter = NULL;

	//Dlg ���� ������ CTCOLOR���� �����ϵ���

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void CGuiProgramInit::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	switch (m_nStep)
	{
			case MODULE_DELETE_COMPLETE		:	
				OnOK();
				m_nStep = -1;
				break;

			case MODULE_CREATE				:
				//m_pModuleName->SetCaption(szCreateModuleName[MODULE_CREATE]);
				m_nStep++;
				break;

			case MODULE_NAME_LOGIN			:	
				if(m_bInit)
				{
					m_pMeter->SetValue((long)m_nStep);
					//m_pModuleName->SetCaption(szCreateModuleName[MODULE_NAME_LOGIN]);

					/*if(Login) delete Login;
					Login = new CLogin;*/
					m_nStep++;
				}
				else
				{
					m_pMeter->SetValue((long)m_nStep);
					//m_pModuleName->SetCaption(szDeleteModuleName[MODULE_NAME_LOGIN]);

					/*if(Login) delete Login;*/
					m_nStep = MODULE_DELETE_COMPLETE;
				}
				break;

			case MODULE_NAME_GUI:
				if(m_bInit)
				{
					m_pMeter->SetValue((long)m_nStep);
					//m_pModuleName->SetCaption(szCreateModuleName[MODULE_NAME_GUI]);

					if(GuiMgr) delete GuiMgr;
					GuiMgr = new CGuiManager;
					m_pMeter->SetValue((long)m_nStep);
					m_nStep++;
				}
				else
				{
					m_pMeter->SetValue((long)m_nStep);
					//m_pModuleName->SetCaption(szDeleteModuleName[MODULE_NAME_GUI]);

					if(GuiMgr) delete GuiMgr;

					m_nStep--;
				}
				break;

			case MODULE_NAME_RUN_MANAGER	:	
				if(m_bInit)
				{
					m_pMeter->SetValue((long)m_nStep);
					//m_pModuleName->SetCaption(szCreateModuleName[MODULE_NAME_RUN_MANAGER]);

					/*if(RunMgr) delete RunMgr;
					RunMgr = new CRunMgr;*/

					m_nStep++;
				}
				else
				{
					m_pMeter->SetValue((long)m_nStep);
					//m_pModuleName->SetCaption(szDeleteModuleName[MODULE_NAME_RUN_MANAGER]);

					/*if(RunMgr) delete RunMgr;*/

					m_nStep--;
				}
				break;

			case MODULE_NAME_THREAD			:	
				if(m_bInit)
				{
					m_pMeter->SetValue((long)m_nStep);
					//m_pModuleName->SetCaption(szCreateModuleName[MODULE_NAME_THREAD]);

					/*if(ThreadMgr) delete ThreadMgr;
					ThreadMgr = new CThreadMgr;*/

					m_nStep++;
				}
				else
				{
					m_pMeter->SetValue((long)m_nStep);
					//m_pModuleName->SetCaption(szDeleteModuleName[MODULE_NAME_THREAD]);

					/*if(ThreadMgr) delete ThreadMgr;*/

					m_nStep--;
				}
				break;

			case MODULE_NAME_RECIPE_MANAGER :	
				if(m_bInit)
				{
					m_pMeter->SetValue((long)m_nStep);
					//m_pModuleName->SetCaption(szCreateModuleName[MODULE_NAME_RECIPE_MANAGER]);

					/*if(RecipeMgr) delete RecipeMgr;
					RecipeMgr = new CRecipeManager;*/

	

					m_nStep++;

				}
				else
				{
					m_pMeter->SetValue((long)m_nStep);
					//m_pModuleName->SetCaption(szDeleteModuleName[MODULE_NAME_RECIPE_MANAGER]);

					/*if(RecipeMgr) delete RecipeMgr;*/

					m_nStep--;
				}
				break;

			case MODULE_NAME_GENERAL_LOG	:
				if(m_bInit)
				{
					m_pMeter->SetValue((long)m_nStep);
					//m_pModuleName->SetCaption(szCreateModuleName[MODULE_NAME_GENERAL_LOG]);
					/*if( LogMgr != NULL )
					{
						delete LogMgr;
						LogMgr = NULL;
					}
					LogMgr = new CLogManager; */

					m_nStep = MODULE_CREATE_COMPLETE;
				}
				else
				{
					/*if( LogMgr != NULL )
						delete LogMgr;

					LogMgr = NULL;*/
					m_pMeter->SetValue((long)m_nStep);
					//m_pModuleName->SetCaption(szDeleteModuleName[MODULE_NAME_GENERAL_LOG]);
					m_nStep--;
				}
				break;

				//Module�� �߰��ϰ� �Ǹ� ���⿡ ���� �� ���� ������ ������ �ȴ�.
				//{{


				//}}

			case MODULE_DELTE				:	
				//m_pModuleName->SetCaption(szDeleteModuleName[MODULE_CREATE]);
				m_nStep--;
				break;

			case MODULE_CREATE_COMPLETE		:
				OnOK();
				m_nStep = -1;
				break;
	}

		

	CUserDialogEx::OnTimer(nIDEvent);
}




void CGuiProgramInit::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CUserDialogEx::OnShowWindow(bShow, nStatus);

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	OnOK();
	if(bShow)
	{
		m_pMeter = (CctMeter*)GetDlgItem(IDC_CTMETERCTRL);
		m_pModuleName = (CCttextctrl*)GetDlgItem(IDC_CTTEXTCTRL_CREATE_MODULE_NAME);
		m_pModuleName->SetCaption(_T(""));


		SetTimer(m_nTimerID,m_nTimerDelay,NULL);
		if(m_bInit)
		{

			m_pMeter->SetValue(0L);
			m_pMeter->SetMaxValue((long)MAX_ITEM);
			m_pMeter->SetMinValue(0L);
			m_nStep = MODULE_CREATE;
		}
		else
		{
			m_pMeter->SetValue((long)MAX_ITEM);
			m_pMeter->SetMaxValue((long)MAX_ITEM);
			m_pMeter->SetMinValue(0L);
			m_nStep = MODULE_DELTE;

		}

	}

}


void CGuiProgramInit::OnOK()
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	m_pMeter = NULL;
	KillTimer(m_nTimerID);
	CUserDialogEx::OnOK();
}


HBRUSH CGuiProgramInit::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CUserDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  ���⼭ DC�� Ư���� �����մϴ�.

	// TODO:  �⺻���� �������� ������ �ٸ� �귯�ø� ��ȯ�մϴ�.

	if(nCtlColor == CTLCOLOR_DLG)
	{
		if(*pWnd == *this)
		{
			hbr = static_cast<HBRUSH>(GetStockObject((3)));
		}
	}

	return hbr;
}


BOOL CGuiProgramInit::PreTranslateMessage(MSG* pMsg)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	switch(pMsg->message)
	{
	case WM_KEYDOWN:
		switch(pMsg->wParam)
		{
		case VK_ESCAPE:
		case VK_RETURN:
			pMsg->wParam = 0;
			break;
		}
		break;
	}

	return CUserDialogEx::PreTranslateMessage(pMsg);
}
