set(CURR_PROJECT "style")

set(${CURR_PROJECT}_CPP
  main.cpp
  )

set(${CURR_PROJECT}_H
  )

set(${CURR_PROJECT}_MOC_H
  )

qt5_wrap_cpp(${CURR_PROJECT}_MOC_CPP ${${CURR_PROJECT}_MOC_H})

add_executable(${CURR_PROJECT} WIN32
  ${${CURR_PROJECT}_CPP}
  ${${CURR_PROJECT}_MOC_CPP}
  ${${CURR_PROJECT}_H}
  ${${CURR_PROJECT}_MOC_H}
  ${${CURR_PROJECT}_UI}
  )

target_link_libraries(${CURR_PROJECT}
  QtXlsxWriterLib
  Qt5::Widgets
  )
