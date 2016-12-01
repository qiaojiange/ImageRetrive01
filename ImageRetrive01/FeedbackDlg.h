#pragma once


// CFeedbackDlg 对话框

class CFeedbackDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CFeedbackDlg)

public:
	CFeedbackDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CFeedbackDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_Feedback };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	BOOL m_Rbutton;
	afx_msg void OnBnClickedOk();
};
