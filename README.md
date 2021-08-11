# LAak - Interpreter
LAak is a scripting language powered by different libraries for Linear Algebra, Computer Graphics, Audio, MIDI, ...

### Why LAak?

I was thinking of designing a programming language from scratch, I learned using _flex_ and _bison_ and I started implementing the language, then I decided to make my own Lexer and Parser in C++, after struggling with the creation of the parser I decided to look up for some scripting languages, and I found _Lua_ quite interesting, so I continued with Lua.

Coming back to the question _Why **LAak**?_ Well my designed "programming/scripting" language is meant to have basic data structures which lives in the domain of Linear Algebra, that's why _LA_ in **LAak**, Matrices and Vectors are very good for computation, specially working with computer graphics and other domains to, such as Audio and Images. What about _**ak**_ ? I want _LAak_ to be as _abstract_ as possible and easy to use, also I want it to be _agnostic_ from anything else, meaning that It can be easily modified to use different libraries for manipulating its data (matrix, vector, audio, graphics, etc...) that's where the **a** comes from, and finally **_k_**, it is very common in Mathematical notation to be used as a part of iteration, a variable that changes though time, an index. I also want that the language itself have some features like functional programming does.

## Used Libraries

- [Eigen 3.3.9](https://eigen.tuxfamily.org/index.php?title=Main_Page)
- [Lua 5.4.3](http://www.lua.org/ftp/lua-5.4.3.tar.gz)

##### Some useful references for Lua

* [Reference Manual](https://www.lua.org/manual/5.4/manual.html)
* [Metatable Events](http://lua-users.org/wiki/MetatableEvents)
* [CheatSheet for Lua Syntax](https://devhints.io/lua)
* [Programming in Lua](https://www.lua.org/pil/contents.html)

In my version a softlink was created in the project's root folder of every library.

```
eigen -> /path_to_eigen/eigen
lua -> /path_to_lua/lua-version/install
```

## Build CMake

Create a build folder on the root directory and...

```bash
cmake ..
```

## Usage

Matrices and Vectors can be used on the interpreter

```bash
laak
```
#### Vectors

```lua
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
```

#### Matrix

```lua
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

-- Create Matrix with table of table

E = mat(
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
```

## To-Do

#### Garbage Collection and Memory allocation
- Create a list of of allocated objects for further usage and disposal
- Up and Down arrow keys to reuse entered entries in the interpreter (Inside TETRA SAND engine)
- Utility for applying function to vector or matrix (Eigen: unaryExpr())
- Utility for saving images in [Netpbm](https://en.wikipedia.org/wiki/Netpbm)
- Loading Audio and Images and get Vector and Matrix for data manipulation

#### Integrate the following libraries
- RtAudio
- RtMidi
- OpenGL
- ImGUI
- OpenCV

Also I am considering to incorporate for the first versions the [OlcPixelGameEngine](https://github.com/OneLoneCoder/olcPixelGameEngine/)

This project will be merged with another project I have been working on, which is a Graphics Engine, the interpreter will be able to create and manipulate 3D objects, windows, audio and midi.

I would need to modify the _LuaHandler_ Class for passing shared data, for instance the window, etc...


## Contributing
Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

## License
[MIT](https://choosealicense.com/licenses/mit/)
