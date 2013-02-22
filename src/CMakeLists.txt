include_directories(${PROJECT_SOURCE_DIR}/include)

include_directories(
    ${OROCOS-RTT_INCLUDE_DIR}
    ${PC_XDECORE_INCLUDE_DIRS}
    ${PC_EIGEN_INCLUDE_DIRS}
	${PC_OCL_INCLUDE_DIRS}
	${PC_OCL_DEPLOY_INCLUDE_DIRS}
)

LINK_DIRECTORIES(
	${PC_XDECORE_LIBRARY_DIRS}
	${PC_OCL_LIBRARY_DIRS}
	${PC_OCL_DEPLOY_LIBRARY_DIRS}
)



orocos_component(XDEKineticEnergyObserver
	XDEKineticEnergyObserver.cpp)

target_link_libraries(
	XDEKineticEnergyObserver
    ${Orocos-RTT_LIBRARIES}
	${PC_OCL_LIBRARIES}
	${PC_OCL_DEPLOY_LIBRARIES}
    ${PC_XDECORE_LIBRARIES}
)



orocos_component(XDEIntersectionObserver
	XDEIntersectionObserver.cpp)

target_link_libraries(
	XDEIntersectionObserver
    ${Orocos-RTT_LIBRARIES}
	${PC_OCL_LIBRARIES}
	${PC_OCL_DEPLOY_LIBRARIES}
    ${PC_XDECORE_LIBRARIES}
)
