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
#include "T2lCanvas.h"
#include "T2lEntityColI.h"
#include "T2lSize2.h"
#include "T2lIntervalF.h"
#include <assert.h>

using namespace T2l;

//=============================================================================
Canvas::Canvas( double scale, double scaleS ) :
    scaleX_(scale),
    scaleY_(scale),
    scaleS_(scaleS),
    color_(Color::WHITE),
    overOffset_(Vector2F(0, 0))
{
}

//=============================================================================
Box2F Canvas::mapRealToPaper(const Box2F& box) const
{
    assert ( (scaleX() > 0.0) && (scaleY() > 0.0) );
    return Box2F( IntervalF(box.x().beg()*scaleX(), box.x().end()*scaleX()),
                        IntervalF(box.y().beg()*scaleY(), box.y().end()*scaleY()) );
}

//=============================================================================
void Canvas::originSet(const Point2F& origin)
{
    bound_ = Box2F( IntervalF(origin.x(), origin.x()+bound().x().getLength()),
                    IntervalF(origin.y(), origin.y()+bound().y().getLength()) );
}

//=============================================================================
