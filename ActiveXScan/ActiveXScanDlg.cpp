
// ActiveXScanDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ActiveXScan.h"
#include "ActiveXScanDlg.h"
#include "afxdialogex.h"

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

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CActiveXScanDlg 对话框




CActiveXScanDlg::CActiveXScanDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CActiveXScanDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CActiveXScanDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_ACTIVEX, m_listActiveX);
}

BEGIN_MESSAGE_MAP(CActiveXScanDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SIZE()
	ON_WM_GETMINMAXINFO()
END_MESSAGE_MAP()


// CActiveXScanDlg 消息处理程序

BOOL CActiveXScanDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// 将“关于...”菜单项添加到系统菜单中。
	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);
	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if(pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if(!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}
	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);         // 设置大图标
	SetIcon(m_hIcon, FALSE);        // 设置小图标
	// TODO: 在此添加额外的初始化代码
	ShowWindow(SW_SHOWMAXIMIZED);
	LayoutWnd();
	InitListCtrl();
	RefreshActiveX();
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CActiveXScanDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
		CDialogEx::OnSysCommand(nID, lParam);
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CActiveXScanDlg::OnPaint()
{
	if(IsIconic())
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
		CDialogEx::OnPaint();
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CActiveXScanDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CActiveXScanDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	// TODO: 在此处添加消息处理程序代码
	LayoutWnd();
}

void CActiveXScanDlg::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CDialogEx::OnGetMinMaxInfo(lpMMI);
	lpMMI->ptMinTrackSize.x = 400;
	lpMMI->ptMinTrackSize.y = 300;
}


void CActiveXScanDlg::LayoutWnd(void)
{
	CRect rect;
	GetClientRect(&rect);
	CWnd* hWnd = GetDlgItem(IDC_LIST_ACTIVEX);
	if(hWnd!=NULL)
		hWnd->MoveWindow(0,0,rect.Width(),rect.Height());
}

void CActiveXScanDlg::RefreshActiveX(void)
{
	m_listActiveX.SetRedraw(FALSE);
	m_listActiveX.DeleteAllItems();
	HKEY hkCLSID;
	LONG lResult = RegOpenKeyEx(HKEY_CLASSES_ROOT, _T("CLSID"), 0, KEY_READ, &hkCLSID);
	if(lResult != ERROR_SUCCESS)
		return;
	DWORD dwListIndex = 0;
	DWORD iIndex = 0;
	BOOL tStopEnumerating = FALSE;
	while(!tStopEnumerating)
	{
		FILETIME time;
		TCHAR szSubkey[MAX_PATH];
		DWORD nSubkeyLength = sizeof(szSubkey)/sizeof(szSubkey[0]);
		lResult = RegEnumKeyEx(hkCLSID, iIndex, szSubkey, &nSubkeyLength, NULL, NULL, NULL, &time);
		if(lResult == ERROR_SUCCESS)
		{
			HKEY hkSubkey;
			lResult = RegOpenKeyEx(hkCLSID, szSubkey, 0, KEY_READ, &hkSubkey);
			if(lResult == ERROR_SUCCESS)
			{
				if(IsActiveX(hkSubkey))
				{
					HKEY hkInprocServer32;
					lResult = RegOpenKeyEx(hkSubkey, _T("InprocServer32"), 0, KEY_READ, &hkInprocServer32);
					if(lResult == ERROR_SUCCESS)
					{
						DWORD dwType;
						TCHAR szInprocServer32[MAX_PATH];
						DWORD nDataLength = sizeof(szInprocServer32);
						lResult = RegQueryValueEx(hkInprocServer32, NULL, NULL, &dwType, LPBYTE(szInprocServer32), &nDataLength);
						RegCloseKey(hkInprocServer32);
						if((lResult == ERROR_SUCCESS) && (dwType == REG_SZ))
						{
							HKEY hkProgID;
							lResult = RegOpenKeyEx(hkSubkey, _T("ProgID"), 0, KEY_READ, &hkProgID);
							if(lResult == ERROR_SUCCESS)
							{
								TCHAR szProgID[80];
								nDataLength = sizeof(szProgID);
								lResult = RegQueryValueEx(hkProgID, NULL, NULL, &dwType, LPBYTE(szProgID), &nDataLength);
								RegCloseKey(hkProgID);
								if((lResult == ERROR_SUCCESS) && (dwType == REG_SZ))
								{
									int iItem = m_listActiveX.InsertItem(dwListIndex, szProgID);
									m_listActiveX.SetItemData(dwListIndex,dwListIndex);
									CString strIndex;
									strIndex.Format(_T("%d"),dwListIndex+1);
									m_listActiveX.SetItemText(iItem, Column_Index_INDEX, strIndex);
									m_listActiveX.SetItemText(iItem, Column_Index_PROGID, szProgID);
									m_listActiveX.SetItemText(iItem, Column_Index_PATH, szInprocServer32);
									dwListIndex++;
								}
							}
						}
					}
				}
			}
		}
		else
			tStopEnumerating = TRUE;
		iIndex++;
	}
	m_listActiveX.SetRedraw(TRUE);
	m_listActiveX.Invalidate();
}

// 判断是否为ActiveX控件
BOOL CActiveXScanDlg::IsActiveX(HKEY hkClass)
{
	ASSERT(hkClass != NULL);
	HKEY hk;
	LONG lResult = RegOpenKeyEx(hkClass, _T("InprocServer32"), 0, KEY_READ, &hk);
	// It doesn't have an inproc server, so it's probably not a control.
	if(lResult != ERROR_SUCCESS)
		return(FALSE);
	RegCloseKey(hk);
	// It doesn't have a ProgID, so it's not a control.
	lResult = RegOpenKeyEx(hkClass, _T("ProgID"), 0, KEY_READ, &hk);
	if(lResult != ERROR_SUCCESS)
		return(FALSE);
	RegCloseKey(hk);
	// It's definitely a control.
	lResult = RegOpenKeyEx(hkClass, _T("Control"), 0, KEY_READ, &hk);
	if(lResult == ERROR_SUCCESS)
	{
		RegCloseKey(hk);
		return(TRUE);
	}
	// It's definitely a control.
	lResult = RegOpenKeyEx(hkClass, _T("ToolboxBitmap32"), 0, KEY_READ, &hk);
	if(lResult == ERROR_SUCCESS)
	{
		RegCloseKey(hk);
		return(TRUE);
	}
	return(FALSE);
}


void CActiveXScanDlg::InitListCtrl(void)
{
	CRect rect;
	GetClientRect(&rect);
	int nWidth = rect.Width();
	CString strTitle;
	LOAD_STRING_FROM_RESOURCE(strTitle, IDS_INDEX);
	m_listActiveX.InsertColumn(Column_Index_INDEX, strTitle, LVCFMT_LEFT, 75);
	LOAD_STRING_FROM_RESOURCE(strTitle, IDS_PROGID);
	m_listActiveX.InsertColumn(Column_Index_PROGID, strTitle, LVCFMT_LEFT, static_cast<int>(nWidth*0.3));
	LOAD_STRING_FROM_RESOURCE(strTitle, IDS_PATH);
	m_listActiveX.InsertColumn(Column_Index_PATH, strTitle, LVCFMT_LEFT, static_cast<int>(nWidth*0.7) - 100);
	m_listActiveX.SetExtendedStyle(LVS_EX_FULLROWSELECT);
}
