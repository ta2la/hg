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

#include "T2lElement.h"
#include "T2lSymbolDefs.h"
#include "T2lPolyLine2.h"
#include "T2lCanvasI.h"

namespace T2l
{
//=============================================================================
class ElemLine : public T2l::Element {
//=============================================================================
public:
//<ENUMS>
//<CONSTRUCTION>
    ElemLine( const Color& color, double width = 1.0, unsigned char alpha = 255 );
    virtual ~ElemLine(void) {;}
//<NEIGHBOURS>
    T2l::PolyLine2& points() { return points_; }
//<METHODS>
    double        width()                  { return width_; }
    void          setWidth( double width ) { width_ = width; }
    unsigned char alpha() const            { return alpha_; }
//=============================================================================
//<OVERRIDES>
    virtual ECategory category() { return ELEM_LINE; }
    void pointAdd(const Point2F& pt, CanvasI& canvas) {
        points().points().add(canvas.mapRealToPaper(pt));
    }
protected:
//<DATA>
    PolyLine2      points_;
    double         width_;
    unsigned char  alpha_;
};

} // namespace T2l
