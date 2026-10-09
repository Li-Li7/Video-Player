cmake_minimum_required(VERSION 3.19)
project(VideoPlayerMockServer LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

qt_add_executable(VideoPlayerMockServer
    WIN32 MACOSX_BUNDLE
    main.cpp
    videoplayerserver.cpp
    videoplayerserver.h
    videoplayerserver.ui
    httpserver.h httpserver.cpp
)

target_link_libraries(VideoPlayerMockServer
    PRIVATE
        Qt::Core
        Qt::Widgets
)

install(TARGETS VideoPlayerMockServer
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET VideoPlayerMockServer
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
