/****************************************************************************
**
** Copyright (c) 2009-2010, Jaco Naude
**
** This file is part of Qtilities which is released under the following
** licensing options.
**
** Option 1: Open Source
** Under this license Qtilities is free software: you can
** redistribute it and/or modify it under the terms of the GNU General
** Public License as published by the Free Software Foundation, either
** version 3 of the License, or (at your option) any later version.
**
** Qtilities is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with Qtilities. If not, see http://www.gnu.org/licenses/.
**
** Option 2: Commercial
** Alternatively, this library is also released under a commercial license
** that allows the development of closed source proprietary applications
** without restrictions on licensing. For more information on this option,
** please see the project website's licensing page:
** http://www.qtilities.org/licensing.html
**
** If you are unsure which license is appropriate for your use, please
** contact support@qtilities.org.
**
****************************************************************************/

#ifndef ACTIONMANAGER_H
#define ACTIONMANAGER_H

#include <QObject>
#include <QAction>
#include <QShortcut>
#include <QMainWindow>

#include "QtilitiesCoreGui_global.h"
#include "IActionManager.h"

namespace Qtilities {
    namespace CoreGui {
        using namespace Qtilities::CoreGui::Interfaces;

        /*!
        \struct ActionManagerData
        \brief A structure storing private data in action managers.
          */
        struct ActionManagerData;

        /*!
        \class ActionManager
        \brief A class which represents an action manager.
          */
        class QTILITIES_CORE_GUI_SHARED_EXPORT ActionManager : public IActionManager
        {
            Q_OBJECT
            Q_INTERFACES(Qtilities::CoreGui::Interfaces::IActionManager)

        public:
            ActionManager(QObject* parent = 0);
            ~ActionManager();

            // --------------------------------
            // IActionManager Implemenation
            // --------------------------------
            ActionContainer* createMenu(const QString &id, bool& existed);
            ActionContainer* menu(const QString &id);
            ActionContainer* createMenuBar(const QString &id, bool& existed);
            ActionContainer* menuBar(const QString &id);
            Command *registerAction(const QString &id, QAction *action, const QList<int> &context = QList<int>());
            Command *registerActionPlaceHolder(const QString &id, const QString& user_text, const QKeySequence& shortcut = QKeySequence(), const QList<int> &context = QList<int>());
            Command* registerShortcut(QShortcut *shortcut, const QString &default_text, const QList<int> &context);
            Command* command(const QString &id) const;
            ActionContainer *actionContainer(const QString &id) const;
            QHash<QString, Command* > commandMap();
            void restoreDefaultShortcuts();
            bool exportShortcutMapping(const QString& file_name);
            bool importShortcutMapping(const QString& file_name);
            QWidget* commandEditor();

        public slots:
            void handleContextChanged(QList<int> new_contexts);
            void multiContextActionTriggerTester();

        private:
            ActionManagerData* d;
        };
    }
}

#endif // ACTIONMANAGER_H
