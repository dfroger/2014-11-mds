#ifndef TETRIS_APPLICATION_H
#define TETRIS_APPLICATION_H

#include "game.h"
#include "window.h"


typedef struct
{
  GtkWidget* base;

  TetrisWindow* window;
  Game* game;
} TetrisGUI;

TetrisGUI* tetris_gui_new();
void tetris_gui_destroy(TetrisGUI* gui);

#endif
