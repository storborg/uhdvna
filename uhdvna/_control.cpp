#include <uhd/types/tune_request.hpp>
#include <uhd/utils/thread_priority.hpp>
#include <uhd/utils/safe_main.hpp>
#include <uhd/usrp/multi_usrp.hpp>
#include <uhd/exception.hpp>

#include <Python.h>


static PyObject *
control_hello(PyObject *self, PyObject *args)
{
    return PyLong_FromLong(42);
}

static PyObject *
control_uhdtest(PyObject *self, PyObject *args)
{
    std::string uhdargs = "";

    double rate = 1e6;
    double freq = 2.45e9;
    double gain = 10;
    double bw = 1e6;

    uhd::usrp::multi_usrp::sptr usrp = uhd::usrp::multi_usrp::make(uhdargs);

    usrp->set_clock_source("internal");
    usrp->set_rx_rate(rate);
    uhd::tune_request_t tune_request(freq);
    usrp->set_rx_freq(tune_request);
    usrp->set_rx_gain(gain);
    usrp->set_rx_bandwidth(bw);

    return PyLong_FromLong(0);
}

static PyMethodDef module_methods[] = {
    {"hello", control_hello, METH_VARARGS, "Hey."},
    {"uhdtest", control_uhdtest, METH_VARARGS, "Testing."},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef mod = {
    PyModuleDef_HEAD_INIT,
    "control",
    NULL,
    -1,
    module_methods
};

PyMODINIT_FUNC
PyInit__control(void)
{
    return PyModule_Create(&mod);
}
