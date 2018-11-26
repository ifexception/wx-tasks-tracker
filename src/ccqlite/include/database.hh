//  TimesheetsTracker is a desktop that aids you in tracking your timesheets
//  and seeing what work you have done.
//
//  Copyright(C)<2018><Szymon Welgus>
//
//  This program is free software : you can redistribute it and /
//  or modify it under the terms of the GNU General Public License as published
//  by the Free Software Foundation
//  , either version 3 of the License
//  , or (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful
//  , but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <https://www.gnu.org/licenses/>.
//
//
//  Contact:
//    szymonwelgus at gmail dot com

#pragma once

#include <chrono>
#include <string>

#include <spdlog/sinks/daily_file_sink.h>
#include <spdlog/spdlog.h>
#include <sqlite3.h>

#include "ccqliteapi.hh"
#include "permission.hh"

namespace ccqlite
{
class CCQLITE_API database
{
  public:
    database() = delete;
    explicit database(const std::string filePath);
    explicit database(const std::string filePath, const permission permission);
    ~database();

    const std::string get_lib_version();
    const int get_lib_version_number();

  private:
    void init_logging();

    sqlite3* pHandle;
};
} // namespace ccqlite
