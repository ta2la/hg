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
#include "T2lStyleChange.h"
#include "T2lElement.h"
#include "T2lElemLine.h"
#include "T2lElemCircle.h"
#include "T2lElemText.h"
#include "T2lCanvas.h"

using namespace T2l;

//=============================================================================
StyleChange::StyleChange( const Color& color, double inflation ) :
    color_(color),
    inflation_(inflation)
{
}

//=============================================================================
void StyleChange::execute(Element* component, Canvas* canvas) const
{
    component->colorSet(color_); //case ELEM_AREA too

    double inflationReal = canvas->mapSymbolicToReal(inflation_);

    switch ( component->category() )
    {
    case Element::ELEM_LINE: {
        ElemLine* line = dynamic_cast<ElemLine*>(component);
        line->setWidth(line->width()+inflationReal); }
        break;
    case Element::ELEM_CIRCLE: {
        ElemCircle* circle = dynamic_cast<ElemCircle*>(component);

        if (circle->fill()) {
            circle->radiusSet(circle->radius()+inflationReal);
            }
        else {
            circle->widthSet(circle->width()+inflationReal);
        } }
        break;
    case Element::ELEM_TEXT: {
        ElemText* text = dynamic_cast<ElemText*>(component);
        text->setHeight(text->height()+inflationReal); }
        break;
    }
}

//=============================================================================
