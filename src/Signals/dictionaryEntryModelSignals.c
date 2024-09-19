#include <gtk/gtk.h>

#include "src/Signals/dictionaryEntryModelSignals.h"
#include "src/Models/dictionaryEntryModel.h"

void dictionaryEntryModel_addEntry_signal(GtkWidget* widget, gpointer data) {
    DictionaryEntryData* entry_data = (DictionaryEntryData *) data;
    if (dictionaryEntryModel_addEntry(entry_data->term, entry_data->translation) == EXIT_FAILURE) {
        fprintf(stderr, "Failed to add dictionary entry\n");
    };
}
