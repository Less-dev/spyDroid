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

set(SOURCE_DIR src/spydroid/data)

set(HEADERS
    ${SOURCE_DIR}/domain/DevicesRepository.h
    ${SOURCE_DIR}/domain/InfoRepository.h
    ${SOURCE_DIR}/domain/MultimediaRepository.h
    ${SOURCE_DIR}/domain/SmsRepository.h
    ${SOURCE_DIR}/models/DevicesHandler.h
    ${SOURCE_DIR}/models/InfoHandler.h
    ${SOURCE_DIR}/models/MultimediaHandler.h
    ${SOURCE_DIR}/models/SmsHandler.h
    ${SOURCE_DIR}/local/SettingsManager.h
    ${SOURCE_DIR}/local/FilesManager.h
    ${SOURCE_DIR}/local/CleanManager.h
)

set(SOURCES
    ${SOURCE_DIR}/data/DevicesRepositoryImp.cpp
    ${SOURCE_DIR}/data/InfoRepositoryImp.cpp
    ${SOURCE_DIR}/data/MultimediaRepositoryImp.cpp
    ${SOURCE_DIR}/data/SmsRepositoryImp.cpp
    ${SOURCE_DIR}/local/SettingsManager.cpp
    ${SOURCE_DIR}/local/FilesManager.cpp
    ${SOURCE_DIR}/local/CleanManager.cpp
)

qt5_wrap_cpp(MOC_SOURCES ${HEADERS})
add_library(core-data STATIC ${SOURCES} ${HEADERS} ${MOC_SOURCES})

target_include_directories(core-data PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(core-data Qt5::Core zip archive) 
