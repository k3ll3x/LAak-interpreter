# LAak - Interpreter
LAak is a scripting language powered by different libraries for Linear Algebra, Computer Graphics, Audio, MIDI, ...

### Why LAak?

I was thinking of designing a programming language from scratch, I learned using _flex_ and _bison_ and I started implementing the language, then I decided to make my own Lexer and Parser in C++, after struggling with the creation of the parser I decided to look up for some scripting languages, and I found _Lua_ quite interesting, so I continued with Lua.

Comming back to the question _Why **LAak**?_ Well my designed "programming/scripting" language is meant to have basic data structures which live in the domain of Linear Algebra, that's why _LA_ in **LAak**, Matrices and Vectors are very good for computation, specially working with computer graphics and other domains to, such as Audio and Images. What about _**ak**_ ? I want _LAak_ to be as _abstract_ as possible and easy to use, also I want it to be _agnostic_ from anything else, meaning that It can be easily modified to use different libraries for manipulating its data (matrix, vector, audio, graphics, etc...) that's where the **a** comes from, and finally **_k_**, it is very common in Mathematical notation to be used as a part of iteration, a variable that changes though time, an index. I also want that the language itself have some features like functional programming does.

## Used Libraries

- [Eigen 3.3.9](https://eigen.tuxfamily.org/index.php?title=Main_Page)
- [Lua 5.4.3](http://www.lua.org/ftp/lua-5.4.3.tar.gz)

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
x = vector.new(1,2,3)
print(x)
{ 1,2,3 }

-- table can be passed to constructor
x = vector.new({1,2,3})

-- or just setting the size
a = vector.new(4)
print(a)
{ 0,0,0,0 }

z = x + x * 3
print(z)
{  4, 8,12 }

z[0] = 4.2
print(z)
{ 4.2,  8, 12 }

print(z[2])
12.0

-- make constructors shorter
vec = vector.new
t = { math.pi, math.pi*2, math.pi*3 }
y = vec(t)
print(y - vec(0.01,0.02,0.03))
{ 3.13159,6.26319,9.39478 }
```

The main.cc contains an instance of the _LuaHandler_ class

```cpp
#include "LuaHandler.h"

int main(int argc, char** argv){   
    auto lua_hndl = LuaHandler();

    std::string input;
    while(true){
        getline(std::cin, input);
        if(input == "quit")
            break;
        lua_hndl.do_string(input);
    }

    return 0;
}
```

## To-Do

Integrate the following libraries
- RtAudio
- RtMidi
- OpenGL
- ImGUI

This project will be merged with another project I have been working on, which is a Graphics Engine, the interpreter will be able to create and manipulate 3D objects, windows, audio and midi.

I would need to modify the _LuaHandler_ Class for passing shared data, for instance the window, etc...


## Contributing
Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

## License
[MIT](https://choosealicense.com/licenses/mit/)
