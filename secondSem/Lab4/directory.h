
#ifndef LAB4_DIRECTORY_H
#define LAB4_DIRECTORY_H


struct Directory {

public:

    std::string name;
    std::vector <Directory*> children;
    std::vector <File*> files;

private:

    time_t lastChangeInSec () const;

    time_t firstChangeInSec () const;

public:

    explicit Directory (std::string_view _name);

    size_t sizeCalculate () const;

    size_t subDirectories () const;

    size_t nestedFiles() const;

    std::string lastChange () const;

    std::string firstChange () const;

    void createFile (std::string_view filename);
};


#endif //LAB4_DIRECTORY_H