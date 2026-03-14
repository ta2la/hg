//
// Copyright (C) 2025 Petr Talla. [petr.talla@gmail.com]
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

#include <T2lDisplay.h>

//#include "T2lFilter.h"
//#include "T2lScene.h"
//#include "T2lGObjectPool.h"

#include "T2lDisplayQml.h"

#include <QQuickImageProvider>
#include <QQuickWidget>
#include <QQmlContext>
#include <QQuickWidget>

namespace T2l
{

class WidgetQml : public QQuickWidget
{
    Q_OBJECT
public:
    WidgetQml(bool noScene, QWidget* parent = nullptr);

    class WidgetQmlProvider : public QQuickImageProvider {
    public:
        WidgetQmlProvider();
        QPixmap requestPixmap(const QString &id, QSize *size, const QSize &requestedSize) override;
        static void create(void);

        EntityPack* entityPack() { return display->entityPack(); }
        void refresh() { display->refresh(); }
        //protected:
        QPixmap     pixmap;
        DisplayQml* display;
    };

private:
    //DisplayQml* display_;

};

}
