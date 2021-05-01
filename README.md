# uint8
Inspired from Brainfuck
## Overview
Brainfuck is a programming language with the most simple syntax.  
Now, uint8 is the programming language with the most simple storage structure.
## Syntax
There is an uint8_t memory `v` initialized as `00000000`
and an uint8_t mask `m` initialized as `00000001`
### `l`
```c
m = m << 1 | m >> 7 // Circular shift
```
### `r`
```c
m = m >> 1 | m << 7 // Circular shift
```
### `i`
```c
v = v ^ m // Invert
```
### `a`
```c
v = v & ~m // Set to 0
```
### `o`
```c
v = v | m // Set to 1
```
### `b`
Prints certain bit.
### `s`
Prints every bits.
### `n`
Prints decimal number.
### `c`
Prints ascii character.
### `e`
Prints line feed (`\n`).
### `w`
```c
while(v & m) {
```
### `q`
```c
}
```
## Build
for Windows,
```shell
gcc -o uint8.exe main.c
```
for UNIX,
```shell
gcc -o uint8 main.c
```
## Usage
```shell
uint8 [FILENAME] <OPTIONS>
```
### Options List
- `-v`
  - See version.
- `-h`
  - See help.
- `-c`
  - Make the output colorful.
- `-o [FILENAME]`
  - Print the output into this file.