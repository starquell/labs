#ifndef LAB4_FILE_H
#define LAB4_FILE_H

#include <string>
#include <chrono>
#include <ctime>

using namespace std::chrono;

class Directory;

class File {

    std::string mName;
    Directory* dir;
    size_t mSize;
    time_t mLastChange;

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

};

#endif //LAB4_FILE_H