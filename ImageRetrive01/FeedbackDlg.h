#pragma once


// CFeedbackDlg �Ի���

class CFeedbackDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CFeedbackDlg)

public:
	CFeedbackDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CFeedbackDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_Feedback };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	BOOL m_Rbutton;
	afx_msg void OnBnClickedOk();
};
