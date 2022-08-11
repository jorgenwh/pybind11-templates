#include <vector>
#include <iostream>
#include <assert.h>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/numpy.h>

#include <X11/Xlib.h>
#include <X11/Xutil.h>

#include "screenshot.h"

static void fooshot(uint8_t *data_ptr, size_t width, size_t height, size_t channels) {
  Display *display = XOpenDisplay(NULL);
  Window root = DefaultRootWindow(display);

  XWindowAttributes attributes;
  XGetWindowAttributes(display, root, &attributes);

  size_t w = attributes.width;
  size_t h = attributes.height;

  assert (w == width);
  assert (h == height);

  XImage *image = XGetImage(display, root, 0, 0, width, height, AllPlanes, ZPixmap);

  int bits_per_pixel = image->bits_per_pixel;
  //assert(bits_per_pixel == channels*8);

  for (size_t x = 0; x < width; x++) {
    for (size_t y = 0; y < height; y++) {
      unsigned long pixel = XGetPixel(image, x, y);

      unsigned char blue = pixel & image->blue_mask;
      unsigned char green = (pixel & image->green_mask) >> 8;
      unsigned char red = (pixel & image->red_mask) >> 16;

      data_ptr[(x + width*y)*3] = red;
      data_ptr[(x + width*y)*3 + 1] = green;
      data_ptr[(x + width*y)*3 + 2] = blue;
    }
  }

  XDestroyImage(image);
  XCloseDisplay(display);
}

py::array_t<uint8_t> screenshot() {
  size_t width = 3440;
  size_t height = 1440;
  size_t channels = 1;

  size_t size = width*height*channels;
  uint8_t *data = new uint8_t[size];

  std::vector<size_t> shape({height, width, channels});

  fooshot(data, width, height, channels);

  py::array_t<uint8_t> ret = py::array_t<uint8_t>(shape, data);
  return ret;
}
