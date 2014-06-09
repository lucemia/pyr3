cimport cpyr3

cdef class R3Tree:
    cdef cpyr3.node* root
    def __cinit__(self, cap=10):
        self.root = cpyr3.r3_tree_create(cap)

    cpdef insert_path(self, path, data):
        cpyr3.r3_tree_insert_path(self.root, path, <void*>data)

    cpdef compile(self):
        cpyr3.r3_tree_compile(self.root, NULL)

    cpdef match(self, path):
        m = cpyr3.r3_tree_match(self.root, path, NULL)

        if m:
            return <object><void*>(m.data)

    def __dealloc__(self):
        if self.root is not NULL:
            cpyr3.r3_tree_free(self.root)
