#ifndef LAB1_LISTBASED_HPP
#define LAB1_LISTBASED_HPP

namespace Deque {

    template <class T>
    class Listbased {

        struct Node {
                T data;
                Node* next;
        };

        using Ptr = Node*;

        class Iterator {

        public:
            explicit Iterator (Ptr head, std::size_t size)
                    : mHead(head), mCur(head), mSize(size), mPos(0)
            {}

            Iterator& operator++() {
                if (mPos >= mSize)
                    throw std::out_of_range("");
                mCur = mCur->next? mCur->next : nullptr;
                ++mPos;
                return *this;
            }

            Iterator& operator--() {
                if (mPos == 0)
                    throw std::out_of_range("");

                Iterator temp (*this);
                temp -= 1;
                --mPos;
                mCur = temp.mCur;
                return *this;
            }

            bool operator== (const Iterator &other) const {
                return mHead == other.mHead and mPos == other.mPos;
            }

            bool operator!= (const Iterator &other) const {
                return !(*this == other);
            }

            Iterator operator+ (std::size_t index) const {
                if (mPos + index > mSize)
                    throw std::out_of_range("");
                Iterator temp(*this);

                for (auto i = 0; i < index; ++i)
                    temp.mCur = temp.mCur->next;
                if (mPos + index == mSize)
                    temp.mCur = nullptr;

                temp.mPos += index;
                return temp;
            }

            Iterator operator- (std::size_t index) const {
                if (mPos - index <= 0)
                        throw std::out_of_range("");
                Iterator temp(*this);
                temp.mPos -= index;
                auto tempHead = mHead;
                for (auto i = 0; i < mPos - index; ++i)
                    tempHead = tempHead->next;
                temp.mCur = tempHead;
                return temp;
            }

            T& operator* () {
                return mCur->data;
            }

          private:
            Ptr mHead;
            Ptr mCur;
            std::size_t mPos;
            std::size_t mSize;
        };

    public:

        using value_type = T;

        Listbased() : head(nullptr), mSize(0)
        {}

        void push (const T &data) {
            if (!head)
                head = new Node{data};
            else {
                Ptr temp = head;
                while (temp->next)
                    temp = temp->next;

                temp->next = new Node{data};
            }
            ++mSize;
        }

        void pushFront (const T& data) {

            Ptr newHead = new Node{data, head};
            head = newHead;
            ++mSize;
        }

        void popBack () {
            if (!head)
                return;

            if (!head->next) {
                delete head;
                head = nullptr;
            }
            Ptr temp = head;
            while (temp->next->next)
                temp = temp->next;

            delete temp->next;
            temp->next = nullptr;

            --mSize;
        }

        void popFront() {
            if (!head)
                return;
            Ptr temp = head;
            head = temp->next;

            delete temp;
            --mSize;
        }

        T front() const {
            return head->data;
        }

        T top() const {
            auto temp = head;
            while (temp->next)
                temp = temp->next;
            return temp->data;
        }

        auto size() const {
            return mSize;
        }

        T& operator[] (std::size_t index) {
            if (index >= mSize)
                throw std::out_of_range("");

            auto temp = head;
            for (auto i = 0; i < index; ++i)
                temp = temp->next;
            return temp->data;
        }

        Iterator begin() {
            return Iterator (head, mSize);
        }

        Iterator end() {
            return Iterator (head, mSize) + mSize;
        }

        bool empty () const {
            return mSize == 0;
        }

    private:
        Ptr head;
        std::size_t mSize;
    };
}
#endif //LAB1_LISTBASED_HPP
