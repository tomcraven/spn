SET(tests_include ${CMAKE_CURRENT_LIST_DIR}/ext/googletest/googletest/include ${CMAKE_CURRENT_LIST_DIR}/ext/googletest/googletest)
SET(tests_src
	./ext/googletest/googletest/src/gtest.cc
	./ext/googletest/googletest/src/gtest-death-test.cc
	./ext/googletest/googletest/src/gtest-filepath.cc
	./ext/googletest/googletest/src/gtest-port.cc
	./ext/googletest/googletest/src/gtest-printers.cc
	./ext/googletest/googletest/src/gtest-test-part.cc
	./ext/googletest/googletest/src/gtest-typed-test.cc
	./src/main.cpp
	./src/core/AlgorithmTest.cpp
)