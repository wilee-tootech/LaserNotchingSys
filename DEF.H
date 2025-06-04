// m_ViewSelector의 헤더 파일
#define VIEW_NOTHING 0
#define VIEW_FONT 1

// 파일 선택자
#define NONE		0
#define FONTFILE	1
#define HPGLFILE	2
#define MKOBJFILE	3

// point manager state
#define IDLE 0
#define ONE_SELECTED 1
#define TWO_SELECTED 2
#define GROUP_SELECTED 100

// current work state
#define IDLE			0
#define MOVE_ONE_POINT	1
#define MOVE_GROUP_POINT 11
#define MOVE_OFFSET		2
#define MOVE_LINE		3
#define DELETE_VECTOR	4
#define DELETE_GROUP_VECTOR 12
#define CHANGE_PEN_TYPE	5
#define DRAW_LINE		6
#define DRAW_RECT		7
#define DRAW_RANRECT	8
#define DRAW_ELLIP		9
#define DRAW_ROUNTD_RECT 10
#define SELECT_GROUP_POINT 13
#define DRAW_GROUP_POINT 14

// character show flag
#define SHOW_ALL_VECTOR			0
#define SHOW_LINEVECTOR_POINTVECTOR	1
#define SHOW_LINEVECTOR			2

// draw define 
#define ELLIP_ANGLE		15
#define EDGE_SPACE		10

// 파일 선택 
#define DEVICEFILE   1
#define SCRIBE1  2 // save all
#define SCRIBE2  3 // save used
#define MARK     4
#define OBJECT   5
#define FORM     6

#define MAXBIN	 8
#define PINNUM_IN_A_BIN 8
/*
#define EMPTY 0
#define STEXT 1
#define RTEXT 2
#define HPGL  3
#define BMP	  4
#define JPG   5
#define GIF   6
#define CODE39 7
#define BITIMG 8
*/

// USER MESSAGE
#define WM_USER_PATHCHANGED WM_USER+10

// 이미지 리스트 상의 index
#define ID_FLOPPY	0
#define ID_HARDDISK	1
#define ID_CDROM	2
#define ID_NETDRIVE	3
#define ID_CLOSEDFOLDER	4
#define ID_OPENFOLDER	5

// 단위
#define MM		0	// 1
#define FIELD	1	// 3
#define POINT	2	// 0
#define MIL		3	// 2
