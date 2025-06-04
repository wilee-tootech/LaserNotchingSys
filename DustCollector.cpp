// DustCollector.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "BeamEditor6.h"
#include "DustCollector.h"
#include "afxdialogex.h"
#include "WriteLog.h"
#include <pdh.h>
#include "PointerContainer.h"
#include "FieldParameter.h"
#include "InitialTable.h"
#include "MainFrm.h"
#include <iostream>
#include <vector>
#include <sstream>
#include <iomanip>
#pragma comment(lib, "pdh.lib")



// CDustCollector 대화 상자입니다.

IMPLEMENT_DYNAMIC(CDustCollector, CUserDialogEx)


int CDustCollector::nCountLaserMonitoring = 0;
double CDustCollector::dHead1Total = 0.0;
double CDustCollector::dHead2Total = 0.0;



#define TM_CPU 0x001
#define TM_POWER 0x002
#define TM_DUSTTRAP 0X003
#define TM_OPENPORT 0x004
#define TM_SCANNER_STATUS 0x005

#define memoryInterval 5000

// CPU 사용률을 가져오는 함수
double GetCPUUsage() {
	PDH_HQUERY query;
	PDH_HCOUNTER counter;
	PDH_FMT_COUNTERVALUE counterValue;

	// PDH 쿼리 생성
	if (PdhOpenQuery(NULL, NULL, &query) != ERROR_SUCCESS) {
		return -1.0;
	}

	// Processor의 % Processor Time 카운터를 추가
	if (PdhAddCounter(query, TEXT("\\Processor(_Total)\\% Processor Time"), NULL, &counter) != ERROR_SUCCESS) {
		PdhCloseQuery(query);
		return -1.0;
	}

	// 첫 번째 데이터 수집 (정확한 값을 얻기 위해서는 두 번 이상 수집이 필요)
	PdhCollectQueryData(query);
	Sleep(1000); // 1초 대기

	// 두 번째 데이터 수집 및 결과 얻기
	PdhCollectQueryData(query);
	if (PdhGetFormattedCounterValue(counter, PDH_FMT_DOUBLE, NULL, &counterValue) != ERROR_SUCCESS) {
		PdhCloseQuery(query);
		return -1.0;
	}

	// 쿼리 종료
	PdhCloseQuery(query);

	return counterValue.doubleValue;
}

// 메모리 사용률을 가져오는 함수
double GetMemoryUsage() {
	MEMORYSTATUSEX memInfo;
	memInfo.dwLength = sizeof(MEMORYSTATUSEX);

	if (GlobalMemoryStatusEx(&memInfo)) {
		DWORDLONG totalPhysMem = memInfo.ullTotalPhys;
		DWORDLONG physMemUsed = memInfo.ullTotalPhys - memInfo.ullAvailPhys;
		return (double)(physMemUsed) / totalPhysMem * 100.0;
	}

	return -1.0;
}

unsigned short CDustCollector::CRC16(char *data, int dataSize)
{
    unsigned short crc16 = 0xFFFF;

    for (int n = 0; n < dataSize; n++)
    {
        unsigned short ch = (unsigned short)data[n];
        crc16 ^= ch;

        for (int i = 0; i < 8; i++)
        {
            if ((crc16 & 0x0001) == 0x0001)
            {
                crc16 >>= 1;
                crc16 ^= 0xA001;
            }
            else
            {
                crc16 >>= 1;
            }
            ch >>= 1;
        }
    }
    return crc16;
}


void CDustCollector::intToByteArray16(int intData, BYTE* byteArr)
{
	union {
        int intValue;
        UINT32 uintValue;
    } converter;

    converter.intValue = intData;

    byteArr[0] = static_cast<BYTE>(converter.uintValue & 0x000000ff);
    byteArr[1] = static_cast<BYTE>((converter.uintValue & 0x0000ff00) >> 8);
}

CDustCollector::CDustCollector(CWnd* pParent /*=NULL*/)
	: CUserDialogEx(CDustCollector::IDD, pParent)
{
	// Communicate.ini 파일에서 읽어오는걸로 수정 2024.10.17 1352 LDY
}

void CDustCollector::OpenPort()
{
	CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();;CString strLogEvent = TEXT("");
	// 생성자에서 첫번째 항목인 흡기온도를 보냄
	unsigned short startAddress = 1000;
	unsigned short numOfPoints = 1;

	// 흡기온도 체크
	BYTE byteArray[2];
	m_buf[0] = 0x01;
	m_buf[1] = 0x04;
	m_buf[2] = 0x03; // (byte)(startAddress >> 8);
	m_buf[3] = 0xE8;// (byte)(startAddress & 0xFF);
	m_buf[4] = 0x00;// (byte)(numOfPoints >> 8);
	m_buf[5] = 0x01;// (byte)(numOfPoints & 0xFF);

	unsigned short crc16 = CRC16((char*)m_buf, 6);

	intToByteArray16(crc16,byteArray);

	// crc16
	m_buf[6] = 0xB1; // byteArray[0];
	m_buf[7] = 0xBA; // byteArray[1];

	SendData((LPCTSTR)m_buf, 8);
}



CDustCollector::~CDustCollector()
{
}

void CDustCollector::DoDataExchange(CDataExchange* pDX)
{
	CUserDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDustCollector, CUserDialogEx)
	ON_WM_TIMER()
	ON_MESSAGE(WM_MYRECEIVE, ReceiveData)

	ON_BN_CLICKED(IDOK, &CDustCollector::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &CDustCollector::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON_TOGGLE, &CDustCollector::OnBnClickedButtonToggle)
	ON_BN_CLICKED(IDC_BUTTON2, &CDustCollector::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CDustCollector::OnBnClickedButton3)
END_MESSAGE_MAP()


// CDustCollector 메시지 처리기입니다.


void CDustCollector::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

float CDustCollector::byteArrayToFloat32(const BYTE* byteArr)
{
    // Use a union to reinterpret the bytes of the integer as a float
    union {
        float floatValue;
        int intValue;
    } converter;

    // Combine the bytes into an integer representation in Little Endian order
    converter.intValue = static_cast<int>(byteArr[0])
                      | (static_cast<int>(byteArr[1]) << 8)
                      | (static_cast<int>(byteArr[2]) << 16)
                      | (static_cast<int>(byteArr[3]) << 24);

    return converter.floatValue;
}



LRESULT CDustCollector::ReceiveData(WPARAM wParam, LPARAM lParam)
{
	float convertedFloat  = 0.0;
	CString str, adress;
	CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();;CString strLogEvent = TEXT("");
	int nDataSize = (int)wParam;

	// 결국 4번인덱스만 사용할거임 일단 대기.
	// 그리고 반환값으로 if문 처리해서 꼬리물기로
	adress = str = "";
	if(m_Comm)
	{
		if(nDataSize > 6)
		{
			m_Comm->Receive(m_data,wParam);
			CString tmpLogStr, tmpLog;
			tmpLogStr = "";
			for(int i = 0; i< nDataSize; i++)
			{
				tmpLog.Format("0x%02x", (BYTE)m_data[i]);
				tmpLogStr += tmpLog;
			}
			CString tmpDataSize;
			tmpDataSize.Format("Receive Data Size : %d, Data : %s\n", nDataSize, tmpLogStr);


			// pMainFrm->AddLogData(tmpDataSize);


			pMainFrm->AddLogData(tmpDataSize);

			// 무슨데이터인지 주소 받아야함.
			adress.Format("%d", m_data[0]); // 0번인덱스가 국번
			if(adress == "4")
			{
				m_ReadData[0] = (BYTE)m_data[4];
				m_ReadData[1] = (BYTE)m_data[3];
				m_ReadData[2] = (BYTE)m_data[6];
				m_ReadData[3] = (BYTE)m_data[5];

				UINT32 dwWord = 0;
				for (int j = 0; j < 4; j++) {
					dwWord |= ((UINT32)(m_ReadData[j]) << (j * 8));
				}
				std::memcpy(&convertedFloat, &dwWord, sizeof(dwWord));
				std::cout << "FloatDate (as float): " << convertedFloat << std::endl;
				std::string ConvertData = std::to_string(convertedFloat);
				double Data = std::stod(ConvertData);

				// convertedFloat = byteArrayToFloat32(m_ReadData);

				str.Format("%0.2f", Data);
			} else if(adress == "5")
			{
				int nConverterData = convertBufferToInt(m_data);
				int nUpdateData = (nConverterData / 10);
				str.Format("%d", nUpdateData);

			} else if(adress == "6")
			{
				int nConverterData = convertBufferToInt(m_data);
				double updateData = (nConverterData / 100) - 1.3;
				str.Format("%0.2f", updateData);
			} else
			{
				str.Format("%d",  (BYTE)m_data[4]);
			}
		
			// 여기서 str을 다른함수에서 처리 - 근데 값만 받는게아닌 무슨데이터인지 필요
			pMainFrm->AddLogData("Receive Data - Address : " + adress + ", Data : " + str);
			StrParsing(adress, str);
		}
		else
		{
			// 만약 데이터가 전체가 오지 않았다면 1번부터 다시 시작
			OpenPort();
		}
	}
	return 0;
}

int CDustCollector::convertBufferToInt(char* buffer) {
    // Converter 배열 생성
    m_Converter[0] = (BYTE)buffer[3];
    m_Converter[1] = (BYTE)buffer[4];

    // hex 값으로 변경
    std::ostringstream oss;
    for (int i = 0; i < 2; ++i) {
        oss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(m_Converter[i]);
    }
    std::string hex = oss.str();

    // 정수로 변환
    int value = std::stoi(hex, nullptr, 16);

    return value;
}

void CDustCollector::StrParsing(CString adress, CString str)
{
	CMainFrame *pMainFrm = (CMainFrame*)AfxGetMainWnd();
	pMainFrm->AddLogData("StrParsing Start");

	// 집진기 데이터 파싱하는 함수 - 주소 어떻게 들어오는지 확인필요
	// 파싱하면서 바로 출력까지 같이
	unsigned short startAddress;
	unsigned short numOfPoints;

	if(adress == "1")
	{
		// 출력 후 꼬리물기 - 순서대로인지도 확인필요
		// 흡기온도 출력
		SetDlgItemText(IDC_CTTEXT_IN_TEMP, str);
		if(m_pDlgMES)
		{
			m_pDlgMES->m_dDustCollectorTemp = _ttoi(str);
		}

		// 배기온도 보내기
		startAddress = 1000;
		numOfPoints = 1;

		BYTE byteArray[2];
		m_buf[0] = 0x02;
		m_buf[1] = 0x04;
		m_buf[2] = 0x03;//(byte)(startAddress >> 8);
		m_buf[3] = 0xE8;//(byte)(startAddress & 0xFF);
		m_buf[4] = 0x00;//(byte)(numOfPoints >> 8);
		m_buf[5] = 0x01;//(byte)(numOfPoints & 0xFF);

		unsigned short crc16 = CRC16((char*)m_buf, 6);

		intToByteArray16(crc16,byteArray);

		// crc16
		m_buf[6] = 0xB1; // byteArray[0];
		m_buf[7] = 0x89; // byteArray[1];

		SendData((LPCTSTR)m_buf, 8);


	} else if(adress == "2")
	{
		// 배기온도 출력 - QMS 이벤트로 올라가지 않음
		SetDlgItemText(IDC_CTTEXT_EXHAUST_TEMP, str);
		// m_pDlgMES->m_dDustCollectorTemp = _ttoi(str);

		// 차압 보내기
		startAddress = 1;
		numOfPoints = 1;

		BYTE byteArray[2];
		m_buf[0] = 0x03;
		m_buf[1] = 0x04;
		m_buf[2] = 0x00; //(byte)(startAddress >> 8);
		m_buf[3] = 0x01; //(byte)(startAddress & 0xFF);
		m_buf[4] = 0x00; //(byte)(numOfPoints >> 8);
		m_buf[5] = 0x01; //(byte)(numOfPoints & 0xFF);

		unsigned short crc16 = CRC16((char*)m_buf, 6);

		intToByteArray16(crc16,byteArray);

		// crc16
		m_buf[6] = 0x61; // byteArray[0];
		m_buf[7] = 0xE8; // byteArray[1];

		SendData((LPCTSTR)m_buf, 8);


	} else if(adress == "3")
	{
		// 차압 출력
		SetDlgItemText(IDC_CTTEXT_ATTACH, str);
		if(m_pDlgMES)
		{
			m_pDlgMES->m_dDustCollectorAttach = _ttoi(str);
		}

		// 풍속 보내기
		startAddress = 7010;
		numOfPoints = 2;

		BYTE byteArray[2];
		m_buf[0] = 0x04;
		m_buf[1] = 0x03;
		m_buf[2] = 0x1B; //(byte)(startAddress >> 8);
		m_buf[3] = 0x62; //(byte)(startAddress & 0xFF);
		m_buf[4] = 0x00; //(byte)(numOfPoints >> 8);
		m_buf[5] = 0x02; //(byte)(numOfPoints & 0xFF);

		unsigned short crc16 = CRC16((char*)m_buf, 6);

		intToByteArray16(crc16,byteArray);

		// crc16
		m_buf[6] = 0x63; // byteArray[0];
		m_buf[7] = 0x64;// byteArray[1];

		SendData((LPCTSTR)m_buf, 8);

	
	} else if(adress == "4")
	{
		// 풍속 출력
		SetDlgItemText(IDC_CTTEXT_DUSTTRAP, str);
		if(m_pDlgMES)
		{
			m_pDlgMES->m_dDustCollector = _ttoi(str);
		}
		// 인버터 보내기
		startAddress = 783;
		numOfPoints = 1;

		BYTE byteArray[2];
		m_buf[0] = 0x05;
		m_buf[1] = 0x03;
		m_buf[2] = 0x03; //(byte)(startAddress >> 8);
		m_buf[3] = 0x0F; //(byte)(startAddress & 0xFF);
		m_buf[4] = 0x00; //(byte)(numOfPoints >> 8);
		m_buf[5] = 0x01; //(byte)(numOfPoints & 0xFF);

		unsigned short crc16 = CRC16((char*)m_buf, 6);

		intToByteArray16(crc16,byteArray);

		// crc16
		m_buf[6] = 0xB5;// byteArray[0];
		m_buf[7] = 0xC9;// byteArray[1];

		SendData((LPCTSTR)m_buf, 8);


	} else if(adress == "5")
	{
		// 인버터 출력
		SetDlgItemText(IDC_CTTEXT_INVERTER, str);
		if(m_pDlgMES)
		{
			m_pDlgMES->m_dDustCollectorInverter = _ttoi(str);
		}

		// 소석회 잔량 보내기
		startAddress = 8;
		numOfPoints = 1;

		BYTE byteArray[2];
		m_buf[0] = 0x06;
		m_buf[1] = 0x04;
		m_buf[2] = 0x00; // (byte)(startAddress >> 8);
		m_buf[3] = 0x02; // (byte)(startAddress & 0xFF);
		m_buf[4] = 0x00; // (byte)(numOfPoints >> 8);
		m_buf[5] = 0x01; // (byte)(numOfPoints & 0xFF);

		unsigned short crc16 = CRC16((char*)m_buf, 6);

		intToByteArray16(crc16,byteArray);

		// crc16
		m_buf[6] = 0x91;// byteArray[0];
		m_buf[7] = 0xBD;// byteArray[1];

		SendData((LPCTSTR)m_buf, 8);


	} else if(adress == "6") // 5개 값밖에없음
	{
		// 소석회 출력
		SetDlgItemText(IDC_CTTEXT_SLACK, str);
		if(m_pDlgMES)
		{
			m_pDlgMES->m_dDustCollectorSlack = _ttoi(str);
		}
		// 처음으로 돌아와서 풍속
		startAddress = 1000;
		numOfPoints = 1;

		// 흡기온도 체크
		BYTE byteArray[2];
		m_buf[0] = 0x01;
		m_buf[1] = 0x04;
		m_buf[2] = 0x03; //(byte)(startAddress >> 8);
		m_buf[3] = 0xE8; //(byte)(startAddress & 0xFF);
		m_buf[4] = 0x00; //(byte)(numOfPoints >> 8);
		m_buf[5] = 0x01; //(byte)(numOfPoints & 0xFF);

		unsigned short crc16 = CRC16((char*)m_buf, 6);
		
		intToByteArray16(crc16,byteArray);

		// crc16
		m_buf[6] = 0xB1; // byteArray[0];
		m_buf[7] = 0xBA; // byteArray[1];

		SendData((LPCTSTR)m_buf, 8);
	} 
	else
	{
		// 이상한데이터
	}
	pMainFrm->AddLogData("StrParsing End");

	
}

void CDustCollector::SendData(LPCTSTR m_buf, int size)
{
	CMainFrame *pMainFrm = (CMainFrame*)AfxGetMainWnd();
	
	if(m_Comm)
	{
		SetDelayTime(500);
		m_Comm->Send((LPCTSTR)m_buf, 8);
	} else
	{
		pMainFrm->AddLogData("DustCollector Send Fail");
	}
}




void CDustCollector::OnTimer(UINT_PTR nIDEvent)
{
	CMainFrame *pMainFrm = (CMainFrame*)AfxGetMainWnd();
	if(nIDEvent == TM_CPU )
	{
		// CPU 및 메모리 사용률 출력
		double cpuUsage = GetCPUUsage();
		double memUsage = GetMemoryUsage();
		CString str;
		str.Format("CPU사용률: %.2f, 메모리 사용률: %.2f", cpuUsage, memUsage);
		SetDlgItemText(IDC_CTTEXTCTRL_CPU, str);

		
	} else if(nIDEvent == TM_POWER)
	{
		CFieldParameter *pFieldParameter = pFieldParameter->GetInstance();
		double head1Power = pFieldParameter->GetHEAD1LaserPower();
        double head2Power = pFieldParameter->GetHEAD2LaserPower();

		CString strHEAD1Power;
		strHEAD1Power.Format("HEAD1 POWER : %.2f(W)",  head1Power);
		SetDlgItemText(IDC_CTTEXTCTRL_HEAD1_POWER, strHEAD1Power);

		CString strHEAD2Power;
		strHEAD2Power.Format("HEAD2 POWER : %.2f(W)",  head2Power);
		SetDlgItemText(IDC_CTTEXTCTRL_HEAD2_POWER, strHEAD2Power);


		dHead1Total += head1Power;
        dHead2Total += head2Power;
        nCountLaserMonitoring++;

        if(nCountLaserMonitoring >= 2) // 500ms * 2 = 1초
        {
            // 평균값 계산
            double avgHead1Power = dHead1Total / nCountLaserMonitoring;
            double avgHead2Power = dHead2Total / nCountLaserMonitoring;

            // 로그 기록
            CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();;CString strLogEvent = TEXT(""); // 객체 생성
            CString strTmpLog;
            strTmpLog.Format("HEAD1 POWER : %.2f, HEAD2 POWER : %.2f", avgHead1Power, avgHead2Power);
            pMainFrm->AddLogData(strTmpLog);

            // 변수 초기화
            nCountLaserMonitoring = 0;
            dHead1Total = 0.0;
            dHead2Total = 0.0;
        }
	} else if(nIDEvent == TM_OPENPORT)
	{
		KillTimer(TM_OPENPORT);
		CMainFrame *pMainFrm = (CMainFrame*)AfxGetMainWnd();
		m_pDlgMES = pMainFrm->GetDlgMES();

		CInitialTable *pInitialTable = pInitialTable->GetInstance();
		
		if(pInitialTable->GetHead1Name() == "Anode")
		{
			m_Comm = new CPYH_Comm("\\\\.\\COM9","9600","None","8 Bit","1 Bit");
			if(	m_Comm->Create(GetSafeHwnd()) != 0)	//통신포트를 열고 윈도우의 핸들을 넘긴다.
			{
				pMainFrm->AddLogData("집진기 통신 오픈 성공");
				m_Comm->Clear(); // 쓰레기 있을까봐 미리 클리어
			}
			else
			{
				pMainFrm->AddLogData("집진기 통신 오픈 실패");
			}
		}
		OpenPort();
		
	} else if(nIDEvent == TM_SCANNER_STATUS)
	{
		UINT nTmpData, uData;
		double dData;
		CString strData;
		//////////////////////// AGC-Voltage ///////////////////////////
		n_control_command (RTC_CARD_NUM_1, 1, 1, 0x0516); 
		Sleep(10);
		nTmpData = n_get_value(RTC_CARD_NUM_1, 1);
		uData = nTmpData & 0xFFFF;
		dData = uData / 1600.0; 
		strData.Format("%0.2f", dData);
		SetDlgItemText(IDC_CTTEXT_AGC_VOLTAGE_X_HEAD1, strData);

		n_control_command (RTC_CARD_NUM_1, 1, 2, 0x0516); 
		Sleep(10);
		nTmpData = n_get_value(RTC_CARD_NUM_1, 2);
		uData = nTmpData & 0xFFFF;
		dData = uData / 1600.0; 
		strData.Format("%0.2f", dData);
		SetDlgItemText(IDC_CTTEXT_AGC_VOLTAGE_Y_HEAD1, strData);

		n_control_command (RTC_CARD_NUM_2, 1, 1, 0x0516); 
		Sleep(10);
		nTmpData = n_get_value(RTC_CARD_NUM_2, 1);
		uData = nTmpData & 0xFFFF;
		dData = uData / 1600.0; 
		strData.Format("%0.2f", dData);
		SetDlgItemText(IDC_CTTEXT_AGC_VOLTAGE_X_HEAD2, strData);

		n_control_command (RTC_CARD_NUM_2, 1, 2, 0x0516); 
		Sleep(10);
		nTmpData = n_get_value(RTC_CARD_NUM_2, 2);
		uData = nTmpData & 0xFFFF;
		dData = uData / 1600.0; 
		strData.Format("%0.2f", dData);
		SetDlgItemText(IDC_CTTEXT_AGC_VOLTAGE_Y_HEAD2, strData);
		//////////////////////////////////////////////////////////////
		////////////////////// DSP Core /////////////////////////////
		n_control_command (RTC_CARD_NUM_1, 1, 1, 0x0517); 
		Sleep(10);
		nTmpData = n_get_value(RTC_CARD_NUM_1, 1);
		uData = nTmpData & 0xFFFF;
		dData = uData / 1600.0; 
		strData.Format("%0.2f", dData);
		SetDlgItemText(IDC_CTTEXT_DSP_CORE_X_HEAD1, strData);

		n_control_command (RTC_CARD_NUM_1, 1, 2, 0x0517); 
		Sleep(10);
		nTmpData = n_get_value(RTC_CARD_NUM_1, 2);
		uData = nTmpData & 0xFFFF;
		dData = uData / 1600.0; 
		strData.Format("%0.2f", dData);
		SetDlgItemText(IDC_CTTEXT_DSP_CORE_Y_HEAD1, strData);

		n_control_command (RTC_CARD_NUM_2, 1, 1, 0x0517); 
		Sleep(10);
		nTmpData = n_get_value(RTC_CARD_NUM_2, 1);
		uData = nTmpData & 0xFFFF;
		dData = uData / 1600.0; 
		strData.Format("%0.2f", dData);
		SetDlgItemText(IDC_CTTEXT_DSP_CORE_X_HEAD2, strData);

		n_control_command (RTC_CARD_NUM_2, 1, 2, 0x0517); 
		Sleep(10);
		nTmpData = n_get_value(RTC_CARD_NUM_2, 2);
		uData = nTmpData & 0xFFFF;
		dData = uData / 1600.0; 
		strData.Format("%0.2f", dData);
		SetDlgItemText(IDC_CTTEXT_DSP_CORE_Y_HEAD2, strData);
		//////////////////////////////////////////////////////////////////
		////////////////////// DSP IO /////////////////////////////
		n_control_command (RTC_CARD_NUM_1, 1, 1, 0x0518); 
		Sleep(10);
		nTmpData = n_get_value(RTC_CARD_NUM_1, 1);
		uData = nTmpData & 0xFFFF;
		dData = uData / 1600.0; 
		strData.Format("%0.2f", dData);
		SetDlgItemText(IDC_CTTEXT_DSP_IO_X_HEAD1, strData);

		n_control_command (RTC_CARD_NUM_1, 1, 2, 0x0518); 
		Sleep(10);
		nTmpData = n_get_value(RTC_CARD_NUM_1, 2);
		uData = nTmpData & 0xFFFF;
		dData = uData / 1600.0; 
		strData.Format("%0.2f", dData);
		SetDlgItemText(IDC_CTTEXT_DSP_IO_Y_HEAD1, strData);

		n_control_command (RTC_CARD_NUM_2, 1, 1, 0x0518); 
		Sleep(10);
		nTmpData = n_get_value(RTC_CARD_NUM_2, 1);
		uData = nTmpData & 0xFFFF;
		dData = uData / 1600.0; 
		strData.Format("%0.2f", dData);
		SetDlgItemText(IDC_CTTEXT_DSP_IO_X_HEAD2, strData);

		n_control_command (RTC_CARD_NUM_2, 1, 2, 0x0518); 
		Sleep(10);
		nTmpData = n_get_value(RTC_CARD_NUM_2, 2);
		uData = nTmpData & 0xFFFF;
		dData = uData / 1600.0; 
		strData.Format("%0.2f", dData);
		SetDlgItemText(IDC_CTTEXT_DSP_IO_Y_HEAD2, strData);
		//////////////////////////////////////////////////////////////////
		////////////////////// ADC /////////////////////////////
		n_control_command (RTC_CARD_NUM_1, 1, 1, 0x051A); 
		Sleep(10);
		nTmpData = n_get_value(RTC_CARD_NUM_1, 1);
		uData = nTmpData & 0xFFFF;
		dData = uData / 1600.0; 
		strData.Format("%0.2f", dData);
		SetDlgItemText(IDC_CTTEXT_ADC_X_HEAD1, strData);

		n_control_command (RTC_CARD_NUM_1, 1, 2, 0x051A); 
		Sleep(10);
		nTmpData = n_get_value(RTC_CARD_NUM_1, 2);
		uData = nTmpData & 0xFFFF;
		dData = uData / 1600.0; 
		strData.Format("%0.2f", dData);
		SetDlgItemText(IDC_CTTEXT_ADC_Y_HEAD1, strData);

		n_control_command (RTC_CARD_NUM_2, 1, 1, 0x051A); 
		Sleep(10);
		nTmpData = n_get_value(RTC_CARD_NUM_2, 1);
		uData = nTmpData & 0xFFFF;
		dData = uData / 1600.0; 
		strData.Format("%0.2f", dData);
		SetDlgItemText(IDC_CTTEXT_ADC_X_HEAD2, strData);

		n_control_command (RTC_CARD_NUM_2, 1, 2, 0x051A); 
		Sleep(10);
		nTmpData = n_get_value(RTC_CARD_NUM_2, 2);
		uData = nTmpData & 0xFFFF;
		dData = uData / 1600.0; 
		strData.Format("%0.2f", dData);
		SetDlgItemText(IDC_CTTEXT_ADC_Y_HEAD2, strData);
		//////////////////////////////////////////////////////////////////
		////////////////////// ADC /////////////////////////////
		n_control_command (RTC_CARD_NUM_1, 1, 1, 0x0519); 
		Sleep(10);
		nTmpData = n_get_value(RTC_CARD_NUM_1, 1);
		uData = nTmpData & 0xFFFF;
		dData = uData / 1600.0; 
		strData.Format("%0.2f", dData);
		SetDlgItemText(IDC_CTTEXT_ANALLOG_X_HEAD1, strData);

		n_control_command (RTC_CARD_NUM_1, 1, 2, 0x0519); 
		Sleep(10);
		nTmpData = n_get_value(RTC_CARD_NUM_1, 2);
		uData = nTmpData & 0xFFFF;
		dData = uData / 1600.0; 
		strData.Format("%0.2f", dData);
		SetDlgItemText(IDC_CTTEXT_ANALLOG_Y_HEAD1, strData);

		n_control_command (RTC_CARD_NUM_2, 1, 1, 0x0519); 
		Sleep(10);
		nTmpData = n_get_value(RTC_CARD_NUM_2, 1);
		uData = nTmpData & 0xFFFF;
		dData = uData / 1600.0; 
		strData.Format("%0.2f", dData);
		SetDlgItemText(IDC_CTTEXT_ANALLOG_X_HEAD2, strData);

		n_control_command (RTC_CARD_NUM_2, 1, 2, 0x0519); 
		Sleep(10);
		nTmpData = n_get_value(RTC_CARD_NUM_2, 2);
		uData = nTmpData & 0xFFFF;
		dData = uData / 1600.0; 
		strData.Format("%0.2f", dData);
		SetDlgItemText(IDC_CTTEXT_ANALLOG_Y_HEAD2, strData);
		//////////////////////////////////////////////////////////////////
		////////////////////// Position Error /////////////////////////////
		n_control_command (RTC_CARD_NUM_1, 1, 1, 0x0503); 
		Sleep(10);
		nTmpData = n_get_value(RTC_CARD_NUM_1, 1);
		uData = nTmpData & 0xFFFF;
		strData.Format("%d", uData);
		SetDlgItemText(IDC_CTTEXT_POS_ERROR_X_HEAD1, strData);

		n_control_command (RTC_CARD_NUM_1, 1, 2, 0x0503); 
		Sleep(10);
		nTmpData = n_get_value(RTC_CARD_NUM_1, 2);
		uData = nTmpData & 0xFFFF;
		strData.Format("%d", uData);
		SetDlgItemText(IDC_CTTEXT_POS_ERROR_Y_HEAD1, strData);

		n_control_command (RTC_CARD_NUM_2, 1, 1, 0x0503); 
		Sleep(10);
		nTmpData = n_get_value(RTC_CARD_NUM_2, 1);
		uData = nTmpData & 0xFFFF;
		strData.Format("%d", uData);
		SetDlgItemText(IDC_CTTEXT_POS_ERROR_X_HEAD2, strData);

		n_control_command (RTC_CARD_NUM_2, 1, 2, 0x0503); 
		Sleep(10);
		nTmpData = n_get_value(RTC_CARD_NUM_2, 2);
		uData = nTmpData & 0xFFFF;
		strData.Format("%d", uData);
		SetDlgItemText(IDC_CTTEXT_POS_ERROR_Y_HEAD2, strData);
		//////////////////////////////////////////////////////////////////
	}
}


BOOL CDustCollector::OnInitDialog()
{
	CUserDialogEx::OnInitDialog();
	m_bToggleBtn = FALSE;


	// SetTimer(TM_OPENPORT, 2000, NULL);

	return TRUE; 
}


void CDustCollector::OnBnClickedButton1()
{
	// 통신연결 임시
	SetTimer(TM_OPENPORT, 2000, NULL);


}

void CDustCollector::floatToByteArray32(float floatData, BYTE* byteArr)
{
	float tmpfloat = 0.0;
    // Use a union to reinterpret the bits of the float as an integer
    union {
        float floatValue;
        UINT32 intValue;
    } converter;

    converter.floatValue = floatData;

	// Extract the bytes from the integer representation little Endian
	byteArr[0] = static_cast<BYTE>(converter.intValue & 0x000000ff);
    byteArr[1] = static_cast<BYTE>((converter.intValue & 0x0000ff00) >> 8);
    byteArr[2] = static_cast<BYTE>((converter.intValue & 0x00ff0000) >> 16);
    byteArr[3] = static_cast<BYTE>((converter.intValue & 0xff000000) >> 24);

    //// Extract the bytes from the integer representation
    //byteArr[0] = static_cast<BYTE>((converter.intValue & 0xff000000) >> 24);
    //byteArr[1] = static_cast<BYTE>((converter.intValue & 0x00ff0000) >> 16);
    //byteArr[2] = static_cast<BYTE>((converter.intValue & 0x0000ff00) >> 8);
    //byteArr[3] = static_cast<BYTE>(converter.intValue & 0x000000ff);

	tmpfloat = byteArrayToFloat32(byteArr);
}


void CDustCollector::OnBnClickedButtonToggle()
{
	// 모니터링 토글 버튼
	
	if(m_bToggleBtn == FALSE)
	{
		SetTimer(TM_CPU, 5000, NULL);
		SetTimer(TM_POWER, 500, NULL);
		SetDlgItemText(IDC_BUTTON_TOGGLE, "STOP");
		
		m_bToggleBtn = TRUE;

	} else
	{
		KillTimer(TM_CPU);
		KillTimer(TM_POWER);
		SetDlgItemText(IDC_BUTTON_TOGGLE, "START");
		SetDlgItemText(IDC_CTTEXTCTRL_CPU, _T("CPU : -  , MEMORY : - "));
		SetDlgItemText(IDC_CTTEXTCTRL_HEAD1_POWER, _T("HEAD1 POWER : -"));
		SetDlgItemText(IDC_CTTEXTCTRL_HEAD2_POWER, _T("HEAD2 POWER : -"));
		
		m_bToggleBtn = FALSE;
	}
}

void CDustCollector::SetDelayTime(unsigned int iSecond)
{
	DWORD dwTick = GetTickCount();
	MSG msg;
	while(GetTickCount() - dwTick < iSecond)
	{					
		if(PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		Sleep(0);
	}
}

void CDustCollector::OnBnClickedButton2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_buf[0] = 0x04;
	m_buf[1] = 0x03;
	m_buf[2] = 0x04;
	m_buf[3] = 0x99;
	m_buf[4] = 0x9a;
	m_buf[5] = 0x41;
	m_buf[6] = 0xe9;

	unsigned short crc16 = CRC16((char*)m_buf, 7);
	BYTE byteArray[2];
	intToByteArray16(crc16,byteArray);

	byteArray[0];
	byteArray[1];



}


void CDustCollector::OnBnClickedButton3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strBtn;
	GetDlgItemText(IDC_BUTTON3, strBtn);
	if(strBtn == "Check")
	{
		SetDlgItemText(IDC_BUTTON3, _T("Stop"));
		SetTimer(TM_SCANNER_STATUS, 100, NULL);
	} else
	{
		SetDlgItemText(IDC_BUTTON3, _T("Check"));
		KillTimer(TM_SCANNER_STATUS);
	}
}
