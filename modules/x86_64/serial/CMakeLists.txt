ADD_BEETROOT_MODULE(x86_64_serial
    SOURCES
        "src/SerialLogger.cpp"
    PUBLIC_INCLUDE_DIRS
        "include"
    REQUIREMENTS
        "arch_x86_64;klib_base;core")