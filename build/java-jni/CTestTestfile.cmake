# CMake generated Testfile for 
# Source directory: /home/geckos/Documents/java-cpp-study/java-jni
# Build directory: /home/geckos/Documents/java-cpp-study/build/java-jni
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(run-jni "/usr/lib/jvm/java-8-oracle/bin/java" "-cp" "java-jni/java/bin" "-Djava.library.path=/home/geckos/Documents/java-cpp-study/build/java-jni" "arm.test.app.Main")
set_tests_properties(run-jni PROPERTIES  WORKING_DIRECTORY "/home/geckos/Documents/java-cpp-study/build")
