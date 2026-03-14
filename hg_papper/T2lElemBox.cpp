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
#include "T2lElemBox.h"
#include "T2lColor.h"

using namespace T2l;

//=============================================================================
ElemBox::ElemBox( const Point2F& pt0, const Point2F& pt1, CanvasI& canvas,
                  const Color& color, double width, bool symbolicScaleWidth,
                  unsigned char alpha,
                  const Point2F& origin, bool symbolicScale ) :
    Element(color),
    pt0_(pt0),
    pt1_(pt1),
    width_(width),
    symbolicScaleWidth_(symbolicScaleWidth),
    alpha_(alpha),
    originAngle_(0),
    origin_(origin),
    symbolicScale_(symbolicScale)
{
}

//=============================================================================

