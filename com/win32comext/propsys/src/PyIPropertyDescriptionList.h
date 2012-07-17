// This file declares the IPropertyDescriptionList Interface and Gateway for Python.
// Generated by makegw.py
// ---------------------------------------------------
//
// Interface Declaration
#include "PythonCOM.h"
#include "PythonCOMServer.h"
#include "propsys.h"

class PyIPropertyDescriptionList : public PyIUnknown
{
public:
	MAKE_PYCOM_CTOR(PyIPropertyDescriptionList);
	static IPropertyDescriptionList *GetI(PyObject *self);
	static PyComTypeObject type;

	// The Python methods
	static PyObject *GetCount(PyObject *self, PyObject *args);
	static PyObject *GetAt(PyObject *self, PyObject *args);

protected:
	PyIPropertyDescriptionList(IUnknown *pdisp);
	~PyIPropertyDescriptionList();
};

// ---------------------------------------------------
//
// Gateway Declaration

class PyGPropertyDescriptionList : public PyGatewayBase, public IPropertyDescriptionList
{
protected:
	PyGPropertyDescriptionList(PyObject *instance) : PyGatewayBase(instance) { ; }
	PYGATEWAY_MAKE_SUPPORT2(PyGPropertyDescriptionList, IPropertyDescriptionList, IID_IPropertyDescriptionList, PyGatewayBase)

	// IPropertyDescriptionList
	STDMETHOD(GetCount)(UINT * pcElem);

	STDMETHOD(GetAt)(
		UINT iElem,
		REFIID riid,
		void ** ppv);

};
