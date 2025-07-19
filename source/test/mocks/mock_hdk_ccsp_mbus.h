/*************************************************************************
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
**************************************************************************/
#ifndef HDK_CCSP_MBUS_MOCK_H
#define HDK_CCSP_MBUS_MOCK_H

#include <gtest/gtest.h>
#include <gmock/gmock.h>

extern "C"
{
#include "hdk_ccsp_mbus.h"
}

class HdkCcspMbusInterface
{
    public:
        virtual ~HdkCcspMbusInterface() {}
        virtual int MBus_GetParamVal(MBusObj_t *, const char *, char *, int) = 0;
        virtual int MBus_SetParamVal(MBusObj_t *, const char *, MBusParamType_t , const char *, int) = 0;
        virtual int MBus_Commit(MBusObj_t *, const char *) = 0;
        virtual int MBus_FindObjectIns(MBusObj_t *, const char *, const char *, const char *, char[][MAX_PATH_NAME], int *) = 0;
        virtual int MBus_AddObjectIns(MBusObj_t *mbus, const char *objPath, int *ins) = 0;
        virtual int MBus_SetParamVect(MBusObj_t *, const char *, const MBusParam_t[], int , int ) = 0;
        virtual int MBus_DelObjectIns(MBusObj_t *mbus, const char *objPath, int ins) = 0;
        virtual MBusObj_t * MBus_Create(const char *, const char *, const char *, const char *) = 0;
};

class HdkCcspMbusMock : public HdkCcspMbusInterface
{
    public:
        virtual ~HdkCcspMbusMock() {}
        MOCK_METHOD4(MBus_GetParamVal, int(MBusObj_t *, const char *, char *, int ));
        MOCK_METHOD5(MBus_SetParamVal, int(MBusObj_t *, const char *, MBusParamType_t, const char *, int));
        MOCK_METHOD2(MBus_Commit, int(MBusObj_t *, const char *));
        MOCK_METHOD6(MBus_FindObjectIns, int(MBusObj_t *, const char *, const char *, const char *, char[][MAX_PATH_NAME], int *));
        MOCK_METHOD3(MBus_AddObjectIns, int(MBusObj_t *, const char *, int *));
        MOCK_METHOD5(MBus_SetParamVect, int(MBusObj_t *, const char *, const MBusParam_t[], int, int));
        MOCK_METHOD3(MBus_DelObjectIns, int(MBusObj_t *, const char *, int));
        MOCK_METHOD4(MBus_Create, MBusObj_t *(const char *, const char *, const char *, const char *));
};
#endif