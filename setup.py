from distutils.core import setup
from distutils.extension import Extension

try:
    from Cython.Distutils import build_ext
except ImportError:
    use_cython = False
else:
    use_cython = True

import os
fs = ['./r3/src/%s'%k for k in os.listdir('./r3/src') if k.endswith('.c') and 'gvc' not in k and 'json' not in k]

cmdclass = {}
ext_modules = []

if False and use_cython:
    ext_modules += [
        Extension(
            "pyr3",
            ["cpyr3.pyx"] + fs + ['./r3/3rdparty/zmalloc.c'],
            libraries=["pcre"],
            include_dirs=['./r3/include', './r3', '/opt/local/include', './r3/3rdparty'],
            library_dirs=['/usr/local/lib', '/opt/local/lib'],
            extra_compile_args=['-std=c99'],
            extra_link_args=['-std=c99']
        )
    ]
    cmdclass.update({ 'build_ext': build_ext })
else:
    ext_modules += [
        Extension(
            "pyr3",
            ["cpyr3.c"] + fs + ['./r3/3rdparty/zmalloc.c'],
            libraries=["pcre"],
            include_dirs=['./r3/include', './r3', '/opt/local/include', './r3/3rdparty'],
            library_dirs=['/usr/local/lib', '/opt/local/lib'],
            extra_compile_args=['-std=c99'],
            extra_link_args=['-std=c99']
        )
    ]


setup(
    cmdclass = cmdclass,
    ext_modules = ext_modules
)
