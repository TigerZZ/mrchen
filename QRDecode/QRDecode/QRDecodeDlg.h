// QRDecodeDlg.h : ͷ�ļ�
//

#pragma once
#include "QRcodeImage.h"
#include "ContentDecoder.h"
#include "resource.h"

// CQRDecodeDlg �Ի���
class CQRDecodeDlg : public CDialog
{
// ����
public:
	CQRDecodeDlg(CWnd* pParent = NULL);	// ��׼���캯��
    ~CQRDecodeDlg();

// �Ի�������
	enum { IDD = IDD_QRDECODE_DIALOG };

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

    afx_msg void OnBnClickedOk();

public:

private:
    void StringSplit(CString &szData);

    QRcodeImage * QR_image;
    ContentDecoder * QR_Decode;

    int m_nCodeSize;            //���������С
    int m_nMoudleSize;          //ģ���С
    int m_nVersion;             //�汾��
    int m_nLevel;               //����ȼ�
    bool flag_draw;             //��ͼ��־
    int nShowSize;
    BYTE m_CodeData[MAX_MODULESIZE][MAX_MODULESIZE]; // �洢������λ����
	CString m_Context;
	CString m_szVersion;
	CString m_szLevel;

};
