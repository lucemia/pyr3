#include <Python.h>
#include "structmember.h"
#include "r3.h"
#include "r3_str.h"
#include "str_array.h"

typedef struct link_data{
    PyObject* data;
    struct link_data* link;
} LINK_NODE;

typedef struct {
    PyObject_HEAD
    node *root;
    LINK_NODE* datas;
} R3Tree;


LINK_NODE *new_node(PyObject* data){
   LINK_NODE *node;
   node=(LINK_NODE *) malloc(sizeof(LINK_NODE));/*<stdlib.h>*/

   // 記憶體不足
   if(node == NULL){ return NULL;}

   node->data=data;
   node->link=NULL;
   return node;
}

/* 加入新的資料於最後 */
LINK_NODE *push_node(LINK_NODE *list, PyObject* data){
   /*產生新節點*/
   LINK_NODE *node=new_node(data);

   // 加入第一個新節點
   if(list==NULL){
       list=node;
   } else{
       LINK_NODE *p=list;
       // 取得最後一個節點
       while(p->link!=NULL){p=p->link;}
       p->link=node;
   }
   return list;
}


static void clean_data(R3Tree* tree) {
    LINK_NODE *node = tree->datas, *next_node=NULL;

    while (node!=NULL) {
        Py_XDECREF(node->data);
        next_node = node->link;
        free(node);
        node = next_node;
    }
    tree->datas = NULL;
}

static void
R3Tree_dealloc(R3Tree* self)
{
    int i=0;
    if(self->root != NULL) {
        clean_data(self);
        r3_tree_free(self->root);
    }
    self->root = NULL;
    self->datas = NULL;
    self->ob_type->tp_free((PyObject*)self);
}

static PyObject *
R3Tree_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    R3Tree *self;

    self = (R3Tree *)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->root = r3_tree_create(255);
        self->datas = new_node(NULL);
    }

    return (PyObject *)self;
}


static int
R3Tree_init(R3Tree *self, PyObject *args, PyObject *kwds)
{
    // TODO: may need to add init here
    return 0;
}

static PyObject *
R3Tree_insert_path(R3Tree* self, PyObject *args, PyObject *kwds)
{
  //http://stackoverflow.com/questions/9896032/how-to-get-a-char-from-a-pyobject-which-points-to-a-string
    PyObject* path = NULL, *data = NULL;

    static char *kwlist[] = {"path", "data", NULL};

    if (! PyArg_ParseTupleAndKeywords(args, kwds, "|OO", kwlist,
                                      &path, &data))
        return NULL ;

    if (path == NULL) {
        PyErr_SetString(PyExc_AttributeError, "path");
        return NULL;
    }
    if (data == NULL) {
        PyErr_SetString(PyExc_AttributeError, "data");
        return NULL;
    }

    Py_XINCREF(data);
    push_node(self->datas, data);
    PyObject* objectsRepresentation = PyObject_Repr(path);
    const char* s = PyString_AsString(objectsRepresentation);

    r3_tree_insert_path(self->root, s, data);

    // return None
    // http://code.activestate.com/recipes/52309-to-return-none-from-your-python-callable-c-functio/
    return Py_None;
}

static PyObject*
R3Tree_compile(R3Tree* self) {
    char *errstr = NULL;
    int err = r3_tree_compile(self->root, &errstr);
    return Py_None;
}

static PyObject*
R3Tree_match(R3Tree* self, PyObject *args, PyObject *kwds)
{
    PyObject* path = NULL;

    static char *kwlist[] = {"path", NULL};

    if (! PyArg_ParseTupleAndKeywords(args, kwds, "|O", kwlist,
                                      &path))
        return NULL ;

    if(path == NULL) {
        PyErr_SetString(PyExc_AttributeError, "path");
        return NULL;
    }

    PyObject* objectsRepresentation = PyObject_Repr(path);
    const char* s = PyString_AsString(objectsRepresentation);


    node* match_node = r3_tree_match(self->root, s, NULL);
    if(match_node != NULL) {
        return match_node->data;
    }

    return Py_None;
}

// https://docs.python.org/2/c-api/structures.html#PyMethodDef
static PyMethodDef R3Tree_methods[] = {
    {"insert_path", (PyCFunction)R3Tree_insert_path, METH_KEYWORDS,
     "Return the name, combining the first and last name"},
     {"compile", (PyCFunction)R3Tree_compile, METH_NOARGS,
    "compile"},
    {"match", (PyCFunction)R3Tree_match, METH_KEYWORDS,
    "match"},
    {NULL}  /* Sentinel */
};


static PyTypeObject r3_TreeType = {
    PyObject_HEAD_INIT(NULL)
    0,                         /*ob_size*/
    "pyr3.R3Tree",             /*tp_name*/
    sizeof(R3Tree), /*tp_basicsize*/
    0,                         /*tp_itemsize*/
    (destructor)R3Tree_dealloc,/*tp_dealloc*/
    0,                         /*tp_print*/
    0,                         /*tp_getattr*/
    0,                         /*tp_setattr*/
    0,                         /*tp_compare*/
    0,                         /*tp_repr*/
    0,                         /*tp_as_number*/
    0,                         /*tp_as_sequence*/
    0,                         /*tp_as_mapping*/
    0,                         /*tp_hash */
    0,                         /*tp_call*/
    0,                         /*tp_str*/
    0,                         /*tp_getattro*/
    0,                         /*tp_setattro*/
    0,                         /*tp_as_buffer*/
    Py_TPFLAGS_DEFAULT,        /*tp_flags*/
    "R3 objects",           /* tp_doc */
    0,                     /* tp_traverse */
    0,                     /* tp_clear */
    0,                     /* tp_richcompare */
    0,                     /* tp_weaklistoffset */
    0,                     /* tp_iter */
    0,                     /* tp_iternext */
    R3Tree_methods,             /* tp_methods */
    0,             /* tp_members */
    0,                         /* tp_getset */
    0,                         /* tp_base */
    0,                         /* tp_dict */
    0,                         /* tp_descr_get */
    0,                         /* tp_descr_set */
    0,                         /* tp_dictoffset */
    (initproc)R3Tree_init,      /* tp_init */
    0,                         /* tp_alloc */
    R3Tree_new,                 /* tp_new */
};

static PyMethodDef r3_methods[] = {
    {NULL}  /* Sentinel */
};

#ifndef PyMODINIT_FUNC  /* declarations for DLL import/export */
#define PyMODINIT_FUNC void
#endif
PyMODINIT_FUNC
initpyr3(void)
{
    PyObject* m;
    if (PyType_Ready(&r3_TreeType) < 0)
        return;

    m = Py_InitModule3("pyr3", r3_methods,
                       "Python wrapper for r3");

    Py_INCREF(&r3_TreeType);
    PyModule_AddObject(m, "R3Tree", (PyObject *)&r3_TreeType);
}
