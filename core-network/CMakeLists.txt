#Copyright (C) 2024 Daniel Gómez (Less)
#
#This program is free software: you can redistribute it and/or modify
#it under the terms of the GNU General Public License as published by
#the Free Software Foundation, either version 3 of the License, or
#any later version.
#
#This program is distributed in the hope that it will be useful,
#but WITHOUT ANY WARRANTY; without even the implied warranty of
#MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
#GNU General Public License for more details.
#
#You should have received a copy of the GNU General Public License
#along with this program. If not, see <https://www.gnu.org/licenses/>.

set(SOURCE_DIR src/spydroid/network)

set(HEADERS
    ${SOURCE_DIR}/services/ApiService.h
    ${SOURCE_DIR}/services/DownloaderService.h
    ${SOURCE_DIR}/daos/DevicesDao.h
    ${SOURCE_DIR}/daos/InfoDao.h
    ${SOURCE_DIR}/daos/MultimediaDao.h
    ${SOURCE_DIR}/daos/SmsDao.h
    ${SOURCE_DIR}/models/Devices.h
    ${SOURCE_DIR}/models/Info.h
    ${SOURCE_DIR}/models/Multimedia.h
    ${SOURCE_DIR}/models/Sms.h
)

set(SOURCES
    ${SOURCE_DIR}/services/ApiService.cpp
    ${SOURCE_DIR}/services/DownloaderService.cpp
    ${SOURCE_DIR}/data/DevicesDaoImp.cpp
    ${SOURCE_DIR}/data/InfoDaoImp.cpp
    ${SOURCE_DIR}/data/MultimediaDaoImp.cpp
    ${SOURCE_DIR}/data/SmsDaoImp.cpp
)

qt5_wrap_cpp(MOC_SOURCES ${HEADERS})
add_library(core-network STATIC ${SOURCES} ${HEADERS} ${MOC_SOURCES})

target_include_directories(core-network PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(core-network JsonCpp::JsonCpp CURL::libcurl)
