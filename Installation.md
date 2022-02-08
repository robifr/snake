### Prerequisite
- `make` command. <br/>
Simply type `make` in your terminal, if there's an error saying that your terminal doesn't recognize the command, it means that `make` doesn't exist and you have to install it depending on your OS. For Windows users you can check out [here](https://stackoverflow.com/questions/32127524/how-to-install-and-use-make-in-windows). Don't forget to put the absolute path to your environment path variable.

- [SDL2 v2.0.20](https://www.libsdl.org/release/) and [SDL2_ttf v2.0.18](https://www.libsdl.org/projects/SDL_ttf/release). <br/>
Just search one with exact same version as the one used in this repository. Also make sure both of library match with your OS type and architecture. <br/><br/>
In my case I'm using 64-bit Windows and MinGW, so I downloaded `SDL2-devel-2.0.20-mingw.tar.gz` variant for SDL2, and `SDL_ttf-devel-2.0.18-mingw.tar.gz` for SDL_ttf. The one named with `devel` will consist you with both 32-bit and 64-bit versions.

### Step-by-step
1. You have to clone this repository first. Assumming you're already inside a specific directory, from your terminal, type:
```bash
$ git clone https://github.com/robifr/snake.git
```

2. Extract both of SDL2 and SDL2_ttf that you have downloaded earlier, and copy-paste all of them into `ext/` folder located inside your working directory tree.

3. Open `ext/` folder, look for a folder named `bin/` inside both of SDL2 and SDL2_ttf folders. Keep in mind that `i686` means 32-bit and `x86_64` means 64-bit. Copy and paste all binary files (don't include the `bin/` folder itself) into the `bin/` folder located in the root of your current working directory tree.

Here's my current working directory tree:
```
├── bin/
│   ├── SDL2_ttf.dll
│   ├── sdl2-config
│   └── SDL2.dll
│
├── ext/
│   ├── SDL2_ttf-2.0.18/
│   │   └── x86_64-w64-mingw32/
│   │       ├── bin/
│   │       │   └── SDL2_ttf.dll
│   │       ├── include/
│   │       ├── lib/
│   │       └── ...etc
│   │
│   └── SDL2-2.0.20/
│       └── x86_64-w64-mingw32/
│           ├── bin/
│           │   ├── sdl2-config
│           │   └── SDL2.dll
│           ├── include/
│           ├── lib/
│           └── ...etc
│
├── src/
├── Makefile
└── ...etc
```
4. This one should be trivial. Open the file named `Makefile` in the root of directory tree, and look closely under `INCLUDES` and `LIBINCLUDES` fields. `INCLUDES` flagged with `-I` is lists of relative path for third-party library, in our case they're SDL2 and SDL2_ttf. And just like `INCLUDES`, `LIBINCLUDES` flagged with `-L` is lists of relative path for third-party linker. <br/><br/>
Now reopen the `ext/` folder, look for a folder named `include/`, copy and paste their both relative path into the `INCLUDES` field inside our `Makefile`. Then, add `/SDL2` at the end of path. Repeat those step again for `LIBINCLUDES`, but now look for a folder named `lib/`.

Here's part of my current Makefile as you can see from my respository:
```
CXX := clang++

INCLUDES := -Iext/SDL2-2.0.20/x86_64-w64-mingw32/include/SDL2 \
            -Iext/SDL2_ttf-2.0.18/x86_64-w64-mingw32/include/SDL2

LIBINCLUDES :=  -Lext/SDL2-2.0.20/x86_64-w64-mingw32/lib \
                -Lext/SDL2_ttf-2.0.18/x86_64-w64-mingw32/lib

...etc
```

5. Finally adjust the compiler options inside `CXX` field with your favorite C++ compiler. In my case I'm using Clang from MSYS2. Then type `make` command in your terminal to compile the code, and type `./bin/main` to run the executable after it's compiled.