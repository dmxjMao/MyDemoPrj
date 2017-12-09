#pragma once



/*UI≈‰÷√¿‡
*/
class CUICfg {
public:
	//…Ë÷√ui Ù–‘
	CUICfg& operator& (const std::string& s);

protected:
	std::unordered_map<std::string, std::string>	m_cfg;
	boost::regex		m_regex;
};