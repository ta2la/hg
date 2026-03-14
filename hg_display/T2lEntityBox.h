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
#pragma once

#include "T2lEntityStyled.h"
#include "T2lSymbolDefs.h"
#include "T2lAngleXcc.h"
#include "T2lEnPoint.h"

namespace T2l
{

//=============================================================================
class EntityBox : public Entity {
//=============================================================================
public:
//<CONSTRUCTION>
    EntityBox( const Point2F& origin, const Point2F& originRelative,
               double height, double width, bool heightIsSymbolic,
               double lineWidth, bool lineWidthIsSymbolic);
    virtual ~EntityBox() {}
//<METHODS>
    Point2F    origin() { return origin_; }
//=============================================================================
//<OVERRIDES>
    virtual void draw(Canvas* canvas);
//<DATA>
    Point2F         origin_;
    Point2F         originRelative_;
    double          height_;
    double          width_;
    bool            heightIsSymbolic_;

    double lineWidth_;
    bool lineWidthIsSymbolic_;
};

} // namespace T2l
