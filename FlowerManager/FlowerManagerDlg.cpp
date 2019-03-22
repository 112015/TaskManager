/*
FlowerManagerDlg.cpp: 主框架
作者：1120151769 侯思凡
     1120151775 罗薇
*/
//——————————————————————————————————————————————————————————————————————————————————————<侯思凡>
#include "stdafx.h"
#include "FlowerManager.h"
#include "FlowerManagerDlg.h"
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
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

														// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// FlowerManagerDlg 对话框



FlowerManagerDlg::FlowerManagerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_FLOWERMANAGER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void FlowerManagerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, m_tab);
}

BEGIN_MESSAGE_MAP(FlowerManagerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &FlowerManagerDlg::OnTcnSelchangeTab1)
	ON_COMMAND(ID_EXIT, &FlowerManagerDlg::OnExit)
	ON_UPDATE_COMMAND_UI(ID_TOP, &FlowerManagerDlg::OnUpdateTop)
	ON_MESSAGE(WM_SHOWTASK, OnShowTask)				//其中WM_SHOWTASK是消息名OnShowTask是自己定义的消息响应函数
	ON_COMMAND(ID_ABOUT, &FlowerManagerDlg::OnAbout)
END_MESSAGE_MAP()


// FlowerManagerDlg 消息处理程序

BOOL FlowerManagerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将菜单项添加到窗体中
	TopMenu.LoadMenu(IDR_MENU1);
	SetMenu(&TopMenu);

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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
//——————————————————————————————————————————————————————————————————————————————————————</侯思凡>

//——————————————————————————————————————————————————————————————————————————————————————<罗薇>
// TODO: 在此添加额外的初始化代码
//Tab控件
// 标签控件客户区的位置和大小  
	CRect tabRect;

	//插入标签名
	m_tab.InsertItem(0, _T("进程"));
	m_tab.InsertItem(1, _T("性能"));
	m_tab.InsertItem(2, _T("网络"));
	m_tab.InsertItem(3, _T("文件浏览"));
	m_tab.InsertItem(4, _T("文件清理"));
	m_tab.InsertItem(5, _T("详细信息"));
	m_tab.InsertItem(6, _T("内存"));

	//插入对应页Dialog
	Process.Create(IDD_PAGE1, &m_tab);
	Performance.Create(IDD_PAGE2, &m_tab);
	Net.Create(IDD_PAGE3, &m_tab);
	FileLook.Create(IDD_PAGE4, &m_tab);
	FileClean.Create(IDD_PAGE5, &m_tab);
	Detail.Create(IDD_PAGE6, &m_tab);
	Memeory.Create(IDD_PAGE7, &m_tab);

	// 获取标签控件客户区Rect   
	m_tab.GetClientRect(&tabRect);

	// 调整tabRect，使其覆盖范围适合放置标签页     
	tabRect.left += 0;
	tabRect.right += 5;
	tabRect.top += 25;
	tabRect.bottom -= 0;

	// 根据调整好的tabRect放置子对话框，并设置为第一个显示
	Process.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW);
	Performance.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
	Net.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
	FileLook.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
	FileClean.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
	Detail.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
	Memeory.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}
//——————————————————————————————————————————————————————————————————————————————————————</罗薇>

//——————————————————————————————————————————————————————————————————————————————————————<侯思凡>
void FlowerManagerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
	if (nID == SC_MINIMIZE)
	{
		ToTray(); //最小化到托盘的函数 
	}

}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void FlowerManagerDlg::OnPaint()
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
HCURSOR FlowerManagerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
//——————————————————————————————————————————————————————————————————————————————————————</侯思凡>

//——————————————————————————————————————————————————————————————————————————————————————<罗薇>
//切换标签页
void FlowerManagerDlg::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	DWORD nSel = m_tab.GetCurSel();
	switch (nSel)
	{
	case 0:										//显示“进程”页
		Process.ShowWindow(SW_SHOW);
		Performance.ShowWindow(SW_HIDE);
		Net.ShowWindow(SW_HIDE);
		FileLook.ShowWindow(SW_HIDE);
		FileClean.ShowWindow(SW_HIDE);
		Detail.ShowWindow(SW_HIDE);
		Memeory.ShowWindow(SW_HIDE);
		/*Process.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW);
		Performance.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		Net.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		FileLook.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		FileClean.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		Detail.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		Serv.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);*/
		break;

	case 1:										//显示“性能”页
		Process.ShowWindow(SW_HIDE);
		Performance.ShowWindow(SW_SHOW);
		Net.ShowWindow(SW_HIDE);
		FileLook.ShowWindow(SW_HIDE);
		FileClean.ShowWindow(SW_HIDE);
		Detail.ShowWindow(SW_HIDE);
		Memeory.ShowWindow(SW_HIDE);
		break;
		//显示“网络”页
	case 2:
		Process.ShowWindow(SW_HIDE);
		Performance.ShowWindow(SW_HIDE);
		Net.ShowWindow(SW_SHOW);
		FileLook.ShowWindow(SW_HIDE);
		FileClean.ShowWindow(SW_HIDE);
		Detail.ShowWindow(SW_HIDE);
		Memeory.ShowWindow(SW_HIDE);
		break;

	case 3:										//显示“文件浏览”页
		Process.ShowWindow(SW_HIDE);
		Performance.ShowWindow(SW_HIDE);
		Net.ShowWindow(SW_HIDE);
		FileLook.ShowWindow(SW_SHOW);
		FileClean.ShowWindow(SW_HIDE);
		Detail.ShowWindow(SW_HIDE);
		Memeory.ShowWindow(SW_HIDE);
		break;

	case 4:										//显示“文件清理”页
		Process.ShowWindow(SW_HIDE);
		Performance.ShowWindow(SW_HIDE);
		Net.ShowWindow(SW_HIDE);
		FileLook.ShowWindow(SW_HIDE);
		FileClean.ShowWindow(SW_SHOW);
		Detail.ShowWindow(SW_HIDE);
		Memeory.ShowWindow(SW_HIDE);
		break;

	case 5:										//显示“详细信息”
		Process.ShowWindow(SW_HIDE);
		Performance.ShowWindow(SW_HIDE);
		Net.ShowWindow(SW_HIDE);
		FileLook.ShowWindow(SW_HIDE);
		FileClean.ShowWindow(SW_HIDE);
		Detail.ShowWindow(SW_SHOW);
		Memeory.ShowWindow(SW_HIDE);
		break;

	case 6:										//显示“内存”页
		Process.ShowWindow(SW_HIDE);
		Performance.ShowWindow(SW_HIDE);
		Net.ShowWindow(SW_HIDE);
		FileLook.ShowWindow(SW_HIDE);
		FileClean.ShowWindow(SW_HIDE);
		Detail.ShowWindow(SW_HIDE);
		Memeory.ShowWindow(SW_SHOW);
		break;
	default:break;
	}
}
//——————————————————————————————————————————————————————————————————————————————————————</罗薇>

//——————————————————————————————————————————————————————————————————————————————————————<侯思凡>
/*退出*/
void FlowerManagerDlg::OnExit()
{
	// TODO: 在此添加命令处理程序代码
	if (MessageBox("确认退出？", "", MB_YESNO | MB_ICONQUESTION) == IDYES) {
		this->SendMessage(WM_CLOSE);
	}
}

/*置顶和取消置顶*/
void FlowerManagerDlg::OnUpdateTop(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	CRect rtClient;

	//别人用的BOOL型，取反就好，我还计数，网友真聪明
	switch (TopClick % 2)
	{
	case 0:							//奇数次点击置顶
		GetWindowRect(rtClient);
		::SetWindowPos(m_hWnd, HWND_TOPMOST, rtClient.left, rtClient.top, rtClient.Width(), rtClient.Height(), SWP_SHOWWINDOW);
		pCmdUI->SetCheck(TRUE);
		break;
	default:						//偶数次点击取消置顶
		GetWindowRect(rtClient);
		::SetWindowPos(m_hWnd, HWND_NOTOPMOST, rtClient.left, rtClient.top, rtClient.Width(), rtClient.Height(), SWP_SHOWWINDOW);
		pCmdUI->SetCheck(FALSE);
		break;
	}
	TopClick++;
}

//最小化到托盘
void FlowerManagerDlg::ToTray()
{
	//这是一个结构体，它要帮助我们联系我们的框框
	NOTIFYICONDATA nid;
	nid.cbSize = (DWORD)sizeof(NOTIFYICONDATA);

	nid.hWnd = this->m_hWnd;
	nid.uID = IDR_MAINFRAME;
	nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
	//自定义的消息名称 
	nid.uCallbackMessage = WM_SHOWTASK;
	nid.hIcon = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_MAINFRAME));
	//鼠标滑过的信息提示条——我们是Flowers!!!
	strcpy(nid.szTip, "Flower Manager");

	//在托盘区添加图标 
	Shell_NotifyIcon(NIM_ADD, &nid);

	//隐藏主窗口 
	ShowWindow(SW_HIDE);
}

//wParam接收的是图标的ID，而lParam接收的是鼠标的行为 
LRESULT FlowerManagerDlg::OnShowTask(WPARAM wParam, LPARAM lParam)
{
	if (wParam != IDR_MAINFRAME)
		return 1;

	switch (lParam)
	{
	case WM_RBUTTONUP:				//右键起来时弹出快捷菜单，此处可以直接关闭我们的管理器
	{
		LPPOINT lpoint = new tagPOINT;

		//得到鼠标位置
		::GetCursorPos(lpoint);

		CMenu menu;
		//声明一个弹出式菜单
		menu.CreatePopupMenu();

		//增加菜单项“关闭”，点击则发送消息WM_DESTROY给主窗口（已隐藏），将程序结束。 
		menu.AppendMenu(MF_STRING, WM_DESTROY, "关闭");
		//确定弹出式菜单的位置 
		menu.TrackPopupMenu(TPM_LEFTALIGN, lpoint->x, lpoint->y, this);
		HMENU hmenu = menu.Detach();

		//资源回收 
		menu.DestroyMenu();
		delete lpoint;
	}
	break;

	case WM_LBUTTONDBLCLK: //双击左键的处理 
	{
		//显示主窗口 
		this->ShowWindow(SW_SHOW);
		DeleteTray();
	}
	break;

	default:
		break;
	}
	return 0;
}

//删除托盘区的图标
void FlowerManagerDlg::DeleteTray()
{
	NOTIFYICONDATA nid;
	nid.cbSize = (DWORD)sizeof(NOTIFYICONDATA);

	nid.hWnd = this->m_hWnd;

	nid.uID = IDR_MAINFRAME;
	nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
	nid.uCallbackMessage = WM_SHOWTASK; //自定义的消息名称 
	nid.hIcon = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_MAINFRAME));
	strcpy(nid.szTip, "Flower Manager"); //信息提示条 

	Shell_NotifyIcon(NIM_DELETE, &nid); //在托盘区删除图标 
}

//弹出关于框
void FlowerManagerDlg::OnAbout()
{
	// TODO: 在此添加命令处理程序代码
	//FlowerManagerDlg  *pDlg = new FlowerManagerDlg;
	//pDlg->Create(IDD_ABOUTBOX, this);
	//pDlg->ShowWindow(SW_SHOW);

	CAboutDlg  Dlg;
	Dlg.DoModal();
}
//——————————————————————————————————————————————————————————————————————————————————————</侯思凡>