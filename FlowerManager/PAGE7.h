/*
PAGE7.h: ���ڴ桱ҳͷ�ļ�
���ߣ�1120151775 ��ޱ
*/
//����������������������������������������������������������������������������������������������������������������������������������������������������������������������������<��ޱ>
#pragma once
#include "afxcmn.h"


// PAGE7 �Ի���

class PAGE7 : public CDialogEx
{
	DECLARE_DYNAMIC(PAGE7)

public:
	PAGE7(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~PAGE7();

	// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PAGE7 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_ListSystemInfo;
	virtual BOOL OnInitDialog();
	void ListProc();
	//void AddItem(TCHAR* name, TCHAR* data);
	afx_msg void OnBnClickedButtonRefresh();
};
//����������������������������������������������������������������������������������������������������������������������������������������������������������������������������</��ޱ>