pyr3
====

a python wrapper for r3 https://github.com/c9s/r3

### Usage

```python
import pyr3
r = pyr3.R3Tree()
print r
print dir(r)
# data can be anything
r.insert_path(path="/bar", data='4')
r.insert_path(path="/zoo", data='5')
r.insert_path(path="/foo/bar", data='123')
r.compile()

print r.match('/foo/bar')
```

### Build

    git clone https://github.com/lucemia/pyr3
    git submodule init
    git submodule update
    cd ./r3
    ./autogen.sh
    ./configure
    cd ..
    python setup.py build_ext --inplace

