#ifndef _MKFileReader
#define _MKFileReader

#define NODE_OBJECT			1
#define NODE_PARAMETER		2
#define NODE_DEVICE         3

class CMKFileReader     // 마크 파일을 다룬다. //다른 파일도 다룰수도 있다. 형식이 같다면 
{
public:
	CMKFileReader();
	virtual ~CMKFileReader();

	
	char *GetAt(const char *srcData, DWORD dwFindID, DWORD &dwGetSize, DWORD &dwGetID); 
	//주로 받아올 데이타가 스트링일때 이함수 쓴다.
	char *GetAt(const char *srcData, DWORD dwFindID, DWORD &dwGetSize); //축약 버젼 


	UINT GetAt(const char *srcData, DWORD dwFindID, void *GetData);
	
	//주로 받아올 데이타가 INT, DWORD, LONG, CHAR, SHORT 형일때  이 함수를 쓰게된다.

	char *GetNext(const char *srcData,  DWORD &dwGetID, DWORD &dwGetSize);  
	//SeekInit 한번 실행 한후 GetNext함수를 올바로 사용할 수 있다. 

	void SeekInit();

	

	// 얻은 데이타는 해당하는 오브젝트에 바로 던져준다.
	
private:
	DWORD m_dwTableSize;
	DWORD m_dwCurPos;   //테이블상의 위치.
	DWORD m_dwReadingPos;

private:
	DWORD GetDWORD(const char *srcData);

	
};

// 특정아이디에 해당하는 오브젝트를 찾는 방법과 배열된 순서대로 읽어오는 방법두가지가 모두 존재해야한다.

/* [TableSize][ID][Size][Position][ID][Size][Position][ID][Size][Position]...
      4Byte  4Byte 4Byte 4Byte   4Byte 4Byte  4Byte   4Byte 4       4

  데이타 시작:[Data] [Data] [Data] [Data] [Data] [Data]
			  가변적 가변적 가변적 가변적 가변적 가변적 
	하나의[Data]또한 Table을 가지고 또 자식들을 가질수 있다. 
	예를 들어 구조는 이렇다.

	*FILE -  OBJECT     -Barcode   - Height
								   - Width
								   - X
								   - Y
								     .
									 .

	                    -Text
						-Matrix
						  .
						  .



          -  PARAMETER  - 1
		                - 2
						- 3
						  .	
						  .


	
		  -  DEVICE - XPitch
					- YPitch
					   .
					   .

  결국 모든 오브젝트들은 Restore란 함수(복구)와 Serialize란 함수(저장)가 있어야한다.
*/

/* CArchive과 CMemFile 이용 해서 저장 및 로드 테스트  완료. */

#endif //_MKFileReader
