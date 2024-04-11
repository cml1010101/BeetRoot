ADD_BEETROOT_MODULE(klib_base
    SOURCES
        "src/String.cpp"
        "src/Vector.cpp"
    PUBLIC_INCLUDE_DIRS
        include
    REQUIREMENTS
        "arch_${ARCH}")