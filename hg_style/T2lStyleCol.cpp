//
// Copyright (C) 2019 Petr Talla. [petr.talla@gmail.com]
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

#include "T2lStyleCol.h"
#include "T2lLstyle.h"
#include "T2lSymbol.h"
#include "T2lSitemCircle.h"
#include "T2lSitemLine.h"
#include "T2lSitemArea.h"
#include "T2lSitemText.h"
#include "T2lSfeatSymbol.h"
#include "T2lAfile.h"
#include <string>

using namespace T2l;
using namespace std;

//====================================================================
StyleCol::StyleCol()
{
}

//====================================================================
void StyleCol::load()
{
    add( new StyleItem( Style::createPointStyle ( Color::BLUE, Style::SYMBOL_CIRCLE,        3,   "void"        )) );
}

//====================================================================
Style* StyleCol::getStyle(const char* id)
{
    string ids(id);

    for (int i = 0; i < count(); i++) {
        Style* stylei = get(i)->style();
        if ( ids == stylei->id() ) return stylei;
    }

    return getStyle("void");
}

//====================================================================
SfeatSymbol* StyleCol::lastSymbol()
{
    if ( count() == 0 ) add(new StyleItem(new Style("implicit")) );
    SfeatSymbol* result = nullptr;
    SfeatCol& sfeats = last()->style()->sfeats();
    for ( int i = 0; i < sfeats.count(); i++ ) {
        result = dynamic_cast<SfeatSymbol*>(sfeats.get(i));
        if ( result != nullptr) break;
    }
    result = new SfeatSymbol(Color::BLACK, new Symbol());
    sfeats.add(result);

    return result;
}

//====================================================================
void StyleCol::load(Afile& afile, double scaleLine)
{
    for (int ir = 0; ir < afile.recordCount(); ir++) {
        AfileRecord* rec = afile.recordGet(ir);

        QString type = rec->valueGet("type", "UNKNOWN");

        if (type == "symbol") {
            AfileAttr* attrId = rec->attrGet("id");
            if ( attrId != nullptr ) {
                string id = attrId->value().toStdString();
                Style* style = new Style(id.c_str());
                add(new StyleItem(style));
            }
        }
        else if (type == "sitem") {
            QString sitemType = rec->valueGet("sitem", "UNKNOWN");

            Color color(Color::BLACK);
            AfileAttr* colorAttr = rec->attrGet("color", 0);
            if ( colorAttr ) color = Color::read( colorAttr->value().toStdString().c_str() );

            if ( sitemType == "circle") {
                Point2F point = rec->valueGet("point-num", Point2F(0,0));
                double  radius = rec->valueGet("radius", 2.0);
                bool    fill   = ( rec->valueGet("fill", "true") == "false" ) ? false : true;
                double  width  = rec->valueGet("width", 0.005)*scaleLine;

                SitemCircle* circle = new SitemCircle(point, radius, color, fill, width );
                lastSymbol()->symbol()->items().add(circle);
            }
            else if ( sitemType == "area" ) {
                SitemArea* area = new SitemArea(color);
                for ( int i = 0; rec->valueGet("point-num", "", i).isEmpty() == false; i++ ) {
                    area->points().points().points().add(rec->valueGet("point-num", Point2F(0,0), i));
                }
                lastSymbol()->symbol()->items().add(area);
            }
            else if ( sitemType == "line" ) {
                SitemLine* line = new SitemLine( color, rec->valueGet("width", 0.002)*scaleLine );
                for ( int i = 0; rec->valueGet("point-num", "", i).isEmpty() == false; i++ ) {
                    line->points().points().add(rec->valueGet("point-num", Point2F(0,0), i));
                }
                lastSymbol()->symbol()->items().add(line);
            }
            else if (sitemType == "text") {
                QString text = rec->valueGet("text");
                Point2F position = rec->valueGet("point-num", Point2F(0, 0));
                double height = rec->valueGet("height", 2);

                SitemText* sitemText = new SitemText(text, position, height, color );
                lastSymbol()->symbol()->items().add(sitemText);
            }
        }
    }
}

//====================================================================
