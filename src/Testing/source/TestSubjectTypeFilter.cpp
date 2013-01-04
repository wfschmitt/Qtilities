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

#include "TestSubjectTypeFilter.h"

#include <QtilitiesCoreGui>
using namespace QtilitiesCoreGui;

#include <TreeIterator>

int Qtilities::Testing::TestSubjectTypeFilter::execTest(int argc, char ** argv) {
    return QTest::qExec(this,argc,argv);
}

void Qtilities::Testing::TestSubjectTypeFilter::testSubjectTypeFiltering() {
    TreeNode node("node");
    SubjectTypeFilter* subject_type_filter = node.setChildType("Test Type");
    QVERIFY(subject_type_filter->inverseFilteringEnabled() == true);

    QVERIFY(node.subjectCount() == 0);
    QObject* obj = new QObject;
    obj->setObjectName("Object1");
    node.attachSubject(obj);
    QVERIFY(node.subjectCount() == 1);
    node.detachSubject(obj);
    QVERIFY(node.subjectCount() == 0);

    TreeItem* tree_item = new TreeItem("TreeItem");
    node.attachSubject(tree_item);
    QVERIFY(node.subjectCount() == 1);
    node.detachAll();
    QVERIFY(node.subjectCount() == 0);

    subject_type_filter->addSubjectType(SubjectTypeInfo("Qtilities::CoreGui::TreeItem","Qtilities tree item"));
    node.attachSubject(tree_item);
    QVERIFY(node.subjectCount() == 0);
    subject_type_filter->enableInverseFiltering(false);
    node.attachSubject(tree_item);
    QVERIFY(node.subjectCount() == 1);
    node.detachAll();
    QVERIFY(node.subjectCount() == 0);

    obj = new QObject;
    obj->setObjectName("Object2");
    node.attachSubject(obj);
    QVERIFY(node.subjectCount() == 0);
    subject_type_filter->addSubjectType(SubjectTypeInfo("QObject","Normal QObject"));
    node.attachSubject(obj);
    QVERIFY(node.subjectCount() == 1);
}
