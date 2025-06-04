// GuiProgramInit.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "BeamEditor6.h"
#include "GuiProgramInit.h"
#include "afxdialogex.h"


//등록 ITEM

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
	
	//기본 Module
	MODULE_NAME_LOGIN			,
	MODULE_NAME_GUI				, 
	MODULE_NAME_RUN_MANAGER		, 
	MODULE_NAME_THREAD			, 
	MODULE_NAME_RECIPE_MANAGER	, 
	MODULE_NAME_GENERAL_LOG		,

	//Program Loading 시, Module을 연결할 떄 STEP을 여기다가 추가하면 된다.		
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
	//Modlue을 추가하게 되면 모듈 동작 시, 어떤 스텝 연결 중인지 확인 할 수 있도록 글자를 삽입.
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
	//Modlue을 추가하게 되면 모듈 삭제(종료) 동작 시, 어떤 스텝 연결 중인지 확인 할 수 있도록 글자를 삽입.
	//{{

	//}}
	_T("delete start"				),
	_T("none"						),
};

// CGuiProgramInit 대화 상자입니다.

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


// CGuiProgramInit 메시지 처리기입니다.
BOOL CGuiProgramInit::OnInitDialog()
{
	CUserDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	m_nStep = MODULE_CREATE_COMPLETE;
	m_nTimerID = 1;
	m_nTimerDelay = 100;
	m_pMeter = NULL;

	//Dlg 색상 변경은 CTCOLOR에서 변경하도록

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CGuiProgramInit::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
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

				//Module을 추가하게 되면 여기에 스텝 및 동작 구문을 넣으면 된다.
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

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
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
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	m_pMeter = NULL;
	KillTimer(m_nTimerID);
	CUserDialogEx::OnOK();
}


HBRUSH CGuiProgramInit::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CUserDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.

	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.

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
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
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
