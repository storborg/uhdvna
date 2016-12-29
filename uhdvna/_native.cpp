#include <uhd/types/tune_request.hpp>
#include <uhd/utils/thread_priority.hpp>
#include <uhd/utils/safe_main.hpp>
#include <uhd/usrp/multi_usrp.hpp>
#include <uhd/exception.hpp>

#include <Python.h>

typedef struct {
    PyObject_HEAD
    uhd::usrp::multi_usrp::sptr usrp;
} VNA;

static PyTypeObject VNAType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "_control.VNA",                 // tp_name
    sizeof(VNA),                    // tp_basicsize
    0,                              // tp_itemsize
    0,                              // tp_dealloc
    0,                              // tp_print
    0,                              // tp_getattr
    0,                              // tp_setattr
    0,                              // tp_reserved
    0,                              // tp_repr
    0,                              // tp_as_number
    0,                              // tp_as_sequence
    0,                              // tp_as_mapping
    0,                              // tp_hash
    0,                              // tp_call
    0,                              // tp_str
    0,                              // tp_getattro
    0,                              // tp_setattro
    0,                              // tp_as_buffer
    Py_TPFLAGS_DEFAULT,             // tp_flags
    "UHD VNA interface",            // tp_doc
};

static PyModuleDef mod = {
    PyModuleDef_HEAD_INIT,
    "_native",
    "Native module for interfacing with UHD C++ API.",
    -1,
    NULL, NULL, NULL, NULL, NULL
};

PyMODINIT_FUNC
PyInit__native(void)
{
    PyObject* m;

    VNAType.tp_new = PyType_GenericNew;
    if (PyType_Ready(&VNAType) < 0) {
        return NULL;
    }

    m = PyModule_Create(&mod);
    if (m == NULL) {
        return NULL;
    }

    Py_INCREF(&VNAType);
    PyModule_AddObject(m, "VNA", (PyObject *)&VNAType);

    return m;
}
