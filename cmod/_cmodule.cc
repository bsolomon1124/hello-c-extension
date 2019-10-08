#define PY_SSIZE_T_CLEAN
#include <Python.h>

static PyObject *
foo(PyObject *self, PyObject *Py_UNUSED(ignored)) {
    return PyLong_FromLong(5);
}

static PyMethodDef FooMethods[] = {
    {"foo",  (PyCFunction)foo,        METH_NOARGS,  "Do the foo"},
    {NULL,   NULL,     0,             NULL}
};

PyDoc_STRVAR(module_doc, "This is the module docstring.");
static struct PyModuleDef cmodule = {
    PyModuleDef_HEAD_INIT,
    "cmod",
    module_doc,
    -1,
    FooMethods,
    NULL,
    NULL,
    NULL,
    NULL
};

PyMODINIT_FUNC
PyInit__cmod(void) {
    PyObject* m = PyModule_Create(&cmodule);
    if (m == NULL) {
        return NULL;
    }
    return m;
}