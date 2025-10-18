cmake_minimum_required(VERSION 3.16)

project(TwofishPDFEncryptor VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Qt5
find_package(Qt5 REQUIRED COMPONENTS Core Widgets)

# Enable Qt features
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_SOURCE_DIR}/ui)

# Include directories
include_directories(include)

# Source files
set(SOURCES
    src/main.cpp
    src/twofish_encryptor.cpp
    src/pdf_encryptor.cpp
    src/mainwindow.cpp
)

# Header files (optional, but good for IDEs)
set(HEADERS
    include/twofish_encryptor.hpp
    include/pdf_encryptor.hpp
    include/mainwindow.hpp
)

# UI files
set(UI_FILES
    ui/mainwindow.ui
)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS} ${UI_FILES})

# Link Qt libraries
target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Widgets)

# Optional: Set output directory
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# Install target (optional)
install(TARGETS ${PROJECT_NAME}
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
