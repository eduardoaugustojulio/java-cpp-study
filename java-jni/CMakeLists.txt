cmake_minimum_required(VERSION 2.8)

# REQUIRED JAVA
FIND_PACKAGE(Java COMPONENTS Development)
INCLUDE(UseJava)
SET(CMAKE_JAVA_COMPILE_FLAGS "-source" "1.8" "-target" "1.8")

SET(JAVA_SOURCE_FILES 
    arm/test/app/Main.java 
    arm/test/lib/FooClass.java)

# Build Java classes
FILE(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/java/bin")
SET(class_files)
FOREACH(_java_file ${JAVA_SOURCE_FILES})
    # _java_file: relative file name
    # _class_file: relative class name
    STRING(REGEX REPLACE "\\.java$"
	   ".class" _class_file
           "${_java_file}")
    ADD_CUSTOM_COMMAND(
        OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/java/bin/${_class_file}"
        COMMAND
            ${Java_JAVAC_EXECUTABLE}
            ${CMAKE_JAVA_COMPILE_FLAGS}
            -sourcepath "${CMAKE_CURRENT_SOURCE_DIR}/java/src"
            -d "${CMAKE_CURRENT_BINARY_DIR}/java/bin"
            "${CMAKE_CURRENT_SOURCE_DIR}/java/src/${_java_file}"
        DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/java/src/${_java_file}")
    LIST(APPEND class_files "java/bin/${_class_file}")
ENDFOREACH()

ADD_CUSTOM_TARGET(JavaJNIClasses ALL DEPENDS ${class_files})

# Make the JNI header file
ADD_CUSTOM_COMMAND(
    OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/include/FooClass_jni.h"
    COMMAND
        ${Java_JAVAH_EXECUTABLE}
        -o "${CMAKE_CURRENT_BINARY_DIR}/include/FooClass_jni.h"
        -classpath "${CMAKE_CURRENT_BINARY_DIR}/java/bin"
        arm.test.lib.FooClass
    DEPENDS "${CMAKE_CURRENT_BINARY_DIR}/java/bin/arm/test/lib/FooClass.class")
ADD_CUSTOM_TARGET(JavaJNIHeaders ALL DEPENDS "${CMAKE_CURRENT_BINARY_DIR}/include/FooClass_jni.h")

# Require JNI
FIND_PACKAGE(JNI REQUIRED)

# Builds the JNI wrapper
INCLUDE_DIRECTORIES("${CPPLIB_INCLUDE_DIR}"
                   "${CMAKE_CURRENT_BINARY_DIR}/include"
	        	    ${JNI_INCLUDE_DIRS}
)

ADD_LIBRARY(foo_jni SHARED c/jni_wrapper.cpp)

link_directories("${CMAKE_BINARY_DIR}/foo")

SET_TARGET_PROPERTIES(
    foo_jni PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
    LIBRARY_OUTPUT_DIRECTORY_DEBUG "${CMAKE_CURRENT_BINARY_DIR}"
    LIBRARY_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_BINARY_DIR}"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_CURRENT_BINARY_DIR}"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_BINARY_DIR}")

TARGET_LINK_LIBRARIES(foo_jni foo)

ADD_DEPENDENCIES(foo_jni JavaJNIHeaders)

# Testing
IF(BUILD_TESTS)
    FIND_PACKAGE(Java COMPONENTS Runtime)
    ADD_TEST(
        NAME run-jni
        COMMAND
            "${Java_JAVA_EXECUTABLE}"
            -cp java-jni/java/bin
            -Djava.library.path=java-jni
            arm.test.app.Main
        WORKING_DIRECTORY "${CMAKE_BINARY_DIR}")
ENDIF()
