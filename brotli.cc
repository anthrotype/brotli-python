#define PY_SSIZE_T_CLEAN 1
#include <Python.h>
#include "brotli/enc/encode.h"

static PyObject *BrotliError;

static PyObject * brotli_compress(PyObject * self, PyObject * args)
{
  PyObject *ReturnVal = NULL;
  uint8_t *input, *output;
  size_t length;
  int mode = -1;
  PyObject* transform = NULL;

  if (!PyArg_ParseTuple(args, "s#|iO!:compress", &input, &length, &mode, &PyBool_Type, &transform))
    return NULL;

  size_t output_length = length * 2;
  output = new uint8_t[output_length];

  brotli::BrotliParams params;
  if (mode != -1)
    params.mode = (brotli::BrotliParams::Mode) mode;
  if (transform)
    params.enable_transforms = PyObject_IsTrue(transform);

  if (brotli::BrotliCompressBuffer(params, length, input, &output_length, output))
    {
      ReturnVal = PyString_FromStringAndSize((char*)output, output_length);
    }
  else
    {
      PyErr_SetString(BrotliError, "BrotliCompressBuffer failed");
      goto error;
    }

error:
  delete[] output;

  return ReturnVal;
}

static PyObject * brotli_decompress(PyObject * self, PyObject * args)
{
  PyErr_SetString(PyExc_NotImplementedError, "brotli.decompress");
  return NULL;
}

static PyMethodDef brotli_methods[] = {
  {"compress", brotli_compress, METH_VARARGS, ""},
  {"decompress", brotli_decompress, METH_VARARGS, ""},
  {NULL, NULL, 0, NULL}
};

PyMODINIT_FUNC
initbrotli(void)
{
  PyObject *m = Py_InitModule("brotli", brotli_methods);

  BrotliError = PyErr_NewException((char*) "brotli.error", NULL, NULL);

  if (BrotliError != NULL) {
    Py_INCREF(BrotliError);
    PyModule_AddObject(m, "error", BrotliError);
  }
}
