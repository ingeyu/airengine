#include "AirEngineMesh.h"
namespace Air{
	
	namespace	Engine{
		//namespace	Mesh3DS{
	#define	Read(pReturn,uiSize,uiCount,pData)	\
		{\
		memcpy(pReturn,pData,uiSize*uiCount);\
		pData+=uiSize*uiCount;\
		uiPos+=uiSize*uiCount;\
	}
	#define ReadStr(pData,pString)\
		{\
		int i=0;\
		do{\
		Read (&pString[i++], 1, 1, pData);\
		}while(*pData != '\0' && i<255);\
		pData++;uiPos++;pString[i]='\0';\
	}
		//inline	ReadMem()
	
	
			class	Parse3DS	:
				public	Mesh::IParseCallBack{
			public:
				Parse3DS(){
					//Mesh::SetParseCallBack(this);
				}
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
					U16 usChunkId		=	0; //Chunk identifier
					U32 uiChunkLenght	=	0; //Chunk lenght
					U16 l_qty			=	0; //Number of elements in each chunk
					U16 l_face_flags	=	0; //Flag that stores some face information
					U8*	l_file			=	pData->GetBuff();
					UInt	uiSize		=	pData->GetSize();
					std::vector<AString>	lstMaterialName;
	
					U32	uiPos	=	0;
					while(uiPos<uiSize){
						Read (&usChunkId, 2, 1, l_file); //Read the chunk header
						Read (&uiChunkLenght, 4, 1, l_file); //Read the lenght of the chunk
						switch (usChunkId){
							//----------------- MAIN3DS -----------------
							// Description: Main chunk, contains all the other chunks
							// Chunk ID: 4d4d 
							// Chunk Lenght: 0 + sub chunks
							//-------------------------------------------
							case 0x4d4d: 
								break;    
	
								//----------------- EDIT3DS -----------------
								// Description: 3D Editor chunk, objects layout info 
								// Chunk ID: 3d3d (hex)
								// Chunk Lenght: 0 + sub chunks
								//-------------------------------------------
							case 0x3d3d:
								break;
	
								//--------------- EDIT_OBJECT ---------------
								// Description: Object block, info for each object
								// Chunk ID: 4000 (hex)
								// Chunk Lenght: len(object name) + sub chunks
								//-------------------------------------------
							case 0x4000: 
								{
	// 								t3DObject obj;
	// 								obj.numOfFaces = 0;
	// 								obj.numOfVerts = 0;
	// 								obj.numTexVertex = 0;
	// 								obj.pFaces = 0;
	// 								obj.pTexVerts = 0;
	// 								obj.pVerts = 0;
	// 								obj.pNormals	=	NULL;
									//	memset(&obj,0,sizeof(t3DObject));
									AChar strName[MAX_NAME];
									ReadStr(l_file,strName);
									lstMaterialName.push_back(strName);
	
								}
								break;
	
								//--------------- OBJ_TRIMESH ---------------
								// Description: Triangular mesh, contains chunks for 3d mesh info
								// Chunk ID: 4100 (hex)
								// Chunk Lenght: 0 + sub chunks
								//-------------------------------------------
							case 0x4100:
								break;
	
								//--------------- TRI_VERTEXL ---------------
								// Description: Vertices list
								// Chunk ID: 4110 (hex)
								// Chunk Lenght: 1 x unsigned short (number of vertices) 
								//             + 3 x float (vertex coordinates) x (number of vertices)
								//             + sub chunks
								//-------------------------------------------
							case 0x4110:{
								U16	usNumVertex	=	0;
								Read (&usNumVertex, sizeof(U16), 1, l_file);
								lstVertex.resize(usNumVertex);
								for (SInt	i=0; i<usNumVertex; i++){
									Read (&lstVertex[i].Position.x, sizeof(float), 1, l_file);
									Read (&lstVertex[i].Position.z, sizeof(float), 1, l_file);
									Read (&lstVertex[i].Position.y, sizeof(float), 1, l_file);
	
	// 								lstVertex[i].Position.z	=	-lstVertex[i].Position.z;
	// 								lstVertex[i].Position.x	=	-lstVertex[i].Position.x;
	
									//lstVertex[i].Position.x	+=	50.0f;
								}
								break;}
	
								//--------------- TRI_FACEL1 ----------------
								// Description: Polygons (faces) list
								// Chunk ID: 4120 (hex)
								// Chunk Lenght: 1 x unsigned short (number of polygons) 
								//             + 3 x unsigned short (polygon points) x (number of polygons)
								//             + sub chunks
								//-------------------------------------------
							case 0x4120:{//face
								U16	usNumFace	=	0;
								Read (&usNumFace, sizeof (unsigned short), 1, l_file);
								lstFace16.resize(usNumFace);
								//	memset(pObj->pFaces,0,sizeof(tFace)*l_qty);
								for (SInt	i=0; i<usNumFace; i++){
									Read (&lstFace16[i].f2, sizeof (unsigned short), 1, l_file);
									Read (&lstFace16[i].f1, sizeof (unsigned short), 1, l_file);
									Read (&lstFace16[i].f0, sizeof (unsigned short), 1, l_file);
									Read (&l_face_flags, sizeof (unsigned short), 1, l_file);
								}
								break;}
							case 0x4130:// This is found if the object has a material, either texture map or color
								{
									char strMaterial[255];
									ReadStr(l_file,strMaterial);
									short n,nf;
									Read (&n, sizeof(short), 1, l_file);
	
									UInt	uiMaterialSize	=	lstMaterialName.size();
									// Go through all of the textures
									for( UInt	i = 0; i < uiMaterialSize; i++)
									{
										// If the material we just read in matches the current texture name
										if(strcmp(strMaterial, lstMaterialName[i].c_str()) == 0)
										{
											while (n-- > 0) 
											{	// Material number assigned to any face
												// Numero di material assegnato ad ogni faccia
												Read (&nf, sizeof(short), 1, l_file);
												//pObj->pFaces[nf].matIndex = i;
											}
											// Now that we found the material, check if it's a texture map.
											// If the strFile has a string length of 1 and over it's a texture
											//if(strlen(pModel->vMaterials[i].strFile) > 0) 
											//{
												// Set the object's flag to say it has a texture map to bind.
												//	pObj->bHasTexture = true;
											//}	
											break;
										}
									}
	
									break;
								}
								//------------- TRI_MAPPINGCOORS ------------
								// Description: Vertices list
								// Chunk ID: 4140 (hex)
								// Chunk Lenght: 1 x unsigned short (number of mapping points) 
								//             + 2 x float (mapping coordinates) x (number of mapping points)
								//             + sub chunks
								//-------------------------------------------
							case 0x4140:{
								U16	usNumVertex	=	0;
								Read (&usNumVertex, sizeof (unsigned short), 1, l_file);
								
								for (SInt	i=0; i<usNumVertex; i++)
								{
									Read (&lstVertex[i].UV.x, sizeof (float), 1, l_file);
									Read (&lstVertex[i].UV.y, sizeof (float), 1, l_file);
								}
								break;}
							case 0xAFFF://MATERIAL:
								{
	//								tMaterialInfo newTexture ;//= {0};
									//	memset(&newTexture,0,sizeof(tMaterialInfo));
	// 								newTexture.strFile[0] = '\0';
	// 								newTexture.strName[0] = '\0';
	// 								m_Model.vMaterials.push_back(newTexture);
									break;
								}
							case 0xA000://// This holds the material name
								{
									//tMaterialInfo &matInfo = m_Model.vMaterials[m_Model.vMaterials.size()-1];
									AChar str[MAX_NAME];
									ReadStr(l_file,str);
									break;
								}
							case 0xA300: //// This holds the file name of the texture
								{
									//tMaterialInfo &matInfo = m_Model.vMaterials[m_Model.vMaterials.size()-1];
									AChar str[MAX_NAME];
									ReadStr(l_file,str);
									break;
								}
							case 0xA200:	//texture map flag//	// This is the header for the texture info
								{break;}
								//----------- Skip unknow chunks ------------
								//We need to skip all the chunks that currently we don't use
								//We use the chunk lenght information to set the file pointer
								//to the same level next chunk
								//-------------------------------------------
							default:
								l_file+=uiChunkLenght-6;uiPos+=uiChunkLenght-6;//Read(l_file, l_chunk_lenght-6, SEEK_CUR);
										}
					}
	
					return true;
				}
				/**	\brief	获取解析后缀名
				*   
				*	@remarks 	获取解析后缀名
				*	@see		IParseCallBack
				*	@return   	AString
				*	@note
				*
				**/
				virtual	AString	GetPostfixName(){
					return	"3ds";
				}
			};
	
			const	static	Parse3DS	g_pParse3DS;
		//}
	}
};