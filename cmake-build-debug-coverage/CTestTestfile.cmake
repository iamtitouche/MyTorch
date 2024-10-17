# CMake generated Testfile for 
# Source directory: C:/Users/dev/Documents/MyTorch
# Build directory: C:/Users/dev/Documents/MyTorch/cmake-build-debug-coverage
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test([=[MyTorchTests]=] "C:/Users/dev/Documents/MyTorch/cmake-build-debug-coverage/tests.exe" "--gtest_color=yes")
set_tests_properties([=[MyTorchTests]=] PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/dev/Documents/MyTorch/CMakeLists.txt;71;add_test;C:/Users/dev/Documents/MyTorch/CMakeLists.txt;0;")
subdirs("googletest")
