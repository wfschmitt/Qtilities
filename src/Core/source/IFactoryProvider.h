/****************************************************************************
**
** Copyright (c) 2009-2013, Jaco Naude
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

#ifndef IFACTORYPROVIDER
#define IFACTORYPROVIDER

#include "QtilitiesCore_global.h"
#include "PointerList.h"
#include "InstanceFactoryInfo.h"
#include "IObjectBase.h"

#include <Logger>

#include <QObject>
#include <QStringList>
#include <QDataStream>
#include <QtilitiesCategory>

class QDomDocument;
class QDomElement;

namespace Qtilities {
    namespace Core {
        using namespace Qtilities::Logging;
        using namespace Interfaces;

        namespace Interfaces {
            /*!
            \class IFactoryProvider
            \brief Objects managing instances of factories can implement this interface if they want to expose these factories to the object manager.

            Objects managing instances of factories can implement this interface if they want to expose these factories to the object manager using the
            Qtilities::Core::Interfaces::IObjectManager::registerIFactoryProvider() function. The interface can be used to represent multiple factories,
            each represented by a QString values. To get a list of all factories provided through the interface, see the providedFactoryTags() function.

            The following example shows how to construct a object through the IFactoryProvider interface:
\code
IFactoryProvider* ifactory = OBJECT_MANAGER->referenceIFactoryProvider("My Factory Tag");
if (ifactory) {
    QObject* obj = ifactory->createInstance(instanceFactoryInfo);
    if (obj) {
        // Do something with the constructed object.
    }
}
\endcode

            For more information see the \ref page_factories article.
            */
            class QTILIITES_CORE_SHARED_EXPORT IFactoryProvider : virtual public IObjectBase {
            public:
                IFactoryProvider() {}
                virtual ~IFactoryProvider() {}

                //! Provides the names of all the factories exposed through this interface.
                virtual QStringList providedFactories() const = 0;
                //! Provides the tags in a specific factory.
                /*!
                  \param factory_name The factory in which the tag is located.
                  \param category_filter Allows you to get tag for a specific category. When empty, all categories are returned.
                  \param ok Set to true if the parameters matches a factory in this provider, false otherwise.
                  \returns The QtilitiesCategory for the found tag. If the tag and factory_name combination is not found by this provider, QtilitiesCategory() is returned.
                  */
                virtual QStringList providedFactoryTags(const QString& factory_name, const QtilitiesCategory& category_filter = QtilitiesCategory(), bool* ok = 0) const = 0;
                //! Provides the category of the specified tag.
                /*!
                  \param factory_name The factory in which the tag is located.
                  \param factory_tag The tag for which the category must is requested.
                  \param ok Set to true if the parameters matches a factory in this provider, false otherwise.
                  \returns The QtilitiesCategory for the found tag. If the tag and factory_name combination is not found by this provider, QtilitiesCategory() is returned.

                  <i>This function was added in %Qtilities v1.2.</i>
                  */
                virtual QtilitiesCategory categoryForTag(const QString& factory_name, const QString& factory_tag, bool* ok = 0) const = 0;
                //! Provides the full tag and category map for the given factory.
                /*!
                  \param factory_name The factory for which the map is requested.
                  \param ok Set to true if the parameters matches a factory in this provider, false otherwise.
                  \returns A QMap with the keys being the tags and the values their corresponding categories. If the factory_name is not a factory provided by this provider, an empty map is returned.

                  <i>This function was added in %Qtilities v1.2.</i>
                  */
                virtual QMap<QString, QtilitiesCategory> tagCategoryMap(const QString& factory_name, bool* ok = 0) const = 0;
                //! Constructs an instance in a specified factory and return it.
                virtual QObject* createInstance(const InstanceFactoryInfo& ifactory_data) = 0;
            };
        }
    }
}

Q_DECLARE_INTERFACE(Qtilities::Core::Interfaces::IFactoryProvider,"com.Qtilities.Core.IFactoryProvider/1.0")

#endif // IFACTORYPROVIDER
