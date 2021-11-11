SET(CMAKE_SYSTEM_NAME Generic)
SET(CMAKE_SYSTEM_VERSION 1)

SET(CMAKE_ASM_COMPILER clang)
SET(CMAKE_C_COMPILER clang)
SET(CMAKE_ASM_FLAGS "-target i686-none-elf -D __assembler__ ${CMAKE_ASM_FLAGS}" CACHE STRING "" FORCE)
SET(CMAKE_C_FLAGS "-target i686-none-elf -ffreestanding ${CMAKE_C_FLAGS}" CACHE STRING "" FORCE)
SET(CMAKE_EXE_LINKER_FLAGS_INIT "-target i686-linux-elf -nostdlib")

IF(APPLE)
	SET(CMAKE_EXE_LINKER_FLAGS_INIT "${CMAKE_EXE_LINKER_FLAGS_INIT} -fuse-ld=lld")
ENDIF()