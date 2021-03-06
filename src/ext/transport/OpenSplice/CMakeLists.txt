cmake_minimum_required (VERSION 3.0.2)

project (OpenSpliceTransport
	VERSION ${RTM_VERSION}
	LANGUAGES CXX)

set(OPENSPLICE_DIR ${OPENSPLICE_DIR} CACHE STRING "set OPENSPLICE_DIR")
set(RAPIDXML_DIR ${RAPIDXML_DIR} CACHE STRING "set RAPIDXML_DIR")

if(NOT OPENSPLICE_DIR)
	message(FATAL_ERROR "Please set OPENSPLICE_DIR.")
endif()

if(NOT RAPIDXML_DIR)
	message(FATAL_ERROR "Please set RAPIDXML_DIR.")
endif()

link_directories(${ORB_LINK_DIR}
		${OPENSPLICE_DIR}/lib)

add_definitions(${ORB_C_FLAGS_LIST})

if(WIN32)
	add_definitions(-DRTM_SKEL_IMPORT_SYMBOL)
	add_definitions(-DTRANSPORT_PLUGIN)
endif()


set(target OpenSpliceTransport)

set(srcs OpenSpliceTransport.cpp OpenSpliceTransport.h OpenSpliceInPort.cpp OpenSpliceInPort.h OpenSpliceOutPort.cpp OpenSpliceOutPort.h OpenSpliceManager.cpp OpenSpliceManager.h OpenSpliceMessageInfo.cpp OpenSpliceMessageInfo.h ccpp_CORBACdrData.h CORBACdrData.cpp CORBACdrData.h CORBACdrDataDcps.cpp CORBACdrDataDcps.h CORBACdrDataDcps_impl.cpp CORBACdrDataDcps_impl.h CORBACdrDataSplDcps.cpp CORBACdrDataSplDcps.h OpenSpliceInPort_Impl.cpp OpenSpliceInPort_Impl.h OpenSpliceOutPort_Impl.cpp OpenSpliceOutPort_Impl.h OpenSpliceManagerFunc.cpp OpenSpliceManagerFunc.h)


if(VXWORKS AND NOT RTP)
	set(libs ${DATATYPE_FACTORIES})

	add_executable(${target} ${srcs})
	openrtm_common_set_compile_props(${target})
	openrtm_include_rtm(${target})
	target_link_libraries(${target} ${libs} dcpsisocpp ddskernel)
	target_include_directories(${target} SYSTEM
				PUBLIC ${OPENSPLICE_DIR}/include/dcps/C++/SACPP
				PUBLIC ${OPENSPLICE_DIR}/include/sys
				PUBLIC ${OPENSPLICE_DIR}/examples/include
				PUBLIC ${RAPIDXML_DIR})

	install(TARGETS ${target} LIBRARY DESTINATION ${INSTALL_RTM_EXT_DIR}/transport
				ARCHIVE DESTINATION ${INSTALL_RTM_EXT_DIR}/transport
				RUNTIME DESTINATION ${INSTALL_RTM_EXT_DIR}/transport
				COMPONENT ext)
else()
	set(libs ${RTM_PROJECT_NAME} ${ORB_LIBRARIES} ${COIL_PROJECT_NAME} ${DATATYPE_FACTORIES})


	add_library(${target} SHARED ${srcs})
	openrtm_common_set_compile_props(${target})
	openrtm_include_rtm(${target})
	target_link_libraries(${target} PRIVATE ${libs} ${RTM_LINKER_OPTION} dcpsisocpp ddskernel)
	target_include_directories(${target} SYSTEM
				PUBLIC ${OPENSPLICE_DIR}/include/dcps/C++/SACPP
				PUBLIC ${OPENSPLICE_DIR}/include/sys
				PUBLIC ${OPENSPLICE_DIR}/examples/include
				PUBLIC ${RAPIDXML_DIR})
	set_target_properties(${target} PROPERTIES PREFIX "")

	set_target_properties(${target} PROPERTIES
				CXX_STANDARD 11
				CXX_STANDARD_REQUIRED YES
				CXX_EXTENSIONS NO
				)

	install(TARGETS ${target} LIBRARY DESTINATION ${INSTALL_RTM_EXT_DIR}/transport
				ARCHIVE DESTINATION ${INSTALL_RTM_EXT_DIR}/transport
				RUNTIME DESTINATION ${INSTALL_RTM_EXT_DIR}/transport
				COMPONENT ext)
endif()


install(FILES OpenSpliceMessageInfo.h DESTINATION ${INSTALL_RTM_INCLUDE_DIR}/rtm/ext COMPONENT ext)



if(VXWORKS)
	if(RTP)
	else(RTP)	
		set_target_properties(${target} PROPERTIES SUFFIX ".out")
	endif(RTP)
endif(VXWORKS)

