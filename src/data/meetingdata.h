// Productivity tool to help you track the time you spend on tasks
// Copyright (C) 2020  Szymon Welgus
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.
//
//  Contact:
//    szymonwelgus at gmail dot com

#pragma once

#include <cstdint>
#include <memory>
#include <vector>

#include <spdlog/spdlog.h>

#include "../database/connectionprovider.h"
#include "../database/sqliteconnection.h"
#include "../models/meetingmodel.h"

namespace app::data
{
class MeetingData final
{
public:
    MeetingData();
    ~MeetingData();

    int64_t Create(std::unique_ptr<model::MeetingModel> project);
    std::unique_ptr<model::MeetingModel> GetById(const int projectId);
    void Update(std::unique_ptr<model::MeetingModel> project);
    void Delete(const int projectId);
    std::vector<std::unique_ptr<model::MeetingModel>> GetAll();

private:
    std::shared_ptr<db::SqliteConnection> pConnection;

    bool bBorrowedConnection;

    static const std::string createMeeting;
    static const std::string getMeeting;
    static const std::string updateMeeting;
    static const std::string deleteMeeting;
    static const std::string getMeetings;
};
}
