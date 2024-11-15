#include <gtest/gtest.h>
#include "../include/Stack.hpp"
#include "../include/MapDynamicMemoryResource.hpp"

TEST(StackTest, DefaultConstructor) {
    Stack<int> stack;
    EXPECT_TRUE(stack.Empty());
    EXPECT_EQ(stack.Size(), 0);
}

TEST(StackTest, PushAndTop) {
    Stack<int> stack;
    stack.Push(1);
    stack.Push(2);
    stack.Push(3);
    EXPECT_EQ(stack.Top(), 3);
    EXPECT_EQ(stack.Size(), 3);
}

TEST(StackTest, Pop) {
    Stack<int> stack;
    stack.Push(1);
    stack.Push(2);
    stack.Push(3);
    
    stack.Pop();
    EXPECT_EQ(stack.Top(), 2);
    EXPECT_EQ(stack.Size(), 2);

    stack.Pop();
    EXPECT_EQ(stack.Top(), 1);
    EXPECT_EQ(stack.Size(), 1);

    stack.Pop();
    EXPECT_TRUE(stack.Empty());
}

TEST(StackTest, Iterator) {
    Stack<int> stack;
    stack.Push(1);
    stack.Push(2);
    stack.Push(3);

    auto it = stack.Begin();
    EXPECT_EQ(*it, 3);
    ++it;
    EXPECT_EQ(*it, 2);
    ++it;
    EXPECT_EQ(*it, 1);
    ++it;
    EXPECT_EQ(it, stack.End());
}

TEST(StackTest, CopyConstructor) {
    Stack<int> stack;
    stack.Push(1);
    stack.Push(2);
    stack.Push(3);

    Stack<int> copied_stack(stack);
    EXPECT_EQ(copied_stack.Size(), 3);
    EXPECT_EQ(copied_stack.Top(), 3);

    copied_stack.Pop();
    EXPECT_EQ(copied_stack.Top(), 2);
    EXPECT_EQ(copied_stack.Size(), 2);
}

TEST(StackTest, MoveConstructor) {
    Stack<int> stack;
    stack.Push(1);
    stack.Push(2);
    stack.Push(3);

    Stack<int> moved_stack(std::move(stack));
    EXPECT_EQ(moved_stack.Size(), 3);
    EXPECT_EQ(moved_stack.Top(), 3);

    EXPECT_TRUE(stack.Empty());
}

TEST(StackTest, Emplace) {
    Stack<std::pair<int, int>> stack;
    stack.Emplace(1, 2);
    stack.Emplace(3, 4);

    EXPECT_EQ(stack.Size(), 2);
    EXPECT_EQ(stack.Top().first, 3);
    EXPECT_EQ(stack.Top().second, 4);
}

TEST(StackTest, IteratorRangeConstructor) {
    std::vector<int> vec = {1, 2, 3, 4, 5};
    Stack<int> stack(vec.begin(), vec.end());

    EXPECT_EQ(stack.Size(), 5);
    EXPECT_EQ(stack.Top(), 5);
}

TEST(MapDynamicMemoryResourceTest, AllocationDeallocation) {
    MapDynamicMemoryResource pool;
    std::pmr::polymorphic_allocator<int> allocator(&pool);

    {
        Stack<int, std::pmr::polymorphic_allocator<int>> stack(allocator);
        stack.Push(1);
        stack.Push(2);
    }

    // Все блоки должны быть деаллоцированы
    EXPECT_EQ(pool.get_used_blocks_count(), 0);
    EXPECT_GE(pool.get_free_blocks_count(), 1);
}

TEST(MapDynamicMemoryResourceTest, ReuseFreedMemoryWithGlobalNewDelete) {
    MapDynamicMemoryResource pool;
    std::pmr::polymorphic_allocator<int> allocator(&pool);

    Stack<int, std::pmr::polymorphic_allocator<int>> stack1(allocator);
    for (int i = 0; i < 20; ++i) {
        stack1.Push(i);
    }

    EXPECT_EQ(pool.get_used_blocks_count(), 1);
    EXPECT_EQ(pool.get_free_blocks_count(), 1);

    Stack<int, std::pmr::polymorphic_allocator<int>> stack2(allocator);
    for (int i = 0; i < 10; ++i) {
        stack2.Push(i);
    }

    EXPECT_EQ(pool.get_used_blocks_count(), 2);
    EXPECT_EQ(pool.get_free_blocks_count(), 0);
}

// Тест для проверки поведения с большим количеством элементов
TEST(StackTest, LargePushAndPop) {
    MapDynamicMemoryResource pool;
    std::pmr::polymorphic_allocator<int> allocator(&pool);
    
    Stack<int, std::pmr::polymorphic_allocator<int>> stack(allocator);
    const int large_count = 1000;
    
    for (int i = 0; i < large_count; ++i) {
        stack.Push(i);
    }
    
    EXPECT_EQ(stack.Size(), large_count);

    for (int i = large_count - 1; i >= 0; --i) {
        EXPECT_EQ(stack.Top(), i);
        stack.Pop();
    }
    
    EXPECT_TRUE(stack.Empty());
}


int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}