/*
PAGE7.cpp: ���ڴ桱ҳ
���ߣ�1120151775 ��ޱ
*/
//����������������������������������������������������������������������������������������������������������������������������������������������������������������������������<��ޱ>

#include <stdio.h>
#include "stdafx.h"
#include "FlowerManager.h"
#include "PAGE7.h"
#include "afxdialogex.h"


// PAGE7 �Ի���

IMPLEMENT_DYNAMIC(PAGE7, CDialogEx)

PAGE7::PAGE7(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_PAGE7, pParent)
{

}

PAGE7::~PAGE7()
{
}

void PAGE7::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_SystemInfo, m_ListSystemInfo);
}


BEGIN_MESSAGE_MAP(PAGE7, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_REFRESH, &PAGE7::OnBnClickedButtonRefresh)
END_MESSAGE_MAP()


// PAGE7 ��Ϣ�������


BOOL PAGE7::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_ListSystemInfo.InsertColumn(0, "ϵͳ�ڴ���Ϣ", NULL, 150, 50);
	m_ListSystemInfo.InsertColumn(1, "����", NULL, 150, 50);

	ListProc();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}

void PAGE7::ListProc()
{
	MEMORYSTATUSEX statex;
	statex.dwLength = sizeof(statex);
	//��ȡϵͳ�ڴ���Ϣ
	GlobalMemoryStatusEx(&statex);

	m_ListSystemInfo.InsertItem(0, "�ڴ�ʹ����");
	TCHAR* MemoryLoad = new TCHAR[10];
	_itoa_s(statex.dwMemoryLoad, MemoryLoad, 10, 10);
	lstrcat(MemoryLoad, " %");
	m_ListSystemInfo.SetItemText(0, 1, MemoryLoad);

	m_ListSystemInfo.InsertItem(1, "�����ڴ�");
	TCHAR* ullTotalPhys = new TCHAR[10];
	_itoa_s((float)statex.ullTotalPhys / 1024 / 1024, ullTotalPhys, 10, 10);
	lstrcat(ullTotalPhys, " MB");
	m_ListSystemInfo.SetItemText(1, 1, ullTotalPhys);

	m_ListSystemInfo.InsertItem(2, "���������ڴ�");
	TCHAR* ullAvailPhys = new TCHAR[10];
	_itoa_s((float)statex.ullAvailPhys / 1024 / 1024, ullAvailPhys, 10, 10);
	lstrcat(ullAvailPhys, " MB");
	m_ListSystemInfo.SetItemText(2, 1, ullAvailPhys);

	m_ListSystemInfo.InsertItem(3, "�ύ���ڴ�����");
	TCHAR* ullTotalPageFile = new TCHAR[10];
	_itoa_s((float)statex.ullTotalPageFile / 1024 / 1024, ullTotalPageFile, 10, 10);
	lstrcat(ullTotalPageFile, " MB");
	m_ListSystemInfo.SetItemText(3, 1, ullTotalPageFile);

	TCHAR sz[MAX_PATH];
	StrFormatByteSize(statex.ullTotalVirtual, sz, MAX_PATH);
	m_ListSystemInfo.InsertItem(4, "�����ڴ�");
	//sprintf(ullTotalVirtual, "%.2f", statex.ullTotalVirtual);
	//_itoa_s((float)statex.ullTotalVirtual / 1024 / 1024 / 1024, ullTotalVirtual, 10, 10);
	//lstrcat(ullTotalVirtual, "GB");
	m_ListSystemInfo.SetItemText(4, 1, sz);

	StrFormatByteSize(statex.ullAvailVirtual, sz, MAX_PATH);
	m_ListSystemInfo.InsertItem(5, "���������ڴ�");
	//TCHAR* ullAvailVirtual = new TCHAR[10];
	//sprintf(ullTotalVirtual, "%.2f", statex.ullAvailVirtual);
	//_itoa_s((float)statex.ullAvailVirtual / 1024 / 1024 / 1024, ullAvailVirtual, 10, 10);
	//lstrcat(ullAvailVirtual, "GB");
	m_ListSystemInfo.SetItemText(5, 1, sz);

}


void PAGE7::OnBnClickedButtonRefresh()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_ListSystemInfo.DeleteAllItems();
	ListProc();
}
//����������������������������������������������������������������������������������������������������������������������������������������������������������������������������</��ޱ>