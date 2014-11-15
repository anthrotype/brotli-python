#include <Python.h>

static PyMethodDef decode_methods[] = {
  {NULL, NULL, 0, NULL}
};

PyMODINIT_FUNC
initdecode(void)
{
  (void) Py_InitModule("decode", decode_methods);
}
