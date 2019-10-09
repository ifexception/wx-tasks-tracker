//  Taskable is a desktop that aids you in tracking your timesheets
//  and seeing what work you have done.
//
//  Copyright(C) <2019> <Szymon Welgus>
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

#include "common.h"

#include "../../res/taskable.xpm"
#include "../../res/about.xpm"
#include "../../res/checkforupdate.xpm"
#include "../../res/entry-task.xpm"
#include "../../res/timed-task.xpm"
#include "../../res/stopwatch.xpm"

const char** app::common::GetProgramIcon()
{
    return taskablexpm;
}

const char** app::common::GetAboutIcon()
{
    return aboutxpm;
}

const char** app::common::GetCheckForUpdateIcon()
{
    return checkforupdatexpm;
}

const char** app::common::GetEntryTaskIcon()
{
    return entrytaskxpm;
}

const char** app::common::GetTimedTaskIcon()
{
    return timedtaskxpm;
}

const char** app::common::GetStopwatchIcon()
{
    return stopwatchxpm;
}

std::string app::common::GetLicense()
{
    return "Taskable is a desktop that aids you in tracking your timesheets"
           "and seeing what work you have done.\n"
           "Copyright(C) 2019 Szymon Welgus\n"
           "This program is free software : you can redistribute it and /"
           "or modify it under the terms of the GNU General Public License as published"
           "by the Free Software Foundation"
           ", either version 3 of the License"
           ", or (at your option) any later version.\n"
           "This program is distributed in the hope that it will be useful"
           ", but WITHOUT ANY WARRANTY; without even the implied warranty of"
           "MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the"
           "GNU General Public License for more details.\n"
           "You should have received a copy of the GNU General Public License"
           "along with this program.If not, see <https://www.gnu.org/licenses/>.";
}

wxString app::common::GetVersion()
{
    return wxString::Format(wxT("%d.%d.%d"), TASKABLE_MAJOR, TASKABLE_MINOR, TASKABLE_PATCH);
}

wxString app::common::GetProgramName()
{
    return wxT("Taskable");
}

wxString app::common::GetDbFileName()
{
    return wxT("taskable.db");
}

wxString app::common::GetConfigFileName()
{
    return wxT("taskable.ini");
}
