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
#include "T2lSymbolDefs.h"
#include "T2lAngleXcc.h"

#include <QString>

namespace T2l
{
//=============================================================================
class ComponentText : public T2l::Component {
//=============================================================================
public:
//<CONSTRUCTION>
    ComponentText( const QString& text, const Point2F& position, double height = 2,
                 const Color& color = Color::BLACK,
                 EPositionH positionH = POSITION_H_LEFT,
                 EPositionV positionV = POSITION_V_TOP,
                 bool bold = false, AngleXcc angle = AngleXcc(0));
    virtual ~ComponentText(void) {;}
//<METHODS>
    const QString&      text() const      { return text_;      }
    const T2l::Point2F& position() const  { return position_;  }
    double              height() const    { return height_;    }
    EPositionH          positionH() const { return positionH_; }
    EPositionV          positionV() const { return positionV_; }
    bool                bold() const      { return bold_;      }
    AngleXcc            angle() const     { return angle_;     }

    void                setHeight(double height) { height_ = height;      }
//=============================================================================
//<OVERRIDES>
    virtual ECategory category() { return COMPONENT_TEXT; }
protected:
//<DATA>
    QString     text_;
    Point2F     position_;
    EPositionH  positionH_;
    EPositionV  positionV_;
    double      height_;
    bool        bold_;
    AngleXcc    angle_;
};

} // namespace T2l
