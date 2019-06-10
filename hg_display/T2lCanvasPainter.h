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
#pragma once

#include "T2lCanvas.h"
#include "T2lSize2.h"
#include "T2lScale2.h"
#include <QPainter>

namespace T2l
{

class ComponentLine;
class ComponentCircle;
class ComponentArea;
class ComponentText;
class ComponentPixmap;

//=============================================================================
class CanvasPainter : public Canvas {
//=============================================================================
public:
//<CONSTRUCTION>
    CanvasPainter( QPainter& painter, const Point2F& origin, const Size2F& size,
                   const Scale2& scale = Scale2(1.0/100, 1.0/100), double ppm = 4000.0,
                   bool xorArg = false );
    virtual ~CanvasPainter() {}
//<METHODS>
    const Point2F& origin() const { return origin_; }
    void  originSet(const Point2F& pt) { origin_ = pt; }

    double  mapPaperToPixels(double d) const { return d*ppm_; }
    QPointF mapPaperToPixels(const Point2F& p) const;
//=============================================================================
//<OVERRIDES>
    virtual bool   draw(Component* c);
//protected:
//<DATA>
    Point2F   origin_;
    Size2F    size_;

    double    ppm_;

    QPainter* painter_;
//<INTERNALS>
    void draw_(ComponentLine* l);
    void draw_(ComponentArea* a);
    void draw_(ComponentCircle* c);
    void draw_(ComponentText* t);
    void draw_(ComponentPixmap* p);

    double dx_(Qt::AlignmentFlag flag, double width);
    double dy_(Qt::AlignmentFlag flag, double height);
};

} // namespace T2l
