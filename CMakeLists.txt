cmake_minimum_required(VERSION 3.8)
project(sealien_ctrlpilot_mavlinkbridge)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(ament_index_cpp REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(sealien_ctrlpilot_msgmanagement REQUIRED)
find_package(yaml-cpp REQUIRED)

add_library(${PROJECT_NAME}_core
  src/mavlink_bridge_core.cpp
)

target_include_directories(${PROJECT_NAME}_core PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

target_include_directories(${PROJECT_NAME}_core SYSTEM PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/lib/v2.0
  ${CMAKE_CURRENT_SOURCE_DIR}/lib/v2.0/sealien_mavlink
)

ament_target_dependencies(${PROJECT_NAME}_core
  ament_index_cpp
  rclcpp
  std_msgs
  geometry_msgs
  sealien_ctrlpilot_msgmanagement
)

target_link_libraries(${PROJECT_NAME}_core yaml-cpp)
target_compile_features(${PROJECT_NAME}_core PUBLIC cxx_std_17)

add_executable(rov_mavlink_node src/rov_mavlink_node.cpp)
target_link_libraries(rov_mavlink_node ${PROJECT_NAME}_core)
ament_target_dependencies(rov_mavlink_node rclcpp)

add_executable(tms_mavlink_node src/tms_mavlink_node.cpp)
target_link_libraries(tms_mavlink_node ${PROJECT_NAME}_core)
ament_target_dependencies(tms_mavlink_node rclcpp)

add_executable(rov_mavlink_test_node src/rov_mavlink_test_node.cpp)
target_link_libraries(rov_mavlink_test_node yaml-cpp)
ament_target_dependencies(
  rov_mavlink_test_node
  ament_index_cpp
  rclcpp
  std_msgs
  geometry_msgs
  sealien_ctrlpilot_msgmanagement
)
target_compile_features(rov_mavlink_test_node PUBLIC cxx_std_17)

install(TARGETS
  ${PROJECT_NAME}_core
  rov_mavlink_node
  tms_mavlink_node
  rov_mavlink_test_node
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION lib/${PROJECT_NAME}
)

install(PROGRAMS
  scripts/start_rov_mavlink_test.sh
  scripts/start_rov_mavlink_long_test.sh
  DESTINATION lib/${PROJECT_NAME}
)

install(DIRECTORY include/
  DESTINATION include
)

install(DIRECTORY config/
  DESTINATION share/${PROJECT_NAME}/config
)

install(DIRECTORY launch/
  DESTINATION share/${PROJECT_NAME}/launch
  PATTERN "__pycache__" EXCLUDE
)

install(DIRECTORY docs/
  DESTINATION share/${PROJECT_NAME}/docs
)

install(DIRECTORY lib/
  DESTINATION share/${PROJECT_NAME}/lib
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  set(ament_cmake_copyright_FOUND TRUE)
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
