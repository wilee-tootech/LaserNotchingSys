
#ifndef _RETURN
#define _RETURN

#define R_DEFAULT			0
#define R_AUTHORITY_OK                  0
//   추가...
#define R_MARKING			2



#define R_FAILED			1
#define R_AUTHORITY_DENIED		100
#define R_NOAUTHORITYDATA               101

// Display 관련 에러 
#define R_BGDRAW_FAILED		200
#define R_OBJDRAW_FAILED	201
#define R_FGDRAW_FAILED		202
#define R_MAXZOOM_FAILED	203
#define R_MINZOOM_FAILED	204
#define R_BITBLT_FAILED     205
#define R_INITIAL_FAILED    206

#define R_INVALID_VALUE		210
#define R_INVALID_DC		211

// 메모리 관련 
#define R_INVALID_POINTER   300
#define R_MALLOC_FAILED     301
#define R_REALLOC_FAILED    302
#define R_ACCESS_VIOLATION  303
#define R_BUFFER_OVERFLOW   304

//화일 처리 관련
#define R_NOTFOUND          350
#define R_FILE_OPEN_ERROR   360
#define R_INVALID_MARKFILE  361 
#define R_INVALID_SCRFILE   362
#define R_INVALID_DEVFILE   363


//유저 체크 관련
#define R_LOGOUT            370
#define R_NOTFOUND_USERNAME 375
#define R_NOTFOUND_PASSWORD 376
#define R_NOTFOUND_DATA     377
#define R_USER_LOAD_FAIL    380


//시리얼 
#define R_SERIAL_END        400 // 시리얼 증가 끝났을때.
#define R_SERIAL_FAIL       401 //조건이 맞지 않아 업데이트가 되지 않을때 



//오브젝트 처리 관련.
#define R_BARCODE_CREATE_FAILED   450

// 커팅 영역
#define R_INVALID_AREA      500
#define R_NOT_CHECKED_DATA  501
#endif //_RETURN

