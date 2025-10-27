#include "gtest/gtest.h"
#include <compare>
#include <cstdlib>
#include <iterator>
#include <pthread.h>
#include <random>
#include <stdexcept>
#include <vector>

#include "data_structures/src/linear/dynamic_array.hpp"

using data_structures::linear::dynamic_array;


enum class constructor_type {
    EMPTY,
    STATIC_SIZE,
    MULTIPLE_VALUE,
    OTHER_ARRAY_COPY,
    OTHER_ARRAY_MOVE,
    ITERATOR,
    ASSIGNMENT,
};

enum class iterator_type {
    FORWARD,
    BACKWARD,
    CONST_FORWARD,
    CONST_BACKWARD,
};

class dynamic_array_test_params {
    public:
        constructor_type test_type;
        unsigned int num_elements;
};

std::array<constructor_type, 7> constructor_list = {constructor_type::EMPTY, 
                                                    constructor_type::STATIC_SIZE, 
                                                    constructor_type::MULTIPLE_VALUE,
                                                    constructor_type::OTHER_ARRAY_COPY,
                                                    constructor_type::OTHER_ARRAY_MOVE,
                                                    constructor_type::ITERATOR,
                                                    constructor_type::ASSIGNMENT,};

std::array<iterator_type, 4> iter_type_list = {
    iterator_type::FORWARD,
    iterator_type::BACKWARD,
    iterator_type::CONST_FORWARD,
    iterator_type::CONST_BACKWARD,
};

template<class T>
std::pair<dynamic_array<T>, std::vector<T>> insert_n_elements(dynamic_array<T> test_arr, std::vector<T> test_vec, T insert_value, unsigned int num_elements) {
    for(unsigned int i = 0; i < num_elements; ++i) {
        test_arr.push_back(insert_value);
        test_vec.push_back(insert_value);
    }
    return std::pair<dynamic_array<T>, std::vector<T>>(test_arr, test_vec);
}

template<class T>
class dynamic_array_tests: public ::testing::Test {
    public:
        std::vector<T> test_vec;
        dynamic_array<T> test_arr;
    
    void run_equality_tests() {
        this->run_equality_tests(this->test_arr, this->test_vec);
    }

    void run_equality_tests(dynamic_array<T> test_array, std::vector<T> test_vector) {
        EXPECT_EQ(test_array.size(), test_vector.size());
        for(unsigned int i = 0; i < test_array.size(); ++i) {
            EXPECT_EQ(test_array[i], test_vector[i]);
            EXPECT_EQ(test_array.at(i), test_vector.at(i));
        }
    }

    void pushback_n_items(unsigned int n_elements, T insert_value) {
        for(unsigned int i = 0; i < n_elements; ++i) {
            test_arr.push_back(insert_value);
            test_vec.push_back(insert_value);
        }
    }
    
    void run_pushback_tests(int number_of_elements) {
        T insert_value = T();
        for(unsigned int i = 0; i < number_of_elements; ++i) {
            pushback_n_items(number_of_elements, insert_value);
            run_equality_tests();
            test_vec.clear();
            test_arr.clear();
        }
    }

    void run_construct_tests(int test_size) {
        for(constructor_type test_init_type: constructor_list) {
            this->construct_test_lists(test_init_type, test_size);
            this->run_equality_tests();
            test_arr.clear();
            test_vec.clear();
        }
        
    }

    void insert_tests(int test_size, T test_value, int num_insertions = 1, bool move_value = false) {
        
        for(int i = 0; i < test_size; ++i) {
            dynamic_array<T> insert_arr = test_arr;
            std::vector<T> insert_vec = test_vec;
            typename dynamic_array<T>::const_iterator insert_arr_iter;
            typename std::vector<T>::const_iterator insert_vec_iter;
            insert_arr_iter = insert_arr.cbegin();
            insert_vec_iter = insert_vec.cbegin();
            insert_arr_iter += i;
            insert_vec_iter += i;

            if(move_value) {
                insert_arr.insert(insert_arr_iter, std::move(test_value));
                insert_vec.insert(insert_vec_iter, std::move(test_value));
                //EXPECT_EQ(test_value, nullptr);
            }
            else {
                insert_arr.insert(insert_arr_iter, num_insertions, test_value);
                insert_vec.insert(insert_vec_iter, num_insertions, test_value);
            }
            
            run_equality_tests(insert_arr, insert_vec);
        }
    }

     void run_single_insertion_tests(int test_size, bool move_value = false) {
        T test_value = T();
        for(constructor_type test_init_type: constructor_list) {
            this->construct_test_lists(test_init_type, test_size);
            this->insert_tests(test_size, test_value, 1, move_value);
        }
        
    }

    void run_multiple_insertion_tests(int test_size) {
        T test_value = T();
        for(constructor_type test_init_type: constructor_list) {
            this->construct_test_lists(test_init_type, test_size);
            for(int i = 0; i < test_size; ++i) {
                this->insert_tests(test_size, test_value, i);
            }
        }
    }

    void run_insertion_iterator_tests(int test_size) {
        for(constructor_type test_init_type: constructor_list) {
            this->construct_test_lists(test_init_type, test_size);
            for(unsigned int i = 0; i < test_size; ++i) {
                dynamic_array<T> insert_iter_arr = this->test_arr;
                std::vector<T> insert_iter_vec = this->test_vec;

                dynamic_array<T> insert_copy_arr = this->test_arr;
                typename dynamic_array<T>::iterator insert_copy_arr_start = insert_copy_arr.begin();
                typename dynamic_array<T>::iterator insert_copy_arr_end = insert_copy_arr.end();

                typename dynamic_array<T>::const_iterator insert_iter_arr_start = insert_iter_arr.cbegin();
                typename std::vector<T>::const_iterator insert_iter_vec_start = insert_iter_vec.cbegin();

                insert_iter_arr_start += i;
                insert_iter_vec_start += i;

                insert_iter_arr.insert(insert_iter_arr_start, insert_copy_arr_start, insert_copy_arr_end);
                insert_iter_vec.insert(insert_iter_vec_start, insert_copy_arr_start, insert_copy_arr_end);
                this->run_equality_tests(insert_iter_arr, insert_iter_vec);
            }
            this->test_arr.clear();
            this->test_vec.clear();
        }
    }

    void run_replacement_insertion_tests(int test_size) {
        this->run_single_insertion_tests(test_size, true);
    }

    template<class... Args>
    void run_emplace_back_tests(int test_size, Args&&... insert_args) {
        for(constructor_type test_init_type: constructor_list) {
            this->construct_test_lists(test_init_type, test_size);
            test_vec.emplace_back(insert_args...);
            test_arr.emplace_back(insert_args...);
            run_equality_tests();
            test_vec.clear();
            test_arr.clear();
        }
    }

    template<class... Args>
    void run_emplace_tests(int test_size, Args&&... test_args) {
        for(constructor_type test_init_type: constructor_list) {
            this->construct_test_lists(test_init_type, test_size);
            for(unsigned int i = 0; i < test_size; ++i) {
                dynamic_array<T> emplace_arr = this->test_arr;
                std::vector<T> emplace_vec = this->test_vec;
                typename dynamic_array<T>::const_iterator emplace_arr_iter = emplace_arr.cbegin();
                typename std::vector<T>::const_iterator emplace_vec_iter = emplace_vec.cbegin();
                emplace_arr_iter += i;
                emplace_vec_iter += i;
                emplace_arr.emplace(emplace_arr_iter, test_args...);
                emplace_vec.emplace(emplace_vec_iter, test_args...);
                run_equality_tests(emplace_arr, emplace_vec);
            }
            test_arr.clear();
            test_vec.clear();
        }
    }

    void run_single_erasure_tests(int test_size) {
        for(constructor_type test_init_type: constructor_list) {
            this->construct_test_lists(test_init_type, test_size);
            for(unsigned int i = 0; i < test_size; ++i) {
                dynamic_array<T> erase_arr = this->test_arr;
                std::vector<T> erase_vec = this->test_vec;

                typename dynamic_array<T>::const_iterator erase_arr_iter = erase_arr.cbegin();
                typename std::vector<T>::const_iterator erase_vec_iter = erase_vec.cbegin();

                erase_arr_iter += i;
                erase_vec_iter += i;

                erase_arr.erase(erase_arr_iter);
                erase_vec.erase(erase_vec_iter);

                this->run_equality_tests(erase_arr, erase_vec);
            }
            this->test_arr.clear();
            this->test_vec.clear();
        }
    }

    void run_multiple_erasure_tests(int test_size) {
        for(constructor_type test_init_type: constructor_list) {
            this->construct_test_lists(test_init_type, test_size);
            for(unsigned int i = 0; i < test_size; ++i) {
                for(unsigned int j = i+1; j < test_size; ++j) {
                    dynamic_array<T> erase_arr = this->test_arr;
                    std::vector<T> erase_vec = this->test_vec;

                    typename dynamic_array<T>::const_iterator erase_arr_beg = erase_arr.cbegin();
                    typename std::vector<T>::const_iterator erase_vec_beg = erase_vec.cbegin();

                    typename dynamic_array<T>::const_iterator erase_arr_end = erase_arr_beg;
                    typename std::vector<T>::const_iterator erase_vec_end = erase_vec_beg;

                    erase_arr_beg += i;
                    erase_vec_beg += i;

                    erase_arr_end += j;
                    erase_vec_end += j;

                    erase_arr.erase(erase_arr_beg, erase_arr_end);
                    erase_vec.erase(erase_vec_beg, erase_vec_end);
                    this->run_equality_tests(erase_arr, erase_vec);
                } 
            }
            this->test_arr.clear();
            this->test_vec.clear();
        }
    }

    void construct_test_lists(constructor_type construct_initializer, int test_size) {

        T insert_value = T();
        dynamic_array<T> copy_array = dynamic_array<T>();

        for(unsigned int i = 0; i < test_size; ++i) {
            copy_array.push_back(insert_value);
        }

        switch(construct_initializer) {
            
            case constructor_type::EMPTY:
                
                pushback_n_items(test_size, insert_value);
                break;
            case constructor_type::STATIC_SIZE:
                test_arr = dynamic_array<T>(test_size);
                test_vec = std::vector<T>(test_size);

                pushback_n_items(test_size, insert_value);

                break;
            case constructor_type::MULTIPLE_VALUE:

                test_arr = dynamic_array<T>(test_size, insert_value);
                test_vec = std::vector<T>(test_size, insert_value);
                break;

            case constructor_type::OTHER_ARRAY_COPY:
                test_arr = dynamic_array<T>(copy_array);
                test_vec = std::vector<T>(copy_array.begin(), copy_array.end());
                break;

            case constructor_type::OTHER_ARRAY_MOVE:
                test_vec = std::vector<T>(copy_array.begin(), copy_array.end());
                test_arr = dynamic_array<T>(std::move(copy_array));
                break;

            case constructor_type::ITERATOR:
                test_arr = dynamic_array<T>(copy_array.begin(), copy_array.end());
                test_vec = std::vector<T>(copy_array.begin(), copy_array.end());
                break;

            case constructor_type::ASSIGNMENT:
                test_arr = copy_array;
                test_vec = std::vector<T>(copy_array.begin(), copy_array.end());
                break;
            
            default:
                break;
        }
        copy_array.clear();
    }

    template<class Arr_Iter, class Vec_Iter>
    void run_forward_backward_tests(Arr_Iter test_arr_iterator, Vec_Iter test_vec_iterator, int test_size, iterator_type iter_type) {
          Arr_Iter test_arr_pre_iter = test_arr_iterator;
        Vec_Iter test_vec_pre_iter = test_vec_iterator;
       
        for(unsigned int i = 0; i < test_size; ++i) {
            switch(iter_type) {
                case iterator_type::FORWARD:
                case iterator_type::CONST_FORWARD:
                    EXPECT_EQ(*test_arr_pre_iter, *test_vec_pre_iter);
                    ++test_arr_pre_iter, ++test_vec_pre_iter;
                    break;
                case iterator_type::BACKWARD:
                case iterator_type::CONST_BACKWARD:
                    --test_arr_pre_iter, --test_vec_pre_iter;
                    EXPECT_EQ(*test_arr_pre_iter, *test_vec_pre_iter);
                    break;
                default:
                    break;
            }
        }

        Arr_Iter test_arr_post_iter = test_arr_iterator;
        Vec_Iter test_vec_post_iter = test_vec_iterator;

        test_arr_pre_iter = test_arr_iterator;
        test_vec_post_iter = test_vec_iterator;

        for(unsigned int i = 0; i < test_size; ++i) {
            switch(iter_type) {
                case iterator_type::FORWARD:
                case iterator_type::CONST_FORWARD:
                    test_arr_pre_iter = test_arr_post_iter++;
                    test_vec_pre_iter = test_vec_post_iter++;

                    EXPECT_EQ(test_arr_post_iter-test_arr_pre_iter, 1);
                    EXPECT_EQ(test_vec_post_iter-test_vec_pre_iter, 1);

                    if(i < test_size-1) {
                        EXPECT_EQ(*test_arr_post_iter, *test_vec_post_iter);
                        EXPECT_EQ(*test_arr_pre_iter, *test_vec_pre_iter);
                    }
                    
                    break;
                case iterator_type::BACKWARD:
                case iterator_type::CONST_BACKWARD:
                    test_arr_pre_iter = test_arr_post_iter--;
                    test_vec_pre_iter = test_vec_post_iter--;
                    
                    EXPECT_EQ(test_arr_post_iter-test_arr_pre_iter, -1);
                    EXPECT_EQ(test_vec_post_iter-test_vec_pre_iter, -1);

                    if(i > 0) {
                        EXPECT_EQ(*test_arr_post_iter, *test_vec_post_iter);
                        EXPECT_EQ(*test_arr_pre_iter, *test_vec_pre_iter);
                    }
                    break;
                default:
                    break;
            }
        }
    }

    template<class Arr_Iter, class Vec_Iter>
    void run_iterator_index_tests(Arr_Iter test_arr_iterator, Vec_Iter test_vec_iterator, int test_size, iterator_type iter_type) {
        Arr_Iter test_index_arr_iterator;
        Vec_Iter test_index_vec_iterator;

        Arr_Iter test_arr_iterator_without_assignment;
        Vec_Iter test_vec_iterator_without_assignment;

        for(unsigned int i = 0; i < test_size; ++i) {
            test_index_arr_iterator = test_arr_iterator;
            test_index_vec_iterator = test_vec_iterator;

            test_arr_iterator_without_assignment = test_arr_iterator;
            test_vec_iterator_without_assignment = test_vec_iterator;

            switch(iter_type) {
                case iterator_type::FORWARD:
                case iterator_type::CONST_FORWARD:       

                    test_index_arr_iterator += i;
                    test_index_vec_iterator += i;

                    EXPECT_EQ(*test_index_arr_iterator, *test_index_vec_iterator);
                    EXPECT_EQ(*(test_arr_iterator_without_assignment + i), *(test_vec_iterator_without_assignment + i));
                    break;
                case iterator_type::BACKWARD:
                case iterator_type::CONST_BACKWARD:

                    test_index_arr_iterator -= i;
                    test_index_vec_iterator -= i;
                    if(i > 0) {
                        EXPECT_EQ(*test_index_arr_iterator, *test_index_vec_iterator);
                        EXPECT_EQ(*(test_arr_iterator_without_assignment - i), *(test_vec_iterator_without_assignment - i));
                    }
                    break;
                default:
                    break;
            }
        }
    }

    template<class Arr_Iter, class Vec_Iter>
    std::pair<Arr_Iter, Vec_Iter> advance_iterator(Arr_Iter test_arr_iterator, Vec_Iter test_vec_iterator, iterator_type iter_type) {
        switch(iter_type) {
                case iterator_type::FORWARD:
                case iterator_type::CONST_FORWARD:
                    test_arr_iterator++;
                    test_vec_iterator++;

                   
                    break;
                case iterator_type::BACKWARD:
                case iterator_type::CONST_BACKWARD:
                    test_arr_iterator--;
                    test_vec_iterator--;
                    break;
                default:
                    break;
        }
        return std::pair<Arr_Iter, Vec_Iter>(test_arr_iterator, test_vec_iterator);
    }

    template<class Arr_Iter, class Vec_Iter>
    void run_iterator_comparison_tests(Arr_Iter test_arr_iterator, Vec_Iter test_vec_iterator, int test_size, iterator_type iter_type) {
        Arr_Iter test_arr_comp_back_iter = test_arr_iterator;
        Vec_Iter test_vec_comp_back_iter = test_vec_iterator;

        Arr_Iter test_arr_comp_forward_iter = test_arr_iterator;
        Vec_Iter test_vec_comp_forward_iter = test_vec_iterator;

        for(unsigned int i = 0; i < test_size; ++i) {
            EXPECT_EQ(test_arr_comp_back_iter, test_arr_comp_forward_iter);
            EXPECT_EQ(test_vec_comp_back_iter, test_vec_comp_forward_iter);

            std::pair<Arr_Iter, Vec_Iter> advanced_pair = this->advance_iterator(test_arr_comp_forward_iter, test_vec_comp_forward_iter, iter_type);
            
            test_arr_comp_forward_iter = advanced_pair.first;
            test_vec_comp_forward_iter = advanced_pair.second;

            EXPECT_NE(test_arr_comp_forward_iter, test_arr_comp_back_iter);
            EXPECT_NE(test_vec_comp_forward_iter, test_vec_comp_back_iter);

            switch(iter_type) {
                case iterator_type::FORWARD:
                case iterator_type::CONST_FORWARD:
                    EXPECT_GE(test_arr_comp_forward_iter, test_arr_comp_back_iter);
                    EXPECT_GE(test_vec_comp_forward_iter, test_vec_comp_back_iter);

            
                    EXPECT_LE(test_arr_comp_back_iter, test_arr_comp_forward_iter);
                    EXPECT_LE(test_vec_comp_back_iter, test_vec_comp_forward_iter);
                    break;

                case iterator_type::BACKWARD:
                case iterator_type::CONST_BACKWARD:
                    EXPECT_GE(test_arr_comp_back_iter, test_arr_comp_forward_iter);
                    EXPECT_GE(test_vec_comp_back_iter, test_vec_comp_forward_iter);

            
                    EXPECT_LE(test_arr_comp_forward_iter, test_arr_comp_back_iter);
                    EXPECT_LE(test_vec_comp_forward_iter, test_vec_comp_back_iter);
                    break;
                default:
                    break;
            }
            

            test_arr_comp_back_iter = test_arr_comp_forward_iter;
            test_vec_comp_back_iter = test_vec_comp_forward_iter;
        }
    }

    template<class Arr_Iter, class Vec_Iter>
    void run_iterator_test_set(Arr_Iter test_arr_iterator, Vec_Iter test_vec_iterator, int test_size, iterator_type iter_type) {
        this->run_forward_backward_tests(test_arr_iterator, test_vec_iterator, test_size, iter_type);
        this->run_iterator_index_tests(test_arr_iterator, test_vec_iterator, test_size, iter_type);
        this->run_iterator_comparison_tests(test_arr_iterator, test_vec_iterator, test_size, iter_type);
    }

    void all_iterator_tests(int test_size, iterator_type iter_type) {
        if(iter_type == iterator_type::FORWARD) {
            typename dynamic_array<T>::iterator test_arr_iterator = test_arr.begin();
            typename std::vector<T>::iterator test_vec_iterator = test_vec.begin();
            this->run_iterator_test_set(test_arr_iterator, test_vec_iterator, test_size, iter_type);
        }
        else if(iter_type == iterator_type::CONST_FORWARD) {
            typename dynamic_array<T>::const_iterator test_arr_iterator = test_arr.cbegin();
            typename std::vector<T>::const_iterator test_vec_iterator = test_vec.cbegin();
            this->run_iterator_test_set(test_arr_iterator, test_vec_iterator, test_size, iter_type);
        }
        else if(iter_type == iterator_type::BACKWARD) {
            typename dynamic_array<T>::reverse_iterator test_arr_iterator = test_arr.rend();
            typename std::vector<T>::reverse_iterator test_vec_iterator = test_vec.rend();
            this->run_iterator_test_set(test_arr_iterator, test_vec_iterator, test_size, iter_type);
        }
        else if(iter_type == iterator_type::CONST_BACKWARD) {
            typename dynamic_array<T>::const_reverse_iterator test_arr_iterator = test_arr.crend();
            typename std::vector<T>::const_reverse_iterator test_vec_iterator = test_vec.crend();
            this->run_iterator_test_set(test_arr_iterator, test_vec_iterator, test_size, iter_type);
        }
    }

    void run_iterator_tests(int test_size) {
        for(constructor_type test_init_type : constructor_list) {
            this->construct_test_lists(test_init_type, test_size);
            for(iterator_type test_iter_type : iter_type_list) {
                this->all_iterator_tests(test_size, test_iter_type);
            }
            this->test_arr.clear();
            this->test_vec.clear();
        }
    }
};

TYPED_TEST_SUITE_P(dynamic_array_tests);

TYPED_TEST_P(dynamic_array_tests, ConstructionTests) {
    this->run_construct_tests(3);
}

TYPED_TEST_P(dynamic_array_tests, SingleInsertionTests) {
    this->run_single_insertion_tests(3);
}

TYPED_TEST_P(dynamic_array_tests, MultipleInsertionTests) {
    this->run_multiple_insertion_tests(3);
}

TYPED_TEST_P(dynamic_array_tests, IteratorInsertionTests) {
    this->run_insertion_iterator_tests(3);
}

TYPED_TEST_P(dynamic_array_tests, ReplacementInsertionTests) {
    this->run_replacement_insertion_tests(3);
}

TYPED_TEST_P(dynamic_array_tests, EmplacementBackTests) {
    this->run_emplace_back_tests(3, "test_literal");
}

TYPED_TEST_P(dynamic_array_tests, EmplacementTests) {
    this->run_emplace_tests(3, "test_literal");
}

TYPED_TEST_P(dynamic_array_tests, ErasureTests) {
    this->run_single_erasure_tests(3);
}

TYPED_TEST_P(dynamic_array_tests, MultipleErasureTests) {
    this->run_multiple_erasure_tests(3);
}

TYPED_TEST_P(dynamic_array_tests, IteratorTests) {
    this->run_iterator_tests(3);
}

REGISTER_TYPED_TEST_SUITE_P(dynamic_array_tests, 
                            ConstructionTests, 
                            SingleInsertionTests,
                            MultipleInsertionTests,
                            IteratorInsertionTests,
                            ReplacementInsertionTests,
                            EmplacementBackTests,
                            EmplacementTests,
                            ErasureTests,
                            MultipleErasureTests,
                            IteratorTests
                            );

using dynamic_array_test_types = ::testing::Types<std::string>;
INSTANTIATE_TYPED_TEST_SUITE_P(DynamicArray, dynamic_array_tests, dynamic_array_test_types);

// template<class T>
// class dynamic_array_tests: public ::testing::TestWithParam<dynamic_array_test_params> {
//     public:
//         void SetUp() {
//             dynamic_array_test_params test_param = GetParam();
//             unsigned int test_size = test_param.num_elements;
//             constructor_type test_type = test_param.test_type;

//             test_array = dynamic_array<T>();
//             test_vec = std::vector<T>();
//             T insert_value = T();
            
//             dynamic_array<T> copy_array = dynamic_array<T>(test_size, insert_value);

//             switch(test_type) {
//                 case constructor_type::EMPTY:
                    
//                     test_array, test_vec = insert_n_elements(test_array, test_vec, insert_value, test_size);
//                     break;
//                 case constructor_type::STATIC_SIZE:
//                     test_array = dynamic_array<T>(test_size);
//                     test_vec = std::vector<T>(test_size);

//                     test_array, test_vec = insert_n_elements(test_array, test_vec, insert_value, test_size);

//                     break;
//                 case constructor_type::MULTIPLE_VALUE:

//                     test_array = dynamic_array<T>(test_size, insert_value);
//                     test_vec = std::vector<T>(test_size, insert_value);
//                     break;

//                 case constructor_type::OTHER_ARRAY_COPY:
//                     test_array = dynamic_array<T>(copy_array);
//                     test_vec = std::vector<T>(copy_array.begin(), copy_array.end());
//                     break;

//                 case constructor_type::OTHER_ARRAY_MOVE:
//                     test_vec = std::vector<T>(copy_array.begin(), copy_array.end());
//                     test_array = dynamic_array<T>(std::move(copy_array));
//                     break;

//                 case constructor_type::ITERATOR:
//                     test_array = dynamic_array<T>(copy_array.begin(), copy_array.end());
//                     test_vec = std::vector<T>(copy_array.begin(), copy_array.end());
//                     break;

//                 case constructor_type::ASSIGNMENT:
//                     test_array = copy_array;
//                     test_vec = std::vector<T>(copy_array.begin(), copy_array.end());
//                     break;
                
//                 default:
//                     break;
//             }
//         }

//     dynamic_array<T> test_array;
//     std::vector<T> test_vec;

//     void test_array_equality(std::vector<T> test_vec_compare, dynamic_array<T> test_arr_compare) {
//         EXPECT_EQ(test_vec_compare.size(), test_arr_compare.size());
//         for(int i = 0; i < test_vec_compare.size(); ++i) {
//             EXPECT_EQ(test_vec_compare[i], test_arr_compare[i]);
//         }
//     }

//     void reserve_vector_size(std::vector<T> vec_to_expand, size_t expansion_size) {
//         if(vec_to_expand.size()+expansion_size > vec_to_expand.capacity()) {
//             vec_to_expand.reserve(vec_to_expand.size()+expansion_size);
//         }
//     }

//     void run_insert_tests(std::vector<T> test_vec_to_insert, dynamic_array<T> test_arr_to_insert, T insert_value) {
    
//         for(int i = 0; i < test_vec_to_insert.size(); ++i) {
//             dynamic_array<T> test_arr_insert_one = test_arr_to_insert;
//             std::vector<T> test_vec_insert_one = test_vec_to_insert;

//             reserve_vector_size(test_vec_insert_one, 1);

//             typename dynamic_array<T>::const_iterator test_arr_insert_one_itr = test_arr_insert_one.cbegin();
//             typename std::vector<T>::const_iterator test_vec_insert_one_itr = test_vec_insert_one.cbegin();
//             test_arr_insert_one_itr += i;
//             test_vec_insert_one_itr += i;

//             test_arr_insert_one.insert(test_arr_insert_one_itr, insert_value);
//             test_vec_insert_one.insert(test_vec_insert_one_itr, insert_value);

//             test_array_equality(test_vec_insert_one, test_arr_insert_one);

//         }

//         for(int i = 0; i < test_vec_to_insert.size(); ++i) {
//             for(int j = 1; j < test_vec_to_insert.size(); ++j) {
//                 dynamic_array<T> test_arr_insert_multiple = test_arr_to_insert;
//                 std::vector<T> test_vec_insert_multiple = test_vec_to_insert;

//                 reserve_vector_size(test_vec_insert_multiple, i+1);

//                 typename dynamic_array<T>::const_iterator test_arr_insert_multiple_itr = test_arr_insert_multiple.cbegin();
//                 typename std::vector<T>::const_iterator test_vec_insert_multiple_itr = test_vec_insert_multiple.cbegin();
//                 test_vec_insert_multiple_itr += i;
//                 test_arr_insert_multiple_itr += i;
//                 test_vec_insert_multiple.insert(test_vec_insert_multiple_itr, (size_t)j, insert_value);
//                 test_arr_insert_multiple.insert(test_arr_insert_multiple_itr, (size_t)j, insert_value);

//                 test_array_equality(test_vec_insert_multiple, test_arr_insert_multiple);
//             }
//         }

//         for(int i = 0; i < test_vec_to_insert.size(); ++i) {
//             for(int j = i+1; j < test_vec_to_insert.size(); ++j) {
//                 dynamic_array<T> test_arr_insert_iterator = test_arr_to_insert;
//                 std::vector<T> test_vec_insert_iterator = test_vec_to_insert;
//                 std::vector<T> test_vec_inserter = test_vec_to_insert;

//                 typename std::vector<T>::const_iterator test_vec_insert_iterator_itr = test_vec_insert_iterator.cbegin();
//                 typename std::vector<T>::const_iterator test_vec_inserter_itr = test_vec_inserter.cbegin();
//                 typename dynamic_array<T>::const_iterator test_arr_insert_iterator_itr = test_arr_insert_iterator.cbegin();
                
//                 test_vec_insert_iterator_itr += i;
//                 test_vec_inserter_itr += i;
//                 test_arr_insert_iterator_itr += i;
            
//                 typename std::vector<T>::const_iterator test_vec_inserter_back_itr = test_vec_inserter.cbegin();
//                 test_vec_inserter_back_itr += j;
//                 test_arr_insert_iterator.insert(test_arr_insert_iterator_itr, test_vec_inserter_itr, test_vec_inserter_back_itr);
//                 test_vec_insert_iterator.insert(test_vec_insert_iterator_itr, test_vec_inserter_itr, test_vec_inserter_back_itr);

//                 test_array_equality(test_vec_insert_iterator,test_arr_insert_iterator);
//             }
//         }
//     }

//     void run_erasure_tests(std::vector<T> test_vec_to_erase, dynamic_array<T> test_arr_to_erase) {
//         for(int i = 0; i < test_vec_to_erase.size(); ++i) {
//             dynamic_array<T> test_erase_arr_one = test_arr_to_erase;
//             std::vector<T> test_erase_vec_one = test_vec_to_erase;

//             typename dynamic_array<T>::iterator test_erase_arr_one_itr = test_erase_arr_one.begin();
//             typename std::vector<T>::iterator test_erase_vec_one_itr = test_erase_vec_one.begin();

//             test_erase_arr_one_itr += i;
//             test_erase_vec_one_itr += i;

//             test_erase_arr_one.erase(test_erase_arr_one_itr);
//             test_erase_vec_one.erase(test_erase_vec_one_itr);

//             test_array_equality(test_erase_vec_one, test_erase_arr_one);

//             for(int j = i; j < test_vec_to_erase.size(); ++j) {
//                 dynamic_array<T> test_erase_arr_multiple = test_arr_to_erase;
//                 std::vector<T> test_erase_vec_multiple = test_vec_to_erase;
                
//                 typename dynamic_array<T>::iterator test_erase_arr_multiple_start = test_erase_arr_multiple.begin();
//                 typename std::vector<T>::iterator test_erase_vec_multiple_start = test_erase_vec_multiple.begin();
                
//                 typename dynamic_array<T>::iterator test_erase_arr_multiple_end = test_erase_arr_multiple.begin();
//                 typename std::vector<T>::iterator test_erase_vec_multiple_end = test_erase_vec_multiple.begin();
                
//                 test_erase_arr_multiple_start += i;
//                 test_erase_vec_multiple_start += i;

//                 test_erase_arr_multiple_end += j;
//                 test_erase_vec_multiple_end += j;

//                 test_erase_arr_multiple.erase(test_erase_arr_multiple_start, test_erase_arr_multiple_end);
//                 test_erase_vec_multiple.erase(test_erase_vec_multiple_start, test_erase_vec_multiple_end);

//                 test_array_equality(test_erase_vec_multiple, test_erase_arr_multiple);
//             }
//         }

//         for(int i = 0; i < test_vec_to_erase.size(); ++i) {
//             dynamic_array<T> test_arr_erase_const = test_arr_to_erase;
//             std::vector<T> test_vec_erase_const = test_vec_to_erase;

//             typename dynamic_array<T>::const_iterator test_arr_erase_const_itr = test_arr_erase_const.cbegin();
//             typename std::vector<T>::const_iterator test_vec_erase_const_itr = test_vec_erase_const.cbegin();

//             test_arr_erase_const_itr += i;
//             test_vec_erase_const_itr += i;

//             test_arr_erase_const.erase(test_arr_erase_const_itr);
//             test_vec_erase_const.erase(test_vec_erase_const_itr);

//             test_array_equality(test_vec_erase_const,test_arr_erase_const);

//             for(int j = i+1; j < test_vec_to_erase.size(); ++j) {
//                 dynamic_array<T> test_arr_erase_multiple_const = test_arr_to_erase;
//                 std::vector<T> test_vec_erase_multiple_const = test_vec_to_erase;

//                 typename dynamic_array<T>::const_iterator test_arr_erase_multiple_const_start = test_arr_erase_multiple_const.cbegin();
//                 typename std::vector<T>::const_iterator test_vec_erase_multiple_const_start = test_vec_erase_multiple_const.cbegin();
                
//                 typename dynamic_array<T>::const_iterator test_arr_erase_multiple_const_end = test_arr_erase_multiple_const_start;
//                 typename std::vector<T>::const_iterator test_vec_erase_multiple_const_end = test_vec_erase_multiple_const_start;

//                 test_arr_erase_multiple_const_start += i;
//                 test_vec_erase_multiple_const_start += i;

//                 test_arr_erase_multiple_const_end += j;
//                 test_vec_erase_multiple_const_end += j;

//                 test_arr_erase_multiple_const.erase(test_arr_erase_multiple_const_start, test_arr_erase_multiple_const_end);
//                 test_vec_erase_multiple_const.erase(test_vec_erase_multiple_const_start, test_vec_erase_multiple_const_end);

//                 test_array_equality(test_vec_erase_multiple_const,test_arr_erase_multiple_const);
//             }
//         }
//     }

//     template<class Iterator>
//     void test_iterator_single_pass(dynamic_array<T> test_arr, Iterator test_iterator, bool is_forward_iterator, bool reverse) {
//         Iterator test_iterator_forward = test_iterator;
//         if(is_forward_iterator) {
//             for(int i = 0; i < test_arr.size(); ++i) {
//                 EXPECT_EQ(*test_iterator_forward, test_arr[i]);
//                 reverse ? --test_iterator_forward : ++test_iterator_forward;
//             }
        
//             Iterator test_iterator_post_forward = test_iterator;
//             for(int i = 0; i < test_arr.size(); ++i) {
//                 Iterator test_iterator_assign_forward = reverse ? test_iterator_post_forward-- : test_iterator_post_forward++;
//                 EXPECT_EQ(*test_iterator_assign_forward, test_arr[i]);
//                 EXPECT_EQ(test_iterator_post_forward - test_iterator_assign_forward, 1);
//                 EXPECT_NE(test_iterator_assign_forward, test_iterator_post_forward);
//             }
//         }
//         else {
//             for(int i = test_arr.size()-1; i > -1; --i) {
//                 EXPECT_EQ(*test_iterator_forward, test_arr[i]);
//                 reverse ? --test_iterator_forward : ++test_iterator_forward;
//             }

//             Iterator test_iterator_post_forward = test_iterator;
//             for(int i = test_arr.size()-1; i > -1; --i) {
//                 Iterator test_iterator_assign_forward = reverse ? test_iterator_post_forward-- : test_iterator_post_forward++;
//                 EXPECT_EQ(*test_iterator_assign_forward, test_arr[i]);
//                 EXPECT_EQ(test_iterator_post_forward - test_iterator_assign_forward, 1);
//                 EXPECT_NE(test_iterator_assign_forward, test_iterator_post_forward);
//             }
//         }
//     }

//     template<class Iterator>
//     void run_iterator_comparison_tests(int num_comparisons, Iterator test_iterator) {
//         Iterator test_arr_itr = test_iterator;
//         Iterator test_arr_comp_itr = test_iterator;
//         for(int i = 0; i < num_comparisons; ++i) {
//             EXPECT_EQ(test_arr_itr == test_arr_comp_itr, true);
//             EXPECT_EQ(*test_arr_itr, *test_arr_comp_itr);

//             test_arr_itr++;
            
//             EXPECT_EQ(test_arr_itr > test_arr_comp_itr, true);
//             EXPECT_EQ(test_arr_comp_itr < test_arr_itr, true);

//             EXPECT_EQ(test_arr_itr >= test_arr_comp_itr, true);
//             EXPECT_EQ(test_arr_comp_itr <= test_arr_itr, true);

//             EXPECT_EQ(test_arr_itr != test_arr_comp_itr, true);

//             test_arr_comp_itr++;

//             EXPECT_EQ(test_arr_itr >= test_arr_comp_itr, true);
//             EXPECT_EQ(test_arr_comp_itr <= test_arr_itr, true);

//             EXPECT_EQ(test_arr_itr > test_arr_comp_itr, false);
//             EXPECT_EQ(test_arr_comp_itr < test_arr_itr, false);

//             EXPECT_EQ(test_arr_itr != test_arr_comp_itr, false);
//         }
//     }

//     template<class Iterator>
//     void run_iterator_offset_tests(dynamic_array<T> test_arr, Iterator test_iterator, bool is_forward_iterator = true) {
//         Iterator iterator_offset_start = test_iterator;
        
//         for(int i = 0; i < test_arr.size(); ++i) {
//         EXPECT_EQ(test_arr[i], is_forward_iterator ? *(iterator_offset_start+i) : *(iterator_offset_start-i) );
//         }

//         for(int i = 0; i < test_arr.size(); ++i) {
//             Iterator iterator_offset_assign = test_iterator;
//             if (is_forward_iterator) {
//                 iterator_offset_assign += i;
//             }
//             else {
//                 iterator_offset_assign -= i;
//             }
//             EXPECT_EQ(*iterator_offset_assign, test_arr[i]);
//             EXPECT_EQ(iterator_offset_assign, is_forward_iterator ? (test_iterator + i) : (test_iterator - i));
//             if(i > 0) {
//                 EXPECT_NE(iterator_offset_assign, test_iterator);
//             }
//         }

//         Iterator test_offset_index = test_iterator;
//         if(is_forward_iterator) {
//             for(int i = 0; i < test_arr.size(); ++i) {
//                 EXPECT_EQ(test_arr[i], *test_offset_index[i]);
//             }
//         }
//         else {
//             for(int i = (test_arr.size()-i); i > -1; --i) {
//                 EXPECT_EQ(test_arr[i], *test_offset_index[i]);
//             }
//         }
//     }

//     template<class Iterator>
//     void run_iterator_distance_tests(dynamic_array<T> test_arr, Iterator test_iterator, bool is_forward_iterator = true) {
//         Iterator start_iterator = test_iterator;
//         for(int i = 0; i < test_arr.size(); ++i) {
//             Iterator end_iterator = start_iterator;
//             for(int j = i; j < test_arr.size(); ++j) {   
//                 is_forward_iterator ? ++end_iterator : --end_iterator;
//                 EXPECT_EQ(end_iterator-start_iterator, (j+1)-i);
//             }
//             is_forward_iterator ? ++start_iterator : --end_iterator;
//         }
//     }

//     template<class Iterator>
//     void run_all_iterator_tests(dynamic_array<T> test_arr, Iterator test_iterator, bool is_forward_iterator = true) {
//         run_iterator_comparison_tests(test_arr.size(), test_iterator);
//         run_iterator_offset_tests(test_arr, test_iterator, is_forward_iterator);
//         run_iterator_distance_tests(test_arr, test_iterator, is_forward_iterator);

//         if(is_forward_iterator) {
//             Iterator test_arr_itr_forward = test_iterator;
//             test_iterator_single_pass(test_arr, test_arr_itr_forward, is_forward_iterator, false);

//             Iterator test_arr_itr_backward = test_iterator;
//             for(int i = 0; i < test_arr.size()-1; ++i, ++test_arr_itr_backward);
            
//             --test_arr_itr_backward;
//             test_iterator_single_pass(test_arr, test_arr_itr_backward, is_forward_iterator, false);
//         }
//         else {
//             Iterator test_arr_itr_reverse_forward = test_iterator;
//             test_iterator_single_pass(test_arr, test_arr_itr_reverse_forward, is_forward_iterator, true);

//             Iterator test_arr_itr_reverse_backward = test_iterator;
//             for(int i = 0; i < test_arr.size()-1; ++i, --test_arr_itr_reverse_backward);

//             ++test_arr_itr_reverse_backward;
//             test_iterator_single_pass(test_arr, test_arr_itr_reverse_backward, is_forward_iterator, true);
//         }

//     }

//     void run_iterator_tests(dynamic_array<T> test_arr) {

//         typename dynamic_array<T>::iterator test_arr_itr = test_arr.begin();
//         run_all_iterator_tests(test_arr, test_arr_itr);

//         typename dynamic_array<T>::const_iterator test_arr_itr_const = test_arr.cbegin();
//         run_all_iterator_tests(test_arr, test_arr_itr_const);

//         typename dynamic_array<T>::reverse_iterator test_arr_itr_back = test_arr.rend();
//         //test_arr_itr_back++;
//         run_all_iterator_tests(test_arr, test_arr_itr_back, false);

//         typename dynamic_array<T>::const_reverse_iterator test_arr_itr_const_back = test_arr.crend();
//         //test_arr_itr_const_back++;
//         run_all_iterator_tests(test_arr, test_arr_itr_const_back, false);
//     }

//     void run_n_element_tests(size_t num_of_elements) {

//         run_iterator_tests(test_array);

//         T example_value = T();
//         run_insert_tests(test_vec, test_array, example_value);

//         run_erasure_tests(test_vec, test_array);
//     }

//};

