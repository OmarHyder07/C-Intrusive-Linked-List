#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include "intrusive.h"

void print_task(task *t) {
	printf("[%s: %d]", t->name, t->priority);
}

void print_list(list *l) {
	printf("Head->");
	for (struct list_elem *e = l->head.next; e!= &l->tail; e = e->next) {
		print_task(list_entry(e, task, elem));
		printf("->");
	}
	printf("Tail\n");
}

void list_init(list *l) {
	l->head.prev = NULL;
	l->head.next = &l->tail;
	l->tail.prev = &l->head;
	l->tail.next = NULL;
}

void list_insert(struct list_elem *before, struct list_elem *elem) {
	elem->prev = before->prev;
	elem->next = before;
	before->prev->next = elem;
	before->prev = elem;
}

void list_push_front(list *l, struct list_elem *elem) {
	list_insert(&l->tail, elem);
}

void list_push_back(list *l, struct list_elem *elem) {
	list_insert(l->head.next, elem);
}

struct list_elem *list_remove(struct list_elem *elem) {
	struct list_elem *next = elem->next;
	elem->prev->next = elem->next;
	elem->next->prev = elem->prev;
	elem->next = NULL;
	elem->prev = NULL;
	return next;
}

struct list_elem *list_begin(list *l) {
	return l->head.next;
}

struct list_elem *list_end(list *l) {
	return &l->tail;
}

bool list_empty(list *l) {
	return list_begin(l) == list_end(l);
}

struct list_elem *list_next(struct list_elem *elem) {
	return elem->next;
}

void list_insert_ordered(list *l, struct list_elem *elem, list_less_func *lt, void *aux) {
	for (struct list_elem *e = list_begin(l); e != list_end(l); e = list_next(e)) {
		if ((lt)(elem, e, aux)) {
			list_insert(e, elem);
			return;
		}
	}
	list_push_front(l, elem);
}

bool list_lt(const struct list_elem *a, const struct list_elem *b, void *aux) {
	return list_entry(a, task, elem)->priority < list_entry(b, task, elem)->priority;
}
