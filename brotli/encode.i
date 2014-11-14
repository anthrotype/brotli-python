%module encode
%feature ("kwargs");

%{
#include "brotli/enc/encode.h"
%}

%include "brotli/enc/encode.h"
