# Build the app, using the HAL

include_directories(include)
file(GLOB MY_SOURCES "src/*.c")
add_executable(motorSample ${MY_SOURCES})

# Make use of the HAL library
target_link_libraries(motorSample LINK_PRIVATE hal)

# Copy executable to final location (change `as1` to project name as needed)
add_custom_command(TARGET motorSample POST_BUILD 
  COMMAND "${CMAKE_COMMAND}" -E copy 
     "$<TARGET_FILE:motorSample>"
     "~/cmpt433/public/myApps/motorSample" 
  COMMENT "Copying ARM executable to public NFS directory")


# Copy the folder of node files to NFS
add_custom_command(TARGET motorSample POST_BUILD
COMMAND "${CMAKE_COMMAND}" -E copy_directory
"${CMAKE_SOURCE_DIR}/my-nodejs-app"
"~/cmpt433/public/myApps/controller-web"
COMMENT "Copying node files to public NFS directory")
#
# Add a custom command to run npm install

##add_custom_command(TARGET motorSample POST_BUILD
#   COMMAND ${CMAKE_COMMAND} -E chdir "~/cmpt433/public/myApps/controller-web" npm install
#   COMMENT "Installing required Node.js packages (This may take some time)"
#)
#/*