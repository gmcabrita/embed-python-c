// A simple program to test calling Python from C
#include <Python.h>
#include <assert.h>
#define PYERR_IF(boolean, body) if(boolean){body}else{PyErr_Print();}
#define ANSI_GREEN   "\x1b[32m"
#define ANSI_RESET   "\x1b[0m"

int test_return_int(int n) {
    return n * 5;
}

int main(void) {
    PyObject *name, *module, *func, *args, *val;//, *dict;

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

        printf("Running test_return_int... ");
        func = PyObject_GetAttrString(module, "test_return_int");
        PYERR_IF(PyCallable_Check(func),
            PyObject *x = PyObject_CallObject(func, NULL);
            assert(5 + (int) PyLong_AsLong(x) == 10);
            Py_DECREF(x);
        );
        printf(ANSI_GREEN "\tOK\n" ANSI_RESET);

        printf("Running test_return_string... ");
        func = PyObject_GetAttrString(module, "test_return_string");
        PYERR_IF(PyCallable_Check(func),
            PyObject *x = PyObject_CallObject(func, NULL);
            assert(!strcmp(PyString_AsString(x), "UROP"));
            Py_DECREF(x);
        );
        printf(ANSI_GREEN "\tOK\n" ANSI_RESET);


        // testing argumento passing into python
        printf("Running test_pass_integer... ");
        args = PyTuple_New(1);
        val = PyLong_FromLong(5);
        PyTuple_SetItem(args, 0, val);
        func = PyObject_GetAttrString(module, "test_pass_integer");
        PYERR_IF(PyCallable_Check(func),
            PyObject *x = PyObject_CallObject(func, args);
            assert(PyLong_AsLong(x) == 6);
            Py_DECREF(x);
        );
        Py_DECREF(val);
        Py_DECREF(args);
        printf(ANSI_GREEN "\tOK\n" ANSI_RESET);

        // testing bidirectionality
        printf("Running test_call_c... ");
        func = PyObject_GetAttrString(module, "test_call_c");
        PYERR_IF(PyCallable_Check(func),
            PyObject *x = PyObject_CallObject(func, NULL);
            assert((int) PyLong_AsLong(x) == test_return_int(5) * 5);
            Py_DECREF(x);
        );
        printf(ANSI_GREEN "\t\tOK\n" ANSI_RESET);

        Py_DECREF(module);
    );
    Py_DECREF(name);

    // close the embedded python interpreter
    Py_Finalize();
    printf("All tests ran successfully.\n");

    return 0;
}