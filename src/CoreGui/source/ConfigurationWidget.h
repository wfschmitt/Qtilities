/****************************************************************************
**
** Copyright (c) 2009-2011, Jaco Naude
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

#ifndef CONFIGURATIONWIDGET_H
#define CONFIGURATIONWIDGET_H

#include "QtilitiesCoreGui_global.h"
#include "QtilitiesCoreGuiConstants.h"
#include "IConfigPage.h"

#include <QWidget>
#include <QTreeWidgetItem>

namespace Ui {
    class ConfigurationWidget;
}

namespace Qtilities {
    namespace CoreGui {
        using namespace Qtilities::CoreGui::Interfaces;

        /*!
          \struct ConfigurationWidgetPrivateData
          \brief The ConfigurationWidgetPrivateData struct stores private data used by the ConfigurationWidget class.
         */
        struct ConfigurationWidgetPrivateData;

        /*!
        \class ConfigurationWidget
        \brief Configuration widget which displays config pages from widgets implementing the Qtilities::CoreGui::Interfaces::IConfigPage interface.

        The configuration widget is a simple widget which can be used to display user settings in your applications. There are many such widgets available to Qt developers, and it is not very difficult to create a simple widget yourself. However, to do it properly takes time and doing it properly normally introduces bugs. Thus, the %Qtilities configuration widget provides a ready to use, tested, extendable and configurable configuration widget solution.

        ConfigurationWidget shows configuration pages that implements Qtilities::CoreGui::Interfaces::IConfigPage. To show pages in the configuration widget, register them in the global object pool and call initialize() on the configuration widget. The widget will find all configuration pages in the object pool. Parts of %Qtilities provides ready to use configuration pages to use in your application. For example:

\code
// The shortcuts editor for commands in your application:
OBJECT_MANAGER->registerObject(ACTION_MANAGER->commandEditor());

// Logging configuration page:
OBJECT_MANAGER->registerObject(LoggerGui::createLoggerConfigWidget());

// Extension system configuration page:
OBJECT_MANAGER->registerObject(EXTENSION_SYSTEM->configWidget());

// The project manager configuration page:
OBJECT_MANAGER->registerObject(PROJECT_MANAGER->configWidget());
\endcode

        To create your widget, add something like the following to your \p main.cpp code:

\code
int main(int argc, char *argv[])
{
    QtilitiesApplication a(argc, argv);

    // Create a settings window for our application:
    ConfigurationWidget* config_widget = new ConfigurationWidget;
    QtilitiesApplication::setConfigWidget(config_widget);

    // ... Lots of application code ...
    // Initialize the widget as soon as all your pages are registered in the global object pool:
    config_widget->initialize();

\endcode

        It is now possible to access the configuration widget from anywhere in your application and perform actions on it:
\code
if (QtilitiesApplication::configWidget()) {
    ConfigurationWidget* config_widget = qobject_cast<ConfigurationWidget*> (QtilitiesApplication::configWidget());
    if (config_widget) {
        // First call initialize on the config_widget to make sure it has all the pages available in the global object pool:
        config_widget->initialize();
        if (config_widget->hasPage(tr("My Page"))) {
            // We can get the interface to this page like this:
            IConfigWidget* config_widget_iface = config_widget->getPage("My Page");

            // Or we can show this page:
            config_widget->setActivePage(tr("Code Editors"));
            config_widget->show();
        }
    }
}
\endcode

        Below is an example of the configuartion widget taken from the Object Management Example in the QtilitiesExamples project:

        \image html project_configuration_widget.jpg "Project Configuration Widget"

        It is possible to either show the configuration pages as a list as shown above, or it can be shown as a categorized tree by using the correct Qtilities::DisplayMode in the constructor. This allows your pages to provide a Qtilities::Core::QtilitiesCategory to use in the categorized tree through the \p IConfigPage interface.

        \sa Qtilities::CoreGui::Interfaces::IConfigPage

        \section configuration_widget_storage_layout Configuration settings storage in Qtilities

        Throughout %Qtilities the modules store application settings using \p QSettings. For this method to work properly, it is important to construct your \p QApplication object properly as shown below:
\code
int main(int argc, char *argv[])
{
    QtilitiesApplication a(argc, argv);
    QtilitiesApplication::setOrganizationName("Jaco Naude");
    QtilitiesApplication::setOrganizationDomain("Qtilities");
    QtilitiesApplication::setApplicationName("Object Management Example");
    QtilitiesApplication::setApplicationVersion(QtilitiesApplication::qtilitiesVersionString());
\endcode

        The construction of the QSettings object is done as follows everywhere that settings are saved. This example saves settings of a specific ObserverWidget:
\code
QSettings settings;
settings.beginGroup("Qtilities");
settings.beginGroup("GUI");
settings.beginGroup(d->global_meta_type);
// .... Stores some ObserverWidget stuff ...
settings.endGroup();
settings.endGroup();
settings.endGroup();
\endcode

        Thus, the settings are saved throughout the %Qtilities modules under the default place used by QSettings, under a group called %Qtilities. For more information see the QSettings documentation.
          */
        class QTILITIES_CORE_GUI_SHARED_EXPORT ConfigurationWidget : public QWidget {
            Q_OBJECT

        public:
            ConfigurationWidget(DisplayMode display_mode = TableView, QWidget *parent = 0);
            ~ConfigurationWidget();

            //! Initializes the config widget with the given set of config pages.
            void initialize(QList<IConfigPage*> config_pages);
            //! Initializes the widget with a list of QObjects. All objects in the list which implements the IConfigPage interface will be added.
            /*!
              You can initialize the ConfigurationWidget multiple times and when called more than once it will just rescan the global object pool
              \note If the list is empty, the function will search the global object pool and automatically add all found config pages. A debug message with information about the found pages will be created.
              */
            void initialize(QList<QObject*> config_pages = QList<QObject*>());

            //! Sets the way the configuration widget handles the \p Apply button.
            /*!
              \param apply_all_pages When true, the apply button will call apply on all the configuration pages. When false, only the active page will be applied.

              Default is true;
              */
            void setApplyAllPages(bool apply_all_pages);
            //! Gets the way the configuration widget handles the \p Apply button.
            bool applyAllPages() const;
            //! Checks if a configuration page with the given name exists.
            bool hasPage(const QString& page_name) const;
            //! Checks if a configuration page with the given name exists and if so returns a pointer to the interface.
            IConfigPage* getPage(const QString& page_name) const;

       signals:
            //! Signal emitted whenever a config page is applied.
            void appliedPage(IConfigPage* conig_page);

        public slots:
            //! Handles the close button.
            void on_btnClose_clicked();
            //! Handles the apply button.
            void on_btnApply_clicked();
            //! Handles item changes in the page tree.
            void handleActiveItemChanges(QList<QObject*> active_pages);
            //! Function to set the active page.
            void setActivePage(const QString& active_page_name);
            //! Function to get the active page name and category.
            QString activePageName() const;
            //! Function to get the reference to the IConfig interface of the active page.
            IConfigPage* activePageIFace() const;

        protected:
            void changeEvent(QEvent *e);

        private:
            Ui::ConfigurationWidget* ui;
            ConfigurationWidgetPrivateData* d;

        signals:
        };
    }
}

#endif // GLOBALPROPERTYEDITOR_H
