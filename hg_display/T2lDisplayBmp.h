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

#include "T2lItem.h"
#include "T2lPoint2.h"
#include "T2lScale2.h"

class QPixmap;

namespace T2l
{

class Display;

//=============================================================================
class DisplayBmp : public T2l::Item
{
//=============================================================================
public:
//<CONSTRUCTION>
    DisplayBmp(  Display& view, const Point2F& origin,
              double scale, int width, int height );
    virtual  ~DisplayBmp();
//<DATA>
    Point2F   bmpOrigin(void) const { return bmpOrigin_; }
    double    bmpScale(Scale2::Dir dir) const { return bmpScale_.scale(dir); }
//<METHODS>
    void      bmpUpdate();
//=============================================================================
//<OVERRIDES>
//protected:
//<DATA_>
    Point2F   bmpOrigin_;
    Scale2    bmpScale_;

    QPixmap*  bmpPixmap;
    Display*     bmpDisplay_;
//<FRIENDS>
    friend class Display;
};

} // namespace T2l
