from distutils.core import setup, Extension
from distutils.command.build_ext import build_ext

class BuildExt(build_ext):
    def get_source_files(self):
        filenames = build_ext.get_source_files(self)
        for ext in self.extensions:
            filenames.extend(ext.depends)
        return filenames

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
                    depends=[
                        "brotli/enc/backward_references.h",
                        "brotli/enc/bit_cost.h",
                        "brotli/enc/block_splitter.h",
                        "brotli/enc/brotli_bit_stream.h",
                        "brotli/enc/cluster.h",
                        "brotli/enc/command.h",
                        "brotli/enc/context.h",
                        "brotli/enc/dictionary.h",
                        "brotli/enc/encode.h",
                        "brotli/enc/entropy_encode.h",
                        "brotli/enc/fast_log.h",
                        "brotli/enc/find_match_length.h",
                        "brotli/enc/hash.h",
                        "brotli/enc/histogram.h",
                        "brotli/enc/literal_cost.h",
                        "brotli/enc/port.h",
                        "brotli/enc/prefix.h",
                        "brotli/enc/ringbuffer.h",
                        "brotli/enc/static_dict.h",
                        "brotli/enc/transform.h",
                        "brotli/enc/write_bits.h",
                        "brotli/dec/bit_reader.h",
                        "brotli/dec/context.h",
                        "brotli/dec/decode.h",
                        "brotli/dec/dictionary.h",
                        "brotli/dec/huffman.h",
                        "brotli/dec/prefix.h",
                        "brotli/dec/safe_malloc.h",
                        "brotli/dec/streams.h",
                        "brotli/dec/transform.h",
                        "brotli/dec/types.h",
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
    cmdclass={'build_ext': BuildExt},
)
