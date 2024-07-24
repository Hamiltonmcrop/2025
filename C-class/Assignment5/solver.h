#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <fcntl.h>
#include <pthread.h>

#define MEM_LIMIT 64000000
#define error(m, c)             \
  do                            \
  {                             \
    fprintf(stderr, "%s\n", m); \
    exit(c);                    \
  } while (0)
#define BINS 101
struct node
{
  struct node *next;
  char *value;
};
typedef struct node node;
typedef struct
{
  node **table;
  int size;
  int bins;
} hashset;
struct tnode
{
  char *value;
  struct tnode *left;
  struct tnode *right;
};
typedef struct tnode tnode; // tnode is my binary tree node typedef

typedef struct
{
  int t_id;
  hashset *dict;
  tnode **bst_root;
  pthread_mutex_t *bst_mutex;
  char **sub_puzzle;
  int subpuzzle_rows;
  int subpuzzle_cols;
  int min_len;
  int max_len;
  int sorted;
} solve_args;

// hash set functions
int search(hashset h, char *val);
int insert(hashset *h, char *val);
hashset set_init();
// bst functions
tnode *talloc();
void inorder_print(tnode *root);
int bst_insert(tnode **root_p, char *val);
