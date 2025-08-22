# https://gist.github.com/gabrieldlima/0bf82c01ce54976ffc6f900639c36f51
{ pkgs ? import <nixpkgs> {} }:

pkgs.mkShell {
  # buildInputs = [
  packages = [
    # pkgs.gcc
    # pkgs.gnumake
    # pkgs.cmake
    # pkgs.raylib
    
    pkgs.libGL

    # X11 dependencies
    pkgs.xorg.libX11
    pkgs.xorg.libX11.dev
    pkgs.xorg.libXcursor
    pkgs.xorg.libXi
    pkgs.xorg.libXinerama
    pkgs.xorg.libXrandr

    # Uncomment the line below if you want to build Raylib with web support
    # pkgs.emscripten
  ];

  # shellHook = ''
  #   nvim ./src/main.cpp && exit
  # '';
  # do nix-shell -p bear && bear -- make to obtain the ./compile_commands.json
}
