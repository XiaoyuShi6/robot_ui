cmake_minimum_required(VERSION 2.8.3)
project(robot_ui)

find_package(catkin REQUIRED COMPONENTS
  message_generation
  pan_tilt_driver
  roscpp
  rviz
  std_msgs
)

find_package(Qt5Widgets)  #
catkin_package()
include_directories(${catkin_INCLUDE_DIRS} )
link_directories(${catkin_LIBRARY_DIRS})
set (Qt5QtCore_DIR /usr/lib/x86_64-linux-gnu/cmake)

#find_package(Qt4 COMPONENTS QtCore QtGui REQUIRED)
find_package(Qt5 COMPONENTS Core Gui REQUIRED)
include_directories(${QT_USE_FILE})

add_definitions(-DQT_NO_KEYWORDS)
add_dependencies(${catkin_EXPORTED_TARGETS})
#qt4_wrap_cpp(MOC_FILES src/robot_ui.h)
qt5_wrap_cpp(MOC_FILES
        src/robot_ui.h)

set(SOURCE_FILES src/robot_ui.cpp ${MOC_FILES})

add_library(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME}  ${catkin_LIBRARIES})
target_link_libraries(robot_ui Qt5::Widgets)
