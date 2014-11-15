import numpy
cimport numpy

from libc.stdint cimport uint8_t
from libcpp cimport bool

cdef extern from "brotli/enc/encode.h" namespace "brotli":
    ctypedef enum BrotliParams_Mode "brotli::BrotliParams::Mode":
        MODE_TEXT "brotli::BrotliParams::Mode::MODE_TEXT"
        MODE_FONT "brotli::BrotliParams::Mode::MODE_FONT"

    cdef cppclass BrotliParams:
        BrotliParams()
        BrotliParams_Mode mode
        bool enable_transforms

    int BrotliCompressBuffer(BrotliParams, size_t, const uint8_t*, size_t*, uint8_t*)


cdef class Params:
    cdef BrotliParams* params

    def __init__(self, mode = None, enable_transforms = None):
        self.params = new BrotliParams()
        if mode is not None:
            self.params.mode = mode
        if enable_transforms is not None:
            self.params.enable_transforms = enable_transforms
    def obj(self):
        return self.params

def CompressBuffer(params, buf):
    size = len(buf)
    out_buf = numpy.ndarray(shape=[size], dtype=int)
    in_buf = numpy.ndarray(shape=[size], dtype=int)
    print buf, size
    #cdef size_t* out_size = size
    print dir(params)
    print params
    #BrotliCompressBuffer(params.obj, size, in_buf.data, out_size, out_buf.data)
