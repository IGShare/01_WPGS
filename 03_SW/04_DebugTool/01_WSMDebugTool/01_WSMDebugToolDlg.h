
// 01_WSMDebugToolDlg.h : 헤더 파일
//

#pragma once
#include "afxwin.h"
#include "Comm.h"
#include "afxcmn.h"


// CMy01_WSMDebugToolDlg 대화 상자
class CMy01_WSMDebugToolDlg : public CDialog
{
// 생성입니다.
public:
	CMy01_WSMDebugToolDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.
	
// 대화 상자 데이터입니다.
	enum { IDD = IDD_MY01_WSMDEBUGTOOL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	TTYSTRUCT Int2TTY();
	afx_msg LONG OnReceiveData(UINT, LONG);
	CComm m_Comm;

	int	m_nBaudRate;
	int	m_nComPort;
	int m_nFlowControl;
	int m_nStopBits;
	int m_nDataBits;
	int m_nParity;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_ctrlComboPort;
	CComboBox m_ctrlComboBaudRate;
	afx_msg void OnBnClickedButtonDeviceManager();
	afx_msg void OnBnClickedButtonComportOpen();
	afx_msg void OnBnClickedButtonComportClose();
	afx_msg void OnBnClickedButtonDataAcquisitionStart();
	afx_msg void OnBnClickedButtonDataAcquisitionStop();

	int m_isComPortOpen;
	int m_receiveF;
	char m_rxData[65535];
	int m_nData[1000]; // for ultrasound sensor data
	int m_nDataX[400]; // for magnetic sensor data
	int m_nDataY[400]; // for magnetic sensor data
	int m_nDataZ[400]; // for magnetic sensor data
	int m_dataLength;
	CRichEditCtrl m_ctrlRichEditTextView;
	CString m_richEditTextView;
	BOOL m_radioValue;
	int m_isDataDrawReady;
	afx_msg void OnBnClickedButtonSave();

	FILE *fp;
	int m_FileSaveF;
	afx_msg void OnBnClickedButtonClear();
};
