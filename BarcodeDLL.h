
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the BARCODEDLL_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// BARCODEDLL_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
#ifdef BARCODEDLL_EXPORTS
#define BARCODEDLL_API __declspec(dllexport)
#else
#define BARCODEDLL_API __declspec(dllimport)
#endif

//
// The Barcode Code Type flags field
//
#define CODE_TYPE_DEFAULT_FLAGS		0x00000000
#define CODE_TYPE_X_DIM				0x00000001
#define CODE_TYPE_N_RATIO			0x00000002
#define CODE_TYPE_CHAR_GAP			0x00000004

struct BC_RECT
{
	double m_dLeft;
	double m_dTop;
	double m_dRight;
	double m_dBottom;
};

class CPtrRect : public CPtrList
{
public:
	CPtrRect() {};
	CPtrRect(const CPtrRect& rhs) // 복사 생성자
	{
		POSITION POS = rhs.GetHeadPosition();
		while( POS )
		{
			BC_RECT* bc_rect = (BC_RECT*)GetNext( POS );
			BC_RECT* pNewRect = new BC_RECT;
			pNewRect->m_dLeft = bc_rect->m_dLeft;
			pNewRect->m_dTop  = bc_rect->m_dTop;
			pNewRect->m_dRight =bc_rect->m_dRight;
			pNewRect->m_dBottom=bc_rect->m_dBottom;
			AddTail( pNewRect );
		}
	};

	~CPtrRect()
	{
		ClearList();
	}

	void ClearList()
	{
		POSITION POS = GetHeadPosition();
		while( POS ) {
			BC_RECT* bc_rect = (BC_RECT*)GetNext( POS );
			delete bc_rect;
		}
		RemoveAll();
	}

	CPtrRect& operator=( const CPtrRect& rhs) // 치환 연산자
	{
		if( this==&rhs )
			return *this;

		// 자신이 이전에 가지고 있던 데이터를 모두 지운다.
		ClearList();

		POSITION POS = rhs.GetHeadPosition();
		while( POS )
		{
			BC_RECT* bc_rect = (BC_RECT*)GetNext( POS );
			BC_RECT* pNewRect = new BC_RECT;
			pNewRect->m_dLeft = bc_rect->m_dLeft;
			pNewRect->m_dTop  = bc_rect->m_dTop;
			pNewRect->m_dRight =bc_rect->m_dRight;
			pNewRect->m_dBottom=bc_rect->m_dBottom;
			AddTail( pNewRect );
		}
		return *this;
	}
};

struct BC_LINE
{
	double m_dX1;
	double m_dY1;
	double m_dX2;
	double m_dY2;
};

class CPtrLine : public CPtrList
{
public:
	CPtrLine() {};
	CPtrLine(const CPtrLine& rhs) // 복사 생성자
	{
		POSITION POS = rhs.GetHeadPosition();
		while( POS )
		{
			BC_LINE* bc_line = (BC_LINE*)GetNext( POS );
			BC_LINE* pNewLine = new BC_LINE;
			pNewLine->m_dX1 = bc_line->m_dX1;
			pNewLine->m_dY1 = bc_line->m_dY1;
			pNewLine->m_dX2 = bc_line->m_dX2;
			pNewLine->m_dY2 = bc_line->m_dY2;
			AddTail( pNewLine );
		}
	};

	~CPtrLine()
	{
		ClearList();
	}

	void ClearList()
	{
		POSITION POS = GetHeadPosition();
		while( POS ) {
			BC_LINE* bc_line = (BC_LINE*)GetNext( POS );
//			BC_LINE* bc_line = (BC_LINE*)RemoveHead();
			delete  bc_line;
		}
		RemoveAll();
	}

	CPtrLine& operator=( const CPtrLine& rhs) // 치환 연산자
	{
		if( this==&rhs )
			return *this;

		// 자신이 이전에 가지고 있던 데이터를 모두 지운다.
		ClearList();

		POSITION POS = rhs.GetHeadPosition();
		while( POS )
		{
			BC_LINE* bc_line = (BC_LINE*)GetNext( POS );
			BC_LINE* pNewLine = new BC_LINE;
			pNewLine->m_dX1 = bc_line->m_dX1;
			pNewLine->m_dY1 = bc_line->m_dY1;
			pNewLine->m_dX2 = bc_line->m_dX2;
			pNewLine->m_dY2 = bc_line->m_dY2;
			AddTail( pNewLine );
		}
		return *this;
	}
};

struct BC_OPTION
{
	CString m_sEncodeType; // CODE 39, CODE 93, CODE 128, CODE I 2/5 등등
	CString m_sSrcString;  // Encode할 문자열.
	BOOL m_bPos;		// 정상, 반전
	BOOL m_bVerifyChar; // 검증문자를 포함할 것인가?
	double m_dHeight;	// Bar 의 높이
	double m_dOffsetX;	// 프린트를 시작할 X Offset
	double m_dOffsetY;	// 프린트를 시작할 Y Offset
	double m_dQZFront;	// 앞쪽 Quiet Zone의 길이
	double m_dQZBack;	// 뒤쪽 Quiet Zone의 길이
	double m_dXDim;		// X Dimension
	double m_dNRatio;	// Wide/Narrow 비율
	double m_dCharGap;	// 문자와 문자 사이의 갭 폭
	double m_dLaserWidth; // Laser의 폭
	CString m_sErrMsg;  // 에러 메시지
	CString m_sEncoded; // 인코드된 String
};

// This class is exported from the BarcodeDLL.dll
class BARCODEDLL_API CBarcodeDLL {
public:
	BOOL GetValidOpt(CString sEncodeType, int& flags);
	BOOL EncodeBarcode(BC_OPTION & BCOpt, CPtrLine & PtrLine );

	CBarcodeDLL(void);
	~CBarcodeDLL(void);
	// TODO: add your methods here.
protected:
	void GetBCRect( BC_OPTION & );
	void DrawCode93( BC_OPTION & );
	void DrawCode39( BC_OPTION & );
	void DrawCodeI25( BC_OPTION & );
	void DrawCode128( BC_OPTION & );
	void DrawCodeEAN( BC_OPTION & );
	void DrawCodeUPC( BC_OPTION & );

	// 레이저로 출력하기 위해 사각형을 선으로 바꿔주는 코드.
	void ConvRectToLine(double dLaserWidth, CPtrLine& PtrLine);

	CString GetEncodeString(CString sSrcString, int flags);
	int encode_id( CString );
	CPtrRect m_PtrRect;
};

// This is an example of an exported variable
extern BARCODEDLL_API int nBarcodeDLL;

// This is an example of an exported function.
BARCODEDLL_API double GetDLL_Version(void);
