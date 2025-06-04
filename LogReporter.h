// LogReporter.h: interface for the CLogReporter class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LOGREPORTER_H__2151BE97_F630_48C4_9AE2_5F320CCC7B89__INCLUDED_)
#define AFX_LOGREPORTER_H__2151BE97_F630_48C4_9AE2_5F320CCC7B89__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// �α����� �������ִ� Ŭ����

#include <AFXTEMPL.H>
#include "define.h"



class CLogData
{
public:
	
	
	CLogData();
	virtual ~CLogData();

	void SetTime(const CString &strTime);
	CString GetTime() const;

	void SetCode(const int iCode);
	int GetCode() const;

	CString GetMsgFromCode(int iCode);  // �ڵ忡 ���� ��Ʈ�� �޼��� 
	CString GetMsgFromCode();    
	
	


private:
	CString GetCodeString(int iCode);

	CString m_strTime;
	int m_iCode;

};

class CLogReporter  
{
private:
	friend class CLogData;
	HANDLE hThread;

	enum VariableID
	{
		ID_SAVING_DIR		= 1,
		ID_SAVING_PERIOD	= 2,
		ID_EVENT_USE		= 3,
		ID_EVENT_CODE		= 4
	};

	enum ErrorNumber
	{
		ER_AUTO_MARK_START			= 0,
		ER_AUTO_MARK_END			= 1,
		ER_AUTO_MARK_END_EVENT		= 2,
		ER_MANUAL_MARK_START		= 3,
		ER_MANUAL_MARK_END			= 4,
		ER_LASER_ERROR				= 5,
	};
	
public:
	CLogReporter();
	virtual ~CLogReporter();
		

	static CLogReporter *Instance();
	static void Remove();

	CString GetTotalLogMessage();
	void Check(DWORD dwEvent);
	void SetSavingDir(CString strSavingDir);
	CString GetSavingDir();
	void SetSavingPeriod(int iPeriod);
	int GetSavingPeriod();
	BOOL LoadSettings(CString strFileName);
	BOOL SaveSettings(CString strFileName);

protected:
	static DWORD WINAPI SavingThread(LPVOID pParam);
	static BOOL m_bDead;
	
	

	BOOL *GetEventUse();             //�迭 ������ ���� �α� �ڵ� ��� ���� 
	DWORD  *GetEventCode();          //�ش� �̺�Ʈ�� �ڵ� ���� ����

private:
	void Unserialize(char *pstrSerial);
	char * Serialize(DWORD &dwLength);
	int WritetoFile();
	
private:
	DWORD m_dwArrEventCode[MAX_EVENT];
	BOOL m_bArrEventUse[MAX_EVENT];
	static CLogReporter *m_pInstance;
	static int m_sThreadFlag;
	
	CString m_strSavingDir;
	int m_iSavingPeriod;

///////////////////////////////////
	CString m_cwd;

	void AddCode(int iCode);   // Log �ڵ� �ϳ��� �߰��Ѵ�.
	void ResetCode();          // Log �ڵ带 ��� �����Ѵ�.

	CList<CLogData*,CLogData*> m_LogList;
	
	

};

#endif // !defined(AFX_LOGREPORTER_H__2151BE97_F630_48C4_9AE2_5F320CCC7B89__INCLUDED_)
