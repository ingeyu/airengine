#ifndef AirEditorSystem_h__
#define AirEditorSystem_h__

#include "AirGame.h"
#include "AirGameHeader.h"
#include "AirHelperRenderable.h"
#include "OIS.h"

namespace	Air{

	namespace	Editor{
		enum enumControlMode{
			enCM_Select,
			enCM_SelectList,
			enCM_Move,
			enCM_Rotate,
			enCM_Scale,
			enCM_Create
		};

		enum enumCreateType{
			enCT_Object,
			enCT_Actor,
			enCT_Building,
			enCT_Water,
			enCT_Sky
		};
		class	GAME_EXPORT	System	:
			public	Common::IFactoryManager,
			public	Singleton<System>,
			public	OIS::MouseListener,
			public	OIS::KeyListener
		{
		public:
			System();

			virtual	U1	Initialization();
			virtual	U1	Release();
			virtual bool mouseMoved( const OIS::MouseEvent &arg );
			virtual bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
			virtual bool mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
			virtual bool keyPressed( const OIS::KeyEvent &arg );
			virtual bool keyReleased( const OIS::KeyEvent &arg );	
		public:
			
			void			LoadScene(CAString& strName);
			void			SaveScene(CAString& strName);
			U32				GetMeshEntity(Engine::MeshEntity** pObjectArray	=	NULL);
			U32				GetMeshEntityName(AString* pStringArray=NULL);
			void			AddObject(CAString& strName,const Float3& vPos);
		public:
			inline	U1				IsInit(){return m_bInit;};
			inline	enumControlMode	GetControlMode(){return m_CM;};
			inline	enumCreateType	GetCreateType(){return m_CT;};
					void			SetControlMode(enumControlMode m);
			inline	void			SetCreateType(enumCreateType t){m_CT	=	t;};
			inline	void			SetCreateName(CAString& strName){m_strCreateObjectName	=	strName;};
			static	AString			AbsPath2Relatve(const AChar*	strPath);
		protected:
			Ray						BuildRay(S32 x,S32 y);
			void					UpdateRayCastPoint(const Ray& ray);
		protected:
			enumControlMode						m_CM;
			enumCreateType						m_CT;
			Float3								m_vRayCastPoint;
			AString								m_strCreateObjectName;
			Engine::MeshEntity*					m_pRayCastMesh;
			Engine::MeshEntityList				m_lstSelectObj;
			U1									m_bIsControl;
			Engine::ObjectController*			m_pObjController;
			U1									m_bLoading;
			AString								m_strDelaySceneName;
			U1									m_bInit;
			Engine::enumMouseRayCastType		m_MoveType;
			Float2								m_MoveDir;
			Float3								m_OldPos;
		};



	}
	typedef	Editor::System	EditorSystem;
}
#endif // AirEditorSystem_h__
