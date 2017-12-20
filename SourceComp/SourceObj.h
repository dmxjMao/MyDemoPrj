
#pragma once


/*
可连接对象（源对象）
	IConnectionPointContainer（ CCmdTarget已有 ），管理所有出接口；
	内嵌连接点对象（BEGIN_CONNECTION_PART），idl文件定义了出接口：IEventSet
	激发函数；通知sink，见FirePropChanged；

客户实现接收器，并建立sink与连接点的连接；

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
	DECLARE_CONNECTION_MAP()//声明连接映射表
	//内嵌连接点对象
	BEGIN_CONNECTION_PART(CSourceObj, EventSetConnPt)
		virtual REFIID GetIID();
	END_CONNECTION_PART(EventSetConnPt)

	//触发出接口事件
	void FirePropChanged(long nInt);

	//自动化接口，
	afx_msg long GetMyProperty();
	afx_msg void SetMyProperty(long nNewValue);

private:
	long mProperty;
};


