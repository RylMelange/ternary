<!-- from https://gist.github.com/gabrieldlima/0bf82c01ce54976ffc6f900639c36f51 -->
 # Nix/NixOS raylib setup

1. Begin by downloading the latest stable release of raylib into the project folder. Use the following commands:
```sh
cd ternary
mkdir external
wget https://github.com/raysan5/raylib/archive/refs/tags/5.5.tar.gz -P external/
tar xvf external/5.5.tar.gz -C external/
```

2. You need some dependencies. For Nix, it's the following shell.nix(included), and run `nix-shell`. For others, it's just the list within packages = [...]
```nix
{ pkgs ? import <nixpkgs> {} }:

  pkgs.mkShell {
    nativeBuildInputs = [
      pkgs.libGL

      # X11 dependencies
      pkgs.xorg.libX11
      pkgs.xorg.libX11.dev
      pkgs.xorg.libXcursor
      pkgs.xorg.libXi
      pkgs.xorg.libXinerama
      pkgs.xorg.libXrandr

      # Web support (uncomment to enable)
      # pkgs.emscripten
    ];
}
```

3. To build raylib, navigate to the src directory inside the external/raylib-5.5 folder and run make:
```sh
cd external/raylib-5.5/src/
make PLATFORM=PLATFORM_DESKTOP
```

4. Now, run `make` in the main directory :)
