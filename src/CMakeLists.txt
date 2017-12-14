set(LIBRARY_TARGET cppatch)

add_library(${LIBRARY_TARGET} SHARED
  cppatch.cpp
  queues.cpp
  sources.cpp
  )

# setting compile flags for this target
if (ASAN)
  c_message(STATUS "[OPTION] ASAN compilation flags activated" YELLOW)
  set_target_properties(${LIBRARY_TARGET} PROPERTIES
    COMPILE_FLAGS "-fsanitize=address -fno-omit-frame-pointer -fno-common")
elseif (TSAN)
  c_message(STATUS "[OPTION] TSAN compilation flags activated" YELLOW)
  set_target_properties(${LIBRARY_TARGET} PROPERTIES
    COMPILE_FLAGS "-fsanitize=thread -fno-omit-frame-pointer -fno-common")
elseif (MSAN)
  c_message(STATUS "[OPTION] MSAN compilation flags activated" YELLOW)
  set_target_properties(${LIBRARY_TARGET} PROPERTIES
    COMPILE_FLAGS "-fsanitize=memory -fno-omit-frame-pointer -fno-common")
endif()


find_library(LIBDISPATCH dispatch)
if (LIBDISPATCH)
  target_link_libraries(cppatch ${LIBDISPATCH})
endif ()


if (GTEST)
  target_include_directories(${LIBRARY_TARGET} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}) # CMAKE >= 2.8.11
endif()

add_in_list(CPPATCH_LIBRARIES ${LIBRARY_TARGET})
