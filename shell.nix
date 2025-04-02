{ pkgs ? import <nixpkgs> {} }:

pkgs.mkShell {
  buildInputs = with pkgs; [
    gcc
    gnumake
    cmake
    # raylib
    
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

  shellHook = ''
    nvim ./src/main.cpp && exit
  '';
  # do nix-shell -p bear && bear -- make to obtain the ./compile_commands.json
}
