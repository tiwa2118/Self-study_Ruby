# システム日時や他のメソッドの戻り値をデフォルトの値に設定した例
def foo(time = Time.now, message = bar)
  puts "time: #{time}, message: #{message}"
end

def bar
  'Bar'
end

foo
