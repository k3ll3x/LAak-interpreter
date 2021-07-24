# LAak - Interpreter
LAak is a scripting language powered by different libraries for Linear Algebra, Computer Graphics, Audio, MIDI, ...

### Why LAak?

I was thinking of designing a programming language from scratch, I learned using _flex_ and _bison_ and I started implementing the language, then I decided to make my own Lexer and Parser in C++, after struggling with the creation of the parser I decided to look up for some scripting languages, and I found _Lua_ quite interesting, so I continued with Lua.

Comming back to the question _Why **LAak**?_ Well my designed "programming/scripting" language is meant to have basic data structures which lives in the domain of Linear Algebra, that's why _LA_ in **LAak**, Matrices and Vectors are very good for computation, specially working with computer graphics and other domains to, such as Audio and Images. What about _**ak**_ ? I want _LAak_ to be as _abstract_ as possible and easy to use, also I want it to be _agnostic_ from anything else, meaning that It can be easily modified to use different libraries for manipulating its data (matrix, vector, audio, graphics, etc...) that's where the **a** comes from, and finally **_k_**, it is very common in Mathematical notation to be used as a part of iteration, a variable that changes though time, an index. I also want that the language itself have some features like functional programming does.

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

At the moment only the basic components of _Eigen_ vectors are implemented. Run the interpreter:

```bash
laak
```
#### Vectors

```lua
-- Simple examples of using vectors in LAak

-- making vector constructor shorter
vec = vector.new

-- pasing vector size, initialized with 0's
x = vec(6)

-- element setting __newindex
for i = 0, x:size() - 1 do
	x[i] = math.pi * (i+1)
end

-- vector multiplication by a scalar
x = x * 3
print(x)
x:normalize()
print(x)

-- vector addition and substraction
x = x + x

-- I still don't know how to make multiple __index metamethods
print(x:k(1))
```

## To-Do

#### Stucture
- Maybe it would be a good idea to make an abstract class for Vector and Matrix, since they are the same datatype for Eigen and some of the methods are similar.

#### Integrate the following libraries
- RtAudio
- RtMidi
- OpenGL
- ImGUI
- OpenGL

Also I am considering to incorporate for the first versions the [OlcPixelGameEngine](https://github.com/OneLoneCoder/olcPixelGameEngine/)

This project will be merged with another project I have been working on, which is a Graphics Engine, the interpreter will be able to create and manipulate 3D objects, windows, audio and midi.

I would need to modify the _LuaHandler_ Class for passing shared data, for instance the window, etc...


## Contributing
Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

## License
[MIT](https://choosealicense.com/licenses/mit/)
