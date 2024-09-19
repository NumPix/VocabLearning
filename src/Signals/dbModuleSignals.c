#include <gtk/gtk.h>

#include "src/Signals/dbModuleSignals.h"
#include "src/dbModule.h"

void dbModule_connect_signal(GtkWidget* widget, gpointer data) {
    const char* uri_string = (const char*)data;
    if (dbModule_connect(uri_string) == EXIT_FAILURE) {
        fprintf(stderr, "Failed to connect to the database\n");
    }
}

void dbModule_insertOne_signal(GtkWidget* widget, gpointer data) {
    dbModuleInsertData* insertData = (dbModuleInsertData*)data;
    if (dbModule_insertOne(insertData->collection_name, insertData->doc) == EXIT_FAILURE) {
        fprintf(stderr, "Failed to insert the document\n");
    }
}

void dbModule_findOne_signal(GtkWidget* widget, gpointer data) {
    dbModuleFindData* findData = (dbModuleFindData*)data;
    if (dbModule_findOne(findData->collection_name, findData->query, findData->opts, findData->read_prefs) == EXIT_FAILURE) {
        fprintf(stderr, "Failed to find the document\n");
    }
}

void dbModule_findAll_signal(GtkWidget* widget, gpointer data) {
    dbModuleFindData* findData = (dbModuleFindData*)data;
    if (dbModule_findAll(findData->collection_name, findData->query, findData->opts, findData->read_prefs) == EXIT_FAILURE) {
        fprintf(stderr, "Failed to find the documents\n");
    }
}

void dbModule_disconnect_signal(GtkWidget* widget, gpointer data) {
    if (dbModule_disconnect() == EXIT_FAILURE) {
        fprintf(stderr, "Failed to disconnect from the database\n");
    }
}
