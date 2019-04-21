#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
#include "directory.h"
#include "File.h"

class Filesystem {

    Directory *mRoot;

public:

    explicit Filesystem(std::string_view startName)

            : mRoot(new Directory(startName)) {}

    Directory* root() const {

        return mRoot;
    }

    Directory* findDirectory(std::string path) const {

        using namespace boost::algorithm;

        std::vector<std::string> directories;
        split(directories, path, is_any_of("/"));

        auto temp = mRoot;

        for (const auto &i : directories) {

            for (const auto &j : temp->children)
                if (j->name == i) {
                    temp = j;
                    break;
                }
        }

        if (directories.back() != temp->name)
            temp = nullptr;

        return temp;
    }

    File* findFile (std::string path) const {

        size_t point = path.rfind('/');
        auto filename = path.substr (point + 1, path.size());

        path.resize(point);
        auto ourDir = findDirectory(path);

        for (auto &i : ourDir->files)
            if (i->name() == filename)
                return i;

        return nullptr;
    }

    void createDir (std::string path, std::string_view _name) {

        findDirectory(std::move(path))->createDir(_name);
    }


    void createFile (std::string path, std::string_view _name, size_t size) {

        findDirectory(std::move(path))->createFile(_name, size);
    }

};

#endif