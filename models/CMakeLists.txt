# 自动复制资源文件到构建目录
file(GLOB RESOURCE_FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/*.urdf"
)

set(RESOURCE_DEST_DIR ${CMAKE_CURRENT_BINARY_DIR})

foreach(file ${RESOURCE_FILES})
    get_filename_component(fname ${file} NAME)
    configure_file(${file} ${RESOURCE_DEST_DIR}/${fname} COPYONLY)
endforeach()
