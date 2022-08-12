#ifndef SCREENSHOT_H_
#define SCREENSHOT_H_

#include <vector>

#include <X11/Xlib.h>
#include <X11/Xutil.h>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/numpy.h>

namespace py = pybind11;

py::array_t<uint8_t> screenshot();

#endif // SCREENSHOT_H_
