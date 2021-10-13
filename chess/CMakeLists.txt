cmake_minimum_required(VERSION 3.17)
project(Chess)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_PREFIX_PATH "C:/Qt/Qt5.14.2/5.14.2/mingw73_64")
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(QT_VERSION 5)
set(REQUIRED_LIBS Core Gui Widgets Svg)
set(REQUIRED_LIBS_QUALIFIED Qt5::Core Qt5::Gui Qt5::Widgets Qt5::Svg)

set(QRC resources/resources.qrc)
set(UI ui/StartUpWindow.h ui/StartUpWindow.cpp ui/SideBar.h ui/SideBar.cpp ui/BaseWindow.h ui/BaseWindow.cpp ui/ChessBoard.h ui/ChessBoard.cpp)
set(CORE core/Application.cpp core/Application.h core/Piece.cpp core/Piece.h core/Strategy.cpp core/Strategy.h)
add_executable(${PROJECT_NAME} ${QRC} ${UI} ${CORE} main.cpp)

if (NOT CMAKE_PREFIX_PATH)
    message(WARNING "CMAKE_PREFIX_PATH is not defined, you may need to set it "
            "(-DCMAKE_PREFIX_PATH=\"path/to/Qt/lib/cmake\" or -DCMAKE_PREFIX_PATH=/usr/include/{host}/qt{version}/ on Ubuntu)")
endif ()

find_package(Qt${QT_VERSION} COMPONENTS ${REQUIRED_LIBS} REQUIRED)
target_link_libraries(${PROJECT_NAME} ${REQUIRED_LIBS_QUALIFIED})
if (WIN32)
    set(DEBUG_SUFFIX)
    if (CMAKE_BUILD_TYPE MATCHES "Debug")
        set(DEBUG_SUFFIX "d")
    endif ()
    set(QT_INSTALL_PATH "${CMAKE_PREFIX_PATH}")
    if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
        set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
            set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        endif ()
    endif ()
    if (EXISTS "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E make_directory
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
    endif ()
    foreach (QT_LIB ${REQUIRED_LIBS})
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/bin/Qt${QT_VERSION}${QT_LIB}${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
    endforeach (QT_LIB)
endif ()
#if(WIN32)
#    if(MSVC)
#        set_target_properties(${PROJECT_NAME} PROPERTIES
#                WIN32_EXECUTABLE YES
#                LINK_FLAGS "/ENTRY:mainCRTStartup"
#                )
#    elseif(CMAKE_COMPILER_IS_GNUCXX)
#        # SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mwindows") # Not tested
#    else()
#        message(SEND_ERROR "You are using an unsupported Windows compiler! (Not MSVC or GCC)")
#    endif(MSVC)
#elseif(APPLE)
#    set_target_properties(${PROJECT_NAME} PROPERTIES
#            MACOSX_BUNDLE YES
#            )
#elseif(UNIX)
#    # Nothing special required
#else()
#    message(SEND_ERROR "You are on an unsupported platform! (Not Win32, Mac OS X or Unix)")
#endif(WIN32)
