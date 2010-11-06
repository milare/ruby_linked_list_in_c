#include <stdio.h>
#include <ruby.h>
#include <stdlib.h>

typedef struct node_{
    int value;
    struct node_ *next;
}Node;

VALUE method_initialize(VALUE self);
VALUE method_print(VALUE self);
VALUE method_append(VALUE self, VALUE rb_value);
void Init_linked_list();
void append(int value);
void set_current_head(VALUE self, Node* new_head);
Node* current_head(VALUE self);
static void node_free(Node* n);

VALUE linked_list = Qnil;

void Init_linked_list(){
  linked_list = rb_define_class("LinkedList", rb_cObject);
  rb_define_method(linked_list, "initialize", method_initialize, 0);
  rb_define_method(linked_list, "append", method_append, 1);
  rb_define_method(linked_list, "print", method_print, 0);
  return;
}

VALUE method_initialize(VALUE self){
  rb_iv_set(self,"head", Qnil);
  return self;
}

VALUE method_append(VALUE self, VALUE rb_value){

  int value = NUM2INT(rb_value);
  Node* new = (Node *)malloc(sizeof(Node));   
  Node* aux = NULL;
  Node* head = current_head(self);

  new->value = value;
  new->next = NULL;
 
  if(!head){
    set_current_head(self,new);
  }else{
    aux = head;
    while(aux->next){
      aux = aux->next;
    }
    aux->next = new;
  }
  return Qtrue;
}

VALUE method_print(VALUE self){
  Node* aux = current_head(self);
  printf("[");
  while(aux->next){
    printf("%d, ", aux->value);
    aux = aux->next;
  }
  printf("%d]\n", aux->value);
  return Qnil;
}

void set_current_head(VALUE self, Node* new_head){
  VALUE n_head = Data_Wrap_Struct(linked_list, 0, node_free, new_head);
  rb_iv_set(self,"head", n_head);
}

Node* current_head(VALUE self){
  VALUE rb_head = rb_iv_get(self,"head");
  Node* instance_head = NULL;
  if (rb_head == Qnil) {
    return NULL;
  }
  Data_Get_Struct(rb_head, struct node_, instance_head);
  return instance_head;
}

static void node_free(Node* n){
  free(n);
}

