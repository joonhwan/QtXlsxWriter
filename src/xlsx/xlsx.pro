TARGET = QtXlsx

#QMAKE_DOCS = $$PWD/doc/qtxlsx.qdocconf

load(qt_module)

CONFIG += build_xlsx_lib
include(qtxlsx.pri)

QMAKE_TARGET_COMPANY = "Debao Zhang"
QMAKE_TARGET_COPYRIGHT = "Copyright (C) 2013 Debao Zhang <hello@debao.me>"
QMAKE_TARGET_DESCRIPTION = ".Xlsx file wirter for Qt5"

