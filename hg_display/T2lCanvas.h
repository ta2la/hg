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
#pragma once

#include "T2lCanvasI.h"
#include "T2lBox2.h"
#include "T2lColor.h"

namespace T2l
{

//=============================================================================
class Canvas : public T2l::CanvasI {
//=============================================================================
public:
//<CONSTRUCTION>
    Canvas( double scale = 0.01, double scaleS = 1.0 );
    virtual ~Canvas(void) {}
//<METHODS>
    void boundSet(const Box2F& bound) { bound_ = bound; }
    Point2F origin() { return T2l::Point2F( bound_.x().beg(), bound_.y().beg() ); }
    void originSet( const Point2F& origin );
    void scaleXSet( double scaleX ) { scaleX_ = scaleX; }
    void scaleYSet( double scaleY ) { scaleY_ = scaleY; }

    Color color() const { return color_; }
    void colorSet( const Color& color ) { color_ = color; }

    Vector2F overOffset() { return overOffset_; }
    void overOffsetSet(const Vector2F& offset) { overOffset_ = offset; }
//=============================================================================
//<OVERRIDES>
    virtual bool draw(Component* /*c*/) { return false; }

    virtual const Box2F& bound()  const { return bound_; }
    virtual double       scaleX() const { return scaleX_; }
    virtual double       scaleY() const { return scaleY_; }
    virtual double       scaleS() const { return 1.0; }
    virtual double       ppm()    const { return 4000; }

    virtual Point2F mapRealToPaper(const Point2F& pt) const   { return Point2F(pt.x()*scaleX(), pt.y()*scaleY()); }
    virtual Box2F   mapRealToPaper(const Box2F& pt) const;
    virtual Point2F mapPaperToReal(const Point2F& pt) const   { return Point2F(pt.x()/scaleX(), pt.y()/scaleY()); }
    virtual double  mapSymbolicToReal(const double d) const    { return d*scaleS()/1000.0; }
    virtual Point2F mapSymbolicToReal(const Point2F& pt) const { return Point2F(mapSymbolicToReal(pt.x()), mapSymbolicToReal(pt.y())); }
//<DATA>
    T2l::Box2F bound_;
    double     scaleX_;
    double     scaleY_;
    double     scaleS_;
    Color      color_;

    Vector2F   overOffset_;
};

} // namespace T2l

