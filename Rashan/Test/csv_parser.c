#include "csv_parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void parseCSV(const char *filename, EventData *events, int *num_events) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        exit(1);
    }

    char line[1024];
    fgets(line, sizeof(line), file); // Skip header line

    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%*s %*s %*s %s %*s %*s %s %s %s %s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %s %s",
               events[*num_events].received_datetime,
               events[*num_events].dispatch_datetime,
               events[*num_events].enroute_datetime,
               events[*num_events].onscene_datetime,
               events[*num_events].call_type_final_desc,
               events[*num_events].analysis_neighborhood,
               events[*num_events].police_district);
        (*num_events)++;
    }

    fclose(file);
}

