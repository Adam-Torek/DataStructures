
#include <memory>
#include <string>
#include <stdexcept>

namespace data_structures {
    namespace linear {
        template<class T, class Allocator = std::allocator<T>>
        class dynamic_array {
            public:
                using value_type = T;
                using reference = value_type&;
                using pointer = value_type*;
                using const_reference = const value_type&;
                using const_pointer = const value_type*;
                using size_type = unsigned long;

            private:
                size_type size_;
                size_type capacity_;
                pointer beg;
                pointer end;
                Allocator alloc_;

                void check_range(size_type index) {
                    if(index < 0 || index >= size_) {
                        throw std::out_of_range("Index is either less than 0 and greater than " + std::to_string(size_));
                    }
                }

                void set_metadata(size_type n, size_type capacity, const Allocator& alloc) {
                    size_ = n;
                    capacity_ = capacity;
                    alloc_ = alloc;
                }

            public:

                explicit dynamic_array(const Allocator& alloc) {
                    set_metadata(0, 0, alloc);
                }

                dynamic_array() : dynamic_array(Allocator()) {}

                explicit dynamic_array(size_type n, const Allocator& alloc = Allocator()) {
                    set_metadata(0, n, alloc);
                    beg = alloc_.allocate(n);
                    end = beg+n;
                }

                dynamic_array(size_type n, const value_type& val, const Allocator& alloc = Allocator()) : dynamic_array(n, alloc) {
                    size_ = n;
                    for(int i = 0; i < n; i++) {
                        beg[i] = val;
                    }
                }

                dynamic_array(const dynamic_array& other, const Allocator& alloc) {
                    set_metadata(other.size_, other.capacity_, alloc);
                    beg = alloc_.allocate(size_);
                    for(int i = 0; i < size_; i++) {
                        beg[i] = other[i];
                    }
                    end = beg + size_;
                }

                dynamic_array(const dynamic_array& other) : dynamic_array(other, Allocator()) {}
                

                size_type size() const noexcept {
                    return size_;
                }

                size_type capacity() const noexcept {
                    return capacity_;
                }

                reference at(size_type index) {
                    check_range(index);
                    return beg[index];
                }

                reference operator[](size_type index) {
                    return at(index);
                }

                const_reference at(size_type index) const {
                    check_range(index);
                    return beg[index];
                }

                const_reference operator[](size_type index) const {
                    return at(index);
                }

                void resize(size_type n) {
                    if(n != capacity_) {
                        capacity_ = n;
                        pointer new_beg = alloc_.allocate(capacity_);
                        for(int i = 0; i < n && i < size_; i++) {
                            new_beg[i] = beg[i];
                        }

                        alloc_.deallocate(beg, size_);

                        beg = new_beg;
                        end = new_beg + size_;
                    }
                }
                    

                void reserve(size_type n) {
                    if(capacity_ < n) {
                        int new_capacity = capacity_;
                        while(new_capacity < n) {
                            new_capacity *= 2;
                        }
                        resize(new_capacity);
                    }
                }
        };
    }
}