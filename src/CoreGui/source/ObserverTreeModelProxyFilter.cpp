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

#include "ObserverTreeModelProxyFilter.h"
#include "ObserverTreeModel.h"
#include "QtilitiesCoreGuiConstants.h"

#include <Observer.h>
#include <QtilitiesCoreConstants.h>

using namespace Qtilities::CoreGui::Constants;
using namespace Qtilities::Core::Properties;
using namespace Qtilities::Core;
using namespace Qtilities::Core::Constants;

Qtilities::CoreGui::ObserverTreeModelProxyFilter::ObserverTreeModelProxyFilter(QObject* parent) : QSortFilterProxyModel(parent) {
    row_filter_types = ObserverTreeItem::TreeItem;
}

Qtilities::CoreGui::ObserverTreeModelProxyFilter::~ObserverTreeModelProxyFilter() {

}

bool Qtilities::CoreGui::ObserverTreeModelProxyFilter::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const {
    ObserverTreeModel* tree_model = dynamic_cast<ObserverTreeModel*> (sourceModel());

    if (tree_model) {
        // Check if it contains the filterRegExp():
        QModelIndex name_index = sourceModel()->index(sourceRow, tree_model->columnPosition(AbstractObserverItemModel::ColumnName), sourceParent);
        ObserverTreeItem* tree_item = tree_model->getItem(name_index);
        if (tree_item) {
            if (!(row_filter_types & tree_item->itemType()))
                return true;
            else {
                if (!sourceModel()->data(name_index).toString().contains(filterRegExp()))
                    return false;
            }
        } else {
            if (!sourceModel()->data(name_index).toString().contains(filterRegExp()))
                return false;
        }
    }
    return true;
}

void Qtilities::CoreGui::ObserverTreeModelProxyFilter::setRowFilterTypes(ObserverTreeItem::TreeItemTypeFlags type_flags) {
    row_filter_types = type_flags;
}

Qtilities::CoreGui::ObserverTreeItem::TreeItemTypeFlags Qtilities::CoreGui::ObserverTreeModelProxyFilter::rowFilterTypes() const {
    return row_filter_types;
}
