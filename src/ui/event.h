// ASEPRITE gui library
// Copyright (C) 2001-2012  David Capello
//
// This source file is distributed under a BSD-like license, please
// read LICENSE.txt for more information.

#ifndef UI_EVENT_H_INCLUDED
#define UI_EVENT_H_INCLUDED

namespace ui {

  class Component;

  // Base class for every kind of event.
  class Event
  {
  public:
    // Creates a new event specifying that it was generated from the
    // source component.
    Event(Component* source);
    virtual ~Event();

    // Returns the component which generated the event.
    Component* getSource();

  private:
    // The component which generates the event.
    Component* m_source;
  };

} // namespace ui

#endif
