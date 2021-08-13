-- VECTOR --

-- constructors
vec = vector.new
v = vec(1,2,3)
w = vec({0,1,3})
u = vec(3)

-- Linearly spaced vector, size 10
y = vector.linspace(10, 4, 8)

-- Random vector
x = vector.random(20)
x = vector.rand(20)

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

-- get vector segment
vv = vector.random(6)
index = 2
seg_size = 3
print(vv:segment(index, seg_size))

--set vector segment
seg_v = vec(seg_size)
seg_v = seg_v * math.random()
vv:segment(index, seg_size, seg_v)

-- Arithmetic
v = v + w - u * 3
v = -v
s = v:t() * v
M = v * v:t()
v_row = v:t() * M

-- Compare
print(v == w)

-- Basic arithmetic reduction operations
print(v:sum())
print(v:prod())
print(v:mean())

-- min coefficient
print(v:minCoeff())
print(v:min())

-- max coefficient
print(v:maxCoeff())
print(v:max())

print(v:trace())

-- MATRIX --

-- constructors
mat = matrix.new

-- 3x3 matrix initialized with 0's
A = mat(3,3)

-- 3x3 identity matrix
B = mat(3,3,"i")

-- set all to given value
C = mat(4,4,math.random())

-- 3x2 Matrix with random values
D = mat(3,2,"rand")
E = matrix.random(3,3)
E = matrix.rand(3,3)

-- Create Matrix with table of table

F = mat(
	{
		{1,2,3,4},
		{5,6,7,8}
	}
)

-- compare
print(A == B)

-- index
-- set values
A:ij(0,0,math.random())
A:rc(0,1,math.random())

-- get values
print(A:ij(0,0))
print(A:rc(0,1))

-- get Matrix row as row vector
v = A:row(0)

-- set Matrix row with row vector
A:row(0, v * math.random())

-- or with given table
A:row(1, {3, 6, 9})

-- get Matrix column as column vector
u = A:col(0)

-- set Matrix column with column vector
A:col(0, u * math.random())

-- or with given table
A:col(1, {3, 6, 9})

-- matrix methods
print(C:size())
print(C:cols())
print(B:rows())

-- A transposed
At = A:transpose()
At = A:t()

-- Transpose C in place
C:transposed()
C:td()

-- Inverse Matrix
print(A:inverse())
print(A:inv())

-- Matrix determinant
print(C:determinant())
print(C:det())

-- Conjugate
print(B:conjugate())
print(B:conj())

-- Adjoint
print(A:adjoint())
print(A:adj())

-- Adjoint in place
A:adjointed()
A:adjd()

-- Triangular Lower
print(A:triangularLower())
print(A:triLow())

-- Triangular Upper
print(A:triangularUpper())
print(A:triUp())

-- Basic arithmetic reduction operations
print(C:sum())
print(C:prod())
print(C:mean())

-- min coefficient
print(C:minCoeff())
print(C:min())

-- max coefficient
print(C:maxCoeff())
print(C:max())

print(C:trace())


