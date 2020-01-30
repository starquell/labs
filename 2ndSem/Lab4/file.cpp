#include "directory.h"
#include "file.h"


std::string File::path() const {

    return dir->path() + "/" + mName;
}

Directory* File::directory() const {

    return dir;
}

time_t File::changeInSec() const {

    return mLastChange;
}

std::string File::lastChange() const {

    return std::ctime (&mLastChange);
}

void File::resize(size_t size) {

    mSize = size;
    mLastChange = system_clock::to_time_t (system_clock::now());
}

size_t File::size() const {

    return mSize;
}

void File::rename(std::string_view name) {

    mName = name;
    mLastChange = system_clock::to_time_t (system_clock::now());
}

std::string File::name() const {

    return mName;
}

File::File(std::string_view name, Directory *parent, size_t size)
        : mName(name),
          mSize(size),
          dir (parent),
          mLastChange (system_clock::to_time_t (system_clock::now()))

{}

void File::info() const {

    std::cout << "Name : " << mName
              << "\nSize : " << mSize
              << "\nParent directory : " << dir->path()
              << "\nLast change : " << lastChange() << "\n\n";
}