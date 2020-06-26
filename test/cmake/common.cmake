﻿include(ExternalProject)

######################################################################
# build flags

set(CNL_EXCEPTIONS ON CACHE BOOL "compile with exceptions enabled")
if (CNL_EXCEPTIONS)
    set(EXCEPTION_FLAGS "${EXCEPTION_ENABLED_FLAGS}")
else (CNL_EXCEPTIONS)
    set(EXCEPTION_FLAGS "${EXCEPTION_DISABLED_FLAGS}")
endif (CNL_EXCEPTIONS)

set(CNL_INT128 ON CACHE BOOL "compile with support for 128-bit integers (where available)")
if (CNL_INT128)
    set(INT128_FLAGS "${INT128_ENABLED_FLAGS}")
else (CNL_INT128)
    set(INT128_FLAGS "${INT128_DISABLED_FLAGS}")
endif (CNL_INT128)

set(CNL_SANITIZE ON CACHE BOOL "compile with UB sanitizer enabled")
if (CNL_SANITIZE)
    set(SANITIZE_CXX_FLAGS "${SANITIZE_ENABLED_CXX_FLAGS}")
    set(SANITIZE_LINKER_FLAGS "${SANITIZE_ENABLED_LINKER_FLAGS}")
endif (CNL_SANITIZE)

set(COMMON_CXX_FLAGS "${MISC_FLAGS} ${EXCEPTION_FLAGS} ${INT128_FLAGS}")
set(COMMON_LINK_FLAGS Cdsp "${CONAN_LIBS}")
