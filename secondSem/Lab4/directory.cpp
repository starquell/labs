#include "directory.h"
#include "File.h"

#include <algorithm>
#include <limits>
#include <iostream>


time_t Directory::lastChangeInSec () const {

    time_t maxInChildren{};

    const auto max = std::max_element (files.begin(), files.end(),

            [] (const File* max, const File* el) {
                return max->changeInSec() < el->changeInSec();
    });

    for (auto &i: children)
        maxInChildren = std::max (maxInChildren, i->lastChangeInSec());

    return std::max ((*max)->changeInSec(), maxInChildren);
}


time_t Directory::firstChangeInSec () const {

    time_t minInChildren = std::numeric_limits <time_t>::max();

    const auto min = std::min_element (files.begin(), files.end(),

            [] (const File* min, const File* el) {
                return min->changeInSec() < el->changeInSec();
    });


    for (auto &i : children)

       minInChildren = std::min (minInChildren, i->firstChangeInSec());

        return std::min ((*min)->changeInSec(), minInChildren);
}

Directory::Directory (std::string_view _name, Directory* _parent)

            : name (_name),
              parent (_parent)

            {}

size_t Directory::sizeCalculate () const {

    size_t size{};

    for (auto &j : files)

        size += j->size();

    for (auto &i : children)

        size += i->sizeCalculate();

    return size;
}

size_t Directory::subDirectories () const {

    size_t count{};
    count += children.size();

    for (const auto &i : children)
        count += i->subDirectories ();

    return count;
}

size_t Directory::nestedFiles() const {

    size_t count{};

    count += files.size();

    for (auto& i : children)
        count += i->nestedFiles();

    return count;
}

std::string Directory::lastChange () const {

    auto last = lastChangeInSec();
    return std::ctime (&last);
}

std::string Directory::firstChange () const {

    auto first = firstChangeInSec();
    return std::ctime (&first);
}

void Directory::createFile (std::string_view filename, size_t size) {

    files.push_back (new File (filename, this, size));
}

void Directory::createDir(std::string_view dirname) {

    children.push_back (new Directory (dirname, this));
}

std::string Directory::getPath (std::string &temp) const {

    if (parent)
         parent->getPath(temp);

    return temp + "/" + this->name;
}

void Directory::showAll() const {

    std::cout << '<' << name << "> path: " << path() << '\n';

    for (auto &i : files)

        std::cout << "\t (File) " << i->name() << " path: " << i->path();


    for (auto &i : children) {

        std::cout << '\t';
        i->showAll();
    }


}