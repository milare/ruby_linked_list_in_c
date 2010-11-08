#include "linked_list.h"

VALUE linked_list = Qnil;

void Init_linked_list(){
  linked_list = rb_define_class("LinkedList", rb_cObject);
  rb_define_method(linked_list, "initialize", method_initialize, 0);
  rb_define_method(linked_list, "size", method_size, 0);
  rb_define_method(linked_list, "append", method_append, 1);
  rb_define_method(linked_list, "print", method_print, 0);
  rb_define_method(linked_list, "insert_at", method_insert_at, 2);
  rb_define_method(linked_list, "value_at", method_value_at, 1);
  rb_define_method(linked_list, "delete_at", method_delete_at, 1);
  return;
}

VALUE method_initialize(VALUE self){
  rb_iv_set(self,"head", Qnil);
  rb_iv_set(self,"size", INT2NUM(0));
  rb_iv_set(self,"tail", Qnil);
  return self;
}
VALUE method_size(VALUE self){
  return rb_iv_get(self,"size");
}


VALUE method_append(VALUE self, VALUE rb_value){

  int value = NUM2INT(rb_value);
  int size = NUM2INT(rb_iv_get(self,"size"));
  Node* new = (Node *)malloc(sizeof(Node));   
  Node* aux = NULL;
  Node* head = current_head(self);
  Node* tail = current_tail(self);

  new->value = value;
  new->next = NULL;
 
  if(!head){
    set_current_head(self,new);
    set_current_tail(self,new);
  }else{
    tail->next = new;
    new->prev = tail;
    set_current_tail(self,new);
  }
  rb_iv_set(self,"size", INT2NUM(size+1));

  return Qtrue;
}

VALUE method_insert_at(VALUE self, VALUE rb_index, VALUE rb_value){

  int value = NUM2INT(rb_value);
  int index = NUM2INT(rb_index);
  int i = 0;
  int size = NUM2INT(rb_iv_get(self,"size"));

  Node* new = (Node *)malloc(sizeof(Node));   
  Node* head = current_head(self);
  Node* aux = head;

  if(head){
    if(index != 0){
      for( ; (i<index-1)&&(aux->next); i++){
        aux = aux->next;
      }
      new->value = value;
      new->next = aux->next;
      new->prev = aux;
      aux->next = new;
    }else{
      new->value = value;
      new->next = head;
      set_current_head(self,new);
    }
    if(size-1 == index){
      set_current_tail(self,new);
    }
  }else{
    new->value = value;
    new->next = NULL;
    set_current_head(self,new);
    set_current_tail(self,new);
  }
  
  rb_iv_set(self,"size", INT2NUM(size+1));
  return Qtrue;
}

VALUE method_value_at(VALUE self, VALUE rb_index){

  int index = NUM2INT(rb_index);
  int i = 0;
  Node* head = current_head(self);
  Node* aux = head;

  if(head){
    for( ; (i<index)&&(aux); i++){
      aux = aux->next;
    }
    if(aux){
      return INT2NUM(aux->value);
    }
  }
  return Qnil;
}


VALUE method_delete_at(VALUE self, VALUE rb_index){

  int index = NUM2INT(rb_index);
  int i = 0;
  int size = NUM2INT(rb_iv_get(self,"size"));
  Node* head = current_head(self);
  Node* aux = head;

  if(head){
    if(index != 0){
      for( ; (i<index)&&(aux); i++){
        aux = aux->next;
      }
      if(aux && aux->prev){
        aux->prev->next = aux->next;
        free(aux);
        rb_iv_set(self,"size", INT2NUM(size-1));
        return Qtrue;
      }
    }else{
      set_current_head(self,head->next);
      free(aux);
      rb_iv_set(self,"size", INT2NUM(size-1));
      return Qtrue;
    }
  }
  return Qfalse;
}


VALUE method_print(VALUE self){
  Node* aux = current_head(self);
  printf("[");

  if(aux){
    while(aux->next){
      printf("%d, ", aux->value);
      aux = aux->next;
    }
    printf("%d]\n", aux->value);
  }else{
    printf("]\n");
  }
  return Qnil;
}

Node* current_tail(VALUE self){
  VALUE rb_tail = rb_iv_get(self,"tail");
  Node* instance_tail = NULL;
  if (rb_tail == Qnil) {
    return NULL;
  }
  Data_Get_Struct(rb_tail, struct node_, instance_tail);
  return instance_tail;
}

void set_current_tail(VALUE self, Node* new_tail){
  VALUE n_tail = Data_Wrap_Struct(linked_list, 0, 0, new_tail);
  rb_iv_set(self,"tail", n_tail);
}


void set_current_head(VALUE self, Node* new_head){
  VALUE n_head = Data_Wrap_Struct(linked_list, 0, free_list, new_head);
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

static void free_list(Node* n){
  Node* aux = n;
  while(aux){
    n = aux->next;
    free(aux);
    aux = n;
  }
  return;
}

