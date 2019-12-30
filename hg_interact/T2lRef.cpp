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
#include "T2lRef.h"
#include "T2lRefCol.h"
#include "T2lGObject.h"
#include "T2lScene.h"
#include "T2lEntityLine.h"
#include "T2lEntityText.h"
#include "T2lEntityArea.h"
#include "T2lEntityPoint.h"
#include "T2lIdentifyLine.h"
#include "T2lIdentifyPoint.h"
#include "T2lIdentifyArea.h"
#include "T2lDisplay.h"
#include <assert.h>

using namespace T2l;//CHECKEND

//=============================================================================
Ref::Ref(GObject* obj) :
    object_(obj),
    parent_(NULL)
{
    object_->refs_.append(this);
}

//=============================================================================
Ref::~Ref()
{
    entitiesClean_();

    if ( object_ != NULL ) object_->refs_.removeOne(this);
    if ( parent_ == NULL ) return;
    parent_->remove_(this);
}

//=============================================================================
void Ref::entitiesClean_()
{
    for ( int i = 0; i < entities_.count(); i++ ) {
        Entity* entity = entities_.get(i);
        entity->destroy_not_delete_();
        delete entity;
    }

    entities_.clean();
}

//=============================================================================
void Ref::repaint()
{
    entitiesClean_();

    if( scene() == NULL ) return;
    object()->display(entities_, scene());

    for (int i = 0; i < entities_.count(); i++) {
        scene()->entities().add(entities_.get(i));
    }

    assert(parent_);
    parent_->dirtySet();
}

//=============================================================================
bool Ref::identifiedByPoint( const Canvas& canvas, const Point2F& pt )
{
    if (object_ == NULL) return false;
    GObject::EIdentified s = object_->identifiedByPoint(canvas, pt);
    if ( s == GObject::IDENTIFIED_YES ) {
        return true;
    }
    else if ( s == GObject::IDENTIFIED_NO ) {
        return false;
    }
    assert ( s == GObject::IDENTIFIED_NOTIMPLEMENTED );
    for ( int i = 0; i < entities_.count(); i++ ) {
        Entity* entity = entities_.get(i);

        EntityPoint* eSymbol = dynamic_cast<EntityPoint*>(entity);
        if (eSymbol != NULL) {
            IdentifyPoint selector(canvas, eSymbol->origin());

            if ( selector.byPoint(pt) ) return true;
        }

        EntityLine* eLine = dynamic_cast<EntityLine*>(entity);
        if (eLine != NULL) {
            IdentifyLine selector(canvas);
            selector.enlargementSet(1.5);

            Point2FCol& points = eLine->points_.points();
            for ( int i = 0; i < points.count(); i++ ) {
                selector.points().add(points.get(i));
            }

            if ( selector.byPoint(pt) ) return true;
        }
    }

    return false;
}

//=============================================================================
void Ref::modifiedSolve_()
{
    repaint();

    if (parent_ == NULL) return;
    parent_->modifiedSolve_(this);
}

//=============================================================================
Scene* Ref::scene()
{
    return dynamic_cast<Scene*>(parent_);
}

//=============================================================================
