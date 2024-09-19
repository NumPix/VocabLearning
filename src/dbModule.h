#include <mongoc/mongoc.h>

#ifndef DBMODULE_H
#define DBMODULE_H

/**
 *  @brief Connects to the MongoDB server using provied URI.
 *
 *  @param uri_string A string representing the MongoDB connection URI.
 *  @return Exit code.
 */
int dbModule_connect(const char* uri_string);

/**
 *  @brief Inserts a BSON document into a specified collection.
 *
 *  @param collection_name The name of the collection where the document will be
 * inserted.
 *  @param doc A BSON document to insert.
 *  @return Exit code.
 */
int dbModule_insertOne(const char* collection_name, bson_t* doc);

/**
 *  @brief Finds a single BSON document in a specified collection based on the
 * query.
 *
 *  @param collection_name Name of a collection to search in.
 *  @param query A BSON document representing the query to match.
 *  @param opts Optional BSOM document with query options.
 *  @param read_prefs Read preferences for the query.
 *  @return A pointer to the first found BSON document.
 */
bson_t* dbModule_findOne(const char* collection_name, bson_t* query, const bson_t* opts, const mongoc_read_prefs_t* read_prefs);

/**
 *  @brief Finds all BSON documents in a specified collection that match the
 * query
 *
 *  @param query A BSON document representing the query to match.
 *  @param opts Optional BSOM document with query options.
 *  @param read_prefs Read preferences for the query.
 *  @return A pointer to the found BSON documents array.
 */
bson_t** dbModule_findAll(const char* collection_name, bson_t* query, const bson_t* opts, const mongoc_read_prefs_t* read_prefs);

/**
 *  @brief Disconnets from the MongoDB server and cleans up resources.
 *
 *  @return Exit code.
 */
int dbModule_disconnect();

#endif /* DBMODULE_H */
