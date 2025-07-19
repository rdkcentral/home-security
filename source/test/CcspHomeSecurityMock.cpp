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

#include "CcspHomeSecurityMock.h"

SyscfgMock *g_syscfgMock = nullptr;
SyseventMock *g_syseventMock = nullptr;
BaseAPIMock * g_baseapiMock = nullptr;
rdkconfigMock *g_rdkconfigMock = nullptr;
libxmlMock *g_libxmlMock = nullptr;
SecureWrapperMock *g_securewrapperMock = nullptr;
SocketMock *g_socketMock = nullptr;
FileIOMock * g_fileIOMock = nullptr;
HdkCcspMbusMock * g_HdkCcspMbusMock = nullptr;

HDK_Context* createMockHDK_Context() {
    HDK_Context* mockContext = (HDK_Context*)malloc(sizeof(HDK_Context));

    // Create temporary files for request and response
    mockContext->fhRequest = tmpfile();
    mockContext->fhResponse = tmpfile();

    if (!mockContext->fhRequest || !mockContext->fhResponse) {
        printf("Failed to create temporary file streams!\n");
        free(mockContext);
        return NULL;
    }

    mockContext->fReboot = 1;
    mockContext->mbus = (MBusObj_t*)malloc(sizeof(MBusObj_s));

    return mockContext;
}
