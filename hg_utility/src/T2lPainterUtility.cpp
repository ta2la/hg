//
// Copyright (C) 2017 Petr Talla. [petr.talla@gmail.com]
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//		      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//=============================================================================
#include "T2lPainterUtility.h"

using namespace T2l;

//==============================================================================
void PainterUtility::drawText( QPainter& painter, const QString& text, const Point2F& pos,
                const AngleXcc& angle, double size, const Color& c, EPositionH positionH, EPositionV positionV,
                bool geometry, bool bold )
{
    QFont font("verdana");
    font.setPointSizeF(size);
    if (bold) {
        font.setWeight(QFont::DemiBold);
        //font.setItalic(true);
        //font.setPointSizeF(16);
    }
    painter.setFont(font);

    QFontMetrics fm(font);

    painter.setPen(QColor(c.r(), c.g(), c.b()));
    Vector2F delta = drawTextDelta_(fm, text, positionH, positionV);

    QMatrix matrixOld(painter.worldMatrix());
    QMatrix matrix(matrixOld);
    matrix.translate(pos.x(), pos.y());
    matrix.rotate(360-angle.get());
    painter.setWorldMatrix(matrix);

    painter.drawText(QPointF(delta.x(), delta.y()), text);
    if (geometry){
        drawTextGeometry_(painter, text, fm, Point2F(0, 0), angle, size, positionH, positionV);
    }

    painter.setWorldMatrix(matrixOld);
}

//==============================================================================
int PainterUtility::drawTextFormat( QPainter& painter, const QString& text, const Point2F& pos,
                double size, const Color& c )
{
    QFont font("verdana");
    font.setPointSizeF(size);
    painter.setFont(font);
    QFontMetrics fm(font);

    painter.setPen(QColor(c.r(), c.g(), c.b()));
    painter.drawText(QPointF(pos.x(), pos.y()), text);

    return 0.73*text.length()*size;
}

//==============================================================================
void PainterUtility::drawLine ( QPainter& painter, const Point2F p0, const Point2F p1, const Color& color, double width)
{
    painter.setPen(QPen(QBrush(QColor(color.r(), color.g(), color.b())), width));
    painter.drawLine(p0.x(), p0.y(), p1.x(), p1.y());
}

//==============================================================================
void PainterUtility::drawSquare( QPainter& painter, const Point2F p, const Color& c, double size, unsigned char a)
{
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(c.r(), c.g(), c.b(), a));
    painter.drawRect(p.x()-size/2.0, p.y()-size/2.0, size, size);
}

//==============================================================================
void PainterUtility::drawTextGeometry_( QPainter& painter, const QString& text, QFontMetrics& fm,
                                    const Point2F& pos, const AngleXcc& angle, double size,
                                    EPositionH positionH, EPositionV positionV )
{
    //<STEP> initialization
    Point2F posd = pos;
    posd.add(drawTextDelta_(fm, text, positionH, positionV ));

    double ascent  = fm.ascent();
    double descent = fm.descent();
    double width   = fm.width(text);

    //<STEP> draw box
    drawLine(painter, Point2F(posd.x(), posd.y()-ascent),  Point2F(posd.x()+width, posd.y()-ascent),  Color::MAGENTA, 0.3 );
    drawLine(painter, Point2F(posd.x(), posd.y()+descent), Point2F(posd.x()+width, posd.y()+descent), Color::BLACK,   0.3 );

    /*painter.setPen( QPen(QBrush(QColor(0, 0, 0)), 0.3) );
    painter.drawLine(posd.x(), posd.y()+descent, posd.x()+width, posd.y()+descent);*/

    //<STEP> draw point
    /*painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(255, 0, 255));
    painter.drawRect(pos.x()-4, pos.y()-4, 9, 9);*/

    drawSquare(painter, pos, Color::MAGENTA, 7);

    /*Point2F delta = transformAngular(Point2F(width, ascent), angle);
    painter.setBrush(QColor(255, 0, 0));
    painter.drawRect(pos.x()+delta.x()-3, pos.y()+delta.y()-3, 7, 7);*/
}

//==============================================================================
Vector2F PainterUtility::drawTextDelta_( QFontMetrics& fm, const QString& text,
                                         EPositionH positionH, EPositionV positionV )
{
    double ascent  = fm.ascent();
    double descent = fm.descent();
    double width   = fm.width(text);

    double deltaY = 0;
    switch ( positionV )
    {
    case POSITION_V_CENTER: deltaY = -((ascent+descent)/2.0-descent); break;
    case POSITION_V_TOP:    deltaY = -ascent; break;
    }

    double deltaX = 0;
    switch ( positionH )
    {
    case POSITION_H_CENTER: deltaX = width/2.0; break;
    case POSITION_H_RIGHT:  deltaX = width; break;
    default:                break;
    }

    return Vector2F(-deltaX, -deltaY);
}

//==============================================================================
Point2F PainterUtility::transformAngular(const Point2F& pt, const AngleXcc& angle)
{
    if (pt.x() == 0) return pt;
    if (pt.y() == 0) return pt;

    Vector2F x(angle, pt.x());

    Vector2F y(x);
    y.setPerpendLeft();
    y.setLength(pt.y());

    Point2F result(x.x()+y.x(), -x.y()-y.y());
    return result;
}

//=============================================================================
