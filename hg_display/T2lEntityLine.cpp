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
#include "T2lEntityLine.h"
#include "T2lSfeatLine.h"

using namespace T2l;

//=============================================================================
EntityLine::EntityLine( Style& style, bool styleOwner, StyleChange* styleChange ) :
    EntityLinear( &style, styleOwner, false, styleChange )
{
}

//=============================================================================
EntityLine::EntityLine( const Color color, double width, StyleChange* styleChange ) :
    EntityLinear( new Style(""), true, false, styleChange )
{
    style_->sfeats().add(new SfeatLine(color, width));
}

//=============================================================================
EntityLine::EntityLine( const Point2F& p0, const Point2F& p1, const Color color, double width ) :
    EntityLinear( new Style(""), true, false, NULL )
{
    style_->sfeats().add(new SfeatLine(color, width));
    points().points().add(p0);
    points().points().add(p1);
}

//=============================================================================
void EntityLine::draw(Canvas* canvas)
{
    drawBasic_(canvas);
}

//=============================================================================
