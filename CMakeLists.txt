cmake_minimum_required (VERSION 2.6)
project (Bomberman)


set(SOURCES 
	Src/backstage.cpp
	Src/engine.cpp
	Src/entity.cpp
	Src/figure.cpp
	Src/file.cpp
	Src/game.cpp
	Src/supervisor.cpp
	Src/subordinate.cpp	
	Src/primitive.cpp
	Src/shader.cpp
	Src/main.cpp
	Src/graph.cpp
	)
	
set(HEADERS
	Headers/backstage.h
	Headers/engine.h
	Headers/entity.h
	Headers/figure.h
	Headers/file.h
	Headers/game.h
	Headers/supervisor.h
	Headers/subordinate.h	
	Headers/primitive.h
	Headers/shader.h
	Headers/graph.h
	)


add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${PROJECT_SOURCE_DIR}/Headers
)


target_link_libraries(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/Libraries/glew32.lib)
target_link_libraries(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/Libraries/glew32s.lib)
target_link_libraries(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/Libraries/glfw3.lib)
target_link_libraries(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/Libraries/glfw3dll.lib)
target_link_libraries(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/Libraries/opengl32.lib)


add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_SOURCE_DIR}/Shaders $<TARGET_FILE_DIR:${PROJECT_NAME}>/Shaders)
					   
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_SOURCE_DIR}/DLibs $<TARGET_FILE_DIR:${PROJECT_NAME}>)					 
					   
set_target_properties(${PROJECT_NAME} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${PROJECT_BINARY_DIR}/Debug")