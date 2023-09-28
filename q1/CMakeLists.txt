cmake_minimum_required(VERSION 2.8)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin") 
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
SET(OpenCV_DIR ~/mahdi/local/include/opencv4)
project( embeddedServer )
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )




add_executable( embeddedServer src/embeddedServer.cpp  )
target_link_libraries(  embeddedServer ${OpenCV_LIBS} -L/usr/lib/x86_64-linux-gnu -lmysqlclient -lpthread -lz -lm -lrt -latomic -lssl -lcrypto -ldl 
-I/usr/include/mysql -lm -lasound  paho-mqtt3c   )


add_executable( webServer src/webServer.cpp  )
target_link_libraries(  webServer -L/usr/lib/x86_64-linux-gnu -lmysqlclient -lpthread -lz -lm -lrt -latomic -lssl -lcrypto -ldl
-I/usr/include/mysql   )
