cmake_minimum_required (VERSION 3.0.2)

if(WIN32)
	set(target rtmCamera${RTM_SHORT_VERSION}_${RTM_VC_VER}_${CMAKE_VS_PLATFORM_NAME})
else()
	set(target rtmCamera)
endif()

if(WIN32)
	set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()

project (${target}
	VERSION ${RTM_VERSION}
	LANGUAGES CXX)

set(${PROJECT_NAME}_IDLS CameraCommonInterface.idl)

openrtm_idl_compile_all(${PROJECT_NAME}
	"${${PROJECT_NAME}_IDLS}"
	"-I${PROJECT_SOURCE_DIR}/..;-I${PROJECT_SOURCE_DIR}/../../idl"
	EXT_RTM "${RTM_INCLUDE_IDLS}")

link_directories(${ORB_LINK_DIR})
add_definitions(${ORB_C_FLAGS_LIST})
add_definitions(${COIL_C_FLAGS_LIST})
if(WIN32)
	add_definitions(-DRTM_SKEL_IMPORT_SYMBOL)
endif()

if(VXWORKS)
	add_library(${PROJECT_NAME} SHARED ${${PROJECT_NAME}_IDLSKEL})
	openrtm_common_set_compile_props(${PROJECT_NAME})
	openrtm_include_rtm(${PROJECT_NAME})
	install(PROJECT_NAMES ${PROJECT_NAME} LIBRARY DESTINATION ${INSTALL_RTM_LIB_DIR}
						ARCHIVE DESTINATION ${INSTALL_RTM_BIN_DIR}
						RUNTIME DESTINATION ${INSTALL_RTM_BIN_DIR}
						COMPONENT ext)
else()
	if(WIN32)
		set(additional_srcs rtmCameraFactory.cpp)
	endif()
	add_library(${PROJECT_NAME}_objlib OBJECT
		${${PROJECT_NAME}_IDLSKEL}
		${additional_srcs})
	openrtm_gencode_set_compile_props(${PROJECT_NAME}_objlib)
	openrtm_include_rtm(${PROJECT_NAME}_objlib)
	target_include_directories(${PROJECT_NAME}_objlib SYSTEM
		PUBLIC ${PROJECT_BINARY_DIR})
	add_library(${PROJECT_NAME}-static STATIC $<TARGET_OBJECTS:${PROJECT_NAME}_objlib>)
	openrtm_set_link_props_static(${PROJECT_NAME}-static)
	set_target_properties(${PROJECT_NAME}-static PROPERTIES DEBUG_POSTFIX d)

	add_library(${PROJECT_NAME} SHARED
		$<TARGET_OBJECTS:${PROJECT_NAME}_objlib>)
	openrtm_set_link_props_shared(${PROJECT_NAME})
	set_target_properties(${PROJECT_NAME} PROPERTIES DEBUG_POSTFIX d)
	if(WIN32)
		target_link_libraries(${PROJECT_NAME} PRIVATE
			${ORB_LIBRARIES} ${COIL_PROJECT_NAME} ${RTM_LINKER_OPTION} ${RTM_PROJECT_NAME} ${RTCSKEL_PROJECT_NAME})
	else()
		target_link_libraries(${PROJECT_NAME} PRIVATE 
			${ORB_LIBRARIES} ${COIL_PROJECT_NAME} ${RTM_LINKER_OPTION} ${RTM_PROJECT_NAME})
	endif()

	if(UNIX)
		install(TARGETS ${PROJECT_NAME} LIBRARY DESTINATION ${INSTALL_RTM_LIB_DIR}
						ARCHIVE DESTINATION ${INSTALL_RTM_LIB_DIR}
						RUNTIME DESTINATION ${INSTALL_RTM_BIN_DIR}
						COMPONENT ext)

		set_target_properties(${PROJECT_NAME}-static PROPERTIES OUTPUT_NAME ${PROJECT_NAME} CLEAN_DIRECT_OUTPUT 1)
		install(TARGETS ${PROJECT_NAME}-static LIBRARY DESTINATION ${INSTALL_RTM_LIB_DIR}
						ARCHIVE DESTINATION ${INSTALL_RTM_LIB_DIR}
						RUNTIME DESTINATION ${INSTALL_RTM_BIN_DIR}
						COMPONENT ext)
	elseif(WIN32)
		add_dependencies(${PROJECT_NAME} ${PROJECT_NAME}-static)
		install(TARGETS ${PROJECT_NAME} LIBRARY DESTINATION ${INSTALL_RTM_LIB_DIR}
						ARCHIVE DESTINATION ${INSTALL_RTM_LIB_DIR}
						RUNTIME DESTINATION ${INSTALL_RTM_LIB_DIR}
						COMPONENT ext)

		install(TARGETS ${PROJECT_NAME}-static LIBRARY DESTINATION ${INSTALL_RTM_LIB_DIR}
						ARCHIVE DESTINATION ${INSTALL_RTM_LIB_DIR}
						RUNTIME DESTINATION ${INSTALL_RTM_LIB_DIR}
						COMPONENT ext)
	endif()
endif()

install(FILES ${${PROJECT_NAME}_IDLS} DESTINATION ${INSTALL_RTM_INCLUDE_DIR}/rtm/ext COMPONENT ext)
foreach(hdr ${${PROJECT_NAME}_IDLHDR})
	install(FILES "${PROJECT_BINARY_DIR}/${hdr}" DESTINATION ${INSTALL_RTM_INCLUDE_DIR}/rtm/ext COMPONENT ext)
endforeach()
