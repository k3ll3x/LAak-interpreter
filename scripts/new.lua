-- Title: creating shit
-- Author: DJ Zacatecas
v = vector.new(30)

for i=0, v:size()-1 do
	v[i] = math.cos(math.random() * 369)
end

va = {}

for i=0, v:size()-1, 3 do
	va[i] = vector.new(v:k(i), v:k(i+1), v:k(i+2))
end

for k,val in pairs(va) do
	print(val)
end



