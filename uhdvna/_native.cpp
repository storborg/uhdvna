#include <uhd/types/tune_request.hpp>
#include <uhd/utils/thread_priority.hpp>
#include <uhd/utils/safe_main.hpp>
#include <uhd/usrp/multi_usrp.hpp>
#include <uhd/exception.hpp>

#include <iostream>

#include <Python.h>
#include <structmember.h>

typedef struct {
    PyObject_HEAD
    uhd::usrp::multi_usrp::sptr usrp;
} VNA;

static void
VNA_dealloc(VNA* self)
{
    Py_TYPE(self)->tp_free((PyObject*)self);
    std::cout << "VNA_dealloc" << std::endl;
}

static PyObject *
VNA_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    VNA *self;
    self = (VNA *)type->tp_alloc(type, 0);
    if (self != NULL) {
        std::cout << "VNA_new" << std::endl;
    }

    return (PyObject *)self;
}

static int
VNA_init(VNA *self, PyObject *args, PyObject *kwds)
{
    std::cout << "VNA_init" << std::endl;

    const char *rawargs;

    static char *kwlist[] = {"uhdargs", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "s", kwlist,
                                     &rawargs))
        return -1;

    std::string uhdargs = rawargs;
    self->usrp = uhd::usrp::multi_usrp::make(uhdargs);

    std::cout << "Setting clock source to internal..." << std::endl;
    self->usrp->set_clock_source("internal");

    std::cout << "Setting sample rates..." << std::endl;
    self->usrp->set_rx_rate(1e6);
    self->usrp->set_tx_rate(1e6);

    std::cout << "Setting RF gains..." << std::endl;
    self->usrp->set_rx_gain(10);
    self->usrp->set_tx_gain(10);

    std::cout << "Ready." << std::endl;

    return 0;
}

static PyMemberDef VNA_members[] = {
    {NULL}  // Sentinel
};

static PyObject *
VNA_hello(VNA* self)
{
    return PyUnicode_FromFormat("Hello!");
}

static PyMethodDef VNA_methods[] = {
    {"hello", (PyCFunction)VNA_hello, METH_NOARGS, "Say hello."},
    {NULL}  // Sentinel
};

static PyTypeObject VNAType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "_control.VNA",                 // tp_name
    sizeof(VNA),                    // tp_basicsize
    0,                              // tp_itemsize
    (destructor)VNA_dealloc,        // tp_dealloc
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
    Py_TPFLAGS_DEFAULT |
        Py_TPFLAGS_BASETYPE,        // tp_flags
    "UHD VNA interface",            // tp_doc
    0,                              // tp_traverse
    0,                              // tp_clear
    0,                              // tp_richcompare
    0,                              // tp_weaklistoffset
    0,                              // tp_iter
    0,                              // tp_iternext
    VNA_methods,                    // tp_methods
    VNA_members,                    // tp_members
    0,                              // tp_getset
    0,                              // tp_base
    0,                              // tp_dict
    0,                              // tp_descr_get
    0,                              // tp_descr_set
    0,                              // tp_dictoffset
    (initproc)VNA_init,             // tp_init
    0,                              // tp_alloc
    VNA_new,                        // tp_new
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
