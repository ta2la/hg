//
// Copyright (C) 2024 Petr Talla. [petr.talla@gmail.com]
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
#include "T2lEntity2Text.h"
#include "T2lCanvas.h"
#include "T2lSfeatText.h"
#include "T2lVector2.h"
#include "T2lElemText.h"
#include "T2lElemLine.h"
#include "T2lStyleChange.h"
#include "T2lPgraphItemText.h"
#include <QFont>
#include <QFontMetrics>

#include <string>
#include <iostream>

using namespace T2l;
using namespace std;

//=============================================================================
Entity2Text::Entity2Text( PgraphCol* pgraphs, const Point2F& p0, const Point2F& p1,
            EPositionH alignH, EPositionV alignV,
            Style* style, bool styleOwner, StyleChange* styleChange, bool metric ) :
    EntityStyled(style, styleOwner, styleChange),
    pgraphs_(pgraphs),
    position_(p0),
    p2_(p1),
    alignH_(alignH),
    alignV_(alignV),
    metric_(metric)
{
}

//=============================================================================
Entity2Text::~Entity2Text(void)
{
    if (pgraphs_ == nullptr) return;
    delete pgraphs_;
}

//=============================================================================
int Entity2Text::draw_nextPos_(const string& str, int posActual)
{
    int posResult = posActual;

    while(posResult<str.size()) {
        posResult++;
        if (str[posResult] != ' ') break;
    }

    while(posResult<str.size()) {
        posResult++;
        if (str[posResult] == ' ') break;
    }

    while(posResult<str.size()) {
        posResult++;
        if (str[posResult] != ' ') break;
    }

    return posResult;
}

//=============================================================================
void Entity2Text::draw(Canvas* canvas)
{
    //<STEP>
    /*SfeatText* sfeatText = nullptr;
    for (int i = 0; i < style()->sfeats().count(); i++) {
        sfeatText = dynamic_cast<SfeatText*>(style()->sfeats().get2(i));
        if (sfeatText != nullptr) continue;
    }
    if (sfeatText == nullptr) return;*/

    //<STEP>
    draw_data_ dd;

    double heightSymbolic = 1;
    double sizeMax = pgraphs_->sizeMax();
    if (metric_) {
        Point2F ptt = canvas->mapRealToPaper(Point2F(sizeMax, 0));
        heightSymbolic = ptt.x();
    }
    else {
        heightSymbolic = canvas->mapSymbolicToReal(sizeMax);
    }

    draw_data_initialize_(dd, canvas, heightSymbolic);

    //if (dd.WIDTH > 3*dd.heightSymbolic) dd.WIDTH-=dd.heightSymbolic*0.2;

    //<STEP>
    for (int pi = 0; pi < pgraphs_->count(); pi++) {
        Pgraph* pgraph = pgraphs_->get(pi);

        //<STEP> single paragraph
        for ( int i = 0; i < pgraph->count(); i++) {
            PgraphItemText* textItrm = pgraph->get(i)->getAsText();
            if (textItrm == nullptr) continue;

            int cursorPos = textItrm->cursorPos_;

            dd.textStr = textItrm->getText();
            //dd.textStr = text->insertCursor(text->getText());
            dd.bold = textItrm->bold();
            if (metric_) {
                Point2F ptt = canvas->mapRealToPaper(Point2F(textItrm->size(), 0));
                dd.size = ptt.x();
            }
            else {
                dd.size = canvas->mapSymbolicToReal(textItrm->size());
            }
            dd.color = textItrm->color();

            if (i >= pgraph->count()-1) dd.textStr += "<<";

            draw_data_initialize_text_(dd, canvas, dd.textStr);

            if ( dd.items.size() == 0 ) continue;

            if (dd.xPos!=0 && dd.xPos+dd.items[0].length>dd.WIDTH) {
                dd.line++;
                dd.xPos = 0;
            }

            dd.bold = textItrm->bold();
            if (metric_) {
                Point2F ptt = canvas->mapRealToPaper(Point2F(textItrm->size(), 0));
                dd.size = ptt.x();
            }
            else {
                dd.size = canvas->mapSymbolicToReal(textItrm->size());
            }

            do {
                double xPos = dd.xPos;
                std::string text = draw_data_take_text_(dd);

                double lineY = dd.lt.y()-dd.line*dd.heightSymbolic*1.3;
                Point2F pt(dd.lt.x()+xPos, lineY);

                ElemText component( text.c_str(), pt, dd.size, dd.color,
                                alignH(), alignV(), /*sfeatText->bold()*/textItrm->bold());
                //if ( styleChange() != nullptr ) styleChange()->execute(&component, canvas);
                canvas->draw(&component);

                if ( cursorPos <= text.length()) {
                    ElemText component( text.substr(0, cursorPos).c_str(), pt, dd.heightSymbolic, dd.color,
                                    alignH(), alignV(), textItrm->bold()/*sfeatText->bold()*/);
                    //if ( styleChange() != nullptr ) styleChange()->execute(&component, canvas);

                    double pos = canvas->width(&component);
                    ElemLine eline(Color::BLUE, dd.size/15);
                    double x = dd.lt.x()+dd.xPosBeg+pos;
                    eline.points().points().add(Point2F(x, lineY+0.5*dd.heightSymbolic));
                    eline.points().points().add(Point2F(x, lineY-1.7*dd.heightSymbolic));
                    canvas->draw(&eline);
                }

                if (dd.items.size() != 0) {
                    dd.line++;
                    dd.xPos = 0;
                }

                cursorPos -= text.length();

            } while (!(dd.items.size() == 0));

            if ( dd.xPos != 0 ) dd.xPos += dd.heightSymbolic;
        }

        dd.line++;
        dd.xPos = 0;
    }

    /*ElemLine eline(Color::BLUE, 0.0005);
    eline.points().points().add(dd.p1);
    eline.points().points().add(Point2F(dd.p1.x(), dd.p0.y()));
    canvas->draw(&eline);*/
}


//=============================================================================
void Entity2Text::draw_data_initialize_(draw_data_& dd, Canvas* canvas, double h) {
    dd.heightSymbolic = h;

    dd.p0 = canvas->mapRealToPaper(position_);
    dd.p1 = canvas->mapRealToPaper(p2_);

    if (dd.p1.x()-dd.p0.x()>h && dd.p1.y()-dd.p0.y()>h) {
        double d = 0.5*h;

        dd.p0 = Point2F(dd.p0.x()+d, dd.p0.y()+d);
        dd.p1 = Point2F(dd.p1.x()-d, dd.p1.y()-d);
    }

    dd.lt = Point2F(dd.p0.x(), dd.p1.y());

    dd.WIDTH = dd.p1.x()-dd.p0.x();
    if (dd.WIDTH < 0) dd.WIDTH = 1;

    dd.line = 0;
    dd.xPos = 0;
}

//=============================================================================
void Entity2Text::draw_data_initialize_text_(draw_data_& dd, Canvas* canvas, std::string& text) {

    std::string str(text);

    do {
        int pos = 0;

        while(pos+1 <= str.size()) {
            if (str[pos+1] != ' ') break;
            pos++;
        }

        while(pos+1 <= str.size()) {
            pos++;
            if (str[pos] == ' ') break;
        }

        while(pos+1 <= str.size()) {
            if (str[pos] != ' ') break;
            pos++;
        }

        std::string texti = str.substr(0, pos);

        ElemText component( texti.c_str(), Point2F(), dd.size, dd.color,
                    alignH(), alignV(), dd.bold);
        //if ( styleChange() != nullptr ) styleChange()->execute(&component, canvas);
        double cwidth = canvas->width(&component);

        dd.items.push_back(strItem_(texti.c_str(), cwidth));

        str.erase(0, pos);
    } while (str.size() > 0);
}

//=============================================================================
std::string Entity2Text::draw_data_take_text_(draw_data_& dd)
{
    if (dd.items.size() == 0 ) return "";

    dd.xPosBeg = dd.xPos;

    string result;

    //if (dd.xPos == 0) {
        result = dd.items[0].str;
        dd.xPos += dd.items[0].length;
        dd.items.erase(dd.items.begin());
    //}

    if (dd.items.size() == 0) return result;

    while ( dd.xPos + dd.items[0].length <= dd.WIDTH ) {
        result += dd.items[0].str;
        dd.xPos += dd.items[0].length;
        dd.items.erase(dd.items.begin());
        if (dd.items.size() == 0) break;
    }

    return result;
}

//=============================================================================
