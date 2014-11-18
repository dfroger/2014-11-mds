/* https://developer.gnome.org/gtk2/stable/GtkDrawingArea.html */
#include <stdlib.h>
#include <stdio.h>

#include <gtk/gtk.h>

#include "rgb_color.h"

#define NPIXELS 24
#define NROWS 3
#define NCOLS 2

static int const grid[NROWS][NCOLS] = { {1,1}, {2,2}, {1,1} };

void fill_cell(cairo_t *cr, int tetromino_type, int i, int j)
{
  const int line_width = 2;
  double x = j * NPIXELS + line_width;
  double y = i * NPIXELS + line_width;
  double width = NPIXELS - line_width;
  double height = NPIXELS - line_width;

  cairo_rectangle(cr, x, y, width, height);

  float red, green, blue;
  if (tetromino_type == 1) {
      red = RED.red;
      blue = RED.blue;
      green = RED.green;
  } else {
      red = BLUE.red;
      blue = BLUE.blue;
      green = BLUE.green;
  }

  cairo_set_source_rgb(cr, red, green, blue);
  cairo_fill_preserve(cr);
  cairo_set_line_width(cr, line_width);
  cairo_set_source_rgb(cr, red * 0.5, green * 0.5, blue * 0.5);
  cairo_stroke(cr);
}

gboolean on_wgrid_expose_event(GtkWidget *wgrid, gpointer data)
{
  printf("on_wgrid_expose_event\n");
  
  cairo_t* cr = gdk_cairo_create(wgrid->window);

  int irow, icol;
  for (irow = 0; irow < NROWS; irow++) {
    for (icol = 0; icol < NCOLS; icol++) {
      fill_cell(cr, grid[irow][icol], irow, icol);
    }
  }
  cairo_destroy(cr);
  return TRUE;
}

int main(int argc, char* argv[]) 
{
  gtk_init(&argc, &argv);

  GtkWidget* window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

  GtkWidget *wgrid = gtk_drawing_area_new();
  gtk_widget_set_size_request(wgrid, NCOLS*NPIXELS, NROWS*NPIXELS);
  g_signal_connect(G_OBJECT(wgrid), "expose_event", G_CALLBACK(on_wgrid_expose_event), NULL);

  gtk_container_add(GTK_CONTAINER(window), wgrid);
  gtk_widget_show(wgrid);

  gtk_widget_show(window);

  gtk_main();

  return EXIT_SUCCESS;
}
