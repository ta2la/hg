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

#include "T2lSitem.h"
#include "T2lColor.h"
#include "T2lPoint2.h"
#include "T2lIntervalF.h"

namespace T2l
{
//=============================================================================
class SitemCircle : public Sitem {
//=============================================================================
public:
//<CONSTRUCTION>
    SitemCircle( const Point2F& center, double radius,
                      const Color& color = Color::BLACK,
                      bool fill = true, double width = 0.5);
    virtual ~SitemCircle(void) {;}
//<METHODS>
    Point2F center() const { return center_; }
    double  radius() const { return radius_; }
    bool    fill()   const { return fill_;   }
    double  width()  const { return width_;  }
//=============================================================================
//<OVERRIDES>
    virtual EType type(void) const { return SITEM_CIRCLE; }
    virtual Box2F bound(void) { return Box2F( IntervalF(-radius_, radius_), IntervalF(-radius_, radius_) ); }
protected:
//<DATA>
    Point2F center_;
    double  radius_;
    bool    fill_;
    double  width_;
};

} // namespace T2l
