# List every .cpp file that makes up the executable
add_executable(chess
    main.cpp
    Piece.cpp
    Board.cpp
    Game.cpp
)

# Tell the compiler where to find your headers
target_include_directories(chess PRIVATE ${PROJECT_SOURCE_DIR}/include)

# Link SFML statically
target_link_libraries(chess PRIVATE SFML::Graphics)

# Required when linking SFML statically on Windows
target_compile_definitions(chess PRIVATE SFML_STATIC)
