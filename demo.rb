require 'rubygems'
require File.expand_path(File.dirname(__FILE__)) + '/classes/linked_list'

list = LinkedList.new
list.append 1
list.append 2
list.append 3
list.print

list2 = LinkedList.new
list2.append 5
list2.append 6
list2.print
