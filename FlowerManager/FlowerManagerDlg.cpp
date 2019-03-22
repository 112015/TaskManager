/*
FlowerManagerDlg.cpp: �����
���ߣ�1120151769 ��˼��
     1120151775 ��ޱ
*/
//����������������������������������������������������������������������������������������������������������������������������������������������������������������������������<��˼��>
#include "stdafx.h"
#include "FlowerManager.h"
#include "FlowerManagerDlg.h"
#include "afxdialogex.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

														// ʵ��
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


// FlowerManagerDlg �Ի���



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
	ON_MESSAGE(WM_SHOWTASK, OnShowTask)				//����WM_SHOWTASK����Ϣ��OnShowTask���Լ��������Ϣ��Ӧ����
	ON_COMMAND(ID_ABOUT, &FlowerManagerDlg::OnAbout)
END_MESSAGE_MAP()


// FlowerManagerDlg ��Ϣ�������

BOOL FlowerManagerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���˵�����ӵ�������
	TopMenu.LoadMenu(IDR_MENU1);
	SetMenu(&TopMenu);

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��
//����������������������������������������������������������������������������������������������������������������������������������������������������������������������������</��˼��>

//����������������������������������������������������������������������������������������������������������������������������������������������������������������������������<��ޱ>
// TODO: �ڴ���Ӷ���ĳ�ʼ������
//Tab�ؼ�
// ��ǩ�ؼ��ͻ�����λ�úʹ�С  
	CRect tabRect;

	//�����ǩ��
	m_tab.InsertItem(0, _T("����"));
	m_tab.InsertItem(1, _T("����"));
	m_tab.InsertItem(2, _T("����"));
	m_tab.InsertItem(3, _T("�ļ����"));
	m_tab.InsertItem(4, _T("�ļ�����"));
	m_tab.InsertItem(5, _T("��ϸ��Ϣ"));
	m_tab.InsertItem(6, _T("�ڴ�"));

	//�����ӦҳDialog
	Process.Create(IDD_PAGE1, &m_tab);
	Performance.Create(IDD_PAGE2, &m_tab);
	Net.Create(IDD_PAGE3, &m_tab);
	FileLook.Create(IDD_PAGE4, &m_tab);
	FileClean.Create(IDD_PAGE5, &m_tab);
	Detail.Create(IDD_PAGE6, &m_tab);
	Memeory.Create(IDD_PAGE7, &m_tab);

	// ��ȡ��ǩ�ؼ��ͻ���Rect   
	m_tab.GetClientRect(&tabRect);

	// ����tabRect��ʹ�串�Ƿ�Χ�ʺϷ��ñ�ǩҳ     
	tabRect.left += 0;
	tabRect.right += 5;
	tabRect.top += 25;
	tabRect.bottom -= 0;

	// ���ݵ����õ�tabRect�����ӶԻ��򣬲�����Ϊ��һ����ʾ
	Process.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW);
	Performance.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
	Net.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
	FileLook.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
	FileClean.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
	Detail.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
	Memeory.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}
//����������������������������������������������������������������������������������������������������������������������������������������������������������������������������</��ޱ>

//����������������������������������������������������������������������������������������������������������������������������������������������������������������������������<��˼��>
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
		ToTray(); //��С�������̵ĺ��� 
	}

}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void FlowerManagerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
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
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR FlowerManagerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
//����������������������������������������������������������������������������������������������������������������������������������������������������������������������������</��˼��>

//����������������������������������������������������������������������������������������������������������������������������������������������������������������������������<��ޱ>
//�л���ǩҳ
void FlowerManagerDlg::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
	DWORD nSel = m_tab.GetCurSel();
	switch (nSel)
	{
	case 0:										//��ʾ�����̡�ҳ
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

	case 1:										//��ʾ�����ܡ�ҳ
		Process.ShowWindow(SW_HIDE);
		Performance.ShowWindow(SW_SHOW);
		Net.ShowWindow(SW_HIDE);
		FileLook.ShowWindow(SW_HIDE);
		FileClean.ShowWindow(SW_HIDE);
		Detail.ShowWindow(SW_HIDE);
		Memeory.ShowWindow(SW_HIDE);
		break;
		//��ʾ�����硱ҳ
	case 2:
		Process.ShowWindow(SW_HIDE);
		Performance.ShowWindow(SW_HIDE);
		Net.ShowWindow(SW_SHOW);
		FileLook.ShowWindow(SW_HIDE);
		FileClean.ShowWindow(SW_HIDE);
		Detail.ShowWindow(SW_HIDE);
		Memeory.ShowWindow(SW_HIDE);
		break;

	case 3:										//��ʾ���ļ������ҳ
		Process.ShowWindow(SW_HIDE);
		Performance.ShowWindow(SW_HIDE);
		Net.ShowWindow(SW_HIDE);
		FileLook.ShowWindow(SW_SHOW);
		FileClean.ShowWindow(SW_HIDE);
		Detail.ShowWindow(SW_HIDE);
		Memeory.ShowWindow(SW_HIDE);
		break;

	case 4:										//��ʾ���ļ�����ҳ
		Process.ShowWindow(SW_HIDE);
		Performance.ShowWindow(SW_HIDE);
		Net.ShowWindow(SW_HIDE);
		FileLook.ShowWindow(SW_HIDE);
		FileClean.ShowWindow(SW_SHOW);
		Detail.ShowWindow(SW_HIDE);
		Memeory.ShowWindow(SW_HIDE);
		break;

	case 5:										//��ʾ����ϸ��Ϣ��
		Process.ShowWindow(SW_HIDE);
		Performance.ShowWindow(SW_HIDE);
		Net.ShowWindow(SW_HIDE);
		FileLook.ShowWindow(SW_HIDE);
		FileClean.ShowWindow(SW_HIDE);
		Detail.ShowWindow(SW_SHOW);
		Memeory.ShowWindow(SW_HIDE);
		break;

	case 6:										//��ʾ���ڴ桱ҳ
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
//����������������������������������������������������������������������������������������������������������������������������������������������������������������������������</��ޱ>

//����������������������������������������������������������������������������������������������������������������������������������������������������������������������������<��˼��>
/*�˳�*/
void FlowerManagerDlg::OnExit()
{
	// TODO: �ڴ���������������
	if (MessageBox("ȷ���˳���", "", MB_YESNO | MB_ICONQUESTION) == IDYES) {
		this->SendMessage(WM_CLOSE);
	}
}

/*�ö���ȡ���ö�*/
void FlowerManagerDlg::OnUpdateTop(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	CRect rtClient;

	//�����õ�BOOL�ͣ�ȡ���ͺã��һ����������������
	switch (TopClick % 2)
	{
	case 0:							//�����ε���ö�
		GetWindowRect(rtClient);
		::SetWindowPos(m_hWnd, HWND_TOPMOST, rtClient.left, rtClient.top, rtClient.Width(), rtClient.Height(), SWP_SHOWWINDOW);
		pCmdUI->SetCheck(TRUE);
		break;
	default:						//ż���ε��ȡ���ö�
		GetWindowRect(rtClient);
		::SetWindowPos(m_hWnd, HWND_NOTOPMOST, rtClient.left, rtClient.top, rtClient.Width(), rtClient.Height(), SWP_SHOWWINDOW);
		pCmdUI->SetCheck(FALSE);
		break;
	}
	TopClick++;
}

//��С��������
void FlowerManagerDlg::ToTray()
{
	//����һ���ṹ�壬��Ҫ����������ϵ���ǵĿ��
	NOTIFYICONDATA nid;
	nid.cbSize = (DWORD)sizeof(NOTIFYICONDATA);

	nid.hWnd = this->m_hWnd;
	nid.uID = IDR_MAINFRAME;
	nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
	//�Զ������Ϣ���� 
	nid.uCallbackMessage = WM_SHOWTASK;
	nid.hIcon = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_MAINFRAME));
	//��껬������Ϣ��ʾ������������Flowers!!!
	strcpy(nid.szTip, "Flower Manager");

	//�����������ͼ�� 
	Shell_NotifyIcon(NIM_ADD, &nid);

	//���������� 
	ShowWindow(SW_HIDE);
}

//wParam���յ���ͼ���ID����lParam���յ���������Ϊ 
LRESULT FlowerManagerDlg::OnShowTask(WPARAM wParam, LPARAM lParam)
{
	if (wParam != IDR_MAINFRAME)
		return 1;

	switch (lParam)
	{
	case WM_RBUTTONUP:				//�Ҽ�����ʱ������ݲ˵����˴�����ֱ�ӹر����ǵĹ�����
	{
		LPPOINT lpoint = new tagPOINT;

		//�õ����λ��
		::GetCursorPos(lpoint);

		CMenu menu;
		//����һ������ʽ�˵�
		menu.CreatePopupMenu();

		//���Ӳ˵���رա������������ϢWM_DESTROY�������ڣ������أ�������������� 
		menu.AppendMenu(MF_STRING, WM_DESTROY, "�ر�");
		//ȷ������ʽ�˵���λ�� 
		menu.TrackPopupMenu(TPM_LEFTALIGN, lpoint->x, lpoint->y, this);
		HMENU hmenu = menu.Detach();

		//��Դ���� 
		menu.DestroyMenu();
		delete lpoint;
	}
	break;

	case WM_LBUTTONDBLCLK: //˫������Ĵ��� 
	{
		//��ʾ������ 
		this->ShowWindow(SW_SHOW);
		DeleteTray();
	}
	break;

	default:
		break;
	}
	return 0;
}

//ɾ����������ͼ��
void FlowerManagerDlg::DeleteTray()
{
	NOTIFYICONDATA nid;
	nid.cbSize = (DWORD)sizeof(NOTIFYICONDATA);

	nid.hWnd = this->m_hWnd;

	nid.uID = IDR_MAINFRAME;
	nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
	nid.uCallbackMessage = WM_SHOWTASK; //�Զ������Ϣ���� 
	nid.hIcon = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_MAINFRAME));
	strcpy(nid.szTip, "Flower Manager"); //��Ϣ��ʾ�� 

	Shell_NotifyIcon(NIM_DELETE, &nid); //��������ɾ��ͼ�� 
}

//�������ڿ�
void FlowerManagerDlg::OnAbout()
{
	// TODO: �ڴ���������������
	//FlowerManagerDlg  *pDlg = new FlowerManagerDlg;
	//pDlg->Create(IDD_ABOUTBOX, this);
	//pDlg->ShowWindow(SW_SHOW);

	CAboutDlg  Dlg;
	Dlg.DoModal();
}
//����������������������������������������������������������������������������������������������������������������������������������������������������������������������������</��˼��>