/*
PAGE3.h: �����硱ҳͷ�ļ�
���ߣ�1120151769 ��˼��
*/
//����������������������������������������������������������������������������������������������������������������������������������������������������������������������������<��˼��>
#pragma once
#include "afxcmn.h"

#include<Winnetwk.h>
#pragma comment(lib,"Mpr.lib")


// PAGE3 �Ի���

class PAGE3 : public CDialogEx
{
	DECLARE_DYNAMIC(PAGE3)

public:
	PAGE3(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~PAGE3();

	// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PAGE3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	static int CALLBACK MyCompareProc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);

	DECLARE_MESSAGE_MAP()
public:
	CTreeCtrl m_TreeNet;
	CListCtrl m_ListNet;

	//�ݹ��������磬ö��������Դ
	void  TreeProc(HTREEITEM hRoot, LPNETRESOURCE lpnr, int depth);
	//��Tree�в���һ���½ڵ�
	HTREEITEM IntsertNode(HTREEITEM hRoot, LPNETRESOURCE lpnrLocal, int depth);
	//��ʾÿһ��Դ������ȡ������ֵ
	void DisplayStruct(int i, LPNETRESOURCE lpnrLocal);
	//���һ����¼
	void AddItem(TCHAR* num, TCHAR* scope, TCHAR* type, TCHAR* displaytype, TCHAR* usage, TCHAR* localname, TCHAR* remotename, TCHAR* comment, TCHAR* provider);

	//��ʼ��
	virtual BOOL OnInitDialog();
	//��껬���ýڵ㣬��ʾ�ýڵ���ӽڵ��������㱨��������Դ����
	afx_msg void OnTvnGetInfoTipTreenet(NMHDR *pNMHDR, LRESULT *pResult);
	//���İ�ť����Ӧ�¼�
	afx_msg void OnBnClickedButtonnet();
	//��ʾѡ�еĽڵ�
	afx_msg void OnTvnSelchangedTreenet(NMHDR *pNMHDR, LRESULT *pResult);
	//���б�ؼ�������
	afx_msg void OnLvnColumnclickListnet(NMHDR *pNMHDR, LRESULT *pResult);
};

//�����б�����
static int sort_column;			// ��¼�������
static bool method;				// ��¼�ȽϷ���
//����������������������������������������������������������������������������������������������������������������������������������������������������������������������������</��˼��>