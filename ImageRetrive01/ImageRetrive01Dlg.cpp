
// ImageRetrive01Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ImageRetrive01.h"
#include "ImageRetrive01Dlg.h"
#include "afxdialogex.h"
#include "FeedbackDlg.h"

#include <string>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{

}

//display parameter
extern void print(std::string str){
	CString str1(str.c_str());
	MessageBox(NULL,str1,_T("print"),MB_OK);
}
extern void printError(const char* str){
	CString str1(str);
	MessageBox(NULL,str1,_T("Error"),MB_ICONERROR|MB_OK);
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CImageRetrive01Dlg 对话框




CImageRetrive01Dlg::CImageRetrive01Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CImageRetrive01Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	this->pAlgo =new MyBayesAlgorithms01();
	m_pageCountMessage = _T("");
}

//添加显示mat函数声明
int CImageRetrive01Dlg::ShowMat(cv::Mat img,HWND hWndDisplay){
	if (img.channels() < 3)
	{
		return -1;
	}

	//构造要显示的Mat版本图片
	RECT rect;
	::GetClientRect(hWndDisplay,&rect);
	cv::Mat imgShow(abs(rect.top - rect.bottom),abs(rect.right-rect.left),CV_8UC3);
	resize(img,imgShow,imgShow.size());

	//在控件上显示要用的CImage类图片
	ATL::CImage ci;
	int width = imgShow.cols;//宽
	int high = imgShow.cols;//高
	int channels = imgShow.channels();//通道数
	ci.Create(width,high,8*channels);//ci像素的复制
	uchar* pS;
	uchar* pImg = (uchar*)ci.GetBits();//得到CImage数据区地址
	int step = ci.GetPitch();
	for(int i = 0;i<high;++i){
		pS = imgShow.ptr<uchar>(i);
		for (int j =0;j<width;++j)
		{
			for (int k = 0;k<3;++k)
			{
				*(pImg+i*step+j*3+k) = pS[j*3+k];
			}
		}
	}

	//在控件上显示图片
	HDC dc;
	dc = ::GetDC(hWndDisplay);
	ci.Draw(dc,0,0);
	::ReleaseDC(hWndDisplay,dc);
	ci.Destroy();
	
	return 0;
}

void CImageRetrive01Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_PageCount, m_pageCountMessage);
	DDV_MaxChars(pDX, m_pageCountMessage, 20);
}

BEGIN_MESSAGE_MAP(CImageRetrive01Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_Choose_Image, &CImageRetrive01Dlg::OnBnClickedButtonChooseImage)
	ON_BN_CLICKED(IDC_BUTTON_ProcessRetrive, &CImageRetrive01Dlg::OnBnClickedButtonProcessretrive)
	ON_BN_CLICKED(IDC_BUTTON_FirstPage, &CImageRetrive01Dlg::OnBnClickedButtonFirstpage)
	ON_BN_CLICKED(IDC_BUTTON_PageUp, &CImageRetrive01Dlg::OnBnClickedButtonPageup)
	ON_BN_CLICKED(IDC_BUTTON_PageDown, &CImageRetrive01Dlg::OnBnClickedButtonPagedown)
	ON_BN_CLICKED(IDC_BUTTON_EndPage, &CImageRetrive01Dlg::OnBnClickedButtonEndpage)
	ON_BN_CLICKED(IDC_BUTTON_Test, &CImageRetrive01Dlg::OnBnClickedButtonTest)
	ON_BN_CLICKED(IDC_BUTTON_Feedback_1, &CImageRetrive01Dlg::OnBnClickedButtonFeedback1)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON_InitSystem, &CImageRetrive01Dlg::OnBnClickedButtonInitsystem)
	ON_BN_CLICKED(IDC_BUTTON_Feedback_2, &CImageRetrive01Dlg::OnBnClickedButtonFeedback2)
	ON_BN_CLICKED(IDC_BUTTON_Feedback_3, &CImageRetrive01Dlg::OnBnClickedButtonFeedback3)
	ON_BN_CLICKED(IDC_BUTTON_Feedback_4, &CImageRetrive01Dlg::OnClickedButtonFeedback4)
	ON_BN_CLICKED(IDC_BUTTON_Feedback_5, &CImageRetrive01Dlg::OnClickedButtonFeedback5)
	ON_BN_CLICKED(IDC_BUTTON_Feedback_6, &CImageRetrive01Dlg::OnClickedButtonFeedback6)
	ON_BN_CLICKED(IDC_BUTTON_Feedback_7, &CImageRetrive01Dlg::OnClickedButtonFeedback7)
	ON_BN_CLICKED(IDC_BUTTON_Feedback_8, &CImageRetrive01Dlg::OnClickedButtonFeedback8)
	ON_BN_CLICKED(IDC_BUTTON_Train, &CImageRetrive01Dlg::OnBnClickedButtonTrain)
END_MESSAGE_MAP()


// CImageRetrive01Dlg 消息处理程序

BOOL CImageRetrive01Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
//	OnLoadImage();
	GetDlgItem(IDC_BUTTON_InitSystem)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_Train)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_ProcessRetrive)->EnableWindow(FALSE);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CImageRetrive01Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CImageRetrive01Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CImageRetrive01Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//绘制图片到指定区域内
void CImageRetrive01Dlg::DrawPictureToHDC(IplImage* img,UINT ID){
	CDC* pDc = GetDlgItem(ID)->GetDC();
	HDC hDC = pDc->GetSafeHdc();
	CRect rect;
	GetDlgItem(ID)->GetClientRect(&rect);
	CvvImage cimg;
	cimg.CopyOf(img);//复制图片
	cimg.DrawToHDC(hDC,&rect);//将图片绘制到显示控件的指定区域内
	
	ReleaseDC(pDc);
	//cvReleaseImage(&img);
}

void CImageRetrive01Dlg::OnBnClickedButtonChooseImage()
{
	// TODO: 在此添加控件通知处理程序代码
	CString filePath;
	CFileDialog fileDialog(TRUE);
	if(IDOK == fileDialog.DoModal()){
		//获取fileDialog对话框返回的路径名
		filePath = fileDialog.GetPathName();

		//将CString 转换为string
		std::string pathName((CStringA(filePath)));

		//读取图片
		//cv::Mat orgImg = cv::imread(pathName);
		//ShowMat(orgImg,GetDlgItem(IDC_STATIC_Choose_Image)->GetSafeHwnd());
		
		cv::Mat orgImg = cv::imread(pathName);
		//显示图片
		IplImage* img = &IplImage(orgImg);
		DrawPictureToHDC(img,IDC_STATIC_Choose_Image);
	}
}


//执行检索
void CImageRetrive01Dlg::OnBnClickedButtonProcessretrive()
{
	// TODO: 在此添加控件通知处理程序代码
	//OnLoadImage();
	GetDlgItem(IDC_BUTTON_ProcessRetrive)->EnableWindow(FALSE);
	//pAlgo->train();
	std::vector<std::string> positiveResponseFilePath;
	for (int i = 0;i<this->m_retrievalFilePath.size();i++)
	{
		float response = pAlgo->predict(m_retrievalFilePath[i]);
		if(1 == response){//将正反馈的图片保存起来
			positiveResponseFilePath.push_back(m_retrievalFilePath[i]);
		}
	}

	m_retrievalFilePath.clear();
	m_retrievalFilePath.assign(positiveResponseFilePath.begin(),positiveResponseFilePath.end());
	//加载图片
	OnBnClickedButtonFirstpage();
	GetDlgItem(IDC_BUTTON_Train)->EnableWindow(TRUE);
	MessageBox(_T("检索完毕"),_T("提醒"),MB_OK|MB_ICONINFORMATION);
	//检索完毕
}



//---------------qjg---11/25日最新版出现问题，导致又回到之前备份的地方
//load image from folder that store images,but in this fuction ,it is certain;
void CImageRetrive01Dlg::OnLoadImage()
{
	char temp[100];
	memset(temp,0,sizeof(temp));
	for (int i = 0;i< 55;++i)
	{
		sprintf(temp,"F:\\opencvTask\\imgs\\imgs\\%d.jpg",i+1);
		std::string str(temp);
		m_retrievalFilePath.push_back(str);
	}
	OnBnClickedButtonFirstpage();
	this->updatePageMessage();
}

void CImageRetrive01Dlg::OnBnClickedButtonFirstpage()
{
	// TODO: 在此添加控件通知处理程序代码
	if(m_retrievalFilePath.size() > 0 ){
		for (int i= 0;i<1*PerPageCount;++i )
		{
			//显示每一张图片
			showPerImage(i);
		}
		updatePageMessage();
	}
	
}


void CImageRetrive01Dlg::OnBnClickedButtonPageup()
{
	// TODO: 在此添加控件通知处理程序代码
	// TODO: 在此添加控件通知处理程序代码
	if(m_retrievalCurrentIndex>PerPageCount){
		if( (m_retrievalCurrentIndex+1)%PerPageCount == 0){
			int temp = m_retrievalCurrentIndex-PerPageCount+1;
			for(int i= m_retrievalCurrentIndex-2*PerPageCount+1;i<temp;++i){
				showPerImage(i);
			}
		}else{
			int temp =m_retrievalCurrentIndex - m_retrievalCurrentIndex%PerPageCount;
			for (int i = temp-PerPageCount;i<temp;++i)
			{
				showPerImage(i);
			}
		}
	}else{
		print("亲，已经是首页了！！！");
	}
	updatePageMessage();
}


void CImageRetrive01Dlg::OnBnClickedButtonPagedown()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_retrievalCurrentIndex +1 == m_retrievalFilePath.size()  )
	{
		print("已经是最后一页了！");
	}else{
		//最后一页
		if (m_retrievalCurrentIndex+PerPageCount >= m_retrievalFilePath.size() && (m_retrievalCurrentIndex+PerPageCount <= m_retrievalFilePath.size()+PerPageCount))
		{
			int i = 0;
			for ( i = m_retrievalCurrentIndex+1;i< m_retrievalFilePath.size();++i)
			{
				showPerImage(i);
			}
			int j = i%8;
			for ( ;j<8;j++)
			{
				IplImage * img = cvLoadImage("f:\\2.jpg",1);
				DrawPictureToHDC(img,IDC_STATIC_ImgFeedback1+j);
			}
		}else if( m_retrievalCurrentIndex+PerPageCount < m_retrievalFilePath.size() )//向下翻页
		{
			int temp = m_retrievalCurrentIndex+PerPageCount+1;
			for (int i = m_retrievalCurrentIndex+1;i< temp;++i)
			{
				showPerImage(i);
			}
		}else{
			print("已经是最后一页了！");
		}	
	}
	updatePageMessage();
}


void CImageRetrive01Dlg::OnBnClickedButtonEndpage()
{
	// TODO: 在此添加控件通知处理程序代码
	if(m_retrievalCurrentIndex+1 >= m_retrievalFilePath.size()){
		print("当前已经是最后一页了！！！");
	}else{
		int endPageIndex =PerPageCount*( m_retrievalFilePath.size()/PerPageCount);
		int i = 0;
		for ( i = endPageIndex;i<m_retrievalFilePath.size();++i)
		{
			showPerImage(i);
		}
		int j = i%8;
		for ( ;j<8;j++)
		{
			IplImage * img = cvLoadImage("f:\\2.jpg",1);
		//	IplImage * img = cvLoadImage((Config::BLACK_IMAGE_FILEPATH).c_str(),1);
			DrawPictureToHDC(img,IDC_STATIC_ImgFeedback1+j);
		}
	}
	updatePageMessage();
}


//show Per Image in order to retrieval.
void CImageRetrive01Dlg::showPerImage(int i)
{
	std::string filePath = m_retrievalFilePath[i];
	IplImage * img = cvLoadImage(filePath.c_str(),CV_LOAD_IMAGE_COLOR);
	m_retrievalCurrentIndex = i;

	DrawPictureToHDC(img,IDC_STATIC_ImgFeedback1+(i%PerPageCount));
	cvReleaseImage(&img);
}


void CImageRetrive01Dlg::OnBnClickedButtonTest()
{
	// TODO: 在此添加控件通知处理程序代码
	OnLoadImage();
	//getFeecBackResult();
}


void CImageRetrive01Dlg::SetPageCount(std::string str)
{
	CString str1(str.c_str());
	GetDlgItem(IDC_EDIT_PageCount)->SetWindowText(str1);
}


// 获取反馈结果
int CImageRetrive01Dlg::getFeecBackResult(void)
{
	CFeedbackDlg dlg;
	if (dlg.DoModal() == IDOK)
	{
		//print("heha");
		TRACE(" ---%d\n",dlg.m_Rbutton);
		switch(dlg.m_Rbutton){
		case 0:
			return 1;
		case 2:
			return -1;
		default:
			return 0;
		}
	}
	return 0;
	
}


void CImageRetrive01Dlg::OnBnClickedButtonFeedback1()
{
	// TODO: 在此添加控件通知处理程序代码
	feedback(1);
	//getFeecBackResult();
}


void CImageRetrive01Dlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
	delete(pAlgo);
}


void CImageRetrive01Dlg::OnBnClickedButtonInitsystem()
{
	// TODO: 在此添加控件通知处理程序代码
	OnLoadImage();

}

void CImageRetrive01Dlg::feedback(int i)
{
	if (m_retrievalFilePath.size() == 0)
	{
		MessageBox(_T("请初始化系统！"),_T("警告"),MB_OK|MB_ICONWARNING);
		return ;
	}

	int temp = getFeecBackResult();

	int index = getFeedBackFileIndex(i);

	//TRACE("m_retrievalCurrentIndex --- %d \n",index);
	TRACE("path = %s\n",m_retrievalFilePath[index].c_str());
	if (1 == temp)
	{
		//正的加入
		pAlgo->m_positiveFilePath.push_back(this->m_retrievalFilePath[index]);
	}else if( -1 == temp){
		//负的加入
		pAlgo->m_negativeFilePath.push_back(this->m_retrievalFilePath[index]);
	}
	GetDlgItem(IDC_BUTTON_Train)->EnableWindow(TRUE);
	
	//str=this->m_retrievalFilePath[index];
	//char tempCh[100];
	//memset(tempCh,0,sizeof(tempCh));
	//sprintf(tempCh,"index = %d,feedback = %d, path= %s",index,temp,m_retrievalFilePath[index]);
	//std::string str(tempCh);
	//print(str);

}


void CImageRetrive01Dlg::OnBnClickedButtonFeedback2()
{
	// TODO: 在此添加控件通知处理程序代码
	feedback(2);
}


void CImageRetrive01Dlg::OnBnClickedButtonFeedback3()
{
	// TODO: 在此添加控件通知处理程序代码
		feedback(3);
}


void CImageRetrive01Dlg::OnClickedButtonFeedback4()
{
	// TODO: 在此添加控件通知处理程序代码
		feedback(4);
}


void CImageRetrive01Dlg::OnClickedButtonFeedback5()
{
	// TODO: 在此添加控件通知处理程序代码
		feedback(5);
}


void CImageRetrive01Dlg::OnClickedButtonFeedback6()
{
	// TODO: 在此添加控件通知处理程序代码
		feedback(6);
}


void CImageRetrive01Dlg::OnClickedButtonFeedback7()
{
	// TODO: 在此添加控件通知处理程序代码
		feedback(7);
}


void CImageRetrive01Dlg::OnClickedButtonFeedback8()
{
	// TODO: 在此添加控件通知处理程序代码
		feedback(8);
}


void CImageRetrive01Dlg::OnBnClickedButtonTrain()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(IDC_BUTTON_InitSystem)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_Train)->EnableWindow(FALSE);
	MessageBox(_T("由于机器性能不同，训练时间可能较长，请耐心等待！！！"),_T("提醒"),MB_OK | MB_ICONINFORMATION);
	pAlgo->train();
	MessageBox(_T("训练完毕"),_T("提醒"),MB_OK | MB_ICONINFORMATION);
	GetDlgItem(IDC_BUTTON_ProcessRetrive)->EnableWindow(TRUE);
}


// 更新页码信息
void CImageRetrive01Dlg::updatePageMessage(void)
{
	char temp[100];
	int currentPage = 0;
	int allPageCount = 0;
	if (m_retrievalFilePath.size() == 0)
	{
		currentPage = 0;
		allPageCount = 0;
	}else{
		currentPage = m_retrievalCurrentIndex/8 +1;
		if ( (m_retrievalFilePath.size()%8) == 0)
		{
			allPageCount = m_retrievalFilePath.size()/8;
		}else{
			allPageCount = (m_retrievalFilePath.size()/8)+1;
		}
	}
	memset(temp,0,sizeof(temp));
	sprintf(temp,"%d/%d",currentPage,allPageCount);
	CString str(temp);
	m_pageCountMessage = str;
	UpdateData(FALSE);
}
