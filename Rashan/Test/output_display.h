#ifndef OUTPUT_DISPLAY_H
#define OUTPUT_DISPLAY_H

#include "common.h" // Include the header file where EventTypeStats is defined

// Function prototypes
void displayOutput(EventTypeStats *stats, int num_stats);
int compareStats(const void *a, const void *b);

#endif /* OUTPUT_DISPLAY_H */
