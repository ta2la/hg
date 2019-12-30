//
// Copyright (C) 2019 Petr Talla. [petr.talla@gmail.com]
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

#include "T2lFilter.h"
#include <QList>

namespace T2l
{

//=============================================================================
class FilterCol : public Filter {
//=============================================================================
public:
//<ENUMS>
    enum EType { FT_AND, FT_OR };
//<CONSTRUCTION>
    FilterCol(EType type);
    virtual ~FilterCol() {}

    void add(Filter* filter) { filters_.append(filter); }
//<METHODS>
//=============================================================================
//<OVERRIDES>
    virtual bool pass(TcObject* object);
    virtual std::string print() { return "FILTER COLLLECTION"; }
//protected:
    EType          type_;
    QList<Filter*> filters_;
};

} // namespace T2l