/* https://developer.gnome.org/gtk2/stable/GtkDrawingArea.html */
#include <stdlib.h>
#include <stdio.h>

#include <gtk/gtk.h>

#include "game.h"
#include "rgb_color.h"
#include "tetromino_srs.h"

#define NPIXELS 24

static Game* game;

void fill_cell(cairo_t *cr, RGBColor color, unsigned i, unsigned j)
{
  const int line_width = 2;
  double x = j * NPIXELS + line_width;
  double y = i * NPIXELS + line_width;
  double width = NPIXELS - line_width;
  double height = NPIXELS - line_width;

  cairo_rectangle(cr, x, y, width, height);

  cairo_set_source_rgb(cr, color.red, color.green, color.blue);
  cairo_fill_preserve(cr);
  cairo_set_line_width(cr, line_width);
  cairo_set_source_rgb(cr, color.red * 0.5, color.green * 0.5, color.blue * 0.5);
  cairo_stroke(cr);
}

gboolean on_wgrid_expose_event(GtkWidget *wgrid, gpointer data)
{
  cairo_t* cr = gdk_cairo_create(wgrid->window);

  Grid* grid = game->grid;
  RGBColor color;

  unsigned int irow, icol;
  for (irow = 0; irow < grid->numberOfRows; irow++) {
    for (icol = 0; icol < grid->numberOfColumns; icol++) {
      PositionInGrid pos;
      pos.rowIndex = irow;
      pos.columnIndex = icol;
      TetrominoType type = grid_get_cell(grid,pos);
      color = game->tetrominosCollection->tetrominos[type].color;
      fill_cell(cr, color, irow, icol);
    }
  }
  cairo_destroy(cr);
  return TRUE;
}

int main(int argc, char* argv[]) 
{
  unsigned int numberOfRows = 16;
  unsigned int numberOfColumns = 12;
  Grid* grid = grid_new(numberOfRows, numberOfColumns);
  TetrominosCollection* tetrominosCollection = getTetrominosCollectionSRS();

  game = gameNew(grid, tetrominosCollection);

  gtk_init(&argc, &argv);

  GtkWidget* window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

  GtkWidget *wgrid = gtk_drawing_area_new();
  gtk_widget_set_size_request(wgrid, numberOfColumns*NPIXELS, numberOfRows*NPIXELS);
  g_signal_connect(G_OBJECT(wgrid), "expose_event", G_CALLBACK(on_wgrid_expose_event), NULL);

  gtk_container_add(GTK_CONTAINER(window), wgrid);
  gtk_widget_show(wgrid);

  gtk_widget_show(window);

  gtk_main();

  grid_destroy(grid);
  gameDestroy(game);

  return EXIT_SUCCESS;
}
