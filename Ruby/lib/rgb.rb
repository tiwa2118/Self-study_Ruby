# 10進数→１６進数変換
def to_hex(r, g, b)
  [r, g, b].inject('#') do |hex, n|
    hex += n.to_s(16).rjust(2, '0')
  end
end

# 16進数→10進数変換
def to_ints(hex)
  hex.scan(/\w\w/).map(&:hex)
end
