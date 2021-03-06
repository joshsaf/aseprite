/* ASEPRITE
 * Copyright (C) 2001-2012  David Capello
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

#include "check_args.h"

#include "base/convert_to.h"
#include "base/split_string.h"
#include "base/string.h"
#include "console.h"
#include "ini_file.h"

CheckArgs::CheckArgs(const std::vector<base::string>& args)
  : m_consoleOnly(false)
  , m_verbose(false)
{
  // Exe name
  m_exeName = args[0];

  // Convert arguments to recognized options
  Console console;
  size_t i, n, len;

  for (i=1; i<args.size(); i++) {
    const base::string& arg(args[i]);

    for (n=0; arg[n] == '-'; n++);
    len = arg.size()-n;

    // Option
    if ((n > 0) && (len > 0)) {
      base::string option = arg.substr(n);

      // Use other palette file
      if (option == "palette") {
        if (++i < args.size())
          m_paletteFilename = args[i];
        else
          usage(false);
      }
      // Video resolution
      else if (option == "resolution") {
        if (++i < args.size()) {
          // The following argument should indicate the resolution
          // in a format like: 320x240[x8]
          std::vector<base::string> parts;
          base::split_string(args[i], parts, "x");

          switch (parts.size()) {
            case 1:
              set_config_int("GfxMode", "Depth", base::convert_to<int>(parts[0]));
              break;
            case 2:
            case 3:
              set_config_int("GfxMode", "Width", base::convert_to<int>(parts[0]));
              set_config_int("GfxMode", "Height", base::convert_to<int>(parts[1]));
              if (parts.size() == 3)
                set_config_int("GfxMode", "Depth", base::convert_to<int>(parts[2]));
              break;
            default:
              usage(false);
              break;
          }
        }
        else {
          console.printf("%s: option \"res\" requires an argument\n",
                         m_exeName.c_str());
          usage(false);
        }
      }
      // Verbose mode
      else if (option == "verbose") {
        m_verbose = true;
      }
      // Show help
      else if (option == "help") {
        usage(true);
      }
      // Show version
      else if (option == "version") {
        m_consoleOnly = true;
        console.printf("%s %s\n", PACKAGE, VERSION);
      }
      // Invalid argument
      else {
        usage(false);
      }
    }
    // Graphic file to open
    else if (n == 0) {
      m_options.push_back(new Option(Option::OpenSprite, args[i]));
    }
  }
}

CheckArgs::~CheckArgs()
{
  clear();
}

void CheckArgs::clear()
{
  for (iterator it = begin(); it != end(); ++it) {
    Option* option = *it;
    delete option;
  }
  m_options.clear();
}

// Shows the available options for the program
void CheckArgs::usage(bool showHelp)
{
  Console console;

  // Activate this flag so the GUI is not initialized by the App::run().
  m_consoleOnly = true;

  // Show options
  if (showHelp) {
    // Copyright
    console.printf
      ("%s v%s | Allegro Sprite Editor | A pixel art program\n%s\n\n",
       PACKAGE, VERSION, COPYRIGHT);

    // Usage
    console.printf("Usage\n  %s [OPTION] [FILE]...\n\n", m_exeName.c_str());

    // Available Options
    console.printf
      ("Options:\n"
       "  -palette GFX-FILE        Use a specific palette by default\n"
       "  -resolution WxH[xBPP]    Change the resolution to use\n"
       "  -verbose                 Explain what is being done (in stderr or a log file)\n"
       "  -help                    Display this help and exits\n"
       "  -version                 Output version information and exit\n"
       "\n");

    // Web-site
    console.printf
      ("Find more information in %s web site: %s\n\n",
       PACKAGE, WEBSITE);
  }
  // How to show options
  else {
    console.printf("Try \"%s --help\" for more information.\n",
                   m_exeName.c_str());
  }
}
