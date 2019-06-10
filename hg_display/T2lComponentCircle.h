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

#include "T2lComponent.h"

namespace T2l
{
//=============================================================================
class ComponentCircle : public Component {
//=============================================================================
public:
//<ENUMS>
//<CONSTRUCTION>
    ComponentCircle( const Color& color, const Point2F& center, double radius,
                   bool fill = true, double width = 1.0 );
    virtual ~ComponentCircle(void) {}
//<METHODS>
    const Point2F& center() const { return center_; }
    double radius() const { return radius_; }
    void radiusSet(double radius) { radius_ = radius; }
    bool fill() const { return fill_; }
    double width() const { return width_; }
    void widthSet( double width)  { width_ = width; }
//=============================================================================
//<OVERRIDES>
    virtual ECategory category() { return COMPONENT_CIRCLE; }
protected:
//<DATA>
    T2l::Point2F center_;
    double       radius_;
    bool         fill_;
    double       width_;
};

} // namespace T2l
