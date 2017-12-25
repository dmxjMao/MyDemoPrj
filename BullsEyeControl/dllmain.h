// dllmain.h: 模块类的声明。

class CBullsEyeControlModule : public ATL::CAtlDllModuleT< CBullsEyeControlModule >
{
public :
	DECLARE_LIBID(LIBID_BullsEyeControlLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_BULLSEYECONTROL, "{06992E77-1AB3-4BFD-9A0A-6A87FA39155A}")
};

extern class CBullsEyeControlModule _AtlModule;
