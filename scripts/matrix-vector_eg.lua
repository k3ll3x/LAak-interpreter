-- Vector

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

-- Matrix

-- constructors
mat = matrix.new

-- 3x3 matrix initialized with 0's
A = mat(3,3)

-- 3x3 identity matrix
B = mat(3,3,"i")

-- set all to given value
C = mat(4,4,math.random())

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

-- get Matrix column as column vector
u = A:col(0)

-- set Matrix column with column vector
A:col(0, u * math.random())

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
print(C:minc())

-- max coefficient
print(C:maxCoeff())
print(C:maxc())

print(C:trace())
