 // CommunicateTable.cpp: implementation of the CCommunicateTable class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "BeamEditor6.h"
#include "CommunicateTable.h"
#include "PointerManager.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCommunicateTable::CCommunicateTable()
{

}

CCommunicateTable::~CCommunicateTable()
{

}

CCommunicateTable* CCommunicateTable::m_pCommunicateTable = 0;
CCommunicateTable* CCommunicateTable::GetInstance()
{
	if (m_pCommunicateTable == 0) {
		m_pCommunicateTable = new CCommunicateTable;
	}
	return m_pCommunicateTable;
}

UINT CCommunicateTable::LoadCommunicateFile(CString FileName, CString WorkingDirectory)
{
	CPointerManager *pPointerManager = pPointerManager->GetInstance();
	FILE *communicateFile;
	char cLine[30];
//	wchar_t cLine[30];
	char cIndex[20];
	char cVariable[20];
	int result;
	CComm *pComm;
	
	communicateFile = fopen(WorkingDirectory + "\\" + FileName, "rt");
	if (communicateFile == NULL) {
		return FALSE;
	}

	do {
// 		result = fscanf(communicateFile, "%s\n", cLine); // Release mode관련 범인ㅡㅡ;;
// 		result = fwscanf(communicateFile, "%s\n", cLine); // Release mode관련 범인ㅡㅡ;;
		result = fscanf(communicateFile, "%[^\n]", cLine);
		if (result == -1)
			break;

		fgetc(communicateFile);
		if (!strcmp(cLine, "[END]")) {
			/* PUSH */
			if (m_strMethod == "RS232") {
				pComm = new CComm(m_strOwner, m_strMethod, m_strPort, m_strBaud, m_strData, m_strParity, m_strStopBit, pPointerManager->GetDlgComm());
				pPointerManager->GetDlgComm()->GetCommList()->Append(pComm);
			}
			else if (m_strMethod == "LAN") {
				pComm = new CComm(m_strOwner, m_strMethod, m_strLocalDevice, m_strNetworkPath, pPointerManager->GetDlgComm());
				pPointerManager->GetDlgComm()->GetCommList()->Append(pComm);
			}
			else if (m_strMethod == "LANSOCKET") {
				pComm = new CComm(m_strOwner, m_strMethod, m_strSocketType, m_strIPAddress, m_strPortNum, pPointerManager->GetDlgComm());
				pPointerManager->GetDlgComm()->GetCommList()->Append(pComm);
			}
		}
		if (strcmp(cLine, "[COMMUNICATION]") != 0 && strcmp(cLine, "[START]") != 0 && strcmp(cLine, "[END]") != 0) {
			for (int i=0; cLine[i] != NULL; i++) {
				cIndex[i] = cLine[i];
				if (cLine[i] == '=') {
					cIndex[i] = '\0';
					int j=0;
					for (j = 0; cLine[++i] != NULL; j++) {
						cVariable[j] = cLine[i];
					}
					cVariable[j] = '\0';
					break;
				}
			}
			SetVariable(cIndex, cVariable);
		}
	} while (TRUE);

	fclose(communicateFile);
	
	return TRUE;
}

UINT CCommunicateTable::SaveCommunicateFile(CString FileName, CString WorkingDirectory)
{
	// 저장 구현 해야함
	FILE *communicateFile;

	communicateFile = fopen(WorkingDirectory + "\\" + FileName, "wt");
	if (communicateFile == NULL) {
		return FALSE;
	}

	// 2007.01.22   - 파일 포인터 닫아줌
	fclose(communicateFile);

	return TRUE;
}

void CCommunicateTable::SetVariable(CString Index, CString Variable)
{
	if (strcmp(Index, "OWNER") == 0) {
		m_strOwner = Variable;
	}
	else if (strcmp(Index, "METHOD") == 0) {
		m_strMethod = Variable;
	}
	else if (strcmp(Index, "PORT") == 0) {
		m_strPort = Variable;
	}
	else if (strcmp(Index, "BAUD") == 0) {
		m_strBaud = Variable;
	}
	else if (strcmp(Index, "DATA") == 0) {
		m_strData = Variable;
	}
	else if (strcmp(Index, "PARITY") == 0) {
		m_strParity = Variable;
	}
	else if (strcmp(Index, "STOP") == 0) {
		m_strStopBit = Variable;
	}
	else if (strcmp(Index, "LOCALDEVICE") == 0) {
		m_strLocalDevice = Variable;
	}
	else if (strcmp(Index, "NETWORKPATH") == 0) {
		m_strNetworkPath = Variable;
	}
	else if (strcmp(Index, "SOCKETTYPE") == 0) {
		m_strSocketType = Variable;
	}
	else if (strcmp(Index, "IPADDRESS") == 0) {
		m_strIPAddress = Variable;
	}
	else if (strcmp(Index, "PORTNUMBER") == 0) {
		m_strPortNum = Variable;
	}
}
