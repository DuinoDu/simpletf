#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "simpletf/simpletf.hpp"

namespace py = pybind11;

namespace simpletf {

PYBIND11_MODULE(_simpletf, m)
{
  m.doc() = "Python Bindings for simpletf";
  m.def("add_one", &add_one, "Increments an integer value");
}

} // namespace simpletf
