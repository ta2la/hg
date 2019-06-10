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

#include "T2lEntityLinear.h"

namespace T2l
{

class Lstyle;

//=============================================================================
class EntityLine : public EntityLinear {
//=============================================================================
public:
//<CONSTRUCTION>
    EntityLine( Style& style, bool styleOwner = false, StyleChange* styleChange = NULL );
    EntityLine( const Color color = Color::BLACK, double width = 0.25,
                StyleChange* styleChange = NULL );
    EntityLine( const Point2F& p0, const Point2F& p1, const Color color = Color::BLACK, double width = 0.25 );
    virtual ~EntityLine(void) {}
//<METHODS>
//=============================================================================
//<OVERRIDES>
    virtual void draw(Canvas* canvas);
};

} // namespace T2l
