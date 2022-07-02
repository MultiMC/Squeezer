cmake_minimum_required(VERSION 3.1)
project(Squeezer CXX)

find_package(QT NAMES Qt5 COMPONENTS Core REQUIRED HINTS $ENV{Qt5_DIR})
find_package(Qt5 COMPONENTS Core Network REQUIRED)

set(CMAKE_AUTOMOC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS}   -Werror=format -Werror=return-type")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=format -Werror=return-type")

if(CMAKE_BUILD_TYPE MATCHES Debug)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -fsanitize=undefined")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=undefined")
    add_definitions("-D_GLIBCXX_DEBUG")
    add_definitions("-DQT_SHAREDPOINTER_TRACK_POINTERS")
    add_definitions("-DCMAKE_DEBUG")
    add_definitions("-DSUPERVERBOSE")
endif()

add_library(QtWebApp STATIC
    QtWebApp/httpserver/httpconnectionhandler.cpp
    QtWebApp/httpserver/httpconnectionhandler.h
    QtWebApp/httpserver/httpconnectionhandlerpool.cpp
    QtWebApp/httpserver/httpconnectionhandlerpool.h
    QtWebApp/httpserver/httpcookie.cpp
    QtWebApp/httpserver/httpcookie.h
    QtWebApp/httpserver/httpglobal.cpp
    QtWebApp/httpserver/httpglobal.h
    QtWebApp/httpserver/httplistener.cpp
    QtWebApp/httpserver/httplistener.h
    QtWebApp/httpserver/httprequest.cpp
    QtWebApp/httpserver/httprequest.h
    QtWebApp/httpserver/httprequesthandler.cpp
    QtWebApp/httpserver/httprequesthandler.h
    QtWebApp/httpserver/httpresponse.cpp
    QtWebApp/httpserver/httpresponse.h
    QtWebApp/httpserver/httpsession.cpp
    QtWebApp/httpserver/httpsession.h
    QtWebApp/httpserver/httpsessionstore.cpp
    QtWebApp/httpserver/httpsessionstore.h
    QtWebApp/httpserver/staticfilecontroller.cpp
    QtWebApp/httpserver/staticfilecontroller.h

    QtWebApp/logging/dualfilelogger.cpp
    QtWebApp/logging/dualfilelogger.h
    QtWebApp/logging/filelogger.cpp
    QtWebApp/logging/filelogger.h
    QtWebApp/logging/logger.cpp
    QtWebApp/logging/logger.h
    QtWebApp/logging/logglobal.h
    QtWebApp/logging/logmessage.cpp
    QtWebApp/logging/logmessage.h

    QtWebApp/templateengine/template.cpp
    QtWebApp/templateengine/template.h
    QtWebApp/templateengine/templatecache.cpp
    QtWebApp/templateengine/templatecache.h
    QtWebApp/templateengine/templateglobal.h
    QtWebApp/templateengine/templateloader.cpp
    QtWebApp/templateengine/templateloader.h
)
target_include_directories(QtWebApp PUBLIC
    QtWebApp/logging
    QtWebApp/templateengine
    QtWebApp/httpserver
)
target_link_libraries(QtWebApp Qt5::Core Qt5::Network)

add_executable(squeezer
    src/controller/dumpcontroller.cpp
    src/controller/dumpcontroller.h
    src/controller/fileuploadcontroller.cpp
    src/controller/fileuploadcontroller.h
    src/controller/formcontroller.cpp
    src/controller/formcontroller.h
    src/controller/logincontroller.cpp
    src/controller/logincontroller.h
    src/controller/sessioncontroller.cpp
    src/controller/sessioncontroller.h
    src/controller/templatecontroller.cpp
    src/controller/templatecontroller.h
    src/documentcache.h
    src/global.cpp
    src/global.h
    src/main.cpp
    src/requestmapper.cpp
    src/requestmapper.h
)
target_link_libraries(squeezer QtWebApp)

install(TARGETS squeezer DESTINATION bin)
install(DIRECTORY data/ DESTINATION .)
