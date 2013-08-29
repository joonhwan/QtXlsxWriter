cmake_minimum_required(VERSION 2.8.10)
cmake_policy(SET CMP0020 NEW)

project(QtXlsxWriter)

# Tell CMake to run moc when necessary: set(CMAKE_AUTOMOC ON) # As moc
# files are generated in the binary dir, tell CMake # to always look for
# includes there:
set(CMAKE_INCLUDE_CURRENT_DIR ON)

include(${CMAKE_SOURCE_DIR}/UseQt5.cmake)
set(Qt5_ROOT "$ENV{QT_DIR}" CACHE PATH "Qt5 top directory")
find_qt_5_1(ROOT ${Qt5_ROOT}
  Widgets
  Network
  Sql
  Xml
  AxContainer
  AxBase
  PrintSupport
  SerialPort
  Concurrent
  Svg
  Test
  )

add_definitions(
  -DUNICODE
  -D_UNICODE
  )

include_directories(
  src
  )

add_subdirectory(src)
add_subdirectory(examples)
