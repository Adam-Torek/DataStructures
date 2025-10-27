
#include <compare>
#include <initializer_list>
#include <iterator>
#include <memory>
#include <pthread.h>
#include <string>
#include <stdexcept>
#include <type_traits>

namespace data_structures {
    namespace linear {

        template<class T>
        class dynamic_array_iterator {        
            public:       
                using value_type = T;
                using reference = value_type&;
                using pointer = value_type*;
                using difference_type = unsigned long;
                using iterator_category = std::random_access_iterator_tag;
                using iter_traits = std::iterator_traits<dynamic_array_iterator<T>>;

             private:
                pointer curr_ptr_;
             public:
                dynamic_array_iterator(): curr_ptr_(nullptr) {};
                dynamic_array_iterator(pointer start_ptr) : curr_ptr_(start_ptr) {};
                dynamic_array_iterator(const dynamic_array_iterator& other) : curr_ptr_(other.get_pointer()) {};
                ~dynamic_array_iterator() = default;

                inline dynamic_array_iterator& operator=(const dynamic_array_iterator& other) = default;

                inline dynamic_array_iterator& operator=(const pointer other_ptr) {
                    curr_ptr_ = other_ptr;
                    return *this;
                }

                inline dynamic_array_iterator& operator++() {
                    ++curr_ptr_;
                    return *this;
                }

                inline dynamic_array_iterator operator++(int) {
                    dynamic_array_iterator temp = dynamic_array_iterator(*this);
                    ++curr_ptr_;
                    return temp;
                }

                inline dynamic_array_iterator& operator--() {
                    --curr_ptr_;
                    return *this;
                }

                inline dynamic_array_iterator operator--(int) {
                    dynamic_array_iterator temp = dynamic_array_iterator(*this);
                    --curr_ptr_;
                    return temp;
                }

                inline reference operator*() const {
                    return *curr_ptr_;
                }

                inline pointer operator->() const {
                    return curr_ptr_;
                }

                inline pointer operator[](const difference_type n) const {
                    return curr_ptr_ + n;
                }
                
                inline dynamic_array_iterator& operator+=(const difference_type n) {
                    curr_ptr_ += n;
                    return *this;
                }

                inline dynamic_array_iterator& operator-=(const difference_type n) {
                    curr_ptr_ -= n;
                    return *this;
                }

                inline difference_type operator-(dynamic_array_iterator& other) const {
                    return curr_ptr_ - other.get_pointer();
                }

                inline dynamic_array_iterator operator-(const difference_type n) const {
                    return dynamic_array_iterator(get_pointer() - n);
                }

                inline dynamic_array_iterator operator+(const difference_type n) const {
                    return dynamic_array_iterator(get_pointer() + n);
                }

                friend inline dynamic_array_iterator operator+(const difference_type n, const dynamic_array_iterator other) {
                    return dynamic_array_iterator(n + other.get_pointer());
                }

                friend inline dynamic_array_iterator operator-(const difference_type n, const dynamic_array_iterator other) {
                    return dynamic_array_iterator(n - other.get_pointer());
                }

                inline bool operator==(const dynamic_array_iterator& other) const {
                    return curr_ptr_ == other.get_pointer();
                }

                inline std::strong_ordering operator<=>(const dynamic_array_iterator& other) const {
                    if(curr_ptr_ > other.get_pointer()) {
                        return std::strong_ordering::greater;
                    }
                    else if(curr_ptr_ < other.get_pointer()) {
                        return std::strong_ordering::less;
                    }
                    return std::strong_ordering::equivalent;
                }

                inline pointer get_pointer() const {
                    return curr_ptr_;
                }
        };

        template<class T>
        class dynamic_array_const_iterator {
             public:
                using value_type = const T;
                using reference = value_type&;
                using pointer = value_type*;
                using difference_type = unsigned long;
                using iterator_category = std::random_access_iterator_tag;
                using iter_traits = std::iterator_traits<dynamic_array_const_iterator<T>>;

             private:
                pointer curr_ptr_;
            public:
                dynamic_array_const_iterator(): curr_ptr_(nullptr) {};
                dynamic_array_const_iterator(pointer start_ptr) : curr_ptr_(start_ptr) {};
                dynamic_array_const_iterator(const dynamic_array_const_iterator& other) : curr_ptr_(other.get_pointer()) {};
                dynamic_array_const_iterator(const dynamic_array_iterator<T>& other) : 
                    curr_ptr_(const_cast<pointer>(other.get_pointer())) {};
                ~dynamic_array_const_iterator() = default;

                inline dynamic_array_const_iterator& operator=(const dynamic_array_const_iterator& other) = default;

                inline dynamic_array_const_iterator& operator=(const pointer other_ptr) {
                    curr_ptr_ = other_ptr;
                    return *this;
                }

                inline dynamic_array_const_iterator& operator++() {
                    ++curr_ptr_;
                    return *this;
                }

                inline dynamic_array_const_iterator operator++(int) {
                    dynamic_array_const_iterator temp = dynamic_array_const_iterator(*this);
                    ++curr_ptr_;
                    return temp;
                }

                inline dynamic_array_const_iterator& operator--() {
                    --curr_ptr_;
                    return *this;
                }

                inline dynamic_array_const_iterator operator--(int) {
                    dynamic_array_const_iterator temp = dynamic_array_const_iterator(*this);
                    --curr_ptr_;
                    return temp;
                }

                inline reference operator*() const {
                    return *curr_ptr_;
                }

                inline pointer operator->() const {
                    return curr_ptr_;
                }

                inline pointer operator[](const difference_type n) const {
                    return curr_ptr_ + n;
                }
                
                inline dynamic_array_const_iterator& operator+=(const difference_type n) {
                    curr_ptr_ += n;
                    return *this;
                }

                inline dynamic_array_const_iterator& operator-=(const difference_type n) {
                    curr_ptr_ -= n;
                    return *this;
                }

                inline difference_type operator-(dynamic_array_const_iterator& other) const {
                    return curr_ptr_ - other.get_pointer();
                }

                inline dynamic_array_const_iterator operator-(const difference_type n) const {
                    return dynamic_array_const_iterator(get_pointer() - n);
                }

                inline dynamic_array_const_iterator operator+(const difference_type n) const {
                    return dynamic_array_const_iterator(get_pointer() + n);
                }

                friend inline dynamic_array_const_iterator operator+(const difference_type n, const dynamic_array_const_iterator other) {
                    return dynamic_array_const_iterator(n + other.get_pointer());
                }

                friend inline dynamic_array_const_iterator operator-(const difference_type n, const dynamic_array_const_iterator other) {
                    return dynamic_array_const_iterator(n - other.get_pointer());
                }

                inline bool operator==(const dynamic_array_const_iterator& other) const {
                    return curr_ptr_ == other.get_pointer();
                }

                inline std::strong_ordering operator<=>(const dynamic_array_const_iterator& other) const {
                    if(curr_ptr_ > other.get_pointer()) {
                        return std::strong_ordering::greater;
                    }
                    else if(curr_ptr_ < other.get_pointer()) {
                        return std::strong_ordering::less;
                    }
                    else {
                        return std::strong_ordering::equivalent;
                    }
                }

                inline pointer get_pointer() const {
                    return curr_ptr_;
                }
        };

        template<class T>
        class dynamic_array_reverse_iterator {
            public:
                using value_type = T;
                using pointer = T*;
                using reference = T&;
                using difference_type = unsigned long;
                using iterator_category = std::random_access_iterator_tag;
                using iter_traits = std::iterator_traits<dynamic_array_reverse_iterator<T>>;

            private:
                pointer base_ptr = nullptr;
            public:
                dynamic_array_reverse_iterator() = default;
                dynamic_array_reverse_iterator(pointer start_ptr): base_ptr(start_ptr) {};

                dynamic_array_reverse_iterator(const dynamic_array_reverse_iterator& other) : base_ptr(other.get_pointer()) {};
                dynamic_array_reverse_iterator(const dynamic_array_iterator<T>& other) : base_ptr(other) {};

                ~dynamic_array_reverse_iterator() = default;

                inline dynamic_array_reverse_iterator& operator++() {
                    --base_ptr;
                    return *this;
                }

                inline dynamic_array_reverse_iterator operator++(int) {
                    dynamic_array_reverse_iterator temp = *this;
                    --base_ptr;
                    return temp;
                }

                inline dynamic_array_reverse_iterator& operator--() {
                    ++base_ptr;
                    return *this;
                }

                inline dynamic_array_reverse_iterator operator--(int) {
                    dynamic_array_reverse_iterator temp = *this;
                    ++base_ptr;
                    return temp;
                }

                inline pointer operator[](const difference_type n) const {
                    return base_ptr - n;
                }

                inline reference operator*() const {
                    return *base_ptr;
                }

                inline pointer operator->() const {
                    return base_ptr;
                } 

                inline dynamic_array_reverse_iterator& operator+=(difference_type n) {
                    base_ptr -= n;
                    return *this;
                }

                inline dynamic_array_reverse_iterator& operator-=(difference_type n) {
                    base_ptr += n;
                    return *this;
                }

                inline difference_type operator-(dynamic_array_reverse_iterator& other) const {
                    return other.get_pointer() - base_ptr;
                }

                inline dynamic_array_reverse_iterator operator-(const difference_type n) const {
                    return dynamic_array_reverse_iterator(base_ptr + n);
                }

                inline dynamic_array_reverse_iterator operator+(const difference_type n) const {
                    return dynamic_array_reverse_iterator(base_ptr - n);
                }

                friend inline dynamic_array_reverse_iterator operator+(const difference_type n, const dynamic_array_reverse_iterator other) {
                    return dynamic_array_reverse_iterator(n - other.get_pointer());
                }

                friend inline dynamic_array_reverse_iterator operator-(const difference_type n, const dynamic_array_reverse_iterator other) {
                    return dynamic_array_reverse_iterator(n + other.get_pointer());
                }

                inline pointer get_pointer() const {
                    return base_ptr;
                }

                inline bool operator==(const dynamic_array_reverse_iterator& other) const {
                    return base_ptr == other.get_pointer();
                }

                inline std::strong_ordering operator<=>(const dynamic_array_reverse_iterator& other) const {
                    pointer other_pointer = other.get_pointer();
                    if(base_ptr > other_pointer) {
                        return std::strong_ordering::less;
                    }
                    else if(base_ptr < other_pointer) {
                        return std::strong_ordering::greater;
                    }
                    return std::strong_ordering::equivalent;
                }
        };

        template<class T>
        class dynamic_array_reverse_const_iterator {
            public:
                using value_type = const T;
                using pointer = T*;
                using reference = T&;
                using difference_type = unsigned long;
                using iterator_category = std::random_access_iterator_tag;
                using iter_traits = std::iterator_traits<dynamic_array_reverse_const_iterator<T>>;

            private:
                pointer base_ptr = nullptr;
            public:
                dynamic_array_reverse_const_iterator() = default;
                dynamic_array_reverse_const_iterator(pointer start_ptr): base_ptr(start_ptr) {};

                dynamic_array_reverse_const_iterator(const dynamic_array_reverse_const_iterator& other) : base_ptr(other.get_pointer()) {};
                dynamic_array_reverse_const_iterator(const dynamic_array_const_iterator<T>& other) : base_ptr(other) {};

                ~dynamic_array_reverse_const_iterator() = default;

                inline dynamic_array_reverse_const_iterator& operator++() {
                    --base_ptr;
                    return *this;
                }

                inline dynamic_array_reverse_const_iterator operator++(int) {
                    dynamic_array_reverse_const_iterator temp = *this;
                    --base_ptr;
                    return temp;
                }

                inline dynamic_array_reverse_const_iterator& operator--() {
                    ++base_ptr;
                    return *this;
                }

                inline dynamic_array_reverse_const_iterator operator--(int) {
                    dynamic_array_reverse_const_iterator temp = *this;
                    ++base_ptr;
                    return temp;
                }

                inline pointer operator[](const difference_type n) const {
                    return base_ptr - n;
                }

                inline reference operator*() const {
                    return *base_ptr;
                }

                inline pointer operator->() const {
                    return base_ptr;
                } 

                inline dynamic_array_reverse_const_iterator& operator+=(difference_type n) {
                    base_ptr -= n;
                    return *this;
                }

                inline dynamic_array_reverse_const_iterator& operator-=(difference_type n) {
                    base_ptr += n;
                    return *this;
                }

                inline difference_type operator-(dynamic_array_reverse_const_iterator& other) const {
                    return other.get_pointer() - base_ptr;
                }

                inline dynamic_array_reverse_const_iterator operator-(const difference_type n) const {
                    return dynamic_array_reverse_const_iterator(get_pointer() + n);
                }

                inline dynamic_array_reverse_const_iterator operator+(const difference_type n) const {
                    return dynamic_array_reverse_const_iterator(get_pointer() - n);
                }

                friend inline dynamic_array_reverse_const_iterator operator+(const difference_type n, const dynamic_array_reverse_const_iterator other) {
                    return dynamic_array_reverse_const_iterator(n - other.get_pointer());
                }

                friend inline dynamic_array_reverse_const_iterator operator-(const difference_type n, const dynamic_array_reverse_const_iterator other) {
                    return dynamic_array_reverse_const_iterator(n + other.get_pointer());
                }

                inline pointer get_pointer() const {
                    return base_ptr;
                }

                inline bool operator==(const dynamic_array_reverse_const_iterator& other) const {
                    return base_ptr == other.get_pointer();
                }

                inline std::strong_ordering operator<=>(const dynamic_array_reverse_const_iterator& other) const {
                    pointer other_pointer = other.get_pointer();
                    if(base_ptr > other_pointer) {
                        return std::strong_ordering::less;
                    }
                    else if(base_ptr < other_pointer) {
                        return std::strong_ordering::greater;
                    }
                    return std::strong_ordering::equivalent;
                }
        };


        template<class T, class Allocator = std::allocator<T>>
        class dynamic_array {
            public:
                using value_type = T;
                using reference = value_type&;
                using pointer = value_type*;
                using const_reference = const value_type&;
                using const_pointer = const value_type*;
                using size_type = unsigned long;
                using iterator = dynamic_array_iterator<T>;
                using const_iterator = dynamic_array_const_iterator<T>;
                using reverse_iterator = dynamic_array_reverse_iterator<T>;
                using const_reverse_iterator = dynamic_array_reverse_const_iterator<T>;
                using allocator_type = Allocator;

            private:
                size_type size_;
                size_type capacity_;
                pointer beg_;
                pointer end_;
                pointer end_of_storage_;
                Allocator alloc_;

                constexpr void check_range(size_type index) const {
                    if(index < 0 || index >= size_) {
                        throw std::out_of_range("Index is either less than 0 and greater than " + std::to_string(size_));
                    }
                }

                constexpr void check_size() {
                    if(size_ == 0) {
                        throw std::runtime_error("Dynamic array is empty. Cannot erase elements.");
                    }
                }

                void set_metadata(size_type n, size_type capacity, const Allocator& alloc) {
                    size_ = n;
                    capacity_ = capacity;
                    alloc_ = alloc;
                }

                size_type get_new_capacity(size_type threshold) const {
                    size_type new_capacity = 1;
                    while(new_capacity < threshold) {
                        new_capacity <<= 2;
                    }
                    return new_capacity;
                }

                void reassign_alloc(pointer new_array, size_type new_size, size_type new_capacity) {
                    destroy_range(begin(), end());
                    destroy_space(beg_, size_);
                    size_ = new_size;
                    beg_ = new_array;
                    end_ = new_array + new_size;
                    capacity_ = new_capacity;
                    end_of_storage_ = beg_ + capacity_;
                }

                void assign_range(iterator destination, iterator first, iterator last) {
                    for(; first != last; ++destination, ++first) {
                        *destination = *first;
                    }
                }

                void copy_range(iterator destination, iterator first, iterator last) {
                    for(; first != last; ++destination, ++first) {
                        std::allocator_traits<Allocator>::construct(alloc_, destination, *first);
                    }
                }

                void copy_range(iterator first, iterator last, value_type value) {
                    for(; first != last; ++first) {
                        std::allocator_traits<Allocator>::construct(alloc_, first, value);
                    }
                }

                void destroy_range(iterator first, iterator last) {
                    for(; first != last; ++first) {
                        std::allocator_traits<Allocator>::destroy(alloc_,  &(*first));
                    }
                }

                void destroy_space(pointer space_start, size_type space_size) {
                    std::allocator_traits<Allocator>::deallocate(alloc_, space_start, space_size);
                }

                pointer create_space(size_type space_size) {
                    return std::allocator_traits<Allocator>::allocate(alloc_, space_size);
                }

                void grow(size_type threshold) {
                    size_type new_capacity = get_new_capacity(threshold);
                    pointer new_array = nullptr;
                    size_type copied_values = 0;
                    try {  
                        new_array = std::allocator_traits<Allocator>::allocate(alloc_, new_capacity);
                        for(; copied_values < size_; ++copied_values) {
                            std::allocator_traits<Allocator>::construct(alloc_, new_array + copied_values, beg_[copied_values]);
                        }
                        destroy_range(begin(), end());
                        destroy_space(beg_, size_);
                        beg_ = new_array;
                        end_ = new_array+size_;
                        end_of_storage_ = new_array + new_capacity;
                        capacity_ = new_capacity;
                    }
                    catch(std::exception ex) {
                        for(; copied_values > 0; --copied_values) {
                            std::allocator_traits<Allocator>::destroy(alloc_, new_array + copied_values);
                        }
                        destroy_space(new_array, new_capacity);
                        throw ex;
                    }
                }

            public:

                explicit dynamic_array(const Allocator& alloc) : size_(0), capacity_(0), alloc_(alloc), 
                                                                 beg_(nullptr), end_(nullptr), end_of_storage_(nullptr) { }

                explicit dynamic_array(): dynamic_array(Allocator()) {}

                dynamic_array(size_type n, const T& val, const Allocator& alloc = Allocator()): dynamic_array(alloc) {
                    this->alloc_ = alloc;
                    size_type initialized_values = 0;
                    try {  
                        capacity_ = get_new_capacity(n);
                        beg_ = create_space(capacity_);
                        for(; initialized_values < capacity_; ++initialized_values) {
                            T value_to_copy;
                            if(initialized_values < n) {
                                value_to_copy = val;
                            }
                            else {
                                value_to_copy = value_type();
                            }
                            std::allocator_traits<Allocator>::construct(alloc_, beg_ + initialized_values, value_to_copy);
                        }
                        this->size_ = n;
                        this->end_ = beg_ + size_;
                        this->end_of_storage_ = beg_ + capacity_;
                    } catch(std::exception ex) {
                        for(; initialized_values > 0; --initialized_values) {
                            std::allocator_traits<Allocator>::destroy(alloc_, beg_ + initialized_values);
                        }
                        destroy_space(beg_, capacity_);
                        size_ = capacity_ = 0;
                        beg_ = end_ = end_of_storage_ = nullptr;
                        throw ex;
                    }
                }

                explicit dynamic_array(size_type n, const Allocator& alloc = Allocator()): dynamic_array(n, T(), alloc) {}

                constexpr dynamic_array(const dynamic_array& other, const Allocator& alloc): dynamic_array(alloc) {
                    size_type copied_values = 0;
                    try {
                        set_metadata(other.size(), other.capacity(), alloc);
                        beg_ = create_space(capacity_);
                        for(; copied_values < other.capacity(); ++copied_values) {
                            value_type value_to_copy;
                            if(copied_values < other.size()) {
                                value_to_copy = other[copied_values];
                            }
                            else {
                                value_to_copy = value_type();
                            }
                            std::allocator_traits<Allocator>::construct(alloc_, beg_ + copied_values, value_to_copy);
                        }
                        end_ = beg_ + size_;
                        end_of_storage_ = beg_+capacity_; 
                    }
                    catch(std::exception ex) {
                        for(; copied_values > 0; --copied_values) {
                            std::allocator_traits<Allocator>::destroy(alloc_, beg_ + copied_values);
                        }
                        destroy_space(beg_, other.capacity_);
                        size_ = capacity_ = 0;
                        beg_ = end_ = end_of_storage_ = nullptr;
                        throw ex;
                    }
                }

                dynamic_array(dynamic_array&& other, const Allocator& alloc) {
                    set_metadata(other.size_, other.capacity_, alloc);
                    beg_ = other.beg_;
                    end_ = other.end_;
                    end_of_storage_ = other.end_of_storage_;

                    other.beg_ = other.end_ = nullptr;
                    other.capacity_ = other.size_ = 0;
                }
                
                dynamic_array(const dynamic_array& other) : dynamic_array(other, Allocator()) {}

                template<class InputIt>
                dynamic_array(InputIt first, InputIt last, const Allocator& alloc = Allocator()) {
                    alloc_ = alloc;
                    size_type initialized_values = 0;
                    try {
                        size_ = std::distance(first, last);
                        capacity_ = get_new_capacity(size_);
                        beg_ = create_space(capacity_);
                        for(; initialized_values < capacity_; ++initialized_values) {
                            value_type value_to_copy;
                            if(initialized_values < size_) {
                                value_to_copy = *(first++);
                            }
                            else {
                                value_to_copy = value_type();
                            }
                            std::allocator_traits<Allocator>::construct(alloc_, beg_ + initialized_values, value_to_copy);
                        }
                        end_ = beg_ + size_;
                        end_of_storage_ = beg_ + capacity_;
                    }
                    catch(std::exception ex) {
                        for(; initialized_values > 0; --initialized_values) {
                            std::allocator_traits<Allocator>::destroy(alloc_, beg_ + initialized_values);
                        }
                        destroy_space(beg_, capacity_);
                        beg_ = end_ = end_of_storage_ = nullptr;
                        size_ = capacity_ = 0;
                        throw ex;
                    }
                    
                }

                dynamic_array(std::initializer_list<T> insert_list) : dynamic_array(insert_list.begin(), insert_list.end()) { }

                dynamic_array& operator=(const dynamic_array& other) {
                
                    if(this != &other) {
                        assign(other.cbegin(), other.cend());
                    }
                    return *this;
                }

                dynamic_array& operator=(dynamic_array&& other) noexcept {
                    if(this == &other) {
                        return *this;
                    }

                    clear();
                    swap(other);
                    return *this;
                }

                ~dynamic_array() {
                   clear();
                    destroy_space(beg_, capacity_);
                    set_metadata(0, 0, alloc_);
                    beg_ = end_ = end_of_storage_ = nullptr;
                }

                dynamic_array(dynamic_array&& other) : dynamic_array(other, other.alloc_) {}

                void clear() {
                    destroy_range(begin(), end());
                    size_ = 0;
                }

                [[nodiscard]] iterator begin() noexcept {
                    return dynamic_array_iterator<T>(beg_);
                }
                
                [[nodiscard]] iterator end() noexcept {
                    return dynamic_array_iterator<T>(end_);
                }

                [[nodiscard]] const_iterator cbegin() const noexcept {
                    return dynamic_array_const_iterator<T>(beg_);
                }

                [[nodiscard]] const_iterator cend() const noexcept {
                    return dynamic_array_const_iterator<T>(end_);
                }

                [[nodiscard]] reverse_iterator rbegin() noexcept {
                    return dynamic_array_reverse_iterator<T>(end_);
                }

                [[nodiscard]] reverse_iterator rend() noexcept {
                    return dynamic_array_reverse_iterator<T>(beg_-1);
                }

                [[nodiscard]] const_reverse_iterator crbegin() const noexcept {
                    return dynamic_array_reverse_const_iterator<T>(end_);
                }

                [[nodiscard]] const_reverse_iterator crend() const noexcept {
                    return dynamic_array_reverse_const_iterator<T>(beg_-1);
                }
                
                size_type size() const noexcept {
                    return size_;
                }

                size_type capacity() const noexcept {
                    return capacity_;
                }

                reference at(size_type index) {
                    check_range(index);
                    return beg_[index];
                }

                reference operator[](size_type index) {
                    return at(index);
                }

                const_reference at(size_type index) const {
                    check_range(index);
                    return const_cast<const_reference>(beg_[index]);
                }

                const_reference operator[](size_type index) const {
                    return at(index);
                }

                reference front() {
                    return at(0);
                }

                const_reference front() const {
                    return at(0);
                }

                reference back() {
                    return at(size_-1);
                }

                const_reference back() const {
                    return at(size_-1);
                }

                void resize(const size_type n) {
                    resize(n, value_type());
                }

                void resize(const size_type n, const value_type& fill_value) {
                    if(n > capacity_) {
                       grow(n);
                    }
                    if((n > size_ && n < capacity_)) {
                        size_type filled_values = 0;
                        size_type size_to_fill = n-size_;
                        try {
                            for(; filled_values < size_to_fill; ++filled_values) {
                                std::allocator_traits<Allocator>::construct(alloc_, beg_ + size_ + filled_values);
                            }
                            size_ = size_to_fill;
                        }
                        catch(std::exception ex) {
                            for(; filled_values > 0; --filled_values) {
                                std::allocator_traits<Allocator>::destroy(alloc_, beg_ + size_ + filled_values);
                            }
                            throw ex;
                        }
                    }
                    else if(n == size_) {
                        return;
                    }
                    else if(n < size_) {
                        destroy_range(begin()+n, end());
                    }
                    else if(n == 0) {
                        clear();
                    }
                }
                
                void reserve(size_type n) {
                    if(capacity_ < n) {
                        grow(n);
                    }
                }

                allocator_type get_allocator() const noexcept {
                    return alloc_;
                }

                void push_back(const value_type& val) {
                    reserve(size_+1);
                    std::allocator_traits<Allocator>::construct(alloc_, end_, val);
                    size_ += 1;
                    end_ = beg_ + size_;
                }

                void push_back(value_type&& val) {
                    push_back(val);
                    val = nullptr;
                }

                constexpr void pop_back() noexcept(std::is_nothrow_destructible_v<pointer>) {
                    if(size_ > 0) {
                        std::allocator_traits<Allocator>::destroy(alloc_, beg_ + (size_-1));
                        --size_;
                    }
                }

                iterator insert(const_iterator pos, const T& value) {
                    return insert(pos, 1, value);
                }

                iterator insert(const_iterator pos, T&& value) {
                    iterator return_iter = insert(pos, 1, std::move(value));
                    return return_iter;
                }

                iterator insert(const_iterator pos, size_type n, const T& value) {
                    const_iterator start_pos = cbegin();
                    size_type insert_index = pos-start_pos;
                    size_type new_size = size_ + n;
                    size_type copied_values = 0;
                    if(new_size >= capacity_) {
                        size_type new_capacity = get_new_capacity(new_size);
                        pointer new_array = nullptr;
                        try {
                            new_array = create_space(new_capacity);
                            for(; copied_values < new_capacity; ++copied_values) {
                                value_type value_to_copy;
                                if(copied_values < insert_index) {
                                    value_to_copy = beg_[copied_values];
                                } else if(copied_values >= insert_index && copied_values < insert_index+n){
                                    value_to_copy = value;
                                }
                                else if (copied_values >= insert_index+n && copied_values < new_size){
                                    value_to_copy = beg_[copied_values-n];
                                }
                                else {
                                    value_to_copy = value_type();
                                }
                                std::allocator_traits<Allocator>::construct(alloc_, new_array + copied_values, value_to_copy);
                            }

                            destroy_range(begin(), end());
                            destroy_space(beg_, capacity_);
                            capacity_ = new_capacity;
                            beg_ = new_array;
                            end_ = new_array + new_size;
                            end_of_storage_ = new_array + capacity_;
                        }
                        catch(std::exception ex) {
                            for(; copied_values > 0; --copied_values) {
                                std::allocator_traits<Allocator>::destroy(alloc_, new_array + copied_values);
                            }
                            destroy_space(new_array, new_size);
                            throw ex;
                        }
                        
                    }
                    else {
                        size_type i = size_ + n;
                        for(; i > insert_index+n; --i) {
                            beg_[i] = std::move(beg_[i-n]);
                        }
                        for(; i > insert_index; --i) {
                            std::allocator_traits<Allocator>::construct(alloc_, beg_ + i, value);
                        }
                    }

                    size_ = new_size;
                    return iterator(beg_+insert_index);
                }

                template<class InputIt>
                iterator insert(const_iterator pos, InputIt first, InputIt last) {
                    size_type input_size = 0;
                    const_iterator start_pos = cbegin();
                    size_type insert_index = pos-start_pos;
                    for(InputIt find_range = first; find_range != last; ++find_range, ++input_size);

                    size_type new_size = size_ + input_size;
                    if(new_size >= capacity_) {
                        size_type new_capacity = get_new_capacity(size_+input_size);
                        pointer new_array = nullptr;
                        size_type copied_values = 0;

                        try{
                            new_array = create_space(new_capacity);
                            for(; copied_values < new_capacity; ++copied_values) {
                                value_type value_to_copy;
                                if(copied_values < insert_index) {
                                    value_to_copy = beg_[copied_values];
                                }
                                else if (copied_values >= insert_index && copied_values < insert_index+input_size && first != last){
                                    value_to_copy = *(first++);
                                }
                                else if (copied_values >= insert_index+input_size && copied_values < new_size) {
                                    value_to_copy = beg_[copied_values-input_size];
                                }
                                else {
                                    value_to_copy = value_type();
                                }
                                std::allocator_traits<Allocator>::construct(alloc_, new_array + copied_values, value_to_copy);
                            }
                        }
                        catch(std::exception e) {
                            for(; copied_values > 0; --copied_values) {
                                std::allocator_traits<Allocator>::destroy(alloc_, new_array + copied_values);
                            }
                            destroy_space(new_array, new_capacity);
                            throw e;
                        }
                        destroy_range(begin(), end());
                        destroy_space(beg_, capacity_);
                        capacity_ = new_capacity;
                        beg_ = new_array;
                        end_ = new_array + new_size;
                        end_of_storage_ = new_array + capacity_;
                    }
                    else {
                        size_type i = size_ + input_size;
                        for(; i > insert_index + input_size; --i) {
                            beg_[i] = std::move(beg_[i-input_size]);
                        }
                        for(i = insert_index; i < insert_index+input_size && first != last; ++i) {
                            beg_[i] = *(first++);
                        }
                    }
                    
                    size_ = new_size;
                    return iterator(beg_ + insert_index + input_size);
                }

                iterator insert(const_iterator pos, std::initializer_list<T> insert_list) {
                    return insert(pos, insert_list.start(), insert_list.end());
                }

                iterator erase(iterator pos) {
                    return erase(pos, pos+1);
                }

                iterator erase(iterator start, iterator end) {
                    check_size();
                    iterator start_pos = begin();
                    size_type erase_start_index = start-start_pos;
                    size_type erase_range = end-start;
                    size_type new_size = size_-erase_range;
                    
                    destroy_range(start, end);
                    for(size_type i = erase_start_index; i < new_size; ++i) {
                        beg_[i] = std::move(beg_[i+erase_range]);
                    }
                    
                    size_ = new_size;
                    return iterator(beg_+erase_start_index-erase_range);
                }

                constexpr iterator erase(const_iterator pos) {
                    return erase(pos, pos+1);
                }

                constexpr iterator erase(const_iterator start, const_iterator end) {
                    check_size();
                    const_iterator start_pos = cbegin();
                    size_type erase_start_index = start-start_pos;
                    size_type erase_range = end-start;
                    size_type new_size = size_-erase_range;
                    
                    for(; start != end; ++start) {
                        std::allocator_traits<Allocator>::destroy(alloc_, &(*start));
                    }
                    for(size_type i = erase_start_index; i < new_size; ++i) {
                        beg_[i] = std::move(beg_[i+erase_range]);
                    }

                    size_ = new_size;
                    return iterator(beg_+erase_start_index-erase_range);
                }

                template<class... Args>
                void emplace_back(Args&&... args) {
                    try {
                        reserve(size_+1);
                        std::allocator_traits<Allocator>::construct(alloc_, beg_+size_, std::forward<Args>(args)...);
                        size_++;
                        end_ = beg_ + size_;
                    } catch(std::exception e) {
                        throw e;
                    }
                }

                template<class... Args>
                iterator emplace(const_iterator pos, Args&&... args) {
                    const_iterator start = cbegin();
                    size_type insert_index = pos-start;
                    if(size_+1 > capacity_) {
                        pointer new_array = nullptr;
                        size_type new_capacity = get_new_capacity(size_+1);
                        size_type copied_values = 0;
                        try {
                            new_array = create_space(new_capacity);
                            for(; copied_values < size_ + 1; ++copied_values) {
                                value_type value_to_copy;
                                if(copied_values < insert_index) {
                                    value_to_copy = beg_[copied_values];
                                }
                                else if(copied_values > insert_index && copied_values < insert_index + 1) {
                                    value_to_copy = value_type(std::forward<Args>(args)...);
                                }
                                else {
                                    value_to_copy = beg_[copied_values-1];
                                }
                                std::allocator_traits<Allocator>::construct(alloc_, new_array + copied_values, value_to_copy);
                            }
                            destroy_range(begin(), end());
                            destroy_space(beg_, capacity_);
                            capacity_ = new_capacity;
                            beg_ = new_array;
                            end_ = new_array + size_;
                            end_of_storage_ = new_array + capacity_;
                        }
                        catch(std::exception ex) {
                            for(; copied_values > 0; --copied_values) {
                                std::allocator_traits<Allocator>::destroy(alloc_, new_array + copied_values);
                            }
                            destroy_space(new_array, new_capacity);
                            throw ex;
                        }
                    }
                    else {
                        for(size_type i = size_; i > insert_index; --i) {
                            beg_[i] = beg_[i-1];
                        }
                        std::allocator_traits<Allocator>::construct(alloc_, beg_ + insert_index, std::forward<Args>(args)...);
                    }
                    size_++;
                    return iterator(beg_+insert_index+1);
                }

            constexpr void assign(size_type count, const T& value) {
                size_type copied_values = 0;
                if(count > capacity_) {
                    pointer new_array = nullptr;
                    size_type new_capacity = get_new_capacity(count);
                    try {
                        new_array = create_space(new_capacity);
                        for(; copied_values < count; ++copied_values) {
                            std::allocator_traits<Allocator>::construct(alloc_, new_array+copied_values, value);
                        }
                       
                    } catch(std::exception ex) {
                        for(; copied_values > 0; --copied_values) {
                            std::allocator_traits<Allocator>::destroy(alloc_, new_array+copied_values);
                        }
                        destroy_space(new_array, new_capacity);
                        throw ex;
                    }
                    destroy_range(begin(), end());
                    destroy_space(beg_, capacity_);
                    capacity_ = new_capacity;
                    size_ = count;
                    beg_ = new_array;
                    end_ = beg_ + size_;
                    end_of_storage_ = beg_ + capacity_;
                }
                else {
                    try {
                        for(; (copied_values < count) && (copied_values < size_); ++copied_values) {
                            *(beg_ + copied_values) = value;
                        }
                        for(; copied_values < count; ++copied_values) {
                            std::allocator_traits<Allocator>::construct(alloc_, beg_ + copied_values, value);
                        }
                        for(size_type index = size_; index > count; --index) {
                            std::allocator_traits<Allocator>::destroy(alloc_, beg_ + index);
                        }
                    }
                    catch(std::exception ex) {
                        for(; copied_values > 0; --copied_values) {
                            std::allocator_traits<Allocator>::destroy(alloc_, beg_ + (copied_values-1));
                        }
                        throw ex;
                    }

                    size_ = count;
                }
            }

            template<class InputIt>
            constexpr void assign(InputIt start, InputIt last) {
                size_type insert_size = std::distance(start, last);
                size_type copied_values = 0;

                if(insert_size > capacity_) {
                    pointer new_array = nullptr;
                    size_type new_capacity = get_new_capacity(insert_size);
                    try {
                        new_array = create_space(new_capacity);
                        for(;copied_values < insert_size && start != last; ++copied_values) {
                            std::allocator_traits<Allocator>::construct(alloc_, new_array+copied_values, *(start++));
                        }
                        destroy_range(begin(), end());
                        destroy_space(beg_, capacity_);
                        size_ = insert_size;
                        capacity_ = new_capacity;
                        beg_ = new_array;
                        end_ = beg_ + size_;
                        end_of_storage_ = beg_ + capacity_;

                    } catch(std::exception ex) {
                        for(; copied_values > 0; ++copied_values) {
                            std::allocator_traits<Allocator>::destroy(alloc_, new_array + copied_values);
                        }
                        destroy_space(new_array, new_capacity);
                        throw ex;
                    }
                }
                else {
                    try {
                        for(; (copied_values < size_) && (copied_values < insert_size); ++copied_values) {
                        *(beg_ + copied_values) = *(start++);
                        }
                        for(; (copied_values < insert_size) && (start != last); ++copied_values) {
                            std::allocator_traits<Allocator>::construct(alloc_, beg_+copied_values, *(start++));
                        }
                        for(size_type index = size_; index > insert_size; --index) {
                            std::allocator_traits<Allocator>::destroy(alloc_, beg_ + copied_values);
                        }
                        size_ = insert_size;
                    }
                    catch(std::exception ex) {
                        for(; copied_values > 0; --copied_values) {
                            std::allocator_traits<Allocator>::destroy(alloc_, beg_ + copied_values-1);
                        }
                        throw ex;
                    }
                }
            }

            constexpr void assign(std::initializer_list<T> init_list) {
                assign(init_list.begin(), init_list.end());
            }

            void swap(dynamic_array& other) noexcept(std::is_nothrow_swappable_v<pointer>) {
                if(this == &other) {
                    return;
                }

                pointer begin_temp = other.beg_;
                pointer end_temp = other.end_;
                pointer end_of_storage_temp = other.end_of_storage_;
                size_type size_temp = other.size_;
                size_type cap_temp = other.capacity_;
            
                other.beg_ = beg_;
                other.end_ = end_;
                other.end_of_storage_ = end_of_storage_;
                other.size_ = size_;
                other.capacity_ = capacity_;

                beg_ = begin_temp;
                end_ = end_temp;
                end_of_storage_ = end_of_storage_temp; 
                size_ = size_temp;
                capacity_ = cap_temp;
            }   

            constexpr bool operator==(const dynamic_array& other) {
                if(size_ != other.size()) {
                    return false;
                }
                for(size_type index = 0; index < size_; ++index) {
                    bool compare_result = beg_[index] == other[index];
                    if(compare_result == false) {
                        return false;
                    }
                }
                return true;
            }

            constexpr std::weak_ordering operator<=>(const dynamic_array& other) {
                if(size_ > other.size()) {
                    return std::weak_ordering::greater;
                }
                else if(size_ < other.size()) {
                    return std::weak_ordering::less;
                }
                for(size_type index = 0; index < size_; ++index) {
                    if((beg_[index] > other[index]) == true) {
                        return std::weak_ordering::greater;
                    }
                    else if((beg_[index] < other[index]) == true) {
                        return std::weak_ordering::less;
                    }
                }
                return std::weak_ordering::equivalent;
            }
        };
    }
}
