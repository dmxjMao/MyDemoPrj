
#pragma once


/*
�����Ӷ���Դ����
	IConnectionPointContainer�� CCmdTarget���� �����������г��ӿڣ�
	��Ƕ���ӵ����BEGIN_CONNECTION_PART����idl�ļ������˳��ӿڣ�IEventSet
	����������֪ͨsink����FirePropChanged��

�ͻ�ʵ�ֽ�������������sink�����ӵ�����ӣ�

*/

class CSourceObj : public CCmdTarget
{
	DECLARE_DYNCREATE(CSourceObj)

public:
	CSourceObj();
	virtual ~CSourceObj();

	virtual void OnFinalRelease();

protected:
	DECLARE_MESSAGE_MAP()
	DECLARE_OLECREATE(CSourceObj)
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
	DECLARE_CONNECTION_MAP()//��������ӳ���
	//��Ƕ���ӵ����
	BEGIN_CONNECTION_PART(CSourceObj, EventSetConnPt)
		virtual REFIID GetIID();
	END_CONNECTION_PART(EventSetConnPt)

	//�������ӿ��¼�
	void FirePropChanged(long nInt);

	//�Զ����ӿڣ�
	afx_msg long GetMyProperty();
	afx_msg void SetMyProperty(long nNewValue);

private:
	long mProperty;
};


