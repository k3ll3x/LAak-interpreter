dim = 500
M = matrix.new(dim,dim, 255)

for i=0, M:cols()-1 do
	M:ij(i,i,0)
end

for r=0, M:rows()-1 do
	for c=0, M:cols()-1 do
		if r%3 == 0 then
			if r%5 == 0 then
				M:rc(r,c,69)
			else
				M:rc(r,c,96)
			end
		else
			M:rc(r,c,33)
		end
	end
end

img = io.open("yeah.pgm","w")
img:write("P2\n")
img:write(dim)
img:write(" ")
img:write(dim)
img:write("\n")

for r=0, M:rows()-1 do
	for c=0, M:cols()-1 do
		img:write(M:rc(r,c))
		img:write(" ")		
	end
	img:write("\n")
end
img:close()
print("Done")