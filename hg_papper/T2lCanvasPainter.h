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

class ElemLine;
class ElemCircle;
class ElemArea;
class ElemText;
class ElemPixmap;
class ElemBox;

//=============================================================================
class CanvasPainter : public Canvas {
//=============================================================================
public:
//<CONSTRUCTION>
    CanvasPainter( QPainter& painter, const Point2F& origin, const Size2F& size,
                   double scale = 1.0/100, double ppm = 4000.0,
                   bool xorArg = false );
    virtual ~CanvasPainter() {}
//<METHODS>
    const Point2F& origin() const { return origin_; } //APTA💊
    void  originSet(const Point2F& pt) { origin_ = pt; } //APTA💊

    double  mapPaperToPixels(double d) const { return d*ppm_; }
    QPointF mapPaperToPixels(const Point2F& p) const;
//=============================================================================
//<OVERRIDES>
    virtual bool draw(Element* c);
    virtual double width(Element* c);
//protected:
//<DATA>
    Point2F   origin_; //in real units
    //Size2F    size_;
    double    originDyPixels_;

    double    ppm_;

    QPainter* painter_;
//<INTERNALS>
    void draw_(ElemLine* l);
    void draw_(ElemArea* a);
    void draw_(ElemCircle* c);
    void draw_(ElemText* t);
    void draw_(ElemPixmap* p);
    void draw_(ElemBox* p);

    double dx_(Qt::AlignmentFlag flag, double width);
    double dy_(Qt::AlignmentFlag flag, double height);
};

} // namespace T2l
