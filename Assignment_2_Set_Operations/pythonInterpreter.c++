include <Python.h>

int main() {
    Py_Initialize();

    // Execute Python code
    PyRun_SimpleString("print('Hello from Python!')");
    if (PyErr_Occurred()) {
        PyErr_Print();
    }
    // Finalize Python interpreter
    Py_Finalize();

    return 0;
} 