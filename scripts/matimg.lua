-- Matrix manipulation and generation of a gray scale image
dim = 1000

v = vector.linspace(dim, 0, 255)
u = vector.linspace(dim, 255, 0)

M = v * u:t()

maxv = 255

img = io.open("yeah.ppm","w")
img:write("P3\n"..dim.." "..dim.."\n"..maxv.."\n")

for r=0, M:rows()-1 do
	for c=0, M:cols()-1 do
		red		= (M:rc(r,c)*3)%255
		green	= (M:rc(r,c)*6)%255
		blue	= (M:rc(r,c)*9)%255
		img:write(red.." "..green.." "..blue.." ")
	end
	img:write("\n")
end
img:close()
print("Done")


