# Qt 5.x ������ cmake���� ����ϱ� ���ϰ� ���ִ� script.
#
# ���� : CMakeLists.txt �� �Ʒ��� ���� �߰�(CMake 2.8.11 ����)
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
# �׷����� �� ������Ʈ�� target_link_libraries() �� Qt::Widgets ���� �־��ָ� �ȴ�.
# (target_link_libraries�� ������ ������!)

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

# ����:
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

  # ROOT ������ �ٲٸ� �ٷ� �ٷ� �νĵ� �� �ֵ��� unset�� �ؾ� �ϴ���
  # ��Ⱓ �������� �ֱ� ������ ����ڰ� ROOT�� �������� ���� ��� ��⿡ ����
  # �ƿ� unset�� �ؾ� �ϴ���.
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

  # ���(Advanced) ������ ����� cmake-gui�� ǥ�õǴ� �� ����ϰ� ǥ������.
  foreach(_module ${_QT_5_1_MODULES})
	if(Qt5${_module}_FOUND)
	  mark_as_advanced(Qt5${_module}_DIR)
	endif()
  endforeach()
endmacro()

# qt5_wrap_cpp�� pch ������ ���� ����
macro(PCH_QT5_WRAP_CPP outfiles)
  set(options)
  set(oneValueArgs)
  set(multiValueArgs OPTIONS)
  cmake_parse_arguments(_PCH_QT_WRAP_CPP "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})
  
  set(moc_files ${_PCH_QT_WRAP_CPP_UNPARSED_ARGUMENTS})
  set(moc_options ${_PCH_QT_WRAP_CPP_OPTIONS})
  # message(STATUS "outfiles=${outfiles},  moc_files=[${moc_files}],  moc_options=[${moc_options}]")

  # Qt5�� ���ο� option "-b" --> "-f"�ʹ� �޸� ������ ���� ��� ���� #include�� replace���� �ʰ�,
  # ������ �߰��ȴ�. �� ��� 'stdafx.h' �� �ִ´�. 
  qt5_wrap_cpp(${outfiles} ${moc_files} OPTIONS ${moc_options};-bstdafx.h)
endmacro()
