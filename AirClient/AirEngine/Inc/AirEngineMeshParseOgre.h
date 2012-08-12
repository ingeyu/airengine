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

#ifndef __ParseOgre_H__
#define __ParseOgre_H__

#include "AirEngine.h"
#include "AirEngineHeader.h"
#include "AirEngineMeshParseOgreImpl.h"
#include "AirCommonFile.h"
////#include "Bound.h"
#include "AirEngineParse.h"
namespace Air{
	
	namespace Client {
		
		class ParseOgreListener;
		class OgreMesh;
		//typedef	Render::Vertex::IDeclare::Element	VertexElement;
	
	
		class ENGINE_EXPORT OgreMesh//: public Resource
		{
			friend class SubMesh;
			friend class ParseOgreImpl;
			friend class ParseOgreImpl_v1_2;
			friend class ParseOgreImpl_v1_1;
	
		public:
			typedef std::vector<Real> LodDistanceList;
			/// Multimap of vertex bone assignments (orders by vertex index)
			typedef std::multimap<UInt, UInt> VertexBoneAssignmentList;
			typedef VertexBoneAssignmentList::iterator BoneAssignmentIterator;
			typedef std::vector<SubMesh*> SubMeshList;
			typedef std::vector<unsigned short> IndexMap;
	
			~OgreMesh(){
				UInt uiSize	=	mSubMeshList.size();
				for(UInt i=0;i<uiSize;i++){
					SubMesh*	p	=	mSubMeshList[i];
					delete p;
				}
				mSubMeshList.clear();
			}
	
	
	
			/** A list of submeshes which make up this mesh.
			Each mesh is made up of 1 or more submeshes, which
			are each based on a single material and can have their
			own vertex data (they may not - they can share vertex data
			from the OgreMesh, depending on preference).
			*/
			SubMeshList mSubMeshList;
	
		public:
			/** A hashmap used to store optional SubMesh names.
			Translates a name into SubMesh index
			*/
			typedef stdext::hash_map<AString, U16> SubMeshNameMap ;
	
	
		protected:
	
			DataStreamPtr mFreshFromDisk;
	
			SubMeshNameMap mSubMeshNameMap ;
			/// Local bounding box volume
			BoundBox mAABB;
			/// Local bounding sphere radius (centered on object)
			Real mBoundRadius;
	
			/// Optional linked skeleton
			AString mSkeletonName;
			UInt mSkeleton;
	
	
			VertexBoneAssignmentList mBoneAssignments;
	
			/// Flag indicating that bone assignments need to be recompiled
			bool mBoneAssignmentsOutOfDate;
	
	
	
			bool mIsLodManual;
			U16 mNumLods;
			typedef std::vector<MeshLodUsage> MeshLodUsageList;
			MeshLodUsageList mMeshLodUsageList;
	
			UInt mVertexBuffUsage;
			UInt mIndexBuffUsage;
			bool mVertexBuffShadowBuffer;
			bool mIndexBuffShadowBuffer;
	
	
			bool mPreparedForShadowVolumes;
			bool mEdgeListsBuilt;
			bool mAutoBuildEdgeLists;
	
			/// Storage of morph animations, lookup by name
			typedef std::map<AString, Anim*> AnimationList;
			AnimationList mAnimationsList;
			/// The vertex animation type associated with the shared vertex data
			mutable UInt mSharedVertexDataAnimationType;
			/// Do we need to scan animations for animation types?
			mutable bool mAnimationTypesDirty;
	
			/// List of available poses for shared and dedicated geometryPoseList
			UInt mPoseList;
		public:
			VertexData *sharedVertexData;
			IndexMap sharedBlendIndexToBoneIndexMap;
	
	
		};
	
	// 	class ENGINE_EXPORT MeshPtr : public SharedPtr<OgreMesh> 
	// 	{
	// 	public:
	// 		MeshPtr() : SharedPtr<OgreMesh>() {}
	// 		explicit MeshPtr(OgreMesh* rep) : SharedPtr<OgreMesh>(rep) {}
	// 		MeshPtr(const MeshPtr& r) : SharedPtr<OgreMesh>(r) {} 
	// 		MeshPtr(const ResourcePtr& r);
	// 		/// Operator used to convert a ResourcePtr to a MeshPtr
	// 		MeshPtr& operator=(const ResourcePtr& r);
	// 	protected:
	// 		/// Override destroy since we need to delete OgreMesh after fully defined
	// 		void destroy(void);
	// 	};
	
		/** A way of recording the way each LODs is recorded this OgreMesh. */
		struct MeshLodUsage
		{
			/// squared Z value from which this LOD will apply
			Real fromDepthSquared;
			/// Only relevant if mIsLodManual is true, the name of the alternative mesh to use
			AString manualName;
			/// Hard link to mesh to avoid looking up each time
			mutable SharedPtr<OgreMesh> manualMesh;
			/// Edge list for this LOD level (may be derived from manual mesh)
			mutable EdgeData* edgeData;
		};
		class ENGINE_EXPORT ParseOgre	:	public	Parse
	    {
	    public:
	        ParseOgre();
	        virtual ~ParseOgre();
	
			
	
	
	        /** Exports a mesh to the file specified. 
	        @remarks
	            This method takes an externally created OgreMesh object, and exports both it
	            and optionally the Materials it uses to a .mesh file.
	        @param pMesh Pointer to the OgreMesh to export
	        @param filename The destination filename
			@param endianMode The endian mode of the written file
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
			void importMesh(DataStreamPtr& stream, OgreMesh* pDest);
	
			/// Sets the listener for this serializer
			void setListener(ParseOgreListener *listener);
			/// Returns the current listener
			ParseOgreListener *getListener();
	    protected:
	        static AString msCurrentVersion;
	
	        typedef std::map<AString, ParseOgreImpl* > ParseOgreImplMap;
	        ParseOgreImplMap mImplementations;
	
			ParseOgreListener *mListener;
	
	    };
	
		/** 
		 @remarks
			This class allows users to hook into the mesh loading process and
			modify references within the mesh as they are loading. Material and
			skeletal references can be processed using this interface which allows
			finer control over resources.
		*/
		class ParseOgreListener
		{
		public:
			virtual ~ParseOgreListener() {}
			/// Called to override the loading of the given named material
			virtual void processMaterialName(OgreMesh *mesh, AString *name) = 0;
			/// Called to override the reference to a skeleton
			virtual void processSkeletonName(OgreMesh *mesh, AString *name) = 0;
		};
		template	<typename	T_Type>
		void	Read(T_Type	pReturn,UInt uiSize,UInt uiCount,U8*	pData,UInt& uiPos)	\
		{
			memcpy(pReturn,pData,uiSize*uiCount);
			pData+=uiSize*uiCount;
			uiPos+=uiSize*uiCount;
		}
	
		inline	void	ReadStr(U8*	pData,S8*	pString,UInt&	uiPos)
		{
			int i=0;
			do{
				Read(&pString[i++], 1, 1, pData,uiPos);
			}while(*pData != '\0' && i<255);
			pData++;uiPos++;pString[i]='\0';
		}
	}
};



#endif
