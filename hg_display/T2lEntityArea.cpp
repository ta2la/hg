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
#include "T2lEntityArea.h"
#include "T2lSfeatArea.h"
#include "T2lComponentArea.h"
#include "T2lCanvas.h"
#include "T2lStyleChange.h"

using namespace T2l;

//=============================================================================
EntityArea::EntityArea( Style& style, bool styleOwner, StyleChange* styleChange ) :
    EntityLinear( &style, styleOwner, true, styleChange )
{
}

//=============================================================================
void EntityArea::draw(Canvas* canvas)
{
    //if ( check_(display) == false ) return; TODO

    drawBasic_(canvas);

    for ( int i = 0; i < style()->sfeats().count(); i++ )
    {
        const SfeatArea* sfArea = dynamic_cast<SfeatArea*>(style()->sfeats().get2(i));
        if ( sfArea == NULL ) continue;

        ComponentArea componentArea(sfArea->color());
        componentArea.alphaSet(sfArea->alpha());

        for ( int i = 0; i < points().count(); i++) {
            componentArea.area().points().points().add(canvas->mapRealToPaper(points().get(i)));
        }

        if ( styleChange() != nullptr ) styleChange()->execute(&componentArea, canvas);

        canvas->draw(&componentArea);
    }
}

//=============================================================================
