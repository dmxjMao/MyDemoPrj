
#pragma once

#include "..\interface\IMath.h"

// CoMath command target

class CoMath : public CCmdTarget
{
	DECLARE_DYNAMIC(CoMath)

public:
	CoMath();
	virtual ~CoMath();

protected:
	DECLARE_MESSAGE_MAP()

	//定义嵌套类
	BEGIN_INTERFACE_PART(MathObj, IMath)
		STDMETHOD(Add)(int, int, long&);
		STDMETHOD(Subtract)(int, int, int&);
	END_INTERFACE_PART(MathObj)

	//声明接口映射表
	/*接口映射表如何工作？
	CCmdTarget::InternalQueryInterface()调用GetInterface，《MFC internal》P377
	*/
	DECLARE_INTERFACE_MAP()
	//声明通用类厂，CoMath是组件对象
	DECLARE_OLECREATE(CoMath)
};


