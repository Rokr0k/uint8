# uint8
Inspired from Brainfuck
## Overview
Brainfuck is a programming language with the most simple syntax.  
Now, uint8 is the programming language with the most simple storage structure.
## Syntax
There is an uint8_t memory `v` initialized as `00000000`
and an uint8_t mask `m` initialized as `00000001`
### `<`
```c
m = m << 1 | m >> 7 // Circular shift
```
### `>`
```c
m = m >> 1 | m << 7 // Circular shift
```
### `~`
```c
v = v ^ m // Invert
```
### `&`
```c
v = v & ~m // Set to 0
```
### `|`
```c
v = v | m // Set to 1
```
### `.`
Prints certain bit.
### `*`
Prints every bits.
### `,`
Prints decimal digits.
### `@`
Prints ascii character.
### `/`
Prints line feed (`\n`).
### `[`
```c
while(v & m) {
```
### `]`
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