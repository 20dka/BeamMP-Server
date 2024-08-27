// BeamMP, the BeamNG.drive multiplayer mod.
// Copyright (C) 2024 BeamMP Ltd., BeamMP team and contributors.
//
// BeamMP Ltd. can be contacted by electronic mail via contact@beammp.com.
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Affero General Public License as published
// by the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#include "TResourceManager.h"

#include <algorithm>
#include <filesystem>

namespace fs = std::filesystem;

std::string TResourceManager::FormatForBackend(const HashMap<std::string, size_t>& mods) {
    std::string monkey;
    for (const auto& [name, size] : mods) {
        monkey += name + ';';
    }
    return monkey;
}
std::string TResourceManager::FormatForClient(const HashMap<std::string, size_t>& mods) {
    std::string monkey = FormatForBackend(mods);
    for (const auto& [name, size] : mods) {
        monkey += std::to_string(size) + ';';
    }
    beammp_infof("hihi {}", monkey);
    return monkey;
}

TResourceManager::TResourceManager() {
    Application::SetSubsystemStatus("ResourceManager", Application::Status::Starting);
    std::string basePath = Application::Settings.getAsString(Settings::Key::General_ResourceFolder) + "/Client";
    if (!fs::exists(basePath))
        fs::create_directories(basePath);
    std::vector<std::string> modNames;
    for (const auto& entry : fs::directory_iterator(basePath)) {
        std::string path(entry.path().string());
        if (entry.path().extension() == ".zip") {
            mMods[entry.path().filename()] = entry.file_size();
            mTotalModSize += entry.file_size();
        }
    }

    if (!mMods.empty()) {
        beammp_infof("Loaded {} mod{}", mMods.size(), mMods.size()!=1 ? 's' : ' ' );
    }

    Application::SetSubsystemStatus("ResourceManager", Application::Status::Good);
}
