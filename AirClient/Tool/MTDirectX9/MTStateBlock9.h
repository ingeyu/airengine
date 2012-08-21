#ifndef MTSTATEBLOCK9_HEAD_FILE
#define	MTSTATEBLOCK9_HEAD_FILE

#include "MTHeader.h"


class MT_IDirect3DStateBlock9	:	public	MT_IUnknown
{
public:
    /*** IUnknown methods ***/
	STDMETHOD(QueryInterface)(THIS_ REFIID riid, void** ppvObj){
		return	m_pIDirect3DStateBlock9->QueryInterface(riid,ppvObj);
	};

    /*** IDirect3DStateBlock9 methods ***/
	STDMETHOD(GetDevice)(THIS_ MT_IDirect3DDevice9** ppDevice);
    STDMETHOD(Capture)(THIS);
    STDMETHOD(Apply)(THIS);

	void	SetIDirect3DStateBlock9(IDirect3DStateBlock9* pStateBlock);
public:
	MT_IDirect3DStateBlock9(MT_IDirect3DDevice9* pMT_IDirect3DDevice9,IDirect3DStateBlock9* pIDirect3DStateBlock9);
	virtual	~MT_IDirect3DStateBlock9();
public:
	IDirect3DStateBlock9*	m_pIDirect3DStateBlock9;
	MT_IDirect3DDevice9*	m_pMT_IDirect3DDevice9;
};

#endif