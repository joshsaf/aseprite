// ASEPRITE gui library
// Copyright (C) 2001-2012  David Capello
//
// This source file is distributed under a BSD-like license, please
// read LICENSE.txt for more information.

#ifndef UI_PREFERRED_SIZE_EVENT_H_INCLUDED
#define UI_PREFERRED_SIZE_EVENT_H_INCLUDED

#include "gfx/size.h"
#include "ui/event.h"

namespace ui {

  class Widget;

  class PreferredSizeEvent : public Event
  {
    gfx::Size m_fitIn;
    gfx::Size m_preferredSize;

  public:

    PreferredSizeEvent(Widget* source, const gfx::Size& fitIn);
    virtual ~PreferredSizeEvent();

    gfx::Size fitInSize() const;
    int fitInWidth() const;
    int fitInHeight() const;

    gfx::Size getPreferredSize() const;
    void setPreferredSize(const gfx::Size& preferredSize);
    void setPreferredSize(int w, int h);

  };

} // namespace ui

#endif
