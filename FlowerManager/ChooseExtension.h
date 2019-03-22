/*
ChooseExtension.h: ���ļ�����ѡ���ļ�����ҳͷ�ļ�
���ߣ�1120151775 ��ޱ
*/
//����������������������������������������������������������������������������������������������������������������������������������������������������������������������������<��ޱ>
#include<string>
using namespace std;

#pragma once


// ChooseExtension �Ի���

class ChooseExtension : public CDialogEx
{
	DECLARE_DYNAMIC(ChooseExtension)

public:
	ChooseExtension(CWnd* pParent = nullptr);   // ��׼���캯��
	virtual ~ChooseExtension();



	// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CHOOSE_EXTENDED };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	BOOL extState[34];
	void AddItem(TCHAR* FileType, TCHAR* FileDescription);
	virtual BOOL OnInitDialog();
	CListCtrl m_list_extension;
	afx_msg void OnLvnItemchangedListExtension(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonExtensionOk();
	afx_msg void OnBnClickedCheckChooseAllExt();
};
//����������������������������������������������������������������������������������������������������������������������������������������������������������������������������</��ޱ>