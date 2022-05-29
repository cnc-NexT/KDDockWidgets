/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#ifndef KD_MAINWINDOW_MDI_QTQUICK_H
#define KD_MAINWINDOW_MDI_QTQUICK_H
#pragma once

#include "views/MainWindowMDI.h"
#include "qtquick/views/MainWindow_qtquick.h"

namespace KDDockWidgets {


/// @brief MainWindow sub-class which uses MDI as a layout
class DOCKS_EXPORT MainWindowMDI_qtquick : public Views::MainWindow_qtquick, public Views::MainWindowMDI
{
    Q_OBJECT
public:
    using Views::MainWindowMDI::addDockWidget;

    ///@brief Constructor. See base class documentation
    explicit MainWindowMDI_qtquick(const QString &uniqueName, QQuickItem *parent = nullptr,
                                   Qt::WindowFlags flags = Qt::WindowFlags());

    ///@brief Destructor
    ~MainWindowMDI_qtquick() override;
};

}

#endif
