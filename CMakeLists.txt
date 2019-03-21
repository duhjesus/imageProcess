# minimal CMakeLists.txt for the AWS SDK for C++
cmake_minimum_required(VERSION 3.2)

# "my-example" is just an example value.
project(process)

# Locate the AWS SDK for C++ package.
# Requires that you build with:
#   -DCMAKE_PREFIX_PATH=/path/to/sdk_install
find_package(AWSSDK REQUIRED COMPONENTS s3)  

# The executable name and its sourcefiles
add_executable(process process.cpp)

# The libraries used by your executable.
# "aws-cpp-sdk-s3" is just an example.
target_link_libraries(process ${AWSSDK_LINK_LIBRARIES})

