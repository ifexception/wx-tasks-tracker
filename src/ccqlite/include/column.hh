//  TimesheetsTracker is a desktop that aids you in tracking your timesheets
//  and seeing what work you have done.
//
//  Copyright(C) <2018> <Szymon Welgus>
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


#pragma once

#include <string>
#include <tuple>

#include <sqlite3.h>

#include "ccqliteapi.hh"
#include "value_type.hh"

namespace ccqlite
{
class CCQLITE_API column
{
  public:
    column() = delete;
    explicit column(const column& other);
    explicit column(sqlite3_stmt* handle);
    ~column() = default;

    column& operator=(const column& other);

    template <class T>
    T get(int index) const;

    template <class... Args>
    std::tuple<Args...> get_columns(int indexes) const;

    const std::string get_name(int index) const noexcept;
    value_type get_type(int index) const noexcept;

  private:
    int get(int index, int) const noexcept;
    unsigned int get(int index, unsigned int) const noexcept;
    long long get(int index, long long) const noexcept;
    double get(int index, double) const noexcept;
    std::string get(int index, std::string) const noexcept;
    const void* get(int index, const void*) const noexcept;

    sqlite3_stmt* pHandle;
};

template <class T>
T column::get(int index) const
{
    return get(index, T());
}

template <class... Args>
std::tuple<Args...> column::get_columns(int indexes) const
{
    return std::make_tuple(get(indexes++, Args())...);
}

} // namespace ccqlite
