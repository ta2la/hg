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
#include "T2lDisplayBmp.h"
#include "T2lDisplay.h"
#include "T2lCanvasPainter.h"
#include "T2lEntityPack.h"
#include <QPixmap>
#include <assert.h>
#include <iostream>

using namespace T2l;
using namespace std;

//=============================================================================
DisplayBmp::DisplayBmp( Display& view, const Point2F& origin,
                  double scale, int width, int height ) :
    bmpDisplay_(&view),
    bmpOrigin_(origin),
    bmpScale_(scale, scale),
    bmpPixmap(new QPixmap(width, height))
{
}

//=============================================================================
DisplayBmp::~DisplayBmp()
{
    assert (bmpPixmap);
    delete bmpPixmap;
    if (bmpDisplay_ == NULL) return;
    bmpDisplay_->bitmap_ = NULL;
}

//=============================================================================
void DisplayBmp::bmpUpdate()
{
    static int updateId_ = 0;
    cout << "))))))))))))))))))))))))))))) BITMAP UPDATE .... " << updateId_++ << endl;

    assert ( bmpDisplay_->entityPack() != NULL );

    if (bmpDisplay_->refreshLock_) {
        bmpDisplay_->refreshedLocked_ = Display::Bitmap;
        return;
    }

    bmpOrigin_ = bmpDisplay_->origin_;
    bmpScale_ = bmpDisplay_->scale_;

    if ( ( bmpPixmap->width()  != bmpDisplay_->widthPx_() ) ||
         ( bmpPixmap->height() != bmpDisplay_->heightPx_() ) ) {
        delete bmpPixmap;
        bmpPixmap = new QPixmap(bmpDisplay_->widthPx_(), bmpDisplay_->heightPx_());
    }

    const Color& bc = bmpDisplay_->colorBackground();
    bmpPixmap->fill(qRgba(bc.r(), bc.g(), bc.b(), 255));

    QPainter painter;
    painter.begin(bmpPixmap);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::TextAntialiasing);

    CanvasPainter display( painter, Point2F(0,0), Size2F(bmpPixmap->width(), bmpPixmap->height()),
                           Scale2( bmpScale(Scale2::X), bmpScale(Scale2::Y) ), bmpDisplay_->ppm_ );
    display.originSet(bmpOrigin());

    Box2F bmpBound;
    bmpBound.inflateTo(bmpOrigin());
    double w = bmpPixmap->width()/(bmpDisplay_->ppm()*bmpScale(Scale2::X));
    double h = bmpPixmap->height()/(bmpDisplay_->ppm()*bmpScale(Scale2::Y));
    bmpBound.inflateTo(Point2F(bmpOrigin().x()+w, bmpOrigin().y()+h));

    display.boundSet(bmpBound);
    bmpDisplay_->entityPack()->draw(display);

    painter.end();

    bmpDisplay_->refresh();
}

//=============================================================================
