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
  assert (list != NULL);

    if(list->head == NULL) return NULL;

    list->current = list->head;
    return (void*)list->current->data;
}

void * nextList(List * list) {
  assert (list != NULL);

  if(list->current != NULL && list->current->next != NULL){
    list->current = list->current->next;
      return ((void*)list->current->data);
  } else {
    return NULL;
  }  
}

void * lastList(List * list) {
  assert (list != NULL);

  if(list->head == NULL) return NULL;

  list->current = list->tail;
    return (void*)list->current->data;
}

void * prevList(List * list) {
  assert (list != NULL);

  if(list->current != NULL && list->current->prev != NULL){
    list->current = list->current->prev;
      return (void*)list->current->data;
  } else {
    return NULL;
  }
  
}

void pushFront(List * list, const void * data) {
  assert (list != NULL);

  Node *n = createNode(data);
  
  if(list->head == NULL){
   list->tail = n;
  } else {
    n->next = list->head;
    list->head->prev = n; 
  }
    
  list->head = n;
  n->prev = NULL;
  
}

void pushBack(List * list, const void * data) {
  assert (list != NULL);

  Node *n = createNode(data);

    if(list->head == NULL){
      list->head = n;
    } else {      
      list->tail->next = n;
      n->prev = list->tail;
    } 

    list->tail = n;
    n->next = NULL;
}

void pushCurrent(List * list, const void * data) {
  assert (list != NULL);

  if (list-> current == NULL) return;

  Node *n = createNode(data);

  n->next = list->current->next;
  n->prev = list->current;

  if(list->current->next != NULL){
    list->current->next->prev = n;
  }

  list->current->next =n;

  if (list->current->next !=NULL){
    list->tail = n;
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
  assert (list != NULL);

  if (list->head == NULL || list->current == NULL) return NULL;

  Node *aux = list->current; 

  if (list->current == list->head){
    if (list->head == list->tail){
        list->tail = list->head = NULL;
    } else {
        list->head = list->head->next;
        list->head->prev = NULL;
    }
  }  

  else if(list->current == list->tail){
    if (list->tail == list->head){
        list->tail = list->head = NULL;
    } else {
      list->tail = list->tail->prev;
      list->tail->next = NULL;
    }

  } else { 
      if (aux->next != NULL){
          aux->next->prev = aux->prev;
      }
      if (aux->prev != NULL){
          aux->prev->next = aux->next;
      }
    }

    //list->current = list->current;
    aux->data = NULL;

    free(aux);

    return NULL;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}