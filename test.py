def setup():
    import noddy
    r = noddy.R3Tree()
    print r
    print dir(r)
    r.insert_path(path="/bar", data='4')
    r.insert_path(path="/zoo", data='5')
    r.insert_path(path="/foo/bar", data='123')
    r.compile()
    return r

def run(r):
    return r.match('/foo/bar')

# if __name__ == "__main__":
#     import timeit
#     t = timeit.Timer('run(r)', setup='from __main__ import setup, run; r = setup()')
#     print t.timeit()

r = setup()
for i in xrange(10000):
    run(r)
