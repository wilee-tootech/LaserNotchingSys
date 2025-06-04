#ifndef _FontLoader
#define _FontLoader

#include "MKObject.h"

#undef PI
#define PI 3.1415927

class  CFontLoader
{

public:
	enum FontHeaderInfo 
	{
		HEADER_LENGTH = 102,
		INDEX_LENGTH = 512
	};
	enum AlignFlag
	{
		modeLEFT = 1,
		modeMIDDLE = 2,
		modeRIGHT =3
	};
	

	

	DWORD LoadString(CString strData);  // 주어진 스트링을 
	UINT LoadFont(CString strFileName); // 해당 폰트를 로딩한다.
	UINT LoadFont(BYTE *pFontData, DWORD dwByte);   // 화일에서 읽어들이지 않고 이미 읽어들인 상태에서 셋팅 한다.
	void SetDefaultFont(CString m_strFont);
										// 추후 .MRK 화일에 폰트까지 포함시킬 경우 필요한 함수.
	Vector *GetVectorData();

	DWORD GetVectorSize();
	DWORD GetWidth();
	DWORD GetHeight();
	DWORD AddX;//jjs
	DWORD FirstX,LastX;

private: //함수들


	DWORD GetTotalLine(CString strData);
	Vector* CreateVectorArray(CString strData, DWORD &dwSize);
	DWORD GetRequireVectorSpace(CString strData);
	DWORD GetVectorCount(CString strData);
	void GetCharInfo(DWORD dwChar, DWORD  &dwDataOffset, DWORD &dwNumberofVectorinByte);
	void GetPositionData(DWORD dwDataOffset, char &pen, short &iX, short &iY);
	
	DWORD LoadCharacter(DWORD dwChar, int pos, int orValue); 
		//dwChar:문자 아스키코드 ,pos:데이타가 저장될 벡터 배열상의 위치 return:벡터 갯수 orValue: 한글자에대한 벡터중 가장앞에 Vector::t에 새겨 놓을 OR연산 값.
	

	void GetMinMaxinChar(DWORD dwDataOffset, DWORD dwNumberofVector, double &MinX,double &MaxX,double &MinY, double &MaxY);
	void GetMinMaxinChar(DWORD dwChar, double &MinX, double &MaxX, double &MinY, double &MaxY);

	void GetMaxWidthHeightinFont(double &nWidth , double &nHeight); //최대 너비와 최대 높이를 구한다.
	void GetMinMaxinFont(double &nMinX, double &nMaxX, double &nMinY, double &nMaxY); // 폰트글자 전체에 걸쳐 최대 최소를 구한다.
	void GetMinMax(Vector *pData, DWORD dwLength, double &nMinX, double &nMaxX, double &nMinY, double &nMaxY);// 벡터 배열에 대해서 최대 최소를 구한다.
	void GetMinMaxVector(Vector *pData, DWORD dwStartPos,DWORD dwEndPos, double &nMinX, double &nMaxX, double &nMinY, double &nMaxY);// 벡터 배열에 대해서 최대 최소를 구한다.

	DWORD GetMaxWidth_LineFeed(Vector *pData, DWORD dwLength);
	//개행 문자를 고려해서 최대 폭을 구한다. 개행문자가 나오면 point=(0,0)으로 초기화 하고 다시 구하는 식.

	void DoAlign();
	void DoArcArray();

	
	CPoint GoThrough(DWORD dwStartPos,DWORD dwEndPos);


public:   //프로퍼티들.
	void SetTotalLetterHeight(double dTotalHeight);
	void SetLetterHeight(double dLetterHeight);
	void SetOrgRatio(double xratio);
	void SetWidtScale(double WidthScale);
	void AddXVector(double xvector);

	

	void SetEqualSpan(BOOL nFlag);
	BOOL GetEqualSpan();

	void SetCharSpace(double dCharSpace);
	double GetCharSpace();

	void SetLineSpace(double dLineSpace);
	double GetLineSpace();

	void SetLetterSpace(double dLetterSpace);
	double GetLetterSpace();

	void SetAlign(DWORD dwFlag);
	DWORD GetAlign();

	void SetArcArray(BOOL bFlag);
	BOOL GetArcArray();
	
	void SetArcRadius(double dRadius);
	double GetArcRadius();

	void SetArcStartAngle(double dStartAngle);
	double GetArcStartAngle();

	// 2011. 03. 11 syhun START - 각도 관련 추가.
	void SetAngle(double dAngle);
	double GetAngle();
	// syhun END.
	

//	int GetCharCenter(int index, CPoint point);
	double GetCharCenter(int index, CDPoint point);
	CFontLoader();
	virtual ~CFontLoader();
	
	//Vector *LoadString(CMKObject *pObject); // 오브젝트를 받아서 알아서 해석해서 알아서 벡터 반환.

private:
	Vector *m_pVectorRel;
	Vector *m_pVectorAbs;
	Vector *m_pVectorTmp;

	double m_dwWidth;
	double m_dwHeight;

	int m_iVectorLength  ;
	DWORD m_dwAlignFlag ;
	double m_dLetterSpace ;
	double m_dCharSpace ;
	double m_dLineSpace ;
	double m_orgMag; //jjs
	double m_dStartAngle ;
	double m_dArcRadius ;
	double m_dLetterHeight;
	double m_dTotalHeight;
	double m_dWidthScale;

	double m_dAngle;	// 2011. 03. 11 syhun START - 각도값 추가.
//	double m_nMinX;		// 2011. 03. 18 syhun START - x최소값 추가.
//	double m_nMinY;		// 2011. 03. 18 syhun START - y최소값 추가.


	BOOL m_bEqualSpan ;
	BOOL m_bArcArray ;




	BYTE *m_pFontData;
	BYTE m_pFontHeader[HEADER_LENGTH];
	DWORD m_pFontIndex[INDEX_LENGTH];
	DWORD m_dwFileSize;
	Vector *m_pVector;
	DWORD m_dwVectorSize;
	CString m_FontName;



};




#endif //_FontLoader