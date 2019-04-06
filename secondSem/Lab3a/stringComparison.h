
bool operator< (const std::string &lhs, const std::string &rhs) {

    if (lhs.size() != rhs.size())
        return lhs.size() < rhs.size();

    for (int i = 0; i < lhs.size(); ++i) {
        if (lhs[i] != rhs[i])
            return lhs[i] <  rhs[i];
    }

    return false;
}

bool operator<= (const std::string &lhs, const std::string &rhs) {

    return lhs == rhs || lhs < rhs;
}


bool operator> (const std::string &lhs, const std::string &rhs) {

    return !(lhs <= rhs);
}

bool operator>= (const std::string &lhs, const std::string &rhs) {

    return !(lhs < rhs);
}

bool comp (const std::string &lhs, const std::string &rhs) {    // comparator for std::sort

    return lhs.size() < rhs.size();
}