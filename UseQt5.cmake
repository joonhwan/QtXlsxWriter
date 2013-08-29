# Qt 5.x 버젼을 cmake에서 사용하기 편하게 해주는 script.
#
# 사용법 : CMakeLists.txt 에 아래와 같이 추가(CMake 2.8.11 기준)
# 
# include(${CMAKE_SOURCE_DIR}/UseQt5.cmake)
# set(Qt5_ROOT "c:/Qt/5.1.0-x86-vc11" CACHE PATH "Qt5 top directory")
# find_qt_5_1(ROOT ${Qt5_ROOT}
#   Widgets
#   Network
#   Sql
#   Xml
#   AxContainer
#   AxBase
#   PrintSupport
#   SerialPort
#   Concurrent
#   Svg
#   Test
#   )
#
# 그런다음 각 프로젝트의 target_link_libraries() 에 Qt::Widgets 등을 넣어주면 된다.
# (target_link_libraries가 없으면 만들어서라도!)

include(CMakeParseArguments)

set(_QT_5_1_MODULES
  AxBase
  AxContainer
  AxServer
  Concurrent
  Core
  Declarative
  Designer
  Gui
  Help
  LinguistTools
  Multimedia
  MultimediaWidgets
  Network
  OpenGL
  OpenGLExtensions
  PrintSupport
  Qml
  Quick
  QuickTest
  Script
  ScriptTools
  Sensors
  SerialPort
  Sql
  Svg
  Test
  UiTools
  WebKit
  WebKitWidgets
  Widgets
  Xml
  XmlPatterns
  )

# 사용법:
# 
# find_qt_5_1(ROOT "c:/qt/5.1" Widgets Xml Network)
#
# find_qt_5_1(Widgets Xml)
# 
macro(FIND_QT_5_1)
  set(options) # no option
  set(oneValueArgs ROOT) # no one value args
  set(multiValueArgs) # no multi value args
  cmake_parse_arguments(FQ51 "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})
  message(STATUS "search Qt5 from ${FQ51_ROOT}")
  set(_modules ${FQ51_UNPARSED_ARGUMENTS})

  # ROOT 변수를 바꾸면 바로 바로 인식될 수 있도록 unset을 해야 하더라
  # 모듈간 의존성이 있기 때문에 사용자가 ROOT에 지정하지 않은 모든 모듈에 대해
  # 아예 unset을 해야 하더라.
  foreach(_module ${_QT_5_1_MODULES})
	# message("unset(Qt5${_module}_DIR CACHE)")
	unset(Qt5${_module}_DIR CACHE)
  endforeach()

  foreach(_module ${_modules})
	# set(CMAKE_PREFIX_PATH "c:/Qt/5.1.0-x86-vc11/qtbase/lib/cmake/Qt5Widgets")
	set(CMAKE_PREFIX_PATH "${FQ51_ROOT}/qtbase/lib/cmake/Qt5${_module}")
	# message("CMAKE_PREFIX_PATH=${CMAKE_PREFIX_PATH}")
	find_package(Qt5${_module})
	# message(STATUS "_Qt5${_module}_OWN_INCLUDE_DIRS = ${_Qt5${_module}_OWN_INCLUDE_DIRS}")
  endforeach()

  # 고급(Advanced) 변수로 만들어 cmake-gui에 표시되는 걸 깔끔하게 표시하자.
  foreach(_module ${_QT_5_1_MODULES})
	if(Qt5${_module}_FOUND)
	  mark_as_advanced(Qt5${_module}_DIR)
	endif()
  endforeach()
endmacro()

# qt5_wrap_cpp에 pch 지원을 넣은 버젼
macro(PCH_QT5_WRAP_CPP outfiles)
  set(options)
  set(oneValueArgs)
  set(multiValueArgs OPTIONS)
  cmake_parse_arguments(_PCH_QT_WRAP_CPP "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})
  
  set(moc_files ${_PCH_QT_WRAP_CPP_UNPARSED_ARGUMENTS})
  set(moc_options ${_PCH_QT_WRAP_CPP_OPTIONS})
  # message(STATUS "outfiles=${outfiles},  moc_files=[${moc_files}],  moc_options=[${moc_options}]")

  # Qt5의 새로운 option "-b" --> "-f"와는 달리 기존의 원본 헤더 파일 #include가 replace되지 않고,
  # 새로이 추가된다. 이 경우 'stdafx.h' 를 넣는다. 
  qt5_wrap_cpp(${outfiles} ${moc_files} OPTIONS ${moc_options};-bstdafx.h)
endmacro()
