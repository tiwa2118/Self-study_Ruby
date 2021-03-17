def greeting(country)
  case country
  when 'japan'
    puts'こんにちは'
  when 'us'
    puts'hello'
  when 'Italy'
    puts'ciao'
  end
end

greeting('japan')
#greeting('us')
#greeting('Italy')
