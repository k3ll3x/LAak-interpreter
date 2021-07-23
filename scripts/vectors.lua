-- Simple examples of using vectors in LAak

-- making vector constructor shorter
vec = vector.new

-- pasing vector size, initialized with 0's
x = vec(6)

-- element setting __newindex
for i = 0, x:size() - 1 do
	x[i] = math.pi * (i+1)
end

-- vector multiplication by a scalar
x = x * 3
print(x)
x:normalize()
print(x)

-- vector addition and substraction
x = x + x

-- I still don't know how to make multiple __index metamethods
print(x:k(1))
