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
#include "T2lPgraph.h"
#include "T2lPgraphItemText.h"

#include <string>

using namespace T2l;
using namespace std;

//===================================================================
Pgraph::Pgraph(void)
{
}

//===================================================================

Pgraph* Pgraph::divide(int itemIndex, int index)
{

    //<STEP> the item to divide
    PgraphItemText* itemText = get(itemIndex)->getAsText();
    string text(itemText->getText());

    //<STEP> the next paragraph
    Pgraph* result = new Pgraph();

    result->add( new PgraphItemText(text.substr(index).c_str()) );

    for ( int i = itemIndex+1; i < count(); i++ ) {
        PgraphItemText* itemText = get(i)->getAsText();
        result->add(new PgraphItemText(itemText->getText()));
    }

    //<STEP> change the paragraph
    //if(index < itemText->getTextSize()-1) {
        itemText->setText(text.substr(0, index).c_str());
        itemText->cursorPos_ = -1;
    //}
    for ( int i = count(); i > itemIndex+1; i-- ) {
        remove(count()-1);
    }

    return result;
}

//===================================================================
