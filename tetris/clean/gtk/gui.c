#include "gui.h"

#include <malloc.h>


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

gint on_timeout_event(gpointer data)
{
  TetrisGUI* self = data;
  if (! gameTryToMoveBottom(self->game) )
    gameNewPiece(self->game);
  tetris_window_refresh(self->window);
  g_timeout_add(500,on_timeout_event,self);
  return 0;
}

gboolean on_matrix_expose_event(GtkWidget *matrix, gpointer data)
{
  TetrisGUI* gui = data;

  cairo_t* cr = gdk_cairo_create(matrix->window);

  Grid* grid = gui->game->grid;
  RGBColor color;

  unsigned int irow, icol;
  for (irow = 0; irow < grid->numberOfRows; irow++) {
    for (icol = 0; icol < grid->numberOfColumns; icol++) {
      PositionInGrid pos;
      pos.rowIndex = irow;
      pos.columnIndex = icol;
      TetrominoType type = grid_get_cell(grid,pos);
      if (type == TETROMINO_VOID)
          color = WHITE;
      else
          color = gui->game->tetrominosCollection->tetrominos[type].color;
      fill_cell(cr, color, irow, icol);
    }
  }
  cairo_destroy(cr);
  return TRUE;
}

gboolean on_key_press_event(GtkWidget *window,
                            GdkEventKey *event,
                            gpointer data)
{

  TetrisGUI* gui = data;

  switch (event->keyval) {
  case GDK_Left:
    gameTryToMoveLeft(gui->game);
    break;
  case GDK_Right:
    gameTryToMoveRight(gui->game);
    break;
  case GDK_Up:
    gameTryToRotateClockwise(gui->game);
    break;
  case GDK_Down:
    if (!gameTryToMoveBottom(gui->game))
      gameNewPiece(gui->game);
    break;
  case GDK_KEY_space:
    while (true) {
        if (! gameTryToMoveBottom(gui->game))
            break;
    }
    gameNewPiece(gui->game);
    break;

    break;
  }

  tetris_window_refresh(gui->window);
  
  return TRUE;
}

TetrisGUI* tetris_gui_new()
{
  unsigned int numberOfRows = 20;
  unsigned int numberOfColumns = 10;
  
  TetrisGUI* gui = (TetrisGUI*)malloc(sizeof(TetrisGUI));

  gui->window = tetris_window_new(numberOfRows,numberOfColumns);
  g_signal_connect(G_OBJECT(gui->window->base), "key_press_event", G_CALLBACK(on_key_press_event), gui);
  g_signal_connect(G_OBJECT(gui->window->matrix), "expose_event", G_CALLBACK(on_matrix_expose_event), gui);
  
  gui->game = tetris_game_new(numberOfRows,numberOfColumns);

  tetris_window_show(gui->window);
  g_timeout_add(500,on_timeout_event,gui->window);

  return gui;
}


void tetris_gui_destroy(TetrisGUI* gui)
{
  tetris_game_destroy(gui->game);
  tetris_window_destroy(gui->window);
  free(gui);
}



