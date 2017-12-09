#include "stdafx.h"
#include "UICfg.h"


using std::string;

/* echart/css属性名
属性名：属性值   （逗号）分割多个属性
obj & "fontSize:12"
obj & "textColor:#A73232,textAlign:center"

正则
"(?|"
"(fontSize):([0-9]+)|"//字体大小
"(titleAlign):(left|center|right)"//标题对齐
")"
//0整个、1整个?|、 2整个 属性:值、 3属性名、 4值

m_cfg[""] = 默认
初始化调用
m_cfg 用户只设置了部分，没关系，有默认
动态修改
*/
CUICfg& CUICfg::operator & (const string& s)
{
	//匹配属性
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