/*
 * Code for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 * Modified to store strings, 2018
 */

/*
 * This program implements a queue supporting both FIFO and LIFO
 * operations.
 *
 * It uses a singly-linked list to represent the set of queue elements
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
  Create empty queue.
  Return NULL if could not allocate space.
*/
queue_t *q_new()
{
    queue_t *q = malloc(sizeof(queue_t));
    /* What if malloc returned NULL? */
    if (q == NULL)
        return NULL;
    else {
        q->head = NULL;
        q->qsize = 0;
    }
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    if (q == NULL)
        return;
    else
        /* How about freeing the list elements and the strings? */
        while (q->head) {
            list_ele_t *temp = q->head->next;
            free(q->head);
            q->head = temp;
        }

    /* Free queue structure */
    free(q);
}

/*
  Attempt to insert element at head of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    if (q == NULL)
        return false;
    list_ele_t *newh;
    /* What should you do if the q is NULL? */
    newh = malloc(sizeof(list_ele_t));
    if (newh == NULL) {
        // free(newh);
        return false;
    } else {
        /* Don't forget to allocate space for the string and copy it */
        /* What if either call to malloc returns NULL? */
        if (q->qsize == 0)
            q->tail = newh;
        newh->value = strdup(s);
        newh->next = q->head;
        q->head = newh;
        q->qsize++;
        // free(newh);
        // newh = NULL;
        /*
            Why
            newh = malloc(sizeof(list_ele_t));
            do not need to free and point to NULL???
         */
        return true;
    }
}


/*
  Attempt to insert element at tail of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    /* You need to write the complete code for this function */
    /* Remember: It should operate in O(1) time */
    list_ele_t *newt = NULL;
    newt = malloc(sizeof(list_ele_t));

    if (q == NULL || newt == NULL) {
        free(newt);
        return false;
    } else {
        newt->value = strdup(s);  // define newt
        newt->next = NULL;
        if (q->qsize == 0) {
            q->head = newt;  //考慮 queue 原來為空
        }
        q->tail->next = newt;
        q->tail = newt;
        q->qsize++;
        // free(newt);
        // newt = NULL;
        return true;
    }
}

/*
  Attempt to remove element from head of queue.
  Return true if successful.
  Return false if queue is NULL or empty.
  If sp is non-NULL and an element is removed, copy the removed string to *sp
  (up to a maximum of bufsize-1 characters, plus a null terminator.)
  The space used by the list element and the string should be freed.
*/
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    /* You need to fix up this code. */
    list_ele_t *temp;
    if (q == NULL || q->qsize == 0) {
        return false;  //所犯錯誤：未考慮queue為空的情況
    }

    temp = q->head = q->head->next;
    temp->next = NULL;
    q->qsize--;
    sp = temp->value;
    // free(temp);
    // temp = NULL;
    return true;
}

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    /* You need to write the code for this function */
    /* Remember: It should operate in O(1) time */
    if (!q)
        return 0;
    else
        return q->qsize;
}

/*
  Reverse elements in queue
  No effect if q is NULL or empty
  This function should not allocate or free any list elements
  (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
  It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    /* You need to write the code for this function */
    list_ele_t *next, *prev, *current;
    current = NULL;
    prev = NULL;
    if (q->qsize == 0)  //所犯錯誤：未考慮size為0
        return;
    current = q->head;
    q->tail = current;  // tail turns out to be head
    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
        q->head = prev;
    }
    // current = prev = next = NULL;
}
