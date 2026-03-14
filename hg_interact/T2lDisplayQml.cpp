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
#include "T2lDisplayQml.h"



using namespace T2l;

//=============================================================================
/*void WidgetQmlProvider::create()
{
    QQuickWidget *quickWidget = new QQuickWidget;
    quickWidget->setResizeMode(QQuickWidget::SizeRootObjectToView);
    quickWidget->setWindowTitle("CREATE");
    quickWidget->resize(400, 300);
    WidgetQmlProvider* view = new WidgetQmlProvider();
    quickWidget->engine()->addImageProvider("mybitmap", view);
    quickWidget->setSource(QUrl("qrc:/hg_display.qml"));
    quickWidget->show();
    quickWidget->rootContext()->setContextProperty("display", view->display);

    Scene* scene = new Scene(new Filter());
    GObjectPool::instance().addRefCol(scene);

    scene->entities().addDisplay(view->display);
}*/

//=============================================================================
