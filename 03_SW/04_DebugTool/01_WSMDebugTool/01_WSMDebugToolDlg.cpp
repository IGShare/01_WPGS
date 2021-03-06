
// 01_WSMDebugToolDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "01_WSMDebugTool.h"
#include "01_WSMDebugToolDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CMy01_WSMDebugToolDlg 대화 상자




CMy01_WSMDebugToolDlg::CMy01_WSMDebugToolDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMy01_WSMDebugToolDlg::IDD, pParent)
	, m_richEditTextView(_T(""))
	, m_radioValue(FALSE)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	for(int i=0; i<65536; i++)
		m_rxData[i] = 0;

	for(int i=0; i<400; i++){
		m_nDataX[i] = 0;
		m_nDataY[i] = 0;
		m_nDataZ[i] = 0;

	}
	m_isDataDrawReady = 0;
}

void CMy01_WSMDebugToolDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_PORT, m_ctrlComboPort);
	DDX_Control(pDX, IDC_COMBO_BAUDRATE, m_ctrlComboBaudRate);
	DDX_Control(pDX, IDC_RICHEDIT21, m_ctrlRichEditTextView);
	DDX_Text(pDX, IDC_RICHEDIT21, m_richEditTextView);
	DDX_Radio(pDX, IDC_RADIO1, m_radioValue);
}

BEGIN_MESSAGE_MAP(CMy01_WSMDebugToolDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_RECEIVEDATA, OnReceiveData)
	ON_BN_CLICKED(IDC_BUTTON_DEVICE_MANAGER, &CMy01_WSMDebugToolDlg::OnBnClickedButtonDeviceManager)
	ON_BN_CLICKED(IDC_BUTTON_COMPORT_OPEN, &CMy01_WSMDebugToolDlg::OnBnClickedButtonComportOpen)
	ON_BN_CLICKED(IDC_BUTTON_COMPORT_CLOSE, &CMy01_WSMDebugToolDlg::OnBnClickedButtonComportClose)
	ON_BN_CLICKED(IDC_BUTTON_DATA_ACQUISITION_START, &CMy01_WSMDebugToolDlg::OnBnClickedButtonDataAcquisitionStart)
	ON_BN_CLICKED(IDC_BUTTON_DATA_ACQUISITION_STOP, &CMy01_WSMDebugToolDlg::OnBnClickedButtonDataAcquisitionStop)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CMy01_WSMDebugToolDlg::OnBnClickedButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, &CMy01_WSMDebugToolDlg::OnBnClickedButtonClear)
END_MESSAGE_MAP()


// CMy01_WSMDebugToolDlg 메시지 처리기

BOOL CMy01_WSMDebugToolDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다. 응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.


	m_Comm.SetHwnd(this->m_hWnd); // CComm 클래스에서 유저 메시지를 사용할 수 있도록 window 핸들을 전달한다.

	m_nComPort = 0; // COM 1
	m_nParity = 0; // no parity bit
	m_nBaudRate = 0; // 1200 baud rates
	m_nDataBits = 1; //8bits
	m_nStopBits = 0; //one stop ibt
	m_nFlowControl = 0; // No control

	//Comport 초기화
	CString portName, boardId;
	for(int i=1; i<30; i++){
		portName.Format(_T("COM%d"),i);
		m_ctrlComboPort.AddString(portName);
	}

	m_ctrlComboPort.SetCurSel(2);
	m_ctrlComboBaudRate.SetCurSel(8);

	CheckDlgButton(IDC_CHECK_X, TRUE);
	CheckDlgButton(IDC_CHECK_Y, TRUE);
	CheckDlgButton(IDC_CHECK_Z, TRUE);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CMy01_WSMDebugToolDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다. 문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMy01_WSMDebugToolDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);

	
	}
	else
	{
		//CDialog::OnPaint();
		///////// 좌표축 생성

		if(m_radioValue == 0){// Magnetic Sensor Data Draw
			CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트
			CPen NewPen(PS_SOLID, 5, RGB(100, 100, 100));
			CPen* pOldPen = dc.SelectObject(&NewPen);
			
			dc.MoveTo(270, 175);
			dc.LineTo(800, 175);
			dc.MoveTo(270, 100);
			dc.LineTo(270, 250);
			dc.SelectObject(pOldPen);

			CPen NewPen2(PS_SOLID, 2, RGB(200, 200, 200));
			CPen* pOldPen2 = dc.SelectObject(&NewPen2);

			dc.Ellipse(295, 350, 445, 500);
			dc.Ellipse(465, 350, 615, 500);
			dc.Ellipse(635, 350, 785, 500);
			dc.SelectObject(pOldPen2);

			CFont Font;
			CFont *pOldFont;

			LOGFONT lf;
			::ZeroMemory(&lf, sizeof(lf));
			wsprintf(lf.lfFaceName, TEXT("%s"), TEXT("Arial"));
			lf.lfHeight = 15;
			int nY = 530;
			Font.CreateFontIndirectA(&lf);
			pOldFont = dc.SelectObject(&Font);
			CString text;
			text.Format(_T("X-Y Plane"));
			dc.TextOutA(295+50, nY,text);
			text.Format(_T("Y-Z Plane"));
			dc.TextOutA(465+50, nY,text);
			text.Format(_T("X-Z Plane"));
			dc.TextOutA(635+50, nY,text);
			dc.SelectObject(pOldFont);
			Font.DeleteObject();
			
			if(m_isDataDrawReady){
				int chk_x = IsDlgButtonChecked(IDC_CHECK_X);
				int chk_y = IsDlgButtonChecked(IDC_CHECK_Y);
				int chk_z = IsDlgButtonChecked(IDC_CHECK_Z);
				
				//Signal View
				if(chk_x){
					int max = 0;
					CPen NewPenX(PS_SOLID, 3, RGB(255, 0, 0));
					CPen* pOldPenX = dc.SelectObject(&NewPenX);
					for(int i=399; i>0; i--){
						m_nDataX[i] = m_nDataX[i-1];
					}
					m_nDataX[0] = m_nData[0];
					for(int i=0; i<400; i++)
						dc.Rectangle(270 + i, 175-int(m_nDataX[i]/(float)10000*150),270 + i+1, 1+175-int(m_nDataX[i]/(float)10000*150));
					dc.SelectObject(pOldPenX);
									// Statistics Text 출력
					CFont Font;
					CFont *pOldFont;

					LOGFONT lf;
					::ZeroMemory(&lf, sizeof(lf));
					wsprintf(lf.lfFaceName, TEXT("%s"), TEXT("Arial"));
					lf.lfHeight = 18;
					int nY = 110;
					Font.CreateFontIndirectA(&lf);
					pOldFont = dc.SelectObject(&Font);
					CString text;
					text.Format(_T("X Axis Value  : %d"), m_nDataX[0]);
					dc.TextOutA(650, nY,text);
					dc.SelectObject(pOldFont);
					Font.DeleteObject();

				}
				if(chk_y){
					CPen NewPenY(PS_SOLID, 3, RGB(0, 255, 0));
					CPen* pOldPenY = dc.SelectObject(&NewPenY);
					for(int i=399; i>0; i--){
						m_nDataY[i] = m_nDataY[i-1];
					}
					m_nDataY[0] = m_nData[1];
					for(int i=0; i<400; i++)
						dc.Rectangle(270 + i, 175-int(m_nDataY[i]/(float)10000*150),270 + i+1, 1+175-int(m_nDataY[i]/(float)10000*150));
					dc.SelectObject(pOldPenY);
					
					CFont Font;
					CFont *pOldFont;

					LOGFONT lf;
					::ZeroMemory(&lf, sizeof(lf));
					wsprintf(lf.lfFaceName, TEXT("%s"), TEXT("Arial"));
					lf.lfHeight = 18;
					int nY = 130;
					Font.CreateFontIndirectA(&lf);
					pOldFont = dc.SelectObject(&Font);
					CString text;
					text.Format(_T("Y Axis Value  : %d"), m_nDataY[0]);
					dc.TextOutA(650, nY,text);
					dc.SelectObject(pOldFont);
					Font.DeleteObject();
				}
				if(chk_z){
					CPen NewPenZ(PS_SOLID, 3, RGB(0, 0, 255));
					CPen* pOldPenZ = dc.SelectObject(&NewPenZ);
					for(int i=399; i>0; i--){
						m_nDataZ[i] = m_nDataZ[i-1];
					}
					m_nDataZ[0] = m_nData[2];
					for(int i=0; i<400; i++)
						dc.Rectangle(270 + i, 175-int(m_nDataZ[i]/(float)10000*150),270 + i+1, 1+175-int(m_nDataZ[i]/(float)10000*150));
					dc.SelectObject(pOldPenZ);

					CFont Font;
					CFont *pOldFont;

					LOGFONT lf;
					::ZeroMemory(&lf, sizeof(lf));
					wsprintf(lf.lfFaceName, TEXT("%s"), TEXT("Arial"));
					lf.lfHeight = 18;
					int nY = 150;
					Font.CreateFontIndirectA(&lf);
					pOldFont = dc.SelectObject(&Font);
					CString text;
					text.Format(_T("Z Axis Value  : %d"), m_nDataZ[0]);
					dc.TextOutA(650, nY,text);
					dc.SelectObject(pOldFont);
					Font.DeleteObject();
				}
				// Plane View

					CPen NewPenXY(PS_SOLID, 3, RGB(255, 0, 0));
					CPen* pOldPenXY = dc.SelectObject(&NewPenXY);
					for(int i=0; i<400; i++)
						dc.Rectangle(370-int(m_nDataX[i]/(float)6000*75),425-int(m_nDataY[i]/(float)6000*75), 370-int(m_nDataX[i]/(float)6000*75)+1,425-int(m_nDataY[i]/(float)6000*75)+1);
					dc.SelectObject(pOldPenXY);

					CPen NewPenYZ(PS_SOLID, 3, RGB(0, 255, 0));
					CPen* pOldPenYZ = dc.SelectObject(&NewPenYZ);
					for(int i=0; i<400; i++)
						dc.Rectangle(540-int(m_nDataY[i]/(float)6000*75),425-int(m_nDataZ[i]/(float)6000*75), 540-int(m_nDataY[i]/(float)6000*75)+1,425-int(m_nDataZ[i]/(float)6000*75)+1);
					dc.SelectObject(pOldPenYZ);

					CPen NewPenXZ(PS_SOLID, 3, RGB(0, 0, 255));
					CPen* pOldPenXZ = dc.SelectObject(&NewPenXZ);
					for(int i=0; i<400; i++)
						dc.Rectangle(710-int(m_nDataX[i]/(float)6000*75),425-int(m_nDataZ[i]/(float)6000*75), 710-int(m_nDataX[i]/(float)6000*75)+1,425-int(m_nDataZ[i]/(float)6000*75)+1);
					dc.SelectObject(pOldPenXZ);


			}
		} 
		if(m_radioValue == 1){// Ultrasound SEnsor Data Draw
			CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트
			//좌표축 세팅
			CPen NewPen(PS_SOLID, 5, RGB(100, 100, 100));
			CPen* pOldPen = dc.SelectObject(&NewPen);
			
			dc.MoveTo(270, 250);
			dc.LineTo(800, 250);
			dc.MoveTo(270, 100);
			dc.LineTo(270, 250);
			dc.SelectObject(pOldPen);

			if(m_isDataDrawReady){
				CPen NewPen2(PS_SOLID, 3, RGB(255, 0, 0));
				CPen* pOldPen2 = dc.SelectObject(&NewPen2);
				int max = 0, min = 900000;
				float avg = 0.f;
				//Staticstics Calculation
				for(int i=0; i< m_dataLength/6; i++){
					avg += m_nData[i];
					if(max < m_nData[i])
						max = m_nData[i];
					if(min > m_nData[i])
						min = m_nData[i];
				}
				//좌표에 Data 표시
				for(int i=0; i< m_dataLength/6; i++){
					//dc.SetPixel(270 + i, 250-int(m_nData[i]/(float)4000*150), RGB(255, 0, 0));
					dc.Rectangle(270 + i, 250-int(m_nData[i]/(float)4000*150),270 + i+1, 1+250-int(m_nData[i]/(float)4000*150));
				}
				m_isDataDrawReady = 0;
				dc.SelectObject(pOldPen2);

				// Statistics Text 출력
				CFont Font;
				CFont *pOldFont;

				LOGFONT lf;
				::ZeroMemory(&lf, sizeof(lf));
				wsprintf(lf.lfFaceName, TEXT("%s"), TEXT("Arial"));
				lf.lfHeight = 20;
				int nY = 120;
				Font.CreateFontIndirectA(&lf);
				pOldFont = dc.SelectObject(&Font);
				CString text;
				text.Format(_T("Max : %d"), max);
				dc.TextOutA(650, nY,text);
				text.Format(_T("Min : %d"), min);
				dc.TextOutA(650, nY+22,text);
				text.Format(_T("Avg : %f"), avg/m_dataLength/6);
				dc.TextOutA(650, nY+44,text);
				dc.SelectObject(pOldFont);
				Font.DeleteObject();
			}
			
		}
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMy01_WSMDebugToolDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


LONG CMy01_WSMDebugToolDlg::OnReceiveData(UINT WParam, LONG a)
{
	UpdateData(true);
	int nLen = WParam;
	int num = 1, dataUnit;
	CString str;
	static char sData[32767] = {0,};
	static int dLength = 0;
	int low=0, high=0;
	static int index = 0;
	int isPacketOK = 0;

	dataUnit = (m_radioValue==0)? 12 : 1000;

	if(true == m_receiveF){
		memcpy(sData+dLength, m_Comm.abIn, nLen);
		dLength += nLen;
		if(dLength < dataUnit*4){
			return 0;
		}
		if(dLength > 32767 - dataUnit*4){
			dLength = 0;
			return 0;
		}

		int head = 0, tail = 0;
		int startF = 0;

		while(1)
		{
			if(startF == 0){
				if(sData[head++] == 'I'){
					if(sData[head++] == 'G'){
						if(sData[head++] == 'S'){
							startF = 1;	
							tail = head;
						
						}
					}
				}
			}
			if(startF == 1){
				index++;
				if(sData[head++] == 'i'){
					if(sData[head++] == 'g'){
						if(sData[head++] == 's'){
							startF = 0;
							memcpy(m_rxData, sData+tail, index-1);
							isPacketOK = 1;
							m_dataLength = index-1;
							tail = head;
							index = 0;
							dLength = 0;
							break;
					
						}
					}
				}
			}
			if(head>32766){
				index = 0;
				dLength = 0;
				break;
			}
		}
		if(isPacketOK){
			
			isPacketOK = 0;
			index = 0;
			CString data;
			data.Format(_T("Data Length = %d\r\n"), m_dataLength);
			m_richEditTextView += data;
			data.Format(_T("%s\r\n"), m_rxData);
			m_richEditTextView += data;
			

			int idx = 0;
			int m = 0;
			int dataval = 0;
			int sign = 1;
			int negativeCnt = 0;
			while(1){
				if(m_rxData[idx] == '-')
				{
					sign = -1;
					idx++;
					negativeCnt++;
				}
				dataval += (m_rxData[idx++]-48)*100000;
				dataval += (m_rxData[idx++]-48)*10000;
				dataval += (m_rxData[idx++]-48)*1000;
				dataval += (m_rxData[idx++]-48)*100;
				dataval += (m_rxData[idx++]-48)*10;
				dataval += (m_rxData[idx++]-48)*1;
				dataval *= sign;
				sign = 1;
				m_nData[m++] = dataval;
				dataval = 0;
				if(m == (m_dataLength-negativeCnt)/6)
					break;
			}

			if(m_FileSaveF == 1)
			{
				for(int i=0; i<(m_dataLength-negativeCnt)/6; i++)
				{
					fprintf(fp, "%d\t", m_nData[i]);
				}
				fprintf(fp, "\n");

				fclose(fp);
			}
			m_isDataDrawReady = 1;
			UpdateData(false);
			Invalidate(true);
			UpdateWindow();
			m_dataLength = 0;
			m_ctrlRichEditTextView.SetSel(-1, -1);
			
		}
	}

	return 0;

}
void CMy01_WSMDebugToolDlg::OnBnClickedButtonDeviceManager()
{
	system("hdwwiz.cpl");
}

void CMy01_WSMDebugToolDlg::OnBnClickedButtonComportOpen()
{
	UpdateData(TRUE);

	m_nComPort = m_ctrlComboPort.GetCurSel();
	m_nBaudRate = m_ctrlComboBaudRate.GetCurSel();

	if(m_Comm.OpenCommPort(&Int2TTY()) != TRUE)
	{
		SetDlgItemText(IDC_STATIC_STATUS_MESSAGE, _T("COM Port Open Fail."));
		UpdateData(FALSE);

		return;
	}
	SetDlgItemText(IDC_STATIC_STATUS_MESSAGE, _T("COM Port Open Success."));
	m_isComPortOpen = 1;
	UpdateData(FALSE);
}

void CMy01_WSMDebugToolDlg::OnBnClickedButtonComportClose()
{
	m_Comm.CloseConnection();
	SetDlgItemText(IDC_STATIC_STATUS_MESSAGE, _T("COM Port Closed."));
	m_isComPortOpen = 0;
}

void CMy01_WSMDebugToolDlg::OnBnClickedButtonDataAcquisitionStart()
{
	if(m_isComPortOpen){
		m_receiveF = 1;
		SetDlgItemText(IDC_STATIC_STATUS_MESSAGE, _T("Data Aquisition Start."));
	}else{
		SetDlgItemText(IDC_STATIC_STATUS_MESSAGE, _T("Com port is not opened. Try COM Port Open First."));
	}
}

void CMy01_WSMDebugToolDlg::OnBnClickedButtonDataAcquisitionStop()
{
	if(m_isComPortOpen){
		m_receiveF = 0;
		SetDlgItemText(IDC_STATIC_STATUS_MESSAGE, _T("Data Aquisition Stopt."));
	}else{
		SetDlgItemText(IDC_STATIC_STATUS_MESSAGE, _T("Com port is not opened. Try COM Port Open First."));
	}
}

TTYSTRUCT CMy01_WSMDebugToolDlg::Int2TTY()
{
	//직접 코딩할 부분(3)
	//COM port 를 열기위한 파라미터 값 설정
	TTYSTRUCT tty;
	ZERO_MEMORY(tty);

	tty.byCommPort = (BYTE)m_nComPort + 1;
	tty.byXonXoff = FALSE;
	tty.byByteSize = (BYTE)_nDataValues[m_nDataBits];
	tty.byFlowCtrl = (BYTE)_nFlow[m_nFlowControl];
	tty.byParity = (BYTE)m_nParity;
	tty.byStopBits = (BYTE)_nStopBits[m_nStopBits];
	tty.dwBaudRate = (DWORD)_nBaudRates[m_nBaudRate];

	return tty;
}

void CMy01_WSMDebugToolDlg::OnBnClickedButtonSave()
{
	m_FileSaveF = TRUE;

	if(m_radioValue==1)
		fp = fopen("data/UltrasoundData.txt", "a");
	if(m_radioValue==0)
		fp = fopen("data/GMSData.txt", "a");
}

void CMy01_WSMDebugToolDlg::OnBnClickedButtonClear()
{
	m_richEditTextView.Format(_T(""));
	UpdateData(false);
}
