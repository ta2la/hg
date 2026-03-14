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
#pragma once

#include "T2lColor.h"
#include "T2lPgraphItem.h"
#include <string>

namespace T2l {

//===================================================================
class PgraphItemText : public PgraphItem {
//===================================================================
public:
    PgraphItemText(const char* text = "MOCK");
    virtual ~PgraphItemText(void) = default;
//===================================================================
    bool backspace();

    const char* getText();
    void setText(const char* text) { text_ = text; }
    int getTextSize() { return text_.size(); }

    bool bold(void) const { return bold_; }
    void boldSet(bool bold) { bold_ = bold; }

    const Color& color(void) const { return color_; }
    void colorSet(const Color& color) { color_ = color; }

    double size(void) const { return size_; }
    void sizeSet(double size) { size_ = size; }

    void appendText(const char* text) { text_ += text; };
    std::string insertCursor(const char* text);

    PgraphItemText* getAsText() override { return this; }

    PgraphItem* clone() override;

    std::string text_;

    bool   bold_;
    double size_;
    Color  color_;

    bool   back_;
    Color  backColor_;
};

} //namespace T2l
