
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

	//����Ƕ����
	BEGIN_INTERFACE_PART(MathObj, IMath)
		STDMETHOD(Add)(int, int, long&);
		STDMETHOD(Subtract)(int, int, int&);
	END_INTERFACE_PART(MathObj)

	//�����ӿ�ӳ���
	/*�ӿ�ӳ�����ι�����
	CCmdTarget::InternalQueryInterface()����GetInterface����MFC internal��P377
	*/
	DECLARE_INTERFACE_MAP()
	//����ͨ���೧��CoMath���������
	DECLARE_OLECREATE(CoMath)
};


