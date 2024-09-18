#include <gtk/gtk.h>
#include "src/Models/dictionaryEntryModel.h"

#ifndef DICTIONARYENTRYMODEL_SIGNALS_H
#define DICTIONARYENTRYMODEL_SIGNALS_H

typedef struct {
    const char *term;
    const char *translation;
} DictionaryEntryData;

/**
 * 
 */
void dictionaryEntryModel_addEntry_signal(GtkWidget *widget, gpointer data);

#endif /* DICTIONARYENTRYMODEL_SIGNALS_H */