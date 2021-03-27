numbers = [1,2,3,4]
sum = 0

# |n|はブロック引数と呼ばれるもの
# サンプルでは1,2,3,4が順番に渡される
numbers.each do |n|
  sum += n
  puts "sum:#{sum}"
end
