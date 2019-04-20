#include <string>
#include <chrono>
#include <ctime>

struct Directory;

using namespace std::chrono;

class File {

    Directory* dir;
    std::string mName;
    size_t mSize;
    time_t mLastChange;

public:

    File () = default;

    explicit File (std::string_view name, Directory *parent, size_t size = 0)
        : mName(name),
          mSize(size),
          dir (parent),
          mLastChange (system_clock::to_time_t (system_clock::now()))

    {}

    std::string name() const {

        return mName;
    }

    void rename (std::string_view name) {

        mName = name;
        mLastChange = system_clock::to_time_t (system_clock::now());
    }

    size_t size() const {

        return mSize;
    }

    void resize (size_t size) {

        mSize = size;
        mLastChange = system_clock::to_time_t (system_clock::now());
    }

    std::string lastChange () const {

        return std::ctime (&mLastChange);
    }

    time_t changeInSec () const {

        return mLastChange;
    }

    Directory* directory () const {

        return dir;
    }
};