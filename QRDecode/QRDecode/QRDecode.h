// QRDecode.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CQRDecodeApp:
// �йش����ʵ�֣������ QRDecode.cpp
//

class CQRDecodeApp : public CWinApp
{
public:
	CQRDecodeApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CQRDecodeApp theApp;