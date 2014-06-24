try:
    import pyr3
    r = pyr3.R3Tree()
    print r
    print dir(r)
    r.insert_path(path="/bar", data='4')
    r.insert_path(path="/zoo", data='5')
    r.insert_path(path="/foo/bar", data='123')
    r.compile()
except:
    import os
    # os.remove('pyr3.so')
    raise
