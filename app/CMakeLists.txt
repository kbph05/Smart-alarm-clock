# Build the app, using the HAL

include_directories(include)
file(GLOB MY_SOURCES "src/*.c")
add_executable(out ${MY_SOURCES})

# Make use of the HAL library
target_link_libraries(out LINK_PRIVATE hal)

# Copy executable to final location (change `hello_world` to project name as needed)
add_custom_command(TARGET out POST_BUILD 
  COMMAND "${CMAKE_COMMAND}" -E copy 
     "$<TARGET_FILE:out>"
     "${CMAKE_CURRENT_SOURCE_DIR}/Smart-alarm-clock" # puts the executable in the same directory as the project for now
  COMMAND "${CMAKE_COMMAND}" -E copy 
     "$<TARGET_FILE:out>"
     "~/ensc351/public/smart-alarm-clock" # puts ARM executable to public NFS directory
  COMMENT "Copying ARM executable to public NFS directory")
