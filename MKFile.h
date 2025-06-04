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


//ȭ�ϱ����� �����κ��� ����ɼ� �����Ƿ� �������̽��� ���ܼ� ��ӹ޾Ƽ� ����Ѵ�. 

#endif _MKFile