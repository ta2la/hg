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
#include "T2lCmd_select.h"
#include "T2lCmdQueue.h"
#include "T2lEntityPack.h"
#include "T2lUpdateLock.h"
#include "T2lRefColSelection.h"
#include "T2lGObjectPool.h"
#include "T2lScene.h"
#include "T2lGObject.h"
#include "T2lEntityLine.h"
#include "T2lEntityText.h"

using namespace T2l;

//=============================================================================
Cmd_select::Cmd_select(bool cumulative) :
    pointKnown_(false),
    selectionCumulative_(cumulative)
{
}

//=============================================================================
void Cmd_select::enterPoint( const Point2F& pt, Display& view )
{
    EntityPack* pack = view.entityPack();
    pack->cleanDynamic();

    for ( int i = 0; i < pack->scene()->count(); i++ ) {
        Ref* ref = pack->scene()->get(i);

        if ( ref->identifiedByPoint(view.getRefCanvas(), pt)) {
            GObject* object = ref->object();
            object->isSelectedSet(object->isSelected());
            break;
        }
    }

    pack->dynamicRefresh();
}

//=============================================================================
void Cmd_select::enterMove( const Point2F& pt, Display& view )
{
    EntityPack* pack = view.entityPack();
    if (pointKnown_ == false)  pack->dynamicRefresh();

    Box2F box(point_, pt);

    EntityLine* line = new EntityLine();
    for ( int i = 0; i < 5; i++ ) {
        Point2F point = box.getPoint(i);
        line->points().points().add(point);
    }

    pack->cleanDynamic();
    pack->addDynamic(line);
    pack->dynamicRefresh();
}

//=============================================================================
