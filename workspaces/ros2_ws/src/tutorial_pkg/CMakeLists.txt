cmake_minimum_required(VERSION 3.8)
project(tutorial_pkg)

# Set C++ standard to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(std_msgs REQUIRED)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

add_executable(my_first_node src/my_first_node.cpp)
add_executable(avg_brightness src/avg_brightness.cpp)
add_executable(publisher src/publisher.cpp)
add_executable(timer src/timer.cpp)

ament_target_dependencies(my_first_node rclcpp sensor_msgs)
ament_target_dependencies(avg_brightness rclcpp sensor_msgs)
ament_target_dependencies(publisher rclcpp sensor_msgs std_msgs)
ament_target_dependencies(timer rclcpp)

install(TARGETS
  my_first_node
  avg_brightness
  publisher
  timer

  DESTINATION lib/${PROJECT_NAME}
)

ament_package()
