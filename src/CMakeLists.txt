
# libchauder.so source files
AUX_SOURCE_DIRECTORY(. CHAUDER_SOURCES) 

add_library(chauder SHARED ${CHAUDER_SOURCES})
target_include_directories(chauder PRIVATE include/)

# Add the public headers
target_include_directories(chauder PUBLIC interface/)
