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

#include "T2lPoint2.h"
#include "T2lPoint3.h"
#include "T2lDisplayCol.h"
#include "T2lCmdQueue.h"

#include <QQuickImageProvider>
#include <QQuickWidget>
#include <QQmlContext>
#include <QQuickWidget>

namespace T2l
{

class DisplayQml : public QObject, public Display {
    Q_OBJECT
    Q_PROPERTY(int version READ version NOTIFY versionChanged)
public:
    explicit DisplayQml() : Display(Point2F(10, 10), 0.001) {

    }

    int version() const { return m_version; }

    virtual void refresh_() {
        m_version++;
        emit versionChanged();
    }

    virtual int widthPx_()  { return 900; }
    virtual int heightPx_() { return 700; }

    virtual bool isQml() { return true; }
signals:
    void versionChanged();

public slots:
    void enterXy(double x, double y) {
        double ptX = x/(ppm_*0.001) + origin().x();
        double ptY = (500.0-y)/(ppm_*0.001) + origin().y();

        DisplayCol::instance().activeSet(this);
        CmdQueue::queue().enterPoint( Point3F(ptX, ptY, 0), *this );
    }

private:
    QImage m_image;
    int m_version = 0;

};

}
