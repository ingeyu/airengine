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

#ifndef __ParseOgreImpl_H__
#define __ParseOgreImpl_H__

// #include "OgrePrerequisites.h"
// #include "OgreString.h"
// #include "OgreSerializer.h"
// #include "OgreMaterial.h"
// #include "OgreMesh.h"
// #include "OgreEdgeListBuilder.h"
#include "AirEngine.h"

#include "AirEngineHeader.h"
#include "AirEngineMesh.h"
#include "AirEngineParse.h"
#include "AirRenderVertexDeclare.h"
namespace Air{
	
	namespace Client {
	
		/** Definition of the OGRE .mesh file format 
	
		.mesh files are binary files (for read efficiency at runtime) and are arranged into chunks 
		of data, very like 3D Studio's format.
		A chunk always consists of:
		unsigned short CHUNK_ID        : one of the following chunk ids identifying the chunk
		unsigned long  LENGTH          : length of the chunk in bytes, including this header
		void*          DATA            : the data, which may contain other sub-chunks (various data types)
	
		A .mesh file can contain both the definition of the OgreMesh itself, and optionally the definitions
		of the materials is uses (although these can be omitted, if so the OgreMesh assumes that at runtime the
		Materials referred to by name in the OgreMesh are loaded/created from another source)
	
		A .mesh file only contains a single mesh, which can itself have multiple submeshes.
	
		*/
	
		enum MeshChunkID {
			M_HEADER                = 0x1000,
			// char*          version           : Version number check
			M_MESH                = 0x3000,
			// bool skeletallyAnimated   // important flag which affects h/w buffer policies
			// Optional M_GEOMETRY chunk
			M_SUBMESH             = 0x4000, 
			// char* materialName
			// bool useSharedVertices
			// unsigned int indexCount
			// bool indexes32Bit
			// unsigned int* faceVertexIndices (indexCount)
			// OR
			// unsigned short* faceVertexIndices (indexCount)
			// M_GEOMETRY chunk (Optional: present only if useSharedVertices = false)
			M_SUBMESH_OPERATION = 0x4010, // optional, trilist assumed if missing
			// unsigned short operationType
			M_SUBMESH_BONE_ASSIGNMENT = 0x4100,
			// Optional bone weights (repeating section)
			// unsigned int vertexIndex;
			// unsigned short boneIndex;
			// float weight;
			// Optional chunk that matches a texture name to an alias
			// a texture alias is sent to the submesh material to use this texture name
			// instead of the one in the texture unit with a matching alias name
			M_SUBMESH_TEXTURE_ALIAS = 0x4200, // Repeating section
			// char* aliasName;
			// char* textureName;
	
			M_GEOMETRY          = 0x5000, // NB this chunk is embedded within M_MESH and M_SUBMESH
			// unsigned int vertexCount
			M_GEOMETRY_VERTEX_DECLARATION = 0x5100,
			M_GEOMETRY_VERTEX_ELEMENT = 0x5110, // Repeating section
			// unsigned short source;  	// buffer bind source
			// unsigned short type;    	// VertexElementType
			// unsigned short semantic; // VertexElementSemantic
			// unsigned short offset;	// start offset in buffer in bytes
			// unsigned short index;	// index of the semantic (for colours and texture coords)
			M_GEOMETRY_VERTEX_BUFFER = 0x5200, // Repeating section
			// unsigned short bindIndex;	// Index to bind this buffer to
			// unsigned short vertexSize;	// Per-vertex size, must agree with declaration at this index
			M_GEOMETRY_VERTEX_BUFFER_DATA = 0x5210,
			// raw buffer data
			M_MESH_SKELETON_LINK = 0x6000,
			// Optional link to skeleton
			// char* skeletonName           : name of .skeleton to use
			M_MESH_BONE_ASSIGNMENT = 0x7000,
			// Optional bone weights (repeating section)
			// unsigned int vertexIndex;
			// unsigned short boneIndex;
			// float weight;
			M_MESH_LOD = 0x8000,
			// Optional LOD information
			// unsigned short numLevels;
			// bool manual;  (true for manual alternate meshes, false for generated)
			M_MESH_LOD_USAGE = 0x8100,
			// Repeating section, ordered in increasing depth
			// NB LOD 0 (full detail from 0 depth) is omitted
			// float fromSquaredDepth;
			M_MESH_LOD_MANUAL = 0x8110,
			// Required if M_MESH_LOD section manual = true
			// String manualMeshName;
			M_MESH_LOD_GENERATED = 0x8120,
			// Required if M_MESH_LOD section manual = false
			// Repeating section (1 per submesh)
			// unsigned int indexCount;
			// bool indexes32Bit
			// unsigned short* faceIndexes;  (indexCount)
			// OR
			// unsigned int* faceIndexes;  (indexCount)
			M_MESH_BOUNDS = 0x9000,
			// float minx, miny, minz
			// float maxx, maxy, maxz
			// float radius
	
			// Added By DrEvil
			// optional chunk that contains a table of submesh indexes and the names of
			// the sub-meshes.
			M_SUBMESH_NAME_TABLE = 0xA000,
			// Subchunks of the name table. Each chunk contains an index & string
			M_SUBMESH_NAME_TABLE_ELEMENT = 0xA100,
			// short index
			// char* name
	
			// Optional chunk which stores precomputed edge data					 
			M_EDGE_LISTS = 0xB000,
			// Each LOD has a separate edge list
			M_EDGE_LIST_LOD = 0xB100,
			// unsigned short lodIndex
			// bool isManual			// If manual, no edge data here, loaded from manual mesh
			// bool isClosed
			// unsigned long numTriangles
			// unsigned long numEdgeGroups
			// Triangle* triangleList
			// unsigned long indexSet
			// unsigned long vertexSet
			// unsigned long vertIndex[3]
			// unsigned long sharedVertIndex[3] 
			// float normal[4] 
	
			M_EDGE_GROUP = 0xB110,
			// unsigned long vertexSet
			// unsigned long triStart
			// unsigned long triCount
			// unsigned long numEdges
			// Edge* edgeList
			// unsigned long  triIndex[2]
			// unsigned long  vertIndex[2]
			// unsigned long  sharedVertIndex[2]
			// bool degenerate
	
			// Optional poses section, referred to by pose keyframes
			M_POSES = 0xC000,
			M_POSE = 0xC100,
			// char* name (may be blank)
			// unsigned short target	// 0 for shared geometry, 
			// 1+ for submesh index + 1
			M_POSE_VERTEX = 0xC111,
			// unsigned long vertexIndex
			// float xoffset, yoffset, zoffset
			// Optional vertex animation chunk
			M_ANIMATIONS = 0xD000, 
			M_ANIMATION = 0xD100,
			// char* name
			// float length
			M_ANIMATION_TRACK = 0xD110,
			// unsigned short type			// 1 == morph, 2 == pose
			// unsigned short target		// 0 for shared geometry, 
			// 1+ for submesh index + 1
			M_ANIMATION_MORPH_KEYFRAME = 0xD111,
			// float time
			// float x,y,z			// repeat by number of vertices in original geometry
			M_ANIMATION_POSE_KEYFRAME = 0xD112,
			// float time
			M_ANIMATION_POSE_REF = 0xD113, // repeat for number of referenced poses
			// unsigned short poseIndex 
			// float influence
	
			// Optional submesh extreme vertex list chink
			M_TABLE_EXTREMES = 0xE000,
			// unsigned short submesh_index;
			// float extremes [n_extremes][3];
	
			/* Version 1.2 of the .mesh format (deprecated)
			enum MeshChunkID {
			M_HEADER                = 0x1000,
			// char*          version           : Version number check
			M_MESH                = 0x3000,
			// bool skeletallyAnimated   // important flag which affects h/w buffer policies
			// Optional M_GEOMETRY chunk
			M_SUBMESH             = 0x4000, 
			// char* materialName
			// bool useSharedVertices
			// unsigned int indexCount
			// bool indexes32Bit
			// unsigned int* faceVertexIndices (indexCount)
			// OR
			// unsigned short* faceVertexIndices (indexCount)
			// M_GEOMETRY chunk (Optional: present only if useSharedVertices = false)
			M_SUBMESH_OPERATION = 0x4010, // optional, trilist assumed if missing
			// unsigned short operationType
			M_SUBMESH_BONE_ASSIGNMENT = 0x4100,
			// Optional bone weights (repeating section)
			// unsigned int vertexIndex;
			// unsigned short boneIndex;
			// float weight;
			M_GEOMETRY          = 0x5000, // NB this chunk is embedded within M_MESH and M_SUBMESH
			*/
			// unsigned int vertexCount
			// float* pVertices (x, y, z order x numVertices)
			M_GEOMETRY_NORMALS = 0x5100,    //(Optional)
			// float* pNormals (x, y, z order x numVertices)
			M_GEOMETRY_COLOURS = 0x5200,    //(Optional)
			// unsigned long* pColours (RGBA 8888 format x numVertices)
			M_GEOMETRY_TEXCOORDS = 0x5300,    //(Optional, REPEATABLE, each one adds an extra set)
			// unsigned short dimensions    (1 for 1D, 2 for 2D, 3 for 3D)
			// float* pTexCoords  (u [v] [w] order, dimensions x numVertices)
			/*
			M_MESH_SKELETON_LINK = 0x6000,
			// Optional link to skeleton
			// char* skeletonName           : name of .skeleton to use
			M_MESH_BONE_ASSIGNMENT = 0x7000,
			// Optional bone weights (repeating section)
			// unsigned int vertexIndex;
			// unsigned short boneIndex;
			// float weight;
			M_MESH_LOD = 0x8000,
			// Optional LOD information
			// unsigned short numLevels;
			// bool manual;  (true for manual alternate meshes, false for generated)
			M_MESH_LOD_USAGE = 0x8100,
			// Repeating section, ordered in increasing depth
			// NB LOD 0 (full detail from 0 depth) is omitted
			// float fromSquaredDepth;
			M_MESH_LOD_MANUAL = 0x8110,
			// Required if M_MESH_LOD section manual = true
			// String manualMeshName;
			M_MESH_LOD_GENERATED = 0x8120,
			// Required if M_MESH_LOD section manual = false
			// Repeating section (1 per submesh)
			// unsigned int indexCount;
			// bool indexes32Bit
			// unsigned short* faceIndexes;  (indexCount)
			// OR
			// unsigned int* faceIndexes;  (indexCount)
			M_MESH_BOUNDS = 0x9000
			// float minx, miny, minz
			// float maxx, maxy, maxz
			// float radius
	
			// Added By DrEvil
			// optional chunk that contains a table of submesh indexes and the names of
			// the sub-meshes.
			M_SUBMESH_NAME_TABLE,
			// Subchunks of the name table. Each chunk contains an index & string
			M_SUBMESH_NAME_TABLE_ELEMENT,
			// short index
			// char* name
	
			*/
		};
		
		class ParseOgreListener;
	
		typedef	void						VertexAnimationTrack;
		typedef	void						VertexMorphKeyFrame;
		typedef	void						EdgeData;
		typedef	void						Pose;
		typedef	void						VertexPoseKeyFrame;
	
		typedef	void*						MaterialPtr;
		//typedef	U8*							DataStreamPtr;
		//typedef	UInt						MeshLodUsage;
	
		typedef	UInt						EdgeGroup;
	
		typedef	void						Anim;
	

		class	Mesh;
		class	OgreMesh;
		//typedef	Mesh											SubMesh;
		typedef	std::vector<Mesh::Vertex>						VertexData;
		typedef	std::vector<Mesh::Face32>						IndexData;
		typedef	std::vector<Mesh::Face16>						IndexData16;
		class	SubMesh{
		public:
			VertexData	m_lstVertex;
			IndexData	m_lstFace32;
			IndexData16	m_lstFace16;
		};
		struct	MeshLodUsage;
	
		typedef	UInt						VertexElementType;
		typedef	UInt						VertexElementSemantic;
		
	
	    /** Internal implementation of OgreMesh reading / writing for the latest version of the
	    .mesh format.
	    @remarks
	    In order to maintain compatibility with older versions of the .mesh format, there
	    will be alternative subclasses of this class to load older versions, whilst this class
	    will remain to load the latest version.
	    */
		class ENGINE_EXPORT ParseOgreImpl	:	public	Parse
	    {
	    public:
	        ParseOgreImpl();
	        virtual ~ParseOgreImpl();
	        /** Exports a mesh to the file specified. 
	        @remarks
	        This method takes an externally created OgreMesh object, and exports both it
	        and optionally the Materials it uses to a .mesh file.
	        @param pMesh Pointer to the OgreMesh to export
	        @param filename The destination filename
			@param endianMode The endian mode for the written file
	        */
	        void exportMesh(const OgreMesh* pMesh, const AString& filename,
				UInt endianMode = 0);
	
	        /** Imports OgreMesh and (optionally) Material data from a .mesh file DataStream.
	        @remarks
	        This method imports data from a DataStream opened from a .mesh file and places it's
	        contents into the OgreMesh object which is passed in. 
	        @param stream The DataStream holding the .mesh data. Must be initialised (pos at the start of the buffer).
	        @param pDest Pointer to the OgreMesh object which will receive the data. Should be blank already.
	        */
			void importMesh(DataStreamPtr& stream, OgreMesh* pDest, ParseOgreListener *listener);
	
	    protected:
	
	        virtual void readTextureLayer(DataStreamPtr& stream, OgreMesh* pMesh, MaterialPtr& pMat);
	        virtual void readSubMeshNameTable(DataStreamPtr& stream, OgreMesh* pMesh);
	        virtual void readMesh(DataStreamPtr& stream, OgreMesh* pMesh, ParseOgreListener *listener);
	        virtual void readSubMesh(DataStreamPtr& stream, OgreMesh* pMesh, ParseOgreListener *listener);
	        virtual void readSubMeshOperation(DataStreamPtr& stream, OgreMesh* pMesh, SubMesh* sub);
	        virtual void readSubMeshTextureAlias(DataStreamPtr& stream, OgreMesh* pMesh, SubMesh* sub);
	        virtual void readGeometry(DataStreamPtr& stream, OgreMesh* pMesh, VertexData* dest);
	        virtual void readGeometryVertexDeclaration(DataStreamPtr& stream, OgreMesh* pMesh, VertexData* dest);
	        virtual void readGeometryVertexElement(DataStreamPtr& stream, OgreMesh* pMesh, VertexData* dest);
	        virtual void readGeometryVertexBuff(DataStreamPtr& stream, OgreMesh* pMesh, VertexData* dest);
	
	        virtual void readSkeletonLink(DataStreamPtr& stream, OgreMesh* pMesh, ParseOgreListener *listener);
	        virtual void readMeshBoneAssignment(DataStreamPtr& stream, OgreMesh* pMesh);
	        virtual void readSubMeshBoneAssignment(DataStreamPtr& stream, OgreMesh* pMesh, 
	            SubMesh* sub);
	        virtual void readMeshLodInfo(DataStreamPtr& stream, OgreMesh* pMesh);
	        virtual void readMeshLodUsageManual(DataStreamPtr& stream, OgreMesh* pMesh, 
	            unsigned short lodNum, MeshLodUsage& usage);
	        virtual void readMeshLodUsageGenerated(DataStreamPtr& stream, OgreMesh* pMesh, 
	            unsigned short lodNum, MeshLodUsage& usage);
	        virtual void readBoundsInfo(DataStreamPtr& stream, OgreMesh* pMesh);
	        virtual void readEdgeList(DataStreamPtr& stream, OgreMesh* pMesh);
	        virtual void readEdgeListLodInfo(DataStreamPtr& stream, EdgeData* edgeData);
			virtual void readPoses(DataStreamPtr& stream, OgreMesh* pMesh);
			virtual void readPose(DataStreamPtr& stream, OgreMesh* pMesh);
			virtual void readAnimations(DataStreamPtr& stream, OgreMesh* pMesh);
			virtual void readAnimation(DataStreamPtr& stream, OgreMesh* pMesh);
			virtual void readAnimationTrack(DataStreamPtr& stream, Anim* anim, 
				OgreMesh* pMesh);
			virtual void readMorphKeyFrame(DataStreamPtr& stream, VertexAnimationTrack* track);
			virtual void readPoseKeyFrame(DataStreamPtr& stream, VertexAnimationTrack* track);
			virtual void readExtremes(DataStreamPtr& stream, OgreMesh *pMesh);
	
	
	        /// Flip an entire vertex buffer from little endian
	        virtual void flipFromLittleEndian(void* pData, UInt vertexCount, UInt vertexSize, const DeclareElementVector& elems);
	        /// Flip an entire vertex buffer to little endian
	        virtual void flipToLittleEndian(void* pData, UInt vertexCount, UInt vertexSize, const DeclareElementVector& elems);
	        /// Flip the endianness of an entire vertex buffer, passed in as a 
	        /// pointer to locked or temporary memory 
	        virtual void flipEndian(void* pData, UInt vertexCount, UInt vertexSize, const DeclareElementVector& elems);
	
	
			AString	mVersion;
	    };
	
	    /** Class for providing backwards-compatibility for loading version 1.3 of the .mesh format. */
	    class ENGINE_EXPORT ParseOgreImpl_v1_3 : public ParseOgreImpl
	    {
	    public:
	        ParseOgreImpl_v1_3();
	        ~ParseOgreImpl_v1_3();
	    protected:
	        virtual void readEdgeListLodInfo(DataStreamPtr& stream, EdgeData* edgeData);
	
	        /// Reorganise triangles of the edge list to group by vertex set
	        virtual void reorganiseTriangles(EdgeData* edgeData);
	    };
	
	    /** Class for providing backwards-compatibility for loading version 1.2 of the .mesh format. */
	    class ENGINE_EXPORT ParseOgreImpl_v1_2 : public ParseOgreImpl_v1_3
	    {
	    public:
	        ParseOgreImpl_v1_2();
	        ~ParseOgreImpl_v1_2();
	    protected:
	        virtual void readMesh(DataStreamPtr& stream, OgreMesh* pMesh, ParseOgreListener *listener);
	        virtual void readGeometry(DataStreamPtr& stream, OgreMesh* pMesh, VertexData* dest);
	        virtual void readGeometryPositions(unsigned short bindIdx, DataStreamPtr& stream, 
	            OgreMesh* pMesh, VertexData* dest);
	        virtual void readGeometryNormals(unsigned short bindIdx, DataStreamPtr& stream, 
	            OgreMesh* pMesh, VertexData* dest);
	        virtual void readGeometryColours(unsigned short bindIdx, DataStreamPtr& stream, 
	            OgreMesh* pMesh, VertexData* dest);
	        virtual void readGeometryTexCoords(unsigned short bindIdx, DataStreamPtr& stream, 
	            OgreMesh* pMesh, VertexData* dest, unsigned short set);
	    };
	
	    /** Class for providing backwards-compatibility for loading version 1.1 of the .mesh format. */
	    class ENGINE_EXPORT ParseOgreImpl_v1_1 : public ParseOgreImpl_v1_2
	    {
	    public:
	        ParseOgreImpl_v1_1();
	        ~ParseOgreImpl_v1_1();
	    protected:
	        void readGeometryTexCoords(unsigned short bindIdx, DataStreamPtr& stream, 
	            OgreMesh* pMesh, VertexData* dest, unsigned short set);
	    };
	
	
	}
};


#endif
