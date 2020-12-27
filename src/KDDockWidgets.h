/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2020 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

/**
 * @file
 * @brief File with KDDockWidgets namespace-level enums and methods.
 *
 * @author Sérgio Martins \<sergio.martins@kdab.com\>
 */

#ifndef KD_KDDOCKWIDGETS_H
#define KD_KDDOCKWIDGETS_H

#include "Qt5Qt6Compat_p.h"

#include <QObject>
#include <QDebug>

#ifdef Q_OS_WIN
// Only on Windows, where this is popular. On linux the Qt::Tool windows need reparenting. Untested on macOS.
# define KDDOCKWIDGETS_SUPPORTS_NESTED_MAINWINDOWS
#endif

namespace KDDockWidgets
{
    enum Location {
        Location_None,
        Location_OnLeft, ///> Left docking location
        Location_OnTop,  ///> Top docking location
        Location_OnRight, ///> Right docking location
        Location_OnBottom ///> Bottom docking location
    };

    enum MainWindowOption {
        MainWindowOption_None = 0, ///> No option set
        MainWindowOption_HasCentralFrame = 1 ///> Makes the MainWindow always have a central frame, for tabbing documents
    };
    Q_DECLARE_FLAGS(MainWindowOptions, MainWindowOption)

    enum class InitialVisibilityOption {
        StartVisible = 0, ///< The dock widget is made visible when docked
        StartHidden ///< Don't show the dock widget when adding it
    };

    /**
     * @brief Struct describing the preferred dock widget size and visibility when adding it to a layout
     *
     * You can pass this to MainWindowBase::addDockWidget() to give an hint of your preferred size
     * and visibility.
     *
     * See bellow the documentation for InitialOption::visibility and InitialOption::preferredSize.
     *
     * @sa MainWindowBase::addDockWidget()
     */
    struct InitialOption
    {
        // Implicit ctors for convenience:

        InitialOption() = default;

        InitialOption(InitialVisibilityOption v)
            : visibility(v) {}

        /*InitialOption(QSize size)
            : preferredSize(size) {}

        InitialOption(InitialVisibilityOption v, QSize size)
            : visibility(v)
            , preferredSize(size)
        {}*/

        bool startsHidden() const {
            return visibility == InitialVisibilityOption::StartHidden;
        }

        /**
         * @brief Allows a dock widget to be docked as hidden.
         *
         * Next time you call DockWidget::show() it will be shown at that place. This avoids
         * flickering, as no show()/hide() workarounds are needed.
         */
        const InitialVisibilityOption visibility = InitialVisibilityOption::StartVisible;

        /**
         * @brief Allows to control the size a dock widget should get when docked.
         *
         * If an invalid or empty size is passed then KDDW's default heuristics are applied.
         *
         * Note that usually only the width or the height will be honoured: For example, when adding a
         * dock widget to the left then only the preferred width will be taken into account, as the
         * height will simply fill the whole layout.
         */
        //const QSize preferredSize; not yet done.
    };

    ///@internal
    enum FrameOption {
        FrameOption_None = 0,
        FrameOption_AlwaysShowsTabs = 1,
        FrameOption_IsCentralFrame = 2,
        FrameOption_IsOverlayed = 4
    };
    Q_DECLARE_FLAGS(FrameOptions, FrameOption)

    enum RestoreOption {
        RestoreOption_None = 0,
        RestoreOption_RelativeToMainWindow = 1, ///< Skips restoring the main window geometry and the restored dock widgets will use relative sizing.
                                                ///< Loading layouts won't change the main window geometry and just use whatever the user has at the moment.
    };
    Q_DECLARE_FLAGS(RestoreOptions, RestoreOption)

    enum class DropIndicatorType {
        Classic,   ///< The default
        Segmented, ///< Segmented indicators
        None ///< Don't show any drop indicators while dragging
    };

    ///@internal
    inline QString locationStr(Location loc)
    {
        switch (loc) {
        case KDDockWidgets::Location_None:
            return QStringLiteral("none");
        case KDDockWidgets::Location_OnLeft:
            return QStringLiteral("left");
        case KDDockWidgets::Location_OnTop:
            return QStringLiteral("top");
        case KDDockWidgets::Location_OnRight:
            return QStringLiteral("right");
        case KDDockWidgets::Location_OnBottom:
            return QStringLiteral("bottom");
        }

        return QString();
    }

    /// @brief Each main window supports 4 sidebars
    enum class SideBarLocation {
        None,
        North,
        East,
        West,
        South
    };

    ///@brief describes a type of button you can have in the title bar
    enum class TitleBarButtonType {
        Close,
        Float,
        Minimize,
        Maximize,
        Normal, // Restore from maximized state
        AutoHide,
        UnautoHide
    };

    ///@internal
    inline Qt5Qt6Compat::qhashtype qHash(SideBarLocation loc, Qt5Qt6Compat::qhashtype seed)
    {
        return ::qHash(static_cast<uint>(loc), seed);
    }
}

///@internal
inline QDebug operator<<(QDebug d, KDDockWidgets::InitialOption o)
{
    d << o.startsHidden();
    return d;
}

Q_DECLARE_OPERATORS_FOR_FLAGS(KDDockWidgets::FrameOptions)
Q_DECLARE_METATYPE(KDDockWidgets::InitialVisibilityOption)

#endif
