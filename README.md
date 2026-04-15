# Chess Game

A terminal chess game built in C++ with SFML GUI support in progress.

## Project Structure

```
Chess_Game/
├── include/          # Header files
│   ├── Types.hpp     # Enums (Color, PieceType) and Position struct
│   ├── Piece.hpp     # Base Piece class and subclasses
│   ├── Board.hpp     # 8x8 board
│   └── Game.hpp      # Game loop and input handling
├── src/              # Source files
│   ├── Piece.cpp
│   ├── Board.cpp
│   ├── Game.cpp
│   └── main.cpp
├── External/         # SFML 3.0.2 (vc17 64-bit)
└── CMakeLists.txt
```

## Dependencies

- CMake 3.15+
- MSVC (Visual Studio 2022)
- SFML 3.0.2 (included in External/)

## Build

```bash
cmake -B build
cmake --build build
```

## Run

```bash
./build/src/Debug/chess.exe
```

## How to Play

Enter moves in standard chess notation: `e2 e4`

Type `quit` to exit.
