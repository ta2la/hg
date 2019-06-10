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
#include "T2lComponentText.h"
#include "T2lColor.h"

using namespace T2l;

//=============================================================================
ComponentText::ComponentText( const QString& text, const Point2F& position,
                          double height, const Color& color,
                          EPositionH positionH, EPositionV positionV,
                          bool bold, AngleXcc angle ) :
    Component(color),
    text_(text),
    position_(position),
    height_(height),
    positionH_(positionH),
    positionV_(positionV),
    angle_(angle),
    bold_(bold)
{
}

//=============================================================================
