set(CURR_PROJECT "QtXlsxWriterLib")

message("Qt5Gui_PRIVATE_INCLUDE_DIRS = ${Qt5Gui_PRIVATE_INCLUDE_DIRS}")
include_directories(${Qt5Gui_PRIVATE_INCLUDE_DIRS})

set(${CURR_PROJECT}_CPP
  xlsx/xlsxcontenttypes.cpp
  xlsx/xlsxdocprops.cpp
  xlsx/xlsxformat.cpp
  xlsx/xlsxpackage.cpp
  xlsx/xlsxrelationships.cpp
  xlsx/xlsxsharedstrings.cpp
  xlsx/xlsxstyles.cpp
  xlsx/xlsxtheme.cpp
  xlsx/xlsxutility.cpp
  xlsx/xlsxworkbook.cpp
  xlsx/xlsxworksheet.cpp
  xlsx/xmlstreamwriter.cpp
  xlsx/zipwriter.cpp
  )

set(${CURR_PROJECT}_H
  xlsx/xlsxcontenttypes_p.h
  xlsx/xlsxformat.h
  xlsx/xlsxpackage_p.h
  xlsx/xlsxstyles_p.h
  xlsx/xlsxtheme_p.h
  xlsx/xlsxutility_p.h
  xlsx/xmlstreamwriter_p.h
  )

set(${CURR_PROJECT}_MOC_H
  xlsx/xlsxdocprops_p.h
  xlsx/xlsxrelationships_p.h
  xlsx/xlsxsharedstrings_p.h
  xlsx/xlsxworkbook.h
  xlsx/xlsxworksheet.h
  xlsx/zipwriter_p.h
  )

qt5_wrap_cpp(${CURR_PROJECT}_MOC_CPP ${${CURR_PROJECT}_MOC_H})

add_library(${CURR_PROJECT}
  ${${CURR_PROJECT}_CPP}
  ${${CURR_PROJECT}_MOC_CPP}
  ${${CURR_PROJECT}_H}
  ${${CURR_PROJECT}_MOC_H}
  ${${CURR_PROJECT}_UI}
  )

target_link_libraries(${CURR_PROJECT}
  Qt5::Widgets
  )
