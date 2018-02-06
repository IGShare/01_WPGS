
// UARTDebugDlg.h : 헤더 파일
//

#pragma once
#include "Comm.h"
#include "afxwin.h"
#include "afxcmn.h"


// CUARTDebugDlg 대화 상자
class CUARTDebugDlg : public CDialog
{
// 생성입니다.
public:
	CUARTDebugDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
	enum { IDD = IDD_UARTDEBUG_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.

	afx_msg LONG OnReceiveData(UINT, LONG);
// 구현입니다.
protected:
	HICON m_hIcon;

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
	TTYSTRUCT Int2TTY();
	afx_msg void OnBnClickedButtonOpenDevmgr();
	afx_msg void OnBnClickedButtonComOpen();
	CComboBox m_ctrlComboPort;
	CComboBox m_ctrlComboBaudRate;
	CString m_editReport;
	afx_msg void OnBnClickedButtonSenddata();
	CString m_editSendData;

	CString m_myReportMessage;
	afx_msg void OnBnClickedButtonComClose();
	CRichEditCtrl m_ctrlRichEdit;
	afx_msg void OnBnClickedButtonStart();
	afx_msg void OnBnClickedButtonStop();

	int m_receiveF;
	int tLength;
};
