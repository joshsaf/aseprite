// ASEPRITE gui library
// Copyright (C) 2001-2012  David Capello
//
// This source file is distributed under a BSD-like license, please
// read LICENSE.txt for more information.

#ifndef UI_LAYOUT_IO_H_INCLUDED
#define UI_LAYOUT_IO_H_INCLUDED

#include <string>

namespace ui {

  class Widget;

  class LayoutIO
  {
  public:
    virtual ~LayoutIO() { }
    virtual std::string loadLayout(Widget* widget) = 0;
    virtual void saveLayout(Widget* widget, const std::string& str) = 0;
  };

} // namespace ui

#endif
