﻿cmake_minimum_required (VERSION 3.0.2)

project (Throughput
	VERSION ${RTM_VERSION}
	LANGUAGES CXX)



set(srcs Throughput.cpp Throughput.h)
examples_build(Throughput SRCS "${srcs}" MAIN ThroughputComp.cpp)