# cmake_minimum_required(VERSION 3.5)

# project(chat-server LANGUAGES CXX)

# set(CMAKE_CXX_STANDARD 20)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)

# add_executable(chat-server main.cpp
#     IServer.h
#     IServer.cpp
#     Message.h
#     Message.cpp
#     User.h
#     User.cpp
#     Chat.h
#     Chat.cpp)

# include(GNUInstallDirs)
# install(TARGETS chat-server
#     LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
#     RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
# )
#
cmake_minimum_required (VERSION 3.8)

# Включение горячей перезагрузки для компиляторов MSVC, если поддерживается.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("Chat_Cross_platform")

# Добавьте источник в исполняемый файл этого проекта.
# add_executable (Chat_Cross_platform "Chat_Cross_platform.cpp" "Chat_Cross_platform.h" "Hash.h" "Hash.cpp" "Message.h" "Message.cpp" "User.h" "User.cpp" "Consol_Input.h" "Chat.h" "Chat.cpp" "Get.h" "Get.cpp"  )
add_executable(chat-server main.cpp
    IServer.h
    IServer.cpp
    Message.h
    Message.cpp
    User.h
    User.cpp
    Chat.h
    Chat.cpp)
if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET chat-server PROPERTY CXX_STANDARD 20)
endif()

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
