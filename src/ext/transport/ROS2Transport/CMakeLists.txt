cmake_minimum_required(VERSION 3.5)

project (ROS2Transport
	VERSION ${RTM_VERSION}
	LANGUAGES C CXX)


if(NOT CMAKE_CXX_STANDARD)
	set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
	add_compile_options(-Wall -Wextra -Wpedantic)
endif()



find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(fastcdr REQUIRED)
find_package(fastrtps REQUIRED)



link_directories(${ORB_LINK_DIR})
add_definitions(${ORB_C_FLAGS_LIST})

if(WIN32)
	add_definitions(-DNOGDI)
	add_definitions(-DRTM_SKEL_IMPORT_SYMBOL)
endif()


set(target ROS2Transport)

set(srcs ROS2Transport.cpp ROS2Transport.h ROS2MessageInfo.cpp ROS2MessageInfo.h ROS2Serializer.cpp ROS2Serializer.h)


if(VXWORKS AND NOT RTP)
	set(libs ${RTCSKEL_PROJECT_NAME} fastcdr fastrtps)

	add_executable(${target} ${srcs})
	openrtm_common_set_compile_props(${target})
	openrtm_include_rtm(${target})
	target_include_directories(${target}
		PRIVATE ${PROJECT_SOURCE_DIR}/..)
	target_include_directories(${target} SYSTEM
		PUBLIC ${rclcpp_INCLUDE_DIRS}
		PUBLIC ${std_msgs_INCLUDE_DIRS}
		PUBLIC ${geometry_msgs_INCLUDE_DIRS}
		PUBLIC ${sensor_msgs_INCLUDE_DIRS})
	target_link_libraries(${target} ${libs})

	install(TARGETS ${target} LIBRARY DESTINATION ${INSTALL_RTM_EXT_DIR}/transport
				ARCHIVE DESTINATION ${INSTALL_RTM_EXT_DIR}/transport
				RUNTIME DESTINATION ${INSTALL_RTM_EXT_DIR}/transport
				COMPONENT ext)
else()
set(libs ${RTM_PROJECT_NAME} ${ORB_LIBRARIES} ${COIL_PROJECT_NAME} ${DATATYPE_FACTORIES} FastRTPSTransport ${rclcpp_LIBRARIES} ${std_msgs_LIBRARIES} ${geometry_msgs_LIBRARIES} ${sensor_msgs_LIBRARIES} fastcdr fastrtps)


	add_library(${target} SHARED ${srcs})
	openrtm_common_set_compile_props(${target})
	openrtm_include_rtm(${target})
	openrtm_set_link_props_shared(${target})
	target_include_directories(${target}
		PRIVATE ${PROJECT_SOURCE_DIR}/..)
	target_include_directories(${target} SYSTEM
		PUBLIC ${rclcpp_INCLUDE_DIRS}
		PUBLIC ${std_msgs_INCLUDE_DIRS}
		PUBLIC ${geometry_msgs_INCLUDE_DIRS}
		PUBLIC ${sensor_msgs_INCLUDE_DIRS})
	target_link_libraries(${target} PRIVATE ${libs} ${RTM_LINKER_OPTION})
	set_target_properties(${target} PROPERTIES PREFIX "")


	install(TARGETS ${target} LIBRARY DESTINATION ${INSTALL_RTM_EXT_DIR}/transport
				ARCHIVE DESTINATION ${INSTALL_RTM_EXT_DIR}/transport
				RUNTIME DESTINATION ${INSTALL_RTM_EXT_DIR}/transport
				COMPONENT ext)
endif()






if(VXWORKS)
	if(RTP)
	else(RTP)	
		set_target_properties(${target} PROPERTIES SUFFIX ".out")
	endif(RTP)
endif(VXWORKS)






