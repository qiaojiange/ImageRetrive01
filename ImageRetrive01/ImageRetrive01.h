
// ImageRetrive01.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CImageRetrive01App:
// �йش����ʵ�֣������ ImageRetrive01.cpp
//

class CImageRetrive01App : public CWinApp
{
public:
	CImageRetrive01App();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CImageRetrive01App theApp;