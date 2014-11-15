from setuptools import setup, Extension

brotli = Extension("brotli",
                    sources=[
                        "brotli.cc",
                        "brotli/enc/backward_references.cc",
                        "brotli/enc/block_splitter.cc",
                        "brotli/enc/brotli_bit_stream.cc",
                        "brotli/enc/encode.cc",
                        "brotli/enc/entropy_encode.cc",
                        "brotli/enc/histogram.cc",
                        "brotli/enc/literal_cost.cc",
                        "brotli/dec/bit_reader.c",
                        "brotli/dec/decode.c",
                        "brotli/dec/huffman.c",
                        "brotli/dec/safe_malloc.c",
                        "brotli/dec/streams.c",
                    ],
                    language="c++",
                    extra_compile_args=["-std=c++0x"])

setup(
    name="Brotli",
    version="0.1",
    url="https://github.com/khaledhosny/brotli-python",
    description="Python binding of the Brotli compression library",
    author="Khaled Hosny",
    ext_modules=[brotli],
)
