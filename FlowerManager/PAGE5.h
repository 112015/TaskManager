/*
PAGE5.h: ���ļ�����ҳͷ�ļ�
���ߣ�1120151764 ������
	 1120151775 ��ޱ
*/
//����������������������������������������������������������������������������������������������������������������������������������������������������������������������������<������>
#pragma once

// PAGE5 �Ի���

class PAGE5 : public CDialogEx
{
	DECLARE_DYNAMIC(PAGE5)

public:
	PAGE5(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~PAGE5();

	// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PAGE5 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	static int CALLBACK MyCompareProc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);
	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_list_page5;
	CEdit m_edit_fileroute;
	afx_msg void OnBnClickedButtonFileroute();
	void searchFile(char * sourceFile);
	afx_msg void OnBnClickedButtonSearch();
	afx_msg void OnLvnColumnclickListPage5(NMHDR *pNMHDR, LRESULT *pResult);
//����������������������������������������������������������������������������������������������������������������������������������������������������������������������������</������>
//����������������������������������������������������������������������������������������������������������������������������������������������������������������������������<��ޱ>
	CEdit m_edit_filetype;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonFiletype();
	afx_msg void OnBnClickedCheckChooseallPage5();
	afx_msg void OnBnClickedButtonClean();
};
//����������������������������������������������������������������������������������������������������������������������������������������������������������������������������</��ޱ>
