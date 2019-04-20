#include <vector>
#include <algorithm>
#include "File.h"
#include "directory.h"

time_t Directory::lastChangeInSec () const {

    time_t time;

    const auto max = std::max_element (files.begin(), files.end(),

            [] (const File& max, const File& el) {
                return max.changeInSec() < el.changeInSec();
    });

    for (auto &i : children)

        time = i->lastChangeInSec();


    return std::max ((*max)->changeInSec(), time);
}


time_t Directory::firstChangeInSec () const {

    time_t time;

    const auto min = std::min_element (files.begin(), files.end(),

            [] (const File& min, const File& el) {
                return min.changeInSec() < el.changeInSec();
    });


    for (auto &i : children)

        time = i->firstChangeInSec();

    if (!children.empty())
        return std::min ((*min)->changeInSec(), time);
    else
        return (*min)->changeInSec();
}

Directory::Directory (std::string_view _name)

            : name (_name)

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

void Directory::createFile (std::string_view filename) {

  //  children.push_back (new File (filename, this));
}