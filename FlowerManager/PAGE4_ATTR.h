/*
PAGE4_ATTR.h: ���ļ����������ҳͷ�ļ�
���ߣ�1120151782 ����ޱ
*/
//����������������������������������������������������������������������������������������������������������������������������������������������������������������������������<����ޱ>
#pragma once


// PAGE4_ATTR �Ի���

class PAGE4_ATTR : public CDialogEx
{
	DECLARE_DYNAMIC(PAGE4_ATTR)

public:
	//��Ҫ����
	PAGE4_ATTR(CWnd* pParent = NULL);   // ��׼���캯�� 
	PAGE4_ATTR(CString  Path);  //���ع��캯��
	virtual ~PAGE4_ATTR();

	// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PAGE4_ATTR };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	CString m_StrFileName;		//�ļ���;
	CString m_StrType;			//����;
	CString m_StrPath;			//·��;
	CString m_StrSize;			//��С;
	CString m_StrCreatTime;		//����ʱ��;
	CString m_StrViewTime;		//����ʱ��;
	CString m_StrModifyTime;	//�޸�ʱ��;
	CString m_StrRead;			//�ļ�����

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
};
//����������������������������������������������������������������������������������������������������������������������������������������������������������������������������</����ޱ>