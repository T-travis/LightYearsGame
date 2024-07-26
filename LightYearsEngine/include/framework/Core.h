#pragma once
#include <stdio.h> // this is faster than <iostream>
#include <memory>
#include <vector>
#include <map>
#include <unordered_map>
#include <unordered_set>

namespace ly
{
//** COMMON DATA TYPES **//

// Using TEMPLATES for Generics

// UNIQUE POINTER -> you don't need to delete/deallocate pointer
// you can't copy/transfered but you can move to another pointer
template<typename T>
using unique = std::unique_ptr<T>;

// SHARED POINTER -> a type of smart pointer that manages the lifetime of an object
// They are suitable for situations where multiple entities share ownership of the object.
// Multiple objects may want to share a pointer.
template<typename T>
using shared = std::shared_ptr<T>;

// WEAK POINTER -> a smart pointer that does not take ownership of an object but acts as an observer.
// It does not participate in reference counting to delete an object or extend its lifetime. 
// Weak pointers are mainly used to break the circular dependency that shared pointers create.
template<typename T>
using weak = std::weak_ptr<T>;

// Container object
template<typename T>
using List = std::vector<T>;

// Set container object
template<typename T>
using Set = std::unordered_set<T>;

// Map object - Ordered Map - Use when you want ordering
// less orders the keyType (1 would be before 2)
template<typename keyType, typename valueType, typename pr = std::less<keyType>>
using Map = std::map<keyType, valueType, pr>;

// Dictionary object - Unordered Map - Faster lookup
// hasing is used for order which isn't known thus unordered
template<typename keyType, typename valueType, typename hasher  = std::hash<keyType>>
using Dictionary = std::unordered_map<keyType, valueType, hasher>;

//** END COMMON DATA TYPES **//


// macro logging:
// printf can be swapped out with any other logger without changing
// other code
#define LOG(M, ...) printf(M "\n", ##__VA_ARGS__)


}