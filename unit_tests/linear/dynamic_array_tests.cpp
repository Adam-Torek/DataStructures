#include "gtest/gtest.h"
#include <stdexcept>
#include <string>

#include "data_structures/include/linear/dynamic_array.hpp"

TEST(DynamicArray, ZeroElementTests) {
    using data_structures::linear::dynamic_array;

    dynamic_array<int*> test = dynamic_array<int*>();
    ASSERT_EQ(0, test.size());
    ASSERT_EQ(0, test.capacity());
}

TEST(DynamicArray, TwoElementTests) {
    using data_structures::linear::dynamic_array;
    unsigned long expected_size = 2;
    int example_num = 2;
    int* example_val = &example_num;
    dynamic_array<int*> test = dynamic_array<int*>(expected_size, example_val);
    unsigned long test_size = test.size();
    int* item1 = test[0];
    int* item2 = test[1];
    EXPECT_EQ(test_size, expected_size);
    EXPECT_EQ(item1, example_val);
    EXPECT_EQ(item2, example_val);

    EXPECT_THROW({
        try{
            test[2];
        }catch(std::out_of_range) {
            throw;
        }
    }, std::out_of_range);
}