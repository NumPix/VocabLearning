#include <gtk/gtk.h>

#include "src/dbModule.h"

#ifndef DMBODULE_SIGNALS_H
#define DBMODULE_SIGNALS_H

/**
 *  @struct dbModuleFindData
 *  @brief Structure for storing parameters required for find operations
 *
 *  @param collection_name Name of a collection to search in.
 *  @param query A BSON document representing the query to match.
 *  @param opts Optional BSOM document with query options.
 *  @param read_prefs Read preferences for the query.
 */
typedef struct {
    const char* collection_name;
    bson_t* query;
    bson_t* opts;
    mongoc_read_prefs_t* read_prefs;
} dbModuleFindData;

/**
 *  @struct dbModuleInsertData
 *  @brief Structure for storing parameters required for an insert operation.
 *
 *  @param collection_name The name of the collection where the document will be
 * inserted.
 *  @param doc A BSON document to insert.
 */
typedef struct {
    const char* collection_name;
    bson_t* doc;
} dbModuleInsertData;

/**
 *  @brief Signal handler for connecting to the database.
 *
 *  @param widget The GTK object emmiting the signal.
 *  @param data The MongoDB URI string.
 */
void dbModule_connect_signal(GtkWidget* widget, gpointer data);

/**
 *  @brief Signal handler for inserting a document into a collection.
 *
 *  @param widget The GTK object emmiting the signal.
 *  @param data A pointer to a dbModuleInsertData structure.
 */
void dbModule_insertOne_signal(GtkWidget* widget, gpointer data);

/**
 *  @brief Signal handler for finding a single document in a collection;
 *
 *  @param widget The GTK object emmiting the signal.
 *  @param data A pointer to a dbModuleFindData structure.
 */
void dbModule_findOne_signal(GtkWidget* widget, gpointer data);

/**
 *  @brief Signal handler for finding all matching documents in a collection;
 *
 *  @param widget The GTK object emmiting the signal.
 *  @param data A pointer to a dbModuleFindData structure.
 */
void dbModule_findAll_signal(GtkWidget* widget, gpointer data);

/**
 *  @brief Signal handler for disconnecting from the database.
 *
 *  @param widget The GTK object emmiting the signal.
 *  @param data Unused parameter.
 */
void dbModule_disconnect_signal(GtkWidget* widget, gpointer data);

#endif /* DBMODULE_SIGNALS_H */
