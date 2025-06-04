#include <windows.h>
#include <afxtempl.h>
#include <MATH.H>
#include "Vector.h"

int IMGConvertOpen(CString path);
int IMGConvertClose();

typedef CArray<Vector, Vector&> ImgCovertVectorArray;
typedef CList<Vector, Vector&> ImgConvertVectorList;

typedef void (*SETCURRENTPATH)(LPCTSTR);
typedef BOOL (*LOADIMGFILE)(LPCTSTR);
typedef BOOL (*HANDLELOADIMGFILE)(LPCTSTR, HANDLE);
typedef void (*IMGCONTOURTRACING)(ImgConvertVectorList&, int erosion);
typedef void (*IMGBLOBCOLORINGHATCH)(ImgConvertVectorList&, BOOL bIsTracing, int nHatchDirect, int nHantchDisPixel);
typedef double (*GETIMGCONVERTWIDTH)(void);
typedef double (*GETIMGCONVERTHEIGHT)(void);
typedef LPBITMAPINFOHEADER (*GETBITMAPHEADER)(void);
typedef void (*IMAGEBITTOVECTORDATA)(ImgConvertVectorList&, BOOL negative, int smaplingX, int samplingY);
typedef void (*SETIMGCONVERTTYPE)(int convertType);

extern SETCURRENTPATH SetCurrentPath;				// DLL에게 현재 폴더를 세팅.
extern LOADIMGFILE LoadImgFile;						// Load image file.
extern HANDLELOADIMGFILE HandleLoadImgFile;			// Handle Load image file.
extern IMGCONTOURTRACING ImageContourTracing;		// 외곽선 추출.
extern IMGBLOBCOLORINGHATCH ImageBlobColoringHatch;	// 라벨링 해칭.
extern GETIMGCONVERTWIDTH GetImgConvertWidth;		// Image width
extern GETIMGCONVERTHEIGHT GetImgConvertHeight;		// Image height
extern GETBITMAPHEADER GetBitMapHeader;				// Image infomation
extern IMAGEBITTOVECTORDATA ImageBitToVectorData;	// Scatter / Dither 방식 이미지 컨버팅.
extern SETIMGCONVERTTYPE SetImgConvertType;			// Image convert 방식 세팅.