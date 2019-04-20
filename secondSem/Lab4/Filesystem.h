#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
#include "directory.cpp"

class Filesystem {

    Directory *root;

public:

    explicit Filesystem (std::string_view startName)

            : root (new Directory (startName))
    {}

    Directory* findDirectory (std::string path) const {

        using namespace boost::algorithm;

        std::vector <std::string> directories;
        split(directories, path, is_any_of("/"));

        auto temp = root;

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

        size_t point = path.rfind ('/');
        auto filename = path.substr (point, path.size());

        path.resize (point);
        auto ourDir = findDirectory (path);

        for (auto &i : ourDir->files)
            if (i->name() == filename)
                return i;

        return nullptr;
    }


};



