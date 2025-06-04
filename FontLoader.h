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
	

	

	DWORD LoadString(CString strData);  // �־��� ��Ʈ���� 
	UINT LoadFont(CString strFileName); // �ش� ��Ʈ�� �ε��Ѵ�.
	UINT LoadFont(BYTE *pFontData, DWORD dwByte);   // ȭ�Ͽ��� �о������ �ʰ� �̹� �о���� ���¿��� ���� �Ѵ�.
	void SetDefaultFont(CString m_strFont);
										// ���� .MRK ȭ�Ͽ� ��Ʈ���� ���Խ�ų ��� �ʿ��� �Լ�.
	Vector *GetVectorData();

	DWORD GetVectorSize();
	DWORD GetWidth();
	DWORD GetHeight();
	DWORD AddX;//jjs
	DWORD FirstX,LastX;

private: //�Լ���


	DWORD GetTotalLine(CString strData);
	Vector* CreateVectorArray(CString strData, DWORD &dwSize);
	DWORD GetRequireVectorSpace(CString strData);
	DWORD GetVectorCount(CString strData);
	void GetCharInfo(DWORD dwChar, DWORD  &dwDataOffset, DWORD &dwNumberofVectorinByte);
	void GetPositionData(DWORD dwDataOffset, char &pen, short &iX, short &iY);
	
	DWORD LoadCharacter(DWORD dwChar, int pos, int orValue); 
		//dwChar:���� �ƽ�Ű�ڵ� ,pos:����Ÿ�� ����� ���� �迭���� ��ġ return:���� ���� orValue: �ѱ��ڿ����� ������ ����տ� Vector::t�� ���� ���� OR���� ��.
	

	void GetMinMaxinChar(DWORD dwDataOffset, DWORD dwNumberofVector, double &MinX,double &MaxX,double &MinY, double &MaxY);
	void GetMinMaxinChar(DWORD dwChar, double &MinX, double &MaxX, double &MinY, double &MaxY);

	void GetMaxWidthHeightinFont(double &nWidth , double &nHeight); //�ִ� �ʺ�� �ִ� ���̸� ���Ѵ�.
	void GetMinMaxinFont(double &nMinX, double &nMaxX, double &nMinY, double &nMaxY); // ��Ʈ���� ��ü�� ���� �ִ� �ּҸ� ���Ѵ�.
	void GetMinMax(Vector *pData, DWORD dwLength, double &nMinX, double &nMaxX, double &nMinY, double &nMaxY);// ���� �迭�� ���ؼ� �ִ� �ּҸ� ���Ѵ�.
	void GetMinMaxVector(Vector *pData, DWORD dwStartPos,DWORD dwEndPos, double &nMinX, double &nMaxX, double &nMinY, double &nMaxY);// ���� �迭�� ���ؼ� �ִ� �ּҸ� ���Ѵ�.

	DWORD GetMaxWidth_LineFeed(Vector *pData, DWORD dwLength);
	//���� ���ڸ� ����ؼ� �ִ� ���� ���Ѵ�. ���๮�ڰ� ������ point=(0,0)���� �ʱ�ȭ �ϰ� �ٽ� ���ϴ� ��.

	void DoAlign();
	void DoArcArray();

	
	CPoint GoThrough(DWORD dwStartPos,DWORD dwEndPos);


public:   //������Ƽ��.
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

	// 2011. 03. 11 syhun START - ���� ���� �߰�.
	void SetAngle(double dAngle);
	double GetAngle();
	// syhun END.
	

//	int GetCharCenter(int index, CPoint point);
	double GetCharCenter(int index, CDPoint point);
	CFontLoader();
	virtual ~CFontLoader();
	
	//Vector *LoadString(CMKObject *pObject); // ������Ʈ�� �޾Ƽ� �˾Ƽ� �ؼ��ؼ� �˾Ƽ� ���� ��ȯ.

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

	double m_dAngle;	// 2011. 03. 11 syhun START - ������ �߰�.
//	double m_nMinX;		// 2011. 03. 18 syhun START - x�ּҰ� �߰�.
//	double m_nMinY;		// 2011. 03. 18 syhun START - y�ּҰ� �߰�.


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