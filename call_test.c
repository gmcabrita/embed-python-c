// A simple program to test calling Python from C
#include <Python.h>
#define PYERR_IF(boolean, body) if(boolean){body}else{PyErr_Print();}

int main(void) {
    PyObject *name, *module, *func;//, *dict;

    // this initializes the embedded python interpreter
    Py_Initialize();
    PySys_SetPath("");

    name = PyString_FromString("call");

    // load the module
    module = PyImport_Import(name);

    PYERR_IF(module != NULL,
        // borrowing dictionary of references from the python module
        //dict = PyModule_GetDict(module);

        // borrowing the function from the python module
        //func = PyDict_GetItemString(dict, "test");
        func = PyObject_GetAttrString(module, "test");
        PYERR_IF(PyCallable_Check(func),
            PyObject *x = PyObject_CallObject(func, NULL);
            printf("%d\n", 5 + (int) PyLong_AsLong(x));
            Py_DECREF(x);
        );
        Py_DECREF(module);
    );
    Py_DECREF(name);

    // close the embedded python interpreter
    Py_Finalize();

    return 0;
}