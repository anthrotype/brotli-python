#define PY_SSIZE_T_CLEAN 1
#include <Python.h>
#include "brotli/enc/encode.h"
#include "brotli/dec/decode.h"

static PyObject *BrotliError;

static int
mode_convertor(PyObject *o, brotli::BrotliParams::Mode *mode)
{
  if (!PyInt_Check(o))
    {
      PyErr_SetString(BrotliError, "Invalid mode");
      return 0;
    }

  *mode = (brotli::BrotliParams::Mode) PyInt_AsLong(o);
  if (*mode != brotli::BrotliParams::Mode::MODE_TEXT && *mode != brotli::BrotliParams::Mode::MODE_FONT)
    {
      PyErr_SetString(BrotliError, "Invalid mode");
      return 0;
    }

  return 1;
}

PyDoc_STRVAR(compress__doc__,
"compress(string[, mode[, transform]]) -- Returned compressed string.\n"
"\n"
"Optional arg mode is the compression mode, either MODE_TEXT (default) or\n"
"MODE_FONT. Optional boolean arg transform controls whether to enable\n"
"encoder transforms or not, defaults to False.");

static PyObject*
brotli_compress(PyObject *self, PyObject *args)
{
  PyObject *ReturnVal = NULL;
  uint8_t *input, *output;
  size_t length;
  brotli::BrotliParams::Mode mode = (brotli::BrotliParams::Mode) -1;
  PyObject* transform = NULL;

  if (!PyArg_ParseTuple(args,
                        "s#|O&O!:compress",
                        &input, &length,
                        &mode_convertor, &mode,
                        &PyBool_Type, &transform))
    return NULL;

  size_t output_length = 1.2 * length + 10240;
  output = new uint8_t[output_length];

  brotli::BrotliParams params;
  if (mode != -1)
    params.mode = mode;
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

PyDoc_STRVAR(decompress__doc__,
"decompress(string[, bufsize]) -- Return decompressed string."
"\n"
"Optional arg bufsize is the initial output buffer size.");

static PyObject*
brotli_decompress(PyObject *self, PyObject *args)
{
  PyObject *ReturnVal = NULL;
  uint8_t *input, *output;
  size_t length;
  size_t output_length = 0;
  if (!PyArg_ParseTuple(args, "s#|n:decompress", &input, &length, &output_length))
    return NULL;

  if (output_length <= 0)
    {
      // Just an arbitrary value, should be big enough
      output_length = 4 * length;
    }

  output = new uint8_t[output_length];

  if (BrotliDecompressBuffer(length, input, &output_length, output))
    {
      ReturnVal = PyString_FromStringAndSize((char*)output, output_length);
    }
  else
    {
      PyErr_SetString(BrotliError, "BrotliDecompressBuffer failed");
      goto error;
    }

error:
  delete[] output;

  return ReturnVal;
}

static PyMethodDef brotli_methods[] = {
  {"compress",   brotli_compress,   METH_VARARGS, compress__doc__},
  {"decompress", brotli_decompress, METH_VARARGS, decompress__doc__},
  {NULL, NULL, 0, NULL}
};

PyDoc_STRVAR(brotli_documentation,
"The functions in this module allow compression and decompression using the\n"
"Brotli library.\n"
"\n"
"compress(string[, mode, transform]) -- Compress string.\n"
"decompress(string) -- Decompresses a compressed string.\n");

PyMODINIT_FUNC
initbrotli(void)
{
  PyObject *m = Py_InitModule3("brotli", brotli_methods, brotli_documentation);

  BrotliError = PyErr_NewException((char*) "brotli.error", NULL, NULL);

  if (BrotliError != NULL)
  {
    Py_INCREF(BrotliError);
    PyModule_AddObject(m, "error", BrotliError);
  }

  PyModule_AddIntConstant(m, "MODE_TEXT", (int) brotli::BrotliParams::Mode::MODE_TEXT);
  PyModule_AddIntConstant(m, "MODE_FONT", (int) brotli::BrotliParams::Mode::MODE_FONT);
}
