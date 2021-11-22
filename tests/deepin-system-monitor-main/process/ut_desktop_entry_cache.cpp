/*
* Copyright (C) 2019 ~ 2021 Uniontech Software Technology Co.,Ltd.
*
* Author:     lishiqi <lishiqi@uniontech.com>
*
* Maintainer: lishiqi  <lishiqi@uniontech.com>
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
//self
#include "process/desktop_entry_cache.h"
#include "process/desktop_entry_cache_updater.h"
//gtest
#include "stub.h"
#include <gtest/gtest.h>
//Qt
#include <QFileInfo>

using namespace core::process;

class UT_DesktopEntryCache : public ::testing::Test
{
public:
    UT_DesktopEntryCache() : m_tester(nullptr) {}

public:
    virtual void SetUp()
    {
        m_tester = new DesktopEntryCache();
    }

    virtual void TearDown()
    {
        delete m_tester;
    }

protected:
    DesktopEntryCache *m_tester;
};

TEST_F(UT_DesktopEntryCache, initTest)
{

}

TEST_F(UT_DesktopEntryCache, test_contains_001)
{
    DesktopEntry entry;
    QString key("test");

    m_tester->m_cache.insert(key, entry);

    EXPECT_EQ(m_tester->contains(key), true);
}

TEST_F(UT_DesktopEntryCache, test_entry_001)
{
    QString key("test");

    const QString filePath("test.desktop");
    const QString name = "test1";
    const QString displayName = "DisplayTest1";
    const QString exec = QString("/usr/bin/%1").arg(name);
    const QString icon = "/usr/share/test1/icon";
    const QString startup = name;

    QFile file(filePath);

    // 创建desktop文件
    if(file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QByteArray data;
        file.write("[Desktop Entry]\n");
        file.write(QString("Name=%1\n").arg(name).toUtf8());
        file.write(QString("GenericName=%1\n").arg(displayName).toUtf8());
        file.write("Type=Application\n");
        file.write(QString("Exec=%1\n").arg(exec).toUtf8());
        file.write(QString("Icon=%1\n").arg(icon).toUtf8());
        file.write("Categories=Utility\n");
        file.write(QString("StartupWMClass=%1\n").arg(startup).toUtf8());
        file.close();
    }

    QFileInfo info(filePath);
    DesktopEntry entry = DesktopEntryCacheUpdater::createEntry(info);

    m_tester->m_cache.insert(key, entry);

    EXPECT_EQ(m_tester->entry(key)->name, name);

    if(file.exists()) {
        file.remove();
    }
}

TEST_F(UT_DesktopEntryCache, test_entryWithDesktopFile_001)
{
    QString key("test");

    const QString filePath("test.desktop");
    const QString name = "test1";
    const QString displayName = "DisplayTest1";
    const QString exec = QString("/usr/bin/%1").arg(name);
    const QString icon = "/usr/share/test1/icon";
    const QString startup = name;

    QFile file(filePath);

    // 创建desktop文件
    if(file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QByteArray data;
        file.write("[Desktop Entry]\n");
        file.write(QString("Name=%1\n").arg(name).toUtf8());
        file.write(QString("GenericName=%1\n").arg(displayName).toUtf8());
        file.write("Type=Application\n");
        file.write(QString("Exec=%1\n").arg(exec).toUtf8());
        file.write(QString("Icon=%1\n").arg(icon).toUtf8());
        file.write("Categories=Utility\n");
        file.write(QString("StartupWMClass=%1\n").arg(startup).toUtf8());
        file.close();
    }

    QFileInfo info(filePath);
    DesktopEntry entry = DesktopEntryCacheUpdater::createEntry(info);

    m_tester->m_cache.insert(key, entry);

    EXPECT_EQ(m_tester->entryWithDesktopFile(filePath)->name, name);

    if(file.exists()) {
        file.remove();
    }
}

TEST_F(UT_DesktopEntryCache, test_entryWithSubName_001)
{
    QString key("test");

    const QString filePath("test.desktop");
    const QString name = "test1";
    const QString displayName = "DisplayTest1";
    const QString exec = QString("/usr/bin/%1").arg(name);
    const QString icon = "/usr/share/test1/icon";
    const QString startup = name;

    QFile file(filePath);

    // 创建desktop文件
    if(file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QByteArray data;
        file.write("[Desktop Entry]\n");
        file.write(QString("Name=%1\n").arg(name).toUtf8());
        file.write(QString("GenericName=%1\n").arg(displayName).toUtf8());
        file.write("Type=Application\n");
        file.write(QString("Exec=%1\n").arg(exec).toUtf8());
        file.write(QString("Icon=%1\n").arg(icon).toUtf8());
        file.write("Categories=Utility\n");
        file.write(QString("StartupWMClass=%1\n").arg(startup).toUtf8());
        file.close();
    }

    QFileInfo info(filePath);
    DesktopEntry entry = DesktopEntryCacheUpdater::createEntry(info);

    m_tester->m_cache.insert(key, entry);

    EXPECT_EQ(m_tester->entryWithSubName(key)->name, name);

    if(file.exists()) {
        file.remove();
    }
}

TEST_F(UT_DesktopEntryCache, test_updateCache_001)
{
    m_tester->updateCache();
    EXPECT_GT(m_tester->m_cache.size(), 0);

}
