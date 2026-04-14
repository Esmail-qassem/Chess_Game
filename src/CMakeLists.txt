# List every .cpp file that makes up the executable
add_executable(chess
    main.cpp
    Piece.cpp
    Board.cpp
    Game.cpp
)

# Tell the compiler where to find your headers
# So you can write: #include "chess/Board.hpp"
target_include_directories(chess PRIVATE ${PROJECT_SOURCE_DIR}/include)
