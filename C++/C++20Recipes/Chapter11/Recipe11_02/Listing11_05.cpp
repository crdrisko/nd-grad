// Copyright (c) 2020 J. Burton Browning and Bruce Sutherland. Some rights reserved.
// Licensed under the Freeware License. See the LICENSE file in the project root for more information.
//
// Name: Listing11_05.cpp
// Author: crdrisko
// Date: 10/13/2020-07:41:39
// Description: Creating a class that uses static data to track state

#include <cstdlib>
#include <iostream>
#include <stack>
#include <thread>
#include <vector>

class MyManagedObject
{
private:
    static const unsigned int MAX_OBJECTS {4};

    using MyManagedObjectCollection = std::vector<MyManagedObject>;
    static MyManagedObjectCollection s_ManagedObjects;

    static std::stack<unsigned int> s_FreeList;

    unsigned int m_Value {0xFFFFFFFF};

public:
    MyManagedObject() = default;
    MyManagedObject(unsigned int value) : m_Value {value} {}

    void* operator new(std::size_t numBytes)
    {
        void* objectMemory {};

        if (s_ManagedObjects.capacity() < MAX_OBJECTS)
            s_ManagedObjects.reserve(MAX_OBJECTS);

        if (numBytes == sizeof(MyManagedObject) && s_ManagedObjects.size() < s_ManagedObjects.capacity())
        {
            unsigned int index {0xFFFFFFFF};

            if (s_FreeList.size() > 0)
            {
                index = s_FreeList.top();
                s_FreeList.pop();
            }

            if (index == 0xFFFFFFFF)
            {
                s_ManagedObjects.push_back({});
                index = s_ManagedObjects.size() - 1;
            }
        }
        else
            objectMemory = malloc(numBytes);

        return objectMemory;
    }

    void operator delete(void* pMem)
    {
        const intptr_t index {(static_cast<MyManagedObject*>(pMem) - s_ManagedObjects.data())
                              / static_cast<intptr_t>(sizeof(MyManagedObject))};

        if (0 <= index && index < static_cast<intptr_t>(s_ManagedObjects.size()))
            s_FreeList.emplace(static_cast<unsigned int>(index));
        else
            free(pMem);
    }
};

MyManagedObject::MyManagedObjectCollection MyManagedObject::s_ManagedObjects {};
std::stack<unsigned int> MyManagedObject::s_FreeList {};

int main(int argc, char* argv[])
{
    std::cout << std::hex << std::showbase;

    MyManagedObject* pObject1 {new MyManagedObject(1)};

    std::cout << "pObject1: " << pObject1 << std::endl;

    MyManagedObject* pObject2 {new MyManagedObject(2)};

    std::cout << "pObject2: " << pObject2 << std::endl;

    delete pObject1;
    pObject1 = nullptr;

    MyManagedObject* pObject3 {new MyManagedObject(3)};

    std::cout << "pObject3: " << pObject3 << std::endl;

    pObject1 = new MyManagedObject(4);

    std::cout << "pObject1: " << pObject1 << std::endl;

    delete pObject2;
    pObject2 = nullptr;

    delete pObject3;
    pObject3 = nullptr;

    delete pObject1;
    pObject1 = nullptr;

    return 0;
}
