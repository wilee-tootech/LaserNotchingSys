/********************************************************************
	created:	2003/10/06
	created:	6:10:2003   16:38
	file base:	MKObject
	file ext:	h
	author:		JinSuk Chung
	
	purpose:	Store the Object Data and to Perform Methods -_-+
*********************************************************************/

#if     _MSC_VER > 1000
#pragma once
#endif

#ifndef _MKObject
#define _MKObject

//#include "afx.h"
#include "ObjectPainter.h"

#include "ObjectSender.h"
#include "Vector.h"
#include "MKDialog.h"

#include "FieldParameter.h"	//  

#include "VectorConverter.h"

#define ID_OBJECT_TYPE 1
///////////

#define ID_TEXT_OBJECT			101
#define ID_IMAGE_OBJECT			102
#define ID_LOGO_OBJECT			103
#define ID_BARCODE_OBJECT		104
#define ID_DATAMATRIX_OBJECT	105
#define ID_TTF_OBJECT           106
#define ID_COMPOSITE_OBJECT		107
#define ID_ARC_OBJECT			108
#define ID_LINE_OBJECT			109
#define ID_2DMATRIX_OBJECT		120
#define ID_DXF_OBJECT			121

// 오브젝트 구분아이디이다. 저장하거나 로드할때 꼭 필요하다.
// 러닝타임시에는 구분이 필요없어도 저장로딩할땐 필요하기때문.
/////////////////////////
class CHatchBuilder;
class CMarking;


#define TEST_MODE


//#include "PointerContainer.h"

// CRectTracker를 사용할것인가 말것인가.
// Width Height는 초기정보를 그대로 유지함을 원칙으로 한다.
class CMKObject : public CObject
{

public:

	virtual ~CMKObject();
	CMKObject();   // 기본값들어가야되는 부분은 생성시 들어가도록. 이것도 외부에 맞길수 있다.런타임시 변경가능하도록.


	enum VariableID   // 멤버 변수들이 저장될때 해당하는 아이디.ID_PARENT_DATA는 통일했다.
	{
		ID_PARENT_DATA = 5000,
		ID_X = 100,
		ID_Y = 101,
		ID_MAGX = 102,
		ID_MAGY = 103,
		ID_WIDTH = 104,
		ID_HEIGHT = 105,
		ID_PARAINDEX = 106,
		ID_BININDEX = 107,
		ID_ANGLE = 108,
		ID_MARKSTATE = 109,
		ID_SERIALFLAG = 110,
		ID_SELECTED = 111,
		ID_OBJECTTYPE = 112,
		ID_SERIALDATA = 113,
		ID_LOCKSTATE = 114,
		ID_SERIALNAME = 115,
		ID_STARTPOINT = 116,
		ID_ENDPOINT = 117,
		ID_MOVINGCENTERPOINT = 118,
		ID_CREATEZOOM = 119,
		// 2011.09.29 syhun START - Hatching 관련.
		ID_HATCH_TYPE = 120,
		ID_HATCH_DISTANCE = 121,
		ID_HATCH_OFFSET = 122,
		ID_HATCH_ANGLE = 123,
		ID_HATCH_OUTLINE = 124,
		// syhun END.
		ID_ISGROUP = 125,	// syhun START - 그룹 상태.
		ID_DOTMARK = 126,
	};
private:

public:	
	virtual BOOL GetDotMark();
	virtual void SetDotMark(BOOL isDotMark);
	virtual BOOL GetIsGroup();
	virtual void SetIsGroup(BOOL isGroup);
	virtual BOOL InObject(CMKObject *pObject, CPoint point);
	virtual CPoint GetMovingCenterPoint();
	virtual CPoint GetStartPoint();
	virtual CPoint GetEndPoint();
	virtual double GetCreateZoom();

	virtual UINT Release();
	virtual UINT Draw(CDC *pDC, CDPoint ptPosition, CDSize size)=0;  // 특정위치에 오브젝트를 그린다. // 그리는 것을 외부에 맞길수 있을듯.
	virtual UINT Draw(CDC *pDC, CDPoint ptPosition, CDSize size, BOOL bIsVector);   // 편의를 위해 다른 Rect로 통째로 받음.
	virtual UINT Draw(CDC *pDC, CDRect rtDrawRect);   // 편의를 위해 다른 Rect로 통째로 받음.
	virtual UINT Draw(CDC *pDC, CDRect rtDrawRect, BOOL bIsVector);   // 편의를 위해 다른 Rect로 통째로 받음.

	//virtual UINT LoadFile(CString strFileName);				// 오브젝트에 해당하는 화일을 연다.
	
	//오버라이딩 해야하는 메소드가 있고 하지않아도 되는 메소드가 있다.
	virtual void SetVectorData(Vector *hpgl_data);
	virtual Vector *GetVectorData();
	virtual void SetVectorLength(DWORD vectorLength);
	virtual DWORD GetVectorLength();

	// 2011.09.29 syhun START - Hatching 관련.
	virtual void SetHatchOutline(BOOL outline);
	virtual BOOL GetHatchOutline();
	virtual void SetHatchAngle(double angle);
	virtual double GetHatchAngle();
	virtual void SetHatchOffset(double offset);
	virtual double GetHatchOffset();
	virtual void SetHatchDistance(double distance);
	virtual double GetHatchDistance();
	virtual void SetHatchType(int type);
	virtual int GetHatchType();
	// syhun END.


	virtual void SetPosX(double dPosX);						//x 좌표 셋팅.
	virtual void SetPosX(double dPosX, BOOL bIsDrawObject); //x 좌표 셋팅.
	virtual double GetPosX();								//X 좌표 가져옴
	virtual double GetPosX(BOOL bIsDrawObject);
	virtual void SetPosY(double dPosY);						//y 좌표 셋팅
	virtual void SetPosY(double dPosY, BOOL bIsDrawObject); //x 좌표 셋팅.
	virtual double GetPosY();								//y 좌표 가져옴
	virtual double GetPosY(BOOL bIsDrawObject);
	virtual void SetWidth(double iWidth);					//width셋팅. //수동적이다.
	virtual double GetWidth();								//width가져옴
	virtual void SetHeight(double iHeight);					//height셋팅. // 역시 수동적..
	virtual double GetHeight();								//height가져옴
	virtual void SetMagX(double dMagX);						//MagX셋팅.
	virtual double GetMagX();								//MagX가져옴
	virtual void SetMagY(double dMagY);						//MagY셋팅.
	virtual double GetMagY();								//MagY가져옴.
	virtual void SetMarkState(BOOL State); //커팅 여부 셋팅.
	virtual BOOL GetMarkState();           //커팅 여부 가져옴.
	virtual void SetAngle(double dAngle);  //오브젝트의 엥글을 셋팅.
	virtual double GetAngle();             //오브젝트의 엥글 가져옴.
	virtual void SetLock(BOOL state);      //오브젝트 고정 여부 
	virtual BOOL GetLock();        

	virtual CDRect Rect();
		
	virtual BOOL GetPreSelected();
	virtual void SetPreSelected(BOOL bPreSelected);

	virtual BOOL IsMixedObject();

	virtual UINT DoModal()=0;								//다이얼로그 띄움. // 다이얼로그에서 포인터를 받아서 해당 오브젝트로 형변환
	virtual void SetDialog(CMKDialog *pDlg);                //Edit명령수행시 띄울 다이얼로그를 설정함.
	virtual CMKDialog *GetDialog();
	virtual UINT GetObjectType();
	virtual void SetObjectType(UINT uiObjectType);
	virtual UINT SetPainter(CObjectPainter *pPainter);  // 그려주는 클래스를 따로 정한다. 
														// 데이타와 뷰의 분리. 나중에 메뉴에서 그리는 방식을 바꿀수 있다.
	virtual CObjectPainter* GetPainter();
	
	/* Data Sender Set and DataSend */
	virtual UINT SetSender(CObjectSender *pSender)=0;
	virtual UINT SendObjectData(CMarking *pMarking, CPoint ptDevicePos)=0;//, int iIndex)=0;

	virtual CMKObject *GetClone()=0; //MemFile과 CArchive이용 해서 Deep 복사. 그러지말구 노가다 복사!! 추천!!! 
	virtual void SetClone(CMKObject *srcObject)=0; //받아서 자신의 상태를 받은 오브젝트와 똑같이 해야하나?
													//자기와 같은 종류가아닌 오브젝트가 들어온경우는 어떻게 처리해야하나. 11.07

	      //소멸전에 할일들 
	virtual UINT Refresh()=0;        // 데이타 다시 로드 (시리얼이 증가한경우, 혹은 로드된경우 이함수호출)
	// Refresh 는 현재 데이타를 모두 셋팅을 한후 Update를 호출할것이다.(다음번에 반영바로 반영되지 않음. ) 따라서 모든 오브젝트가 같은 시리얼 데이타 객체를 가지고 있다면
	//하나의 객체가 관리하게 되는것이고 따로 시리얼객체를 넣는다면 따로 따로 증가할수 있게 된다.
	//각기 제맘대로 놀수 있게 됨.  호출안하면 안된다!!!!
	

	// 임시로 이렇게 해놨다!!!! 테스트용!!!!
#ifndef TEST_MODE
	virtual UINT TransferData(CMarking *pMarking)=0;  //커팅 데이타를 전송한다. 
													//DSP혹은 다른 매채를 통해서라두.
#endif	
	//상속받은 객체는 Serialize를 오버라이딩 해야함.->취소.->하자 다만 CMKFileWriter를 이용해서 Serialize한다.

	virtual void SetParaIndex(UINT uiParaIndex); // 파라미터 인덱스
	virtual void SetBinIndex(UINT uiBinIndex);   // 빈넘버.
	virtual UINT GetParaIndex();                 // 파라미터 인덱스 가져옴.
	virtual UINT GetBinIndex();					// 빈 인덱스 가져옴.

	virtual void ReSize(double dPercent);  
	virtual void ReSize(double XMag, double YMag);   

	//실제 회전은 누가 시켜줄것인가..  10.07  회전 시켜주는 오브젝트 만들자.ok
#ifndef TEST_MODE	
	virtual void RotateObjectAngle(double dAngle)=0; //오브젝트 기준으로 회전.
	virtual void RotateFieldAngle(double dAngle)=0;  //회전하는 기준좌표를 파라메타로 줄것인지 안줄것인지. 휠드 기준 회전.
#endif

	virtual void SetSelect(BOOL nFlag);             //선택 여부 설정.
	virtual BOOL GetSelect();						// 선택상태 가져옴. 선택인지 아닌지.

	virtual void SetUseSerial(BOOL bSerialFlag);    // 시리얼 증가를 사용할것인가 안할것인가.
	virtual BOOL GetUseSerial();                    // 시리얼 증가 설정된 상태를 가져옴.

	virtual char *Serialize(DWORD &dwLength);                   // 직렬화 된 데이타를 받아옴.
	virtual UINT Unserialize(char *pstrSerial);    // 셋팅함.. 자기자신이 해석해서 적절히 변수를 삽입한다.


	                //설정된 그 객체를 반환. 

	virtual void Update();  // 업데잇트를 커팅 데이터를 생성할때마다 호출 할것이다.

	virtual void SetColor(COLORREF col);
// MAG처리 UserInterface에서 오브젝트 수정이 끝나면 실제 데이타에 반영한다.
// MAG는 보통때는 1이 될꺼다.



protected:

	BOOL m_bIsDotMark;

	double m_dX;   //위치 X 필드
	double m_dY;   //위치 Y 필드
	double m_dMagX;   // X 증폭.
	double m_dMagY;   // Y 증폭.
	double m_dWidth;  // 너비.
	double m_dHeight; // 높이 
	CObjectPainter *m_pPainter; //객체 그려주는 놈 이놈을 대체하면 또다른 방식의 그림이 될지도.~// 
	                           // 혹은 이놈에게 옵션을 줄수 있도록하면.. 많은 다양한 변화를 추구할수 있을듯.
								// 일단 페인터 지정은 CreateFactory에서 하면 어떨까. 
	

	CObjectSender *m_pSender;
	
	UINT m_uiParaIndex;
	UINT m_uiBinIndex;
	double m_dAngle;
	BOOL m_bMarkState;
	BOOL m_bSerialFlag;
	BOOL m_bSelected;
	BOOL m_bLock;


	UINT m_uiObjectType;

	CMKDialog *m_pDlg; // 요놈도 크리에이트 펙토리에서 말이지.. 설정을 해주는거야!
	CString m_strSerialName;

	CDPoint m_ptStartPoint;
	CDPoint m_ptEndPoint;
	CPoint m_ptMovingCenterPoint;
	double m_dCreateZoom;

	BOOL m_bPreSelected;

	// 2011.09.29 syhun START - Hatching 관련.
	
	int m_nHatchType;
	double m_dHatchDistance;
	double m_dHatchOffset;
	double m_dHatchAngle;
	BOOL m_bHatchOutLine;
	// syhun END.

	// syhun START - 그룹 상태.
	BOOL m_bIsGroup;
	// syhun END.

	// syhun START - Vector Converter관련.
	CVectorConverter m_VectorConverter;
	// syhun END.

	DWORD	m_dwVectorLength;
	Vector *m_hpgl_data;







};
//상속받은 클래스와 painter클래스는 Friend다. 

//어떤 오브젝트는 여러개 오브젝트를 포함하는 오브젝트도 있을수 있다.








/*




class CMKTextObject : public CMKObject
{








private:

	CString m_strFontName;
	//double m_dHeightRatio;
	//double m_dWidthRatio;보류 XMag YMag와 같은 기능을 할뿐이다.
	double m_dLineSpace;    //줄간격
	double m_dCharSpace;    //자간.
	double m_dLetterSpace;  //문자사이공간크기.
	
	UINT m_uiAlignVerticalEqual; //수평 배분 정렬.
	

	// 원형 배열 시작.
	BOOL m_uiRadialFlag;
	double m_dRadius;
	double m_dArcStartAngle;
	// 원형 배열 끝.
	

	Vector *m_hpgl_data;
	int m_iAlign;


public:
	void SetFontName(CString strFontName);  //폰트 화일을 지정한다.
	CString GetFontName();                  // 폰트 화일을 가져온다.
	void SetLineSpace(double dLineSpace);   //줄간격을 셋팅.
	double GetLineSpace();				    //줄간격 가져옴.
	void SetCharSpace(double dCharSpace);   //자간.셋
	double GetCharSpace();                  //자간 가져옴
	void SetLetterSpace(double dLetterSpace); //글자 빈공간 크기.
	double GetLetterSpace();                  //글자 빈공간 크기 가져옴.
	void SetAlignVerticalEqual(UINT uiFlag);  //수평 배분 정렬. 사용여부 셋.  
	UINT GetAlignVerticalEqual();			  //수평 배분 정렬 플레그 가져옴.
	void SetRadialFlag(BOOL bFlag);		   //Arc Array를 쓸것인가 말것인가.
	BOOL GetRadialFlag();                  //설정 상태를 가져온다.
	void SetRadius(double dRadius);        //배열의 반지름 설정.
	double GetRadius();					   //배열의 반지름을 가져온다. 
	void SetRadialStartAngle(double dStartAngle);   // Arc 배열의 시작 엥글을 셋팅한다.
	double GetRadialStartAngle();					// 가져온다.
	void SetAlign(int iAlign);                   // 정렬을. 설정. (왼쪽, 중앙, 오른쪽)
	int GetAlign();								// 정렬 설정 상태를 가져온다. 


	
};
// 오브젝트 스스로. ID 를 해석해서 다시 복구 한다.


class CMKBarcodeObject : public CMKObject
{
	


private:

	double m_dHeight;            //바코드 높이.
	double m_dXDim;				 //X 디멘젼.
	double m_dLaserWidth;        //Laser 굵기.
	double m_dQZFront;           //QuietZoneFront
	double m_dQZBack;			 //QuietZoneBack
	double m_dCharGap;			 //문자사이.
	CString m_strSrcString;
	int m_iCodeType;
	double m_dNRatio;            // wide 대 Narrow 비율 
	BOOL m_bVerifyChar;    //검증문자 사용여부
	BOOL m_bReverse;      // 반전인지 아닌지.
	//BOOL bNRatio;
	Vector *m_Hpgl_Data;     //바코드 벡터 데이타.
	UINT m_uiNumberofVector; //벡터 갯수.



public:
	void SetHeight(double dHeight);    // 바코드 높이. 필드단위.
	void SetXDimension(double dXDim);  // XDimension 설정.
	void SetLaserWidth(double dLaserWidth);  // 레이져 폭 설정.
	void SetQZFront(double dQZFront);        // Quiet Zone Front 설정.
	void SetQZBack(double dQZBack);          // Quiet Zone Back 설정.
	void SetCharGap(double dCharGap);        // 자간?설정
	void SetSrcString(CString strSrcString);  // 바코드의 메세지를 설정한다.
	void SetCodeType(int iCodeType);         //바코드 타입을 설정.
	void SetNRatio(double NRatio);          // 비율 설정. Narrow 대 Wide비율 
	void SetVerifyCharFlag(BOOL bVerifyChar);  // 검증 문자를 사용할것인지 아닌지.
	void SetVerifyChar(char cVerify);           // 검증문자를 셋팅한다.? 할필요가 있을지는 모르겠지만.
	void SetReverseFlag(BOOL bReverse);         // 반전 플레그 셋팅.
	void SetVectorData(Vector *Hpgl_Data);     // 벡터 데이타를 설정.
	void SetNumberofVector(UINT uiNumberofVector);  // 벡터데이타 갯수를 설정.
	void Encode(); //바코드 엔코드!


public:
	double GetHeight(); 
	double GetXDimension();
	double GetLaserWidth();
	double GetQZFront();
	double GetQZBack();
	double GetCharGap();
	CString GetSrcString();
	int GetCodeType();
	double GetNRatio();
	BOOL GetVerifyCharFlag();
	char GetVerifyChar();
	BOOL SetReverseFlag();
	Vector *SetVectorData();
	UINT SetNumberofVector();




	
};

class CMKDataMatrixObject : public CMKObject   //Refresh란 함수에서 실제로 bmp로 저장 하고 만든다.
{

public:
	void SetBackColor(long lBackColor);        // 빽 칼러.
	void SetForeColor(long lForeColor);        // 앞 칼러.
	void SetMatrixModule(long lMatrixModule);  // 메트릭스 모듈.
	void SetBarWidthReduction(long lBarWidthReduction); 
	void SetRotation(int iRotation);
	void SetBarHeight(long lBarHeight);
	void SetNarrowBarWidth(long lNarrowBarWidth);
	void SetSymbology(long lSymbology);
	void SetCommentAlignment(long lCommentAlignment);
	void SetBarcodeComment(CString strBarcodeComment);
	void SetBCMessage(CString strBCMessage);
	void SetFileName(CString strSaveFile);

	
	void SetBMPSize(int iBMPSize);
	void SetLineMoveDelay(int iLineMoveDelay);
	void SetDwellTime(int iDwellTime);
	void SetSamplingRate(int iSampling);

	
	
public:
	
	long GetBackColor();
	long GetForeColor();
	long GetMatrixModule();
	long GetBarWidthReduction();
	int GetRotation();
	long GetBarHeight();
	long GetNarrowBarWidth();
	long GetSymbology();
	long GetCommentAlignment();
	CString SetBarcodeComment();
	CString SetBCMessage();
	CString GetFileName();

	

	int GetBMPSize();
	int GetLineMoveDelay();
	int GetDwellTime();
	int GetSamplingRate();
	
	

private:
	
//2D Matrix 관련 데이타 시작.
	long m_lBackColor;
	long m_lForeColor;
	long m_lMatrixModule;
	long m_lBarWidthReduction;
	int m_iRotation;
	long m_lBarHeight;
	long m_lNarrowBarWidth;
	long m_lSymbology;
	long m_lCommentAlignment;
	CString m_strBarCodeComment;
	CString m_strBCMessage;
//2D Matrix 관련 데이타 끝.

	int m_iBMPSize;
	int m_iLineMoveDelay;
	int m_iDwellTime;
	int m_iSampling;

};

//Refresh를 오버라이딩하여 필요시 비트맵을 ReLoad하게 한다.
class CMKImageObject : public CMKObject
{



public:
	void SetBMPSize(int iBMPSize);                    //픽셀 점과 점을 띄우는 거리 설정.
	void SetLineMoveDelay(int iLineMoveDelay);      //// 한라인을 커팅한후 다음 줄로 가는데까지 쉬는 딜레이 타임. 너무 적게주면 갈바가 못따라갈수도 있음
	void SetDwellTime(int iDwellTime);          //한픽셀에 머무르는 시간.
	void SetSamplingRate(int iSampling);              //모든 픽셀을 데이터로 보내지 않고 몇개 건너띄워서 데이터 추출.
	void SetFileName(CString strFileName);         // 이미지 화일 이름.

	int GetBMPSize();        
	int GetLineMoveDelay();
	int GetDwellTime();
	int GetSamplingRate();
	CString GetFileName();


private:

	int m_iBMPSize;    //픽셀 점과 점을 띄우는 거리.
	int m_iLineMoveDelay; // 한라인을 커팅한후 다음 줄로 가는데까지 쉬는 딜레이 타임. 너무 적게주면 갈바가 못따라갈수도 있음
	int m_iDwellTime;     //한픽셀에 머무르는 시간.
	int m_iSampling;      //모든 픽셀을 데이터로 보내지 않고 몇개 건너띄워서 데이터 추출.
	CString m_strFileName;  // 이미지 화일 이름.

};





class CMKLogoObject : public CMKObject
{

public:     //메소드.

	Vector* GetVectorData();
	int  GetNumberofVector();
	CString GetFileName();

	void SetVectorData(Vector *hpgl_data);
	void SetNumberofVector(int nVector);
	void SetFileName( CString strFileName);

	
private:
	Vector *m_Hpgl_Data;
	int m_NumberofVector;
	CString m_strFileName;
	
	
};

class CMKCompositeObject : public CMKObject   //CMKObject를 상속받은 객체들을 하나의 객체로 묶어준다.
{											// 밖의 클라이언트는 모른다. 그냥 객채인줄 안다. 
											//할수 있는것들.
											//SetMag SetPos Transfer  , Delete , Copy MarkState Refresh Rotate,등 대부분.


//CMKObject의 최종 내용을 복사해서 여기다가 갖다 놓으면 됨.
// 모든 인터페이스의 함수에대해서 오버라이딩을 해서 다중객체를 담당할수 있게 함.
// List나 Array이용 CMKObject들의 관리까지 여기서.
	
};

  */


#endif //_MKObject