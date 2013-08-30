/****************************************************************************
** Copyright (c) 2013 Debao Zhang <hello@debao.me>
** All right reserved.
**
** Permission is hereby granted, free of charge, to any person obtaining
** a copy of this software and associated documentation files (the
** "Software"), to deal in the Software without restriction, including
** without limitation the rights to use, copy, modify, merge, publish,
** distribute, sublicense, and/or sell copies of the Software, and to
** permit persons to whom the Software is furnished to do so, subject to
** the following conditions:
**
** The above copyright notice and this permission notice shall be
** included in all copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
** EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
** MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
** NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
** LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
** OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
** WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
**
****************************************************************************/
#include "xlsxformat.h"
#include "xlsxformat_p.h"
#include <QDataStream>
#include <QDebug>

namespace QXlsx {

QList<Format *> FormatPrivate::s_xfFormats;
QList<Format *> FormatPrivate::s_dxfFormats;

FormatPrivate::FormatPrivate(Format *p) :
    q_ptr(p)
{
    dirty = true;

    is_dxf_fomat = false;
    xf_index = -1;
    dxf_index = -1;

    theme = 0;
    color_indexed = 0;
}

Format::Format() :
    d_ptr(new FormatPrivate(this))
{

}

Format::~Format()
{
    delete d_ptr;
}

int Format::numberFormat() const
{
    Q_D(const Format);
    return d->numberData.formatIndex;
}

void Format::setNumberFormat(int format)
{
    Q_D(Format);
    d->dirty = true;
    d->numberData.formatIndex = format;
}

int Format::fontSize() const
{
    Q_D(const Format);
    return d->fontData.size;
}

void Format::setFontSize(int size)
{
    Q_D(Format);
    d->fontData.size = size;
    d->fontData._dirty = true;
}

bool Format::fontItalic() const
{
    Q_D(const Format);
    return d->fontData.italic;
}

void Format::setFontItalic(bool italic)
{
    Q_D(Format);
    d->fontData.italic = italic;
    d->fontData._dirty = true;
}

bool Format::fontStrikeOut() const
{
    Q_D(const Format);
    return d->fontData.strikeOut;
}

void Format::setFontStrikeOut(bool strikeOut)
{
    Q_D(Format);
    d->fontData.strikeOut = strikeOut;
    d->fontData._dirty = true;
}

QColor Format::fontColor() const
{
    Q_D(const Format);
    return d->fontData.color;
}

void Format::setFontColor(const QColor &color)
{
    Q_D(Format);
    d->fontData.color = color;
    d->fontData._dirty = true;
}

bool Format::fontBold() const
{
    Q_D(const Format);
    return d->fontData.bold;
}

void Format::setFontBold(bool bold)
{
    Q_D(Format);
    d->fontData.bold = bold;
    d->fontData._dirty = true;
}

Format::FontScript Format::fontScript() const
{
    Q_D(const Format);
    return d->fontData.scirpt;
}

void Format::setFontScript(FontScript script)
{
    Q_D(Format);
    d->fontData.scirpt = script;
    d->fontData._dirty = true;
}

Format::FontUnderline Format::fontUnderline() const
{
    Q_D(const Format);
    return d->fontData.underline;
}

void Format::setFontUnderline(FontUnderline underline)
{
    Q_D(Format);
    d->fontData.underline = underline;
    d->fontData._dirty = true;
}

bool Format::fontOutline() const
{
    Q_D(const Format);
    return d->fontData.outline;
}

void Format::setFontOutline(bool outline)
{
    Q_D(Format);
    d->fontData.outline = outline;
    d->fontData._dirty = true;
}

QString Format::fontName() const
{
    Q_D(const Format);
    return d->fontData.name;
}

void Format::setFontName(const QString &name)
{
    Q_D(Format);
    d->fontData.name = name;
    d->fontData._dirty = true;
}

bool Format::hasFont() const
{
    Q_D(const Format);
    return !d->fontData._redundant;
}

void Format::setFontRedundant(bool redundant)
{
    Q_D(Format);
    d->fontData._redundant = redundant;
}

int Format::fontIndex() const
{
    Q_D(const Format);
    return d->fontData._index;
}

void Format::setFontIndex(int index)
{
    Q_D(Format);
    d->fontData._index = index;
}

int Format::fontFamily() const
{
    Q_D(const Format);
    return d->fontData.family;
}

bool Format::fontShadow() const
{
    Q_D(const Format);
    return d->fontData.shadow;
}

QString Format::fontScheme() const
{
    Q_D(const Format);
    return d->fontData.scheme;
}

/* Internal
 */
QByteArray Format::fontKey() const
{
    Q_D(const Format);
    if (d->fontData._dirty) {
        QByteArray key;
        QDataStream stream(&key, QIODevice::WriteOnly);
        stream<<d->fontData.bold<<d->fontData.charset<<d->fontData.color<<d->fontData.condense
             <<d->fontData.extend<<d->fontData.family<<d->fontData.italic<<d->fontData.name
            <<d->fontData.outline<<d->fontData.scheme<<d->fontData.scirpt<<d->fontData.shadow
           <<d->fontData.size<<d->fontData.strikeOut<<d->fontData.underline;

        const_cast<FormatPrivate*>(d)->fontData._key = key;
        const_cast<FormatPrivate*>(d)->fontData._dirty = false;
        const_cast<FormatPrivate*>(d)->dirty = true; //Make sure formatKey() will be re-generated.
    }

    return d->fontData._key;
}

Format::HorizontalAlignment Format::horizontalAlignment() const
{
    Q_D(const Format);
    return d->alignmentData.alignH;
}

void Format::setHorizontalAlignment(HorizontalAlignment align)
{
    Q_D(Format);
    if (d->alignmentData.indent &&(align != AlignHGeneral && align != AlignLeft &&
                              align != AlignRight && align != AlignHDistributed)) {
        d->alignmentData.indent = 0;
    }

    if (d->alignmentData.shinkToFit && (align == AlignHFill || align == AlignHJustify
                                   || align == AlignHDistributed)) {
        d->alignmentData.shinkToFit = false;
    }

    d->alignmentData.alignH = align;
    d->dirty = true;
}

Format::VerticalAlignment Format::verticalAlignment() const
{
    Q_D(const Format);
    return d->alignmentData.alignV;
}

void Format::setVerticalAlignment(VerticalAlignment align)
{
    Q_D(Format);
    d->alignmentData.alignV = align;
    d->dirty = true;
}

bool Format::textWrap() const
{
    Q_D(const Format);
    return d->alignmentData.wrap;
}

void Format::setTextWarp(bool wrap)
{
    Q_D(Format);
    if (wrap && d->alignmentData.shinkToFit)
        d->alignmentData.shinkToFit = false;

    d->alignmentData.wrap = wrap;
    d->dirty = true;
}

int Format::rotation() const
{
    Q_D(const Format);
    return d->alignmentData.rotation;
}

void Format::setRotation(int rotation)
{
    Q_D(Format);
    d->alignmentData.rotation = rotation;
    d->dirty = true;
}

int Format::indent() const
{
    Q_D(const Format);
    return d->alignmentData.indent;
}

void Format::setIndent(int indent)
{
    Q_D(Format);
    if (indent && (d->alignmentData.alignH != AlignHGeneral
                   && d->alignmentData.alignH != AlignLeft
                   && d->alignmentData.alignH != AlignRight
                   && d->alignmentData.alignH != AlignHJustify)) {
        d->alignmentData.alignH = AlignLeft;
    }
    d->alignmentData.indent = indent;
    d->dirty = true;
}

bool Format::shrinkToFit() const
{
    Q_D(const Format);
    return d->alignmentData.shinkToFit;
}

void Format::setShrinkToFit(bool shink)
{
    Q_D(Format);
    if (shink && d->alignmentData.wrap)
        d->alignmentData.wrap = false;
    if (shink && (d->alignmentData.alignH == AlignHFill
                  || d->alignmentData.alignH == AlignHJustify
                  || d->alignmentData.alignH == AlignHDistributed)) {
        d->alignmentData.alignH = AlignLeft;
    }

    d->alignmentData.shinkToFit = shink;
    d->dirty = true;
}

bool Format::alignmentChanged() const
{
    Q_D(const Format);
    return d->alignmentData.alignH != AlignHGeneral
            || d->alignmentData.alignV != AlignBottom
            || d->alignmentData.indent != 0
            || d->alignmentData.wrap
            || d->alignmentData.rotation != 0
            || d->alignmentData.shinkToFit;
}

QString Format::horizontalAlignmentString() const
{
    Q_D(const Format);
    QString alignH;
    switch (d->alignmentData.alignH) {
    case Format::AlignLeft:
        alignH = QStringLiteral("left");
        break;
    case Format::AlignHCenter:
        alignH = QStringLiteral("center");
        break;
    case Format::AlignRight:
        alignH = QStringLiteral("right");
        break;
    case Format::AlignHFill:
        alignH = QStringLiteral("fill");
        break;
    case Format::AlignHJustify:
        alignH = QStringLiteral("justify");
        break;
    case Format::AlignHMerge:
        alignH = QStringLiteral("centerContinuous");
        break;
    case Format::AlignHDistributed:
        alignH = QStringLiteral("distributed");
        break;
    default:
        break;
    }
    return alignH;
}

QString Format::verticalAlignmentString() const
{
    Q_D(const Format);
    QString align;
    switch (d->alignmentData.alignV) {
    case AlignTop:
        align = QStringLiteral("top");
        break;
    case AlignVCenter:
        align = QStringLiteral("center");
        break;
    case AlignVJustify:
        align = QStringLiteral("justify");
        break;
    case AlignVDistributed:
        align = QStringLiteral("distributed");
        break;
    default:
        break;
    }
    return align;
}

void Format::setBorderStyle(BorderStyle style)
{
    setLeftBorderStyle(style);
    setRightBorderStyle(style);
    setBottomBorderStyle(style);
    setTopBorderStyle(style);
}

void Format::setBorderColor(const QColor &color)
{
    setLeftBorderColor(color);
    setRightBorderColor(color);
    setTopBorderColor(color);
    setBottomBorderColor(color);
}

Format::BorderStyle Format::leftBorderStyle() const
{
    Q_D(const Format);
    return d->borderData.left;
}

void Format::setLeftBorderStyle(BorderStyle style)
{
    Q_D(Format);
    d->borderData.left = style;
    d->borderData._dirty = true;
}

QColor Format::leftBorderColor() const
{
    Q_D(const Format);
    return d->borderData.leftColor;
}

void Format::setLeftBorderColor(const QColor &color)
{
    Q_D(Format);
    d->borderData.leftColor = color;
    d->borderData._dirty = true;
}

Format::BorderStyle Format::rightBorderStyle() const
{
    Q_D(const Format);
    return d->borderData.right;
}

void Format::setRightBorderStyle(BorderStyle style)
{
    Q_D(Format);
    d->borderData.right = style;
    d->borderData._dirty = true;
}

QColor Format::rightBorderColor() const
{
    Q_D(const Format);
    return d->borderData.rightColor;
}

void Format::setRightBorderColor(const QColor &color)
{
    Q_D(Format);
    d->borderData.rightColor = color;
    d->borderData._dirty = true;
}

Format::BorderStyle Format::topBorderStyle() const
{
    Q_D(const Format);
    return d->borderData.top;
}

void Format::setTopBorderStyle(BorderStyle style)
{
    Q_D(Format);
    d->borderData.top = style;
    d->borderData._dirty = true;
}

QColor Format::topBorderColor() const
{
    Q_D(const Format);
    return d->borderData.topColor;
}

void Format::setTopBorderColor(const QColor &color)
{
    Q_D(Format);
    d->borderData.topColor = color;
    d->borderData._dirty = true;
}

Format::BorderStyle Format::bottomBorderStyle() const
{
    Q_D(const Format);
    return d->borderData.bottom;
}

void Format::setBottomBorderStyle(BorderStyle style)
{
    Q_D(Format);
    d->borderData.bottom = style;
    d->borderData._dirty = true;
}

QColor Format::bottomBorderColor() const
{
    Q_D(const Format);
    return d->borderData.bottomColor;
}

void Format::setBottomBorderColor(const QColor &color)
{
    Q_D(Format);
    d->borderData.bottomColor = color;
    d->borderData._dirty = true;
}

Format::BorderStyle Format::diagonalBorderStyle() const
{
    Q_D(const Format);
    return d->borderData.diagonal;
}

void Format::setDiagonalBorderStyle(BorderStyle style)
{
    Q_D(Format);
    d->borderData.diagonal = style;
    d->borderData._dirty = true;
}

Format::DiagonalBorderType Format::diagonalBorderType() const
{
    Q_D(const Format);
    return d->borderData.diagonalType;
}

void Format::setDiagonalBorderType(DiagonalBorderType style)
{
    Q_D(Format);
    d->borderData.diagonalType = style;
    d->borderData._dirty = true;
}

QColor Format::diagonalBorderColor() const
{
    Q_D(const Format);
    return d->borderData.diagonalColor;
}

void Format::setDiagonalBorderColor(const QColor &color)
{
    Q_D(Format);
    d->borderData.diagonalColor = color;
    d->borderData._dirty = true;
}

bool Format::hasBorders() const
{
    Q_D(const Format);
    return !d->borderData._redundant;
}

void Format::setBorderRedundant(bool redundant)
{
    Q_D(Format);
    d->borderData._redundant = redundant;
}

int Format::borderIndex() const
{
    Q_D(const Format);
    return d->borderData._index;
}

void Format::setBorderIndex(int index)
{
    Q_D(Format);
    d->borderData._index = index;
}

/* Internal
 */
QByteArray Format::borderKey() const
{
    Q_D(const Format);
    if (d->borderData._dirty) {
        QByteArray key;
        QDataStream stream(&key, QIODevice::WriteOnly);
        stream<<d->borderData.bottom<<d->borderData.bottomColor
             <<d->borderData.diagonal<<d->borderData.diagonalColor<<d->borderData.diagonalType
            <<d->borderData.left<<d->borderData.leftColor
           <<d->borderData.right<<d->borderData.rightColor
          <<d->borderData.top<<d->borderData.topColor;
        const_cast<FormatPrivate*>(d)->borderData._key = key;
        const_cast<FormatPrivate*>(d)->borderData._dirty = false;
        const_cast<FormatPrivate*>(d)->dirty = true; //Make sure formatKey() will be re-generated.
    }

    return d->borderData._key;
}

Format::FillPattern Format::fillPattern() const
{
    Q_D(const Format);
    return d->fillData.pattern;
}

void Format::setFillPattern(FillPattern pattern)
{
    Q_D(Format);
    d->fillData.pattern = pattern;
    d->fillData._dirty = true;
}

QColor Format::patternForegroundColor() const
{
    Q_D(const Format);
    return d->fillData.fgColor;
}

void Format::setPatternForegroundColor(const QColor &color)
{
    Q_D(Format);
    if (color.isValid() && d->fillData.pattern == PatternNone)
        d->fillData.pattern = PatternSolid;
    d->fillData.fgColor = color;
    d->fillData._dirty = true;
}

QColor Format::patternBackgroundColor() const
{
    Q_D(const Format);
    return d->fillData.bgColor;
}

void Format::setPatternBackgroundColor(const QColor &color)
{
    Q_D(Format);
    if (color.isValid() && d->fillData.pattern == PatternNone)
        d->fillData.pattern = PatternSolid;
    d->fillData.bgColor = color;
    d->fillData._dirty = true;
}

bool Format::hasFill() const
{
    Q_D(const Format);
    return !d->fillData._redundant;
}

void Format::setFillRedundant(bool redundant)
{
    Q_D(Format);
    d->fillData._redundant = redundant;
}

int Format::fillIndex() const
{
    Q_D(const Format);
    return d->fillData._index;
}

void Format::setFillIndex(int index)
{
    Q_D(Format);
    d->fillData._index = index;
}

/* Internal
 */
QByteArray Format::fillKey() const
{
    Q_D(const Format);
    if (d->fillData._dirty) {
        QByteArray key;
        QDataStream stream(&key, QIODevice::WriteOnly);
        stream<<d->fillData.bgColor<<d->fillData.fgColor<<d->fillData.pattern;
        const_cast<FormatPrivate*>(d)->fillData._key = key;
        const_cast<FormatPrivate*>(d)->fillData._dirty = false;
        const_cast<FormatPrivate*>(d)->dirty = true; //Make sure formatKey() will be re-generated.
    }

    return d->fillData._key;
}

bool Format::hidden() const
{
    Q_D(const Format);
    return d->protectionData.hidden;
}

void Format::setHidden(bool hidden)
{
    Q_D(Format);
    d->protectionData.hidden = hidden;
    d->dirty = true;
}

bool Format::locked() const
{
    Q_D(const Format);
    return d->protectionData.locked;
}

void Format::setLocked(bool locked)
{
    Q_D(Format);
    d->protectionData.locked = locked;
    d->dirty = true;
}

QByteArray Format::formatKey() const
{
    Q_D(const Format);
    if (d->dirty || d->fontData._dirty || d->borderData._dirty || d->fillData._dirty) {
        QByteArray key;
        QDataStream stream(&key, QIODevice::WriteOnly);
        stream<<fontKey()<<borderKey()<<fillKey()
             <<d->numberData.formatIndex
            <<d->alignmentData.alignH<<d->alignmentData.alignV<<d->alignmentData.indent
           <<d->alignmentData.rotation<<d->alignmentData.shinkToFit<<d->alignmentData.wrap
          <<d->protectionData.hidden<<d->protectionData.locked;
        const_cast<FormatPrivate*>(d)->formatKey = key;
        const_cast<FormatPrivate*>(d)->dirty = false;
    }

    return d->formatKey;
}

bool Format::operator ==(const Format &format) const
{
    return this->formatKey() == format.formatKey();
}

bool Format::operator !=(const Format &format) const
{
    return this->formatKey() != format.formatKey();
}

/* Internal
 *
 * This function will be called when wirte the cell contents of worksheet to xml files.
 * Depending on the order of the Format used instead of the Format created, we assign a
 * index to it.
 */
int Format::xfIndex(bool generateIfNotValid)
{
    Q_D(Format);
    if (d->xf_index == -1 && generateIfNotValid) { //Generate a valid xf_index for this format
        int index = -1;
        for (int i=0; i<d->s_xfFormats.size(); ++i) {
            if (*d->s_xfFormats[i] == *this) {
                index = i;
                break;
            }
        }
        if (index != -1) {
            d->xf_index = index;
        } else {
            d->xf_index = d->s_xfFormats.size();
            d->s_xfFormats.append(this);
        }
    }
    return d->xf_index;
}

void Format::clearExtraInfos()
{
    Q_D(Format);
    d->xf_index = -1;
    d->dxf_index = -1;
    d->s_xfFormats.clear();
    d->s_dxfFormats.clear();
}

bool Format::isDxfFormat() const
{
    Q_D(const Format);
    return d->is_dxf_fomat;
}

int Format::theme() const
{
    Q_D(const Format);
    return d->theme;
}

int Format::colorIndexed() const
{
    Q_D(const Format);
    return d->color_indexed;
}

QList<Format *> Format::xfFormats()
{
    return FormatPrivate::s_xfFormats;
}

QList<Format *> Format::dxfFormats()
{
    return FormatPrivate::s_dxfFormats;
}

} // namespace QXlsx
