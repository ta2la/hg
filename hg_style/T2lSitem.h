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

#include "T2lColor.h"
#include "T2lBox2.h"
#include "T2lItem.h"
#include "T2lItemCol.h"

namespace T2l
{
//=============================================================================
class Sitem : public Item {
//=============================================================================
public:
//<ENUMS>
    enum EType
    {
        SITEM_LINE,
        SITEM_AREA,
        SITEM_CIRCLE,
        SITEM_TEXT
    };
//<CONSTRUCTION>
    Sitem( const Color& color );
    virtual ~Sitem(void)      {;}
//<METHODS>
    virtual EType type(void) const = 0;
    virtual Box2F bound(void)      = 0;
    Color   color(void) const      { return color_; }
//=============================================================================
//<OVERRIDES>
protected:
//<DATA>
    Color color_;
};

typedef ItemCol<Sitem> SitemCol;

} // namespace T2l
