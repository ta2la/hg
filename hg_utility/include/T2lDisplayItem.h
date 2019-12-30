//
// Copyright (C) 2017 Petr Talla. [petr.talla@gmail.com]
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

#include <QPainter>

namespace T2l
{

namespace DisplayItemType {
    enum { DISPLAY_TEXT, DISPLAY_HEADER };
}

//=============================================================================
class DisplayItem {
//=============================================================================
public:
//<CONSTRUCTION>
    DisplayItem( int type);
//<METHODS>
    bool typeEqualsTo(int type);
//=============================================================================
//protected:
//<DATA>
    int type_;
};

} //namespace T2l
