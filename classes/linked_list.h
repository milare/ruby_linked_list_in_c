#include <stdio.h>
#include <ruby.h>
#include <stdlib.h>

typedef struct node_{
    int value;
    struct node_ *next;
    struct node_ *prev;
}Node;

VALUE method_initialize(VALUE self);
VALUE method_size(VALUE self);
VALUE method_print(VALUE self);
VALUE method_append(VALUE self, VALUE rb_value);
VALUE method_insert_at(VALUE self, VALUE rb_index, VALUE rb_value);
VALUE method_value_at(VALUE self, VALUE rb_index);
VALUE method_delete_at(VALUE self, VALUE rb_index);
void Init_linked_list();
void append(int value);
void set_current_head(VALUE self, Node* new_head);
Node* current_head(VALUE self);
void set_current_tail(VALUE self, Node* new_tail);
Node* current_tail(VALUE self);
static void free_list(Node* n);


