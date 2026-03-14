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
#include "T2lSitemArea.h"
#include "T2lPoint2.h"

#include "T2lIntervalF.h"

using namespace T2l;

//=============================================================================
SitemArea::SitemArea( const Color& color) :
    Sitem(color)
{
}

//=============================================================================
Box2F SitemArea::bound(void)
{
    Box2F b = points_.points().points().bound();
    return Box2F( IntervalF(b.x().beg()*1000, b.x().end()*1000),
                  IntervalF(b.y().beg()*1000, b.y().end()*1000));
}

//=============================================================================
