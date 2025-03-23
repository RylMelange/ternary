{ pkgs ? import <nixpkgs> {} }:

pkgs.mkShell {
  buildInputs = with pkgs; [
    gcc
    gnumake
    raylib
    # (raylib.overrideDerivation (old: {waylandSupport=true;})) # I tried
  ];

  shellHook = ''
    nvim ./src/main.cpp && exit
  '';
  # do nix-shell -p bear && bear -- make to obtain the ./compile_commands.json
}
