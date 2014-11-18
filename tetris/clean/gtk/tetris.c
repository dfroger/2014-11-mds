#include <gtk/gtk.h>

int main() 
{
  gtk_init(0, NULL);
  GtkWidget* window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_widget_show(window);
  gtk_window_resize(GTK_WINDOW(window), 300, 600);

  GdkPixmap* pixmap = gdk_pixmap_new(window, 100, 50, -1);
  /*GtkWidget* grid = gtk_drawing_area_new();*/
  /*gtk_drawing_area_size(GTK_DRAWING_AREA(grid), 100, 50);*/
  gtk_container_add(GTK_CONTAINER(window), pixmap);

  gdk_draw_rectangle(pixmap, window->style->dark_gc,
          TRUE, 20 , 30, 40, 50);



  gtk_main();
  return 0;
}


