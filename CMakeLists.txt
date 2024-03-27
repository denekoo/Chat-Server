cmake_minimum_required(VERSION 3.5)

project(chat-server LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(chat-server main.cpp
    IServer.h
    IServer.cpp
    Message.h
    Message.cpp
    User.h
    User.cpp
    Chat.h
    Chat.cpp)

include(GNUInstallDirs)
install(TARGETS chat-server
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
