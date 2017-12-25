// dllmain.h: 模块类的声明。

class CBankModule : public ATL::CAtlDllModuleT< CBankModule >
{
public :
	DECLARE_LIBID(LIBID_BankLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_BANK, "{53266C4F-3789-49B0-BF38-AC4D54F155BD}")
};

extern class CBankModule _AtlModule;
