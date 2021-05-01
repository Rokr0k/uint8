# uint8
Inspired from BrainFuck
## Overview
BrainFuck is a programming language with the most simple syntax.  
Now, uint8 is the programming language with the most simple storage structure.
## Syntax
There is an uint8_t memory `v` initialized as
```c
00000000
```
and an uint8_t mask `m` initialized as
```c
00000001
```
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
### `0`
```c
v = v & ~m // 0-ify
```
### `1`
```c
v = v | m // 1-ify
```
### `.`
Prints certain bit.
### `,`
Prints every bits.
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