
// ActiveXScan.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CActiveXScanApp:
// �йش����ʵ�֣������ ActiveXScan.cpp
//

class CActiveXScanApp : public CWinApp
{
	public:
		CActiveXScanApp();

		// ��д
	public:
		virtual BOOL InitInstance();

		// ʵ��

		DECLARE_MESSAGE_MAP()
};

extern CActiveXScanApp theApp;