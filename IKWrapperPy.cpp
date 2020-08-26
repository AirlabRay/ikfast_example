#include <Python.h>
#include <iostream>
#include "ikfast.h"

PyObject *ikfast_fk(PyObject *self, PyObject * args)
{    
    double joints[6]={0,};
    if (PyArg_ParseTuple(args,"dddddd",&joints[0],&joints[1],&joints[2],&joints[3],&joints[4],&joints[5]))
    {
      double* position = fk_euler(joints);
      return(Py_BuildValue("[dddddd]",position[0],position[1],position[2],position[3],position[4],position[5])); 
    }PyErr_Clear();
}    

PyObject *ikfast_ik(PyObject *self, PyObject * args)
{
    double points[6]={0,};
    int sol = 0;
    if (PyArg_ParseTuple(args,"ddddddi",&points[0],&points[1],&points[2],&points[3],&points[4],&points[5],&sol))
    {
      double* solution = ik_euler(points,sol);
      return(Py_BuildValue("[ddddddd]",solution[0],solution[1],solution[2],solution[3],solution[4],solution[5],solution[6])); 
    }PyErr_Clear();
}

static PyMethodDef callMethods[] =
{    
     {"fk", ikfast_fk, METH_VARARGS,"fk: j1~j6"},
     {"ik", ikfast_ik, METH_VARARGS,"ik: x,y,z,rx,ry,rz,sol"},
     {NULL,NULL,0,NULL}
};

PyMODINIT_FUNC initikfast(void)
{    
   Py_InitModule("ikfast",callMethods); 
}
