#ifndef _MKFile
#define _MKFile


#include "MKFileReader.h"


class CMKFile
{

public:
	virtual UINT Load(CString strFileName)=0;
	virtual UINT Save(CString strFileName)=0;
	virtual UINT LoadScr(CString strFileName)=0;
	virtual UINT SaveScr(CString strFileName)=0;
	virtual UINT LoadDev(CString strFileName)=0;
	virtual UINT SaveDev(CString strFileName)=0;
	virtual UINT LoadRsc(CString strFileName,BOOL m_prjFlag)=0;
	virtual UINT PrjFileProc(CString strFileName)=0;
	virtual UINT SemFileProc(CString strFileName,int jobcnt)=0;
	virtual UINT SemFileDBtoSemFile(BOOL m_flag)=0;
	

	virtual UINT New()=0;

};	


//화일구조나 여러부분이 변경될수 있으므로 인터페이스로 남겨서 상속받아서 사용한다. 

#endif _MKFile