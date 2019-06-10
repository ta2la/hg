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
#include "T2lComponent.h"
#include "T2lComponentLine.h"
#include "T2lComponentCircle.h"
#include "T2lComponentText.h"
#include "T2lCanvas.h"

using namespace T2l;

//=============================================================================
StyleChange::StyleChange( const Color& color, double inflation ) :
    color_(color),
    inflation_(inflation)
{
}

//=============================================================================
void StyleChange::execute(Component* component, Canvas* canvas) const
{
    component->colorSet(color_); //case COMPONENT_AREA too

    double inflationReal = canvas->mapSymbolicToReal(inflation_);

    switch ( component->category() )
    {
    case Component::COMPONENT_LINE: {
        ComponentLine* line = dynamic_cast<ComponentLine*>(component);
        line->setWidth(line->width()+inflationReal); }
        break;
    case Component::COMPONENT_CIRCLE: {
        ComponentCircle* circle = dynamic_cast<ComponentCircle*>(component);

        if (circle->fill()) {
            circle->radiusSet(circle->radius()+inflationReal);
            }
        else {
            circle->widthSet(circle->width()+inflationReal);
        } }
        break;
    case Component::COMPONENT_TEXT: {
        ComponentText* text = dynamic_cast<ComponentText*>(component);
        text->setHeight(text->height()+inflationReal); }
        break;
    }
}

//=============================================================================
