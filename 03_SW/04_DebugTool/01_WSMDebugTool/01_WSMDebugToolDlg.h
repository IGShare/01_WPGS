
// 01_WSMDebugToolDlg.h : ��� ����
//

#pragma once
#include "afxwin.h"
#include "Comm.h"
#include "afxcmn.h"


// CMy01_WSMDebugToolDlg ��ȭ ����
class CMy01_WSMDebugToolDlg : public CDialog
{
// �����Դϴ�.
public:
	CMy01_WSMDebugToolDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.
	
// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_MY01_WSMDEBUGTOOL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
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

	// ������ �޽��� �� �Լ�
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
