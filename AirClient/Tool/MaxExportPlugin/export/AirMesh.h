#ifndef AirMesh_h__
#define AirMesh_h__

class IGameNode;

namespace	Air{
	enum DECLUSAGE
	{
		DECLUSAGE_POSITION = 0,
		DECLUSAGE_BLENDWEIGHT,   // 1
		DECLUSAGE_BLENDINDICES,  // 2
		DECLUSAGE_NORMAL,        // 3
		DECLUSAGE_PSIZE,         // 4
		DECLUSAGE_TEXCOORD,      // 5
		DECLUSAGE_TANGENT,       // 6
		DECLUSAGE_BINORMAL,      // 7
		DECLUSAGE_TESSFACTOR,    // 8
		DECLUSAGE_POSITIONT,     // 9
		DECLUSAGE_COLOR,         // 10
		DECLUSAGE_FOG,           // 11
		DECLUSAGE_DEPTH,         // 12
		DECLUSAGE_SAMPLE,        // 13
	};
	enum DECLMETHOD
	{
		DECLMETHOD_DEFAULT = 0,
		DECLMETHOD_PARTIALU,
		DECLMETHOD_PARTIALV,
		DECLMETHOD_CROSSUV,    // Normal
		DECLMETHOD_UV,
		DECLMETHOD_LOOKUP,               // Lookup a displacement map
		DECLMETHOD_LOOKUPPRESAMPLED,     // Lookup a pre-sampled displacement map
	};
	enum DECLTYPE
	{
		DECLTYPE_FLOAT1    =  0,  // 1D float expanded to (value, 0., 0., 1.)
		DECLTYPE_FLOAT2    =  1,  // 2D float expanded to (value, value, 0., 1.)
		DECLTYPE_FLOAT3    =  2,  // 3D float expanded to (value, value, value, 1.)
		DECLTYPE_FLOAT4    =  3,  // 4D float
		DECLTYPE_D3DCOLOR  =  4,  // 4D packed unsigned bytes mapped to 0. to 1. range
		// Input is in D3DCOLOR format (ARGB) expanded to (R, G, B, A)
		DECLTYPE_UBYTE4    =  5,  // 4D unsigned byte
		DECLTYPE_SHORT2    =  6,  // 2D signed short expanded to (value, value, 0., 1.)
		DECLTYPE_SHORT4    =  7,  // 4D signed short
	
		// The following types are valid only with vertex shaders >= 2.0
	
	
		DECLTYPE_UBYTE4N   =  8,  // Each of 4 bytes is normalized by dividing to 255.0
		DECLTYPE_SHORT2N   =  9,  // 2D signed short normalized (v[0]/32767.0,v[1]/32767.0,0,1)
		DECLTYPE_SHORT4N   = 10,  // 4D signed short normalized (v[0]/32767.0,v[1]/32767.0,v[2]/32767.0,v[3]/32767.0)
		DECLTYPE_USHORT2N  = 11,  // 2D unsigned short normalized (v[0]/65535.0,v[1]/65535.0,0,1)
		DECLTYPE_USHORT4N  = 12,  // 4D unsigned short normalized (v[0]/65535.0,v[1]/65535.0,v[2]/65535.0,v[3]/65535.0)
		DECLTYPE_UDEC3     = 13,  // 3D unsigned 10 10 10 format expanded to (value, value, value, 1)
		DECLTYPE_DEC3N     = 14,  // 3D signed 10 10 10 format normalized and expanded to (v[0]/511.0, v[1]/511.0, v[2]/511.0, 1)
		DECLTYPE_FLOAT16_2 = 15,  // Two 16-bit floating point values, expanded to (value, value, 0, 1)
		DECLTYPE_FLOAT16_4 = 16,  // Four 16-bit floating point values
		DECLTYPE_UNUSED    = 17,  // When the type field in a decl is unused.
	};
///#define DECL_END() {0xFF,0,17,0,0,0}
	
	/**	\brief	创建声明需要的元素
	*
	*	创建声明需要的元素
	*
	***/
// 	struct Element{
// 		WORD    Stream;     // Stream index
// 		WORD    Offset;     // Offset in the stream in bytes
// 		BYTE    Type;       // Data type
// 		BYTE    Method;     // Processing method
// 		BYTE    Usage;      // Semantics
// 		BYTE    UsageIndex; // Semantic index
// 	};
	void	SetFullPath(const char*	pFullName);
	void	SetPath(const char*		pPath);
	
	bool	ExportNode(IGameNode*	pNode,bool bExportScene);
	bool	Export(bool bExportSelect = true);
}
#endif // AirMesh_h__