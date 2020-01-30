#ifndef LAB4_FILE_H
#define LAB4_FILE_H

#include <chrono>
#include <ctime>
#include <iostream>
#include "directory.h"

using namespace std::chrono;

class Directory;

class File {

    std::string mName;
    Directory* dir;
    size_t mSize;
    time_t mLastChange;

    friend class Filesystem;

public:

    File () = default;

    explicit File (std::string_view name, Directory *parent, size_t size = 0);

    std::string name() const;

    void rename (std::string_view name);

    size_t size() const;

    void resize (size_t size);

    std::string lastChange () const;

    time_t changeInSec () const;

    Directory* directory () const;

    std::string path() const;

    void info() const;
};

#endif //LAB4_FILE_H