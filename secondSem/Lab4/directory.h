#ifndef LAB4_DIRECTORY_H
#define LAB4_DIRECTORY_H

#include <string>
#include <vector>

struct File;

struct Directory {

public:

    std::string name;
    Directory *parent;
    std::vector <Directory*> children;
    std::vector <File*> files;


private:


    time_t lastChangeInSec () const;

    time_t firstChangeInSec () const;

    std::string getPath (std::string &temp) const;

public:

    explicit Directory (std::string_view _name, Directory *_parent = nullptr);

    size_t sizeCalculate () const;

    size_t subDirectories () const;

    size_t nestedFiles() const;

    std::string lastChange () const;

    std::string firstChange () const;

    void createFile (std::string_view filename, size_t size = 0);

    void createDir (std::string_view dirname);

    std::string path() const {

        std::string temp;
        return getPath (temp);
    }

    void showAll () const;

};


#endif //LAB4_DIRECTORY_H