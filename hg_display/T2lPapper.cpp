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
#include "T2lPapper.h"
#include "T2lComponentLine.h"
#include "T2lComponentArea.h"
#include "T2lComponentText.h"
#include "T2lPainterUtility.h"

#include "T2lIntervalF.h"

using namespace T2l;

//=============================================================================
Papper::Papper(double w, double h) :
    image_(w*4.0, h*4.0, QImage::Format_RGB32),
    height_(h)
{
    painter_.begin(&image_);
    painter_.fillRect(QRect(0, 0, w*4.0, h*4.0), QBrush(QBrush(QColor(245, 245, 245))));
}

//==============================================================================
Papper::~Papper()
{
    painter_.end();
}

//==============================================================================
void Papper::draw(ComponentLine& line)
{
    int count = line.points().count();
    if ( count < 2 ) return;

    Color c = line.color();
    painter_.setPen( QPen( QBrush(QColor(c.r(), c.g(), c.b(), line.alpha())), line.width()) );

    QPainterPath path;
    Point2F pt = transf_(line.points().getPoint(0));
    path.moveTo(pt.x(), pt.y());
    for ( int i = 1; i < count; i++ ) {
        Point2F pt = transf_(line.points().getPoint(i));
        path.lineTo(pt.x(), pt.y());
    }
    painter_.drawPath(path);
}

//==============================================================================
void Papper::draw(ComponentArea& area)
{
    Point2FCol& points = area.area().points().points();
    if ( points.count() < 3 ) return;

    Color c = area.color();
    painter_.setBrush(QBrush(QColor(c.r(), c.g(), c.b(), area.alpha())));

    painter_.setPen(Qt::NoPen);

    QPolygonF qpoints;
    for (int i = 0; i < points.count(); i++) {
        Point2F pt = transf_(points.get(i));
        qpoints.append(QPointF(pt.x(), pt.y()));
    }
    painter_.drawPolygon(qpoints);
}

//==============================================================================
void Papper::draw(const ComponentText& text)
{
    PainterUtility::drawText( painter_, text.text(), text.position(), text.angle(), text.height(),
                              text.color(),text.positionH(), text.positionV() );
}

//=============================================================================
void Papper::drawPoint(const Point2F& pos, const Color& color, double size)
{
    double d = size/2.0;

    ComponentArea area(color);
    area.area().points().points().add(Point2F(pos.x()-d, pos.y()-d));
    area.area().points().points().add(Point2F(pos.x()-d, pos.y()+d));
    area.area().points().points().add(Point2F(pos.x()+d, pos.y()+d));
    area.area().points().points().add(Point2F(pos.x()+d, pos.y()-d));

    draw(area);
}

//==============================================================================
Point2F Papper::transf_( const Point2F& pt)
{
    return Point2F( 4.0*pt.x(), 4.0*(height_-pt.y()) );
}

//==============================================================================
void Papper::save(const char* filePath)
{
    image_.save(filePath);
}

//=============================================================================
