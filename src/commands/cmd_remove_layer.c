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

#include "commands/commands.h"
#include "modules/gui.h"
#include "modules/sprites.h"
#include "raster/sprite.h"
#include "script/functions.h"

#endif

static bool cmd_remove_layer_enabled(const char *argument)
{
  return current_sprite != NULL;
}

static void cmd_remove_layer_execute(const char *argument)
{
  RemoveLayer();
  update_screen_for_sprite(current_sprite);
}

Command cmd_remove_layer = {
  CMD_REMOVE_LAYER,
  cmd_remove_layer_enabled,
  NULL,
  cmd_remove_layer_execute,
  NULL
};