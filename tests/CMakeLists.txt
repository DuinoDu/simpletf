add_executable(tests tests.cpp simpletf_t.cpp)
target_link_libraries(tests PUBLIC simpletf Catch2::Catch2 glog)

# allow user to run tests with `make test` or `ctest`
catch_discover_tests(tests)
