ADD_BEETROOT_MODULE(arch_x86_64
    SOURCES
        "src/Paging.cpp"
        "src/CPU.cpp"
    PUBLIC_INCLUDE_DIRS
        "include"
    REQUIREMENTS
        "klib_base")