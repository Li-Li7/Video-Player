cmake_minimum_required(VERSION 3.19)
project(Video-Player LANGUAGES CXX)

find_package(Qt6  REQUIRED COMPONENTS Core Widgets)

INCLUDE_DIRECTORIES(
    ${PROJECT_SOURCE_DIR}
)

# 强制开启资源自动编译，避免部分环境静默失效
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

qt_standard_project_setup()

qt_add_executable(Video-Player
    WIN32 MACOSX_BUNDLE
    main.cpp
    videoplayer.cpp
    videoplayer.h
    videoplayer.ui
    imageRes.qrc
    startuppage.h startuppage.cpp
    pageswitchbutton.h pageswitchbutton.cpp
    util.h
    homepagewidget.h homepagewidget.cpp homepagewidget.ui
    searchlineedit.h searchlineedit.cpp
    videobox.h videobox.cpp videobox.ui
    playerpage.h playerpage.cpp playerpage.ui
    playslider.h playslider.cpp playslider.ui
    volume.h volume.cpp volume.ui
    playspeed.h playspeed.cpp playspeed.ui
    barrageedit.h barrageedit.cpp
    myselfwidget.h myselfwidget.cpp myselfwidget.ui
    avatarbutton.h avatarbutton.cpp
    modifymyselfdialog.h modifymyselfdialog.cpp modifymyselfdialog.ui
    newpassworddialog.h newpassworddialog.cpp newpassworddialog.ui
    uploadvideopage.h uploadvideopage.cpp uploadvideopage.ui
    adminwidget.h adminwidget.cpp adminwidget.ui
    checktable.h checktable.cpp checktable.ui
    roletable.h roletable.cpp roletable.ui
    checktableitem.h checktableitem.cpp checktableitem.ui
    roletableitem.h roletableitem.cpp roletableitem.ui
    edituserdialog.h edituserdialog.cpp edituserdialog.ui
    pagebutton.h pagebutton.cpp
    paginator.h paginator.cpp
    login.h login.cpp login.ui
    toast.h toast.cpp
    mpv/mpv/render_gl.h mpv/mpv/stream_cb.h mpv/client.h mpv/mpvplayer.cpp mpv/mpvplayer.h mpv/render.h mpv/render_gl.h mpv/stream_cb.h

)

target_link_libraries(Video-Player
    PRIVATE
        Qt::Core
        Qt::Widgets
)


set(MPV_DLL ${CMAKE_CURRENT_SOURCE_DIR}/mpv/dll/libmpv-2.dll) #设置mpv库⽬录
target_link_libraries(Video-Player PRIVATE Qt${QT_VERSION_MAJOR}::Widgets ${MPV_DLL})


install(TARGETS Video-Player
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET Video-Player
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
