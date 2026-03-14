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
#include "T2lCmd_displayInfo.h"
#include "T2lEntityPack.h"
#include "T2lDisplay.h"
#include "T2lDisplayBmp.h"
#include <QPixmap>
#include <QPainter>

using namespace T2l;
using namespace std;

//QPixmap* Cmd_pan::pixmap_ = nullptr;

//=============================================================================
Cmd_displayInfo::Cmd_displayInfo() :
    Cmd("display info")
{
}

//=============================================================================
Cmd_displayInfo::~Cmd_displayInfo()
{

}

//=============================================================================
void Cmd_displayInfo::enterPoint( const Point2F& pt, Display& view )
{
    info_ =  QString() + "TC;CT;text: You clicked at: [" +
             QString::number(pt.x()) + "," +
             QString::number(pt.y()) + "];;";
    info_ += "TC;CT;text: <hup>;;";

    info_ += QString() + "TC;CT;text: Origin: <b>[" +
             QString::number(view.origin_.x()) + "," +
             QString::number(view.origin_.y()) + "]</b>;;";
    info_ += QString() + "TC;CT;text: Scale: <b>" +
             QString::number(view.scale()) + "</b>;;";
    info_ += QString() + "TC;CT;text: Ppm: <b>" +
             QString::number(view.ppm()) + "</b>;;";
    info_ += "TC;CT;text: <hup>;;";

    if (view.bitmap_) {
    info_ += QString() + "TC;CT;text: Bitmap scale: <b>" +
             QString::number(view.bitmap_->bmpScale()) + "</b>;;";
    }
    if (view.bitmap_->bmpDisplay_) {
        info_ += QString() + "TC;CT;text: size: <b>[" +
                 QString::number(view.bitmap_->bmpDisplay_->widthPx_()) + "," +
                 QString::number(view.bitmap_->bmpDisplay_->heightPx_()) + "]</b>;;";
        view.bitmap_->bmpDisplay_->bitmap()->save("/home/rce/TEMP/bmp.png", "PNG");
    }


}

//=============================================================================
void Cmd_displayInfo::enterMove( const Point2F& pt, Display& view )
{
}

//=============================================================================
void Cmd_displayInfo::enterReset( Display& view )
{
}

//===================================================================
QString Cmd_displayInfo::dialogTml() const
{
    QString result = info_;

    //===================================================
    result = result.replace("TC", "type: control");
    result = result.replace("CT", "control: text");
    result = result.replace("CB", "control: button");
    result = result.replace(";", "\n");

    return result;
}

//===================================================================
QString Cmd_displayInfo::hint(void) const
{

    return "click in cad view";
}

//=============================================================================
