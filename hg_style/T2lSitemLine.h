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
#include "T2lPolyLine2.h"

namespace T2l
{
//=============================================================================
class SitemLine : public Sitem {
//=============================================================================
public:
//<CONSTRUCTION>
    SitemLine( const Color& color, double width = 1);
    virtual ~SitemLine(void) {;}
//<NEIGHBOURS>
    PolyLine2& points() { return points_; }
//<METHODS>
    double  width()  const { return width_;  }
//=============================================================================
//<OVERRIDES>
    virtual EType type(void) const { return SITEM_LINE; }
    virtual Box2F bound(void) { return points_.points().bound(); }
protected:
//<DATA>
    PolyLine2 points_;
    double    width_;
};

} // namespace T2l
