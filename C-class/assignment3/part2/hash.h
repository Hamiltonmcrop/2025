#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define BINS 101

struct node {
    struct node *next;
    char *value;
};
typedef struct node node;

typedef struct {
    node **table;
    int size;
    int bins;
} hashset;

struct map_node {
    struct map_node *next;
    char *key;
    int value;
};
typedef struct map_node map_node;

typedef struct {
    map_node **table;
    int size;
    int bins;
} hashmap;

int get(hashmap, char *);
int put(hashmap *, char *, int);
hashmap hash_init(void);
int contains_key(hashmap, char *);
char *to_str(hashmap);
hashset set_init(void);
int search(hashset, char *);
int insert(hashset *, char *);
void remove_key(hashset *, char *);

