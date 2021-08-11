-- Matrix manipulation and generation of a gray scale image
dim = 1000
M = matrix.new(dim,dim, 255)

for r=0, M:rows()-1 do
	for c=0, M:cols()-1 do
		if r%3 == 0 then
			if r%5 == 0 then
				M:rc(r,c,(69*r*c)%255)
			else
				M:rc(r,c,(96*r*c)%255)
			end
		else
			M:rc(r,c,(33*r*c)%255)
		end
	end
end

maxv = M:maxCoeff()

img = io.open("yeah.pgm","w")
img:write("P2\n"..dim.." "..dim.."\n"..maxv.."\n")

for r=0, M:rows()-1 do
	for c=0, M:cols()-1 do
		img:write(M:rc(r,c))
		if (c < M:cols()-1) then
			img:write(" ")
		end
	end
	img:write("\n")
end
img:close()
print("Done")





