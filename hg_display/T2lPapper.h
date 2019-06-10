//
// Copyright (C) 2017 Petr Talla. [petr.talla@gmail.com]
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
#pragma once

#include "T2lBox2.h"

#include <QImage>
#include <QPainter>

namespace T2l

{

class ComponentLine;
class ComponentArea;
class ComponentText;
class Color;

//=============================================================================
class Papper {
//=============================================================================
public:
//<CONSTRUCTION>
    Papper(double w, double h);
    ~Papper();
//<METHODS>
    void save(const char* filePath);
    void draw(ComponentLine& line);
    void draw(ComponentArea& area);
    void draw(const ComponentText& text);

    void drawPoint(const Point2F& pos, const Color& color, double size);

    QPainter& painter() { return painter_; }
//=============================================================================
//protected:
//<DATA>
    QImage       image_;
    QPainter     painter_;
    double       height_;
//<INTERNALS>
    Point2F transf_( const Point2F& pt);
    //void drawGeometry_(ComponentText& text, QFontMetrics& fm);
//<FRIENDS>
    friend class Cmds_honey_exe;
};

} //namespace Hnw
