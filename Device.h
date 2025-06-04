#ifndef _DeviceManager
#define _DeviceManager


//#include <Afxwin.h>
#include <afxtempl.h>
#include "Chip.h"
#include "define.h"
#include "Vector.h"


//2018.10.02 jjsjong
#include <vector>
#include <iterator>
#include <algorithm>
#include <math.h>

//#if     _MSC_VER > 1000
//#pragma once
//#endif


// �ø�������� �����ؾ��Ѵ�.

// ������ ��
#define OFFSETDIRECTIONSIZE     256
#define STRIPNAMESIZE           256
#define MAX_TAP_BUFF_SIZE		10000	// 10000����Ʈ
			
class  CDeviceData 
{
public:
	
	enum VariableIDDeviceData  // Seriallize�ÿ� �̿�Ǵ� ID�� 
	{
		    ID_CHAR_OFFSET_DIRECTION = 100, // m_cOffsetDirection
			ID_STRIP_NAME			= 101,  // m_cStripName
			ID_STRIP_WIDTH			= 102,  // m_dStripWidth
			ID_STRIP_HEIGHT			= 103,  // m_dStripWidth
			ID_CHIP_WIDTH			= 104,  // m_dChipWidth
			ID_CHIP_HEIGHT			= 105,  // m_dChipHeight
			ID_XPITCH1				= 106,  // m_dXPitch1
			ID_YPITCH1				= 107,  // m_dYPitch1
			ID_XPITCH2				= 108,  // m_dXPitch2
			ID_YPITCH2				= 109,  // m_dYPitch2
			ID_OFFSET				= 110,  // m_dOffset
			ID_XNUM					= 111,  // m_iXNum
			ID_YNUM					= 112,  // m_iYNum
			ID_SMALL_XNUM			= 113,  // m_iSmallXNum
			ID_SMALL_YNUM			= 114,  // m_iSmallYNum
			ID_MARK_METHOD			= 115,  // m_iMarkMethod
			ID_CUR_INDEX			= 116,  // m_iCurIndex
			ID_START_POS			= 117,  // m_iStartPos
			ID_INT_OFFSET_DIRECTION = 118,  // m_iOffsetDirection
			ID_SELECT_ARRAY			= 119,  // m_bSelectArray
			ID_SELECT_ARRAY2		= 120,  // m_bSelectArray2
			ID_ODD_FLAG				= 121,  // m_bOddFlag
			ID_CHECK_DEVICE			= 122,  // m_bCheckDevice
			ID_USE2PITCH			= 123,  // m_bUse2Pitch
			ID_READY_PART			= 124,  // m_bReadyPart1
			ID_IS_PARTIAL_NO_MARK	= 125,  // m_bisPartialNoMark
			ID_MASTER_OFFSETX       = 126,
			ID_MASTER_OFFSETY       = 127,
			ID_SLAVE_OFFSETX        = 128,
			ID_SLAVE_OFFSETY        = 129, 
			ID_GUIDE_VALUE          = 130,
			ID_SIDE_ARRAY_SKIP		= 131,
	//----------------------------------LOGO ���� ���尪----------------
			ID_WIDTH = 132,
			ID_HEIGHT = 133,
			ID_EXPEND_DIST = 134,
			ID_START_EXT_OFFSET = 135,
			ID_END_EXT_OFFSET = 136,
			ID_LT_RADIUS = 137,
			ID_LB_RADIUS = 138,
			ID_RT_RADIUS = 139,
			ID_RB_RADIUS = 140,
			ID_L_SLOOP_ANGLE = 141,
			ID_L_CTRL_POINT1 = 142,
			ID_L_CTRL_POINT2 = 143,
			ID_R_SLOOP_ANGLE = 144,
			ID_R_CTRL_POINT1 = 145,
			ID_R_CTRL_POINT2 = 146,
			ID_Y_FLIP        = 147, 
			ID_Y_OFFSET	  = 148,
			ID_OFFSET_CUT_WIDTH = 149,
			ID_SLOOP_WIDTH = 150,
			ID_SLOOP_WIDTH_L = 151,
			ID_SLOOP_WIDTH_R = 152,
			ID_BASE_CUTWIDTH = 153,
			ID_SLOOP_SEGMENT_LT = 154,
			ID_SLOOP_SEGMENT_LB = 155,
			ID_SLOOP_SEGMENT_RT = 156,
			ID_SLOOP_SEGMENT_RB = 157,
			ID_EXTEND_XWIDTH_L = 158,
			ID_EXTEND_XWIDTH_R = 159,
			ID_EXTEND_YHEIGHT_L = 160,
			ID_EXTEND_YHEIGHT_R = 161,
			//-------------T�� �Ķ����--------------------
			ID_UNFLAG_START = 162,
			ID_UNFLAG_START_HEIGHT = 163,
			ID_UNFLAG_END = 164,
			ID_UNFLAG_END_HEIGHT = 165,
			ID_NUBLESS_REGION = 166,
			ID_NUBLESS_HEIGHT = 167,
			ID_BURIED_REGION = 168,
			ID_BURIED_HEIGHT = 169,
			ID_FLAG_COUNT = 170,
			ID_FLAG_LENGTH = 171,
			ID_FLAG_WIDTH = 172,
			ID_FLAG_START_WIDTH = 173,
			ID_FLAG_DEGREES = 174,
			ID_HEAD2_WIDTH = 175,
			ID_FOIL_EXTENSION = 176,
			ID_NOTCH_ROOT = 177,
			ID_CHANGE_OFFSET = 178,
	};
	/* ���� ���� start */
private:
	Vector *m_ltMasterOffset;
	Vector *m_ltSlaveOffset;
	CDRect *m_pGuideRect;
	CChip  *m_pChip;
	char   m_cOffsetDirection[OFFSETDIRECTIONSIZE];
	char   m_cStripName[STRIPNAMESIZE];
	double m_dStripWidth;
	double m_dStripHeight;
	double m_dChipWidth;
	double m_dChipHeight;
	double m_dXPitch1;
	double m_dYPitch1;
	double m_dXPitch2;
	double m_dYPitch2;
	double m_dOffset;
	int m_iXNum;
	int m_iYNum;
	int m_iSmallXNum;
	int m_iSmallYNum;
	int m_iMarkMethod; // Ŀ�� ���� ����
	int m_iCurIndex;
	int m_iStartPos; // Ŀ�� ���� Ĩ ���ϴ� ��
	int m_iOffsetDirection; // Offset ���� ������ int ������
	int m_iMoveShutter; // Shutter ������ ����ؾ��� ��� ����� ���� ���������� ����
	int	m_iNumOfXPitch1;
	int	m_iNumOfXPitch2;
	int	m_iNumOfYPitch1;
	int	m_iNumOfYPitch2;
	int m_iFirstIndex;
	double m_dManualCutWidth;
	double m_dManualCutStep;
	double m_dManualCutExtend;
	BOOL m_bOddFlag;
	BOOL m_bCheckDevice;
	BOOL m_bUse2Pitch;
	BOOL m_bReadyPart1;
	BOOL m_bIsPartialNoMark;
	int m_DeviceType;
	BOOL m_bSideArraySkip;
	double m_dMasterX;
	double m_dMasterY;
	double m_dSlaveX;
	double m_dSlaveY;

	st_Tap_PositionData  m_st1_Tap_Position;
	std::vector< st_Tap_PositionData>	m_st_Tap_Position;

	st_Tap_Monitoring_PositionData  m_st1_Tap_MonitoringData;
	std::vector< st_Tap_Monitoring_PositionData> m_st_Tap_MonitoringData;



public:
	int GetCurrentIndex();
	int GetShutterFlag();
	double GetSlaveY();
	double GetSlaveX();
	double GetMasterY();
	double GetMasterX();
	void SetSlaveOffset(double m_dslaveX, double m_dslaveY);
	void SetMasterOffset(double m_dmasterX, double m_dmasterY);
	CChip GetCurrentChip(int iIndex);
	void CreateDeviceList();
	CDeviceData();
	virtual ~CDeviceData();
	
	void   SetStripWidth(double dStripWidth);
	double GetStripWidth();
	void   SetStripHeight(double dStripHeight);
	double GetStripHeight();
	void   SetChipWidth(double dChipWidth);
	double GetChipWidth();
	void   SetChipHeight(double dChipHeight);
	double GetChipHeight();
	void   SetXPitch1(double dXPitch1);
	double GetXPitch1();
	void   SetYPitch1(double dYPitch1);
	double GetYPitch1();
	void   SetXPitch2(double dXPitch2);
	double GetXPitch2();
	void   SetYPitch2(double dYPitch2);
	double GetYPitch2();
	void SetXNum(int iXNum);
	int  GetXNum();
	void SetYNum(int iYNum);
	int  GetYNum();
	void SetSmallXNum(int iSmallXNum);
	int  GetSmallXNum();
	void SetSmallYNum(int iSmallYNum);
	int  GetSmallYNum();
	void SetMarkMethod(int iMarkMethod);
	int  GetMarkMethod();
	void SetCurrentIndex(int iCurIndex);
	void SetOddFlag(BOOL bOddFlag);
	int  GetOddFlag();
	void SetCheckDevice(BOOL m_bCheckDevice);
	int  GetCheckDevice();
	void SetOffsetDirection(int iOffsetDirection);
	int  GetOffsetDirection();
	void SetOffset(double dOffset);
	double GetOffset();
	void SetIDLocation(int m_IdPos);
	int  GetIDLocation();
	void SetStripName(char *strStripName);
	char *GetStripName();
	void SetUse2Pitch(BOOL bUse2Pitch);
	BOOL GetUse2Pitch();
	char *Serialize(DWORD &dwLength);
	void Unserialize(char *pstrSerial);
	CPoint GetNext();
	void ReadyToExtract();
	void CalculatePitch();
	BOOL GetIsPartialNoMark();
	UINT SetMasterOffset(Vector *ltMasterOffset);
	UINT SetSlaveOffset(Vector *ltSlaveOffset);
	Vector *GetMasterOffset();
	Vector *GetSlaveOffset();
	int GetDeviceType();
	void SetDeviceType(int m_DeviceType);
	void ClearGuideMemory();

	void SetUseSideArraySkip(BOOL b);
	BOOL GetUseSideArraySkip();

	void Clear_Tap_PositionData();
	void Add_Tap_Position(st_Tap_PositionData tTap_Position);
	void Add_Tap_Position(int index, st_Tap_PositionData tTap_Position);
	void Delete_Tap_Position(int index);
	void DeleteAll_Tap_Position();

	st_Tap_PositionData Get_TapPosition(int nindex);
	int Get_TapPositionCount();



	void Clear_Tap_MonitoringData();
	void Add_Tap_MonitoringData(st_Tap_Monitoring_PositionData tTap_MonitoringData);
	st_Tap_Monitoring_PositionData Get_Tap_MonitoringData(int nindex);
	int Get_Tap_MonitoringDataCount();

	/* ���� ���� end */
	
	//���� 
	////	float xo;  // top margin.
	////	float yo;  // left margin.
	//��
	
	//   float rm;  // right margin.
	//   float bm;  // bottom margin.
	//	int   semiidlo;
	void SetFirstIndex(int nFirstIndex);
	int GetFirstIndex();

	void SetManualCutWidth(double nManualCutWidth);
	double GetManualCutWidth();
	void SetManualCutStep(double nManualCutStep);
	double GetManualCutStep();
	void SetManualCutExtend(double nManualCutExtend);
	double GetManualCutExtend();
};



class CDeviceManager
{
	
	
public:
	
	
	CDeviceManager();
	virtual ~CDeviceManager();
	
	void CreateData();
	void DeleteData();
	
	CPoint *GetPositionList(UINT &uiGetDeviceCount);
	void SetPositionList(CPoint *ptPosList, UINT uiSetDeviceCount);
	UINT Calculate();  //DeviceData�� ������ positionList�� ������. ���� �� 0�� ���� ���ϰ� ����̽� ī��Ʈ!
	
	UINT DoModal(UINT &uiGetResultCode);   // uiGetResultCode : ���̾�α׸� ������� ���ϰ��� �޴º���.
	UINT SetDialog(CDialog *pDlg); // ��� ���̾�α׸� �����س��. 
	CDeviceData *GetDeviceData(); // ������ ����Ÿ�� �Ѱ��ش�. (NULL������ ��� ���� ��ɵ� ����)
	void SetDeviceData(CDeviceData *pDevData);
	
	
    static CDeviceManager *Instance();
	static void Remove();
	
	
	double GetDevWidth();
	double GetDevHeight();
	int Get_IDLocation();
	CString Get_StripName();
	
	
	char *Serialize(DWORD &dwLength);
	void Unserialize(char *pstrSerial);
	
	enum VariableIDDeviceManager
	{
		ID_DEVICE_DATA = 1000
	};
	
	// �߰�
	CDialog *GetDialog();
	
private:
	static CDeviceManager *m_pDeviceManager;
	
	
	
	CDeviceData *m_pDeviceData;
	CPoint *m_pPositionList;
	UINT m_pPositionCount;
	
	
	
	CDialog *m_pDlg;
};



#endif // _Device

