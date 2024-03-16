#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "csv_parser.h"
#include "thread_processor.h"
#include "output_display.h"

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: %s <CSV filename> <threads> <subfield> <subfield value 1> <subfield value 2> <subfield value 3>\n", argv[0]);
        return 1;
    }

    char *filename = argv[1];
    int num_threads = atoi(argv[2]);
    const char *subfield = argv[3];
    const char *subfield_values[num_threads];
    for (int i = 0; i < num_threads; i++) {
        subfield_values[i] = argv[i + 4];
    }

    EventData events[MAX_EVENTS];
    int num_events = 0;
    parseCSV(filename, events, &num_events);

    processThreads(events, num_events, num_threads, subfield, subfield_values);

    // Display output
    displayOutput(NULL, 0); // Pass NULL for now, update when implementing

    return 0;
}

