//
// Copyright (C) 2020 Petr Talla. [petr.talla@gmail.com]
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

#include "T2lEntity.h"
#include "T2lColor.h"

namespace T2l
{

//=============================================================================
class EntityEnLinear : public Entity {
//=============================================================================
public:
//<CONSTRUCTION>
    EntityEnLinear(const Color& color, const Color& colorLine, int transp);
    virtual ~EntityEnLinear(void) {}
//<METHODS>
    void pointAdd( const Point2F& pt, const Point2F& offset);
//=============================================================================
//<OVERRIDES>
    virtual void draw(Canvas* canvas);

    Color color_;
    Color colorLine_;
    int   transp_;

    Point2FCol points_;
    Point2FCol ofsets_;
};

} // namespace T2l
