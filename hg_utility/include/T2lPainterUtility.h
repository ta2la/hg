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
#pragma once

#include "T2lPoint2.h"
#include "T2lColor.h"
#include "T2lVector2.h"
#include "T2lAngle.h"
#include "T2lSymbolDefs.h"

#include <QFontMetrics>
#include <QPainter>

namespace T2l
{

class ComponentText;

//=============================================================================
class PainterUtility {
//=============================================================================
public:
//<CONSTRUCTION>
    PainterUtility() = delete;
//<METHODS>
    static void drawText  ( QPainter& painter, const QString& text, const Point2F& pos,
                            const AngleXcc& angle, double size, const Color& c,
                            EPositionH positionH, EPositionV positionV, bool geometry = false, bool bold = false );
    static int  drawTextFormat( QPainter& painter, const QString& text, const Point2F& pos,
                            double size, const Color& c );
    static void drawLine  ( QPainter& painter, const Point2F p0, const Point2F p1, const Color& color, double width);
    static void drawSquare( QPainter& painter, const Point2F p, const Color& color, double size, unsigned char a = 30);
//=============================================================================
//protected:
//<INTERNALS>
    static void drawTextGeometry_( QPainter& painter, const QString& text, QFontMetrics& fm,
                               const Point2F& pos, const AngleXcc& angle, double size,
                               EPositionH positionH, EPositionV positionV);
    static Vector2F drawTextDelta_( QFontMetrics& fm, const QString& text,
                                    EPositionH positionH, EPositionV positionV );
    static Point2F transformAngular(const Point2F& pt, const AngleXcc& angle);
//<FRIENDS>
};

} //namespace T2l
