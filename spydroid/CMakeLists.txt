if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
  message(FATAL_ERROR "cmake must be invoked with the top level directory")
endif()

add_executable(spydroid
  features/vncviewer/fltk/Fl_Monitor_Arrangement.cxx
  features/vncviewer/fltk/Fl_Navigation.cxx
  features/vncviewer/fltk/theme.cxx
  features/vncviewer/menukey.cxx
  features/vncviewer/BaseTouchHandler.cxx
  features/vncviewer/CConn.cxx
  features/vncviewer/DesktopWindow.cxx
  features/vncviewer/EmulateMB.cxx
  features/vncviewer/UserDialog.cxx
  features/vncviewer/ServerDialog.cxx
  features/vncviewer/Surface.cxx
  features/vncviewer/OptionsDialog.cxx
  features/vncviewer/PlatformPixelBuffer.cxx
  features/vncviewer/Viewport.cxx
  features/vncviewer/parameters.cxx
  features/vncviewer/keysym2ucs.c
  features/vncviewer/touch.cxx
  features/vncviewer/MonitorIndicesParameter.cxx
  features/vncviewer/vncviewer.cxx
  app/src/main/net/spydroid/desktop/main.cpp
  app/src/main/net/spydroid/desktop/presentation/home.cpp
  app/src/main/net/spydroid/desktop/presentation/profile.cpp
  app/src/main/net/spydroid/desktop/data/VncConnect.cpp
  app/src/main/net/spydroid/desktop/models/VncData.h
  app/src/main/net/spydroid/desktop/data/colors.cpp
  app/src/main/net/spydroid/desktop/remote/network/api/ApiService.cpp
  app/src/main/net/spydroid/desktop/remote/network/data/DevicesDaoImp.cpp
  
)

if(WIN32 AND NOT CMAKE_BUILD_TYPE STREQUAL "Debug")
  set___properties(spydroid PROPERTIES WIN32_EXECUTABLE TRUE)
endif()

if(WIN32)
  target_include_directories(spydroid PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
  configure_file(vncviewer.rc.in spydroid.rc)
  target_sources(spydroid PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/spydroid.rc)
endif()

if(WIN32)
  target_sources(spydroid PRIVATE features/vncviewer/Win32TouchHandler.cxx features/vncviewer/win32.c)
elseif(APPLE)
  target_sources(spydroid PRIVATE features/vncviewer/cocoa.mm features/vncviewer/osx_to_qnum.c)
else()
  target_sources(spydroid PRIVATE features/vncviewer/GestureHandler.cxx features/vncviewer/XInputTouchHandler.cxx features/vncviewer/xkb_to_qnum.c)
endif()

if(WIN32)
  target_sources(spydroid PRIVATE features/vncviewer/Surface_Win32.cxx)
elseif(APPLE)
  target_sources(spydroid PRIVATE features/vncviewer/Surface_OSX.cxx)
else()
  target_sources(spydroid PRIVATE features/vncviewer/Surface_X11.cxx)
endif()

target_include_directories(spydroid SYSTEM PUBLIC ${FLTK_INCLUDE_DIR})
target_include_directories(spydroid SYSTEM PUBLIC ${GETTEXT_INCLUDE_DIR})
target_include_directories(spydroid PUBLIC ${CMAKE_SOURCE_DIR}/common)
target_link_libraries(spydroid rfb network rdr os ${FLTK_LIBRARIES} ${GETTEXT_LIBRARIES})
target_link_libraries(spydroid ${CURL_LIBRARIES})
target_link_libraries(spydroid  jsoncpp_lib)
if(WIN32)
  target_link_libraries(spydroid msimg32)
elseif(APPLE)
  target_link_libraries(spydroid "-framework Cocoa")
  target_link_libraries(spydroid "-framework Carbon")
  target_link_libraries(spydroid "-framework IOKit")
else()
  target_link_libraries(spydroid ${X11_Xi_LIB})

  if(X11_Xrandr_LIB)
    target_link_libraries(spydroid ${X11_Xrandr_LIB})
  endif()
endif()

install(TARGETS spydroid DESTINATION ${CMAKE_INSTALL_FULL_BINDIR})
