#ifndef GLOBALSETTING_HEAD_FILE
#define GLOBALSETTING_HEAD_FILE

#include "AirEngineHeader.h"
#include "AirEngineShaderShareParam.h"
namespace Air{
	
	namespace	Common{
		class	Log;
	}
	
	namespace Engine{
		
		namespace	Render{
			class	System;
			class	ITexture;
			class	IMaterial;
		};
		namespace	Physics{
			class	ISystem;
		}
		namespace	Script{
			class	ISystem;
		}
		namespace	UI{
			class	ISystem;
		}
		namespace	Audio{
			class	ISystem;
		}
		namespace	Resource{
			class	ISystem;
		}
		namespace	Net{
			class	ISystem;
		}
		namespace	Particle{
			class	ISystem;
		}
		namespace	Input{
			class	ISystem;
		}
	
		class Camera;
		class	Font;
		/**	\brief	加载引擎需要的参数
		*
		*	加载引擎需要的参数
		*
		***/
		struct	EngineParam{
			EngineParam(){
				hParentWnd	=	NULL;
				hWnd		=	NULL;
				InputWnd	=	NULL;
				ZeroMemory(strPlugin,128);
				ZeroMemory(strGamePlugin,128);
				ZeroMemory(strMedia,128);
				ZeroMemory(strCustomMedia,128);
				ZeroMemory(strDisplay,128);
			};
			HWND	hParentWnd;
			HWND	hWnd;
			HWND	InputWnd;
			AChar	strPlugin[128];
			AChar	strGamePlugin[128];
			AChar	strMedia[128];
			AChar	strCustomMedia[128];
			AChar	strDisplay[128];
		};
		/**	\brief	显示参数
		*
		*	显示参数
		*
		***/
		struct	DisplayParam{
			DisplayParam(){
				iWidth			=	1024;
				iHeight			=	700;
				bWindow			=	true;
				iMSAAType		=	0;
				iMSAAQuality	=	0;
			};
			U32		iWidth;
			U32		iHeight;
			U1		bWindow;
			U32		iMSAAType;
			U32		iMSAAQuality;
		};
	
	#ifndef MAX_LIGHT
	#define MAX_LIGHT	9
	#endif
		/**	\brief	全局设置类
		*
		*	全局设置类
		*
		***/
		class ENGINE_EXPORT	GlobalSetting{
		public:
			GlobalSetting();
			virtual	~GlobalSetting();
	
			/**	\brief	从路径中获取后缀名
			*   
			*	@remarks 	从路径中获取后缀名
			*	@see		GlobalSetting
			*	@return   	AString
			*	@param		AString strName
			*	@note
			*
			**/
			static	U1	ParsePath(AString	strName,AString*	pStrPostfix,AString*	pStrFileName	=	NULL,AString*	pStrPath	=	NULL);	
	
			/**	\brief	获取鼠标射线
			*   
			*	@remarks 	获取鼠标射线
			*	@see		GlobalSetting
			*	@return   	Client::Ray
			*	@param		SInt x
			*	@param		SInt y
			*	@note
			*
			**/
			Ray		GetCursorPostionRay(SInt x	=	-1,SInt y = -1);
	
			/**	\brief	获取按键的字符串
			*   
			*	@remarks 	获取按键的字符串
			*	@see		GlobalSetting
			*	@return   	AString
			*	@param		U8 key
			*	@note
			*
			**/
			AString	GetKeyString(U8	key);
			/**	\brief	将字符串转换为按键
			*   
			*	@remarks 	将字符串转换为按键
			*	@see		GlobalSetting
			*	@return   	U8
			*	@param		AString & str
			*	@note
			*
			**/
			U8		GetKey(AString&	str);
	

	
			//渲染系统

			Physics::ISystem*			m_pPhysicsSystem;	///<	物理系统指针
			Input::ISystem*				m_pInputSystem;		///<	输入系统指针
			Script::ISystem*			m_pScriptSystem;	///<	脚本系统指针
			UI::ISystem*				m_pUISystem;		///<	界面系统指针

			Net::ISystem*				m_pNetSystem;		///<	网络系统指针

			Particle::ISystem*			m_pParticleSystem;	///<	粒子系统指针
	
	
	
	
	
	
	
			UInt						m_uiOrginTechnique;		///<	原始技术
			UInt						m_uiCurrentTechnique;	///<	当前技术
	
	
	
			EngineParam					m_EngineParam;			///<	引擎参数
			DisplayParam				m_DisplayParam;			///<	显示参数
			ShaderShareParam			m_ShaderParam;			///<	着色语言共享参数
	
			Font*						m_pDefaultFont;
	
			U1							m_bQuit;
			/**	\brief	解析三维向量
			*   
			*	@remarks 	解析三维向量
			*	@see		GlobalSetting
			*	@return   	Client::Float3
			*	@param		AString & strValue
			*	@note
			*
			**/
			static	inline	Float3			ParseFloat3(AString&	strValue){
				_XMFLOAT4 v	=	_XMFLOAT4(0,0,0,0);
				if(!strValue.empty())
					sscanf_s(strValue.c_str(),"%f,%f,%f",&v.x,&v.y,&v.z);
				return *(Float3*)&v;
			};
			/**	\brief	解析四维向量
			*   
			*	@remarks 	解析四维向量
			*	@see		GlobalSetting
			*	@return   	Client::Float4
			*	@param		AString & strValue
			*	@note
			*
			**/
			static	inline	Float4			ParseFloat4(AString&	strValue){
				Float4 v	=	Float4(0,0,0,0);
				if(!strValue.empty())
					sscanf_s(strValue.c_str(),"%f,%f,%f,%f",&v.x,&v.y,&v.z,&v.w);
				return v;
			};
	
			/**	\brief	解析四元数
			*   
			*	@remarks 	解析四元数
			*	@see		GlobalSetting
			*	@return   	Client::Float4
			*	@param		AString & strValue
			*	@note
			*
			**/
			static	inline	Float4		ParseQuat(AString&	strValue){
				_XMFLOAT4 v	=	_XMFLOAT4(0,0,0,1);
				if(!strValue.empty())
					sscanf_s(strValue.c_str(),"%f,%f,%f,%f",&v.x,&v.y,&v.z,&v.w);
				return *(Float4*)&v;
			};
	
			/**	\brief	三角形射线检测
			*   
			*	@remarks 	三角形射线检测
			*	@see		GlobalSetting
			*	@return   	bool
			*	@param		Ray & ray
			*	@param		Float3 & v0
			*	@param		Float3 & v1
			*	@param		Float3 & v2
			*	@param		Real * t
			*	@param		Real * u
			*	@param		Real * v
			*	@note
			*
			**/
			bool IntersectTriangle( Ray&		ray,
									Float3&	v0, 
									Float3&	v1, 
									Float3&	v2,
									Real*		t, 
									Real*		u/*	=	NULL*/, 
									Real*		v/*	=	NULL*/ );
			/**	\brief	计算切线
			*   
			*	@remarks 	计算切线
			*	@see		GlobalSetting
			*	@return   	void
			*	@param		UInt vertexCount
			*	@param		Float3 * vertex
			*	@param		Float3 * normal
			*	@param		Vector2 * texcoord
			*	@param		UInt triangleCount
			*	@param		UInt * triangle
			*	@param		Float4 * tangent
			*	@note
			*
			**/
			void CalculateTangentArray(	UInt		vertexCount, 
										Float3*	vertex,
										Float3*	normal,
										Float2*	texcoord,
										UInt		triangleCount,
										UInt*		triangle,
										Float3*	tangent);
		};
	
		/**	\brief	获取全局设置
		*   
		*	@remarks 	获取全局设置
		*	@see		
		*	@return   	GlobalSetting&
		*	@note
		*
		**/
		ENGINE_EXPORT GlobalSetting&	GetGlobalSetting();
	};
};
#endif // GLOBALSETTING_HEAD_FILE