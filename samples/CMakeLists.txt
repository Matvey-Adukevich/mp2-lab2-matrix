## Get all cpp-files in the current directory
#file(GLOB samples_list RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)
#
## Remove files that should be libraries, not executables
##list(REMOVE_ITEM samples_list "main.cpp" "Road.cpp" "Svetofor.cpp")
#
#foreach(sample_filename ${samples_list})
#  # Get file name without extension
#  get_filename_component(sample ${sample_filename} NAME_WE)
#
#  # Add and configure executable file to be produced
#  add_executable(${sample} ${sample_filename})
#  #target_link_libraries(${sample} ${MP2_LIBRARY})
#  set_target_properties(${sample} PROPERTIES
#    OUTPUT_NAME "${sample}"
#    PROJECT_LABEL "${sample}"
#    RUNTIME_OUTPUT_DIRECTORY "../")
#endforeach()

# Now create static libraries for Road and Svetofor
#add_library(Road STATIC Road.cpp)
#add_library(Svetofor STATIC Svetofor.cpp)

# Create main executable that links with the libraries
#add_executable(main main.cpp)
#arget_link_libraries(main Road Svetofor ${MP2_LIBRARY})
#set_target_properties(main PROPERTIES
#  RUNTIME_OUTPUT_DIRECTORY "../")
# Get all cpp-files in the current directory
file(GLOB samples_list RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)

foreach(sample_filename ${samples_list})
  # Get file name without extension
  get_filename_component(sample ${sample_filename} NAME_WE)

  # Add and configure executable file to be produced
  add_executable(${sample} ${sample_filename})
  
  # «ј ќћћ≈Ќ“»–”… эту строку - она вызывает проблему с set.lib
  # target_link_libraries(${sample} ${MP2_LIBRARY})
  
  set_target_properties(${sample} PROPERTIES
    OUTPUT_NAME "${sample}"
    PROJECT_LABEL "${sample}"
    RUNTIME_OUTPUT_DIRECTORY "../")
endforeach()