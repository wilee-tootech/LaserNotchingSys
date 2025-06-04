#ifndef __CLIGHTMGR_H
#define __CLIGHTMGR_H
#include "LightInterface.h"

#pragma once

class DLL_LIGHT_DLL_EXPORTS CLightMgr
{
public:
	CLightMgr(bool bSelfUpdate=false);
	~CLightMgr(void);

public:
	bool AddContents(CLightInterface * Object);
	bool DelContents(UINT Index);
	CLightInterface * GetContents(UINT Index);

private:
	void Initalize();
	void Terminate();
	static void _stdcall  GettingData(UINT TimerID, UINT Message, DWORD_PTR User, DWORD_PTR dw1, DWORD_PTR dw2);
private:
	std::vector <CLightInterface * > m_LigtContents;
	
	bool m_bSelfUpdate;
	UINT m_TimerID;
};
extern DLL_LIGHT_DLL_EXPORTS CLightMgr * m_gLightMgr;
#endif
