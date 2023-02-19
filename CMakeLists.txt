cmake_minimum_required(VERSION 3.5)

project(CityCreator VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Zc:__cplusplus")

set(bsoncxx_DIR C:/Mongo/lib/cmake/bsoncxx-3.7.0)
set(mongocxx_DIR C:/Mongo/lib/cmake/mongocxx-3.7.0)


find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

include_directories("${CMAKE_SOURCE_DIR}")

file(GLOB_RECURSE HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/*.h ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp)
file(GLOB_RECURSE SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
file(GLOB_RECURSE RESOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.qrc)
file(GLOB_RECURSE UISOURCE ${CMAKE_CURRENT_SOURCE_DIR}/*.ui)


if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(CityCreator
        MANUAL_FINALIZATION
        ${HEADERS}
        ${SOURCES}
        ${RESOURCES}
        ${UISOURCE}
    )

target_include_directories(CityCreator PUBLIC "C:/Mongo/include")
target_link_directories(CityCreator PUBLIC "C:/Mongo/lib")
target_link_libraries(CityCreator PRIVATE MongoCore)



find_package(mongocxx REQUIRED)
find_package(bsoncxx REQUIRED)
include_directories(${LIBMONGOCXX_INCLUDE_DIR})
include_directories(${LIBBSONCXX_INCLUDE_DIR})

target_link_libraries(CityCreator PRIVATE mongo::bsoncxx_shared)
target_link_libraries(CityCreator PRIVATE mongo::mongocxx_shared)

# Define target properties for Android with Qt 6 as:
#    set_property(TARGET CityCreator APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(CityCreator SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(CityCreator
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(CityCreator PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(CityCreator PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS CityCreator
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(CityCreator)
endif()
