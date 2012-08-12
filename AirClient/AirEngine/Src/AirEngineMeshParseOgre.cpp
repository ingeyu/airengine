/*
-----------------------------------------------------------------------------
This source file is part of OGRE
    (Object-oriented Graphics Rendering Engine)
For the latest info, see http://www.ogre3d.org/

Copyright (c) 2000-2006 Torus Knot Software Ltd
Also see acknowledgements in Readme.html

This program is free software; you can redistribute it and/or modify it under
the terms of the GNU Lesser General Public License as published by the Free Software
Foundation; either version 2 of the License, or (at your option) any later
version.

This program is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License along with
this program; if not, write to the Free Software Foundation, Inc., 59 Temple
Place - Suite 330, Boston, MA 02111-1307, USA, or go to
http://www.gnu.org/copyleft/lesser.txt.

You may alternatively use this source under the terms of a specific version of
the OGRE Unrestricted License provided you have obtained such a license from
Torus Knot Software Ltd.
-----------------------------------------------------------------------------
*/
#include "AirEngineMeshParseOgre.h"

namespace Air{
	
	
	namespace Client {
	
	    AString ParseOgre::msCurrentVersion = "[MeshSerializer_v1.40]";
	    const unsigned short HEADER_CHUNK_ID = 0x1000;
	    //---------------------------------------------------------------------
	    ParseOgre::ParseOgre()
			:mListener(0)
	    {
	        // Set up map
	        mImplementations.insert(
	            ParseOgreImplMap::value_type("[MeshSerializer_v1.10]", 
	            new ParseOgreImpl_v1_1() ) );
	
	        mImplementations.insert(
	           ParseOgreImplMap::value_type("[MeshSerializer_v1.20]", 
	            new ParseOgreImpl_v1_2() ) );
	
	        mImplementations.insert(
	            ParseOgreImplMap::value_type("[MeshSerializer_v1.30]", 
	            new ParseOgreImpl_v1_3() ) );
	
	        mImplementations.insert(
	            ParseOgreImplMap::value_type(msCurrentVersion, 
	            new ParseOgreImpl() ) );
	    }
	    //---------------------------------------------------------------------
	    ParseOgre::~ParseOgre()
	    {
	        // delete map
	        for (ParseOgreImplMap::iterator i = mImplementations.begin();
	            i != mImplementations.end(); ++i)
	        {
	            delete i->second;
	        }
	        mImplementations.clear();
	
	    }
	    //---------------------------------------------------------------------
	    void ParseOgre::exportMesh(const OgreMesh* pMesh, const AString& filename,
			UInt endianMode)
	    {
	        ParseOgreImplMap::iterator impl = mImplementations.find(msCurrentVersion);
	        if (impl == mImplementations.end())
	        {
	//             OGRE_EXCEPT(0, "Cannot find serializer implementation for "
	//                 "current version " + msCurrentVersion, "ParseOgre::exportMesh");
	        }
	
	        impl->second->exportMesh(pMesh, filename, endianMode);
	    }
	    //---------------------------------------------------------------------
	    void ParseOgre::importMesh(DataStreamPtr&	stream, OgreMesh* pDest)
	    {
	        determineEndianness(stream);
	
	        // Read header and determine the version
	        unsigned short headerID;//	=	*(U16*)p;
	        
	        // Read header ID
			//stream.g
	        readShorts(stream, &headerID, 1);
			//Read(&headerID,sizeof(headerID),1,pData,uiPos);
	        
	        if (headerID != HEADER_CHUNK_ID)
	        {
	//             OGRE_EXCEPT(0, "File header not found",
	//                 "ParseOgre::importMesh");
	        }
	        // Read version
	        AString ver = readString(stream);
	// 		AChar	version[MAX_NAME];
	// 		ReadStr(pData,version,uiPos);
	// 		ver	=	version;
	        // Jump back to start
	        stream->seek(0);
	
	        // Find the implementation to use
	        ParseOgreImplMap::iterator impl = mImplementations.find(ver);
	        if (impl == mImplementations.end())
	        {
	//             OGRE_EXCEPT(0, "Cannot find serializer implementation for "
	//                 "current version " + ver, "ParseOgre::importMesh");
	        }
	
	        // Call implementation
	        impl->second->importMesh(stream, pDest, mListener);
	        // Warn on old version of mesh
	        if (ver != msCurrentVersion)
	        {
	//             LogManager("WARNING: " + pDest->getName() + 
	//                 " is an older format (" + ver + "); you should upgrade it as soon as possible" +
	//                 " using the OgreMeshUpgrade tool.");
	        }
	
	    }
	    //---------------------------------------------------------------------
		void ParseOgre::setListener(ParseOgreListener *listener)
		{
			mListener = listener;
		}
		//-------------------------------------------------------------------------
		ParseOgreListener *ParseOgre::getListener()
		{
			return mListener;
		}
	
		/**	\brief	 解析OgreMesh
		*
		*	解析OgreMesh
		*
		***/
		
		class	ParseOgreMesh	:
			public	Mesh::IParseCallBack{
		public:
			ParseOgreMesh(){
				//Mesh::SetParseCallBack(this);
			};
			/**	\brief	解析
			*   
			*	@remarks 	解析
			*	@see		ParseImp
			*	@return   	U1
			*	@param		Mesh::Data * pData
			*	@param		std::vector<Mesh::Vertex> & lstVertex
			*	@param		std::vector<Mesh::Face32> & lstFace32
			*	@param		std::vector<Mesh::Face16> & lstFace16
			*	@param		U1 & bUseNormal
			*	@param		U1 & bUseTexCoord
			*	@param		U1 & bUseTangent
			*	@note
			*
			**/
			virtual	U1	Parse(	Data*					pData,
								std::vector<Mesh::Vertex>&	lstVertex,
								std::vector<Mesh::Face32>&	lstFace32,
								std::vector<Mesh::Face16>&	lstFace16,
								U1&							bUseNormal,
								U1&							bUseTexCoord,
								U1&							bUseTangent)
			{
				ParseOgre parse;
				MemoryDataStream	data(pData->GetBuff(),pData->GetSize());
				DataStreamPtr dataptr(&data);
				OgreMesh mesh;
				parse.importMesh(dataptr,&mesh);
	
				UInt iSize	=	mesh.mSubMeshList.size();
				if(iSize==0)
					return false;
	
				SubMesh&	subMesh	=	*mesh.mSubMeshList[0];
				lstVertex	=	subMesh.m_lstVertex;
				lstFace16	=	subMesh.m_lstFace16;
				lstFace32	=	subMesh.m_lstFace32;
	
				return true;
	
			};
			/**	\brief	获取解析后缀名
			*   
			*	@remarks 	获取解析后缀名
			*	@see		IParseCallBack
			*	@return   	AString
			*	@note
			*
			**/
			virtual	AString	GetPostfixName(){
				return	"mesh";
			}
		};
	
		ParseOgreMesh	g_ParseOgreMesh;
	
	
	}
	
};
