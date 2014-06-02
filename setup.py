from distutils.core import setup, Extension
setup(name="pyr3", version="1.0",
    ext_modules=[Extension(
    "pyr3",
    ["pyr3.c"],
    libraries=["pcre","r3"],
    include_dirs=['./r3/include', './r3'],
    library_dirs=['/usr/local/lib'],
    runtime_library_dirs=['/usr/local/lib']
)])

try:
    import pyr3
    r = pyr3.R3Tree()
    print r
    print dir(r)
    r.insert_path(path="/bar", data=0)
    r.insert_path(path="/zoo", data=1)
    r.insert_path(path="/foo/bar", data='123')
    r.compile()

    print r.match('/foo/bar')
except:
    raise
finally:
    import os
    os.remove('pyr3.so')
