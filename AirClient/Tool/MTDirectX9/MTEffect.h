#ifndef MTEFFECT_HEAD_FILE
#define	MTEFFECT_HEAD_FILE

#include "MTHeader.h"

class	MT_ID3DXEffect	:	public		MT_IUnknown//, ID3DXBaseEffect)
{
    // ID3DXBaseEffect
	STDMETHOD(QueryInterface)(THIS_ REFIID iid, LPVOID *ppv){
		return	m_pID3DXEffect->QueryInterface(iid,ppv);
	};
    //STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    //STDMETHOD_(ULONG, Release)(THIS) PURE;

    // Descs
	STDMETHOD(GetDesc)(THIS_ D3DXEFFECT_DESC* pDesc){
		return	m_pID3DXEffect->GetDesc(pDesc);
	};
	STDMETHOD(GetParameterDesc)(THIS_ D3DXHANDLE hParameter, D3DXPARAMETER_DESC* pDesc){
		return	m_pID3DXEffect->GetParameterDesc(hParameter,pDesc);
	};
    STDMETHOD(GetTechniqueDesc)(THIS_ D3DXHANDLE hTechnique, D3DXTECHNIQUE_DESC* pDesc){
		return	m_pID3DXEffect->GetTechniqueDesc(hTechnique,pDesc);
	};
    STDMETHOD(GetPassDesc)(THIS_ D3DXHANDLE hPass, D3DXPASS_DESC* pDesc){
		return	m_pID3DXEffect->GetPassDesc(hPass,pDesc);
	};
    STDMETHOD(GetFunctionDesc)(THIS_ D3DXHANDLE hShader, D3DXFUNCTION_DESC* pDesc){
		return	m_pID3DXEffect->GetFunctionDesc(hShader,pDesc);
	};

    // Handle operations
	STDMETHOD_(D3DXHANDLE, GetParameter)(THIS_ D3DXHANDLE hParameter, UINT Index){
		return	m_pID3DXEffect->GetParameter(hParameter,Index);
	};
	STDMETHOD_(D3DXHANDLE, GetParameterByName)(THIS_ D3DXHANDLE hParameter, LPCSTR pName){
		return	m_pID3DXEffect->GetParameterByName(hParameter,pName);
	};
	STDMETHOD_(D3DXHANDLE, GetParameterBySemantic)(THIS_ D3DXHANDLE hParameter, LPCSTR pSemantic){
		return	m_pID3DXEffect->GetParameterBySemantic(hParameter,pSemantic);
	};
	STDMETHOD_(D3DXHANDLE, GetParameterElement)(THIS_ D3DXHANDLE hParameter, UINT Index){
		return	m_pID3DXEffect->GetParameterElement(hParameter,Index);
	};
    STDMETHOD_(D3DXHANDLE, GetTechnique)(THIS_ UINT Index){
		return	m_pID3DXEffect->GetTechnique(Index);
	};
	STDMETHOD_(D3DXHANDLE, GetTechniqueByName)(THIS_ LPCSTR pName){
		return	m_pID3DXEffect->GetTechniqueByName(pName);
	};
    STDMETHOD_(D3DXHANDLE, GetPass)(THIS_ D3DXHANDLE hTechnique, UINT Index){
		return	m_pID3DXEffect->GetPass(hTechnique,Index);
	};
    STDMETHOD_(D3DXHANDLE, GetPassByName)(THIS_ D3DXHANDLE hTechnique, LPCSTR pName){
		return	m_pID3DXEffect->GetPassByName(hTechnique,pName);
	};
    STDMETHOD_(D3DXHANDLE, GetFunction)(THIS_ UINT Index){
		return	m_pID3DXEffect->GetFunction(Index);
	};
    STDMETHOD_(D3DXHANDLE, GetFunctionByName)(THIS_ LPCSTR pName){
		return	m_pID3DXEffect->GetFunctionByName(pName);
	};
    STDMETHOD_(D3DXHANDLE, GetAnnotation)(THIS_ D3DXHANDLE hObject, UINT Index){
		return	m_pID3DXEffect->GetAnnotation(hObject,Index);
	};
    STDMETHOD_(D3DXHANDLE, GetAnnotationByName)(THIS_ D3DXHANDLE hObject, LPCSTR pName){
		return	m_pID3DXEffect->GetAnnotationByName(hObject,pName);
	};

    // Get/Set Parameters
    STDMETHOD(SetValue)(THIS_ D3DXHANDLE hParameter, LPCVOID pData, UINT Bytes);
	STDMETHOD(GetValue)(THIS_ D3DXHANDLE hParameter, LPVOID pData, UINT Bytes){return	S_OK;};
    STDMETHOD(SetBool)(THIS_ D3DXHANDLE hParameter, BOOL b);
    STDMETHOD(GetBool)(THIS_ D3DXHANDLE hParameter, BOOL* pb){return	S_OK;};
    STDMETHOD(SetBoolArray)(THIS_ D3DXHANDLE hParameter, CONST BOOL* pb, UINT Count);
    STDMETHOD(GetBoolArray)(THIS_ D3DXHANDLE hParameter, BOOL* pb, UINT Count){return	S_OK;};
    STDMETHOD(SetInt)(THIS_ D3DXHANDLE hParameter, INT n);
    STDMETHOD(GetInt)(THIS_ D3DXHANDLE hParameter, INT* pn){return	S_OK;};
    STDMETHOD(SetIntArray)(THIS_ D3DXHANDLE hParameter, CONST INT* pn, UINT Count);
    STDMETHOD(GetIntArray)(THIS_ D3DXHANDLE hParameter, INT* pn, UINT Count){return	S_OK;};
    STDMETHOD(SetFloat)(THIS_ D3DXHANDLE hParameter, FLOAT f);
    STDMETHOD(GetFloat)(THIS_ D3DXHANDLE hParameter, FLOAT* pf){return	S_OK;};
    STDMETHOD(SetFloatArray)(THIS_ D3DXHANDLE hParameter, CONST FLOAT* pf, UINT Count);
    STDMETHOD(GetFloatArray)(THIS_ D3DXHANDLE hParameter, FLOAT* pf, UINT Count){return	S_OK;};
    STDMETHOD(SetVector)(THIS_ D3DXHANDLE hParameter, CONST D3DXVECTOR4* pVector);
    STDMETHOD(GetVector)(THIS_ D3DXHANDLE hParameter, D3DXVECTOR4* pVector){return	S_OK;};
    STDMETHOD(SetVectorArray)(THIS_ D3DXHANDLE hParameter, CONST D3DXVECTOR4* pVector, UINT Count);
    STDMETHOD(GetVectorArray)(THIS_ D3DXHANDLE hParameter, D3DXVECTOR4* pVector, UINT Count){return	S_OK;};
    STDMETHOD(SetMatrix)(THIS_ D3DXHANDLE hParameter, CONST D3DXMATRIX* pMatrix);
    STDMETHOD(GetMatrix)(THIS_ D3DXHANDLE hParameter, D3DXMATRIX* pMatrix){return	S_OK;};
    STDMETHOD(SetMatrixArray)(THIS_ D3DXHANDLE hParameter, CONST D3DXMATRIX* pMatrix, UINT Count);
    STDMETHOD(GetMatrixArray)(THIS_ D3DXHANDLE hParameter, D3DXMATRIX* pMatrix, UINT Count){return	S_OK;};
    STDMETHOD(SetMatrixPointerArray)(THIS_ D3DXHANDLE hParameter, CONST D3DXMATRIX** ppMatrix, UINT Count);
    STDMETHOD(GetMatrixPointerArray)(THIS_ D3DXHANDLE hParameter, D3DXMATRIX** ppMatrix, UINT Count){return	S_OK;};
    STDMETHOD(SetMatrixTranspose)(THIS_ D3DXHANDLE hParameter, CONST D3DXMATRIX* pMatrix);
    STDMETHOD(GetMatrixTranspose)(THIS_ D3DXHANDLE hParameter, D3DXMATRIX* pMatrix){return	S_OK;};
    STDMETHOD(SetMatrixTransposeArray)(THIS_ D3DXHANDLE hParameter, CONST D3DXMATRIX* pMatrix, UINT Count);
    STDMETHOD(GetMatrixTransposeArray)(THIS_ D3DXHANDLE hParameter, D3DXMATRIX* pMatrix, UINT Count){return	S_OK;};
    STDMETHOD(SetMatrixTransposePointerArray)(THIS_ D3DXHANDLE hParameter, CONST D3DXMATRIX** ppMatrix, UINT Count);
    STDMETHOD(GetMatrixTransposePointerArray)(THIS_ D3DXHANDLE hParameter, D3DXMATRIX** ppMatrix, UINT Count){return	S_OK;};
    STDMETHOD(SetString)(THIS_ D3DXHANDLE hParameter, LPCSTR pString);
    STDMETHOD(GetString)(THIS_ D3DXHANDLE hParameter, LPCSTR* ppString){return	S_OK;};
    STDMETHOD(SetTexture)(THIS_ D3DXHANDLE hParameter, LPDIRECT3DBASETEXTURE9 pTexture);
    STDMETHOD(GetTexture)(THIS_ D3DXHANDLE hParameter, LPDIRECT3DBASETEXTURE9 *ppTexture){return	S_OK;};
    STDMETHOD(GetPixelShader)(THIS_ D3DXHANDLE hParameter, LPDIRECT3DPIXELSHADER9 *ppPShader){return	S_OK;};
    STDMETHOD(GetVertexShader)(THIS_ D3DXHANDLE hParameter, LPDIRECT3DVERTEXSHADER9 *ppVShader){return	S_OK;};

	//Set Range of an Array to pass to device
	//Usefull for sending only a subrange of an array down to the device
	STDMETHOD(SetArrayRange)(THIS_ D3DXHANDLE hParameter, UINT uStart, UINT uEnd) PURE; 
	// ID3DXBaseEffect
    
    
    // Pool
	STDMETHOD(GetPool)(THIS_ LPD3DXEFFECTPOOL* ppPool){
		return	m_pID3DXEffect->GetPool(ppPool);
	};

    // Selecting and setting a technique
    STDMETHOD(SetTechnique)(THIS_ D3DXHANDLE hTechnique);
    STDMETHOD_(D3DXHANDLE, GetCurrentTechnique)(THIS);
    STDMETHOD(ValidateTechnique)(THIS_ D3DXHANDLE hTechnique) PURE;
	STDMETHOD(FindNextValidTechnique)(THIS_ D3DXHANDLE hTechnique, D3DXHANDLE *pTechnique){
		return	m_pID3DXEffect->FindNextValidTechnique(hTechnique,pTechnique);
	};
	STDMETHOD_(BOOL, IsParameterUsed)(THIS_ D3DXHANDLE hParameter, D3DXHANDLE hTechnique){
		return	m_pID3DXEffect->IsParameterUsed(hParameter,hTechnique);
	};

    // Using current technique
    // Begin           starts active technique
    // BeginPass       begins a pass
    // CommitChanges   updates changes to any set calls in the pass. This should be called before
    //                 any DrawPrimitive call to d3d
    // EndPass         ends a pass
    // End             ends active technique
    STDMETHOD(Begin)(THIS_ UINT *pPasses, DWORD Flags) PURE;
    STDMETHOD(BeginPass)(THIS_ UINT Pass) PURE;
    STDMETHOD(CommitChanges)(THIS) PURE;
    STDMETHOD(EndPass)(THIS) PURE;
    STDMETHOD(End)(THIS) PURE;

    // Managing D3D Device
	STDMETHOD(GetDevice)(THIS_ MT_LPDIRECT3DDEVICE9* ppDevice);
	STDMETHOD(OnLostDevice)(THIS){
		return	m_pID3DXEffect->OnLostDevice();
	};
	STDMETHOD(OnResetDevice)(THIS){
		return	m_pID3DXEffect->OnResetDevice();
	}

    // Logging device calls
    STDMETHOD(SetStateManager)(THIS_ LPD3DXEFFECTSTATEMANAGER pManager);
	STDMETHOD(GetStateManager)(THIS_ LPD3DXEFFECTSTATEMANAGER *ppManager){
		return	m_pID3DXEffect->GetStateManager(ppManager);
	};

    // Parameter blocks
    //STDMETHOD(BeginParameterBlock)(THIS) PURE;
    //STDMETHOD_(D3DXHANDLE, EndParameterBlock)(THIS) PURE;
    //STDMETHOD(ApplyParameterBlock)(THIS_ D3DXHANDLE hParameterBlock) PURE;
    //STDMETHOD(DeleteParameterBlock)(THIS_ D3DXHANDLE hParameterBlock) PURE;

    // Cloning
	STDMETHOD(CloneEffect)(THIS_ MT_LPDIRECT3DDEVICE9 pDevice, MT_LPD3DXEFFECT* ppEffect);
    
    // Fast path for setting variables directly in ID3DXEffect
    STDMETHOD(SetRawValue)(THIS_ D3DXHANDLE hParameter, LPCVOID pData, UINT ByteOffset, UINT Bytes) PURE;
public:
	MT_ID3DXEffect(MT_IDirect3DDevice9*	pMT_IDirect3DDevice9,ID3DXEffect*			pID3DXEffect);
	virtual	~MT_ID3DXEffect();
public:
	MT_IDirect3DDevice9*	m_pMT_IDirect3DDevice9;
	ID3DXEffect*			m_pID3DXEffect;
};

#endif