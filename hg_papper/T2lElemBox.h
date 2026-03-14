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
class ElemBox : public Element {
//=============================================================================
public:
//<ENUMS>
//<CONSTRUCTION>
    ElemBox( const Point2F& pt0, const Point2F& pt1, CanvasI& canvas,
             const Color& color, double width = 1.0, bool symbolicScaleWidth = true,
             unsigned char alpha = 255,
             const Point2F& origin = Point2F(), bool symbolicScale = false );
    virtual ~ElemBox(void) {;}
//<NEIGHBOURS>
//<METHODS>
    double        lineWidth()              { return width_; }
    void          setLineWidth( double width ) { width_ = width; }
    bool          symbolicScaleWidth()     { return symbolicScaleWidth_; }

    unsigned char alpha() const            { return alpha_; }
    Point2F       pt0()                    { return pt0_; }
    Point2F       pt1()                    { return pt1_; }

    Point2F       origin()                 { return origin_; }
    bool          symbolicScale()          {return symbolicScale_; }
//=============================================================================
//<OVERRIDES>
    virtual ECategory category() { return ELEM_BOX; }
protected:
//<DATA>
    unsigned char  alpha_;

    Point2F        pt0_;
    Point2F        pt1_;

    Point2F        origin_;
    AngleXcc       originAngle_;

    bool           symbolicScale_;

    double         width_;
    bool           symbolicScaleWidth_;
};

} // namespace T2l
