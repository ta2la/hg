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
#include "T2lWidgetQml.h"
#include "T2lUpdateLock.h"
#include "T2lScene.h"
#include "T2lFilter.h"
#include "T2lGObjectPool.h"
#include "T2lEntityLine.h"

using namespace T2l;

//=============================================================================
WidgetQml::WidgetQml(bool noScene, QWidget* parent) :
    QQuickWidget(parent)
{
    setResizeMode(QQuickWidget::SizeRootObjectToView);
    setWindowTitle("Floating QML Widget");
    resize(400, 300);
    WidgetQmlProvider* view = new WidgetQmlProvider();
    engine()->addImageProvider("mybitmap", view);
    setSource(QUrl("qrc:/hg_display.qml"));
    rootContext()->setContextProperty("display", view->display);

    if (noScene) {
        for (int i = -200; i < 200; i+=10) {
            EntityPack* pack = view->entityPack();

            pack->add(new EntityLine(Point2F(-200, i), Point2F(200, i), Color::BLACK, 0.5));
            pack->add(new EntityLine(Point2F(i, -200), Point2F(i, 200), Color::BLACK, 0.5));
        }
    }
    else
    {
        Scene* scene = new Scene(new Filter());
        GObjectPool::instance().addRefCol(scene);

        scene->entities().addDisplay(view->display);
        UpdateLock l;
    }
}

//=============================================================================
WidgetQml::WidgetQmlProvider::WidgetQmlProvider() :
    QQuickImageProvider(QQuickImageProvider::Pixmap),
    pixmap("/home/rce/COMPUTER/violet.jpg"),
    display(new DisplayQml())
{
}

//=============================================================================
QPixmap WidgetQml::WidgetQmlProvider::requestPixmap(const QString &id, QSize *size, const QSize &requestedSize)
{
    Q_UNUSED(id); // For this simple example, we ignore the id
    if (size) {
        if (display->bitmap() == nullptr) {
            *size = pixmap.size();
        }
        else {
            *size = display->bitmap()->size();
        }
        //if (requestedSize.isValid()) {
        if (display->bitmap() == nullptr) {
            return pixmap.scaled(requestedSize);
        }
        else {
            return *display->bitmap();//->scaled(requestedSize);
        }
        //}
    }
    return pixmap;
}

//=============================================================================
