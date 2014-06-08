
cdef extern from "r3.h":
    ctypedef struct node:
        pass

    ctypedef struct edge:
        pass

    ctypedef struct match_entry:
        pass

    node * r3_tree_create(int cap)
    void r3_tree_free(node * tree)
    node * r3_tree_insert_path(node *tree, const char *path, void * data)

    int r3_tree_compile(node *n, char** errstr)
    node * r3_tree_match(const node * n, const char * path, match_entry * entry)




