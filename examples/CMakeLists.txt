file(GLOB_RECURSE EXAMPLE_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_LIST_DIR}/*.cpp")

foreach(SOURCE_FILE ${EXAMPLE_SOURCES})
    get_filename_component(FILE_NAME ${SOURCE_FILE} NAME_WE)

    get_filename_component(DIR_PATH ${SOURCE_FILE} DIRECTORY)
    get_filename_component(DIR_NAME ${DIR_PATH} NAME)

    # parent folder + file name
    set(TARGET_NAME "${DIR_NAME}_${FILE_NAME}")

    add_executable(${TARGET_NAME} ${SOURCE_FILE})
    target_link_libraries(${TARGET_NAME} PRIVATE ${PROJECT_NAME}_lib)
endforeach()
