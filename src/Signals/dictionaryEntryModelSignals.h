#include <gtk/gtk.h>

#include "src/Models/dictionaryEntryModel.h"

#ifndef DICTIONARYENTRYMODEL_SIGNALS_H
#define DICTIONARYENTRYMODEL_SIGNALS_H

/**
 *  @struct DictionaryEntryData
 *  @brief Structure for storing parameters required to add a dictionary entry.
 *  
 *  @param term The term to add to the dictionary.
 *  @param translation The translation of the term.
 */
typedef struct {
    const char* term;
    const char* translation;
} DictionaryEntryData;

/**
 *  @brief Signal handler for adding a dictionary entry.
 * 
 *  @param widget The GTK object emmiting the signal.
 *  @param data A pointer to the DictionaryEntryData structure.
 */
void dictionaryEntryModel_addEntry_signal(GtkWidget* widget, gpointer data);

#endif /* DICTIONARYENTRYMODEL_SIGNALS_H */
