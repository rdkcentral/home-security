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
#include "mock_hdk_ccsp_mbus.h"

using namespace std;

extern HdkCcspMbusMock * g_HdkCcspMbusMock;

extern "C" int MBus_GetParamVal(MBusObj_t *mbus, const char *path, char *val, int size) {
    if (!g_HdkCcspMbusMock) {
        return -1;
    }
    return g_HdkCcspMbusMock->MBus_GetParamVal(mbus, path, val, size);
}

extern "C" int MBus_SetParamVal(MBusObj_t *mbus, const char *path, MBusParamType_t type, const char *val, int commit) {
    if (!g_HdkCcspMbusMock) {
        return -1;
    }
    return g_HdkCcspMbusMock->MBus_SetParamVal(mbus, path, type, val, commit);
}

extern "C" int MBus_Commit(MBusObj_t *mbus, const char *path) {
    if (!g_HdkCcspMbusMock) {
        return -1;
    }
    return g_HdkCcspMbusMock->MBus_Commit(mbus, path);
}

extern "C" int MBus_FindObjectIns(MBusObj_t *mbus, const char *objPath, const char *paramName, const char *paramVal, char insPath[][MAX_PATH_NAME], int *insNum) {
    if (!g_HdkCcspMbusMock) {
        return -1;
    }
    return g_HdkCcspMbusMock->MBus_FindObjectIns(mbus, objPath, paramName, paramVal, insPath, insNum);
}

extern "C" int MBus_AddObjectIns(MBusObj_t *mbus, const char *objPath, int *ins) {
    if (!g_HdkCcspMbusMock) {
        return -1;
    }
    return g_HdkCcspMbusMock->MBus_AddObjectIns(mbus, objPath, ins);
}

extern "C" int MBus_SetParamVect(MBusObj_t *mbus, const char *object, const MBusParam_t params[], int num, int commit) {
    if (!g_HdkCcspMbusMock) {
        return -1;
    }
    return g_HdkCcspMbusMock->MBus_SetParamVect(mbus, object, params, num, commit);
}

extern "C" int MBus_DelObjectIns(MBusObj_t *mbus, const char *objPath, int ins) {
    if (!g_HdkCcspMbusMock) {
        return -1;
    }
    return g_HdkCcspMbusMock->MBus_DelObjectIns(mbus, objPath, ins);
}

extern "C" MBusObj_t * MBus_Create(const char *subSystem, const char *confFile, const char *compId, const char *compCrId) {
    if (!g_HdkCcspMbusMock) {
        return nullptr;
    }
    return g_HdkCcspMbusMock->MBus_Create(subSystem, confFile, compId, compCrId);
}