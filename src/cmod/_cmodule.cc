/*
 * cmod._cmod -- minimal C++ extension, written to match the idioms in
 *   https://docs.python.org/3/extending/extending.html
 *
 * Key choices:
 *   - Multi-phase initialization (PEP 489) via PyModuleDef_Init + Py_mod_exec.
 *   - m_size = 0: module holds no per-interpreter state.
 *   - Fully-qualified m_name ("cmod._cmod") so __name__/repr/pickling agree.
 *   - Declares subinterpreter + free-threading support on 3.12+/3.13+.
 */

#define PY_SSIZE_T_CLEAN
#include <Python.h>

PyDoc_STRVAR(foo_doc, "foo() -> int\n\nReturn the integer 5.");

static PyObject *
foo(PyObject *Py_UNUSED(self), PyObject *Py_UNUSED(ignored))
{
    return PyLong_FromLong(5);
}

static PyMethodDef cmod_methods[] = {
    {"foo", foo, METH_NOARGS, foo_doc},
    {NULL, NULL, 0, NULL}  // sentinel
};

static int
cmod_exec(PyObject *Py_UNUSED(module))
{
    // Stateless module: nothing to initialize. Kept as an extension point.
    return 0;
}

static PyModuleDef_Slot cmod_slots[] = {
    {Py_mod_exec, reinterpret_cast<void *>(cmod_exec)},
#if PY_VERSION_HEX >= 0x030C0000  // Python 3.12+: subinterpreter support
    {Py_mod_multiple_interpreters, Py_MOD_PER_INTERPRETER_GIL_SUPPORTED},
#endif
#if PY_VERSION_HEX >= 0x030D0000  // Python 3.13+: free-threading support
    {Py_mod_gil, Py_MOD_GIL_NOT_USED},
#endif
    {0, NULL}  // sentinel
};

PyDoc_STRVAR(module_doc, "Minimal C++ extension module demonstrating packaging.");

static struct PyModuleDef cmodule = {
    PyModuleDef_HEAD_INIT,
    "cmod._cmod",   // m_name: fully-qualified dotted name
    module_doc,     // m_doc
    0,              // m_size: stateless module
    cmod_methods,   // m_methods
    cmod_slots,     // m_slots: multi-phase init
    NULL,           // m_traverse
    NULL,           // m_clear
    NULL            // m_free
};

PyMODINIT_FUNC
PyInit__cmod(void)
{
    return PyModuleDef_Init(&cmodule);
}
