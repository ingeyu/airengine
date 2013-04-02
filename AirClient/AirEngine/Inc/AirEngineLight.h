#ifndef ENGINELIGHT_HEAD_FILE
#define ENGINELIGHT_HEAD_FILE

#include "AirEngine.h"
#include "AirEngineHeader.h"
#include "AirEngineMovableObject.h"
#include "AirEngineCamera.h"

namespace Air{
	namespace Engine{
	
		//class	Camera;
	
		namespace	Render{
			class	Target;
		}
		/**	\brief	灯光
		*
		*	灯光
		*
		***/
		class	ENGINE_EXPORT	Light	:
			public	Camera{
		public:
			enum	enumType{	
				enPoint,			///<	点光源
				enDirection,		///<	方向
				enSpot				///<	聚光灯
			};
			struct	Info{
				Info(){
					type		=	enPoint;
					vPosition	=	Float4(0,0,0,1);
					vDiff		=	Float4(1,1,1,1);
					fSize		=	1024;
					bCastShadow	=	false;
				};
				void	SetDirection(Float3 dir){
					type		=	enDirection;
					vPosition	=	Float4(dir.x,dir.y,dir.z,0);
					fSize		=	1024;
					bCastShadow	=	false;
				};
				enumType		type;			///<	类型
				Float4	vDiff;			///<	颜色
				Float4	vPosition;		///<	位置
				Real 	fSize;			///<	纹理大小
				U1		bCastShadow;	///<	是否投射阴影
			};
			Light(CAString&	strName,Info*	pInfo);
			/**	\brief	设置灯光类型
			*   
			*	@remarks 	设置灯光类型
			*	@see		Light
			*	@return   	void
			*	@param		enumType type
			*	@note
			*
			**/
			virtual	void		SetLightType(enumType	type);
			/**	\brief	获取灯光类型
			*   
			*	@remarks 	获取灯光类型
			*	@see		Light
			*	@return   	Client::Light::enumType
			*	@note
			*
			**/
			virtual	enumType	GetLightType();
			/**	\brief	获取信息
			*   
			*	@remarks 	获取信息
			*	@see		Light
			*	@return   	Client::Light::Info
			*	@note
			*
			**/
			Info				GetInfo();
	
			/**	\brief	设置颜色
			*   
			*	@remarks 	设置颜色
			*	@see		Light
			*	@return   	void
			*	@param		Float4 color
			*	@note
			*
			**/
			void				SetColor(const Float4&	color);
			Float4				GetColor()const{return m_Info.vDiff;};
	
			/**	\brief	获取灯光位置
			*   
			*	@remarks 	获取灯光位置
			*	@see		Light
			*	@return   	Client::Float4
			*	@note
			*
			**/
			Float4				GetLightPosition();
	
			void				SetAttenuation(Real	fAttenuation);
	
			void				SetSpecular(Real	fSpec);
		protected:
			Info				m_Info;
			Real				m_fAttenuation;			///<	衰减		
	
		};
	};
};
#endif // ENGINELIGHT_HEAD_FILE