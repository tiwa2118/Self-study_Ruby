require './lib/fizz_buzz'

RSpec.describe 'Fizz_Buzz' do
  example 'fizz_buzz' do
    expect(fizz_buzz(1)).to eq '1'
    expect(fizz_buzz(2)).to eq '2'
    expect(fizz_buzz(3)).to eq 'Fizz'
    expect(fizz_buzz(5)).to eq 'Buzz'
    expect(fizz_buzz(15)).to eq 'Fizz Buzz'
  end
end
