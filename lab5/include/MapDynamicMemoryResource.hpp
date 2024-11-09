#pragma once

#include <cstddef>
#include <memory_resource>
#include <map>

class MapDynamicMemoryResource : public std::pmr::memory_resource {
private:
    std::map<void*, size_t> used_blocks;
    std::multimap<size_t, void*> free_blocks;

public:
    void* do_allocate(size_t bytes, size_t alignment) override {
        auto it = free_blocks.lower_bound(bytes);
        if (it == free_blocks.end()) {
            void* new_block = ::operator new(bytes);
            used_blocks[new_block] = bytes;
            return new_block;
        }
        size_t block_size = it->first;
        void* block_ptr = it->second;
        free_blocks.erase(it);

        used_blocks[block_ptr] = bytes;
        free_blocks.insert({block_size - bytes, static_cast<char*>(block_ptr) + bytes});

        return block_ptr;
    }

    void do_deallocate(void* ptr, size_t bytes, size_t alignment) override {
        auto it = used_blocks.find(ptr);
        if (it == used_blocks.end()) {
            return;
        }
        void* block_ptr = it->first;
        size_t block_size = it->second;
        
        free_blocks.insert({block_size, block_ptr});
        used_blocks.erase(it);
    }

    bool do_is_equal(const std::pmr::memory_resource& other) const noexcept override {
        return this == &other;
    }
};