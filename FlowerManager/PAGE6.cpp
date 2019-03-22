/*
PAGE6.cpp: “详细信息”页
作者：1120151764 陈牧乔
*/
//——————————————————————————————————————————————————————————————————————————————————————<陈牧乔>

#include "stdafx.h"
#include "FlowerManager.h"
#include "PAGE6.h"
#include "VMWalker.h"
#include "afxdialogex.h"
#include <windows.h>
#include"afxcmn.h"
#include <tchar.h>  
#include <string>  
#include <iostream>  
#include "stdio.h"  
#include <Windows.h>
#include <Psapi.h>
#include <Shlwapi.h>
#include <iomanip>
#include <TlHelp32.h>
using namespace std;

#pragma comment(lib, "version.lib")  

int sort_column; // 记录点击的列
bool method = false; // 记录比较方法
string GetFileVersion(char * strFilePath);

// PAGE6 对话框

IMPLEMENT_DYNAMIC(PAGE6, CDialogEx)

PAGE6::PAGE6(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_PAGE6, pParent)
{

}

PAGE6::~PAGE6()
{
}

void PAGE6::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_Detail, m_list_page6);
}


BEGIN_MESSAGE_MAP(PAGE6, CDialogEx)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST_Detail, &PAGE6::OnLvnColumnclickListDetail)
	ON_BN_CLICKED(IDC_BUTTON_KILLPROCESS, &PAGE6::OnBnClickedButtonKillprocess)
	ON_BN_CLICKED(IDC_BUTTON_FRESHEN_P6, &PAGE6::OnBnClickedButtonFreshenP6)
	ON_BN_CLICKED(IDC_BUTTON_VMWALKER, &PAGE6::OnBnClickedButtonVmwalker)
END_MESSAGE_MAP()


// PAGE6 消息处理程序


BOOL PAGE6::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_list_page6.SetExtendedStyle(LVS_EX_FULLROWSELECT);	//设置选中为一整行
	m_list_page6.InsertColumn(0, "名称", NULL, 150, 50);
	m_list_page6.InsertColumn(1, "PID", NULL, 80, 50);
	m_list_page6.InsertColumn(2, "内存", NULL, 80, 50);
	m_list_page6.InsertColumn(3, "描述", NULL, 200, 50);

	ListProc();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

//列出所有进程
void PAGE6::ListProc()
{
	PROCESSENTRY32 pe;	//需要include tlhelp32.h
	pe.dwSize = sizeof(pe);
	//获得当前运行进程的快照，TH32CS_SNAPPROCESS参数：快照包含系统中所有的进程
	HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	BOOL bMore = Process32First(hProcessSnap, &pe);		//获得第一个进程的句柄
	while (bMore)
	{
		HANDLE hP = OpenProcess(	//来打开一个已存在的进程对象，并返回进程的句柄
			PROCESS_ALL_ACCESS,		//渴望得到的访问权限
			FALSE,					//不继承句柄
			pe.th32ProcessID);		//进程标示符
		PROCESS_MEMORY_COUNTERS pmc;	//进程的内存统计信息
		ZeroMemory(&pmc, sizeof(pmc));

		if (GetProcessMemoryInfo(hP, &pmc, sizeof(pmc)) == TRUE)	//成功获得进程内存信息
		{
			TCHAR* name = new TCHAR[MAX_PATH];
			TCHAR* pid = new TCHAR[6];
			TCHAR* memory = new TCHAR[MAX_PATH];
			TCHAR* description = new TCHAR[MAX_PATH];

			//设置进程名
			name = pe.szExeFile;

			//设置pid
			_itoa_s(pe.th32ProcessID, pid, 6, 10);

			//设置内存大小
			_itoa_s((int)pmc.WorkingSetSize / 1024, memory, MAX_PATH, 10);
			lstrcat(memory, "K");

			//通过进程句柄获得进程地址
			CString sFilePath;
			GetProcessFilePath(hP, sFilePath);
			//将获得的地址从CString转换为char*类型
			char *pchar;
			pchar = (char*)sFilePath.GetBuffer(0);
			//根据进程地址获得描述信息
			string szVersion;
			szVersion = GetFileVersion(pchar);
			//将描述信息的类型从string转换为char*再转换为TCHAR*
			_stprintf_s(description, MAX_PATH, "%s", szVersion.c_str());


			AddItem(name, pid, memory, description);
		}
		bMore = Process32Next(hProcessSnap, &pe);	//获取下一个进程的句柄
	}
}

void PAGE6::AddItem(TCHAR* name, TCHAR* pid, TCHAR* memory, TCHAR* description)
{
	int nItemNum = m_list_page6.GetItemCount();
	m_list_page6.InsertItem(nItemNum, name);
	m_list_page6.SetItemText(nItemNum, 1, pid);
	m_list_page6.SetItemText(nItemNum, 2, memory);
	m_list_page6.SetItemText(nItemNum, 3, description);
}

//刷新按钮，清空list并重新列出进程列表
void PAGE6::OnBnClickedButtonFreshenP6()
{
	// TODO: 在此添加控件通知处理程序代码
	m_list_page6.DeleteAllItems();
	ListProc();
}

//弹出选定进程的虚拟内存信息
void PAGE6::OnBnClickedButtonVmwalker()
{
	// TODO: 在此添加控件通知处理程序代码
	int i = m_list_page6.GetSelectionMark();//获得选中行的行标

	if (i == -1)	//未选中
	{
		MessageBox(		//弹出提示框
			_T("请先选择一个进程再查看进程信息！"),	//文字内容
			_T("错误提示"),		//顶部文字
			MB_ICONWARNING);	//警告图标
		return;
	}

	CString s = m_list_page6.GetItemText(i, 1);	//获得选中进程的PID

	VMWalker* VMWdlg;
	VMWdlg = new VMWalker(this);
	VMWdlg->pid = m_list_page6.GetItemText(i, 1);		//获得选中进程的pid
	VMWdlg->pname = m_list_page6.GetItemText(i, 0);		//获得选中进程的进程名
	VMWdlg->psize = m_list_page6.GetItemText(i, 2);		//获得选中进程的内存大小

	VMWdlg->DoModal();	//弹出VMWalker窗口
}

//比较函数，用于list根据某一列排序
int CALLBACK PAGE6::MyCompareProc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	UNREFERENCED_PARAMETER(lParamSort);
	// 从参数中提取所需比较lc的两行数据
	int row1 = (int)lParam1;
	int row2 = (int)lParam2;
	CListCtrl* lc = (CListCtrl*)lParamSort;
	CString lp1 = lc->GetItemText(row1, sort_column);
	CString lp2 = lc->GetItemText(row2, sort_column);

	//如果是PID或内存大小，则按照整数排序
	if (sort_column == 1 || sort_column == 2)
	{
		if (method)
			return atoi(lp1) - atoi(lp2);
		else
			return atoi(lp2) - atoi(lp1);
	}
	//否则按照字符串排序
	else
	{
		if (method)
			return lp1.CompareNoCase(lp2);
		else
			return lp2.CompareNoCase(lp1);
	}
	return 0;
}

//响应list的某column单击事件，排序
void PAGE6::OnLvnColumnclickListDetail(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	sort_column = pNMLV->iSubItem;	//点击的列
	int count = m_list_page6.GetItemCount();	//list的行数
	for (int i = 0; i < count; i++)
	{
		//每行的比较关键字，此处为列序号（点击的列号），比较函数的第一二个参数
		m_list_page6.SetItemData(i, i);
	}
	method = !method;		//下一次点击改变排序顺序
							//对list排序
	m_list_page6.SortItems(
		MyCompareProc,			//比较函数
		(LPARAM)&m_list_page6);	//比较函数的第三个参数
	*pResult = 0;
}

//根据进程路径获得进程的描述信息
string GetFileVersion(char * strFilePath)
{
	DWORD dwSize;
	DWORD dwRtn;
	string szVersion;
	//获取版本信息大小  
	dwSize = GetFileVersionInfoSize(strFilePath, NULL);
	if (dwSize == 0)
	{
		return "";
	}
	char *pBuf;
	pBuf = new char[dwSize + 1];
	if (pBuf == NULL)
		return "";
	memset(pBuf, 0, dwSize + 1);
	//获取版本信息  
	dwRtn = GetFileVersionInfo(strFilePath, NULL, dwSize, pBuf);
	if (dwRtn == 0)
	{
		return "";
	}
	LPVOID lpBuffer = NULL;
	UINT uLen = 0;

	//版本资源中获取信息  
	//查找英文和中文内容
	dwRtn = VerQueryValue(pBuf,
		TEXT("\\StringFileInfo\\040904B0\\FileDescription"), //0409英文；04b0:ANSI  
		&lpBuffer,
		&uLen);
	if (dwRtn == 0)
	{
		dwRtn = VerQueryValue(pBuf,
			TEXT("\\StringFileInfo\\080404B0\\FileDescription"), //0804中文；04b0:ANSI  
			&lpBuffer,
			&uLen);
		if (dwRtn == 0)
		{
			return "";
		}
	}
	szVersion = (char*)lpBuffer;
	delete pBuf;
	return szVersion;
}

//根据进程句柄获得进程路径
void PAGE6::GetProcessFilePath(IN HANDLE hProcess, OUT CString& sFilePath)
{
	sFilePath = _T("");
	TCHAR tsFileDosPath[MAX_PATH + 1];
	ZeroMemory(tsFileDosPath, sizeof(TCHAR)*(MAX_PATH + 1));
	if (0 == GetProcessImageFileName(hProcess, tsFileDosPath, MAX_PATH + 1))
	{
		return;
	}

	// 获取Logic Drive String长度
	UINT uiLen = GetLogicalDriveStrings(0, NULL);
	if (0 == uiLen)
	{
		return;
	}

	PTSTR pLogicDriveString = new TCHAR[uiLen + 1];
	ZeroMemory(pLogicDriveString, uiLen + 1);
	uiLen = GetLogicalDriveStrings(uiLen, pLogicDriveString);
	if (0 == uiLen)
	{
		delete[]pLogicDriveString;
		return;
	}

	TCHAR szDrive[3] = TEXT(" :");
	PTSTR pDosDriveName = new TCHAR[MAX_PATH];
	PTSTR pLogicIndex = pLogicDriveString;

	do
	{
		szDrive[0] = *pLogicIndex;
		uiLen = QueryDosDevice(szDrive, pDosDriveName, MAX_PATH);
		if (0 == uiLen)
		{
			if (ERROR_INSUFFICIENT_BUFFER != GetLastError())
			{
				break;
			}

			delete[]pDosDriveName;
			pDosDriveName = new TCHAR[uiLen + 1];
			uiLen = QueryDosDevice(szDrive, pDosDriveName, uiLen + 1);
			if (0 == uiLen)
			{
				break;
			}
		}

		uiLen = _tcslen(pDosDriveName);
		if (0 == _tcsnicmp(tsFileDosPath, pDosDriveName, uiLen))
		{
			sFilePath.Format(_T("%s%s"), szDrive, tsFileDosPath + uiLen);
			break;
		}

		while (*pLogicIndex++);
	} while (*pLogicIndex);

	delete[]pLogicDriveString;
	delete[]pDosDriveName;
}

//根据进程名查找进程PID
DWORD PAGE6::GetProcessidFromName(LPCTSTR name)
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

//结束进程
void PAGE6::OnBnClickedButtonKillprocess()
{
	// TODO: 在此添加控件通知处理程序代码
	int i = m_list_page6.GetSelectionMark();//获得选中行的行标

	if (i == -1)	//未选中
	{
		MessageBox(		//弹出提示框
			_T("请选择要结束的进程！"),	//文字内容
			_T("错误提示"),		//顶部文字
			MB_ICONWARNING);	//警告图标
		return;
	}

	CString pid = m_list_page6.GetItemText(i, 1);	//获得选中进程的PID
	CString pname = m_list_page6.GetItemText(i, 0);	//获得选中进程的名称

													//根据进程名查询选中进程是否存在
	int returnID = GetProcessidFromName(pname);
	if (returnID == 0)	//选中进程不存在（已被关闭，但是页面没有刷新）
	{
		MessageBox(		//弹出提示框
			_T("选中进程已关闭！\n请刷新列表"),	//文字内容
			_T("错误提示"),		//顶部文字
			MB_ICONWARNING);	//警告图标
		return;
	}

	//打开进程，返回句柄
	HANDLE hP = OpenProcess(
		PROCESS_ALL_ACCESS,     //访问权限    
		FALSE,					//不继承句柄
		atoi(pid));				//进程PID

								//打开失败，提示，返回
	if (hP == NULL)
	{
		MessageBox(		//弹出提示框
			_T("打开进程失败！"),	//文字内容
			_T("错误提示"),		//顶部文字
			MB_ICONWARNING);	//警告图标
		return;
	}

	//如果结束指定进程成功
	if (TerminateProcess(hP, 0))
	{
		MessageBox(		//弹出提示框
			_T("结束进程成功！"),	//文字内容
			_T("提示"),		//顶部文字
			MB_ICONASTERISK);	//提示图标
	}
	else
	{
		MessageBox(		//弹出提示框
			_T("结束进程失败！"),	//文字内容
			_T("错误提示"),		//顶部文字
			MB_ICONWARNING);	//警告图标
	}

	//刷新列表
	m_list_page6.DeleteAllItems();
	ListProc();
}
//——————————————————————————————————————————————————————————————————————————————————————</陈牧乔>