/*
ChooseExtension.cpp: ���ļ�����ѡ���ļ�����ҳ
���ߣ�1120151775 ��ޱ
*/
//����������������������������������������������������������������������������������������������������������������������������������������������������������������������������<��ޱ>
#include "stdafx.h"
#include "FlowerManager.h"
#include "ChooseExtension.h"
#include "afxdialogex.h"
#include "PAGE5.h"

// ChooseExtension �Ի���

IMPLEMENT_DYNAMIC(ChooseExtension, CDialogEx)

ChooseExtension::ChooseExtension(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CHOOSE_EXTENDED, pParent)
{
}

ChooseExtension::~ChooseExtension()
{
}

void ChooseExtension::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_EXTENSION, m_list_extension);
}

BEGIN_MESSAGE_MAP(ChooseExtension, CDialogEx)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_EXTENSION, &ChooseExtension::OnLvnItemchangedListExtension)
	ON_BN_CLICKED(IDC_BUTTON_EXTENSION_OK, &ChooseExtension::OnBnClickedButtonExtensionOk)
	ON_BN_CLICKED(IDC_CHECK_CHOOSE_ALL_EXT, &ChooseExtension::OnBnClickedCheckChooseAllExt)
END_MESSAGE_MAP()

// ChooseExtension ��Ϣ�������

BOOL ChooseExtension::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	m_list_extension.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT | LVS_EX_CHECKBOXES);
	m_list_extension.InsertColumn(0, "�ļ�����", NULL, 200, 50);
	m_list_extension.InsertColumn(1, "����", NULL, 200, 50);
	AddItem("*.syd", "��ʱ�ļ�");
	AddItem("*.~*", "��ʱ�ļ�");
	AddItem("~*.*", "��ʱ�ļ�");
	AddItem("*.---", "��ʱ�ļ�");
	AddItem("*.^*", "��ʱ�ļ�");
	AddItem("*.??~", "��ʱ�ļ�");
	AddItem("*.??$", "��ʱ�ļ�");
	AddItem("*.tmp", "��ʱ�ļ�");
	AddItem("*._mp", "��ʱ�ļ�");
	AddItem("*.spc", "WordPerfect��ʱ�ļ�");
	AddItem("*.cdr_", "Corel DRAW��ʱ�ļ�");
	AddItem("*.#Res", "Mac Photoshop��ʱ�ļ�");
	AddItem("*.%%%", "��װ����ʱ�ļ�");
	AddItem("*.@@@", "��װ����ʱ�ļ�");
	AddItem("*.$$$", "��װ����ʱ�ļ�");
	AddItem("mscreate.dir", "��װ����ʱ�ļ�");
	AddItem("*.chk", "��ʧ�صĻָ��ļ�");
	AddItem("chklist.*", "��ʧ�صĻָ��ļ�");
	AddItem("*.gid", "������֧�ֵ���ʱ�ļ�");
	AddItem("*.fts", "������֧�ֵ���ʱ�ļ�");
	AddItem("*.ftg", "������֧�ֵ���ʱ�ļ�");
	AddItem("*.ms", "΢���Ʒ�����ļ�");
	AddItem("*.old", "�����ļ�");
	AddItem("*.bak", "�����ļ�");
	AddItem("*.prv", "�����ļ�");
	AddItem("*.wbk", "Word�ı����ļ�");
	AddItem("*.xlk", "Excel�ı����ļ�");
	AddItem("*.pch", "Ԥ����ͷ�ļ�");
	AddItem("*.dmp", "�ڴ�ת���ļ�");
	AddItem("*.diz", "zip�ĵ�˵���ļ�");
	AddItem("Thumbs.db", "ͼƬԤ������ͼ�ļ�");
	AddItem("*.err", "������־�ļ�");
	AddItem("*.log.txt", "������־�ļ�");

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}

void ChooseExtension::AddItem(TCHAR* FileType, TCHAR* FileDescription)
{
	int nItemNum = m_list_extension.GetItemCount();
	m_list_extension.InsertItem(nItemNum, FileType);
	m_list_extension.SetItemText(nItemNum, 1, FileDescription);
	m_list_extension.SetCheck(nItemNum, extState[nItemNum]);
}


void ChooseExtension::OnLvnItemchangedListExtension(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

	*pResult = 0;
}

//���ȷ��ʱ��ҳ����list��checkbox״̬д��extState[i]��Ȼ��رմ���
//���ڸ�ҳ�����ҳ��Ĳ�������
void ChooseExtension::OnBnClickedButtonExtensionOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//string str = "";

	for (int i = 0; i<m_list_extension.GetItemCount(); i++)
	{
		if (m_list_extension.GetCheck(i))
		{
			extState[i] = TRUE;
			//str += "1";
		}
		else
		{
			extState[i] = FALSE;
			//str += "0";
		}
	}

	OnCancel();
}

//ȫѡ��ť
void ChooseExtension::OnBnClickedCheckChooseAllExt()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CButton* pBtn = (CButton*)GetDlgItem(IDC_CHECK_CHOOSE_ALL_EXT);
	int state = pBtn->GetCheck();
	if (state == 0)
	{
		for (int i = 0; i<m_list_extension.GetItemCount(); i++)
		{
			m_list_extension.SetCheck(i, false);
		}
	}
	else
	{
		for (int i = 0; i<m_list_extension.GetItemCount(); i++)
		{
			m_list_extension.SetCheck(i, true);
		}
	}
}
//����������������������������������������������������������������������������������������������������������������������������������������������������������������������������</��ޱ>