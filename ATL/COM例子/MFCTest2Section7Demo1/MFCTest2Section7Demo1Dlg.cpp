// MFCTest2Section7Demo1Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCTest2Section7Demo1.h"
#include "MFCTest2Section7Demo1Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
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

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CMFCTest2Section7Demo1Dlg 对话框




CMFCTest2Section7Demo1Dlg::CMFCTest2Section7Demo1Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMFCTest2Section7Demo1Dlg::IDD, pParent)
{
	CoInitialize(NULL);
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pSink = new CSink(this);
}

CMFCTest2Section7Demo1Dlg::~CMFCTest2Section7Demo1Dlg()
{
	m_pSink->Release();
	CoUninitialize();
}

void CMFCTest2Section7Demo1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCTest2Section7Demo1Dlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


// CMFCTest2Section7Demo1Dlg 消息处理程序

BOOL CMFCTest2Section7Demo1Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	HRESULT hr = E_FAIL;
	CComPtr<IHelloSOE> spHelloSOE;

	//创建简单对象
	hr = spHelloSOE.CoCreateInstance(CLSID_HelloSOE);

	if (SUCCEEDED(hr))
	{
		//事件注册
		DWORD dw = 0;
		hr = spHelloSOE.Advise(m_pSink, DIID__IHelloSOEEvents, &dw);

		if (SUCCEEDED(hr))
		{
			//简单对象的加法
			hr = spHelloSOE->Add(9,99);
		}
	}


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCTest2Section7Demo1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFCTest2Section7Demo1Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作矩形中居中
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
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
//
HCURSOR CMFCTest2Section7Demo1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMFCTest2Section7Demo1Dlg::OnAddResult(LONG lResult)
{
	//简单对象的事件触发

	CString str;
	str.Format(_T("加法运算的结果是：%ld"), lResult);

	AfxMessageBox(str);
}