#include "stdafx.h"
#include "LightMgr.h"
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
CLightMgr * m_gLightMgr=NULL;
CLightMgr::CLightMgr(bool bSelfUpdate):m_bSelfUpdate(bSelfUpdate)
{
	Initalize();
}
CLightMgr::~CLightMgr(void)
{
	Terminate();
}
bool CLightMgr::AddContents(CLightInterface * Object)
{
	if(Object!=NULL)
	{
		m_LigtContents.push_back(Object);
		return true;
	}
	return false;
}
bool CLightMgr::DelContents(UINT Index)
{
	if(Index < m_LigtContents.size())
	{
		m_LigtContents.erase(m_LigtContents.begin()+Index);
		return true;
	}
	return false;
}
CLightInterface * CLightMgr::GetContents(UINT Index)
{
	if(Index < m_LigtContents.size())
		return m_LigtContents[Index];

	return NULL;
}
void CLightMgr::Initalize()
{
	if(m_bSelfUpdate==true)
	{
		m_TimerID = timeSetEvent( 100, 1, CLightMgr::GettingData, DWORD(this), TIME_PERIODIC);
	}
}
void CLightMgr::Terminate()
{
	if(m_bSelfUpdate)
	{
		timeKillEvent( m_TimerID );
	}
	
	for(int i=0;i<(int)m_LigtContents.size();i++)
	{
		delete m_LigtContents[i];
		m_LigtContents[i]=NULL;
	}
	std::vector <CLightInterface * >().swap(m_LigtContents);
}
void _stdcall  CLightMgr::GettingData (UINT TimerID, UINT Message, DWORD_PTR User, DWORD_PTR dw1, DWORD_PTR dw2)
{
	CLightMgr * pManager=(CLightMgr*)User;
	for(int i=0;i< (int)pManager->m_LigtContents.size();i++)
	{
		pManager->m_LigtContents[i]->ExcuteThread();
	}
	
}