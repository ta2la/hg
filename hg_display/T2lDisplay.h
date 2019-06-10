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

#include "T2lCanvas.h"
#include "T2lPoint2.h"
#include "T2lScale2.h"
#include "T2lSize2.h"
#include "T2lItem.h"
#include "T2lColor.h"
#include "TcObject.h"

//TODOM #include <opencv2/opencv.hpp>

namespace T2l
{

class DisplayBmp;
class EntityPack;

//=============================================================================
class Display : public TcObject, public Item {
//=============================================================================
public:
//<ENUM>
    enum EEdge {
        EDGE_LEFT   = 0,
        EDGE_BOTTOM = 1,
        EDGE_RIGHT  = 2,
        EDGE_TOP    = 3
    };
//<CONSTRUCTION>
    Display(const Point2F& origin, double scale);
    virtual ~Display();
//<NEIGHBOURS>
    EntityPack* entityPack() { return entityPack_; }
//<DATA>
    Point2F origin() const { return origin_; }
    virtual void originSet(const Point2F& origin);

    double scale(Scale2::Dir dir = Scale2::XY) const { return scale_.scale(dir); }
    virtual void scaleSet(double scale, Scale2::Dir dir = T2l::Scale2::XY);

    double ppm() {return ppm_; }

    void colorBackgroundSet(const Color& color) { colorBackground_ = color; }
    const Color& colorBackground() const { return colorBackground_; }

    virtual Size2F size() const { return Size2F(100, 100); }
    Canvas getRefCanvas() const;

    //TODOM void set_image_file(const char* file, IplImage* image) { image_file_ = file; image_ = image; }
    const char* get_image_file() { return image_file_.c_str(); }
    //TODOM IplImage* get_image() { return image_; }
//<METHODS>
    void refresh();
    virtual void updateDynamic() {;}

    Vector2F overOffset() { return overOffset_; }
    void overOffsetSet(const Vector2F& offset) { overOffset_ = offset; }
//=============================================================================
//<OVERRIDES>
//protected:
    DisplayBmp* bitmap_;

    Point2F origin_;
    Scale2  scale_;

    EntityPack* entityPack_;

    Color    colorBackground_;
    int      edge_[4];

    double   ppm_;

    int refreshLock_;
    enum RefreshedLockedMemo { Fresh, Widget, Bitmap };
    RefreshedLockedMemo refreshedLocked_;

    std::string image_file_;

    Vector2F overOffset_;
    //IplImage*   image_;
//<INTERNALS>
    void unlockRefresh();
    virtual bool isBitmapFresh_();
    virtual int widthPx_() { return 100; } //TODO
    virtual int heightPx_() { return 100; } //TODO
    virtual void refresh_() {}
//<FRIENDS>
    friend class DisplayBmp;
    friend class EntityPack;
};

} // namespace T2l
