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
#include "T2lDisplayDynamic.h"
#include "T2lWidget.h"
#include "T2lCanvasPainter.h"
#include "T2lEntityPack.h"
#include <QPainter>
#include <assert.h>

using namespace T2l;

//=============================================================================
DisplayDynamic::DisplayDynamic()
{
    setMouseTracking(true);
    setAttribute(Qt::WA_TransparentForMouseEvents, true);

    setAttribute(Qt::WA_NoSystemBackground, true);
}

//=============================================================================
void DisplayDynamic::paintEvent( QPaintEvent* event )
{
    Widget* w = dynamic_cast<Widget*>(parentWidget());

    assert( w->entityPack() != nullptr );
    assert( w->bitmap_ != nullptr );

    Box2F box( w->origin(),
               Point2F( w->origin_.x()+width()/(w->ppm()*w->scale() ),
                        w->origin_.y()+height()/(w->ppm()*w->scale() )));

    QPainter painter;
    painter.begin(this);

    double ratio = 1.5;
    CanvasPainter canvas( painter, Point2F(0, 0), Size2F(width(), height()),
                          w->scale(), w->ppm());
    canvas.originSet(Point2F(w->origin_.x(), w->origin_.y()));//APTA💊
//    canvas.boundSet(box);//APTA💊

    w->entityPack()->drawDynamic(canvas);

    painter.end();
}

//=============================================================================
void DisplayDynamic::drawPainter( QPainter& painter )
{
    Widget* w = dynamic_cast<Widget*>(parentWidget());

    CanvasPainter canvas( painter, Point2F(0, 0), Size2F(width(), height()),
                         w->scale(), w->ppm());
    canvas.originSet(Point2F(w->origin_.x(), w->origin_.y()));//APTA💊
    w->entityPack()->drawDynamic(canvas);
}

//=============================================================================
