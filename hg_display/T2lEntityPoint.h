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

#include "T2lEntityStyled.h"
#include "T2lSymbolDefs.h"
#include "T2lAngleXcc.h"
#include "T2lEnPoint.h"

namespace T2l
{

//=============================================================================
class EntityPoint : public EntityStyled {
//=============================================================================
public:
//<CONSTRUCTION>
    EntityPoint( EnPoint* origin, Style& style, bool styleOwner = false,
                  EAngleZero angleZero = ANGLE_ZERO_VIEW,
                  AngleXcc angle = AngleXcc(0.0), StyleChange* styleChange = NULL );
    EntityPoint( const Point2F& origin, Style& style, bool styleOwner = false,
                  EAngleZero angleZero = ANGLE_ZERO_VIEW,
                  AngleXcc angle = AngleXcc(0.0), StyleChange* styleChange = NULL );
    virtual ~EntityPoint() {}
//<METHODS>
    Point2F    origin(const Canvas* canvas) { return origin_->xy(canvas); }
    EAngleZero angleZero() const      { return angleZero_; }
    AngleXcc   angle() const          { return angle_; }
//=============================================================================
//<OVERRIDES>
    virtual void draw(Canvas* canvas);
//<DATA>
    EnPoint*      origin_;
    EAngleZero    angleZero_;
    AngleXcc      angle_;
};

} // namespace T2l
