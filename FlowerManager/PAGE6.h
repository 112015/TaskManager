/*
PAGE6.h: ����ϸ��Ϣ��ҳͷ�ļ�
���ߣ�1120151764 ������
*/
//����������������������������������������������������������������������������������������������������������������������������������������������������������������������������<������>
#pragma once
#include "afxcmn.h"

//#pragma comment(lib,"atlsd.lib") 


// PAGE6 �Ի���

class PAGE6 : public CDialogEx
{
	DECLARE_DYNAMIC(PAGE6)

public:
	PAGE6(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~PAGE6();

	// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PAGE6 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	static int CALLBACK MyCompareProc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);
	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_list_page6;
	virtual BOOL OnInitDialog();
	void AddItem(TCHAR* name, TCHAR* pid, TCHAR* memory, TCHAR* description);
	void ListProc();
	void GetProcessFilePath(IN HANDLE hProcess, OUT CString& sFilePath);
	DWORD GetProcessidFromName(LPCTSTR name);
	afx_msg void OnLvnColumnclickListDetail(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonKillprocess();
	afx_msg void OnBnClickedButtonFreshenP6();
	afx_msg void OnBnClickedButtonVmwalker();
};
//����������������������������������������������������������������������������������������������������������������������������������������������������������������������������</������>