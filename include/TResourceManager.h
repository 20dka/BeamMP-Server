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

#pragma once

#include "Common.h"
#include <optional>

using ModMap = HashMap<std::string, size_t>;

class TResourceManager {
public:
    TResourceManager();

    [[nodiscard]] size_t TotalModsSize() const { return mTotalModSize; }
    [[nodiscard]] ModMap FileMap() const { return mMods; }
    [[nodiscard]] static std::string FormatForBackend(const ModMap& mods);
    [[nodiscard]] static std::string FormatForClient(const ModMap& mods);
    [[nodiscard]] static std::optional<std::string> IsModValid(std::string& pathString, const ModMap& mods);
    [[nodiscard]] int LoadedModCount() const { return mMods.size(); }

private:
    size_t mTotalModSize = 0; // size of all mods
    ModMap mMods; // vector of mod names
};
