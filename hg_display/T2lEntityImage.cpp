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
#include "T2lEntityImage.h"
#include "T2lComponentImage.h"
#include "T2lCanvas.h"
#include "T2lArea2.h"
#include "T2lIntervalF.h"

using namespace T2l;

//=============================================================================
EntityImage::EntityImage(const Box2F& bound, QPixmap* pixmap, bool owner) :
    Entity(NULL),
    pixmap_(pixmap),
    image_(nullptr),
    owner_(owner)
{
    bound_ = bound;
}

EntityImage::EntityImage(const Box2F& bound, QImage* image) :
    Entity(NULL),
    pixmap_(nullptr),
    image_(image),
    owner_(false)
{
    bound_ = bound;
}

//=============================================================================
EntityImage::~EntityImage()
{
    destroy_();
}

//=============================================================================
void EntityImage::destroy_()
{
    if (pixmap_ == NULL) return;
    if (owner_ == false) return;
    delete pixmap_;
}

//=============================================================================
void EntityImage::pixmapSet(const QPixmap* pixmap, bool owner)
{
    destroy_();
    pixmap_ = pixmap;
    owner_  = owner;
}

//=============================================================================
void EntityImage::draw(Canvas* canvas)
{
    Point2F boundFrom(bound_.x().beg(), bound_.y().beg());
    Point2F boundTo(bound_.x().end(), bound_.y().end());

    Point2F  from = canvas->mapRealToPaper(boundFrom);
    Point2F  to   = canvas->mapRealToPaper(boundTo);

    if ( pixmap_ != nullptr ) {
        ComponentPixmap component( pixmap_, Box2F( IntervalF(from.x(), to.x()),
                                               IntervalF(from.y(), to.y()) ) );
        for ( Area2* clip : clips_ ) {

            component.clips().push_back(Area2());
            Point2FCol points = clip->points().points();

            for ( int i = 0; i < points.count(); i++ ) {
                Point2F pti = points.get(i);
                Point2F ptiReal = canvas->mapRealToPaper(pti);
                component.clips().back().points().points().add(ptiReal);

                /*component.clips().pop_back(area);
                Area& areaComp = component.clips().back();
                Point2Col& areaPts = area.points().points();
                for ( int i = 0; i < areaPts.count(); )
                component.clips().back() = area;*/
            }
        }

        canvas->draw(&component);
    }
    else if (image_ != nullptr) {
        Vector2F dir(to.x()-from.x(), 0);
        double height = to.y()-from.y();
        ComponentPixmap component( image_,  Rectangle2(from, dir, height ) );
        canvas->draw(&component);
    }
}

//=============================================================================
