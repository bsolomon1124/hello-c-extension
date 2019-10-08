#define PY_SSIZE_T_CLEAN
#include <Python.h>

#if PY_MAJOR_VERSION >= 3
#define IS_PY3K
#endif

static PyObject *
foo(PyObject *self, PyObject *Py_UNUSED(ignored)) {
    return PyLong_FromLong(5);
}

static PyMethodDef FooMethods[] = {
    {"foo",  (PyCFunction)foo,        METH_NOARGS,  "Do the foo"},
    {NULL,   NULL,     0,             NULL}
};


#if PY_MAJOR_VERSION >= 3

PyDoc_STRVAR(module_doc, "This is the module docstring.");
static struct PyModuleDef cmodule = {
    PyModuleDef_HEAD_INIT,                  // m_base
    "cmod",                                 // m_name
    module_doc,                             // m_doc
    -1,                                     // m_size
    FooMethods,                             // m_methods
    NULL,                                   // m_slots
    NULL,                                   // m_traverse
    NULL,                                   // m_clear
    NULL                                    // m_free
};

#define INITERROR return NULL

PyMODINIT_FUNC
PyInit__cmod(void)

#else
#define INITERROR return

void
init_cmod(void)
#endif  // PY_MAJOR_VERSION >= 3
{
#if PY_MAJOR_VERSION >= 3
    PyObject *m = PyModule_Create(&cmodule);
#else
    PyObject *m = Py_InitModule("cmod", FooMethods);
#endif // PY_MAJOR_VERSION >= 3

    if (m == NULL) {
        INITERROR;
    }
#if PY_MAJOR_VERSION >= 3
    return m;
#endif // PY_MAJOR_VERSION >= 3
}
