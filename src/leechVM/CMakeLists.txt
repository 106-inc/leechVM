add_library(leechVM leechVM.cc)
target_include_directories(leechVM
    PRIVATE
    ${CMAKE_BINARY_DIR}/src/frontend
)
