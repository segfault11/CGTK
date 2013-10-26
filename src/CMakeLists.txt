# build and install the library
FILE(GLOB_RECURSE files  RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)
FILE(GLOB_RECURSE cfiles  RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.c)
add_library(CGTK STATIC ${files} ${cfiles})
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/libCGTK.a DESTINATION lib)

# install the headers
file(GLOB_RECURSE headers RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "*.h")
foreach(header ${headers})
    get_filename_component(directory ${header} PATH)
    #message(STATUS ${directory})
    install(FILES ${header} DESTINATION include/CGTK/${directory})
endforeach()

#install inline files
file(GLOB_RECURSE inlinefiles RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "*.inl")
foreach(inlinefile ${inlinefiles})
    get_filename_component(directory ${inlinefile} PATH)
    #message(STATUS ${directory})
    install(FILES ${inlinefile} DESTINATION include/CGTK/${directory})
endforeach()