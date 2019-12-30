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
#include "T2lCmd_pan.h"
#include "T2lEntityPack.h"
#include "T2lDisplay.h"
#include "T2lWidget.h"
#include "T2lEntityImage.h"
#include "T2lCanvasPainter.h"
#include <QPixmap>
#include <QPainter>
#include <iostream>

using namespace T2l;
using namespace std;

QPixmap* Cmd_pan::pixmap_ = NULL;

//=============================================================================
Cmd_pan::Cmd_pan() :
    Cmd("pan"),
    pointKnown_(false),
    view_(NULL)
{
}

//=============================================================================
Cmd_pan::~Cmd_pan()
{

}

//=============================================================================
QString Cmd_pan::hint() const
{
    if ( pointKnown_ == false ) {
        return "enter first point";
    }
    else {
        return "enter second point";
    }
}

//=============================================================================
void Cmd_pan::enterPoint( const Point2F& pt, Display& view )
{
    if ( pointKnown_ ) {
        pointKnown_ = false;

        Point2F origin = view.origin();
        Vector2F delta(pt, point_);
        origin.add(delta);

        view.originSet(origin);

        view.refresh();

        view.entityPack()->cleanDynamic();

        pixmapBound_ = Box2F();

        //cant delete the pixmap here, because some refresh follows
        //deleted with delay
        //delete pixmap_;
        //pixmap_ = NULL;

        if ( once_ ) delete this;
    }
    else {
        point_ = pt;
        pointKnown_ =  true;

        view.entityPack()->cleanDynamic();

        Widget* widget = dynamic_cast<Widget*>(&view);
        createPixmap_( *widget);
    }
}

//=============================================================================
void Cmd_pan::enterMove( const Point2F& pt, Display& view )
{
    if ( pointKnown_ == false ) return;

    EntityPack* pack = view.entityPack();
    pack->cleanDynamic();

    Vector2F delta(pt, point_);
    delta.multiply(-1.0);
    Box2F bound = pixmapBound_;
    bound.moveBy(delta);

    EntityImage* entityImage = new EntityImage(bound);
    entityImage->pixmapSet(pixmap_, false);
    pack->addDynamic(entityImage);

    pack->dynamicRefresh();
}

//=============================================================================
void Cmd_pan::enterReset( Display& view )
{
    pointKnown_ = false;
    view.entityPack()->cleanDynamic();
}

//=============================================================================
void Cmd_pan::createPixmap_ ( Widget& view )
{
    if (pixmap_ != NULL) delete pixmap_;

    pixmap_ = new QPixmap( 2.0 * view.width()  - view.edge_[Widget::EDGE_LEFT]   - view.edge_[Widget::EDGE_RIGHT],
                           2.0 * view.height() - view.edge_[Widget::EDGE_BOTTOM] - view.edge_[Widget::EDGE_TOP] );
    Color c = view.colorBackground();
    pixmap_->fill(QColor(c.r(), c.g(), c.b()));

    QPainter painter;
    painter.begin(pixmap_);
    painter.setRenderHint(QPainter::TextAntialiasing);
    painter.setRenderHint(QPainter::Antialiasing);

    CanvasPainter display( painter, Point2F(0, 0), Size2F(pixmap_->width(), pixmap_->height()),
                           Scale2(view.scale(Scale2::X), view.scale(Scale2::Y)), view.ppm());

    Point2F bmpOrigin(view.origin().x()-view.size().w()/2.0, view.origin().y()-view.size().h()/2.0);
    pixmapBound_.inflateTo(bmpOrigin);
    Point2F bmpRt(bmpOrigin);
    bmpRt.add(Vector2F(view.size().w()*2, view.size().h()*2));
    pixmapBound_.inflateTo(bmpRt);

    display.originSet ( bmpOrigin );
    display.boundSet(pixmapBound_);
    view.entityPack()->draw(display);

    painter.end();
}

//=============================================================================
