/*
PAGE6.cpp: ����ϸ��Ϣ��ҳ
���ߣ�1120151764 ������
*/
//����������������������������������������������������������������������������������������������������������������������������������������������������������������������������<������>

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

int sort_column; // ��¼�������
bool method = false; // ��¼�ȽϷ���
string GetFileVersion(char * strFilePath);

// PAGE6 �Ի���

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


// PAGE6 ��Ϣ�������


BOOL PAGE6::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_list_page6.SetExtendedStyle(LVS_EX_FULLROWSELECT);	//����ѡ��Ϊһ����
	m_list_page6.InsertColumn(0, "����", NULL, 150, 50);
	m_list_page6.InsertColumn(1, "PID", NULL, 80, 50);
	m_list_page6.InsertColumn(2, "�ڴ�", NULL, 80, 50);
	m_list_page6.InsertColumn(3, "����", NULL, 200, 50);

	ListProc();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}

//�г����н���
void PAGE6::ListProc()
{
	PROCESSENTRY32 pe;	//��Ҫinclude tlhelp32.h
	pe.dwSize = sizeof(pe);
	//��õ�ǰ���н��̵Ŀ��գ�TH32CS_SNAPPROCESS���������հ���ϵͳ�����еĽ���
	HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	BOOL bMore = Process32First(hProcessSnap, &pe);		//��õ�һ�����̵ľ��
	while (bMore)
	{
		HANDLE hP = OpenProcess(	//����һ���Ѵ��ڵĽ��̶��󣬲����ؽ��̵ľ��
			PROCESS_ALL_ACCESS,		//�����õ��ķ���Ȩ��
			FALSE,					//���̳о��
			pe.th32ProcessID);		//���̱�ʾ��
		PROCESS_MEMORY_COUNTERS pmc;	//���̵��ڴ�ͳ����Ϣ
		ZeroMemory(&pmc, sizeof(pmc));

		if (GetProcessMemoryInfo(hP, &pmc, sizeof(pmc)) == TRUE)	//�ɹ���ý����ڴ���Ϣ
		{
			TCHAR* name = new TCHAR[MAX_PATH];
			TCHAR* pid = new TCHAR[6];
			TCHAR* memory = new TCHAR[MAX_PATH];
			TCHAR* description = new TCHAR[MAX_PATH];

			//���ý�����
			name = pe.szExeFile;

			//����pid
			_itoa_s(pe.th32ProcessID, pid, 6, 10);

			//�����ڴ��С
			_itoa_s((int)pmc.WorkingSetSize / 1024, memory, MAX_PATH, 10);
			lstrcat(memory, "K");

			//ͨ�����̾����ý��̵�ַ
			CString sFilePath;
			GetProcessFilePath(hP, sFilePath);
			//����õĵ�ַ��CStringת��Ϊchar*����
			char *pchar;
			pchar = (char*)sFilePath.GetBuffer(0);
			//���ݽ��̵�ַ���������Ϣ
			string szVersion;
			szVersion = GetFileVersion(pchar);
			//��������Ϣ�����ʹ�stringת��Ϊchar*��ת��ΪTCHAR*
			_stprintf_s(description, MAX_PATH, "%s", szVersion.c_str());


			AddItem(name, pid, memory, description);
		}
		bMore = Process32Next(hProcessSnap, &pe);	//��ȡ��һ�����̵ľ��
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

//ˢ�°�ť�����list�������г������б�
void PAGE6::OnBnClickedButtonFreshenP6()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_list_page6.DeleteAllItems();
	ListProc();
}

//����ѡ�����̵������ڴ���Ϣ
void PAGE6::OnBnClickedButtonVmwalker()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int i = m_list_page6.GetSelectionMark();//���ѡ���е��б�

	if (i == -1)	//δѡ��
	{
		MessageBox(		//������ʾ��
			_T("����ѡ��һ�������ٲ鿴������Ϣ��"),	//��������
			_T("������ʾ"),		//��������
			MB_ICONWARNING);	//����ͼ��
		return;
	}

	CString s = m_list_page6.GetItemText(i, 1);	//���ѡ�н��̵�PID

	VMWalker* VMWdlg;
	VMWdlg = new VMWalker(this);
	VMWdlg->pid = m_list_page6.GetItemText(i, 1);		//���ѡ�н��̵�pid
	VMWdlg->pname = m_list_page6.GetItemText(i, 0);		//���ѡ�н��̵Ľ�����
	VMWdlg->psize = m_list_page6.GetItemText(i, 2);		//���ѡ�н��̵��ڴ��С

	VMWdlg->DoModal();	//����VMWalker����
}

//�ȽϺ���������list����ĳһ������
int CALLBACK PAGE6::MyCompareProc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	UNREFERENCED_PARAMETER(lParamSort);
	// �Ӳ�������ȡ����Ƚ�lc����������
	int row1 = (int)lParam1;
	int row2 = (int)lParam2;
	CListCtrl* lc = (CListCtrl*)lParamSort;
	CString lp1 = lc->GetItemText(row1, sort_column);
	CString lp2 = lc->GetItemText(row2, sort_column);

	//�����PID���ڴ��С��������������
	if (sort_column == 1 || sort_column == 2)
	{
		if (method)
			return atoi(lp1) - atoi(lp2);
		else
			return atoi(lp2) - atoi(lp1);
	}
	//�������ַ�������
	else
	{
		if (method)
			return lp1.CompareNoCase(lp2);
		else
			return lp2.CompareNoCase(lp1);
	}
	return 0;
}

//��Ӧlist��ĳcolumn�����¼�������
void PAGE6::OnLvnColumnclickListDetail(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	sort_column = pNMLV->iSubItem;	//�������
	int count = m_list_page6.GetItemCount();	//list������
	for (int i = 0; i < count; i++)
	{
		//ÿ�еıȽϹؼ��֣��˴�Ϊ����ţ�������кţ����ȽϺ����ĵ�һ��������
		m_list_page6.SetItemData(i, i);
	}
	method = !method;		//��һ�ε���ı�����˳��
							//��list����
	m_list_page6.SortItems(
		MyCompareProc,			//�ȽϺ���
		(LPARAM)&m_list_page6);	//�ȽϺ����ĵ���������
	*pResult = 0;
}

//���ݽ���·����ý��̵�������Ϣ
string GetFileVersion(char * strFilePath)
{
	DWORD dwSize;
	DWORD dwRtn;
	string szVersion;
	//��ȡ�汾��Ϣ��С  
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
	//��ȡ�汾��Ϣ  
	dwRtn = GetFileVersionInfo(strFilePath, NULL, dwSize, pBuf);
	if (dwRtn == 0)
	{
		return "";
	}
	LPVOID lpBuffer = NULL;
	UINT uLen = 0;

	//�汾��Դ�л�ȡ��Ϣ  
	//����Ӣ�ĺ���������
	dwRtn = VerQueryValue(pBuf,
		TEXT("\\StringFileInfo\\040904B0\\FileDescription"), //0409Ӣ�ģ�04b0:ANSI  
		&lpBuffer,
		&uLen);
	if (dwRtn == 0)
	{
		dwRtn = VerQueryValue(pBuf,
			TEXT("\\StringFileInfo\\080404B0\\FileDescription"), //0804���ģ�04b0:ANSI  
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

//���ݽ��̾����ý���·��
void PAGE6::GetProcessFilePath(IN HANDLE hProcess, OUT CString& sFilePath)
{
	sFilePath = _T("");
	TCHAR tsFileDosPath[MAX_PATH + 1];
	ZeroMemory(tsFileDosPath, sizeof(TCHAR)*(MAX_PATH + 1));
	if (0 == GetProcessImageFileName(hProcess, tsFileDosPath, MAX_PATH + 1))
	{
		return;
	}

	// ��ȡLogic Drive String����
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

//���ݽ��������ҽ���PID
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

//��������
void PAGE6::OnBnClickedButtonKillprocess()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int i = m_list_page6.GetSelectionMark();//���ѡ���е��б�

	if (i == -1)	//δѡ��
	{
		MessageBox(		//������ʾ��
			_T("��ѡ��Ҫ�����Ľ��̣�"),	//��������
			_T("������ʾ"),		//��������
			MB_ICONWARNING);	//����ͼ��
		return;
	}

	CString pid = m_list_page6.GetItemText(i, 1);	//���ѡ�н��̵�PID
	CString pname = m_list_page6.GetItemText(i, 0);	//���ѡ�н��̵�����

													//���ݽ�������ѯѡ�н����Ƿ����
	int returnID = GetProcessidFromName(pname);
	if (returnID == 0)	//ѡ�н��̲����ڣ��ѱ��رգ�����ҳ��û��ˢ�£�
	{
		MessageBox(		//������ʾ��
			_T("ѡ�н����ѹرգ�\n��ˢ���б�"),	//��������
			_T("������ʾ"),		//��������
			MB_ICONWARNING);	//����ͼ��
		return;
	}

	//�򿪽��̣����ؾ��
	HANDLE hP = OpenProcess(
		PROCESS_ALL_ACCESS,     //����Ȩ��    
		FALSE,					//���̳о��
		atoi(pid));				//����PID

								//��ʧ�ܣ���ʾ������
	if (hP == NULL)
	{
		MessageBox(		//������ʾ��
			_T("�򿪽���ʧ�ܣ�"),	//��������
			_T("������ʾ"),		//��������
			MB_ICONWARNING);	//����ͼ��
		return;
	}

	//�������ָ�����̳ɹ�
	if (TerminateProcess(hP, 0))
	{
		MessageBox(		//������ʾ��
			_T("�������̳ɹ���"),	//��������
			_T("��ʾ"),		//��������
			MB_ICONASTERISK);	//��ʾͼ��
	}
	else
	{
		MessageBox(		//������ʾ��
			_T("��������ʧ�ܣ�"),	//��������
			_T("������ʾ"),		//��������
			MB_ICONWARNING);	//����ͼ��
	}

	//ˢ���б�
	m_list_page6.DeleteAllItems();
	ListProc();
}
//����������������������������������������������������������������������������������������������������������������������������������������������������������������������������</������>