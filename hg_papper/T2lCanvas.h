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
class Canvas : public CanvasI {
//=============================================================================
public:
//<CONSTRUCTION>
    Canvas( double scale = 0.01, double scaleS = 1 );
    virtual ~Canvas(void) {}
//<METHODS>
//    void boundSet(const Box2F& bound) { int a = 50;
//                                        int b = 888;
//                                        //bound_ = bound;
//                                        //bound_.inflateBy(0.4);
//                                      } //APTA💊
    //Point2F origin() { return Point2F( bound_.x().beg(), bound_.y().beg() ); } //APTA💊
    //void originSet( const Point2F& origin ); //APTA💊
    void scaleSet( double scale ) { scale_ = scale; }

    Color color() const { return color_; }
    void colorSet( const Color& color ) { color_ = color; }

    //Vector2F overOffset() { return overOffset_; }
    //void overOffsetSet(const Vector2F& offset) { overOffset_ = offset; }
//=============================================================================
//<OVERRIDES>
    virtual bool draw(Element* /*c*/) { return false; }
    virtual double  width(Element* c) { return 1; }

    virtual double       scale() const { return scale_; }
    virtual double       scaleS() const { return scaleS_; }

    virtual double cutPlane() const { return cutPlane_; };

    virtual double   mapRealToPaper   (const double d )    const  { return d*scale();}
    virtual Point2F  mapRealToPaper   (const Point2F& pt ) const  { return Point2F( mapRealToPaper(pt.x()), mapRealToPaper(pt.y()) ); }
    virtual Box2F    mapRealToPaper   (const Box2F& pt   ) const;
    virtual Point2F  mapPaperToReal   (const Point2F& pt ) const  { return Point2F(pt.x()/scale(), pt.y()/scale()); }
    virtual double   mapSymbolicToReal(const double d    ) const  { return mapSymbolicScale(d)/1000.0; }
    virtual Point2F  mapSymbolicToReal(const Point2F& pt ) const  { return Point2F(mapSymbolicToReal(pt.x()), mapSymbolicToReal(pt.y())); }
    virtual double   mapSymbolicScale (const double d    ) const  { return d*scaleS(); }
    virtual Point2F  mapSymbolicScale (const Point2F& pt ) const  { return Point2F(mapSymbolicScale(pt.x()), mapSymbolicScale(pt.y())); }
    virtual Vector2F mapSymbolicScaleV(const Point2F& pt ) const  { return Vector2F(mapSymbolicScale(pt.x()), mapSymbolicScale(pt.y())); }

//<DATA>
    //T2l::Box2F bound_; //APTA💊
    double cutPlane_ = 1.5;

    double     scale_;
    double     scaleS_;
    Color      color_;


    //Vector2F   overOffset_;
};

} // namespace T2l

