#ifndef DATABASEEXCEPTION_HPP
#define DATABASEEXCEPTION_HPP

#include <stdexcept>
#include <string_view>
#include <string>

class DBError : std::runtime_error {
public:
    explicit DBError(std::string_view err)
        : std::runtime_error(err.data())
    {}

public:
    const char* what() const noexcept override;
};

const char* DBError::what() const noexcept {
    return std::runtime_error::what();
}

class NoteSaveError : DBError {
public:

    explicit NoteSaveError ()
        : DBError ("Unable to save note.")
    {}

    const char* what() const noexcept override;
};

const char* NoteSaveError::what() const noexcept {
    return DBError::what();
}


class NoteCreationError : DBError {
public:

    explicit NoteCreationError ()
        : DBError ("Unable to create new note.")
    {}

    const char* what() const noexcept override;
};

const char* NoteCreationError::what() const noexcept {
    return DBError::what();
}

class NoteLoadError : DBError {
public:

    explicit NoteLoadError ()
        : DBError ("Unable to load this note.")
    {}

    const char* what() const noexcept override;
};

const char* NoteLoadError::what() const noexcept {
    return DBError::what();
}

class NoteDeletionError : DBError {
public:

    explicit NoteDeletionError ()
        : DBError ("Unable to delete this note.")
    {}

    const char* what() const noexcept override;
};

const char* NoteDeletionError::what() const noexcept {
    return DBError::what();
}


#endif // DATABASEEXCEPTION_HPP
