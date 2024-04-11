ADD_BEETROOT_MODULE(core
    SOURCES
        "src/Logger.cpp"
        "src/Heap.cpp"
    PUBLIC_INCLUDE_DIRS
        include
    REQUIREMENTS
        "klib_base")