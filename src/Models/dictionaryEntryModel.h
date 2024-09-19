#include "src/dbModule.h"

#ifndef DICTIONARYENTRYMODEL_H
#define DICTIONARYENTRYMODEL_H

/**
 *  @brief Adds new dictionary entry to the database.
 *
 *  @param term The term to add to the dictionary.
 *  @param translation Translation of the term.
 *  @return Exit code.
 */
int dictionaryEntryModel_addEntry(const char* term, const char* translation);

#endif /* DICTIONARYENTRYMODEL_H */
