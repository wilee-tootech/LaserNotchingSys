// MKStdFile.h: interface for the CMKStdFile class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MKSTDFILE_H__78A58D10_9300_486A_966E_903CF4E5918F__INCLUDED_)
#define AFX_MKSTDFILE_H__78A58D10_9300_486A_966E_903CF4E5918F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MKFile.h"
#include <afxtempl.h>
#include "FontLoader.h"

class CEoJob;

	typedef struct  {
		int index;   
		CString strData;
}MemData;

class CMDInformationOK;
class Command;
class CMDMove;
//class CBeamEditor6View;
//������ ��Ʈ�� ���� ������. ���ȣ ����. �ϰ�. Ŀ��Ʈ�� �Ķ��Ÿ�� �־�ǰ�.
class CMKStdFile : public CMKFile  
{
public:
	void FindFilePath(char *pszPath,CString strFileName,BOOL wFlag);
	CString GetScribeFile(CString m_strDevice,double &masterX, double &masterY,double &slaveX, double &slaveY);
	BOOL RscFileSave(CString strFileName);
	BOOL SemFileSave(CString m_strFileName);
	CString Line_read_string(FILE *pfile);
	//UNIT MrkFileSave(CString m_strFileName);
	void FindAlltFile(char *pszPath);
	
	void LoadRsc();
	
	void SetPositionXY(/*CMKObject* pObject,*/double NewX, double NewY,double nWidth, double nHeight);
	UINT MrkFileProc(CString strFileName);
	virtual UINT SemFileProc(CString strFileName,int jobcnt);
	virtual UINT SemFileDBtoSemFile(BOOL m_flag);
	//virtual UINT TxtChangeFromDB(BOOL m_flag);

	BOOL ParserLogobjParam(CString buf, int index,UINT iUnit);
	void MemDataProcess();
	void LoadDataToMemory(char *buf, int index);
	
	CArray<FieldParam*, FieldParam*>Array;
	CArray<MemData*, MemData*>_MemData;
	Vector *m_ltMasterOffset;
	Vector *m_ltSlaveOffset;
	CList <CRect, CRect> *m_rtMaster;
	CList <CRect, CRect> *m_rtSlave;
	MemData* m_Data;
	
	BOOL ParserTxtobjParam(CString buf, int index,UINT iUnit);
	CMKStdFile();
	virtual ~CMKStdFile();
   
	CEoJob* m_EO;
	CMDInformationOK* pCmd;
	int Objindex;
	int m_iSemStartPoint;
	CString m_txtobjmap[28]; // TextObj Param ����
	CString m_PrjFileName;
	CString m_SemFileName;
	CString ResourceVersion,SemVersion;
	CString tmp_buf;
	CString m_DeviceFile;
	BOOL m_prjFlag;
	BOOL StopFlag;
	CString m_strLogFile;
	CString m_strFontName;
	CStringArray m_strArray ;
	CString   m_strCurrentFileName;


	//------------------------------------------------------ Amkor Rsc ���� ����
	int m_IDF;
	double m_IDFoffset;
	double m_dStripHeight;
	double m_dStripWidth;
	double m_dChipHeight;
	double m_dChipWidth;
	double m_dXPitch1;
	double m_dXPitch2;
	double m_dYPitch1;
	double m_dYPitch2;
	double m_iXNum;
	double m_iYNum;
	double m_iSmallXNum ;
	double m_iSmallYNum ;
	//----------------------------------------------------
	double offsetBuffer[100];
	CDRect m_guideRect_Buf[10];
	int offsetBuffercnt;
	int m_UseSerial;
	int m_SerialNo;
	int m_SubSerialNo;
	int m_SSubSerialNo;
	int m_TxtLength;
	int m_tmpAngle;
	int m_dTxtAlign;
	double m_dWidthtmp;
	double m_dHeighttmp;
	BOOL m_bTxtChangeFromDB;
	double m_dOrgTmpPos;
	enum DataType
	{
		ID_OBJECT = 1,
		ID_PARAMETER = 2,
		ID_DEVICE = 3,
		ID_BIN = 4,
		ID_OFFSET = 5,
		ID_SERIALDATA = 6,
		ID_OPTIONTABLE = 7,
		ID_FONTDATA = 8,
		ID_SCRIBE = 9,
	};

	
	virtual UINT Load(CString strFileName); 
	// ũ�� Object, Para, Device�� �������µ�. 
	// ũ�� ���еǴ� ���� Object20���� 20������.�ɰ��� �ش� ������Ʈ�� �������ִ°ͱ������Ѵ�.
	// �ش� ������Ʈ�� ����Ÿ�� ������ �˾Ƽ� �ؼ� �ؼ� �ڱ��ڽ��� ä���ִ´�.
	// ������ �������ִ�. 
	virtual UINT Save(CString strFileName);
	virtual UINT LoadScr(CString strFileName);
	virtual UINT SaveScr(CString strFileName);
	virtual UINT LoadDev(CString strFileName);
	virtual UINT SaveDev(CString strFileName);
	virtual UINT LoadRsc(CString m_FileName,BOOL m_prjFlag);
	virtual UINT PrjFileProc(CString m_strFileName);
	//virtual UINT SemFileProc(CString strFileName);
	

	virtual UINT New();
private:
	 CMDMove* m_pCmd;

public:
	void SetFileName(CString strFilename);
	CString GetFileName(void);
};

#endif // !defined(AFX_MKSTDFILE_H__78A58D10_9300_486A_966E_903CF4E5918F__INCLUDED_)
