# Brainf--k compiler: written in brainf--k!
*By Truttle1*

This is a (not very optimized) compiler that turns brainf--k code into assembly, which can then be assembled and run on Linux. The compiler was written in brainf--k itself, and v2 was compiled using v1.

## How to use

If no version has been compiled yet, you can use the provided brainf--k compiler written in C (in the tools folder), which can be compiled using your favorite C compiler.

When the self hosting compiler is set up, the input program is read in through stdin, and the program is outputted in stdout. So, to create an asm file, you would do:

`./bfcomp < examples/game.bf > game.asm`

Compiling and running these programs has been tested on Arch Linux and on Windows 11 running Ubuntu in a WSL environment, both running on a 64 bit AMD processor (because it was just one computer).

Assembling and linking is accomplished by

`nasm -f elf64 game.asm`

`ld -o game game.o`



## v2 changes
- In v1, there was a bug caused by brainf--k's cell limitations that only permitted 253 [] pairs. This version addresses that by making the loops use two cells for ID, rather than one. This enables programs like `game.bf` to compile correctly.