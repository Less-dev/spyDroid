# Check for Json
find_package(jsoncpp REQUIRED)

# Check Qt5
find_package(Qt5 COMPONENTS Widgets REQUIRED)

# Cehck Curl 
find_package(CURL REQUIRED)

set(HEADERS
    app/src/main/net/spydroid/desktop/presentation/home.h
    app/src/main/net/spydroid/desktop/presentation/profile.h
)

include_directories(app/src/main/net/spydroid/desktop/presentation)

# Añadir los archivos para el moc (necesario cuando se usa Q_OBJECT)
qt5_wrap_cpp(MOC_SOURCES ${HEADERS})

add_executable(spydroid
  app/src/main/net/spydroid/desktop/main.cpp
  app/src/main/net/spydroid/desktop/presentation/home.cpp
  app/src/main/net/spydroid/desktop/presentation/profile.cpp
  app/src/main/net/spydroid/desktop/data/colors.cpp
  app/src/main/net/spydroid/desktop/remote/network/api/ApiService.cpp
  app/src/main/net/spydroid/desktop/remote/network/data/DevicesDaoImp.cpp
  app/src/main/net/spydroid/desktop/remote/data/DevicesRepositoryImp.cpp
  app/src/main/net/spydroid/desktop/components/goBack.cpp
  ${SOURCES} ${HEADERS} ${MOC_SOURCES}
)

qt5_add_resources(RESOURCES app/src/main/net/spydroid/desktop/resources.qrc)
target_sources(spydroid PRIVATE ${RESOURCES})

target_link_libraries(spydroid ${FLTK_LIBRARIES} ${GETTEXT_LIBRARIES} ${CURL_LIBRARIES} jsoncpp_lib Qt5::Widgets)

install(TARGETS spydroid DESTINATION ${CMAKE_INSTALL_FULL_BINDIR})
