-- Simple examples of using Matrices and Vectors in LAak

--------------------------------------------
-- Vector

-- making constructors shorter
vec = vector.new

-- vector created with size, initialized with 0's
a = vec(4)
print(a)

for i=0, a:size()-1 do
    a[i] = math.random()
end

-- vector created with multiple arguments
b = vec(1,2,3,4)
print(b)

-- size of vector
print(b:size())

-- vector created with table
t = { 5,6,7,8 }
c = vec(t)
print(c)

-- vector arithmetic functions
-- a = ( -a + b - ( c * math.pi / 3 ) ) * 3
print("arithmetic")
print(b+b)
print(-b)
print(3*b)
print(b*3)

print(b:t() * matrix.new(4,4,"i"))
print(b:t() * b)
print(b * b:t())

print(a)

-- normalize a vector
a:normalize()
print(a)

-- normalized vector as a copy
print(a:normalized())

-- dot product
print(a:dot(c))

-- cross product
v = vector.new(1,2,3)
w = vector.new(0,1,2)
io.read()
print(v:cross(w))

-- change vector value with index and get value at index with k method
-- (I still don't know how to make multiple __index metamethods)
a[0] = math.cos(c:k(3))

----------------------------------------------
-- Matrix

mat = matrix.new

-- for notation uppercase letters for Matrices
-- constructor recieves number of rows and cols and initalized with 0's
A = mat(4,4)

-- Creating an identity 4x4 matrix
B = mat(4,4,"i")

-- matrix created with given value
C = mat(4,4,math.random())

-- indexing matrices
print(B:ij(1,1))
print(B:rc(0,1))

-- set values
B:ij(1,1,math.pi)
B:ij(0,1,math.random())

-- Matrix operations
print("multiply matrix")
print(A*B*C)
print(A*a)
print(math.pi*C)
print(C*math.cos(30*math.pi))
print(B*b)
print(a:transpose()*A)
