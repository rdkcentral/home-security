/**
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2024 RDK Management
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
*/

#ifndef CCSP_HOME_SECURITY_MOCK_H
#define CCSP_HOME_SECURITY_MOCK_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <experimental/filesystem>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <mocks/mock_syscfg.h>
#include <mocks/mock_sysevent.h>
#include <mocks/mock_base_api.h>
#include <mocks/mock_rdkconfig.h>
#include <mocks/mock_libxml.h>
#include <mocks/mock_securewrapper.h>
#include <mocks/mock_socket.h>
#include <mocks/mock_file_io.h>
#include "mocks/mock_hdk_ccsp_mbus.h"

extern SyscfgMock *g_syscfgMock;
extern SyseventMock *g_syseventMock;
extern BaseAPIMock * g_baseapiMock;
extern rdkconfigMock *g_rdkconfigMock;
extern libxmlMock *g_libxmlMock;
extern SecureWrapperMock *g_securewrapperMock;
extern SocketMock *g_socketMock;
extern FileIOMock * g_fileIOMock;
extern HdkCcspMbusMock * g_HdkCcspMbusMock;

using namespace std;
using std::experimental::filesystem::exists;
using ::testing::_;
using ::testing::Return;
using ::testing::StrEq;
using ::testing::HasSubstr;
using ::testing::SetArgPointee;
using ::testing::DoAll;

extern "C" {
#include "chs_log.h"
#include "hdk.h"
#include "hdk_adi.h"
#include "hdk_context.h"
#include "hdk_data.h"
#include "hdk_encode.h"
#include "hdk_interface.h"
#include "hdk_internal.h"
#include "hdk_methods.h"
}

struct MBusObj_s {
    /* configuration */
    char    *subSystem;     /* sub-system: eRT, eMG, eGW ... */
    char    *confFile;      /* config file for ccsp message bus */
    char    *compId;        /* component ID of this module */
    char    *compCrId;      /* component ID of CR */

    /* internal use */
    void    *handle;
};

typedef struct _HDK_Member__INT__
{
    HDK_Member node;
    int iValue;
} HDK_Member__INT__;

typedef struct _HDK_Member__STRING__
{
    HDK_Member node;
    char* pszValue;
} HDK_Member__STRING__;

typedef struct _HDK_Member_IPAddress
{
    HDK_Member node;
    HDK_IPAddress ipAddress;
} HDK_Member_IPAddress;

typedef struct _HDK_Member_MACAddress
{
    HDK_Member node;
    HDK_MACAddress macAddress;
} HDK_Member_MACAddress;

#endif // CCSP_HOME_SECURITY_MOCK_H
