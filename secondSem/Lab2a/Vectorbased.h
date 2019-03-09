#include <vector>

template <typename T>
class Vectorbased{

    std::vector <T> v;

public:

    void push(const T &data){
        v.push_back(data);
    }

    void pop(){
        v.erase(v.begin());
    }

    T getFront(){
        return v.front();
    }

    bool isEmpty(){
        return v.empty();
    }
};