// This file declares the IEnumSTATSTG Interface and Gateway for Python.
// Generated by makegw.py
// ---------------------------------------------------
//
// Interface Declaration

class PyIEnumSTATSTG : public PyIUnknown
{
public:
	MAKE_PYCOM_CTOR(PyIEnumSTATSTG);
	static IEnumSTATSTG *GetI(PyObject *self);
	static PyComTypeObject type;

	// The Python methods
	static PyObject *Next(PyObject *self, PyObject *args);
	static PyObject *Skip(PyObject *self, PyObject *args);
	static PyObject *Reset(PyObject *self, PyObject *args);
	static PyObject *Clone(PyObject *self, PyObject *args);

protected:
	PyIEnumSTATSTG(IUnknown *pdisp);
	~PyIEnumSTATSTG();
};
// ---------------------------------------------------
//
// Gateway Declaration

class PyGEnumSTATSTG : public PyGatewayBase, public IEnumSTATSTG
{
protected:
	PyGEnumSTATSTG(PyObject *instance) : PyGatewayBase(instance) { ; }
	PYGATEWAY_MAKE_SUPPORT(PyGEnumSTATSTG, IEnumSTATSTG, IID_IEnumSTATSTG)

	// IEnumSTATSTG
	STDMETHOD(Next)(
		ULONG celt,
		STATSTG __RPC_FAR * rgelt,
		ULONG __RPC_FAR * pceltFetched);

	STDMETHOD(Skip)(
		ULONG celt);

	STDMETHOD(Reset)(
		void);

	STDMETHOD(Clone)(
		IEnumSTATSTG __RPC_FAR *__RPC_FAR * ppenum);

};
