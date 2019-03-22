/*
VMWalker.h: ����ϸ��Ϣ�������ڴ�ҳͷ�ļ�
���ߣ�1120151764 ������
*/
//����������������������������������������������������������������������������������������������������������������������������������������������������������������������������<������>
#pragma once


// VMWalker �Ի���

class VMWalker : public CDialogEx
{
	DECLARE_DYNAMIC(VMWalker)

public:
	VMWalker(CWnd* pParent = nullptr);   // ��׼���캯��
	virtual ~VMWalker();

	// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_VMWALKER };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CString pid;
	CString pname;
	CString psize;
	CEdit m_pid;
	CEdit m_pname;
	CEdit m_psize;
	CListCtrl m_list_vmwalker;
	void AddItem(TCHAR* startAddtrss, TCHAR* endAddress, TCHAR* size,
		TCHAR* state, TCHAR* protection, TCHAR* type, TCHAR* name);
	void WalkVM(HANDLE hProcess);
	DWORD GetProcessidFromName(LPCTSTR name);
};
//����������������������������������������������������������������������������������������������������������������������������������������������������������������������������</������>