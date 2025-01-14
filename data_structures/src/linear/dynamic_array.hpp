
#include <cstddef>
#include <initializer_list>
#include <iterator>
#include <memory>
#include <string>
#include <stdexcept>

namespace data_structures {
    namespace linear {

        template<class T>
        class dynamic_array_iterator {        
            public:       
                using value_type = T;
                using reference = value_type&;
                using pointer = value_type*;
                using difference_type = std::ptrdiff_t;
                using iterator_category = std::random_access_iterator_tag;
                using iter_traits = std::iterator_traits<dynamic_array_iterator<T>>;

             private:
                pointer curr_ptr_;
             public:
                dynamic_array_iterator(): curr_ptr_(nullptr) {};
                dynamic_array_iterator(pointer start_ptr) : curr_ptr_(start_ptr) {};
                dynamic_array_iterator(const dynamic_array_iterator& other) : curr_ptr_(other.curr_ptr_) {};
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
                    return &(curr_ptr_ + n);
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
                    return curr_ptr_ - other.curr_ptr_;
                }

                inline dynamic_array_iterator operator-(const difference_type n) const {
                    return dynamic_array_iterator(curr_ptr_ - n);
                }

                inline dynamic_array_iterator operator+(const difference_type n) const {
                    return dynamic_array_iterator(curr_ptr_ + n);
                }

                friend inline dynamic_array_iterator operator+(const difference_type n, const dynamic_array_iterator other) {
                    return dynamic_array_iterator(n + other.curr_ptr_);
                }

                friend inline dynamic_array_iterator operator-(const difference_type n, const dynamic_array_iterator other) {
                    return dynamic_array_iterator(n - other.curr_ptr_);
                }

                inline bool operator==(const dynamic_array_iterator& other) const {
                    return curr_ptr_ = other.curr_ptr_;
                }

                inline bool operator!=(const dynamic_array_iterator& other) const  {
                    return curr_ptr_ != other.curr_ptr_;
                }

                inline bool operator>(const dynamic_array_iterator& other) const  {
                    return curr_ptr_ > other.curr_ptr_;
                }

                inline bool operator<(const dynamic_array_iterator& other) const  {
                    return curr_ptr_ < other.curr_ptr_;
                }

                inline bool operator>=(const dynamic_array_iterator& other)const {
                    return curr_ptr_ >= other.curr_ptr_;
                }

                inline bool operator<=(const dynamic_array_iterator& other) const {
                    return curr_ptr_ <= other.curr_ptr_;
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
                using difference_type = std::ptrdiff_t;
                using iterator_category = std::random_access_iterator_tag;

             private:
                pointer curr_ptr_;
            public:
                dynamic_array_const_iterator(): curr_ptr_(nullptr) {};
                dynamic_array_const_iterator(pointer start_ptr) : curr_ptr_(start_ptr) {};
                dynamic_array_const_iterator(const dynamic_array_const_iterator& other) : curr_ptr_(other.curr_ptr_) {};
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
                    return &(curr_ptr_ + n);
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
                    return curr_ptr_ - other.curr_ptr_;
                }

                inline dynamic_array_const_iterator operator-(const difference_type n) const {
                    return dynamic_array_const_iterator(curr_ptr_ - n);
                }

                inline dynamic_array_const_iterator operator+(const difference_type n) const {
                    return dynamic_array_const_iterator(curr_ptr_ + n);
                }

                friend inline dynamic_array_const_iterator operator+(const difference_type n, const dynamic_array_const_iterator other) {
                    return dynamic_array_const_iterator(n + other.curr_ptr_);
                }

                friend inline dynamic_array_const_iterator operator-(const difference_type n, const dynamic_array_const_iterator other) {
                    return dynamic_array_const_iterator(n - other.curr_ptr_);
                }

                inline bool operator==(const dynamic_array_const_iterator& other) const {
                    return curr_ptr_ == other.curr_ptr_;
                }

                inline bool operator!=(const dynamic_array_const_iterator& other) const {
                    return curr_ptr_ != other.curr_ptr_;
                }

                inline bool operator>(const dynamic_array_const_iterator& other) const {
                    return curr_ptr_ > other.curr_ptr_;
                }

                inline bool operator<(const dynamic_array_const_iterator& other) const {
                    return curr_ptr_ < other.curr_ptr_;
                }

                inline bool operator>=(const dynamic_array_const_iterator& other) const {
                    return curr_ptr_ >= other.curr_ptr_;
                }

                inline bool operator<=(const dynamic_array_const_iterator& other) const {
                    return curr_ptr_ <= other.curr_ptr_;
                }

                inline pointer get_pointer() const {
                    return curr_ptr_;
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
                using allocator_type = std::allocator<T>;

            private:
                size_type size_;
                size_type capacity_;
                pointer beg_;
                pointer end_;
                pointer end_of_storage_;
                Allocator alloc_;

                void check_range(size_type index) const {
                    if(index < 0 || index >= size_) {
                        throw std::out_of_range("Index is either less than 0 and greater than " + std::to_string(size_));
                    }
                }

                void set_metadata(size_type n, size_type capacity, const Allocator& alloc) {
                    size_ = n;
                    capacity_ = capacity;
                    alloc_ = alloc;
                }

                size_type get_new_capacity(size_type threshold) const {
                    size_type new_capacity = capacity_;
                    while(new_capacity < threshold) {
                        new_capacity <<= 2;
                    }
                    return new_capacity;
                }

                void reassign_alloc(pointer new_array, size_type new_size, size_type new_capacity) {
                    alloc_.deallocate(beg_, size_);
                    size_ = new_size;
                    beg_ = new_array;
                    end_ = new_array + new_size;
                    capacity_ = new_capacity;
                    end_of_storage_ = beg_ + capacity_;
                }

            public:

                explicit dynamic_array(const Allocator& alloc) {
                    set_metadata(0, 0, alloc);
                    beg_ = end_ = end_of_storage_ = nullptr;
                }

                explicit dynamic_array() : dynamic_array(Allocator()) {}

                explicit dynamic_array(size_type n, const Allocator& alloc = Allocator()) {
                    set_metadata(0, n, alloc);
                    beg_ = alloc_.allocate(n);
                    end_ = beg_+n;
                    end_of_storage_ = end_;
                }

                explicit dynamic_array(size_type n, const value_type& val, const Allocator& alloc = Allocator()) : dynamic_array(n, alloc) {
                    size_ = n;
                    for(int i = 0; i < n; i++) {
                        beg_[i] = val;
                    }
                }

                constexpr dynamic_array(const dynamic_array& other, const Allocator& alloc) {
                    set_metadata(other.size_, other.capacity_, alloc);
                    beg_ = alloc_.allocate(size_);
                    for(int i = 0; i < size_; i++) {
                        beg_[i] = other[i];
                    }
                    end_ = beg_ + size_;
                    end_of_storage_ = end_; 
                }

                
                dynamic_array(const dynamic_array& other) : dynamic_array(other, Allocator()) {}

                dynamic_array(dynamic_array&& other, const Allocator& alloc) {
                    set_metadata(other.size_, other.capacity_, alloc);
                    beg_ = other.beg_;
                    end_ = other.end_;
                    end_of_storage_ = other.end_of_storage_;

                    other.beg_ = other.end_ = nullptr;
                    other.capacity_ = other.size_ = 0;
                }

                dynamic_array(dynamic_array&& other) : dynamic_array(other, other.alloc_) {}

                iterator begin() {
                    return dynamic_array_iterator<T>(beg_);
                }
                
                iterator end() {
                    return dynamic_array_iterator<T>(end_);
                }

                const_iterator cbegin() {
                    return dynamic_array_const_iterator<T>(beg_);
                }

                const_iterator cend() {
                    return dynamic_array_const_iterator<T>(end_);
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

                void resize(size_type n) {
                    if(n != capacity_) {
                        capacity_ = n;
                        pointer new_beg = alloc_.allocate(capacity_);
                        for(int i = 0; i < n && i < size_; i++) {
                            new_beg[i] = beg_[i];
                        }

                        if(beg_ != nullptr) {
                            alloc_.deallocate(beg_, size_);
                        }
                            
                        beg_ = new_beg;
                        end_ = new_beg + size_;
                        end_of_storage_ = beg_ + capacity_;
                    }
                }
                
                void reserve(size_type n) {
                    if(capacity_ < n) {
                        int new_capacity = capacity_ == 0 ? 1 : capacity_;
                        while(new_capacity <= n) {
                            new_capacity <<= 1;
                        }
                        resize(new_capacity);
                    }
                }

                allocator_type get_allocator() const noexcept {
                    return alloc_;
                }

                void push_back(const value_type& val) {
                    reserve(size_+1);
                    beg_[size_] = val;
                    size_ += 1;
                    end_ = beg_ + size_;
                }

                void push_back(value_type&& val) {
                    push_back(val);
                    val = nullptr;
                }

                iterator insert(const_iterator pos, const T& value) {
                    return insert(pos, 1, value);
                }

                iterator insert(const_iterator pos, T&& value) {
                    iterator return_it = insert(pos, value);
                    value = nullptr;
                    return return_it;
                }

                iterator insert(const_iterator pos, size_type n, const T& value) {
                    size_type insert_index = abs(cbegin() - pos);
                    size_type new_size = size_ + n;
                    if(new_size > capacity_) {
                        size_type new_capacity = get_new_capacity(new_size);
                        pointer new_array = alloc_.allocate(new_capacity);
                    
                        for(size_type i = 0; i < size_ + n; ++i) {
                            if(i < insert_index) {
                                new_array[i] = beg_[i];
                            }
                            else if(i >= insert_index && i < insert_index + n) {
                                new_array[i] = value;
                            } else {
                                new_array[i] = beg_[i-n];
                            }
                        }

                        reassign_alloc(new_array, new_size, new_capacity);
                    }
                    else {
                        for(size_type i = size_+n; i >= insert_index; --i) {
                            beg_[i] = i < insert_index+n ? value : beg_[i - n];
                        }
                        size_ = new_size;
                    }
                   
                    return iterator(beg_+insert_index+n);
                }

                template<class InputIt>
                iterator insert(const_iterator pos, InputIt first, InputIt last) {
                    size_type input_size = 0;
                    size_type insert_index = std::abs(cbegin() - pos);
                    for(InputIt find_range = first; find_range != last; ++find_range, ++input_size);

                    size_type new_size = size_ + input_size;
                    if(new_size >= capacity_) {
                        size_type new_capacity = get_new_capacity(size_+input_size);
                        pointer new_array = alloc_.allocate(new_capacity);
                        for(unsigned int i = 0; i < new_size; ++i) {
                            if(i < insert_index) {
                                new_array[i] = beg_[i];
                            }
                            else if(i >= insert_index && i < insert_index + input_size && first != last) {
                                new_array[i] = *first;
                                ++first;
                            }
                            else {
                                new_array[i] = beg_[i-input_size];
                            }
                        }

                        reassign_alloc(new_array, new_size, new_capacity);
                    }
                    else {
                       for(unsigned int i = new_size; i > insert_index; --i) {
                            if(i >= insert_index + input_size) {
                                beg_[i] = beg_[i - input_size];
                            }
                            else if( i < insert_index + input_size && last != first) {
                                beg_[i] = *last;
                                --last;
                            }
                       } 
                    }

                    return iterator(beg_ + insert_index + input_size);
                }

                iterator insert(const_iterator pos, std::initializer_list<T> insert_list) {
                    return insert(pos, insert_list.start(), insert_list.end());
                }
        };
    }
}
