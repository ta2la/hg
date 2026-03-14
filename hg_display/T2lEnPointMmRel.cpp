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
#include "T2lEnPointMmRel.h"

using namespace T2l;

//=============================================================================
EnPointMmRel::EnPointMmRel(const Point2F& xy, const Vector2F& offset) :
    EnPointXy(xy),
    offset_(offset)
{
}

//=============================================================================
Point2F EnPointMmRel::xy(const Canvas* canvas)
{
    Point2F ptx( offset_.x(),  offset_.y() );
    ptx = canvas->mapPaperToReal(ptx);

    double x = xy_.x() + ptx.x()/1000.0;
    double y = xy_.y() + ptx.y()/1000.0;

    return Point2F(x, y);
}

//=============================================================================
