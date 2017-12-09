#include "stdafx.h"
#include "UICfg.h"


using std::string;

/* echart/css������
������������ֵ   �����ţ��ָ�������
obj & "fontSize:12"
obj & "textColor:#A73232,textAlign:center"

����
"(?|"
"(fontSize):([0-9]+)|"//�����С
"(titleAlign):(left|center|right)"//�������
")"
//0������1����?|�� 2���� ����:ֵ�� 3�������� 4ֵ

m_cfg[""] = Ĭ��
��ʼ������
m_cfg �û�ֻ�����˲��֣�û��ϵ����Ĭ��
��̬�޸�
*/
CUICfg& CUICfg::operator & (const string& s)
{
	//ƥ������
	boost::sregex_iterator it(s.begin(), s.end(), m_regex), itend;
	//std::for_each(it, itend, &CUICfg::ParseCfg);
	for (; it != itend; ++it) {
		//ParseCfg(*it);
		const boost::smatch& cfg = *it;
		
		auto& name = cfg.str(1);
		auto it = m_cfg.find(name);
		if (m_cfg.end() != it) {
			it->second = cfg.str(2);
		}
	}

	return(*this);
}