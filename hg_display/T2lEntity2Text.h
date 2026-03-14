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

#include "T2lSymbolDefs.h"
#include "T2lEntityStyled.h"
#include "T2lAngleXcc.h"
#include <QString>
#include "T2lEnPointMmRel.h"
#include "T2lPgraphCol.h"
#include "T2lElem2Text.h"

namespace T2l
{
//=============================================================================
class Entity2Text : public EntityStyled {
//=============================================================================
public:
//<ENUMS>
//<CONSTRUCTION>
    Entity2Text( PgraphCol* pgraphs, const Point2F& p0, const Point2F& p1,
                EPositionH alignH, EPositionV alignV,
                Style* style, bool styleOwner, StyleChange* styleChange = nullptr,
                bool metric = false);
    virtual ~Entity2Text(void);
//<METHODS>
    const Point2F& position() const { return position_; }

    EPositionH    alignH() const { return alignH_; }
    EPositionV    alignV() const { return alignV_; }
//=============================================================================
//<OVERRIDES>
    virtual void draw(Canvas* canvas);
protected:
//<DATA>
    PgraphCol*  pgraphs_;

    Point2F     position_;
    Point2F     p2_;

    EPositionH  alignH_;
    EPositionV  alignV_;

    bool        metric_;
//<INTERNALS>
    int draw_nextPos_(const std::string& str, int cntActual);

    struct strItem_ {
        strItem_(const char* str, double length) : str(str), length(length) {};

        std::string str;
        double length;
    };

    struct draw_data_ {
        Point2F p0;
        Point2F p1;
        Point2F lt;

        double WIDTH;
        double heightSymbolic = {1};

        int line;
        double xPos;
        double xPosBeg;

        std::string textStr;

        bool bold;
        Color color;
        double size;

        std::vector<strItem_> items;
    };

    void draw_data_initialize_(draw_data_& dd, Canvas* canvas, double height);
    void draw_data_initialize_text_(draw_data_& dd, Canvas* canvas, std::string& text);
    std::string draw_data_take_text_(draw_data_& dd);

};

} // namespace T2l
