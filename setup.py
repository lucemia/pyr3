from distutils.core import setup, Extension
setup(name="pyr3", version="1.0",
    ext_modules=[Extension(
    "pyr3",
    ["pyr3.c"],
    libraries=["pcre","r3"],
    include_dirs=['./r3/include', './r3', '/opt/local/include'],
    library_dirs=['/usr/local/lib', '/opt/local/lib'],
    runtime_library_dirs=['/usr/local/lib']
)])

try:
    import setup_test
except:
    pass
