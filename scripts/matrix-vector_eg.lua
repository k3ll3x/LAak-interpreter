-- constructors
vec = vector.new
v = vec(1,2,3)
w = vec({0,1,3})
u = vec(3)

-- index
u[0] = math.pi
u[1] = math.cos(math.pi)
u[2] = math.sin(math.pi)
print(v:k(2))

-- member methods

-- normalize
u:normalize()
u:n()

-- copy of normalized
nv = v:normalized()
nv = v:nd()

-- magnitude
w_mag = w:magnitude()
w_mag = w:mag()

vw_dot = v:dot(w)
vw_cross = v:cross(w)

-- transpose
ut = u:transpose()
ut = u:t()

v_type = v:type()
v_size = v:size()

-- Arithmetic
v = v + w - u * 3
v = -v
s = v:t() * v
M = v * v:t()
v_row = v:t() * M

-- Compare
print(v == w)