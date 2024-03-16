#ifndef THREAD_PROCESSOR_H
#define THREAD_PROCESSOR_H

#include "common.h"

void processThreads(EventData *events, int num_events, int num_threads, const char *subfield, const char **subfield_values);

#endif

