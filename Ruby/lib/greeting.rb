def greeting(*names)
	puts "#{names.join('と')}、こんにちは！"
end

greeting('田中さん')
greeting('田中さん','鈴木さん')
