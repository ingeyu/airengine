// 3ds.h: interface for the C3ds class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_3DS_H__04660DA5_F54E_4F1F_9BF8_2607D6D9D0B0__INCLUDED_)
#define AFX_3DS_H__04660DA5_F54E_4F1F_9BF8_2607D6D9D0B0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "AirEngine.h"
#include "AirEngineHeader.h"
//#include "Vector2.h"
//#include "Float3.h"
//
namespace Air{
	
	namespace	Engine{
	
		class ENGINE_EXPORT	C3DS{
		public:
			// This is our 2D point class.  This will be used to store the UV coordinates.
	// 		struct tVector2 {
	// 			float x, y;
	// 		};
			typedef		Float2	tVector2;
			typedef		Float3	tFloat3;
			// This is our face structure.  This is is used for indexing into the vertex 
			// and texture coordinate arrays.  From this information we know which vertices
			// from our vertex array go to which face, along with the correct texture coordinates.
			struct tFace{
				U32	a,b,c;//vertIndex[3];			// indicies for the verts that make up this triangle
				S16 matIndex;						//The texture ID to use, which is the index into our texture array
			};
			
			// This holds the information for a material.  It may be a texture map of a color.
			// Some of t hese are not used, but I left them because you will want to eventually
			// read in the UV tile ratio and the UV tile offset for some models.
			struct tMaterialInfo{
				AChar	strName[255];			// The texture name
				AChar	strFile[255];			// The texture file name (If this is set it's a texture map)
				U8		color[3];				// The color of the object (R, G, B)
				//CTexture cTxt;
			} ;
			// This holds all the information for our model/scene. 
			// You should eventually turn into a robust class that 
			// has loading/drawing/querying functions like:
			// LoadModel(...); DrawObject(...); DrawModel(...); DestroyModel(...);
			struct t3DObject 
			{
				t3DObject(){
					numOfFaces	=	0;
					numOfVerts	=	0;
					numTexVertex=	0;
					pVerts		=	0;
					pFaces		=	0;
					pNormals	=	0;
					pTexVerts	=	0;
					pTangents	=	0;
				};
				SInt  numOfVerts;			// The number of verts in the model
				SInt  numOfFaces;			// The number of faces in the model
				SInt  numTexVertex;			// The number of texture coordinates
				AChar strName[255];			// The name of the object
				tFloat3  *pVerts;			// The object's vertices
				tFloat3  *pNormals;		// The object's normals
				tFloat3  *pTangents;
				tVector2  *pTexVerts;		// The texture's UV coordinates
				tFace *pFaces;				// The faces information of the object
			//  物体的外包框  下面是我自己加上的,你可以不理会
				tFloat3 tCenter; //中心点
				Real xLen,yLen,zLen;//三个方向的长度的一半
			//  子物体列表
				std::list<t3DObject* >lstObj;
			};
			
			// This holds our model information.  This should also turn into a robust class.
			// We use STL's (Standard Template Library) vector class to ease our link list burdens. :)
			struct t3DModel 
			{
				std::vector<tMaterialInfo>	vMaterials;			// The list of material information (Textures and colors)
				std::vector<t3DObject>		vObject;			// The object list for our model
			};
	// 	CTexture m_txt;
	// 	CFrustum *m_pFrustum;
		public:
			U1	Load3DS(char *p_filename);
			U1	LoadFromMemery(U8*	pData,U32	uiSize);
	
			U1	ComputeNormal(U1	bTangent	=	false);
	
			void Draw();
	
			U1 Init(char *sFileName);
	
			t3DModel m_Model;
			C3DS();
			virtual ~C3DS();
	
		};
	
	}
};

#endif // !defined(AFX_3DS_H__04660DA5_F54E_4F1F_9BF8_2607D6D9D0B0__INCLUDED_)
