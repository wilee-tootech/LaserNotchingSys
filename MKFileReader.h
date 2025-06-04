#ifndef _MKFileReader
#define _MKFileReader

#define NODE_OBJECT			1
#define NODE_PARAMETER		2
#define NODE_DEVICE         3

class CMKFileReader     // ��ũ ������ �ٷ��. //�ٸ� ���ϵ� �ٷ���� �ִ�. ������ ���ٸ� 
{
public:
	CMKFileReader();
	virtual ~CMKFileReader();

	
	char *GetAt(const char *srcData, DWORD dwFindID, DWORD &dwGetSize, DWORD &dwGetID); 
	//�ַ� �޾ƿ� ����Ÿ�� ��Ʈ���϶� ���Լ� ����.
	char *GetAt(const char *srcData, DWORD dwFindID, DWORD &dwGetSize); //��� ���� 


	UINT GetAt(const char *srcData, DWORD dwFindID, void *GetData);
	
	//�ַ� �޾ƿ� ����Ÿ�� INT, DWORD, LONG, CHAR, SHORT ���϶�  �� �Լ��� ���Եȴ�.

	char *GetNext(const char *srcData,  DWORD &dwGetID, DWORD &dwGetSize);  
	//SeekInit �ѹ� ���� ���� GetNext�Լ��� �ùٷ� ����� �� �ִ�. 

	void SeekInit();

	

	// ���� ����Ÿ�� �ش��ϴ� ������Ʈ�� �ٷ� �����ش�.
	
private:
	DWORD m_dwTableSize;
	DWORD m_dwCurPos;   //���̺���� ��ġ.
	DWORD m_dwReadingPos;

private:
	DWORD GetDWORD(const char *srcData);

	
};

// Ư�����̵� �ش��ϴ� ������Ʈ�� ã�� ����� �迭�� ������� �о���� ����ΰ����� ��� �����ؾ��Ѵ�.

/* [TableSize][ID][Size][Position][ID][Size][Position][ID][Size][Position]...
      4Byte  4Byte 4Byte 4Byte   4Byte 4Byte  4Byte   4Byte 4       4

  ����Ÿ ����:[Data] [Data] [Data] [Data] [Data] [Data]
			  ������ ������ ������ ������ ������ ������ 
	�ϳ���[Data]���� Table�� ������ �� �ڽĵ��� ������ �ִ�. 
	���� ��� ������ �̷���.

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

  �ᱹ ��� ������Ʈ���� Restore�� �Լ�(����)�� Serialize�� �Լ�(����)�� �־���Ѵ�.
*/

/* CArchive�� CMemFile �̿� �ؼ� ���� �� �ε� �׽�Ʈ  �Ϸ�. */

#endif //_MKFileReader
