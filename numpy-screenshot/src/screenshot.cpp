#include <vector>
#include <iostream>
#include <assert.h>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/numpy.h>

#include <X11/Xlib.h>
#include <X11/Xutil.h>

#include "screenshot.h"

uint8_t *XScreenshot(size_t &width, size_t &height, size_t channels, float scale_factor) {
  Display *display = XOpenDisplay(NULL);
  Window root = DefaultRootWindow(display);

  XWindowAttributes attributes;
  XGetWindowAttributes(display, root, &attributes);

  width = attributes.width;
  height = attributes.height;

  size_t downsampled_width = width * scale_factor;
  size_t downsampled_height = height * scale_factor;

  float skip_pixels = (float)width / (float)downsampled_width;

  size_t img_size = downsampled_width*downsampled_height*channels;
  uint8_t *data_ptr = new uint8_t[img_size];

  XImage *image = XGetImage(display, root, 0, 0, width, height, AllPlanes, ZPixmap);

  const float cmyk_scale = 255.0f;
  const float rgb_scale = 255.0f;

  size_t ow = 0;
  size_t oh = 0;
  for (float iw = 0; iw < width; iw += skip_pixels) {
    for (float ih = 0; ih < height; ih += skip_pixels) {
      size_t ii = iw + ih*width;
      size_t oi = ow + oh*downsampled_width;

      uint8_t c = image->data[ii*4];
      uint8_t m = image->data[ii*4 + 1];
      uint8_t y = image->data[ii*4 + 2];
      uint8_t k = image->data[ii*4 + 3];

      // Convert cmyk to rgb
      // The rgb_scale - ({r,g,b}) is to invert the image. For some reason this is necessary here
      data_ptr[oi*3] = rgb_scale - (rgb_scale * (1.0f - (c+k) / cmyk_scale));
      data_ptr[oi*3 + 1] = rgb_scale - (rgb_scale * (1.0f - (m+k) / cmyk_scale));
      data_ptr[oi*3 + 2] = rgb_scale - (rgb_scale * (1.0f - (y+k) / cmyk_scale));

      oh++;
    }
    ow++;
  }

  /*size_t ow = 0;
  size_t oh = 0;
  for (size_t iw = 0; iw < width; iw+=skip_pixels) {
    for (size_t ih = 0; ih < height; ih+=skip_pixels) {
      //size_t ii = (w*skip_pixels) + (h*skip_pixels)*width;

      //int ii = ((float)w*skip_pixels) + ((float)h*skip_pixels)*width;
      //int oi = w + h*downsampled_width;

      size_t ii = iw + ih*width;
      size_t oi = ow + oh*downsampled_width;

      assert(ii*4+3 < width*height*4);
      uint8_t c = image->data[ii*4];
      uint8_t m = image->data[ii*4 + 1];
      uint8_t y = image->data[ii*4 + 2];
      uint8_t k = image->data[ii*4 + 3];

      assert(oi*3+2 < img_size);
      // Convert cmyk to rgb
      // The rgb_scale - ({r,g,b}) is to invert the image. For some reason this is necessary here
      data_ptr[oi*3] = rgb_scale - (rgb_scale * (1.0f - (c+k) / cmyk_scale));
      data_ptr[oi*3 + 1] = rgb_scale - (rgb_scale * (1.0f - (m+k) / cmyk_scale));
      data_ptr[oi*3 + 2] = rgb_scale - (rgb_scale * (1.0f - (y+k) / cmyk_scale));

      oh++;
    }
    ow++;
  }*/

  XDestroyImage(image);
  XCloseDisplay(display);

  width = downsampled_width;
  height = downsampled_height;

  return data_ptr;
}

py::array_t<uint8_t> screenshot(float scale_factor) {
  // scale_factor cannot be larger than 1
  scale_factor = (scale_factor > 1.0f) ? 1.0f : scale_factor;

  size_t width;
  size_t height;
  size_t channels = 3;

  uint8_t *data_ptr = XScreenshot(width, height, channels, scale_factor);
  std::vector<size_t> arr_shape({height, width, channels});

  py::array_t<uint8_t> sc = py::array_t<uint8_t>(arr_shape, data_ptr);
  return sc;
}
