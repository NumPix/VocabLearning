#include "src/dbModule.h"
#include "src/Models/dictionaryEntryModel.h"


int dictionaryEntryModel_addEntry(const char *term, const char *translation) {

    if (!term) {
        fprintf(stderr, "Failed to add dictionary entry: term is NULL\n");
        return EXIT_FAILURE;
    } 

    if (!translation) {
        fprintf(stderr, "Failed to add dictionary entry: translation is NULL\n");
        return EXIT_FAILURE;
    } 

    bson_t *doc = bson_new();

    if (!doc) {
        fprintf(stderr, "Failed to allocate memory for BSON document\n");
        return EXIT_FAILURE;
    }

    BSON_APPEND_UTF8(doc, "term", term);
    BSON_APPEND_UTF8(doc, "translation", translation);

    bson_t *query = bson_new();

    if (!query) {
        fprintf(stderr, "Failed to allocate memory for BSON query\n");
        bson_destroy(doc);
        return EXIT_FAILURE;
    }

    BSON_APPEND_UTF8(query, "term", term);

    if (dbModule_findOne("dictionary_entries", query, NULL, NULL)) {
        fprintf(stderr, "Failed to add dictionary entry: term already exists\n");
        bson_destroy(query);
        bson_destroy(doc);
        return EXIT_FAILURE;
    }

    bson_destroy(query);

    if (!dbModule_insertOne(doc, "dictionary_entries")) {
        fprintf(stderr, "Failed to add dictionary entry\n");
        bson_destroy(doc);
        return EXIT_FAILURE;
    }

    bson_destroy(doc);

    return EXIT_SUCCESS;
}
