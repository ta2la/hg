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
#include "T2lDisplay.h"
#include "T2lDisplayBmp.h"
#include "T2lDisplayCol.h"
#include "T2lEntityPack.h"
#include <assert.h>
#include <iostream>
#include <QPixmap>

using namespace T2l;
using namespace std;

//=============================================================================
Display::Display(const Point2F& origin, double scale) :
    bitmap_( new DisplayBmp(*this, origin, scale, 600, 400)),
    origin_(origin),
    scale_(scale, scale),
    ppm_(4000.0),
    refreshLock_(0),
    refreshedLocked_(Fresh),
    overOffset_(Vector2F(0, 0))
{
    DisplayCol& vc = DisplayCol::instance();
    vc.add(this);

    edge_[EDGE_LEFT] = 5;
    edge_[EDGE_TOP] = 0;
    edge_[EDGE_RIGHT] = 0;
    edge_[EDGE_BOTTOM] = 0;
}

//=============================================================================
Display::~Display()
{
    if (bitmap_) delete bitmap_;
    DisplayCol::instance().remove(this);

    //delete entityPack_;
}

//=============================================================================
void Display::originSet(const Point2F& origin)
{
    origin_ = origin;
    //cout << "///// VIEW ORIGIN SET: " << origin_.x() << ", " << origin_.y() << endl;
}

//=============================================================================
void Display::scaleSet(double scale, Scale2::Dir dir)
{
    scale_.scaleSet(scale, dir);
    //cout << "///// VIEW SCALE SET: " << scale_.scaleX() << ", " << scale_.scaleY() << endl;
}

//=============================================================================
void Display::refresh()
{
    if ( refreshLock_ <= 0 ) {
        refresh_();
        return;
    }

    if ( refreshedLocked_ == Fresh ) refreshedLocked_ = Widget;
}

//=============================================================================
void Display::unlockRefresh()
{
    if ( --refreshLock_ > 0 ) return;
    if ( refreshLock_ <= 0 ) assert(0);

    if ( refreshedLocked_ == Bitmap ) {
        bitmap_->bmpUpdate();
    }
    else if ( refreshedLocked_ == Widget ) {
        refresh_();
    }
}

//=============================================================================
bool Display::isBitmapFresh_()
{
    int result = 0;

    if ( origin().x()         != bitmap_->bmpOrigin().x() )             result = 1;
    else if ( origin().y()    != bitmap_->bmpOrigin().y() )             result = 2;
    else if ( scale_.scaleX() > (bitmap_->bmpScale_.scaleX() + 10e-5) ) result = 3;
    else if ( scale_.scaleX() < (bitmap_->bmpScale_.scaleX() - 10e-5) ) result = 4;
    else if ( scale_.scaleY() > (bitmap_->bmpScale_.scaleY() + 10e-5) ) result = 5;
    else if ( scale_.scaleY() < (bitmap_->bmpScale_.scaleY() - 10e-5) ) result = 6;
    else if ( widthPx_()      != bitmap_->bmpPixmap->width() )          result = 7;
    else if ( heightPx_()     != bitmap_->bmpPixmap->height() )         result = 8;

    double h1 = heightPx_();
    double h2 = bitmap_->bmpPixmap->height();

    //cout << "** Hwidget: " << h1 << " Hbitmap: " << h2 << endl;

    if (result == 0) {
        return true;
    }
    else {
        return false;
    }

    return false;
}

//=============================================================================
Canvas Display::getRefCanvas() const
{
    Canvas result(scale_.scaleX(), 1.0);
    result.scaleYSet(scale_.scaleY());

    Box2F bound;
    bound.inflateTo(origin());
    bound.inflateTo(Point2F(origin().x()+size().w(), origin().y()+size().h()));
    result.boundSet(bound);

    result.overOffsetSet(overOffset_);

    return result;
}


//=============================================================================
