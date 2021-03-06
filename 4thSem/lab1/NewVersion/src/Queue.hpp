#ifndef LAB1_QUEUE_HPP
#define LAB1_QUEUE_HPP

#include "StaticArray.hpp"
#include "DynamicArray.hpp"
#include "LinkedList.hpp"

namespace lab {

    /**
     *  @enum Storage
     *  @brief Enumeration of storage types for usage in class Queue
     *
     */
    enum class Storage {
        Static,     /// Enables queue implementation defined in @param StaticArrayQueue
        Dynamic,    /// Enables queue implementation defined in @param DynamicArrayQueue
        LinkedList     /// Enables queue implementation defined in @param LinkedListQueue
    };

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

    /**
     *  @brief Class with queue implementation based on @p StorageType
     *  @attention Use @param SizeForStaticStorage to set max queue size if StorageType == Static
     */
    template <typename T,
              Storage StorageType = Storage::LinkedList,
              std::size_t... SizeForStaticStorage>
    class Queue : public impl::StorageSelector<StorageType>
                         ::template storage_type<T, SizeForStaticStorage...> {

    using StorageImpl = typename impl::StorageSelector<StorageType>
                                 ::template storage_type<T, SizeForStaticStorage...>;
    public:

        explicit Queue () = default;

        /**
       *  @brief Constructs queue from arbitary number of args
       *  @param Args must be same type
       */
        template <typename... Ts>
        Queue(Ts&&... args)
            : StorageImpl (std::forward<Ts>(args)...)
        {}
        ~Queue() noexcept = default;
    };
}




#endif //LAB1_QUEUE_HPP
