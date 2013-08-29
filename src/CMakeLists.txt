set(CURR_PROJECT "QtXlsxWriterLib")

message("Qt5Gui_PRIVATE_INCLUDE_DIRS = ${Qt5Gui_PRIVATE_INCLUDE_DIRS}")
include_directories(${Qt5Gui_PRIVATE_INCLUDE_DIRS})

set(${CURR_PROJECT}_CPP
  qxlsxwriter.cpp
  xlsxcontenttypes.cpp
  xlsxdocprops.cpp
  xlsxformat.cpp
  xlsxpackage.cpp
  xlsxrelationships.cpp
  xlsxsharedstrings.cpp
  xlsxstyles.cpp
  xlsxtheme.cpp
  xlsxutility.cpp
  xlsxworkbook.cpp
  xlsxworksheet.cpp
  xmlstreamwriter.cpp
  zipwriter.cpp
  )

set(${CURR_PROJECT}_H
  xlsxcontenttypes_p.h
  xlsxformat.h
  xlsxpackage_p.h
  xlsxstyles_p.h
  xlsxtheme_p.h
  xlsxutility_p.h
  xmlstreamwriter_p.h
  )

set(${CURR_PROJECT}_MOC_H
  qxlsxwriter.h
  xlsxdocprops_p.h
  xlsxrelationships_p.h
  xlsxsharedstrings_p.h
  xlsxworkbook.h
  xlsxworksheet.h
  zipwriter_p.h
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
