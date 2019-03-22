/*
VMWalker.cpp: “详细信息”虚拟内存页
作者：1120151764 陈牧乔
*/
//——————————————————————————————————————————————————————————————————————————————————————<陈牧乔>

#include "stdafx.h"
#include "FlowerManager.h"
#include "VMWalker.h"
#include "afxdialogex.h"

#include<windows.h>
#include<psapi.h> 
#include<iostream>
#include<shlwapi.h>
#include<iomanip>
#include<tlhelp32.h>
#pragma comment(lib, "shlwapi.lib")


// VMWalker 对话框

IMPLEMENT_DYNAMIC(VMWalker, CDialogEx)

VMWalker::VMWalker(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_VMWALKER, pParent)
{

}

VMWalker::~VMWalker()
{
}

void VMWalker::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_VMwalker, m_list_vmwalker);
	DDX_Control(pDX, IDC_EDIT_PID, m_pid);
	DDX_Control(pDX, IDC_EDIT_PNAME, m_pname);
	DDX_Control(pDX, IDC_EDIT_PSIZE, m_psize);
}


BEGIN_MESSAGE_MAP(VMWalker, CDialogEx)

END_MESSAGE_MAP()


// VMWalker 消息处理程序

BOOL VMWalker::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_pid.SetWindowText(pid);
	m_pname.SetWindowText(pname);
	m_psize.SetWindowText(psize);

	// TODO:  在此添加额外的初始化
	m_list_vmwalker.InsertColumn(0, "起始地址", NULL, 70, 50);
	m_list_vmwalker.InsertColumn(1, "结束地址", NULL, 70, 50);
	m_list_vmwalker.InsertColumn(2, "大小", NULL, 70, 50);
	m_list_vmwalker.InsertColumn(3, "状态", NULL, 70, 50);
	m_list_vmwalker.InsertColumn(4, "保护", NULL, 100, 50);
	m_list_vmwalker.InsertColumn(5, "类型", NULL, 70, 50);
	m_list_vmwalker.InsertColumn(6, "名称", NULL, 150, 50);

	//根据进程名查询选中进程是否存在
	int returnID = GetProcessidFromName(pname);
	if (returnID == 0)	//选中进程不存在（已被关闭，但是页面没有刷新）
	{
		MessageBox(		//弹出提示框
			_T("选中进程不存在！\n请刷新列表再重新选择"),	//文字内容
			_T("错误提示"),		//顶部文字
			MB_ICONWARNING);	//警告图标
		return FALSE;
	}

	else
	{
		//根据PID打开进程句柄
		HANDLE hP = OpenProcess(
			PROCESS_ALL_ACCESS,		//对进程对象的访问
			FALSE,	//是否继承句柄
			_ttoi(pid));	//要打开进程的PID，将Cstring转换为int

							//遍历虚拟内存，显示其分配情况
		WalkVM(hP);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

//根据进程名查找进程PID
DWORD VMWalker::GetProcessidFromName(LPCTSTR name)
{
	PROCESSENTRY32 pe;
	DWORD id = 0;
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	pe.dwSize = sizeof(PROCESSENTRY32);
	if (!Process32First(hSnapshot, &pe))
		return 0;
	while (1)
	{
		pe.dwSize = sizeof(PROCESSENTRY32);
		if (Process32Next(hSnapshot, &pe) == FALSE)
			break;
		if (strcmp(pe.szExeFile, name) == 0)
		{
			id = pe.th32ProcessID;

			break;
		}
	}
	CloseHandle(hSnapshot);
	return id;
}

void VMWalker::AddItem(TCHAR* startAddtrss, TCHAR* endAddress, TCHAR* size,
	TCHAR* state, TCHAR* protection, TCHAR* type, TCHAR* name)
{
	int nItemNum = m_list_vmwalker.GetItemCount();
	m_list_vmwalker.InsertItem(nItemNum, startAddtrss);
	m_list_vmwalker.SetItemText(nItemNum, 1, endAddress);
	m_list_vmwalker.SetItemText(nItemNum, 2, size);
	m_list_vmwalker.SetItemText(nItemNum, 3, state);
	m_list_vmwalker.SetItemText(nItemNum, 4, protection);
	m_list_vmwalker.SetItemText(nItemNum, 5, type);
	m_list_vmwalker.SetItemText(nItemNum, 6, name);
}

void VMWalker::WalkVM(HANDLE hProcess)
{

	SYSTEM_INFO si;	//系统信息结构
	ZeroMemory(&si, sizeof(si));
	GetSystemInfo(&si);	//获得系统信息

	MEMORY_BASIC_INFORMATION mbi;	//进程虚拟内存空间的基本信息结构
	ZeroMemory(&mbi, sizeof(mbi));	//分配缓冲区，用于保存信息

									//循环整个应用程序的地址空间
	LPCVOID pBlock = (LPVOID)si.lpMinimumApplicationAddress;	//最小地址
	while (pBlock < si.lpMaximumApplicationAddress)
	{
		//获得下一个虚拟内存块的信息
		if (VirtualQueryEx(
			hProcess,	//相关进程句柄
			pBlock,	//开始位置
			&mbi,	//缓冲区
			sizeof(mbi)) == sizeof(mbi))	//确认长度
		{
			//计算块的结尾和长度
			LPVOID pEnd = (PBYTE)pBlock + mbi.RegionSize;	//结尾地址=起始地址+区域大小
			TCHAR szSize[MAX_PATH];
			//将mbi.RegionSize的大小转化为字符串，存在szSize中
			StrFormatByteSize(mbi.RegionSize, szSize, MAX_PATH);

			TCHAR* startAddtrss = new TCHAR[MAX_PATH];
			TCHAR* endAddress = new TCHAR[MAX_PATH];
			TCHAR* size = new TCHAR[MAX_PATH];
			TCHAR* state = new TCHAR[11];
			TCHAR* protection = new TCHAR[15];
			TCHAR* type = new TCHAR[10];
			TCHAR* name = new TCHAR[MAX_PATH];

			//设置块的起始地址
			sprintf_s(startAddtrss, MAX_PATH, "%08x", (DWORD)pBlock);

			//设置块的结束地址
			sprintf_s(endAddress, MAX_PATH, "%08x", (DWORD)pEnd);

			//设置块的大小
			size = szSize;

			//设置块的状态
			switch (mbi.State)
			{
			case MEM_COMMIT:
				state = "Commit";
				break;
			case MEM_FREE:
				state = "Free";
				break;
			case MEM_RESERVE:
				state = "Reserved";
				break;
			default:
				state = "";
				break;
			}

			//设置块的保护
			if (mbi.Protect == 0 && mbi.State != MEM_FREE)
			{
				mbi.Protect = PAGE_READONLY;
			}
			switch (mbi.Protect)
			{
			case PAGE_READONLY:
				protection = "READONLY";
				break;
			case PAGE_GUARD:
				protection = "GUARD";
				break;
			case PAGE_NOCACHE:
				protection = "NOCACHE";
				break;
			case PAGE_READWRITE:
				protection = "READWRITE";
				break;
			case PAGE_WRITECOPY:
				protection = "WRITECOPY";
				break;
			case PAGE_EXECUTE:
				protection = "EXECUTE";
				break;
			case PAGE_EXECUTE_READ:
				protection = "EXECUTE_READ";
				break;
			case PAGE_EXECUTE_READWRITE:
				protection = "EXECUTE_READWRITE";
				break;
			case PAGE_EXECUTE_WRITECOPY:
				protection = "EXECUTE_WRITECOPY";
				break;
			case PAGE_NOACCESS:
				protection = "NOACCESS";
				break;
			default:
				protection = "";
				break;
			}

			//设置块的类型
			switch (mbi.Type)
			{
			case MEM_IMAGE:
				type = "Image";
				break;
			case MEM_MAPPED:
				type = "Mapped";
				break;
			case MEM_PRIVATE:
				type = "Private";
				break;
			default:
				type = "";
				break;
			}

			//检验可执行的映像
			//设置块的名称
			TCHAR szFilename[MAX_PATH];
			if (GetModuleFileName(
				(HMODULE)pBlock,
				szFilename,
				MAX_PATH) > 0)
			{
				//除去路径并显示名称
				PathStripPath(szFilename);
				name = szFilename;
			}
			else
			{
				name = "";
			}

			//在List中添加一行信息
			AddItem(startAddtrss, endAddress, size, state, protection, type, name);

			//移动块指针以获得下一个块
			pBlock = pEnd;
		}
	}
}
//——————————————————————————————————————————————————————————————————————————————————————</陈牧乔>