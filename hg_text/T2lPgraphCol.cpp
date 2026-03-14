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
#include "T2lPgraphCol.h"
#include "T2lPgraphItemText.h"
#include "T2lPgraphItemBox.h"

using namespace T2l;

//===================================================================
PgraphCol::PgraphCol(void)
{
}

//===================================================================
PgraphCol* PgraphCol::clone()
{
    PgraphCol* result = new PgraphCol();

    for (int pi = 0; pi < count(); pi++) {
        result->add(new Pgraph());
        Pgraph* pgraph = get(pi);

        for (int i = 0; i < pgraph->count(); i++) {
            result->last()->add(pgraph->get(i)->clone());
        }
    }

    return result;
}

double PgraphCol::sizeMax()
{
    double result = -1;

    for (int pi = 0; pi < count(); pi++) {
        Pgraph* pgraph = get(pi);

        for (int i = 0; i < pgraph->count(); i++) {
            PgraphItem* item = pgraph->get(i);
            if (item == nullptr) continue;

            PgraphItemText* itemText = item->getAsText();
            if (result <= 0) {
                result = itemText->size();
                continue;
            }

            if (itemText->size() <= result) continue;

            result = itemText->size();
        }
    }

    return result;
}

//===================================================================
