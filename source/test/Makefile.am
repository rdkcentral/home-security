#
# If not stated otherwise in this file or this component's LICENSE file the
# following copyright and licenses apply:
#
# Copyright 2024 RDK Management
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

AM_CFLAGS =

AM_CXXFLAGS = -std=c++11

AUTOMAKE_OPTIONS = subdir-objects

ACLOCAL_AMFLAGS = -I m4

bin_PROGRAMS = CcspHomeSecurity_gtest.bin

CcspHomeSecurity_gtest_bin_CPPFLAGS = -I$(PKG_CONFIG_SYSROOT_DIR)$(includedir)/gtest \
                                      -I${top_srcdir}/gtest/include \
                                      -I${top_srcdir}/source/Ssp

CcspHomeSecurity_gtest_bin_CPPFLAGS += -DUNIT_TEST_DOCKER_SUPPORT \
                                       -DHDK_METHOD_PN_GETWLANRADIOSETTINGS \
                                       -DHDK_METHOD_PN_SETDEVICESETTINGS2 \
                                       -DHDK_METHOD_PN_SETROUTERSETTINGS

CcspHomeSecurity_gtest_bin_SOURCES = ${top_builddir}/source/Ssp/hdk.c \
                                     ${top_builddir}/source/Ssp/hdk_adi.c \
                                     ${top_builddir}/source/Ssp/hdk_context.c \
                                     ${top_builddir}/source/Ssp/hdk_data.c \
                                     ${top_builddir}/source/Ssp/hdk_device.c \
                                     ${top_builddir}/source/Ssp/hdk_encode.c \
                                     ${top_builddir}/source/Ssp/hdk_methods.c \
                                     ${top_builddir}/source/Ssp/hnapd.c \
                                     mocks/mock_hdk_ccsp_mbus.cpp \
                                     CcspHomeSecurityMock.cpp \
                                     hnapd_test.cpp \
                                     hdk_adi_test.cpp \
                                     hdk_encode_test.cpp \
                                     hdk_test.cpp \
                                     hdk_context_test.cpp \
                                     hdk_device_GetValue_test.cpp \
                                     hdk_device_test.cpp \
                                     gtest_main.cpp

CcspHomeSecurity_gtest_bin_LDFLAGS = -lgtest -lgmock -lgcov -pthread

CcspHomeSecurity_gtest_bin_LDADD = $(HOME)/usr/local/lib/libmock_ccsp_common.la \
                                   $(HOME)/usr/local/lib/libmock_sysevent.la \
                                   $(HOME)/usr/local/lib/libmock_syscfg.la \
                                   $(HOME)/usr/local/lib/libmock_rdkconfig.la \
                                   $(HOME)/usr/local/lib/libmock_libxml.la \
                                   $(HOME)/usr/local/lib/libmock_secure_wrapper.la \
                                   $(HOME)/usr/local/lib/libmock_socket.la \
                                   $(HOME)/usr/local/lib/libmock_file_io.la


#Code Coverage Flags
AM_CFLAGS += -fprofile-arcs -ftest-coverage
AM_CXXFLAGS += -fprofile-arcs -ftest-coverage
CcspHomeSecurity_gtest_bin_LDFLAGS += --coverage

