/*
VMWalker.cpp: ����ϸ��Ϣ�������ڴ�ҳ
���ߣ�1120151764 ������
*/
//����������������������������������������������������������������������������������������������������������������������������������������������������������������������������<������>

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


// VMWalker �Ի���

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


// VMWalker ��Ϣ�������

BOOL VMWalker::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_pid.SetWindowText(pid);
	m_pname.SetWindowText(pname);
	m_psize.SetWindowText(psize);

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_list_vmwalker.InsertColumn(0, "��ʼ��ַ", NULL, 70, 50);
	m_list_vmwalker.InsertColumn(1, "������ַ", NULL, 70, 50);
	m_list_vmwalker.InsertColumn(2, "��С", NULL, 70, 50);
	m_list_vmwalker.InsertColumn(3, "״̬", NULL, 70, 50);
	m_list_vmwalker.InsertColumn(4, "����", NULL, 100, 50);
	m_list_vmwalker.InsertColumn(5, "����", NULL, 70, 50);
	m_list_vmwalker.InsertColumn(6, "����", NULL, 150, 50);

	//���ݽ�������ѯѡ�н����Ƿ����
	int returnID = GetProcessidFromName(pname);
	if (returnID == 0)	//ѡ�н��̲����ڣ��ѱ��رգ�����ҳ��û��ˢ�£�
	{
		MessageBox(		//������ʾ��
			_T("ѡ�н��̲����ڣ�\n��ˢ���б�������ѡ��"),	//��������
			_T("������ʾ"),		//��������
			MB_ICONWARNING);	//����ͼ��
		return FALSE;
	}

	else
	{
		//����PID�򿪽��̾��
		HANDLE hP = OpenProcess(
			PROCESS_ALL_ACCESS,		//�Խ��̶���ķ���
			FALSE,	//�Ƿ�̳о��
			_ttoi(pid));	//Ҫ�򿪽��̵�PID����Cstringת��Ϊint

							//���������ڴ棬��ʾ��������
		WalkVM(hP);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}

//���ݽ��������ҽ���PID
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

	SYSTEM_INFO si;	//ϵͳ��Ϣ�ṹ
	ZeroMemory(&si, sizeof(si));
	GetSystemInfo(&si);	//���ϵͳ��Ϣ

	MEMORY_BASIC_INFORMATION mbi;	//���������ڴ�ռ�Ļ�����Ϣ�ṹ
	ZeroMemory(&mbi, sizeof(mbi));	//���仺���������ڱ�����Ϣ

									//ѭ������Ӧ�ó���ĵ�ַ�ռ�
	LPCVOID pBlock = (LPVOID)si.lpMinimumApplicationAddress;	//��С��ַ
	while (pBlock < si.lpMaximumApplicationAddress)
	{
		//�����һ�������ڴ�����Ϣ
		if (VirtualQueryEx(
			hProcess,	//��ؽ��̾��
			pBlock,	//��ʼλ��
			&mbi,	//������
			sizeof(mbi)) == sizeof(mbi))	//ȷ�ϳ���
		{
			//�����Ľ�β�ͳ���
			LPVOID pEnd = (PBYTE)pBlock + mbi.RegionSize;	//��β��ַ=��ʼ��ַ+�����С
			TCHAR szSize[MAX_PATH];
			//��mbi.RegionSize�Ĵ�Сת��Ϊ�ַ���������szSize��
			StrFormatByteSize(mbi.RegionSize, szSize, MAX_PATH);

			TCHAR* startAddtrss = new TCHAR[MAX_PATH];
			TCHAR* endAddress = new TCHAR[MAX_PATH];
			TCHAR* size = new TCHAR[MAX_PATH];
			TCHAR* state = new TCHAR[11];
			TCHAR* protection = new TCHAR[15];
			TCHAR* type = new TCHAR[10];
			TCHAR* name = new TCHAR[MAX_PATH];

			//���ÿ����ʼ��ַ
			sprintf_s(startAddtrss, MAX_PATH, "%08x", (DWORD)pBlock);

			//���ÿ�Ľ�����ַ
			sprintf_s(endAddress, MAX_PATH, "%08x", (DWORD)pEnd);

			//���ÿ�Ĵ�С
			size = szSize;

			//���ÿ��״̬
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

			//���ÿ�ı���
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

			//���ÿ������
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

			//�����ִ�е�ӳ��
			//���ÿ������
			TCHAR szFilename[MAX_PATH];
			if (GetModuleFileName(
				(HMODULE)pBlock,
				szFilename,
				MAX_PATH) > 0)
			{
				//��ȥ·������ʾ����
				PathStripPath(szFilename);
				name = szFilename;
			}
			else
			{
				name = "";
			}

			//��List�����һ����Ϣ
			AddItem(startAddtrss, endAddress, size, state, protection, type, name);

			//�ƶ���ָ���Ի����һ����
			pBlock = pEnd;
		}
	}
}
//����������������������������������������������������������������������������������������������������������������������������������������������������������������������������</������>