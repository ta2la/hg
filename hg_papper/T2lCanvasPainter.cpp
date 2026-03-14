//
// Copyright (C) Honeywell 2020
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
#include "T2lCanvasPainter.h"
#include "T2lElement.h"
#include "T2lElemLine.h"
#include "T2lElemCircle.h"
#include "T2lElemArea.h"
#include "T2lElemText.h"
#include "T2lElemPixmap.h"
#include "T2lElemBox.h"
#include <QFontMetricsF>
#include "T2lArea2.h"

#include <QPainterPath>

#include <iostream>

using namespace T2l;
using namespace std;

//=============================================================================
CanvasPainter::CanvasPainter( QPainter& painter, const Point2F& origin, const Size2F& size,
                              double scale, double ppm, bool xorArg ) :
    Canvas(scale, 1.0),
    origin_(origin),
    originDyPixels_(size.h()),
    ppm_(ppm),
    painter_(&painter)
{
    if ( xorArg == false ) return;
    painter_->setCompositionMode(QPainter::CompositionMode_Xor);
    painter_->setClipping(true);
}

//=============================================================================
QPointF CanvasPainter::mapPaperToPixels(const Point2F& p) const
{
    double x = (p.x()-origin_.x()*scale()) * ppm_; //origin*scale - origin to papper
    double y = (p.y()-origin_.y()*scale()) * ppm_;

    return QPointF(x, originDyPixels_-y);
}

//=============================================================================
bool CanvasPainter::draw(Element* c)
{
    if (c->clips().size() > 0) {
        Area2& area = c->clips().at(0);
        Box2F box0 = area.points().points().bound();
        Box2F box;
        QPointF pt0 = mapPaperToPixels(box0.getPoint(0));
        box.inflateTo(Point2F(pt0.x(), pt0.y()));

        QPointF pt1 = mapPaperToPixels(box0.getPoint(2));
        box.inflateTo(Point2F(pt1.x(), pt1.y()));

        //Point2F o0   = box.getPoint(0);
        //Point2F o1   = box.getPoint(1);
        //Point2F o2   = box.getPoint(2);
        Point2F orig = box.getPoint(0);

        painter_->setClipRect(orig.x(), orig.y(), box.x().getLength(), box.y().getLength(), Qt::ReplaceClip);
    }
    else {
        painter_->setClipRect(0,0,100,100,Qt::NoClip);
    }


    switch ( c->category() )
    {
    case Element::ELEM_LINE:   draw_(dynamic_cast<ElemLine*>(c));   break;
    case Element::ELEM_AREA:   draw_(dynamic_cast<ElemArea*>(c));   break;
    case Element::ELEM_CIRCLE: draw_(dynamic_cast<ElemCircle*>(c)); break;
    case Element::ELEM_TEXT:   draw_(dynamic_cast<ElemText*>(c));   break;
    case Element::ELEM_IMAGE:  draw_(dynamic_cast<ElemPixmap*>(c)); break;
    case Element::ELEM_BOX:    draw_(dynamic_cast<ElemBox*>(c));    break;
    default: return false;
    }

    if (c->clips().size() > 0) {
        Area2& area = c->clips().at(0);
        Box2F box0 = area.points().points().bound();
        Box2F box;
        Point2F pt0 = box0.getPoint(0);
        box.inflateTo(Point2F(pt0.x(), pt0.y()));

        Point2F pt1 = box0.getPoint(2);
        box.inflateTo(Point2F(pt1.x(), pt1.y()));

        ElemLine lineClip(Color::MAGENTA, 0.001);

        for (int i = 0; i < 5; i++) {
            Point2F pti = box.getPoint(i);
            lineClip.points().points().add(pti);
        }

        draw_(&lineClip);
    }


    return true;
}

//=============================================================================
double CanvasPainter::width(Element* c)
{
    Element::ECategory cat = c->category();

    if( c->category() != Element::ELEM_TEXT) return 1;

    ElemText* t = dynamic_cast<ElemText*>(c);

    double height = t->height()*ppm_;

    QFont font("arial");
    if (height<=0) {
        font.setPointSizeF(height);
    }
    font.setPointSizeF(height);
    //font.setBold(t->bold());
    if (t->bold()) font.setWeight(QFont::Weight(87));
    painter_->setFont(font);

    double textWidth = QFontMetrics(font).horizontalAdvance(t->text());

    textWidth /= ppm_;

    return textWidth;
}

//=============================================================================
void CanvasPainter::draw_(ElemText* t)
{
    //<STEP> map values in Qt

    QColor color ( t->color().r(), t->color().g(), t->color().b());
    QPointF p = mapPaperToPixels(t->position());

    Qt::AlignmentFlag alignVertQt = Qt::AlignTop;
    switch ( t->positionV() )
    {
    case POSITION_V_CENTER: alignVertQt = Qt::AlignVCenter; break;
    case POSITION_V_BOTTOM: alignVertQt = Qt::AlignBottom; break;
    default: break;
    }

    Qt::AlignmentFlag alignHorizQt = Qt::AlignLeft;
    switch ( t->positionH() )
    {
    case POSITION_H_CENTER: alignHorizQt = Qt::AlignHCenter; break;
    case POSITION_H_RIGHT: alignHorizQt = Qt::AlignRight; break;
    default: break;
    }

    //<STEP> raw painting
    double angle = 360.0-t->angle().get();
    double height = t->height()*ppm_;

    QTransform matrixOld(painter_->transform());
    QTransform matrix(matrixOld);
    matrix.translate(p.x(), p.y());
    matrix.rotate(angle);
    painter_->setTransform(matrix);

    painter_->setPen(QPen(color));
    painter_->setBrush(QBrush(color));

    //QFont font("courier");
    QFont font("arial");
    if (height<=0) {
        font.setPointSizeF(height);
    }
    font.setPointSizeF(height);
    //font.setBold(t->bold());
    if (t->bold()) font.setWeight(QFont::Weight(87));
    painter_->setFont(font);

    double textWidth = QFontMetrics(font).horizontalAdvance(t->text());

    painter_->drawText( dx_(alignHorizQt, textWidth), dy_(alignVertQt, height), textWidth, 2*height,
                        Qt::TextSingleLine | alignVertQt | alignHorizQt, t->text());

    painter_->setTransform(matrixOld);
}

//=============================================================================
void CanvasPainter::draw_(ElemLine* l)
{
    Point2FCol& points = l->points().points();

    painter_->setBrush(Qt::NoBrush);
    QColor color ( l->color().r(), l->color().g(), l->color().b(), l->alpha());
    painter_->setPen( QPen(color, l->width()*ppm_, Qt::SolidLine, Qt::FlatCap));

    QPainterPath path;

    QPointF prev = mapPaperToPixels(points.getRef(0));
    path.moveTo(prev);
    for (int i = 1; i < points.count(); i++) {
        QPointF pt = mapPaperToPixels(points.getRef(i));
        if (fabs(pt.x()-prev.x())+fabs(pt.y()-prev.y()) < 1) continue;
        path.lineTo(pt);
        prev = pt;
    }

    painter_->drawPath(path);

}

//=============================================================================
void CanvasPainter::draw_(ElemArea* a)
{
    Point2FCol& points = a->area().points().points();
    if (points.count() < 3) return;

    QPointF* ptsQt = new QPointF[points.count()];
    int current = 1;

    ptsQt[0] = mapPaperToPixels(points.get(0));
    for (int i = 1; i < points.count(); i++) {
        Point2F pt = points.get(i);
        QPointF ptQt = mapPaperToPixels(pt);
        if ( fabs(pt.x()-ptQt.x())+fabs(pt.y()-ptQt.y()) < 1.0) continue;

        ptsQt[current++] = ptQt;
    }

    if ( current < 3 ) return;

    painter_->setPen(Qt::NoPen);
    QColor color ( a->color().r(), a->color().g(), a->color().b(), a->alpha());
    painter_->setBrush(QBrush(color));

    painter_->drawPolygon(ptsQt, current);

    delete [] ptsQt;
}

//=============================================================================
void CanvasPainter::draw_(ElemCircle* c)
{
    double r = mapPaperToPixels(c->radius());

    if (r < 0.5) return;

    QPointF o = mapPaperToPixels(c->center());

    //if (o.x()-r < 0) return;
    //if (o.y()-r < 0) return;
    //if (o.x()+r >= size_.w()) return;
    //if (o.y()+r >= size_.h() ) return;

    QColor color ( c->color().r(), c->color().g(), c->color().b());

    if ( c->fill() ) {
        painter_->setBrush(QBrush(color));
        painter_->setPen(Qt::NoPen);
    }
    else {
        painter_->setBrush(Qt::NoBrush);
        painter_->setPen(QPen(color, c->width()*ppm_));
    }

    painter_->drawEllipse(o, r, r);
}

//=============================================================================
void CanvasPainter::draw_(ElemBox* b)
{
    //<STEP>recalculate to real
    Point2F pt0;
    Point2F pt1;

    if (b->symbolicScale()) {
        pt0 = mapRealToPaper(b->origin());
        pt1 = pt0;

        pt0.add(mapSymbolicScaleV(b->pt0()));
        pt1.add(mapSymbolicScaleV(b->pt1()));
    }
    else {
        pt0 = mapRealToPaper(b->pt0());
        pt1 = mapRealToPaper(b->pt1());
    }

    //<STEP>line width
    double lineWidth = 1;
    if (b->symbolicScaleWidth()) {
        lineWidth = mapSymbolicScale(b->lineWidth());
    }
    else {
        lineWidth = mapRealToPaper(b->lineWidth());
    }

    //<STEP>papper to pixels
    QPointF p0 = mapPaperToPixels(pt0);
    QPointF p1 = mapPaperToPixels(pt1);

    lineWidth = mapPaperToPixels(lineWidth);

    //<STEP>draw qt
    QColor color (b->color().r(), b->color().g(), b->color().b());
    painter_->setBrush(Qt::NoBrush);
    painter_->setPen(QPen(color, lineWidth));

    QPoint tl(p0.x(), p1.y());
    QPoint rb(p1.x(), p0.y());
    painter_->drawRect(QRect(tl, rb));
}

//=============================================================================
void CanvasPainter::draw_(ElemPixmap* p)
{
    //p->pixmap();
    //p->pixmap()->isNull();

    bool isValid = p->pixmap() && !p->pixmap()->isNull();
    if ( isValid == false ) isValid = p->image() && !p->image()->isNull();
    if ( isValid == false ) return;

    if ( p->image() ) {
        Point2F p0 = p->imageRect().point(0);
        Point2F p1 = p->imageRect().point(1);
        Point2F p3 = p->imageRect().point(3);

        /*cout << "image premap 0: ["  << p0.x() << "," << p0.y() << "] "
                          << "1: ["  << p1.x() << "," << p1.y() << "] "
                          << "3: ["  << p3.x() << "," << p3.y() << "]"  << endl;*/

        QPointF ptQt0 = mapPaperToPixels(p0);
        QPointF ptQt1 = mapPaperToPixels(p1);
        QPointF ptQt3 = mapPaperToPixels(p3);

        /*cout << "image 0: ["  << ptQt0.x() << "," << ptQt0.y() << "] "
                   << "1: ["  << ptQt1.x() << "," << ptQt1.y() << "] "
                   << "3: ["  << ptQt3.x() << "," << ptQt3.y() << "]"  << endl;*/

        Point2F pt0(ptQt0.x(), ptQt0.y());
        Point2F pt1(ptQt1.x(), ptQt1.y());
        Point2F pt3(ptQt3.x(), ptQt3.y());

        double d01 = Vector2F(pt0, pt1).getLength()/p->image()->width();
        double d03 = Vector2F(pt0, pt3).getLength()/p->image()->height();

        painter_->scale( d01 * scale()  > 0 ? 1.0 : -1.0,
                         d03 * scale() > 0  ? 1.0 : -1.0 );

        QTransform oldMatrix = painter_->transform();

        Vector2F angle(p->imageRect().point(0), p->imageRect().point(1));
        QPointF translation = painter_->transform().inverted().map(QPointF(ptQt0.x(), ptQt0.y()));

        painter_->translate( translation.x(), translation.y()-p->image()->height() );
        painter_->rotate(-angle.getAngle().get());
        //painter_->drawImage(0, 0, *p->image());

        painter_->setTransform(oldMatrix);

        const Box2F& box = p->pixmapBox();

        QPointF beg = mapPaperToPixels(Point2F(box.x().beg(), box.y().beg()));
        QPointF end = mapPaperToPixels(Point2F(box.x().end(), box.y().end()));

        beg = mapPaperToPixels(p->imageRect().point(0));
        QPointF pp1 = mapPaperToPixels(p->imageRect().point(1));
        end = mapPaperToPixels(p->imageRect().point(2));
        QPointF pp3 = mapPaperToPixels(p->imageRect().point(3));

        /*cout << "begi: ["  << beg.x() << "," << beg.y() << "] "
             << "endi: ["  << end.x() << "," << end.y() << "] " << endl;*/

        double X = beg.x();
        double Y = end.y();
        double W = fabs(beg.x()-end.x());
        double H = fabs(beg.y()-end.y());

        QRectF boxQt( X, Y, W, H);

        p->imageRect().point(0);

        painter_->drawImage(boxQt, *p->image());

        /*painter_->setBrush(QBrush(QColor(255, 150, 50)));
        painter_->setPen(Qt::NoPen);
        painter_->drawEllipse(beg.x(), beg.y(), 5, 5);
        painter_->drawEllipse(end.x(), end.y(), 5, 5);
        painter_->drawEllipse(pp1.x(), pp1.y(), 5, 5);
        painter_->drawEllipse(pp3.x(), pp3.y(), 5, 5);*/
    }
    else {
        const Box2F& box = p->pixmapBox();

        QPointF beg = mapPaperToPixels(Point2F(box.x().beg(), box.y().beg()));
        QPointF end = mapPaperToPixels(Point2F(box.x().end(), box.y().end()));

        /*cout << "beg: ["  << beg.x() << "," << beg.y() << "] "
             << "end: ["  << end.x() << "," << end.y() << "] " << endl;*/

        double X = beg.x()<end.x() ? beg.x() : beg.x();
        double Y = beg.y()<end.y() ? end.y() : end.y();
        double W = fabs(beg.x()-end.x());
        double H = fabs(beg.y()-end.y());

        QRectF boxQt( X, Y, W, H);

        //if ( boxQt.left()   >= size_.w() ) return;
        //if ( boxQt.right()  <  0         ) return;
        //if ( boxQt.bottom() <  0         ) return;
        //if ( boxQt.top()    >= size_.h() ) return;

        //QPixmap* pp = const_cast<QPixmap*>(p->pixmap_);
        //pp->setDevicePixelRatio(0.05);

        double opacity = painter_->opacity();
        painter_->setOpacity(p->transparency_);
        painter_->drawPixmap(boxQt.toRect(), *p->pixmap());
        painter_->setOpacity(opacity);
    }
}

//=============================================================================
double CanvasPainter::dx_(Qt::AlignmentFlag flag, double width)
{
    int result = 0;

    switch ( flag )
    {
    case Qt::AlignHCenter: result = -width/2; break;
    case Qt::AlignRight:  result = -width; break;
    default: break;
    }

    return result;
}

//=============================================================================
double CanvasPainter::dy_(Qt::AlignmentFlag flag, double height)
{
    int result = -0.25*height;

    switch (flag)
    {
    case Qt::AlignVCenter: result =    -height; break;
    case Qt::AlignBottom:  result += -2*height; break;
    default: break;
    }

    return result;
}

//=============================================================================
