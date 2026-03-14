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
#include "T2lPgraphItemText.h"

using namespace T2l;
using namespace std;

//===================================================================
PgraphItemText::PgraphItemText(const char* text) :
    text_(text),
    bold_(false),
    size_(1),
    color_(Color::BLACK),
    back_(false)
{
}

//===================================================================
const char* PgraphItemText::getText()
{
    return text_.c_str();
}

//===================================================================
string PgraphItemText::insertCursor(const char* text)
{
    if (cursorPos_ < 0 ) return text_.c_str();
    if (cursorPos_ > text_.size()) return text_.c_str();

    string result(text_);
    result.insert(cursorPos_, 1, '|');
    return result;
}

//===================================================================
bool PgraphItemText::backspace()
{
    if ( cursorPos_ <= 0) return false;
    text_.erase(--cursorPos_, 1);
}

//===================================================================
PgraphItem* PgraphItemText::clone()
{
    PgraphItemText* result = new PgraphItemText(text_.c_str());

    result->cursorPos_ = cursorPos_;
    result->color_     = color_;
    result->size_      = size_;
    result->bold_      = bold_;
    result->back_      = back_;
    result->backColor_ = backColor_;

    return result;
}

//===================================================================
