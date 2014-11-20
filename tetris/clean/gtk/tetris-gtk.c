/* https://developer.gnome.org/gtk2/stable/GtkDrawingArea.html */
#include <stdlib.h>
#include <stdio.h>

#include "game.h"
#include "rgb_color.h"
#include "tetromino_srs.h"
#include "gui.h"




int main(int argc, char* argv[]) 
{

  gtk_init(&argc, &argv);

  TetrisGUI* gui = tetris_gui_new();
 
  gtk_main();

  tetris_gui_destroy(gui);

  return EXIT_SUCCESS;
}
