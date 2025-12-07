//
// Created by omank on 7.12.2025.
//

#ifndef GAMEDEVELOPMENTPROJECT_FILESYSTEM_H
#define GAMEDEVELOPMENTPROJECT_FILESYSTEM_H
#include <filesystem>

namespace eng {
    class FileSystem {
    public:
        std::filesystem::path GetExecutableFolder() const;
        std::filesystem::path GetAssetsFolder() const;
    };
} // eng

#endif //GAMEDEVELOPMENTPROJECT_FILESYSTEM_H