//*****************************************************/
/* @All Right Reserved (C), 2009-2012, CLIENT TECO CO.


 \author    InfernalHell	Xinhe
 \date      2010/04/03
 \version   ver 0.6.0.0
 \filepath  F:\Air\AirClient\AirEngine\Inc
 \filename  EngineHeader.h
 \note     
       
 \attention:
			
 \remarks    created by InfernalHell version 0.6.0.0 
 \History:
   <author>      <time>      <version>         <desc>
******************************************************/


#ifndef ENGINEHEADER_HEAD_FILE
#define ENGINEHEADER_HEAD_FILE


#include "AirCommonHeader.h"
#include "AirEngine.h"
#include "AirUnion.h"
#include "AirRandom.h"
#include "AirCommonFlag.h"
#include "AirCommonMemory.h"
#include "AirCommonHash.h"
#include "AirCommonString.h"
#include "AirCommonPlugin.h"
#include "AirCommonProduct.h"
#include "AirCommonRequestProduct.h"
#include "AirCommonFactory.h"
#include "AirCommonFile.h"
#include "AirCommonPlugin.h"
#include "AirCommonIniFile.h"
#include "AirCommonMath.h"
#include "AirCommonLog.h"
#include "AirCommonConverter.h"
#include "AirCommonLock.h"
#include "AirCommonXml.h"
#include "AirCommonCollision.h"
#include "AirCommonSystemManager.h"
#include "AirCommonRequest.h"
#include "AirInterfaceNode.h"
#include "AirBoundingBox.h"
#include "AirRay.h"
#include "AirTimer.h"





#ifndef ENGINE_LOG_INFO
#define ENGINE_LOG_INFO	LOG_INFO(Engine)
#endif
namespace Air{
	
	namespace Engine{
	
	

		typedef		Common::Matrix			Matrix;	
		typedef		Common::Number			Number;
		typedef		Common::Plane			Plane;
		typedef		Common::AxisAlignedBox	BoundBox;
		typedef		Common::Sphere			Sphere;
		typedef		Common::AxisAlignedBox	AxisAlignedBox;
		typedef		Common::OrientedBox		OrientedBox;
		//typedef		Common::PlaneList		PlaneList;

		typedef		Common::File			File;
		typedef		Common::Data			MemoryData;
		typedef		Common::Data			Data;
		typedef		Common::IniFile			IniFile;
		typedef		Common::IProduct		IProduct;
		typedef		Common::IFactory		IFactory;
		typedef		Common::IFactoryManager	IFactoryManager;
		typedef		Common::Log				Log;
		
		typedef		Common::IntVec4			IntVec4;
		typedef		Common::Converter		Converter;
		typedef		Common::Union4			Union4;
		typedef		Common::Union8			Union8;
		typedef		Common::CriticalSection	CriticalSection;

		typedef		std::vector<Union4*>	Union4Vector;	

		typedef		std::vector<Float4>		VectorArray;
		typedef		std::vector<Float44>	MatrixArray;
		typedef		StringVector			StringArray;

	
	
	
		typedef		Common::IPlugin			IPlugin;
		typedef		Common::Plugin			Plugin;
		typedef		Common::IFactoryManager	IFactoryManager;
		typedef		Common::IFactoryParamList	IFactoryParamList;

	
// 		typedef		YExcel::BasicExcel			Excel;
// 		typedef		YExcel::BasicExcelWorksheet	ExcelWorksheet;
// 		typedef		YExcel::BasicExcelCell		ExcelCell;
	
		typedef		Common::Xml				Xml;
	
		namespace	Render{
			class	System;
			class	Target;
			class	Texture;
			class	IText;
			class	IConstantBuffer;
			class	State;
			struct	LockOption;
			class	Window;
			class	Buffer;
			namespace	Vertex{
				class	IDeclare;
			}
			namespace	Draw{
				struct	Option;
				struct	Buff;
			}
			
		}
		class	Shader;
	
 		typedef		Render::Target				RenderTarget;
		typedef		Render::Window				RenderWindow;
		typedef		Render::System				RenderSystem;
		typedef		Render::State				RenderState;
		typedef		Render::State				SamplerState;
		typedef		Render::State				DepthStencilState;
		typedef		Render::State				RasterizerState;
		typedef		Render::State				BlendState;
		typedef		Render::Buffer				VertexBuffer;
		typedef		Render::Buffer				IndexBuffer;
		typedef		Render::Buffer				Buffer;
		typedef		Render::Vertex::IDeclare	VertexDeclare;
		typedef		Render::IText				RenderText;
		typedef		Render::Texture				Texture;
		typedef		Render::Draw::Buff			DrawBuff;
		typedef		Render::Draw::Option		DrawOption;
		//typedef		Render::IShader				Shader;


		typedef		std::vector<SamplerState*>	SamplerStateVector;
		
		class		Renderable;
		class		SceneNode;
		class		MovableObject;
		class		Camera;
		class		Light;
		class		Scene;
		class		Material;
		class		MaterialTemplate;
		class		Pass;
		class		ShaderProgram;
		class		Pipeline;

		typedef	std::set<Camera*>	CameraSet;
		

	
		/**	\brief	引擎错误日志函数
		*   
		*	@remarks 	引擎错误日志函数
		*	@see		
		*	@return   	void
		*	@param		AChar * strName
		*	@param		AChar * strInfo
		*	@note
		*
		**/
		inline	void	EngineLogError(const AChar*	strName,const AChar*	strInfo){
			AChar	str[MAX_NAME];
			sprintf_s(str,MAX_NAME,"(%s)(%s)",strName,strInfo);
			Common::Logger("Engine","Error",str);
		};
		/**	\brief	引擎警告日志
		*   
		*	@remarks 	引擎警告日志
		*	@see		
		*	@return   	void
		*	@param		AChar * strName
		*	@param		AChar * strInfo
		*	@note
		*
		**/
		inline	void	EngineLogWarnning(AChar*	strName,AChar*	strInfo){
			AChar	str[MAX_NAME];
			sprintf_s(str,MAX_NAME,"(%s)(%s)",strName,strInfo);
			Common::Logger("Engine","Warnning",str);
		};
	
	
	
	
	};
};
#endif // ENGINEHEADER_HEAD_FILE