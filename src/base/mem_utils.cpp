// ASEPRITE base library
// Copyright (C) 2001-2012  David Capello
//
// This source file is distributed under a BSD-like license, please
// read LICENSE.txt for more information.

#include "config.h"

#include <string>
#include <cstdio>

using namespace std;

string get_pretty_memory_size(size_t memsize)
{
  char buf[256];

  if (memsize < 1000) {
    sprintf(buf, "%lu bytes", memsize);
  }
  else if (memsize < 1000*1000) {
    sprintf(buf, "%0.1fK", memsize/1024.0f);
  }
  else {
    sprintf(buf, "%0.1fM", memsize/(1024.0f*1024.0f));
  }

  return buf;
}
