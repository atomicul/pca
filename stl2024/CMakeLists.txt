cmake_minimum_required(VERSION 3.27)
set(CMAKE_CPP_COMPILER clang++-17)
project(stl2023)

set(CMAKE_CXX_STANDARD 20)

include_directories(include)
add_executable(stl2023 main.cpp
        src/items/Item.cpp
        include/items/Item.h
        src/Batch.cpp
        include/Batch.h
        src/Market.cpp
        include/Market.h
        src/items/CompositeItem.cpp
        include/items/CompositeItem.h
        src/Offer.cpp
        include/Offer.h
        include/Ingredient.h)
