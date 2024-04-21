set(CMAKE_SYSTEM_NAME rosco_m68k)
set(CMAKE_SYSTEM_PROCESSOR m68k)

set(CMAKE_C_COMPILER m68k-elf-gcc)
set(CMAKE_CXX_COMPILER m68k-elf-g++)
set(CMAKE_ASM_COMPILER m68k-elf-gcc)

add_compile_options(-m68010)
add_link_options(-m68010 -nolibc -s)