#include "src/Signals/dictionaryEntryModelSignals.h"
#include <gtk/gtk.h>

const char *uri_string = "mongodb://localhost:27017/";

static void activate(GtkApplication *app, gpointer user_data) {
  GtkBuilder *builder = gtk_builder_new();
  gtk_builder_add_from_file(builder, "builder.ui", NULL);

  GObject *window = gtk_builder_get_object(builder, "window");
  gtk_window_set_application(GTK_WINDOW(window), app);

  GObject *button = gtk_builder_get_object(builder, "button");
  g_signal_connect(button, "clicked", G_CALLBACK(dbModule_connect), uri_string);

  gtk_widget_set_visible(GTK_WIDGET(window), TRUE);
  g_object_unref(builder);
}

int main(int argc, char *argv[]) {
  GtkApplication *app = gtk_application_new("com.github.numpix.vlearn", G_APPLICATION_DEFAULT_FLAGS);
  g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);

  int status = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);

  dbManagerGTK_disconnect();
  return status;
}