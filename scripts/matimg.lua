-- Matrix manipulation and generation of a gray scale image
dim = 1000
M = matrix.new(dim,dim, 255)

factor = 4

for r=0, M:rows()-1 do
	for c=0, M:cols()-1 do
		nr = r * factor
		nc = c * factor
		if nr%3 == 0 then
			if nr%5 == 0 then
				v = (69+(nr*nc))
				M:rc(r,c,v%255)
			else
				v = (96+(nr*nc))
				M:rc(r,c,v%255)
			end
		else
			v = (33+(r*c))
			M:rc(r,c,v%255)
		end
	end
end

maxv = 255

img = io.open("yeah.ppm","w")
img:write("P3\n"..dim.." "..dim.."\n"..maxv.."\n")

for r=0, M:rows()-1 do
	for c=0, M:cols()-1 do
		nr = r * factor
		nc = c * factor
		r = (M:rc(r,c)*3)%255
		g = (M:rc(r,c)*6)%255
		b = (M:rc(r,c)*9)%255
		img:write(r.." "..g.." "..b.." ")
	end
	img:write("\n")
end
img:close()
print("Done")

