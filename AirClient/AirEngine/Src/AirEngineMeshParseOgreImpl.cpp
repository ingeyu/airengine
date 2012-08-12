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
#include "AirEngineMeshParseOgreImpl.h"
#include "AirEngineMeshParseOgre.h"
#include "AirEngineMesh.h"


//#if OGRE_COMPILER == OGRE_COMPILER_MSVC
// Disable conversion warnings, we do a lot of them, intentionally
#   pragma warning (disable : 4267)
//#endif

namespace Air{
	
	namespace Client {
	
	    /// stream overhead = ID + size
	    const long STREAM_OVERHEAD_SIZE = sizeof(U16) + sizeof(U32);
	    //---------------------------------------------------------------------
	    ParseOgreImpl::ParseOgreImpl()
	    {
	
	        // Version number
	        mVersion = "[MeshSerializer_v1.40]";
	    }
	    //---------------------------------------------------------------------
	    ParseOgreImpl::~ParseOgreImpl()
	    {
	    }
	
	    //---------------------------------------------------------------------
	    void ParseOgreImpl::exportMesh(const OgreMesh* pMesh, 
			const AString& filename, UInt endianMode)
	    {
	//         //LogManager("ParseOgre writing mesh data to " + filename + "...");
	// 
	// 		// Decide on endian mode
	// 		//determineEndianness(endianMode);
	// 
	//         // Check that the mesh has it's bounds set
	//         if (pMesh->getBounds().isNull() || pMesh->getBoundingSphereRadius() == 0.0f)
	//         {
	// //             OGRE_EXCEPT(0, "The OgreMesh you have supplied does not have its"
	// //                 " bounds completely defined. Define them first before exporting.",
	// //                 "ParseOgreImpl::exportMesh");
	//         }
	//         mpfFile = fopen(filename.c_str(), "wb");
	// 		if (!mpfFile)
	// 		{
	// // 			OGRE_EXCEPT(0,
	// // 				"Unable to open file " + filename + " for writing",
	// // 				"ParseOgreImpl::exportMesh");
	// 		}
	// 
	//         writeFileHeader();
	//         LogManager("File header written.");
	// 
	// 
	//         LogManager("Writing mesh data...");
	//         writeMesh(pMesh);
	//         LogManager("OgreMesh data exported.");
	// 
	//         fclose(mpfFile);
	//         LogManager("ParseOgre export successful.");
	    }
	    //---------------------------------------------------------------------
		void ParseOgreImpl::importMesh(DataStreamPtr& stream, OgreMesh* pMesh, ParseOgreListener *listener)
	    {
			// Determine endianness (must be the first thing we do!)
			determineEndianness(stream);
	
			// Check header
			readFileHeader(stream);
	
			unsigned short streamID;
			while(!stream->eof())
			{
				streamID = readChunk(stream);
				switch (streamID)
				{
				case M_MESH:
					readMesh(stream, pMesh, listener);
					break;
				}
	
			}
	    }
	   
	    //---------------------------------------------------------------------
	    void ParseOgreImpl::readGeometry(DataStreamPtr& stream, OgreMesh* pMesh,
	        VertexData* dest)
	    {
	
	        //dest->vertexStart = 0;
	
	        unsigned int vertexCount = 0;
	        readInts(stream, &vertexCount, 1);
	        dest->resize(vertexCount);
	
	        // Find optional geometry streams
	        if (!stream->eof())
	        {
	            unsigned short streamID = readChunk(stream);
	            while(!stream->eof() &&
	                (streamID == M_GEOMETRY_VERTEX_DECLARATION ||
	                 streamID == M_GEOMETRY_VERTEX_BUFFER ))
	            {
	                switch (streamID)
	                {
	                case M_GEOMETRY_VERTEX_DECLARATION:
	                    readGeometryVertexDeclaration(stream, pMesh, dest);
	                    break;
	                case M_GEOMETRY_VERTEX_BUFFER:
	                    readGeometryVertexBuff(stream, pMesh, dest);
	                    break;
	                }
	                // Get next stream
	                if (!stream->eof())
	                {
	                    streamID = readChunk(stream);
	                }
	            }
	            if (!stream->eof())
	            {
	                // Backpedal back to start of non-submesh stream
	                stream->skip(-STREAM_OVERHEAD_SIZE);
	            }
	        }
	
			// Perform any necessary colour conversion for an active rendersystem
	// 		if (Root::getSingletonPtr() && Root::getSingleton().getRenderSystem())
	// 		{
	// 			// We don't know the source type if it's VET_COLOUR, but assume ARGB
	// 			// since that's the most common. Won't get used unless the mesh is
	// 			// ambiguous anyway, which will have been warned about in the log
	// 			dest->convertPackedColour(VET_COLOUR_ARGB, 
	// 				VertexElement::getBestColourVertexElementType());
	// 		}
	    }
	    //---------------------------------------------------------------------
	    void ParseOgreImpl::readGeometryVertexDeclaration(DataStreamPtr& stream,
	        OgreMesh* pMesh, VertexData* dest)
	    {
	        // Find optional geometry streams
	        if (!stream->eof())
	        {
	            unsigned short streamID = readChunk(stream);
	            while(!stream->eof() &&
	                (streamID == M_GEOMETRY_VERTEX_ELEMENT ))
	            {
	                switch (streamID)
	                {
	                case M_GEOMETRY_VERTEX_ELEMENT:
	                    readGeometryVertexElement(stream, pMesh, dest);
	                    break;
	                }
	                // Get next stream
	                if (!stream->eof())
	                {
	                    streamID = readChunk(stream);
	                }
	            }
	            if (!stream->eof())
	            {
	                // Backpedal back to start of non-submesh stream
	                stream->skip(-STREAM_OVERHEAD_SIZE);
	            }
	        }
	
		}
	    //---------------------------------------------------------------------
	    void ParseOgreImpl::readGeometryVertexElement(DataStreamPtr& stream,
	        OgreMesh* pMesh, VertexData* dest)
	    {
			unsigned short source, offset, index, tmp;
			VertexElementType vType;
			VertexElementSemantic vSemantic;
			// unsigned short source;  	// buffer bind source
			readShorts(stream, &source, 1);
			// unsigned short type;    	// VertexElementType
			readShorts(stream, &tmp, 1);
			vType = static_cast<VertexElementType>(tmp);
			// unsigned short semantic; // VertexElementSemantic
			readShorts(stream, &tmp, 1);
			vSemantic = static_cast<VertexElementSemantic>(tmp);
			// unsigned short offset;	// start offset in buffer in bytes
			readShorts(stream, &offset, 1);
			// unsigned short index;	// index of the semantic
			readShorts(stream, &index, 1);
	
			//dest->vertexDeclaration->addElement(source, offset, vType, vSemantic, index);
	
	// 		if (vType == VET_COLOUR)
	// 		{
	// 			LogManager::getSingleton().stream()
	// 				<< "Warning: VET_COLOUR element type is deprecated, you should use "
	// 				<< "one of the more specific types to indicate the byte order. "
	// 				<< "Use OgreMeshUpgrade on " << pMesh->getName() << " as soon as possible. ";
	// 		}
	
		}
	    //---------------------------------------------------------------------
	    void ParseOgreImpl::readGeometryVertexBuff(DataStreamPtr& stream,
	        OgreMesh* pMesh, VertexData* dest)
	    {
			unsigned short bindIndex, vertexSize;
			// unsigned short bindIndex;	// Index to bind this buffer to
			readShorts(stream, &bindIndex, 1);
			// unsigned short vertexSize;	// Per-vertex size, must agree with declaration at this index
			readShorts(stream, &vertexSize, 1);
	
			// Check for vertex data header
			unsigned short headerID;
			headerID = readChunk(stream);
			if (headerID != M_GEOMETRY_VERTEX_BUFFER_DATA)
			{
				OGRE_EXCEPT(0, "Can't find vertex buffer data area",
	            	"ParseOgreImpl::readGeometryVertexBuff");
			}
			// Check that vertex size agrees
	// 		if (dest->vertexDeclaration->getVertexSize(bindIndex) != vertexSize)
	// 		{
	// 			OGRE_EXCEPT(0, "Buffer vertex size does not agree with vertex declaration",
	//             	"ParseOgreImpl::readGeometryVertexBuff");
	// 		}
	
			// Create / populate vertex buffer
			UInt uiSize	=	dest->size();
			U8*	p	=	new	U8[uiSize*vertexSize];
			//dest->resize()
	        stream->read(p, uiSize * vertexSize);
			float*	pFloat	=	(float*)p;
			int iPerFloat	=	vertexSize/sizeof(float);
			VertexData& data	=	*dest;
			for(UInt i=0;i<uiSize;i++){
				data[i].Position.x	=	pFloat[iPerFloat*i];
				data[i].Position.y	=	pFloat[iPerFloat*i+1];
				data[i].Position.z	=	pFloat[iPerFloat*i+2];
				if(iPerFloat==11){
					data[i].Normal.x	=	pFloat[iPerFloat*i+3];
					data[i].Normal.y	=	pFloat[iPerFloat*i+4];
					data[i].Normal.z	=	pFloat[iPerFloat*i+5];
					data[i].UV.x	=	pFloat[iPerFloat*i+6];
					data[i].UV.y	=	pFloat[iPerFloat*i+7];
					data[i].Tangent.x	=	pFloat[iPerFloat*i+8];
					data[i].Tangent.y	=	pFloat[iPerFloat*i+9];
					data[i].Tangent.z	=	pFloat[iPerFloat*i+10];
				}
				else	if(iPerFloat==8){
					data[i].Normal.x	=	pFloat[iPerFloat*i+3];
					data[i].Normal.y	=	pFloat[iPerFloat*i+4];
					data[i].Normal.z	=	pFloat[iPerFloat*i+5];
					data[i].UV.x	=	pFloat[iPerFloat*i+6];
					data[i].UV.y	=	pFloat[iPerFloat*i+7];
				}else	if(iPerFloat==5){
					data[i].UV.x	=	pFloat[iPerFloat*i+3];
					data[i].UV.y	=	pFloat[iPerFloat*i+4];
				}
			}
			delete[] p;
	
			// endian conversion for OSX
	// 		flipFromLittleEndian(
	// 			pBuf,
	// 			dest->vertexCount,
	// 			vertexSize,
	// 			dest->vertexDeclaration->findElementsBySource(bindIndex));
	/*        vbuf->unlock();*/
	
			// Set binding
	 //       dest->VertexBuffBinding->setBinding(bindIndex, vbuf);
	
		}
	    //---------------------------------------------------------------------
		void ParseOgreImpl::readSubMeshNameTable(DataStreamPtr& stream, OgreMesh* pMesh)
		{
			// The map for
			std::map<unsigned short, AString> subMeshNames;
			unsigned short streamID, subMeshIndex;
	
			// Need something to store the index, and the objects name
			// This table is a method that imported meshes can retain their naming
			// so that the names established in the modelling software can be used
			// to get the sub-meshes by name. The exporter must support exporting
			// the optional stream M_SUBMESH_NAME_TABLE.
	
	        // Read in all the sub-streams. Each sub-stream should contain an index and Ogre::AString for the name.
			if (!stream->eof())
			{
				streamID = readChunk(stream);
				while(!stream->eof() && (streamID == M_SUBMESH_NAME_TABLE_ELEMENT ))
				{
					// Read in the index of the submesh.
					readShorts(stream, &subMeshIndex, 1);
					// Read in the AString and map it to its index.
					subMeshNames[subMeshIndex] = readString(stream);
	
					// If we're not end of file get the next stream ID
					if (!stream->eof())
						streamID = readChunk(stream);
				}
				if (!stream->eof())
				{
					// Backpedal back to start of stream
					stream->skip(-STREAM_OVERHEAD_SIZE);
				}
			}
	
			// Set all the submeshes names
			// ?
	
			// Loop through and save out the index and names.
	// 		std::map<unsigned short, AString>::const_iterator it = subMeshNames.begin();
	// 
	// 		while(it != subMeshNames.end())
	// 		{
	// 			// Name this submesh to the stored name.
	// 			//pMesh->nameSubMesh(it->second, it->first);
	// 			++it;
	// 		}
	
	
	
		}
	    //---------------------------------------------------------------------
	    void ParseOgreImpl::readMesh(DataStreamPtr& stream, OgreMesh* pMesh, ParseOgreListener *listener)
	    {
	        unsigned short streamID;
	
	        // Never automatically build edge lists for this version
	        // expect them in the file or not at all
	        pMesh->mAutoBuildEdgeLists = false;
	
			// bool skeletallyAnimated
			bool skeletallyAnimated;
			readBools(stream, &skeletallyAnimated, 1);
	
	        // Find all substreams
	        if (!stream->eof())
	        {
	            streamID = readChunk(stream);
	            while(!stream->eof() &&
	                (streamID == M_GEOMETRY ||
					 streamID == M_SUBMESH ||
	                 streamID == M_MESH_SKELETON_LINK ||
	                 streamID == M_MESH_BONE_ASSIGNMENT ||
					 streamID == M_MESH_LOD ||
	                 streamID == M_MESH_BOUNDS ||
					 streamID == M_SUBMESH_NAME_TABLE ||
					 streamID == M_EDGE_LISTS ||
					 streamID == M_POSES ||
					 streamID == M_ANIMATIONS ||
					 streamID == M_TABLE_EXTREMES))
	            {
	                switch(streamID)
	                {
					case M_GEOMETRY:
						pMesh->sharedVertexData = OGRE_NEW VertexData();
						try {
							readGeometry(stream, pMesh, pMesh->sharedVertexData);
						}
						catch (...)
						{
	
						}
						break;
	                case M_SUBMESH:
	                    readSubMesh(stream, pMesh, listener);
	                    break;
	                case M_MESH_SKELETON_LINK:
	                    readSkeletonLink(stream, pMesh, listener);
	                    break;
	                case M_MESH_BONE_ASSIGNMENT:
	                    readMeshBoneAssignment(stream, pMesh);
	                    break;
	                case M_MESH_LOD:
						readMeshLodInfo(stream, pMesh);
						break;
	                case M_MESH_BOUNDS:
	                    readBoundsInfo(stream, pMesh);
	                    break;
					case M_SUBMESH_NAME_TABLE:
	    	            readSubMeshNameTable(stream, pMesh);
						break;
	                case M_EDGE_LISTS:
	                    readEdgeList(stream, pMesh);
	                    break;
					case M_POSES:
						readPoses(stream, pMesh);
						break;
					case M_ANIMATIONS:
						readAnimations(stream, pMesh);
	                    break;
	                case M_TABLE_EXTREMES:
	                    readExtremes(stream, pMesh);
	                    break;
	                }
	
	                if (!stream->eof())
	                {
	                    streamID = readChunk(stream);
	                }
	
	            }
	            if (!stream->eof())
	            {
	                // Backpedal back to start of stream
	                stream->skip(-STREAM_OVERHEAD_SIZE);
	            }
	        }
	
	    }
	    //---------------------------------------------------------------------
	    void ParseOgreImpl::readSubMesh(DataStreamPtr& stream, OgreMesh* pMesh, ParseOgreListener *listener)
	    {
	        unsigned short streamID;
	
	        SubMesh* sm = new	SubMesh;//pMesh->createSubMesh();
	
	        // char* materialName
	        AString materialName = readString(stream);
	
	        //sm->mMaterialName	=	materialName;
	
	        bool useSharedVertices;
	        readBools(stream,&useSharedVertices, 1);
	
	        //sm->indexData->indexStart = 0;
	        unsigned int indexCount = 0;
	        readInts(stream, &indexCount, 1);
	        //sm->(indexCount);
	
	        //HardwareIndexBuffSharedPtr ibuf;
	        // bool indexes32Bit
	        bool idx32bit;
	        readBools(stream, &idx32bit, 1);
	        if (idx32bit)
	        {
				sm->m_lstFace32.resize(indexCount/3);
				Mesh::Face32* pFace	=	new	Mesh::Face32[indexCount/3];
	             readInts(stream, (UInt*)&pFace[0], indexCount);
	             //delete[] pIdx;
				 for(UInt i=0;i<indexCount/3;i++){
					sm->m_lstFace32[i].f0	=	pFace[i].f0;
					sm->m_lstFace32[i].f1	=	pFace[i].f1;
					sm->m_lstFace32[i].f2	=	pFace[i].f2;
				 }
				 delete[]	pFace;
	
	        }
	        else // 16-bit
	        {
				sm->m_lstFace16.resize(indexCount/3);
				Mesh::Face16* pFace	=	new	Mesh::Face16[indexCount/3];
	             readShorts(stream, (U16*)&pFace[0], indexCount);
				 for(UInt i=0;i<indexCount/3;i++){
					 sm->m_lstFace16[i].f0	=	pFace[i].f0;
					 sm->m_lstFace16[i].f1	=	pFace[i].f1;
					 sm->m_lstFace16[i].f2	=	pFace[i].f2;
				 }
				 delete[]	pFace;
	        }
	
	        // M_GEOMETRY stream (Optional: present only if useSharedVertices = false)
	        if (!useSharedVertices)
	        {
	            streamID = readChunk(stream);
	            if (streamID != M_GEOMETRY)
	            {
	                OGRE_EXCEPT(0, "Missing geometry data in mesh file",
	                    "ParseOgreImpl::readSubMesh");
	            }
	            //sm->vertexData = OGRE_NEW VertexData();
	            readGeometry(stream, pMesh, &sm->m_lstVertex);
	        }
	
	
	        // Find all bone assignments, submesh operation, and texture aliases (if present)
	        if (!stream->eof())
	        {
	            streamID = readChunk(stream);
	            while(!stream->eof() &&
	                (streamID == M_SUBMESH_BONE_ASSIGNMENT ||
	                 streamID == M_SUBMESH_OPERATION ||
	                 streamID == M_SUBMESH_TEXTURE_ALIAS))
	            {
	                switch(streamID)
	                {
	                case M_SUBMESH_OPERATION:
	                    readSubMeshOperation(stream, pMesh, sm);
	                    break;
	                case M_SUBMESH_BONE_ASSIGNMENT:
	                    readSubMeshBoneAssignment(stream, pMesh, sm);
	                    break;
	                case M_SUBMESH_TEXTURE_ALIAS:
	                    readSubMeshTextureAlias(stream, pMesh, sm);
	                    break;
	                }
	
	                if (!stream->eof())
	                {
	                    streamID = readChunk(stream);
	                }
	
	            }
	            if (!stream->eof())
	            {
	                // Backpedal back to start of stream
	                stream->skip(-STREAM_OVERHEAD_SIZE);
	            }
	        }
	
			pMesh->mSubMeshList.push_back(sm);
	    }
	    //---------------------------------------------------------------------
	    void ParseOgreImpl::readSubMeshOperation(DataStreamPtr& stream,
	        OgreMesh* pMesh, SubMesh* sm)
	    {
	        // unsigned short operationType
	        unsigned short opType;
	        readShorts(stream, &opType, 1);
	        //sm->operationType = static_cast<RenderOperation::OperationType>(opType);
	    }
	    //---------------------------------------------------------------------
	    void ParseOgreImpl::readSubMeshTextureAlias(DataStreamPtr& stream, OgreMesh* pMesh, SubMesh* sub)
	    {
	        AString aliasName = readString(stream);
	        AString textureName = readString(stream);
	        //sub->addTextureAlias(aliasName, textureName);
	    }
	    //---------------------------------------------------------------------
	    void ParseOgreImpl::readSkeletonLink(DataStreamPtr& stream, OgreMesh* pMesh, ParseOgreListener *listener)
	    {
	        AString skelName = readString(stream);
	
			if(listener)
				listener->processSkeletonName(pMesh, &skelName);
	
	        pMesh->mSkeletonName	=	(skelName);
	    }
	    //---------------------------------------------------------------------
	    void ParseOgreImpl::readTextureLayer(DataStreamPtr& stream, OgreMesh* pMesh,
	        MaterialPtr& pMat)
	    {
	        // Material definition section phased out of 1.1
	    }
	
	    //---------------------------------------------------------------------
	    void ParseOgreImpl::readMeshBoneAssignment(DataStreamPtr& stream, OgreMesh* pMesh)
	    {
	        //VertexBoneAssignment assign;
			UInt	i32;
			U16		i16;
			Real	f32;
	
	        // unsigned int vertexIndex;
	        readInts(stream, &(i32),1);
	        // unsigned short boneIndex;
	        readShorts(stream, &(i16),1);
	        // float weight;
	        readFloats(stream, &(f32), 1);
	
	        //pMesh->addBoneAssignment(assign);
	
	    }
	    //---------------------------------------------------------------------
	    void ParseOgreImpl::readSubMeshBoneAssignment(DataStreamPtr& stream,
	        OgreMesh* pMesh, SubMesh* sub)
	    {
	        //VertexBoneAssignment assign;
			UInt	i32;
			U16		i16;
			Real	f32;
	
	
	        // unsigned int vertexIndex;
	        readInts(stream, &(i32),1);
	        // unsigned short boneIndex;
	        readShorts(stream, &(i16),1);
	        // float weight;
	        readFloats(stream, &(f32), 1);
	
	        //sub->addBoneAssignment(assign);
	
	    }
	
	    //---------------------------------------------------------------------
	
	    //---------------------------------------------------------------------
	    void ParseOgreImpl::readBoundsInfo(DataStreamPtr& stream, OgreMesh* pMesh)
	    {
	        Float3 min, max;
	        // float minx, miny, minz
	        readFloats(stream, &min.x, 1);
	        readFloats(stream, &min.y, 1);
	        readFloats(stream, &min.z, 1);
	        // float maxx, maxy, maxz
	        readFloats(stream, &max.x, 1);
	        readFloats(stream, &max.y, 1);
	        readFloats(stream, &max.z, 1);
			//BoundBox box(min, max);
	        //pMesh->_setBounds(box, true);
	        // float radius
	        float radius;
	        readFloats(stream, &radius, 1);
	        //pMesh->_setBoundingSphereRadius(radius);
	
	
	
	    }
	    //---------------------------------------------------------------------
		void ParseOgreImpl::readMeshLodInfo(DataStreamPtr& stream, OgreMesh* pMesh)
		{
			unsigned short streamID, i;
	
	        // unsigned short numLevels;
			readShorts(stream, &(pMesh->mNumLods), 1);
	        // bool manual;  (true for manual alternate meshes, false for generated)
			readBools(stream, &(pMesh->mIsLodManual), 1);
	
			// Preallocate submesh lod face data if not manual
			if (!pMesh->mIsLodManual)
			{
				unsigned short numsubs = pMesh->mSubMeshList.size();//>getNumSubMeshes();
				for (i = 0; i < numsubs; ++i)
				{
					SubMesh* sm = pMesh->mSubMeshList[i];//(i);
					//sm->mLodFaceList	= 0;//.resize(pMesh->mNumLods-1);
				}
			}
	
			// Loop from 1 rather than 0 (full detail index is not in file)
			for (i = 1; i < pMesh->mNumLods; ++i)
			{
				streamID = readChunk(stream);
				if (streamID != M_MESH_LOD_USAGE)
				{
					OGRE_EXCEPT(0,
						"Missing M_MESH_LOD_USAGE stream in " + pMesh->getName(),
						"ParseOgreImpl::readMeshLodInfo");
				}
				// Read depth
				MeshLodUsage usage;
				float fromDepthSquared;
				readFloats(stream, &(fromDepthSquared), 1);
	
				if (pMesh->mIsLodManual)
				{
					readMeshLodUsageManual(stream, pMesh, i, usage);
				}
				else //(!pMesh->isLodManual)
				{
					readMeshLodUsageGenerated(stream, pMesh, i, usage);
				}
	            usage.edgeData = NULL;
	
				// Save usage
				pMesh->mMeshLodUsageList.push_back(usage);
			}
	
	
		}
	    //---------------------------------------------------------------------
		void ParseOgreImpl::readMeshLodUsageManual(DataStreamPtr& stream,
	        OgreMesh* pMesh, unsigned short lodNum, MeshLodUsage& usage)
		{
			unsigned long streamID;
			// Read detail stream
			streamID = readChunk(stream);
			if (streamID != M_MESH_LOD_MANUAL)
			{
				OGRE_EXCEPT(0,
					"Missing M_MESH_LOD_MANUAL stream in " + pMesh->getName(),
					"ParseOgreImpl::readMeshLodUsageManual");
			}
	
			usage.manualName = readString(stream);
			//usage.manualMesh.setNull(); // will trigger load later
		}
	    //---------------------------------------------------------------------
		void ParseOgreImpl::readMeshLodUsageGenerated(DataStreamPtr& stream,
	        OgreMesh* pMesh, unsigned short lodNum, MeshLodUsage& usage)
		{
			usage.manualName = "";
			//usage.manualMesh.setNull();
	
			// Get one set of detail per SubMesh
			unsigned short numSubs, i;
			unsigned long streamID;
			numSubs = pMesh->mSubMeshList.size();
			for (i = 0; i < numSubs; ++i)
			{
				streamID = readChunk(stream);
				if (streamID != M_MESH_LOD_GENERATED)
				{
					OGRE_EXCEPT(0,
						"Missing M_MESH_LOD_GENERATED stream in " + pMesh->getName(),
						"ParseOgreImpl::readMeshLodUsageGenerated");
				}
	
				SubMesh* sm = pMesh->mSubMeshList[i];
				// lodNum - 1 because SubMesh doesn't store full detail LOD
	            //IndexData* indexData	= OGRE_NEW IndexData();
				//IndexData* indexData = 0;//sm->mLodFaceList[lodNum - 1];
	            // unsigned int numIndexes
	            unsigned int numIndexes;
				readInts(stream, &numIndexes, 1);
	            //indexData->resize( numIndexes/3);
	            // bool indexes32Bit
	            bool idx32Bit;
	            readBools(stream, &idx32Bit, 1);
	            // unsigned short*/int* faceIndexes;  ((v1, v2, v3) * numFaces)
	            if (idx32Bit)
	            {
	                //DWORD*	p	=	new	DWORD[indexData->indexCount];
					sm->m_lstFace32.resize(numIndexes/3);
				    readInts(stream, (UInt*)&sm->m_lstFace32[0].f0,numIndexes);
					//delete[] p;
	
	            }
	            else
	            {
					sm->m_lstFace16.resize(numIndexes/3);
					readShorts(stream, (U16*)&sm->m_lstFace16[0].f0,numIndexes);
					//delete[]	p;
	
	            }
	
			}
		}
	    //---------------------------------------------------------------------
	    void ParseOgreImpl::flipFromLittleEndian(void* pData, UInt vertexCount,
	        UInt vertexSize, const DeclareElementVector& elems)
		{
			if (mFlipEndian)
			{
		        flipEndian(pData, vertexCount, vertexSize, elems);
			}
	    }
	    //---------------------------------------------------------------------
	    void ParseOgreImpl::flipToLittleEndian(void* pData, UInt vertexCount,
				UInt vertexSize, const DeclareElementVector& elems)
		{
			if (mFlipEndian)
			{
		        flipEndian(pData, vertexCount, vertexSize, elems);
			}
		}
	    //---------------------------------------------------------------------
	    void ParseOgreImpl::flipEndian(void* pData, UInt vertexCount,
	        UInt vertexSize, const DeclareElementVector& elems)
		{
			void *pBase = pData;
			for (UInt v = 0; v < vertexCount; ++v)
			{
// 				VertexElementList::const_iterator ei, eiend;
// 				eiend = elems.end();
// 				for (ei = elems.begin(); ei != eiend; ++ei)
// 				{
					//void *pElem;
					// re-base pointer to the element
					//(*ei).baseVertexPointerToElement(pBase, &pElem);
					// Flip the endian based on the type
	//				UInt typeSize = 4;
	// 				switch (VertexElement::getBaseType((*ei).getType()))
	// 				{
	// 					case VET_FLOAT1:
	// 						typeSize = sizeof(float);
	// 						break;
	// 					case VET_SHORT1:
	// 						typeSize = sizeof(short);
	// 						break;
	// 					case VET_COLOUR:
	// 					case VET_COLOUR_ABGR:
	// 					case VET_COLOUR_ARGB:
	// 						typeSize = sizeof(DWORD);
	// 						break;
	// 					case VET_UBYTE4:
	// 						typeSize = 0; // NO FLIPPING
	// 						break;
	// 					default:
	// 						assert(false); // Should never happen
	// 				};
	//                  Parse::flipEndian(pElem, typeSize,
	// 					VertexElement::getTypeCount((*ei).getType()));
	
	//			}
	
				pBase = static_cast<void*>(
					static_cast<unsigned char*>(pBase) + vertexSize);
	
			}
		}
	
	
	    //---------------------------------------------------------------------
		void ParseOgreImpl::readEdgeList(DataStreamPtr& stream, OgreMesh* pMesh)
		{
	        unsigned short streamID;
	
	        if (!stream->eof())
	        {
	            streamID = readChunk(stream);
	            while(!stream->eof() &&
	                streamID == M_EDGE_LIST_LOD)
	            {
	                // Process single LOD
	
	                // unsigned short lodIndex
	                unsigned short lodIndex;
	                readShorts(stream, &lodIndex, 1);
	
	                // bool isManual			// If manual, no edge data here, loaded from manual mesh
	                bool isManual;
	                readBools(stream, &isManual, 1);
	                // Only load in non-manual levels; others will be connected up by OgreMesh on demand
	                if (!isManual)
	                {
	                    MeshLodUsage usage ;//const_cast<MeshLodUsage&>(pMesh->getLodLevel(lodIndex));
	
	                    usage.edgeData = 0;//OGRE_NEW EdgeData();
	
	                    // Read detail information of the edge list
	                    readEdgeListLodInfo(stream, usage.edgeData);
	
	                    // Postprocessing edge groups
	//                     EdgeData::EdgeGroupList::iterator egi, egend;
	//                     egend = usage.edgeData->edgeGroups.end();
	//                     for (egi = usage.edgeData->edgeGroups.begin(); egi != egend; ++egi)
	//                     {
	//                         EdgeData::EdgeGroup& edgeGroup = *egi;
	//                         // Populate edgeGroup.vertexData pointers
	//                         // If there is shared vertex data, vertexSet 0 is that,
	//                         // otherwise 0 is first dedicated
	//                         if (pMesh->sharedVertexData)
	//                         {
	//                             if (edgeGroup.vertexSet == 0)
	//                             {
	//                                 edgeGroup.vertexData = pMesh->sharedVertexData;
	//                             }
	//                             else
	//                             {
	//                                 edgeGroup.vertexData = pMesh->getSubMesh(
	//                                     edgeGroup.vertexSet-1)->vertexData;
	//                             }
	//                         }
	//                         else
	//                         {
	//                             edgeGroup.vertexData = pMesh->getSubMesh(
	//                                 edgeGroup.vertexSet)->vertexData;
	//                         }
	//                     }
	                }
	
	                if (!stream->eof())
	                {
	                    streamID = readChunk(stream);
	                }
	
	            }
	            if (!stream->eof())
	            {
	                // Backpedal back to start of stream
	                stream->skip(-STREAM_OVERHEAD_SIZE);
	            }
	        }
	
	        pMesh->mEdgeListsBuilt = true;
		}
		//---------------------------------------------------------------------
	    void ParseOgreImpl::readEdgeListLodInfo(DataStreamPtr& stream,
	        EdgeData* edgeData)
	    {
	        bool isClosed;
	        readBools(stream, &isClosed, 1);
	        // unsigned long numTriangles
	        UInt numTriangles;
	        readInts(stream, &numTriangles, 1);
	        // Allocate correct amount of memory
	//         edgeData->triangles.resize(numTriangles);
	//         edgeData->triangleFaceNormals.resize(numTriangles);
	//         edgeData->triangleLightFacings.resize(numTriangles);
	        // unsigned long numEdgeGroups
	        UInt numEdgeGroups;
	        readInts(stream, &numEdgeGroups, 1);
	        // Allocate correct amount of memory
	        //edgeData->edgeGroups.resize(numEdgeGroups);
	        // Triangle* triangleList
	        UInt tmp[3];
	        for (UInt t = 0; t < numTriangles; ++t)
	        {
	            //EdgeData::Triangle& tri = edgeData->triangles[t];
	            // unsigned long indexSet
	            readInts(stream, tmp, 1);
	            //tri.indexSet = tmp[0];
	            // unsigned long vertexSet
	            readInts(stream, tmp, 1);
	            //tri.vertexSet = tmp[0];
	            // unsigned long vertIndex[3]
	            readInts(stream, tmp, 3);
	//             tri.vertIndex[0] = tmp[0];
	//             tri.vertIndex[1] = tmp[1];
	//             tri.vertIndex[2] = tmp[2];
	            // unsigned long sharedVertIndex[3]
	//             readInts(stream, tmp, 3);
	//             tri.sharedVertIndex[0] = tmp[0];
	//             tri.sharedVertIndex[1] = tmp[1];
	//             tri.sharedVertIndex[2] = tmp[2];
	             float normal[4];
	            readFloats(stream, normal/*&(edgeData->triangleFaceNormals[t].x)*/, 4);
	
	        }
	
	        for (U32 eg = 0; eg < numEdgeGroups; ++eg)
	        {
	            unsigned short streamID = readChunk(stream);
	            if (streamID != M_EDGE_GROUP)
	            {
	                OGRE_EXCEPT(0,
	                    "Missing M_EDGE_GROUP stream",
	                    "ParseOgreImpl::readEdgeListLodInfo");
	            }
	            //EdgeData::EdgeGroup& edgeGroup = edgeData->edgeGroups[eg];
	
	            // unsigned long vertexSet
	            readInts(stream, tmp, 1);
	            //edgeGroup.vertexSet = tmp[0];
	            // unsigned long triStart
	            readInts(stream, tmp, 1);
	            //edgeGroup.triStart = tmp[0];
	            // unsigned long triCount
	            readInts(stream, tmp, 1);
	            //edgeGroup.triCount = tmp[0];
	            // unsigned long numEdges
	            UInt numEdges;
	            readInts(stream, &numEdges, 1);
	           // edgeGroup.edges.resize(numEdges);
	            // Edge* edgeList
	//             for (U32 e = 0; e < numEdges; ++e)
	//             {
	//                 //EdgeData::Edge& edge = edgeGroup.edges[e];
	//                 // unsigned long  triIndex[2]
	//                 readInts(stream, tmp, 2);
	//                 //edge.triIndex[0] = tmp[0];
	//                 //edge.triIndex[1] = tmp[1];
	//                 // unsigned long  vertIndex[2]
	//                 readInts(stream, tmp, 2);
	//                 //edge.vertIndex[0] = tmp[0];
	//                 //edge.vertIndex[1] = tmp[1];
	//                 // unsigned long  sharedVertIndex[2]
	//                 readInts(stream, tmp, 2);
	//                 //edge.sharedVertIndex[0] = tmp[0];
	//                 //edge.sharedVertIndex[1] = tmp[1];
	//                  bool degenerate;
	//                 readBools(stream, &(degenerate), 1);
	//             }
	        }
	    }
	
	
	
	
		//---------------------------------------------------------------------
		void ParseOgreImpl::readPoses(DataStreamPtr& stream, OgreMesh* pMesh)
		{
			unsigned short streamID;
	
			// Find all substreams
			if (!stream->eof())
			{
				streamID = readChunk(stream);
				while(!stream->eof() &&
					(streamID == M_POSE))
				{
					switch(streamID)
					{
					case M_POSE:
						readPose(stream, pMesh);
						break;
	
					}
	
					if (!stream->eof())
					{
						streamID = readChunk(stream);
					}
	
				}
				if (!stream->eof())
				{
					// Backpedal back to start of stream
					stream->skip(-STREAM_OVERHEAD_SIZE);
				}
			}
		}
		//---------------------------------------------------------------------
		void ParseOgreImpl::readPose(DataStreamPtr& stream, OgreMesh* pMesh)
		{
			// char* name (may be blank)
			AString name = readString(stream);
			// unsigned short target
			unsigned short target;
			readShorts(stream, &target, 1);
	
			Pose* pose = 0;//pMesh->createPose(target, name);
	
			// Find all substreams
			unsigned short streamID;
			if (!stream->eof())
			{
				streamID = readChunk(stream);
				while(!stream->eof() &&
					(streamID == M_POSE_VERTEX))
				{
					switch(streamID)
					{
					case M_POSE_VERTEX:
						// create vertex offset
						UInt vertIndex;
						Float3 offset;
						// unsigned long vertexIndex
						readInts(stream, &vertIndex, 1);
						// float xoffset, yoffset, zoffset
						readFloats(stream, &offset.x, 3);
	
						//pose->addVertex(vertIndex, offset);
						break;
	
					}
	
					if (!stream->eof())
					{
						streamID = readChunk(stream);
					}
	
				}
				if (!stream->eof())
				{
					// Backpedal back to start of stream
					stream->skip(-STREAM_OVERHEAD_SIZE);
				}
			}
	
		}
		//---------------------------------------------------------------------
		void ParseOgreImpl::readAnimations(DataStreamPtr& stream, OgreMesh* pMesh)
		{
			unsigned short streamID;
	
			// Find all substreams
			if (!stream->eof())
			{
				streamID = readChunk(stream);
				while(!stream->eof() &&
					(streamID == M_ANIMATION))
				{
					switch(streamID)
					{
					case M_ANIMATION:
						readAnimation(stream, pMesh);
						break;
	
					}
	
					if (!stream->eof())
					{
						streamID = readChunk(stream);
					}
	
				}
				if (!stream->eof())
				{
					// Backpedal back to start of stream
					stream->skip(-STREAM_OVERHEAD_SIZE);
				}
			}
	
	
		}
		//---------------------------------------------------------------------
		void ParseOgreImpl::readAnimation(DataStreamPtr& stream, OgreMesh* pMesh)
		{
	
			// char* name
			AString name = readString(stream);
			// float length
			float len;
			readFloats(stream, &len, 1);
	
			Anim* anim = NULL;//pMesh->createAnimation(name, len);
	
			// tracks
			unsigned short streamID;
	
			if (!stream->eof())
			{
				streamID = readChunk(stream);
				while(!stream->eof() &&
					streamID == M_ANIMATION_TRACK)
				{
					switch(streamID)
					{
					case M_ANIMATION_TRACK:
						readAnimationTrack(stream, anim, pMesh);
						break;
					};
					if (!stream->eof())
					{
						streamID = readChunk(stream);
					}
	
				}
				if (!stream->eof())
				{
					// Backpedal back to start of stream
					stream->skip(-STREAM_OVERHEAD_SIZE);
				}
			}
		}
		//---------------------------------------------------------------------
		void ParseOgreImpl::readAnimationTrack(DataStreamPtr& stream,
			Anim* anim, OgreMesh* pMesh)
		{
			// ushort type
			U16 inAnimType;
			readShorts(stream, &inAnimType, 1);
			//VertexAnimationType animType = (VertexAnimationType)inAnimType;
	
			// unsigned short target
			U16 target;
			readShorts(stream, &target, 1);
	
	// 		VertexAnimationTrack* track = anim->createVertexTrack(target,
	// 			pMesh->getVertexDataByTrackHandle(target), animType);
	
			// keyframes
			unsigned short streamID;
	
			if (!stream->eof())
			{
				streamID = readChunk(stream);
				while(!stream->eof() &&
					(streamID == M_ANIMATION_MORPH_KEYFRAME ||
					 streamID == M_ANIMATION_POSE_KEYFRAME))
				{
					switch(streamID)
					{
					case M_ANIMATION_MORPH_KEYFRAME:
						readMorphKeyFrame(stream, NULL);
						break;
					case M_ANIMATION_POSE_KEYFRAME:
						readPoseKeyFrame(stream, NULL);
						break;
					};
					if (!stream->eof())
					{
						streamID = readChunk(stream);
					}
	
				}
				if (!stream->eof())
				{
					// Backpedal back to start of stream
					stream->skip(-STREAM_OVERHEAD_SIZE);
				}
			}
	
		}
		//---------------------------------------------------------------------
		void ParseOgreImpl::readMorphKeyFrame(DataStreamPtr& stream, VertexAnimationTrack* track)
		{
			// float time
			float timePos;
			readFloats(stream, &timePos, 1);
	
			//VertexMorphKeyFrame* kf = track->createVertexMorphKeyFrame(timePos);
	
			// Create buffer, allow read and use shadow buffer
			UInt vertexCount = 0;//track->getAssociatedVertexData()->vertexCount;
			return;
	// 		HardwareVertexBuffSharedPtr vbuf =
	// 			HardwareBufferManager::getSingleton().createVertexBuff(
	// 				VertexElement::getTypeSize(VET_FLOAT3), vertexCount,
	// 				HardwareBuffer::HBU_STATIC, true);
	// 		// float x,y,z			// repeat by number of vertices in original geometry
	// 		float* pDst = static_cast<float*>(
	// 			vbuf->lock(HardwareBuffer::HBL_DISCARD));
			Float3* p	=	new	Float3[vertexCount];
			readFloats(stream, &p->x, vertexCount * 3);
			delete[] p;
	// 		vbuf->unlock();
	// 		kf->setVertexBuff(vbuf);
	
		}
		//---------------------------------------------------------------------
		void ParseOgreImpl::readPoseKeyFrame(DataStreamPtr& stream, VertexAnimationTrack* track)
		{
			// float time
			float timePos;
			readFloats(stream, &timePos, 1);
	
			// Create keyframe
			//VertexPoseKeyFrame* kf = track->createVertexPoseKeyFrame(timePos);
	
			unsigned short streamID;
	
			if (!stream->eof())
			{
				streamID = readChunk(stream);
				while(!stream->eof() &&
					streamID == M_ANIMATION_POSE_REF)
				{
					switch(streamID)
					{
					case M_ANIMATION_POSE_REF:
						U16 poseIndex;
						float influence;
						// unsigned short poseIndex
						readShorts(stream, &poseIndex, 1);
						// float influence
						readFloats(stream, &influence, 1);
	
						//kf->addPoseReference(poseIndex, influence);
	
						break;
					};
					if (!stream->eof())
					{
						streamID = readChunk(stream);
					}
	
				}
				if (!stream->eof())
				{
					// Backpedal back to start of stream
					stream->skip(-STREAM_OVERHEAD_SIZE);
				}
			}
	
		}
	    //---------------------------------------------------------------------
	    //---------------------------------------------------------------------
	    //---------------------------------------------------------------------
	    ParseOgreImpl_v1_3::ParseOgreImpl_v1_3()
	    {
	        // Version number
	        mVersion = "[MeshSerializer_v1.30]";
	    }
	    //---------------------------------------------------------------------
	    ParseOgreImpl_v1_3::~ParseOgreImpl_v1_3()
	    {
	    }
	    //---------------------------------------------------------------------
	    void ParseOgreImpl_v1_3::readEdgeListLodInfo(DataStreamPtr& stream,
	        EdgeData* edgeData)
	    {
	        // unsigned long numTriangles
	        UInt numTriangles;
	        readInts(stream, &numTriangles, 1);
	        // Allocate correct amount of memory
	//         edgeData->triangles.resize(numTriangles);
	//         edgeData->triangleFaceNormals.resize(numTriangles);
	//         edgeData->triangleLightFacings.resize(numTriangles);
	        // unsigned long numEdgeGroups
	        UInt numEdgeGroups;
	        readInts(stream, &numEdgeGroups, 1);
	        // Allocate correct amount of memory
	        //edgeData->edgeGroups.resize(numEdgeGroups);
	        // Triangle* triangleList
	        UInt tmp[3];
	        for (UInt t = 0; t < numTriangles; ++t)
	        {
	            //EdgeData::Triangle& tri = edgeData->triangles[t];
	            // unsigned long indexSet
	            readInts(stream, tmp, 1);
	            //tri.indexSet = tmp[0];
	            // unsigned long vertexSet
	            readInts(stream, tmp, 1);
	            //tri.vertexSet = tmp[0];
	            // unsigned long vertIndex[3]
	            readInts(stream, tmp, 3);
	            //tri.vertIndex[0] = tmp[0];
	            //tri.vertIndex[1] = tmp[1];
	           // tri.vertIndex[2] = tmp[2];
	            // unsigned long sharedVertIndex[3]
	            readInts(stream, tmp, 3);
	            //tri.sharedVertIndex[0] = tmp[0];
	            //tri.sharedVertIndex[1] = tmp[1];
	            //tri.sharedVertIndex[2] = tmp[2];
	             float normal[4];
	            readFloats(stream, (normal), 4);
	
	        }
	
	        // Assume the mesh is closed, it will update later
	        //edgeData->isClosed = true;
	
	        for (U32 eg = 0; eg < numEdgeGroups; ++eg)
	        {
	            unsigned short streamID = readChunk(stream);
	            if (streamID != M_EDGE_GROUP)
	            {
	                OGRE_EXCEPT(0,
	                    "Missing M_EDGE_GROUP stream",
	                    "ParseOgreImpl_v1_3::readEdgeListLodInfo");
	            }
	            //EdgeData::EdgeGroup& edgeGroup = edgeData->edgeGroups[eg];
	
	            // unsigned long vertexSet
	            readInts(stream, tmp, 1);
	            //edgeGroup.vertexSet = tmp[0];
	            // unsigned long numEdges
	            UInt numEdges;
	            readInts(stream, &numEdges, 1);
	            //edgeGroup.edges.resize(numEdges);
	            // Edge* edgeList
	            for (U32 e = 0; e < numEdges; ++e)
	            {
	                //EdgeData::Edge& edge = edgeGroup.edges[e];
	                // unsigned long  triIndex[2]
	                readInts(stream, tmp, 2);
	                //edge.triIndex[0] = tmp[0];
	                //edge.triIndex[1] = tmp[1];
	                // unsigned long  vertIndex[2]
	                readInts(stream, tmp, 2);
	                //edge.vertIndex[0] = tmp[0];
	                //edge.vertIndex[1] = tmp[1];
	                // unsigned long  sharedVertIndex[2]
	                readInts(stream, tmp, 2);
	               // edge.sharedVertIndex[0] = tmp[0];
	                //edge.sharedVertIndex[1] = tmp[1];
	                bool degenerate;
	                readBools(stream, &(degenerate), 1);
	
	                // The mesh is closed only if no degenerate edge here
	//                 if (edge.degenerate)
	//                 {
	//                     edgeData->isClosed = false;
	//                 }
	            }
	        }
	
	        reorganiseTriangles(edgeData);
	    }
	    //---------------------------------------------------------------------
	    void ParseOgreImpl_v1_3::reorganiseTriangles(EdgeData* edgeData)
	    {
	        
	    }
		//---------------------------------------------------------------------
		void ParseOgreImpl::readExtremes(DataStreamPtr& stream, OgreMesh *pMesh)
		{
			unsigned short idx;
			readShorts(stream, &idx, 1);
	
			SubMesh *sm = pMesh->mSubMeshList[idx];
	
			int n_floats = (mCurrentstreamLen - STREAM_OVERHEAD_SIZE -
							sizeof (unsigned short)) / sizeof (float);
	
	        assert ((n_floats % 3) == 0);
	
	        float *vert = OGRE_ALLOC_T(float, n_floats, 0);
			readFloats(stream, vert, n_floats);
	
	
	
	        OGRE_FREE(vert, 0);
		}
		//---------------------------------------------------------------------
	    //---------------------------------------------------------------------
	    //---------------------------------------------------------------------
	    ParseOgreImpl_v1_2::ParseOgreImpl_v1_2()
	    {
	        // Version number
	        mVersion = "[MeshSerializer_v1.20]";
	    }
	    //---------------------------------------------------------------------
	    ParseOgreImpl_v1_2::~ParseOgreImpl_v1_2()
	    {
	    }
	    //---------------------------------------------------------------------
	    void ParseOgreImpl_v1_2::readMesh(DataStreamPtr& stream, OgreMesh* pMesh, ParseOgreListener *listener)
	    {
	        ParseOgreImpl::readMesh(stream, pMesh, listener);
	        // Always automatically build edge lists for this version
	        pMesh->mAutoBuildEdgeLists = true;
	
	    }
	    //---------------------------------------------------------------------
	    void ParseOgreImpl_v1_2::readGeometry(DataStreamPtr& stream, OgreMesh* pMesh,
	        VertexData* dest)
	    {
	        unsigned short texCoordSet = 0;
	
	        unsigned short bindIdx = 0;
	
	        //dest->vertexStart = 0;
	
	        unsigned int vertexCount = 0;
	        readInts(stream, &vertexCount, 1);
	        dest->resize(vertexCount);//vertexCount = vertexCount;
	
	        // Vertex buffers
	
	        readGeometryPositions(bindIdx, stream, pMesh, dest);
	        ++bindIdx;
	
	        // Find optional geometry streams
	        if (!stream->eof())
	        {
	            unsigned short streamID = readChunk(stream);
	            while(!stream->eof() &&
	                (streamID == M_GEOMETRY_NORMALS ||
	                 streamID == M_GEOMETRY_COLOURS ||
	                 streamID == M_GEOMETRY_TEXCOORDS ))
	            {
	                switch (streamID)
	                {
	                case M_GEOMETRY_NORMALS:
	                    readGeometryNormals(bindIdx++, stream, pMesh, dest);
	                    break;
	                case M_GEOMETRY_COLOURS:
	                    readGeometryColours(bindIdx++, stream, pMesh, dest);
	                    break;
	                case M_GEOMETRY_TEXCOORDS:
	                    readGeometryTexCoords(bindIdx++, stream, pMesh, dest, texCoordSet++);
	                    break;
	                }
	                // Get next stream
	                if (!stream->eof())
	                {
	                    streamID = readChunk(stream);
	                }
	            }
	            if (!stream->eof())
	            {
	                // Backpedal back to start of non-submesh stream
	                stream->skip(-STREAM_OVERHEAD_SIZE);
	            }
	        }
	    }
	    //---------------------------------------------------------------------
	    void ParseOgreImpl_v1_2::readGeometryPositions(unsigned short bindIdx,
	        DataStreamPtr& stream, OgreMesh* pMesh, VertexData* dest)
	    {
	        float *pFloat = new	float[dest->size()*3];
	        readFloats(stream, pFloat, dest->size() * 3);
			VertexData&	data	=	*dest;
			for(UInt i=0;i<dest->size();i++){
				data[i].Position.x	=	pFloat[i*3];
				data[i].Position.y	=	pFloat[i*3+1];
				data[i].Position.z	=	pFloat[i*3+2];
	
			}
			delete[] pFloat;
	    }
	    //---------------------------------------------------------------------
	    void ParseOgreImpl_v1_2::readGeometryNormals(unsigned short bindIdx,
	        DataStreamPtr& stream, OgreMesh* pMesh, VertexData* dest)
	    {
			float *pFloat = new	float[dest->size()*3];
			readFloats(stream, pFloat, dest->size() * 3);
			VertexData&	data	=	*dest;
			for(UInt i=0;i<dest->size();i++){
				data[i].Normal.x	=	pFloat[i*3];
				data[i].Normal.y	=	pFloat[i*3+1];
				data[i].Normal.z	=	pFloat[i*3+2];
	
			}
			delete[] pFloat;
	    }
	    //---------------------------------------------------------------------
	    void ParseOgreImpl_v1_2::readGeometryColours(unsigned short bindIdx,
	        DataStreamPtr& stream, OgreMesh* pMesh, VertexData* dest)
	    {
	        UInt *p = new	UInt[dest->size()];
	        readInts(stream, p, dest->size());
	        delete[] p;
	    }
	    //---------------------------------------------------------------------
	    void ParseOgreImpl_v1_2::readGeometryTexCoords(unsigned short bindIdx,
	        DataStreamPtr& stream, OgreMesh* pMesh, VertexData* dest, unsigned short texCoordSet)
	    {
	        float *pFloat = 0;
	        // unsigned short dimensions    (1 for 1D, 2 for 2D, 3 for 3D)
	        unsigned short dim;
	        readShorts(stream, &dim, 1);
	
			float *p	=	new	float[dest->size() * dim];
	        
	        readFloats(stream, p, dest->size() * dim);
			VertexData&	data	=	*dest;
			for(UInt i=0;i<dest->size();i++){
				data[i].UV.x	=	pFloat[i*dim];
				if(dim==2)
					data[i].UV.y	=	pFloat[i*dim+1];
				//data[i].Normal.z	=	pFloat[i*dim+2];
	
			}
			delete[] p;
	
	
	//         vbuf->unlock();
	//         dest->VertexBuffBinding->setBinding(bindIdx, vbuf);
	    }
	    //---------------------------------------------------------------------
	    //---------------------------------------------------------------------
	    //---------------------------------------------------------------------
	    ParseOgreImpl_v1_1::ParseOgreImpl_v1_1()
	    {
	        // Version number
	        mVersion = "[MeshSerializer_v1.10]";
	    }
	    //---------------------------------------------------------------------
	    ParseOgreImpl_v1_1::~ParseOgreImpl_v1_1()
	    {
	    }
	    //---------------------------------------------------------------------
	    void ParseOgreImpl_v1_1::readGeometryTexCoords(unsigned short bindIdx,
	        DataStreamPtr& stream, OgreMesh* pMesh, VertexData* dest, unsigned short texCoordSet)
	    {
	        
	        //HardwareVertexBuffSharedPtr vbuf;
	        // unsigned short dimensions    (1 for 1D, 2 for 2D, 3 for 3D)
	        unsigned short dim;
	        readShorts(stream, &dim, 1);
	        // float* pTexCoords  (u [v] [w] order, dimensions x numVertices)
			VertexData&	data	=	*dest;
	        float *p	=	new	float[dest->size() * dim];
			float *pFloat = p;
	        readFloats(stream, p, dest->size() * dim);
	
	        // Adjust individual v values to (1 - v)
	        if (dim == 2)
	        {
	            for (UInt i = 0; i < dest->size(); ++i)
	            {
	                ++pFloat; // skip u
	                *pFloat = 1.0 - *pFloat; // v = 1 - v
	                ++pFloat;
	            }
	
	
	        }
			for (UInt i = 0; i < dest->size(); ++i){
				data[i].UV.x	=	p[i*dim];
				if(dim==2)
					data[i].UV.y	=	p[i*dim+1];
			}
			delete[] p;
	    }
	}
	
};
