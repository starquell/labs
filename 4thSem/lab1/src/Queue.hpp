#ifndef LAB1_QUEUE_HPP
#define LAB1_QUEUE_HPP

#include "StaticArray.hpp"
#include "DynamicArray.hpp"
#include "LinkedList.hpp"

namespace lab {

    enum class Storage {Static, Dynamic, LinkedList};

    namespace impl {

        class UndefinedStorage {};

        template <Storage storage>
        struct StorageSelector {
            using storage_type = UndefinedStorage;
        };

        template <>
        struct StorageSelector<Storage::Static> {

            template <typename T, std::size_t SizeForStatic>
            using storage_type = impl::StaticArrayQueue<T, SizeForStatic>;
        };

        template <>
        struct StorageSelector<Storage::Dynamic> {
            template <typename T>
            using storage_type = impl::DynamicArrayQueue<T>;
        };

        template <>
        struct StorageSelector<Storage::LinkedList> {
            template <typename T>
            using storage_type = impl::LinkedListQueue<T>;
        };
    }

    template <typename T,
              Storage StorageType = Storage::LinkedList,
              std::size_t... SizeForStaticStorage>
    class Queue : public impl::StorageSelector<StorageType>
                         ::template storage_type<T, SizeForStaticStorage...> {

    using StorageImpl = typename impl::StorageSelector<StorageType>
                                 ::template storage_type<T, SizeForStaticStorage...>;
    public:

        explicit Queue () = default;

        template <typename... Ts>
        Queue(Ts&&... args)
            : StorageImpl (std::forward<Ts>(args)...)
        {}
        ~Queue() noexcept = default;
    };
}




#endif //LAB1_QUEUE_HPP
