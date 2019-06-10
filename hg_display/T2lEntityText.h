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

#include "T2lSymbolDefs.h"
#include "T2lEntityStyled.h"
#include "T2lAngleXcc.h"
#include <QString>

namespace T2l
{
//=============================================================================
class EntityText : public EntityStyled {
//=============================================================================
public:
//<ENUMS>
//<CONSTRUCTION>
    EntityText( const QString& text, const Point2F& position,
                EPositionH alignH = POSITION_H_LEFT, EPositionV alignV = POSITION_V_TOP,
                AngleXcc angle = AngleXcc(0),
                const Point2F& offset = Point2F(0, 0), StyleChange* styleChange = NULL );
    EntityText( const QString& text, const Point2F& position,
                EPositionH alignH, EPositionV alignV,
                Style* style, bool styleOwner,
                AngleXcc angle = AngleXcc(0),
                const Point2F& offset = Point2F(0, 0), StyleChange* styleChange = NULL );
    virtual ~EntityText(void) {}
//<METHODS>
    QString text() { return text_; }
    const Point2F& position() const { return position_; }

    EPositionH    alignH() const { return alignH_; }
    EPositionV    alignV() const { return alignV_; }
    const Point2F offset() const { return offset_; }
    AngleXcc      angle() const { return angle_; }
//=============================================================================
//<OVERRIDES>
    virtual void draw(Canvas* canvas);
protected:
//<DATA>
    QString     text_;
    Point2F     position_;
    EPositionH  alignH_;
    EPositionV  alignV_;
    AngleXcc    angle_;
    Point2F     offset_;

//<INTERNALS>
    void draw_(Canvas* canvas, const Point2F& position, const AngleXcc& angle,
                            const Color& colorArg, double heightArg, bool bold);
};

} // namespace T2l
