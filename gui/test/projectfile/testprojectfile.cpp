/*
 * Cppcheck - A tool for static C/C++ code analysis
 * Copyright (C) 2007-2011 Daniel Marjamäki and Cppcheck team.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <QtTest>
#include <QObject>
#include "testprojectfile.h"
#include "projectfile.h"

void TestProjectFile::loadInexisting()
{
    const QString filepath(QString(SRCDIR) + "/../projectfiles/foo.cppcheck");
    ProjectFile pfile(filepath);
    QCOMPARE(pfile.Read(), false);
}

void TestProjectFile::loadSimple()
{
    const QString filepath(QString(SRCDIR) + "/../projectfiles/simple.cppcheck");
    ProjectFile pfile(filepath);
    QVERIFY(pfile.Read());
    QCOMPARE(pfile.GetRootPath(), QString("../.."));
    QStringList includes = pfile.GetIncludeDirs();
    QCOMPARE(includes.size(), 2);
    QCOMPARE(includes[0], QString("lib/"));
    QCOMPARE(includes[1], QString("cli/"));
    QStringList paths = pfile.GetCheckPaths();
    QCOMPARE(paths.size(), 2);
    QCOMPARE(paths[0], QString("gui/"));
    QCOMPARE(paths[1], QString("test/"));
    QStringList ignores = pfile.GetIgnoredPaths();
    QCOMPARE(ignores.size(), 1);
    QCOMPARE(ignores[0], QString("gui/temp/"));
    QStringList defines = pfile.GetDefines();
    QCOMPARE(defines.size(), 1);
    QCOMPARE(defines[0], QString("FOO"));
}

void TestProjectFile::loadSimpleNoroot()
{
    const QString filepath(QString(SRCDIR) + "/../projectfiles/simple_noroot.cppcheck");
    ProjectFile pfile(filepath);
    QVERIFY(pfile.Read());
    QCOMPARE(pfile.GetRootPath(), QString());
    QStringList includes = pfile.GetIncludeDirs();
    QCOMPARE(includes.size(), 2);
    QCOMPARE(includes[0], QString("lib/"));
    QCOMPARE(includes[1], QString("cli/"));
    QStringList paths = pfile.GetCheckPaths();
    QCOMPARE(paths.size(), 2);
    QCOMPARE(paths[0], QString("gui/"));
    QCOMPARE(paths[1], QString("test/"));
    QStringList ignores = pfile.GetIgnoredPaths();
    QCOMPARE(ignores.size(), 1);
    QCOMPARE(ignores[0], QString("gui/temp/"));
    QStringList defines = pfile.GetDefines();
    QCOMPARE(defines.size(), 1);
    QCOMPARE(defines[0], QString("FOO"));
}

QTEST_MAIN(TestProjectFile)