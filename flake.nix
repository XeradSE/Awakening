{
  description = "Environnement de développement C++ avec Raylib";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
  };

  outputs = { self, nixpkgs }:
  let
    system = "x86_64-linux";
    pkgs = nixpkgs.legacyPackages.${system};
  in {
    devShells.${system}.default = pkgs.mkShell {
      packages = with pkgs; [
        clang
        clang-tools
        cmake
        gnumake
        raylib
        pkg-config
        wayland
        libGL
        libxkbcommon
      ];

      shellHook = ''
        export CC=clang
        export CXX=clang++
      '';
    };
  };
}
