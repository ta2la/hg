//
// Copyright (C) 2015 Petr Talla. [petr.talla@gmail.com]
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
#include "T2lWidget.h"
#include "T2lDisplayDynamic.h"
#include "T2lDisplayBmp.h"
#include "T2lEntityPack.h"
//#include "T2lTimeObject.h"

#include <QPainter>

#include <assert.h>
#include <iostream>
#include <stdlib.h>

using namespace T2l;
using namespace std;

//=============================================================================
Widget::Widget(const Point2F& origin, double scale) :
    Display(origin, scale)
    //resized_(true)
{
    setMouseTracking(true);
    setAutoFillBackground(false);
    setAttribute(Qt::WA_NoBackground, true);
    
    displayDynamic_ = new DisplayDynamic();
    displayDynamic_->move(0,0);
    displayDynamic_->resize(400, 250);
    displayDynamic_->setParent(this);
    
    displayDynamic_->show();
}

//=============================================================================
Widget::~Widget()
{
    fabs(0);
}

//=============================================================================
void Widget::closeEvent(QCloseEvent *event)
{
    deleteLater();
    QWidget::closeEvent(event);
}

//=============================================================================
void Widget::updateDynamic()
{
    displayDynamic_->update();
}

//=============================================================================
void Widget::resizeEvent(QResizeEvent* event)
{
    assert(bitmap_ != NULL);
    displayDynamic_->resize( width()-edge_[EDGE_RIGHT]-edge_[EDGE_LEFT],
                             height()-edge_[EDGE_TOP]-edge_[EDGE_BOTTOM]);
    displayDynamic_->move(edge_[EDGE_LEFT], edge_[EDGE_TOP]);
    //resized_ = true;
    QWidget::resizeEvent(event);

    //BAD HACK
    originSet(Point2F(origin_.x()+10e-9, origin_.y()+10e-9));
}

//=============================================================================
void Widget::paintEvent( QPaintEvent* )
{
    //TimeObject to;

    static int id = 0;
    id++;
    if (id %100 == 0) return;

    if (bitmap_ == NULL ) return;

    if (isBitmapFresh_() == false) {
        bitmap_->bmpUpdate();
    }

    QPainter paint;
    paint.begin(this);

    double dx = (double)(bitmap_->bmpOrigin_.x() - origin().x() ) * scale_.scaleX() * ppm_;
    double dy = (double)(bitmap_->bmpOrigin_.y() - origin().y() ) * scale_.scaleY() * ppm_ + ( bitmap_->bmpPixmap->height()-height() );

    double w = width()  - edge_[EDGE_LEFT] - edge_[EDGE_RIGHT];
    double h = height() - edge_[EDGE_TOP]  - edge_[EDGE_BOTTOM];

    paint.drawPixmap( edge_[EDGE_LEFT], edge_[EDGE_TOP], (int)w, (int)h,
                      *bitmap_->bmpPixmap, (int)(-dx), (int)(dy+edge_[EDGE_TOP]+edge_[EDGE_BOTTOM]), (int)w, (int)h );

    cleanDrawing_(paint);

    paint.setPen(Qt::NoPen);
    paint.setBrush(Qt::gray);
    if ( edge_[EDGE_LEFT]   > 0 ) paint.drawRect(0,            0,                  edge_[EDGE_LEFT], height());
    if ( edge_[EDGE_RIGHT]  > 0 ) paint.drawRect(width()-edge_[EDGE_RIGHT],       0,                  edge_[EDGE_RIGHT], height());
    if ( edge_[EDGE_TOP]    > 0 ) paint.drawRect(0,            0,                  width(),            edge_[EDGE_TOP]);
    if ( edge_[EDGE_BOTTOM] > 0 ) paint.drawRect(0,            height()-edge_[EDGE_BOTTOM], width(), edge_[EDGE_BOTTOM]);

    /*char buff[100];
    itoa(id, buff, 10);
    paint.setPen(QPen(QColor(125,125,125)));
    paint.setBrush(QBrush(QColor(125,125,125)));

    QFont font("courier");
    font.setPointSizeF(30);
    font.setBold(true);
    paint.setFont(font);*/

    //paint.drawText(50, 50, buff);

    paint.end();

    //cout << "//////// paint: " << to.existenceTimeSec() << endl;
}

//=============================================================================
Size2F Widget::size() const
{
    return Size2F( fabs( width()-edge_[EDGE_LEFT]-edge_[EDGE_RIGHT]) / (ppm_*fabs(scale(Scale2::X))),
                   fabs( height()-edge_[EDGE_TOP]-edge_[EDGE_BOTTOM]) / (ppm_*fabs(scale(Scale2::Y))) );
}

//=============================================================================
void Widget::leaveEvent(QEvent*)
{
    EntityPack* pack = entityPack();
    if (pack == NULL ) return;
    pack->cleanDynamic();
    pack->dynamicRefresh();
}

//=============================================================================
bool Widget::isBitmapFresh_()
{
    /*if ( resized_ ) {
        resized_ = false;
        return false;
    }*/
    if ( Display::isBitmapFresh_() == false ) return false;
    if ( bitmap_->bmpPixmap->width() != widthPx_() ) return false;
    if ( bitmap_->bmpPixmap->height() != heightPx_()) return false;
    return true;
}

//=============================================================================
void Widget::cleanDrawing_box_( QPainter& paint, const Box2I& box )
{
    paint.setPen(Qt::NoPen);
    paint.setBrush(QColor(colorBackground_.r(), colorBackground_.g(), colorBackground_.b()));
    paint.drawRect(box.x().beg(), height()-box.y().end(), box.x().getLength(), box.y().getLength());
}

//=============================================================================
Point2F Widget::mapPixelInMetric_(const Point2F pt)
{
    double x = pt.x()*1.0/(ppm_*scale(Scale2::X)) + origin().x();
    double y = (height()-pt.y())*1.0/(ppm_*scale(Scale2::Y)) + origin().y();
    return Point2F(x, y);
}

//=============================================================================
void Widget::refresh_()
{
    update();
}

//=============================================================================
void Widget::cleanDrawing_(QPainter& paint)
{
    if (bitmap_ == NULL) return;

    int x = (int)((double)(bitmap_->bmpOrigin_.x() - origin().x() ) * scale_.scaleX() * ppm_);
    int y = (int)((double)(bitmap_->bmpOrigin_.y() - origin().y() ) * scale_.scaleY() * ppm_);

    if (x > 0) cleanDrawing_box_( paint, Box2I( IntervalI(edge_[EDGE_LEFT], x),
                                                IntervalI(height()-edge_[EDGE_TOP], edge_[EDGE_BOTTOM])));
    if (y > 0) cleanDrawing_box_( paint, Box2I( IntervalI(edge_[EDGE_LEFT], width()-edge_[EDGE_RIGHT]),
                                                IntervalI(y, edge_[EDGE_BOTTOM])));

    int maxX = x + bitmap_->bmpPixmap->width();
    int maxY = y + bitmap_->bmpPixmap->height();

    if ( maxX < width() - edge_[EDGE_LEFT] - edge_[EDGE_RIGHT] ) {
        cleanDrawing_box_( paint, Box2I( IntervalI(maxX+edge_[EDGE_LEFT], width()-edge_[EDGE_RIGHT]),
                                         IntervalI( height()-edge_[EDGE_TOP], edge_[EDGE_BOTTOM])));
    }
    if ( maxY < height() - edge_[EDGE_TOP] - edge_[EDGE_BOTTOM] ) {
        cleanDrawing_box_( paint, Box2I( IntervalI(edge_[EDGE_LEFT], width()-edge_[EDGE_RIGHT]),
                                         IntervalI( height()-edge_[EDGE_TOP], edge_[EDGE_BOTTOM])));
    }
}

//=============================================================================
