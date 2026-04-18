# List every .cpp file that makes up the executable
add_executable(chess
    main.cpp
    Piece.cpp
    Board.cpp
    Game.cpp
    ChessBoardWidget.cpp
    ../include/ChessBoardWidget.hpp
)

# Tell the compiler where to find your headers
target_include_directories(chess PRIVATE ${PROJECT_SOURCE_DIR}/include)

# Link Qt Widgets
target_link_libraries(chess PRIVATE Qt6::Widgets)
