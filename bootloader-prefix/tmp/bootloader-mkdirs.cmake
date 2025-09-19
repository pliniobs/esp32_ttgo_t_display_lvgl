# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

# If CMAKE_DISABLE_SOURCE_CHANGES is set to true and the source directory is an
# existing directory in our source tree, calling file(MAKE_DIRECTORY) on it
# would cause a fatal error, even though it would be a no-op.
if(NOT EXISTS "/home/plinio/esp/esp-idf/components/bootloader/subproject")
  file(MAKE_DIRECTORY "/home/plinio/esp/esp-idf/components/bootloader/subproject")
endif()
file(MAKE_DIRECTORY
  "/home/plinio/workspace_esp/ttgo_TDisplay_LVGL/bootloader"
  "/home/plinio/workspace_esp/ttgo_TDisplay_LVGL/bootloader-prefix"
  "/home/plinio/workspace_esp/ttgo_TDisplay_LVGL/bootloader-prefix/tmp"
  "/home/plinio/workspace_esp/ttgo_TDisplay_LVGL/bootloader-prefix/src/bootloader-stamp"
  "/home/plinio/workspace_esp/ttgo_TDisplay_LVGL/bootloader-prefix/src"
  "/home/plinio/workspace_esp/ttgo_TDisplay_LVGL/bootloader-prefix/src/bootloader-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/plinio/workspace_esp/ttgo_TDisplay_LVGL/bootloader-prefix/src/bootloader-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/plinio/workspace_esp/ttgo_TDisplay_LVGL/bootloader-prefix/src/bootloader-stamp${cfgdir}") # cfgdir has leading slash
endif()
