// FeedbackDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ImageRetrive01.h"
#include "FeedbackDlg.h"
#include "afxdialogex.h"


// CFeedbackDlg 对话框

IMPLEMENT_DYNAMIC(CFeedbackDlg, CDialogEx)

CFeedbackDlg::CFeedbackDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CFeedbackDlg::IDD, pParent)
{
	m_Rbutton = 1;
}

CFeedbackDlg::~CFeedbackDlg()
{
}

void CFeedbackDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO_Positive, m_Rbutton);
}


BEGIN_MESSAGE_MAP(CFeedbackDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CFeedbackDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CFeedbackDlg 消息处理程序


void CFeedbackDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}
