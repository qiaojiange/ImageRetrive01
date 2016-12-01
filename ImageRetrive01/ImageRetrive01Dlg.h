
// ImageRetrive01Dlg.h : ͷ�ļ�
//

#pragma once
#include "CvvImage.h"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "BayesAlgorithms.h"
#include "MyBayesAlgorithms01.h"
#include "afxwin.h"
#include <string>
#include <vector>

#define PerPageCount 8

// CImageRetrive01Dlg �Ի���
class CImageRetrive01Dlg : public CDialogEx
{
// ����
public:
	CImageRetrive01Dlg(CWnd* pParent = NULL);	// ��׼���캯��
	int ShowMat(cv::Mat img,HWND hWndDisplay);
	void DrawPictureToHDC(IplImage* img,UINT ID);
// �Ի�������
	enum { IDD = IDD_IMAGERETRIVE01_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	// ��ǰ�����±�
	int m_retrievalCurrentIndex;
	// �����ļ�·��
	std::vector<std::string> m_retrievalFilePath;
	
	std::string m_userChooseImagePath;
	void OnLoadImage();
	void showPerImage(int i);
	void SetPageCount(std::string str);
	afx_msg void OnBnClickedButtonChooseImage();
	afx_msg void OnBnClickedButtonProcessretrive();
	afx_msg void OnBnClickedButtonFirstpage();
	afx_msg void OnBnClickedButtonPageup();
	afx_msg void OnBnClickedButtonPagedown();
	afx_msg void OnBnClickedButtonEndpage();
	afx_msg void OnBnClickedButtonTest();
	// ��ȡ�������
	int getFeecBackResult(void);
	afx_msg void OnBnClickedButtonFeedback1();

	void feedback(int i);

	int getFeedBackFileIndex(int i)
	{
		if (i<1 ||i>8)
		{
		//	throw Exception("getFeedBackFileIndex ----��i��������Χ���±����");
		//	printError("getFeedBackFileIndex ----��i��������Χ���±����");
			MessageBox(_T("getFeedBackFileIndex ----��i��������Χ���±����"),_T("����"),MB_ICONWARNING | MB_OK);
			return -1;
		}
		return m_retrievalCurrentIndex-8+i;
	}

private:
	BayesAlgorithms* pAlgo;
public:
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedButtonInitsystem();
	afx_msg void OnBnClickedButtonFeedback2();
	afx_msg void OnBnClickedButtonFeedback3();
	afx_msg void OnClickedButtonFeedback4();
	afx_msg void OnClickedButtonFeedback5();
	afx_msg void OnClickedButtonFeedback6();
	afx_msg void OnClickedButtonFeedback7();
	afx_msg void OnClickedButtonFeedback8();
	afx_msg void OnBnClickedButtonTrain();
	// ����ҳ����Ϣ
	void updatePageMessage(void);
	CString m_pageCountMessage;
};
