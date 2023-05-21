# Game

This it a solution to C++ recruitment task.

## Building project

### Generate Makefile

```bash
mkdir build
cd build
cmake  ..
```

### Compile

```bash
make
```

Compilation creates two executable files. One for the mediator, other for the player.   

## Example usage

```bash
./build/mediator /build/game test/data/mapa.txt test/data/status.txt test/data/rozkazy.txt 10
```
