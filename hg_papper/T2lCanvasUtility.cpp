//
// Copyright (C) 2024 Petr Talla. [petr.talla@gmail.com]
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
#include "T2lCanvasUtility.h"
#include "T2lCanvasPainter.h"
#include "T2lSymbol.h"
#include "T2lElexSymbol.h"
#include "T2lSfeatSymbol.h"

#include <QPainter>

using namespace T2l;

//=============================================================================
QImage* CanvasUtility::drawSymbol(Style* style)
{
    double SIZE  = 200;

    QImage* image = new QImage(SIZE, SIZE, QImage::Format_RGB32);
    image->fill(QColor(200, 200, 255));

    QPainter painter(image);

    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::TextAntialiasing);


    double PPM   = 10;
    double SCALE = 1000;

    double origin = -0.5*SIZE/PPM/SCALE;

    CanvasPainter canvas( painter, Point2F(origin, origin), Size2F(SIZE, SIZE), SCALE, PPM);

    double height = 9000;

    SfeatCol& sfeats = style->sfeats();
    for ( int i = 0; i < sfeats.count(); i++) {
        Symbol* symbol2 = sfeats.get(i)->getAsSymbol()->symbol();
        ElexSymbol e2( Point2F(0, 0), *symbol2, Color(Color::BLACK), AngleXcc(0),
              ANGLE_ZERO_COORDS, nullptr, height);
        if ( canvas.draw(&e2) == false ) e2.decompose(&canvas);
    }

    painter.end();

    return image;
}

//=============================================================================
