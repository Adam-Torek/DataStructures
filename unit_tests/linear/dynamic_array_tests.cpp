#include "gtest/gtest.h"
#include <initializer_list>
#include <stdexcept>
#include <string>
#include <vector>

#include "data_structures/src/linear/dynamic_array.hpp"

using data_structures::linear::dynamic_array;

template<class T>
void run_insert_tests(std::vector<T> test_vec, dynamic_array<T> test_arr, T insert_value) {
    
}

void run_n_element_tests(size_t num_of_elements) {
    

    std::vector<int*> test_vec = std::vector<int*>();
    dynamic_array<int*> test_arr = dynamic_array<int*>();
    for(int i = 0; i < num_of_elements; ++i) {
        test_vec.push_back(&i);
        test_arr.push_back(&i);
    }

    EXPECT_EQ(test_arr.size(), num_of_elements);

    for(int i = 0; i < num_of_elements; ++i) {
        EXPECT_EQ(test_vec.at(i), test_arr.at(i));
        EXPECT_EQ(test_vec[i], test_arr[i]);
    }

    dynamic_array<int*>::iterator test_arr_itr = test_arr.begin();
    std::vector<int*>::iterator test_vec_itr = test_vec.begin();

    for(; test_arr_itr != test_arr.end() && test_vec_itr != test_vec.end(); ++test_arr_itr, ++test_vec_itr) {
        EXPECT_EQ(*test_arr_itr, *test_vec_itr);
    }

    for(; test_arr_itr != test_arr.begin() && test_vec_itr != test_vec.begin(); --test_arr_itr, --test_vec_itr) {
        EXPECT_EQ(*test_arr_itr, *test_vec_itr);
    }
    
    for(int i = 0; i < num_of_elements; ++i) {
        dynamic_array<int*> insert_test = test_arr;
        dynamic_array<int*>::const_iterator test_arr_itr_const = insert_test.cbegin();
        test_arr_itr_const += i;
        dynamic_array<int*>::iterator result = insert_test.insert(test_arr_itr_const,  &i);
        EXPECT_EQ(*(result-1),&i);
        EXPECT_EQ(insert_test.size(), num_of_elements+1);

        dynamic_array<int*> test_insert_multiple = test_arr;
        dynamic_array<int*>::const_iterator test_arr_itr_const_multiple = test_insert_multiple.cbegin();
        size_t multiple_insert_len = num_of_elements;
        dynamic_array<int*>::iterator result_multiple = test_insert_multiple.insert(test_arr_itr_const_multiple, multiple_insert_len, &i);
        EXPECT_EQ(test_insert_multiple.size(), multiple_insert_len + num_of_elements);
        
        for(int j = 1; j < multiple_insert_len+1; ++j) {
            EXPECT_EQ(*(result_multiple-j), &i);
        }

        for(int j = 0; j < multiple_insert_len+1; j++) {
            
        }
    }



}

TEST(DynamicArray, ZeroElementTests) {
    using data_structures::linear::dynamic_array;

    dynamic_array<int*> test = dynamic_array<int*>();
    ASSERT_EQ(0, test.size());
    ASSERT_EQ(0, test.capacity());
}

TEST(DynamicArray, TwoElementTests) {
    // using data_structures::linear::dynamic_array;
    // unsigned long expected_size = 2;
    // int example_num = 2;
    // int* example_val = &example_num;
    // dynamic_array<int*> test = dynamic_array<int*>(expected_size, example_val);
    // unsigned long test_size = test.size();
    // int* item1 = test[0];
    // int* item2 = test[1];
    // EXPECT_EQ(test_size, expected_size);
    // EXPECT_EQ(item1, example_val);
    // EXPECT_EQ(item2, example_val);

    // EXPECT_THROW({
    //     try{
    //         test[2];
    //     }catch(std::out_of_range) {
    //         throw;
    //     }
    // }, std::out_of_range);

    // test.reserve(5);

    // data_structures::linear::dynamic_array_const_iterator<int*> insert_itr = test.begin();
    // //data_structures::linear::dynamic_array_const_iterator<int*> insert_iter_2 = test.begin();
    // //EXPECT_EQ(insert_itr, insert_iter_2);
    // insert_itr += 2;
    // int example_num_2 = 3;
    // int* insert_val = &example_num_2;
    // test.insert(insert_itr, 3, insert_val);
    // EXPECT_EQ(test.size(), 5);
    // EXPECT_EQ(test[0], insert_val);
    // EXPECT_EQ(test[1], insert_val);
    run_n_element_tests(2);
}