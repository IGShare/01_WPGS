
// UARTDebugDlg.h : ��� ����
//

#pragma once
#include "Comm.h"
#include "afxwin.h"
#include "afxcmn.h"


// CUARTDebugDlg ��ȭ ����
class CUARTDebugDlg : public CDialog
{
// �����Դϴ�.
public:
	CUARTDebugDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_UARTDEBUG_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.

	afx_msg LONG OnReceiveData(UINT, LONG);
// �����Դϴ�.
protected:
	HICON m_hIcon;

	CComm m_Comm;

	int	m_nBaudRate;
	int	m_nComPort;
	int m_nFlowControl;
	int m_nStopBits;
	int m_nDataBits;
	int m_nParity;


	// ������ �޽��� �� �Լ�
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
