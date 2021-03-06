// SHE library
// Copyright (C) 2012  David Capello
//
// This source file is distributed under a BSD-like license, please
// read LICENSE.txt for more information.

#ifndef SHE_DISPLAY_H_INCLUDED
#define SHE_DISPLAY_H_INCLUDED

namespace she {

  class Surface;
  class NotDisposableSurface;

  // A display or window to show graphics.
  class Display {
  public:
    virtual ~Display() { }
    virtual void dispose() = 0;

    // Returns the real and current display's size (without scale applied).
    virtual int width() const = 0;
    virtual int height() const = 0;

    // Returns the display when it was not maximized.
    virtual int originalWidth() const = 0;
    virtual int originalHeight() const = 0;

    // Changes the scale (each pixel will be SCALExSCALE in the screen).
    // The available surface size will be (Display::width() / scale,
    //                                     Display::height() / scale)
    virtual void setScale(int scale) = 0;

    // Returns the main surface to draw into this display.
    // You must not dispose this surface.
    virtual NotDisposableSurface* getSurface() = 0;

    // Flips all graphics in the surface to the real display.  Returns
    // false if the flip couldn't be done because the display was
    // resized.
    virtual bool flip() = 0;

    virtual void maximize() = 0;
    virtual bool isMaximized() const = 0;

    // Returns the HWND on Windows.
    virtual void* nativeHandle() = 0;
  };

} // namespace she

#endif
