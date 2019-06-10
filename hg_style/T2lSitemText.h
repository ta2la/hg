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
#include "T2lPoint2.h"
#include <QString>
#include "T2lSymbolDefs.h"

namespace T2l
{
//=============================================================================
class SitemText : public Sitem {
//=============================================================================
public:
//<ENUMS>

//<CONSTRUCTION>
    SitemText( const QString& text,           const Point2F& position,
                    double height  = 2.5,          const Color& color = Color::BLACK,
                    EPositionH alignH = POSITION_H_LEFT, EPositionV alignV     = POSITION_V_CENTER );
    virtual ~SitemText(void) {;}
//<METHODS>
    const QString&  text()       const { return text_;     }
    const Point2F&  position()   const { return position_; }
    double          height()     const { return height_;   }
    EPositionV         alignV()     const { return alignV_;   }
    EPositionH         alignH()     const { return alignH_;   }
//=============================================================================
//<OVERRIDES>
    virtual EType type(void) const { return SITEM_TEXT; }
protected:
//<DATA>
    QString  text_;
    Point2F  position_;
    double   height_;
    EPositionV  alignV_;
    EPositionH  alignH_;
};

} // namespace T2l
