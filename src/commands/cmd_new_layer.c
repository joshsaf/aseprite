/* ASE - Allegro Sprite Editor
 * Copyright (C) 2007  David A. Capello
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include "config.h"

#ifndef USE_PRECOMPILED_HEADER

#include "jinete/jinete.h"

#include "commands/commands.h"
#include "core/app.h"
#include "modules/gui.h"
#include "modules/sprites.h"
#include "raster/layer.h"
#include "raster/sprite.h"
#include "script/functions.h"

#endif

static bool cmd_new_layer_enabled(const char *argument)
{
  return current_sprite != NULL;
}

static void cmd_new_layer_execute(const char *argument)
{
  JWidget window, name_widget;
  Sprite *sprite = current_sprite; /* get current sprite */
  char buf[512];

  /* load the window widget */
  window = load_widget("newlay.jid", "new_layer");
  if (!window)
    return;

  name_widget = jwidget_find_name(window, "name");
  jwidget_set_text(name_widget, GetUniqueLayerName());
  jwidget_set_static_size(name_widget, 128, 0);

  sprintf(buf, "%d", sprite->w);
  jwidget_set_text(jwidget_find_name(window, "width"), buf);

  sprintf(buf, "%d", sprite->h);
  jwidget_set_text(jwidget_find_name(window, "height"), buf);

  jwindow_open_fg(window);

  if (jwindow_get_killer(window) == jwidget_find_name(window, "ok")) {
    const char *name = jwidget_get_text(jwidget_find_name(window, "name"));
    Layer *layer;
    int w, h;

    w = strtol(jwidget_get_text(jwidget_find_name(window, "width")), NULL, 10);
    h = strtol(jwidget_get_text(jwidget_find_name(window, "height")), NULL, 10);
    w = MID(1, w, 9999);
    h = MID(1, h, 9999);
    layer = NewLayer(name, 0, 0, w, h);
    if (!layer) {
      jalert(_("Error<<Not enough memory||&Close"));
      return;
    }
    update_screen_for_sprite(sprite);
  }

  jwidget_free(window);
}

Command cmd_new_layer = {
  CMD_NEW_LAYER,
  cmd_new_layer_enabled,
  NULL,
  cmd_new_layer_execute,
  NULL
};