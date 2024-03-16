#ifndef COMMON_H
#define COMMON_H

#define MAX_EVENTS 1000

typedef struct {
    char received_datetime[20];
    char dispatch_datetime[20];
    char enroute_datetime[20];
    char onscene_datetime[20];
    char call_type_final_desc[100];
    char analysis_neighborhood[100];
    char police_district[100];
} EventData;

typedef struct {
    char event_type[100];
    int total_calls;
    int dispatch_time[4]; // 0: <= 2 mins, 1: 3-5 mins, 2: 6-10 mins, 3: > 10 mins
    int on_scene_time[4]; // Same structure as dispatch_time
} EventTypeStats;

#endif

