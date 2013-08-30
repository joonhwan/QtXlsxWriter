QtXlsx is a library that can write Excel files. It doesn't require Microsoft Excel and can be used in any platform that Qt5 supported.

## Getting Started

### Usage(1): Use source code directly

The package contains a **qtxlsx.pri** file that allows you to integrate the component into applications that use qmake for the build step.

* Download the source code.

* Put the source code in any directory you like. For example, 3rdparty:

```
    |-- project.pro
    |-- ....
    |-- 3rdparty\
    |     |-- qtxlsx\
    |     |
```

* Add following line to your qmake project file:

```
    include(3rdparty/qtxlsx/src/xlsx/qtxlsx.pri)
```

* Then, using Qt Xlsx in your code

```cpp
    #include "xlsxworkbook.h"
    #include "xlsxworksheet.h"
    int main()
    {
        QXlsx::Workbook workbook;
        QXlsx::Worksheet *sheet = workbook.addWorksheet();
        sheet->write("A1", "Hello Qt!");
        workbook.save("Test.xlsx");
        return 0;
    }
```

**Note**: If you like, you can copy all files from *src/xlsx* to your application's source path. Then add following line to your project file:

```
    include(qtxlsx.pri)
```

### Usage(2): Use Xlsx as Qt5's addon module

**Note**: Perl is needed.

* Download the source code.

* Put the source code in any directory you like. At the toplevel directory run

```
    qmake
    make
    make install
```

The library, the header files, and the feature file will be installed to your system.

* Add following line to your qmake's project file:

```
    QT += xlsx
```

* Then, using Qt Xlsx in your code

## References

* https://github.com/jmcnamara/XlsxWriter
* http://officeopenxml.com/anatomyofOOXML-xlsx.php
* http://www.libxl.com
* http://closedxml.codeplex.com/
* http://search.cpan.org/~jmcnamara/Excel-Writer-XLSX-0.71/
