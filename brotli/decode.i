%module decode
%feature ("kwargs");

%{
#include "brotli/dec/decode.h"
%}

%include "brotli/dec/decode.h"
