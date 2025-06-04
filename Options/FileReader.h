#ifndef _FileReader
#define _FileReader

#define NODE_OBJECT			1
#define NODE_PARAMETER		2
#define NODE_DEVICE         3

class CFileReader
{
public:
	CFileReader();
	virtual ~CFileReader();	
	char *GetAt(const char *srcData, DWORD dwFindID, DWORD &dwGetSize, DWORD &dwGetID); 
	UINT GetAt(const char *srcData, DWORD dwFindID, void *GetData);
	char *GetNext(const char *srcData,  DWORD &dwGetID, DWORD &dwGetSize);  
	void SeekInit();
	
private:
	DWORD m_dwTableSize;
	DWORD m_dwCurPos;
	DWORD m_dwReadingPos;

private:
	DWORD GetDWORD(const char *srcData);

};

#endif
