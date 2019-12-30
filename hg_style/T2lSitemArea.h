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
#include "T2lArea2.h"

namespace T2l
{
//=============================================================================
class SitemArea : public Sitem {
//=============================================================================
public:
//<CONSTRUCTION>
    SitemArea( const Color& color);
    virtual ~SitemArea(void) {;}
//<NEIGHBOURS>
    Area2& points() { return points_; }
//<METHODS>
//=============================================================================
//<OVERRIDES>
    virtual EType type(void) const { return SITEM_AREA; }
    virtual Box2F bound(void) { return points_.points().points().bound(); }
protected:
//<DATA>
    Area2 points_;
};

} // namespace T2l
