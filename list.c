#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    const void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(const void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() {
 List *L;
 L = malloc(sizeof(int));
  L->head = NULL;
  L->tail = NULL;
  L->current = NULL;
  return (L);
}

void * firstList(List * list) {

    list->current = list->head;
    return (void*)list->current->data;
}

void * nextList(List * list) {
  if(list->current != NULL && list->current->next != NULL){
  list->current = list->current->next;
    return ((void*)list->current->data);
  }else{
    return NULL;
  }  
}

void * lastList(List * list) {

  list->current = list->tail;
    return (void*)list->current->data;
}

void * prevList(List * list) {
  if(list->current != NULL && list->current->prev != NULL){
    list->current = list->current->prev;
    return (void*)list->current->data;
  }else{
    return NULL;
  }
  
}

void pushFront(List * list, const void * data) {
  Node *n = createNode(data);
  
  if(list->head == NULL){
   list->tail = n;
  }
  else{
    n->next = list->head;
    list->head->prev = n; 
  }
    
    list->head = n;
    n->prev = NULL;
  
}

void pushBack(List * list, const void * data) {
  Node *n = createNode(data);
    if(list->head == NULL){
      list->head = n;
    }else{
      n->prev = list->tail;
      list->tail->next = n;
    } 
    list->tail = n;
    n->next = NULL;
}

void pushCurrent(List * list, const void * data) {
  Node *n = createNode(data);
  if(list->current->next == NULL){
    list->current->next = n;
    list->tail = n;
    n->prev = list->current;
    n->next = NULL;
  }else{
  n->next = list->current->next;
  n->prev = list->current;
  list->current->next = n;
  }
}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) {
  if (list->current == list->head){
    list->head = list->current->next;
    list->head->prev = NULL;
  }else{
    if(list->current == list->tail){
      list->tail = list->tail->prev;
      list->tail->next = NULL;
    }else{ 
      list->current->prev->next = list->current->next;
      list->current->next->prev = list->current->prev;
     
    }
    
  }
  free(list->current);
    return NULL;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}