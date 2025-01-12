cmake_minimum_required(VERSION 3.5)
project(quadrotor)

# Default to C99
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(gazebo_ros REQUIRED)
find_package(gazebo REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclpy REQUIRED)
find_package(xacro REQUIRED)
find_package(robot_state_publisher REQUIRED)
# uncomment the following section in order to fill in
# further dependencies manually.
# find_package(<dependency> REQUIRED)

install(DIRECTORY
    urdf
    meshes
    launch
    worlds
    src
    scripts
    DESTINATION share/${PROJECT_NAME}/
    )

install(PROGRAMS
    launch/robot_description_publisher.py
    scripts/spawn_object.py
    DESTINATION lib/${PROJECT_NAME}
    )

add_library(quadrotor_plugin SHARED 
    src/quadrotor_plugin.cpp
)

target_include_directories(quadrotor_plugin PUBLIC include)
ament_target_dependencies(quadrotor_plugin
    "gazebo_ros"
)
ament_export_libraries(quadrotor_plugin)

install(TARGETS
    quadrotor_plugin
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # uncomment the line when a copyright and license is not present in all source files
  #set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # uncomment the line when this package is not in a git repo
  #set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()

install(DIRECTORY include/
    DESTINATION include)
