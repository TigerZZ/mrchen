// QRDecodeDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "QRDecode.h"
#include "QRDecodeDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CQRDecodeDlg �Ի���




CQRDecodeDlg::CQRDecodeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CQRDecodeDlg::IDD, pParent)
  /*  , m_szMovieName(_T(""))
    , m_szPhoneNum(_T(""))
    , m_szIDNum(_T(""))
    , m_szRow(_T(""))
    , m_szColumn(_T(""))
    , m_szMovieNum(_T(""))
    , m_szVersion(_T(""))
    , m_szLevel(_T(""))
    , m_szDate(_T(""))
    , m_szTime(_T(""))*/

    ,QR_image(NULL)
    , QR_Decode(NULL)
    , flag_draw(false)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CQRDecodeDlg::~CQRDecodeDlg()
{
    if (QR_image != NULL)
    {
        delete QR_image;
    }

    if (QR_Decode != NULL)
    {
        delete QR_Decode;
    }
}

void CQRDecodeDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
	DDX_Text(pDX,IDC_EDIT_Context,m_Context);
	DDX_Text(pDX, IDC_EDIT7, m_szVersion);
	DDX_Text(pDX, IDC_EDIT8, m_szLevel);
}

BEGIN_MESSAGE_MAP(CQRDecodeDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
    ON_BN_CLICKED(IDOK, &CQRDecodeDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CQRDecodeDlg ��Ϣ�������

BOOL CQRDecodeDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CQRDecodeDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CQRDecodeDlg::OnPaint()
{
    CPaintDC dc(this); // ���ڻ��Ƶ��豸������

	if (IsIconic())
	{	
		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ��������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
        if (flag_draw)
        {
            CRect rt;
            GetDlgItem(IDC_STATIC_IMAGE)->GetClientRect(&rt);
            GetDlgItem(IDC_STATIC_IMAGE)->MapWindowPoints(this, &rt);     

            dc.StretchBlt(rt.left, rt.top, rt.Width(), rt.Height(), QR_image->m_pDC, 0, 0, QR_image->nWidth, QR_image->nHeight, SRCCOPY);
        }
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù����ʾ��
//
HCURSOR CQRDecodeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CQRDecodeDlg::OnBnClickedOk()
{
    CString FilePathName;
    CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,_T( "֧�ֵĸ�ʽ (*.bmp)|*.bmp||"));
    if(dlg.DoModal()==IDOK)
    {
        //��ȡѡ����ļ���·����ʾ
        FilePathName=dlg.GetPathName();

        if (QR_image != NULL)
        {
            delete QR_image;
        }
        QR_image = new QRcodeImage(FilePathName);
        QR_image->GetImageData();

        m_nVersion = QR_image->finderPattern->m_version;
        m_nCodeSize = m_nVersion * 4 +17;
        for(int i=0;i<m_nCodeSize;i++)
            for(int j=0;j<m_nCodeSize;j++)
                m_CodeData[i][j]=QR_image->bitMatrix[i][j];

        //����ͼ����ʾ�ڶԻ�����
        CRect rt;
        GetDlgItem(IDC_STATIC_IMAGE)->GetClientRect(&rt);
        GetDlgItem(IDC_STATIC_IMAGE)->MapWindowPoints(this, &rt);            

        nShowSize=120;
        CDC * pDC=this->GetDC();
        pDC->StretchBlt(rt.left, rt.top, rt.Width(), rt.Height(), QR_image->m_pDC, 0, 0, QR_image->nWidth, QR_image->nHeight, SRCCOPY);
        flag_draw=true;


        //����
        if (QR_Decode != NULL)
        {
            delete QR_Decode;
        }
        QR_Decode = new ContentDecoder;
        QR_Decode->DecodeData(m_nCodeSize,m_nVersion,m_CodeData);

        StringSplit(QR_Decode->m_strData);
	//AfxMessageBox(QR_Decode->m_strData);

        //m_szVersion.Format("%d", QR_Decode->m_nVersion);
        m_Context  = QR_Decode->m_strData ;
	GetDlgItem(IDC_EDIT_Context)->SetWindowText(m_Context);
	
	
        const char *vLevel[] = {"L(%7)", "M(%15)", "Q(%25)", "H(%30)"};
        m_szLevel   = vLevel[QR_Decode->m_nLevel];
		GetDlgItem(IDC_EDIT8)->SetWindowText(m_szLevel);
		m_szVersion.Format(_T("%d"),QR_Decode->m_nVersion);
		GetDlgItem(IDC_EDIT7)->SetWindowText(m_szVersion);
        UpdateData(FALSE);
    }
}

void CQRDecodeDlg::StringSplit(CString &szData)
{
   // if (szData.IsEmpty())
   // {
   //     return;
   // }

   ///* CString *vMems[] = {&m_szMovieName, &m_szPhoneNum, &m_szIDNum, &m_szDate, &m_szTime, &m_szRow, &m_szColumn, &m_szMovieNum};*/

   // int iPos = 0;
   // for (int i=0; i<_countof(vMems); i++)
   // {
			////*vMems[i] = szData.Tokenize("/", iPos);
   // }

    UpdateData(FALSE);
}