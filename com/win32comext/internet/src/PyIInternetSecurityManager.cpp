// This file implements the IInternetSecurityManager Interface and Gateway for Python.
// Generated by makegw.py

#include "internet_pch.h"
#include "PyIInternetSecurityManager.h"

// @doc - This file contains autoduck documentation
// ---------------------------------------------------
//
// Interface Implementation

PyIInternetSecurityManager::PyIInternetSecurityManager(IUnknown *pdisp):
	PyIUnknown(pdisp)
{
	ob_type = &type;
}

PyIInternetSecurityManager::~PyIInternetSecurityManager()
{
}

/* static */ IInternetSecurityManager *PyIInternetSecurityManager::GetI(PyObject *self)
{
	return (IInternetSecurityManager *)PyIUnknown::GetI(self);
}

// @pymethod |PyIInternetSecurityManager|SetSecuritySite|Description of SetSecuritySite.
PyObject *PyIInternetSecurityManager::SetSecuritySite(PyObject *self, PyObject *args)
{
	IInternetSecurityManager *pIISM = GetI(self);
	if ( pIISM == NULL )
		return NULL;
	// @pyparm <o PyIInternetSecurityMgrSite>|pSite||Description for pSite
	PyObject *obpSite;
	IInternetSecurityMgrSite * pSite;
	if (!PyArg_ParseTuple(args, "O:SetSecuritySite", &obpSite))
		return NULL;
	if (!PyCom_InterfaceFromPyInstanceOrObject(obpSite, IID_IInternetSecurityMgrSite, (void **)&pSite, TRUE /* bNoneOK */))
		return NULL;
	HRESULT hr;
	PY_INTERFACE_PRECALL;
	hr = pIISM->SetSecuritySite( pSite );
	if (pSite) pSite->Release();
	PY_INTERFACE_POSTCALL;
	if ( FAILED(hr) )
		return PyCom_BuildPyException(hr, pIISM, IID_IInternetSecurityManager );
	Py_INCREF(Py_None);
	return Py_None;

}

// @pymethod |PyIInternetSecurityManager|GetSecuritySite|Description of GetSecuritySite.
PyObject *PyIInternetSecurityManager::GetSecuritySite(PyObject *self, PyObject *args)
{
	IInternetSecurityManager *pIISM = GetI(self);
	if ( pIISM == NULL )
		return NULL;
	IInternetSecurityMgrSite * ppSite;
	if ( !PyArg_ParseTuple(args, ":GetSecuritySite") )
		return NULL;
	HRESULT hr;
	PY_INTERFACE_PRECALL;
	hr = pIISM->GetSecuritySite(&ppSite);
	PY_INTERFACE_POSTCALL;
	if ( FAILED(hr) )
		return PyCom_BuildPyException(hr, pIISM, IID_IInternetSecurityManager );
	return PyCom_PyObjectFromIUnknown(ppSite, IID_IInternetSecurityMgrSite, FALSE);
}

// @pymethod |PyIInternetSecurityManager|MapUrlToZone|Description of MapUrlToZone.
PyObject *PyIInternetSecurityManager::MapUrlToZone(PyObject *self, PyObject *args)
{
	IInternetSecurityManager *pIISM = GetI(self);
	if ( pIISM == NULL )
		return NULL;
	// @pyparm <o unicode>|pwszUrl||Description for pwszUrl
	// @pyparm int|dwFlags||Description for dwFlags
	PyObject *obpwszUrl;
	LPWSTR pwszUrl;
	DWORD pdwZone;
	DWORD dwFlags;
	if (!PyArg_ParseTuple(args, "Ol:MapUrlToZone", &obpwszUrl, &dwFlags))
		return NULL;
	if (!PyWinObject_AsBstr(obpwszUrl, &pwszUrl))
		return NULL;
	HRESULT hr;
	PY_INTERFACE_PRECALL;
	hr = pIISM->MapUrlToZone( pwszUrl, &pdwZone, dwFlags );
	SysFreeString(pwszUrl);
	PY_INTERFACE_POSTCALL;
	if ( FAILED(hr) )
		return PyCom_BuildPyException(hr, pIISM, IID_IInternetSecurityManager );
	return PyInt_FromLong(pdwZone);
}

// @pymethod |PyIInternetSecurityManager|GetSecurityId|Description of GetSecurityId.
PyObject *PyIInternetSecurityManager::GetSecurityId(PyObject *self, PyObject *args)
{
	IInternetSecurityManager *pIISM = GetI(self);
	if ( pIISM == NULL )
		return NULL;
	// @pyparm <o unicode>|pwszUrl||Description for pwszUrl
	// @pyparm int|pcbSecurityId||Description for pcbSecurityId
	DWORD_PTR dwReserved = 0;
	PyObject *obdwReserved = Py_None;
	// ACK - 'reserved' docs appears to indicate its actually a string.
	// so ignore it for now.
	PyObject *obpwszUrl;
	LPWSTR pwszUrl;
	if ( !PyArg_ParseTuple(args, "O:GetSecurityId", &obpwszUrl) )
		return NULL;
	if (!PyWinObject_AsBstr(obpwszUrl, &pwszUrl))
		return NULL;
	BYTE buf[1024]; // big enough?
	DWORD cbSecurityId = sizeof(buf);
	HRESULT hr;
	PY_INTERFACE_PRECALL;
	hr = pIISM->GetSecurityId( pwszUrl, buf, &cbSecurityId, 0);
	SysFreeString(pwszUrl);
	PY_INTERFACE_POSTCALL;
	if ( FAILED(hr) )
		return PyCom_BuildPyException(hr, pIISM, IID_IInternetSecurityManager );
	return PyString_FromStringAndSize((char *)buf, cbSecurityId);
}

// @pymethod |PyIInternetSecurityManager|ProcessUrlAction|Description of ProcessUrlAction.
PyObject *PyIInternetSecurityManager::ProcessUrlAction(PyObject *self, PyObject *args)
{
	IInternetSecurityManager *pIISM = GetI(self);
	if ( pIISM == NULL )
		return NULL;
	// @pyparm <o unicode>|pwszUrl||Description for pwszUrl
	// @pyparm int|dwAction||Description for dwAction
	// @pyparm int|dwFlags||Description for dwFlags
	PyObject *obpwszUrl;
	LPWSTR pwszUrl;
	DWORD dwAction;
	PyObject *obContext;
	DWORD dwFlags;
	if ( !PyArg_ParseTuple(args, "OlOl:ProcessUrlAction", &obpwszUrl, &dwAction, &obContext, &dwFlags) )
		return NULL;
	BOOL bPythonIsHappy = TRUE;
	IID context;
	if (bPythonIsHappy && !PyWinObject_AsBstr(obpwszUrl, &pwszUrl)) bPythonIsHappy = FALSE;
	if (bPythonIsHappy && !PyWinObject_AsIID(obContext, &context)) bPythonIsHappy = FALSE;
	if (!bPythonIsHappy) return NULL;
	DWORD dwPolicy = 0;
	HRESULT hr;
	PY_INTERFACE_PRECALL;
	hr = pIISM->ProcessUrlAction( pwszUrl, dwAction, (BYTE *)&dwPolicy, sizeof(dwPolicy), (BYTE *)&context, sizeof(context), dwFlags, 0);
	SysFreeString(pwszUrl);
	PY_INTERFACE_POSTCALL;
	if ( FAILED(hr) )
		return PyCom_BuildPyException(hr, pIISM, IID_IInternetSecurityManager);
	return Py_BuildValue("ll", hr, dwPolicy);
}

/***
// @pymethod |PyIInternetSecurityManager|QueryCustomPolicy|Description of QueryCustomPolicy.
PyObject *PyIInternetSecurityManager::QueryCustomPolicy(PyObject *self, PyObject *args)
{
	IInternetSecurityManager *pIISM = GetI(self);
	if ( pIISM == NULL )
		return NULL;
	// @pyparm <o unicode>|pwszUrl||Description for pwszUrl
	// @pyparm <o PyIID>|guidKey||Description for guidKey
	// @pyparm int|pContext||Description for pContext
	// @pyparm int|cbContext||Description for cbContext
	// @pyparm int|dwReserved||Description for dwReserved
	PyObject *obpwszUrl;
	PyObject *obguidKey;
	LPWSTR pwszUrl;
	IID guidKey;
	BYTE ppPolicy;
	DWORD pcbPolicy;
	BYTE pContext;
	DWORD cbContext;
	DWORD dwReserved;
	if ( !PyArg_ParseTuple(args, "OOill:QueryCustomPolicy", &obpwszUrl, &obguidKey, &pContext, &cbContext, &dwReserved) )
		return NULL;
	BOOL bPythonIsHappy = TRUE;
	if (bPythonIsHappy && !PyWinObject_AsBstr(obpwszUrl, &pwszUrl)) bPythonIsHappy = FALSE;
	if (!PyWinObject_AsIID(obguidKey, &guidKey)) bPythonIsHappy = FALSE;
	if (!bPythonIsHappy) return NULL;
	HRESULT hr;
	PY_INTERFACE_PRECALL;
	hr = pIISM->QueryCustomPolicy( pwszUrl, guidKey, ?? (-2)ppPolicy, &pcbPolicy, &pContext, cbContext, dwReserved );
	SysFreeString(pwszUrl);

	PY_INTERFACE_POSTCALL;

	if ( FAILED(hr) )
		return PyCom_BuildPyException(hr, pIISM, IID_IInternetSecurityManager );

	PyObject *pyretval = Py_BuildValue("il", ppPolicy, pcbPolicy);
	return pyretval;
}
***/

// @pymethod |PyIInternetSecurityManager|SetZoneMapping|Description of SetZoneMapping.
PyObject *PyIInternetSecurityManager::SetZoneMapping(PyObject *self, PyObject *args)
{
	IInternetSecurityManager *pIISM = GetI(self);
	if ( pIISM == NULL )
		return NULL;
	// @pyparm int|dwZone||Description for dwZone
	// @pyparm <o unicode>|lpszPattern||Description for lpszPattern
	// @pyparm int|dwFlags||Description for dwFlags
	PyObject *oblpszPattern;
	DWORD dwZone;
	LPWSTR lpszPattern;
	DWORD dwFlags;
	if (!PyArg_ParseTuple(args, "lOl:SetZoneMapping", &dwZone, &oblpszPattern, &dwFlags))
		return NULL;
	if (!PyWinObject_AsBstr(oblpszPattern, &lpszPattern))
		return NULL;
	HRESULT hr;
	PY_INTERFACE_PRECALL;
	hr = pIISM->SetZoneMapping( dwZone, lpszPattern, dwFlags );
	SysFreeString(lpszPattern);
	PY_INTERFACE_POSTCALL;
	if ( FAILED(hr) )
		return PyCom_BuildPyException(hr, pIISM, IID_IInternetSecurityManager );
	Py_INCREF(Py_None);
	return Py_None;

}

// @pymethod |PyIInternetSecurityManager|GetZoneMappings|Description of GetZoneMappings.
PyObject *PyIInternetSecurityManager::GetZoneMappings(PyObject *self, PyObject *args)
{
	IInternetSecurityManager *pIISM = GetI(self);
	if ( pIISM == NULL )
		return NULL;
	// @pyparm int|dwZone||Description for dwZone
	// @pyparm int|dwFlags||Description for dwFlags
	DWORD dwZone;
	IEnumString * ppenumString;
	DWORD dwFlags;
	if ( !PyArg_ParseTuple(args, "ll:GetZoneMappings", &dwZone, &dwFlags) )
		return NULL;
	HRESULT hr;
	PY_INTERFACE_PRECALL;
	hr = pIISM->GetZoneMappings( dwZone, &ppenumString, dwFlags );
	PY_INTERFACE_POSTCALL;
	if ( FAILED(hr) )
		return PyCom_BuildPyException(hr, pIISM, IID_IInternetSecurityManager );
	return PyCom_PyObjectFromIUnknown(ppenumString, IID_IEnumString, FALSE);
}

// @object PyIInternetSecurityManager|Description of the interface
static struct PyMethodDef PyIInternetSecurityManager_methods[] =
{
	{ "SetSecuritySite", PyIInternetSecurityManager::SetSecuritySite, 1 }, // @pymeth SetSecuritySite|Description of SetSecuritySite
	{ "GetSecuritySite", PyIInternetSecurityManager::GetSecuritySite, 1 }, // @pymeth GetSecuritySite|Description of GetSecuritySite
	{ "MapUrlToZone", PyIInternetSecurityManager::MapUrlToZone, 1 }, // @pymeth MapUrlToZone|Description of MapUrlToZone
	{ "GetSecurityId", PyIInternetSecurityManager::GetSecurityId, 1 }, // @pymeth GetSecurityId|Description of GetSecurityId
	{ "ProcessUrlAction", PyIInternetSecurityManager::ProcessUrlAction, 1 }, // @pymeth ProcessUrlAction|Description of ProcessUrlAction
//	{ "QueryCustomPolicy", PyIInternetSecurityManager::QueryCustomPolicy, 1 },
	{ "SetZoneMapping", PyIInternetSecurityManager::SetZoneMapping, 1 }, // @pymeth SetZoneMapping|Description of SetZoneMapping
	{ "GetZoneMappings", PyIInternetSecurityManager::GetZoneMappings, 1 }, // @pymeth GetZoneMappings|Description of GetZoneMappings
	{ NULL }
};

PyComTypeObject PyIInternetSecurityManager::type("PyIInternetSecurityManager",
		&PyIUnknown::type,
		sizeof(PyIInternetSecurityManager),
		PyIInternetSecurityManager_methods,
		GET_PYCOM_CTOR(PyIInternetSecurityManager));
// ---------------------------------------------------
//
// Gateway Implementation
STDMETHODIMP PyGInternetSecurityManager::SetSecuritySite(
		/* [unique][in] */ IInternetSecurityMgrSite * pSite)
{
	PY_GATEWAY_METHOD;
	PyObject *obpSite;
	obpSite = PyCom_PyObjectFromIUnknown(pSite, IID_IInternetSecurityMgrSite, TRUE);
	HRESULT hr=InvokeViaPolicy("SetSecuritySite", NULL, "O", obpSite);
	Py_XDECREF(obpSite);
	return hr;
}

STDMETHODIMP PyGInternetSecurityManager::GetSecuritySite(
		/* [out] */ IInternetSecurityMgrSite ** ppSite)
{
	PY_GATEWAY_METHOD;
	if (ppSite==NULL) return E_POINTER;
	PyObject *result;
	HRESULT hr=InvokeViaPolicy("GetSecuritySite", &result);
	if (FAILED(hr)) return hr;
	// Process the Python results, and convert back to the real params
	if (!PyCom_InterfaceFromPyInstanceOrObject(result, IID_IInternetSecurityMgrSite, (void **)ppSite, TRUE /* bNoneOK */))
		hr = MAKE_PYCOM_GATEWAY_FAILURE_CODE("GetSecuritySite");
	Py_DECREF(result);
	return hr;
}

STDMETHODIMP PyGInternetSecurityManager::MapUrlToZone(
		/* [in] */ LPCWSTR pwszUrl,
		/* [out] */ DWORD * pdwZone,
		/* [in] */ DWORD dwFlags)
{
	PY_GATEWAY_METHOD;
	PyObject *obpwszUrl;
	obpwszUrl = MakeOLECHARToObj(pwszUrl);
	PyObject *result;
	HRESULT hr=InvokeViaPolicy("MapUrlToZone", &result, "Ol", obpwszUrl, dwFlags);
	Py_XDECREF(obpwszUrl);
	if (FAILED(hr)) return hr;
	// Process the Python results, and convert back to the real params
	if (!PyArg_Parse(result, "l" , pdwZone))
		return MAKE_PYCOM_GATEWAY_FAILURE_CODE("MapUrlToZone");
	Py_DECREF(result);
	return hr;
}

STDMETHODIMP PyGInternetSecurityManager::GetSecurityId(
		/* [in] */ LPCWSTR pwszUrl,
		/* [size_is][out] */ BYTE * pbSecurityId,
		/* [out][in] */ DWORD * pcbSecurityId,
		/* [in] */ DWORD_PTR dwReserved)
{
	PY_GATEWAY_METHOD;
	PyObject *obdwReserved = PyWinObject_FromDWORD_PTR(dwReserved);
	if (obdwReserved==NULL) return MAKE_PYCOM_GATEWAY_FAILURE_CODE("GetSecurityId");
	PyObject *obpwszUrl;
	obpwszUrl = MakeOLECHARToObj(pwszUrl);
	PyObject *result;
	HRESULT hr=InvokeViaPolicy("GetSecurityId", &result, "OlO", obpwszUrl, *pcbSecurityId, obdwReserved);
	Py_XDECREF(obpwszUrl);
	Py_DECREF(obdwReserved);
	if (FAILED(hr)) return hr;
	// Process the Python results, and convert back to the real params
	void *buf;
	DWORD buf_len;
	if (!PyWinObject_AsReadBuffer(result, &buf, &buf_len)) {
		Py_DECREF(result);
		return MAKE_PYCOM_GATEWAY_FAILURE_CODE("GetSecurityId");
	}
	*pcbSecurityId = min(buf_len, *pcbSecurityId);
	memcpy(pbSecurityId, buf, *pcbSecurityId);
	Py_DECREF(result);
	return hr;
}

STDMETHODIMP PyGInternetSecurityManager::ProcessUrlAction(
		/* [in] */ LPCWSTR pwszUrl,
		/* [in] */ DWORD dwAction,
		/* [size_is][out] */ BYTE * pPolicy,
		/* [in] */ DWORD cbPolicy,
		/* [in] */ BYTE * pContext,
		/* [in] */ DWORD cbContext,
		/* [in] */ DWORD dwFlags,
		/* [in] */ DWORD dwReserved)
{
	PY_GATEWAY_METHOD;
	PyObject *obpwszUrl;
	PyObject *obContext;
	obpwszUrl = MakeOLECHARToObj(pwszUrl);
	if (cbContext==0 || pContext==NULL) {
		obContext = Py_None;
		Py_INCREF(Py_None);
	} else if (cbContext==sizeof(GUID))
		obContext = PyWinObject_FromIID(*((IID *)*pContext));
	else {
		PyCom_LoggerWarning(NULL, "PyGInternetSecurityManager::ProcessUrlAction has %d bytes for context - what is that?", cbContext);
		obContext = Py_None;
		Py_INCREF(Py_None);
	}
	PyObject *result;
	HRESULT hr=InvokeViaPolicy("ProcessUrlAction", &result, "OlOll", obpwszUrl, dwAction, obContext, dwFlags, dwReserved);
	Py_XDECREF(obpwszUrl);
	Py_XDECREF(obContext);
	if (FAILED(hr)) return hr;
	// Process the Python results, and convert back to the real params
	if (cbPolicy==sizeof(DWORD)) {
		*((DWORD *)pPolicy) = PyInt_AsLong(result);
		if (*((DWORD *)pPolicy)==-1)
			hr = MAKE_PYCOM_GATEWAY_FAILURE_CODE("ProcessUrlAction");
	} else {
		PyCom_LoggerWarning(NULL, "PyGInternetSecurityManager::ProcessUrlAction has %d bytes for policy - what is that?", cbPolicy);
		hr = E_UNEXPECTED;
	}
	return hr;
}

STDMETHODIMP PyGInternetSecurityManager::QueryCustomPolicy(
		/* [in] */ LPCWSTR pwszUrl,
		/* [in] */ REFGUID guidKey,
		/* [size_is][size_is][out] */ BYTE ** ppPolicy,
		/* [out] */ DWORD * pcbPolicy,
		/* [in] */ BYTE * pContext,
		/* [in] */ DWORD cbContext,
		/* [in] */ DWORD dwReserved)
{
    return INET_E_DEFAULT_ACTION;
/***
	PY_GATEWAY_METHOD;
	if (ppPolicy==NULL) return E_POINTER;
	PyObject *obpwszUrl;
	PyObject *obguidKey;
	obpwszUrl = MakeOLECHARToObj(pwszUrl);
	obguidKey = PyWinObject_FromIID(guidKey);
	PyObject *result;
	HRESULT hr=InvokeViaPolicy("QueryCustomPolicy", &result, "OOill", obpwszUrl, obguidKey, pContext, cbContext, dwReserved);
	Py_XDECREF(obpwszUrl);
	Py_XDECREF(obguidKey);
	if (FAILED(hr)) return hr;
	// Process the Python results, and convert back to the real params
	if (!PyArg_ParseTuple(result, "il" , *ppPolicy, pcbPolicy))
		return MAKE_PYCOM_GATEWAY_FAILURE_CODE("QueryCustomPolicy");
	Py_DECREF(result);
	return hr;
***/
}

STDMETHODIMP PyGInternetSecurityManager::SetZoneMapping(
		/* [in] */ DWORD dwZone,
		/* [in] */ LPCWSTR lpszPattern,
		/* [in] */ DWORD dwFlags)
{
	PY_GATEWAY_METHOD;
	return InvokeViaPolicy("SetZoneMapping", NULL, "lNl",
			       dwZone,
			       MakeOLECHARToObj(lpszPattern),
			       dwFlags);
}

STDMETHODIMP PyGInternetSecurityManager::GetZoneMappings(
		/* [in] */ DWORD dwZone,
		/* [out] */ IEnumString ** ppenumString,
		/* [in] */ DWORD dwFlags)
{
	PY_GATEWAY_METHOD;
	if (ppenumString==NULL) return E_POINTER;
	PyObject *result;
	HRESULT hr=InvokeViaPolicy("GetZoneMappings", &result, "ll", dwZone, dwFlags);
	if (FAILED(hr)) return hr;
	// Process the Python results, and convert back to the real params
	PyObject *obppenumString;
	if (!PyArg_Parse(result, "O" , &obppenumString))
		return MAKE_PYCOM_GATEWAY_FAILURE_CODE("GetZoneMappings");
	if (!PyCom_InterfaceFromPyInstanceOrObject(obppenumString, IID_IEnumString, (void **)ppenumString, TRUE /* bNoneOK */))
		hr = MAKE_PYCOM_GATEWAY_FAILURE_CODE("GetZoneMappings");
	Py_DECREF(result);
	return hr;
}
