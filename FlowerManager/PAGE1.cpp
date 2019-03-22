/* 
PAGE1.cpp: “进程”页
作者：1120151782 王紫薇    
*/
//——————————————————————————————————————————————————————————————————————————————————————<王紫薇>
#include "stdafx.h"
#include "FlowerManager.h"
#include "PAGE1.h"
//#include "PAGE4_ATTR.h"
#include "afxdialogex.h"

#include <windows.h>
#include <iostream>
#include <iomanip>			//操纵运算子
#include <Tlhelp32.h>		//调用PROCESSENTRY32结构体
#include <stdio.h>
#include <shlwapi.h>
#include <string.h>
#include <stdlib.h>
#include "Memory.h"


// PAGE1 对话框

IMPLEMENT_DYNAMIC(PAGE1, CDialogEx)

PAGE1::PAGE1(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_PAGE1, pParent)
{

}

PAGE1::~PAGE1()
{
}

void PAGE1::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_Process, m_ListProcess);
}


BEGIN_MESSAGE_MAP(PAGE1, CDialog)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_Process, &PAGE1::OnRclickListProcess)
	//ON_COMMAND(ID_Pro_Attr, &PAGE1::OnProAttr)
	ON_COMMAND(ID_PRO_Update, &PAGE1::OnProUpdate)
END_MESSAGE_MAP()


// PAGE1 消息处理程序


BOOL PAGE1::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_ListProcess.InsertColumn(0, "名称", NULL, 100, 50);
	m_ListProcess.InsertColumn(1, "PID", NULL, 80, 50);
	m_ListProcess.InsertColumn(2, "父进程", NULL, 80, 50);
	m_ListProcess.InsertColumn(3, "线程数", NULL, 80, 50);
	m_ListProcess.InsertColumn(4, "优先级", NULL, 80, 50);
	//m_ListProcess.InsertColumn(5, "完整路径", NULL, 70, 50);

	ListProc();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

void PAGE1::ListProc()
{
	PROCESSENTRY32 pe;//定义进程信息结构
	pe.dwSize = sizeof(PROCESSENTRY32);

	HANDLE hProcessShot;
	HANDLE hPro;
	hProcessShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);    //获取进程列表，最后一个参数是0
																	   // 创建系统当前进程快照
	BOOL bRet;
	int i = 0, Parent_Pid;
	bRet = Process32First(hProcessShot, &pe);//从第一个进程开始

	TCHAR* name = new TCHAR[MAX_PATH];
	TCHAR* pid = new TCHAR[6];
	TCHAR* fpid = new TCHAR[6];
	TCHAR* cntThreads = new TCHAR[6];
	TCHAR* PriClassBase = new TCHAR[MAX_PATH];
	TCHAR* FullPath = new TCHAR[MAX_PATH];

	while (bRet) {
		FullPath = "";
		name = pe.szExeFile;
		_itoa_s(pe.th32ProcessID, pid, 6, 10);
		_itoa_s(pe.th32ParentProcessID, fpid, 6, 10);
		_itoa_s(pe.cntThreads, cntThreads, 6, 10);
		_itoa_s(pe.pcPriClassBase, PriClassBase, 6, 10);

		AddItem(name, pid, fpid, cntThreads, PriClassBase);
		bRet = Process32Next(hProcessShot, &pe);
	}//遍历进程快照

	CloseHandle(hProcessShot);
}

void PAGE1::AddItem(TCHAR* name, TCHAR* pid, TCHAR* fpid, TCHAR* cntThreads, TCHAR* PriClassBase)
{
	int nItemNum = m_ListProcess.GetItemCount();   //?
	m_ListProcess.InsertItem(nItemNum, name);
	m_ListProcess.SetItemText(nItemNum, 1, pid);
	m_ListProcess.SetItemText(nItemNum, 2, fpid);
	m_ListProcess.SetItemText(nItemNum, 3, cntThreads);
	m_ListProcess.SetItemText(nItemNum, 4, PriClassBase);
}


void PAGE1::OnRclickListProcess(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	CMenu* pMenuDir = new CMenu;
	pMenuDir->LoadMenu(IDR_MENU2);

	CMenu* pSubThread = pMenuDir->GetSubMenu(1);

	//!获取鼠标位置;
	CPoint point;
	GetCursorPos(&point);

	//弹出;
	pSubThread->TrackPopupMenu(TPM_LEFTALIGN, point.x, point.y, this, NULL);

	*pResult = 0;
}

void PAGE1::OnProUpdate()
{
	// TODO: 在此添加命令处理程序代码
	m_ListProcess.DeleteAllItems();
	//重载进程信息
	ListProc();
}
//——————————————————————————————————————————————————————————————————————————————————————</王紫薇>