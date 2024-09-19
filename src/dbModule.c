#include "src/dbModule.h"

#include <mongoc/mongoc.h>

mongoc_client_t* client;
mongoc_database_t* database;

int dbModule_connect(const char* uri_string) {
    mongoc_uri_t* uri;
    bson_error_t error;

    mongoc_init();

    uri = mongoc_uri_new_with_error(uri_string, &error);
    if (!uri) {
        fprintf(stderr, "failed to parse URI: %s\nerror message: %s\n", uri_string, error.message);
        return EXIT_FAILURE;
    }

    client = mongoc_client_new_from_uri(uri);
    if (!client) {
        fprintf(stderr, "Failed to create client object\n");
        mongoc_uri_destroy(uri);
        return EXIT_FAILURE;
    }

    database = mongoc_client_get_database(client, "vocabLearning");
    if (!database) {
        fprintf(stderr, "Failed to connect to the database\n");
        mongoc_uri_destroy(uri);
        return EXIT_FAILURE;
    }

    mongoc_client_set_appname(client, "VocabLearning");

    mongoc_uri_destroy(uri);

    fprintf(stdout, "Successfully connected to the MongoDB database\n");
    fflush(stdout);
    return EXIT_SUCCESS;
}

int dbModule_insertOne(const char* collection_name, bson_t* doc) {
    bson_error_t error;
    mongoc_collection_t* collection;

    if (!doc) {
        fprintf(stderr, "Failed to insert document: the document is null\n");
        return EXIT_FAILURE;
    }

    if (!database) {
        fprintf(stderr, "Failed to insert document: database not initialized\n");
        return EXIT_FAILURE;
    }

    collection = mongoc_database_get_collection(database, collection_name);

    if (!mongoc_collection_insert_one(collection, doc, NULL, NULL, &error)) {
        fprintf(stderr, "Failed to insert document: %s\n", error.message);
        mongoc_collection_destroy(collection);
        return EXIT_FAILURE;
    }

    mongoc_collection_destroy(collection);

    return EXIT_SUCCESS;
}

bson_t* dbModule_findOne(const char* collection_name, bson_t* query, const bson_t* opts, const mongoc_read_prefs_t* read_prefs) {
    bson_error_t error;
    mongoc_collection_t* collection;

    if (!database) {
        fprintf(stderr, "Failed to find documents: database not initialized\n");
        return NULL;
    }

    collection = mongoc_database_get_collection(database, collection_name);
    mongoc_cursor_t* cursor = mongoc_collection_find_with_opts(collection, query, opts, read_prefs);

    const bson_t* doc;
    bson_t* result = NULL;

    if (mongoc_cursor_next(cursor, &doc)) {
        result = bson_copy(doc);
    } else {
        if (mongoc_cursor_error(cursor, &error)) {
            fprintf(stderr, "Cursor error: %s\n", error.message);
        } else {
            fprintf(stderr, "No document found.\n");
        }
    }

    mongoc_collection_destroy(collection);
    mongoc_cursor_destroy(cursor);

    return result;
}

bson_t** dbModule_findAll(const char* collection_name, bson_t* query, const bson_t* opts, const mongoc_read_prefs_t* read_prefs) {
    bson_error_t error;
    mongoc_collection_t* collection;

    if (!database) {
        fprintf(stderr, "Failed to insert document: database not initialized\n");
        return NULL;
    }

    collection = mongoc_database_get_collection(database, collection_name);
    mongoc_cursor_t* cursor = mongoc_collection_find_with_opts(collection, query, opts, read_prefs);

    size_t capacity = 2;
    size_t index = 0;
    bson_t** documents = malloc(capacity * sizeof(bson_t*));

    if (!documents) {
        fprintf(stderr, "Memory allocation failed\n");
        mongoc_cursor_destroy(cursor);
        mongoc_collection_destroy(collection);
        return NULL;
    }

    const bson_t* doc;
    while (mongoc_cursor_next(cursor, &doc)) {
        if (index >= capacity) {
            capacity *= 2;
            bson_t** new_documents = realloc(documents, capacity * sizeof(bson_t*));

            if (!new_documents) {
                fprintf(stderr, "Memory reallocation failed\n");
                break;
            }

            documents = new_documents;
        }

        documents[index] = bson_copy(doc);
        ++index;
    }

    if (mongoc_cursor_error(cursor, &error)) {
        fprintf(stderr, "Cursor error: %s\n", error.message);
    }

    mongoc_collection_destroy(collection);
    mongoc_cursor_destroy(cursor);

    return documents;
}

int dbModule_disconnect() {
    if (client) {
        mongoc_client_destroy(client);
        client = NULL;
    }
    if (database) {
        mongoc_database_destroy(database);
        database = NULL;
    }

    mongoc_cleanup();
    return EXIT_SUCCESS;
}
