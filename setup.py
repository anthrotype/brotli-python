from setuptools import setup, Extension
from Cython.Build import cythonize

encode = Extension("brotli.encode",
                    sources=[
                        "brotli/encode.cc",
                        "brotli/brotli/enc/backward_references.cc",
                        "brotli/brotli/enc/block_splitter.cc",
                        "brotli/brotli/enc/brotli_bit_stream.cc",
                        "brotli/brotli/enc/encode.cc",
                        "brotli/brotli/enc/entropy_encode.cc",
                        "brotli/brotli/enc/histogram.cc",
                        "brotli/brotli/enc/literal_cost.cc",
                    ],
                    language="c++",
                    extra_compile_args=["-std=c++0x"])

decode = Extension("brotli.decode",
                    sources=[
                        "brotli/decode.c",
                        "brotli/brotli/dec/bit_reader.c",
                        "brotli/brotli/dec/decode.c",
                        "brotli/brotli/dec/huffman.c",
                        "brotli/brotli/dec/safe_malloc.c",
                        "brotli/brotli/dec/streams.c",
                    ])

setup(
    name="Brotli",
    version="0.1",
    url="https://github.com/khaledhosny/brotli-python",
    description="Python binding of the Brotli compression library",
    author="Khaled Hosny",
    packages=["brotli"],
    ext_modules=[encode, decode],
)
