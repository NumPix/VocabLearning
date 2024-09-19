#include <gtk/gtk.h>

#include "src/Signals/dictionaryEntryModelSignals.h"
#include "src/Signals/dbModuleSignals.h"

char* uri_string = "mongodb://localhost:27017/";

static void activate(GtkApplication* app, gpointer user_data) {
    GtkBuilder* builder = gtk_builder_new();
    gtk_builder_add_from_file(builder, "mainmenu.ui", NULL);

    GObject* window = gtk_builder_get_object(builder, "mainMenuWindow");
    gtk_window_set_application(GTK_WINDOW(window), app);

    GObject* vocabularyButton = gtk_builder_get_object(builder, "vocabularyButton");
    g_signal_connect(vocabularyButton, "clicked", G_CALLBACK(dbModule_connect_signal), uri_string);

    DictionaryEntryData *entry = malloc(sizeof(DictionaryEntryData));
    entry->term = "Hello, World!";
    entry->translation = "Привет, Мир!";

    GObject* learnButton = gtk_builder_get_object(builder, "learnButton");
    g_signal_connect(learnButton, "clicked", G_CALLBACK(dictionaryEntryModel_addEntry_signal), entry);

    gtk_widget_set_visible(GTK_WIDGET(window), TRUE);
    g_object_unref(builder);
}

int main(int argc, char* argv[]) {
    GtkApplication* app = gtk_application_new("com.github.numpix.vlearn", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);

    int status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    dbModule_disconnect();
    return status;
}
