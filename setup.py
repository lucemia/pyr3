from distutils.core import setup
from distutils.extension import Extension
from Cython.Distutils import build_ext

import os
fs = ['./r3/src/%s'%k for k in os.listdir('./r3/src') if k.endswith('.c') and 'gvc' not in k and 'json' not in k]

setup(
    cmdclass = {'build_ext': build_ext},
    ext_modules = [Extension(
        "pyr3",
        ["cpyr3.pyx"] + fs + ['./r3/3rdparty/zmalloc.c'],
        libraries=["pcre"],
        include_dirs=['./r3/include', './r3', '/opt/local/include', './r3/3rdparty'],
        library_dirs=['/usr/local/lib', '/opt/local/lib'],
        extra_compile_args=['-std=c99'],
        extra_link_args=['-std=c99']
    )]
)
