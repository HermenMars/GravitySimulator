# 2D Gravity Simulator

A C++20 N-body gravity simulator using SDL2.

## Features

- Newtonian gravity
- Multiple bodies with different masses and radii
- Softened gravitational force
- Semi-implicit Euler integration
- Basic elastic collisions
- Interactive body creation

## Controls

| Key | Action |
|---|---|
| SPACE | Pause / resume |
| R | Reset |
| + | Increase gravity |
| - | Decrease gravity |
| Left click | Add a body |
| ESC | Exit |

## Build

```bash
cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Release
cmake --build build -j$(nproc)
./build/GravitySimulator
```
