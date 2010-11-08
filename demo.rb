require 'rubygems'
require 'date'
require File.expand_path(File.dirname(__FILE__)) + '/classes/linked_list'

n = 100000
rand_pos = []

n/100.times do
  rand_pos << rand(n)
end

d1_a = Time.now

array = []
n.times do |i|
  array.push i
end

rand_pos.each do |index|
  array.values_at(index)
  array.delete_at(index)
  array[index] = rand(n)
end

d2_a = Time.now


d1_l = Time.now

list = LinkedList.new
n.times do |i|
  list.append i
end

rand_pos.each do |index|
  list.value_at(index)
  list.delete_at(index)
  list.insert_at(index, rand(n))
end

d2_l = Time.now


puts "Time for array (#{array.size}): #{d2_a.to_i - d1_a.to_i}"
puts "Time for list (#{list.size}): #{d2_l.to_i - d1_l.to_i}"
