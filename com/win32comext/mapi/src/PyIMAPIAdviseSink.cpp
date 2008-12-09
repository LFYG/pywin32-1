// This file implements the IMAPIAdviseSink Interface and Gateway for Python.
// Generated by makegw.py

#include "PythonCOM.h"
#include "PythonCOMServer.h"
#include "mapidefs.h"
#include "mapiguid.h"
#include "PyMAPIUtil.h"
#include "PyIMAPIAdviseSink.h"

// @doc - This file contains autoduck documentation
// ---------------------------------------------------
//
PyObject *PyObject_FromNOTIFICATION(NOTIFICATION *n)
{
	PyObject *ret = NULL;
	switch (n->ulEventType) {
		case fnevCriticalError: {
			ERROR_NOTIFICATION &err(n->info.err);
			ret = Py_BuildValue("k(s#iiN)",
					    n->ulEventType,
					    err.lpEntryID, err.cbEntryID,
					    err.scode,
					    err.ulFlags,
					    PyObject_FromMAPIERROR(err.lpMAPIError, err.ulFlags&MAPI_UNICODE, FALSE));
			break;
		}
		case fnevExtended: {
			EXTENDED_NOTIFICATION &ext = n->info.ext;
			ret = Py_BuildValue("k(ks#)", n->ulEventType, ext.ulEvent,
					    ext.pbEventParameters, ext.cb);
			break;
		}
		case fnevNewMail: {
			NEWMAIL_NOTIFICATION &newmail = n->info.newmail;
			PyObject *msg_class = newmail.ulFlags&MAPI_UNICODE?
					PyWinObject_FromWCHAR((const WCHAR *)newmail.lpszMessageClass) :
					PyString_FromString((const char *)newmail.lpszMessageClass);
			if (!msg_class)
				return NULL;
			ret = Py_BuildValue("k(s#s#kNk)",
					    n->ulEventType,
					    newmail.lpEntryID, newmail.cbEntryID,
					    newmail.lpParentID, newmail.cbParentID,
					    newmail.ulFlags,
					    msg_class,
					    newmail.ulMessageFlags);
			break;
		}
		case fnevObjectCopied:
		case fnevObjectCreated:
		case fnevObjectDeleted:
		case fnevObjectModified: 
		case fnevObjectMoved:
		case fnevSearchComplete: {
			OBJECT_NOTIFICATION &obj = n->info.obj;
			PyObject *obArray = PyMAPIObject_FromSPropTagArray(obj.lpPropTagArray);
			if (!obArray)
				return NULL;
			ret = Py_BuildValue("k(s#is#s#s#N)",
					    n->ulEventType,
					    obj.lpEntryID, obj.cbEntryID,
					    obj.ulObjType,
					    obj.lpParentID, obj.cbParentID,
					    obj.lpOldID, obj.cbOldID,
					    obj.lpOldParentID, obj.cbOldParentID,
					    obArray);
			break;
		}
		case fnevTableModified: {
			TABLE_NOTIFICATION &tab = n->info.tab;
			ret = Py_BuildValue("k(kiNNN)",
					    n->ulEventType,
					    tab.ulTableEvent,
					    tab.hResult,
					    PyMAPIObject_FromSPropValue(&tab.propIndex),
					    PyMAPIObject_FromSPropValue(&tab.propPrior),
					    PyMAPIObject_FromSRow(&tab.row));
			break;
		}
		case fnevStatusObjectModified: {
			STATUS_OBJECT_NOTIFICATION &statobj = n->info.statobj;
			ret = Py_BuildValue("k(s#N)",
					    n->ulEventType,
					    statobj.lpEntryID, statobj.cbEntryID,
					    PyMAPIObject_FromSPropValueArray(statobj.lpPropVals, statobj.cValues));
			break;
		}
		default: {
			PyCom_LoggerWarning(NULL, "unknown MAPI notification type %x", n->ulEventType);
			ret = Py_BuildValue("k(O)", n->ulEventType, Py_None);
			break;
		}
	}
	return ret;
}

ULONG PyGMAPIAdviseSink::OnNotify(ULONG cNotif,  LPNOTIFICATION lpNotifications  )
{
	PY_GATEWAY_METHOD;
	PyObject *arg = PyList_New(cNotif);
	if (!arg)
		return MAKE_PYCOM_GATEWAY_FAILURE_CODE("OnNotify");
	ULONG i;
	for (i=0;i<cNotif;i++) {
		PyObject *sub = PyObject_FromNOTIFICATION(lpNotifications+i);
		if (!sub) {
			Py_DECREF(arg);
			return MAKE_PYCOM_GATEWAY_FAILURE_CODE("OnNotify");
		}
		PyList_SET_ITEM(arg, i, sub);
	}
	return InvokeViaPolicy("OnNotify", NULL, "(N)", arg);
}
