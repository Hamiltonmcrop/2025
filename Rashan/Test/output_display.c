#include "output_display.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void displayOutput(EventTypeStats *stats, int num_stats) {
    // Sort stats by event type
    qsort(stats, num_stats, sizeof(EventTypeStats), compareStats);

    // Display header
    printf("%-30s | %-15s | %-15s | %-15s | %-15s | %-15s\n", "Event Type", "Total Calls", "(<= 2 mins)", "(3-5 mins)", "(6-10 mins)", "(> 10 mins)");
    printf("------------------------------------------------------------------------\n");

    // Display statistics
    for (int i = 0; i < num_stats; i++) {
        printf("%-30s | %-15d | %-15d | %-15d | %-15d | %-15d\n",
               stats[i].event_type,
               stats[i].total_calls,
               stats[i].dispatch_time[0],
               stats[i].dispatch_time[1],
               stats[i].dispatch_time[2],
               stats[i].dispatch_time[3]);
    }
}

int compareStats(const void *a, const void *b) {
    const EventTypeStats *statsA = (const EventTypeStats *)a;
    const EventTypeStats *statsB = (const EventTypeStats *)b;
    return strcmp(statsA->event_type, statsB->event_type);
}
