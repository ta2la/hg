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
#include "T2lEntityBox.h"
#include "T2lCanvas.h"
#include "T2lSfeatSymbol.h"
#include "T2lElexSymbol.h"
#include "T2lStyleChange.h"
#include "T2lEnPointXy.h"
#include "T2lElemBox.h"

using namespace T2l;

//=============================================================================
EntityBox::EntityBox( const Point2F& origin, const Point2F& originRelative,
                      double height, double width, bool heightIsSymbolic,
                      double lineWidth, bool lineWidthIsSymbolic ) :
    origin_(origin),
    originRelative_(originRelative),
    height_(height),
    width_(width),
    heightIsSymbolic_(heightIsSymbolic),
    lineWidth_(lineWidth),
    lineWidthIsSymbolic_(lineWidthIsSymbolic)
{
}

//=============================================================================
void EntityBox::draw(Canvas* canvas)
{
    double h0 = height_*originRelative_.x();
    double w0 = width_*originRelative_.y();

    double h1 = height_*(1.0-originRelative_.x());
    double w1 = width_*(1.0-originRelative_.y());

    Color color = Color::BLACK;
    if ( lineWidthIsSymbolic_ ) color = Color::BROWN;

    if (heightIsSymbolic_) {
        ElemBox box(Point2F(-h0,-w0), Point2F(h1,w1), *canvas, color,
                lineWidth_, lineWidthIsSymbolic_, 255, origin(), true );
        canvas->draw(&box);
    }
    else {
        Point2F pt0(origin_);
        pt0.add(Vector2F(-h0, -w0));

        Point2F pt1(origin_);
        pt1.add(Vector2F(h1, w1));

        ElemBox box( pt0, pt1, *canvas, color,
                     lineWidth_, lineWidthIsSymbolic_);
        canvas->draw(&box);
    }
}

//=============================================================================
