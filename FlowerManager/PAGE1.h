/*
PAGE1.h: �����̡�ҳͷ�ļ�
���ߣ�1120151782 ����ޱ
*/
//����������������������������������������������������������������������������������������������������������������������������������������������������������������������������<����ޱ>
#pragma once
//����

// PAGE1 �Ի���

class PAGE1 : public CDialogEx
{
	DECLARE_DYNAMIC(PAGE1)

public:
	PAGE1(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~PAGE1();

	// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PAGE1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_ListProcess;
	virtual BOOL OnInitDialog();
	void ListProc();
	void AddItem(TCHAR* name, TCHAR* pid, TCHAR* fpid, TCHAR* cntThreads, TCHAR* PriClassBase);
	afx_msg void OnRclickListProcess(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnProUpdate();
};
//����������������������������������������������������������������������������������������������������������������������������������������������������������������������������</����ޱ>