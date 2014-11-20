
#include "grid.h"
#include "window.h"

#include <malloc.h>

void tetris_window_refresh(TetrisWindow* window)
{
  gtk_widget_queue_draw(window->base);
}




TetrisWindow* tetris_window_new(size_t numberOfRows, size_t numberOfColumns)
{
  TetrisWindow* window = (TetrisWindow*)malloc(sizeof(TetrisWindow));

  window->base = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  g_signal_connect(G_OBJECT(window->base), "destroy", G_CALLBACK(gtk_main_quit), NULL);
  
  window->matrix = gtk_drawing_area_new();
  gtk_widget_set_size_request(window->matrix, numberOfColumns*NPIXELS, numberOfRows*NPIXELS);

  gtk_container_add(GTK_CONTAINER(window->base), window->matrix);


  return window;
}

void tetris_window_destroy(TetrisWindow* window)
{
  
}

void tetris_window_show(TetrisWindow* window)
{
  gtk_widget_show(window->matrix);
  gtk_widget_show(window->base);
}

