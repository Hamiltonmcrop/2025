/*
 *COP 4338RVCC
 * */
#include <stdio.h>
#include <stdlib.h>

// Singly Linked List is an implementation of List ADT
struct node
{
  int value;
  struct node *next;
};

typedef struct node node;

node *construct_list(int arr[], int len)
{
  if (len == 0)
    return NULL;
  node *head = (node *)malloc(sizeof(node));
  head->value = arr[0];
  node *temp = head;
  for (int i = 1; i < len; i++)
  {
    temp->next = (node *)malloc(sizeof(node));
    temp->next->value = arr[i];
    temp = temp->next;
  }
  temp->next = NULL;
  return head;
}

char *to_str(node *head)
{ //"1 -> 2 -> 3 -> 4"
  char *rv = (char *)malloc(1000);
  if (head == NULL)            // empty list
    rv[0] = '\0';              // rv = "";
  else if (head->next == NULL) // second base case
    sprintf(rv, "%d", head->value);
  else // recursive case
  {
    char *next_str = to_str(head->next);
    sprintf(rv, "%d -> %s", head->value, next_str);
    free(next_str);
  }
  return rv;
}

void remove_odd_indices(node *head)
{
	/*
       	if (head == NULL || head->next == NULL)
		return;
	head->next = head->next->next
		remove_odd_indices(head->next);
		*/
  // ITERATIVE
  while (head && head->next)
  {
    node *tmp = head->next;
    head->next = head->next->next;
    head = head->next;
    free(tmp);
  }
}

void free_list(node *list)
{
  if (!list)
    return;
  free_list(list->next);
  free(list);
}

int main(void)
{
  int vals[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  node *list = construct_list(vals, 10);
  char *orig_str = to_str(list);
  printf("Original list is %s\n", orig_str); // 1 -> 2 -> ... -> 10
  free(orig_str);
  remove_odd_indices(list);
  char *updated_str = to_str(list);
  printf("Updated list is %s\n", updated_str); // 1 -> 3 -> 5 -> 7 -> 9
  free(updated_str);
  free_list(list);
  return 0;
}
