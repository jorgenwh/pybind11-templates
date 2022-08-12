#include <vector>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/numpy.h>

#include <X11/Xlib.h>
#include <X11/Xutil.h>

#include "screenshot.h"

uint8_t *XScreenshot(size_t &width, size_t &height) {
  Display *display = XOpenDisplay(NULL);
  Window root = DefaultRootWindow(display);

  XWindowAttributes attributes;
  XGetWindowAttributes(display, root, &attributes);

  width = attributes.width;
  height = attributes.height;

  size_t img_size = width*height*3;
  uint8_t *data_ptr = new uint8_t[img_size];

  XImage *image = XGetImage(display, root, 0, 0, width, height, AllPlanes, ZPixmap);

  const float cmyk_scale = 255.0f;
  const float rgb_scale = 255.0f;

  for (size_t w = 0; w < width; w++) {
    for (size_t h = 0; h < height; h++) {
      size_t i = w + h*width;

      uint8_t c = image->data[i*4];
      uint8_t m = image->data[i*4 + 1];
      uint8_t y = image->data[i*4 + 2];
      uint8_t k = image->data[i*4 + 3];

      // Convert cmyk to rgb
      // The rgb_scale - ({r,g,b}) is to invert the image. For some reason this is necessary here
      data_ptr[i*3] = rgb_scale - (rgb_scale * (1.0f - (c+k) / cmyk_scale));
      data_ptr[i*3+ 1] = rgb_scale - (rgb_scale * (1.0f - (m+k) / cmyk_scale));
      data_ptr[i*3+ 2] = rgb_scale - (rgb_scale * (1.0f - (y+k) / cmyk_scale));
    }
  }

  XDestroyImage(image);
  XCloseDisplay(display);

  return data_ptr;
}

py::array_t<uint8_t> screenshot() {
  size_t width;
  size_t height;

  uint8_t *data_ptr = XScreenshot(width, height);

  std::vector<size_t> arr_shape({height, width, 3});
  py::array_t<uint8_t> sc = py::array_t<uint8_t>(arr_shape, data_ptr);
  return sc;
}
