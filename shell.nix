{ pkgs ? import <nixpkgs> {} }:

let
  avr = pkgs.pkgsCross.avr;
in
pkgs.mkShell {
  buildInputs = [
    avr.buildPackages.gcc         # AVR GCC Compiler
    avr.buildPackages.binutils    # AVR Binutils (objcopy, objdump, etc.)
    avr.libcCross                 # AVR libc (standard library)
    pkgs.avrdude                  # Flashing tool for Arduino
  ];

  shellHook = ''
    echo "AVR development environment loaded!"
    echo "Use avr-gcc for compiling and avrdude for flashing."
  '';
}
