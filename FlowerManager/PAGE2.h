/*
PAGE2.cpp: �����ܡ�ҳͷ�ļ�
���ߣ�1120151769 ��˼��
*/
//����������������������������������������������������������������������������������������������������������������������������������������������������������������������������<��˼��>
#pragma once
//����
#include<Psapi.h>	
#include<Shlwapi.h>
#include<TlHelp32.h>
#include<winbase.h>

#pragma comment(lib,"Shlwapi.lib")  
#pragma comment(lib,"Kernel32.lib")  

// PAGE2 �Ի���

class PAGE2 : public CDialogEx
{
	DECLARE_DYNAMIC(PAGE2)

public:
	PAGE2(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~PAGE2();

	// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PAGE2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	static int CALLBACK MyCompareProc1(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);
	static int CALLBACK MyCompareProc2(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_ListPer;
	CListCtrl m_ListPower;

	//��OnInitDialog���ã���ȡϵͳ�͵������
	void ListProc();
	//д��һ����õ�����ֵ
	void AddItem(bool flag, TCHAR* name, TCHAR* value);

	//��ʼ������
	virtual BOOL OnInitDialog();
	//ˢ�°�ť����Ӧ�¼�
	afx_msg void OnBnClickedButtonper1();
	//��ϵͳ�����б������
	afx_msg void OnLvnColumnclickListper(NMHDR *pNMHDR, LRESULT *pResult);
	//�Ե�Դ�����б������
	afx_msg void OnLvnColumnclickListpower(NMHDR *pNMHDR, LRESULT *pResult);
};

//ϵͳ����������
static int sort_column1;		// ��¼�������
static bool method1;			// ��¼�ȽϷ���
//��Դ����������
static int sort_column2;		// ��¼�������
static bool method2;			// ��¼�ȽϷ���
//����������������������������������������������������������������������������������������������������������������������������������������������������������������������������</��˼��>