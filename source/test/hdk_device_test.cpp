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

class CcspHomeSecurityHDKDeviceFixture : public ::testing::Test {
protected:
    void SetUp() override {
        g_syscfgMock = new SyscfgMock();
        g_baseapiMock = new BaseAPIMock();
        g_HdkCcspMbusMock = new HdkCcspMbusMock();
    }

    void TearDown() override {
        delete g_syscfgMock;
        delete g_baseapiMock;
        delete g_HdkCcspMbusMock;
        g_syscfgMock = nullptr;
        g_baseapiMock = nullptr;
        g_HdkCcspMbusMock = nullptr;
    }
};

extern HDK_Context* createMockHDK_Context();

TEST_F(CcspHomeSecurityHDKDeviceFixture, HDK_Device_Read) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    char pBuf[] = "Data";
    int cbBuf = strlen(pBuf);

    int result = HDK_Device_Read((void*)mockDeviceCtx, pBuf, cbBuf);
    EXPECT_EQ(result, 0);
}

TEST_F(CcspHomeSecurityHDKDeviceFixture, HDK_Device_PrepareWrite) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_Enum_Result result =  HDK_Enum_Result_OK;

    HDK_Device_PrepareWrite((void*)mockDeviceCtx, &result);
    EXPECT_EQ(result, HDK_Enum_Result_REBOOT);
}

TEST_F(CcspHomeSecurityHDKDeviceFixture, HDK_Device_Write) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    char pBuf[] = "Data";
    int cbBuf = strlen(pBuf);

    HDK_Device_Write((void*)mockDeviceCtx, pBuf, cbBuf);
}

TEST_F(CcspHomeSecurityHDKDeviceFixture, HDK_Device_ValidateValue_PortMappings) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_PortMappings;

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    HDK_Member__INT__* pMember = (HDK_Member__INT__*) malloc(sizeof(HDK_Member__INT__));
    ASSERT_NE(pMember, nullptr);

    pMember->node.element = HDK_Element_PN_PortMappingProtocol;
    pMember->node.type = HDK_Type_PN_IPProtocol;
    pMember->node.pNext = nullptr;
    pMember->iValue = HDK_Enum_PN_IPProtocol_UDP;

    pStruct->pHead = (HDK_Member*)pMember;
    pStruct->pTail = (HDK_Member*)pMember;

    int result = HDK_Device_ValidateValue((void*)mockDeviceCtx, eValue, pStruct);
    EXPECT_EQ(result, 1);

    free(pMember);
    free(pStruct);
    pMember = nullptr;
    pStruct = nullptr;
}

TEST_F(CcspHomeSecurityHDKDeviceFixture, HDK_Device_ValidateValue_WLanKeyRenewal) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WLanKeyRenewal;

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    HDK_Member__INT__* pMember = (HDK_Member__INT__*) malloc(sizeof(HDK_Member__INT__));
    ASSERT_NE(pMember, nullptr);

    pMember->node.element = HDK_Element_PN_KeyRenewal;
    pMember->node.type = HDK_Type__INT__;
    pMember->node.pNext = nullptr;
    pMember->iValue = 1;

    pStruct->pHead = (HDK_Member*)pMember;
    pStruct->pTail = (HDK_Member*)pMember;

    int result = HDK_Device_ValidateValue((void*)mockDeviceCtx, eValue, pStruct);
    EXPECT_EQ(result, 1);

    free(pStruct);
    free(pMember);
    pMember = nullptr;
    pStruct = nullptr;
}

TEST_F(CcspHomeSecurityHDKDeviceFixture, HDK_Device_ValidateValue_DeviceName) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_DeviceName;

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    HDK_Member__STRING__* pMember = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember, nullptr);

    pMember->node.element = HDK_Element_PN_DeviceName;
    pMember->node.type = HDK_Type__STRING__;
    pMember->node.pNext = nullptr;
    pMember->pszValue = strdup("testDevice");

    pStruct->pHead = (HDK_Member*)pMember;
    pStruct->pTail = (HDK_Member*)pMember;

    int result = HDK_Device_ValidateValue((void*)mockDeviceCtx, eValue, pStruct);
    EXPECT_EQ(result, 1);

    free(pMember);
    free(pStruct);
    pMember = nullptr;
    pStruct = nullptr;
}

TEST_F(CcspHomeSecurityHDKDeviceFixture, HDK_Device_ValidateValue_AdminPassword) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_AdminPassword;

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    if (!pStruct) {
        printf("Memory allocation failed for pStruct!\n");
        return;
    }

    HDK_Member__STRING__* pMember = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember, nullptr);

    pMember->node.element = HDK_Element_PN_AdminPassword;
    pMember->node.type = HDK_Type__STRING__;
    pMember->node.pNext = nullptr;
    pMember->pszValue = strdup("password");

    pStruct->pHead = (HDK_Member*)pMember;
    pStruct->pTail = (HDK_Member*)pMember;

    int result = HDK_Device_ValidateValue((void*)mockDeviceCtx, eValue, pStruct);
    EXPECT_EQ(result, 1);

    free(pMember);
    free(pStruct);
    pMember = nullptr;
    pStruct = nullptr;
}

TEST_F(CcspHomeSecurityHDKDeviceFixture, HDK_Device_ValidateValue_Locale) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_Locale;

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    if (!pStruct) {
        printf("Memory allocation failed for pStruct!\n");
        return;
    }

    HDK_Member* pMember = (HDK_Member*) malloc (sizeof(HDK_Member));
    if (!pMember) {
        printf("Memory allocation failed for pMember!\n");
        free(pStruct);
        return;
    }

    pMember->element = HDK_Element_PN_Locale;
    pMember->type = HDK_Type__STRING__;
    pMember->pNext = nullptr;

    pStruct->pHead = pMember;
    pStruct->pTail = pMember;

    int result = HDK_Device_ValidateValue((void*)mockDeviceCtx, eValue, pStruct);
    EXPECT_EQ(result, 0);

    free(pMember);
    free(pStruct);
    pMember = nullptr;
    pStruct = nullptr;
}

TEST_F(CcspHomeSecurityHDKDeviceFixture, HDK_Device_ValidateValue_WanIP) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WanIP;
    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    if (!pStruct) {
        printf("Memory allocation failed for pStruct!\n");
        return;
    }

    int result = HDK_Device_ValidateValue((void*)mockDeviceCtx, eValue, pStruct);
    EXPECT_EQ(result, 1);

    free(pStruct);
    pStruct = nullptr;
}

TEST_F(CcspHomeSecurityHDKDeviceFixture, HDK_Stop_HomeSecurity_Bridge_SUCCESS) {
    int result;
    char mockPath1[] = "Device.Bridging.Bridge.1";
    char mockPath2[] = "Device.Bridging.Bridge.2";
    char mockPort1[] = "1";
    char mockPort2[] = "2";
    char mockTrue[] = "true";
    char mockFalse[] = "false";
    MBusObj_t* ccsp_bus = (MBusObj_t*)malloc(sizeof(MBusObj_s));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityBridge"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPath2, mockPath2 + strlen(mockPath2) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityBridgePorts"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPort2, mockPort2 + strlen(mockPort2) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.Bridging.Bridge.2.Port.2.Enable"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockTrue, mockTrue + strlen(mockTrue) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_SetParamVal(_, StrEq("Device.Bridging.Bridge.2.Port.2.Enable"), _, _, _))
    .Times(1).WillOnce(Return(0));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.PrimaryLANBridge"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPath1, mockPath1 + strlen(mockPath1) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.PrimaryLANBridgeHSPorts"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPort1, mockPort1 + strlen(mockPort1) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.Bridging.Bridge.1.Port.1.Enable"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockFalse, mockFalse + strlen(mockFalse) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_SetParamVal(_, StrEq("Device.Bridging.Bridge.1.Port.1.Enable"), _, _, _))
    .Times(1).WillOnce(Return(0));


    result = HDK_Stop_HomeSecurity_Bridge(ccsp_bus);

    EXPECT_EQ(result, 0);
}

TEST_F(CcspHomeSecurityHDKDeviceFixture, HDK_Stop_HomeSecurity_Bridge_FAIL_1) {
    int result;
    MBusObj_t* ccsp_bus = nullptr;

    result = HDK_Stop_HomeSecurity_Bridge(ccsp_bus);

    EXPECT_EQ(result, -1);
}

TEST_F(CcspHomeSecurityHDKDeviceFixture, HDK_Stop_HomeSecurity_Bridge_FAIL_2) {
    int result;
    MBusObj_t* ccsp_bus = (MBusObj_t*)malloc(sizeof(MBusObj_s));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, _, _, _)).Times(1).WillOnce(Return(1));

    result = HDK_Stop_HomeSecurity_Bridge(ccsp_bus);

    EXPECT_EQ(result, -1);
}

TEST_F(CcspHomeSecurityHDKDeviceFixture, HDK_Stop_HomeSecurity_Bridge_FAIL_3) {
    int result;
    char mockPath2[] = "Device.Bridging.Bridge.2";
    MBusObj_t* ccsp_bus = (MBusObj_t*)malloc(sizeof(MBusObj_s));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityBridge"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPath2, mockPath2 + strlen(mockPath2) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityBridgePorts"), _, _))
    .Times(1).WillOnce(Return(1));

    result = HDK_Stop_HomeSecurity_Bridge(ccsp_bus);

    EXPECT_EQ(result, -1);
}

TEST_F(CcspHomeSecurityHDKDeviceFixture, HDK_Stop_HomeSecurity_Bridge_FAIL_4) {
    int result;
    char mockPath2[] = "Device.Bridging.Bridge.2";
    char mockPort2[] = "2";
    MBusObj_t* ccsp_bus = (MBusObj_t*)malloc(sizeof(MBusObj_s));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityBridge"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPath2, mockPath2 + strlen(mockPath2) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityBridgePorts"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPort2, mockPort2 + strlen(mockPort2) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.Bridging.Bridge.2.Port.2.Enable"), _, _))
    .Times(1).WillOnce(Return(1));

    result = HDK_Stop_HomeSecurity_Bridge(ccsp_bus);

    EXPECT_EQ(result, -1);
}

TEST_F(CcspHomeSecurityHDKDeviceFixture, HDK_Stop_HomeSecurity_Bridge_FAIL_5) {
    int result;
    char mockPath2[] = "Device.Bridging.Bridge.2";
    char mockPort2[] = "2";
    char mockTrue[] = "true";
    MBusObj_t* ccsp_bus = (MBusObj_t*)malloc(sizeof(MBusObj_s));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityBridge"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPath2, mockPath2 + strlen(mockPath2) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityBridgePorts"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPort2, mockPort2 + strlen(mockPort2) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.Bridging.Bridge.2.Port.2.Enable"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockTrue, mockTrue + strlen(mockTrue) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_SetParamVal(_, StrEq("Device.Bridging.Bridge.2.Port.2.Enable"), _, _, _))
    .Times(1).WillOnce(Return(1));

    result = HDK_Stop_HomeSecurity_Bridge(ccsp_bus);

    EXPECT_EQ(result, -1);
}

TEST_F(CcspHomeSecurityHDKDeviceFixture, HDK_Stop_HomeSecurity_Bridge_FAIL_6) {
    int result;
    char mockPath2[] = "Device.Bridging.Bridge.2";
    char mockPort2[] = "2";
    char mockTrue[] = "true";
    MBusObj_t* ccsp_bus = (MBusObj_t*)malloc(sizeof(MBusObj_s));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityBridge"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPath2, mockPath2 + strlen(mockPath2) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityBridgePorts"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPort2, mockPort2 + strlen(mockPort2) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.Bridging.Bridge.2.Port.2.Enable"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockTrue, mockTrue + strlen(mockTrue) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_SetParamVal(_, StrEq("Device.Bridging.Bridge.2.Port.2.Enable"), _, _, _))
    .Times(1).WillOnce(Return(0));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.PrimaryLANBridge"), _, _))
    .Times(1).WillOnce(Return(1));

    result = HDK_Stop_HomeSecurity_Bridge(ccsp_bus);

    EXPECT_EQ(result, -1);
}

TEST_F(CcspHomeSecurityHDKDeviceFixture, HDK_Stop_HomeSecurity_Bridge_FAIL_7) {
    int result;
    char mockPath1[] = "Device.Bridging.Bridge.1";
    char mockPath2[] = "Device.Bridging.Bridge.2";
    char mockPort2[] = "2";
    char mockTrue[] = "true";
    MBusObj_t* ccsp_bus = (MBusObj_t*)malloc(sizeof(MBusObj_s));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityBridge"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPath2, mockPath2 + strlen(mockPath2) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityBridgePorts"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPort2, mockPort2 + strlen(mockPort2) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.Bridging.Bridge.2.Port.2.Enable"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockTrue, mockTrue + strlen(mockTrue) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_SetParamVal(_, StrEq("Device.Bridging.Bridge.2.Port.2.Enable"), _, _, _))
    .Times(1).WillOnce(Return(0));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.PrimaryLANBridge"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPath1, mockPath1 + strlen(mockPath1) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.PrimaryLANBridgeHSPorts"), _, _))
    .Times(1).WillOnce(Return(1));

    result = HDK_Stop_HomeSecurity_Bridge(ccsp_bus);

    EXPECT_EQ(result, -1);
}

TEST_F(CcspHomeSecurityHDKDeviceFixture, HDK_Stop_HomeSecurity_Bridge_FAIL_8) {
    int result;
    char mockPath1[] = "Device.Bridging.Bridge.1";
    char mockPath2[] = "Device.Bridging.Bridge.2";
    char mockPort1[] = "1";
    char mockPort2[] = "2";
    char mockTrue[] = "true";
    MBusObj_t* ccsp_bus = (MBusObj_t*)malloc(sizeof(MBusObj_s));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityBridge"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPath2, mockPath2 + strlen(mockPath2) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityBridgePorts"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPort2, mockPort2 + strlen(mockPort2) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.Bridging.Bridge.2.Port.2.Enable"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockTrue, mockTrue + strlen(mockTrue) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_SetParamVal(_, StrEq("Device.Bridging.Bridge.2.Port.2.Enable"), _, _, _))
    .Times(1).WillOnce(Return(0));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.PrimaryLANBridge"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPath1, mockPath1 + strlen(mockPath1) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.PrimaryLANBridgeHSPorts"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPort1, mockPort1 + strlen(mockPort1) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.Bridging.Bridge.1.Port.1.Enable"), _, _))
    .Times(1).WillOnce(Return(1));

    result = HDK_Stop_HomeSecurity_Bridge(ccsp_bus);

    EXPECT_EQ(result, -1);
}

TEST_F(CcspHomeSecurityHDKDeviceFixture, HDK_Stop_HomeSecurity_Bridge_FAIL_9) {
    int result;
    char mockPath1[] = "Device.Bridging.Bridge.1";
    char mockPath2[] = "Device.Bridging.Bridge.2";
    char mockPort1[] = "1";
    char mockPort2[] = "2";
    char mockTrue[] = "true";
    char mockFalse[] = "false";
    MBusObj_t* ccsp_bus = (MBusObj_t*)malloc(sizeof(MBusObj_s));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityBridge"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPath2, mockPath2 + strlen(mockPath2) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityBridgePorts"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPort2, mockPort2 + strlen(mockPort2) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.Bridging.Bridge.2.Port.2.Enable"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockTrue, mockTrue + strlen(mockTrue) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_SetParamVal(_, StrEq("Device.Bridging.Bridge.2.Port.2.Enable"), _, _, _))
    .Times(1).WillOnce(Return(0));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.PrimaryLANBridge"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPath1, mockPath1 + strlen(mockPath1) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.PrimaryLANBridgeHSPorts"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPort1, mockPort1 + strlen(mockPort1) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.Bridging.Bridge.1.Port.1.Enable"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockFalse, mockFalse + strlen(mockFalse) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_SetParamVal(_, StrEq("Device.Bridging.Bridge.1.Port.1.Enable"), _, _, _))
    .Times(1).WillOnce(Return(1));

    result = HDK_Stop_HomeSecurity_Bridge(ccsp_bus);

    EXPECT_EQ(result, -1);
}

TEST_F(CcspHomeSecurityHDKDeviceFixture, HDK_Start_HomeSecurity_Bridge_SUCCESS) {
    int result;
    char mockPath1[] = "Device.Bridging.Bridge.1";
    char mockPath2[] = "Device.Bridging.Bridge.2";
    char mockPort1[] = "1";
    char mockPort2[] = "2";
    char mockTrue[] = "true";
    char mockFalse[] = "false";
    MBusObj_t* ccsp_bus = (MBusObj_t*)malloc(sizeof(MBusObj_s));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.PrimaryLANBridge"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPath1, mockPath1 + strlen(mockPath1) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.PrimaryLANBridgeHSPorts"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPort1, mockPort1 + strlen(mockPort1) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.Bridging.Bridge.1.Port.1.Enable"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockTrue, mockTrue + strlen(mockTrue) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityBridge"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPath2, mockPath2 + strlen(mockPath2) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityBridgePorts"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPort2, mockPort2 + strlen(mockPort2) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.Bridging.Bridge.2.Port.2.Enable"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockFalse, mockFalse + strlen(mockTrue) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_SetParamVal(_, _, _, _, _)).WillRepeatedly(Return(0));

    result = HDK_Start_HomeSecurity_Bridge(ccsp_bus);

    EXPECT_EQ(result, 0);
}

TEST_F(CcspHomeSecurityHDKDeviceFixture, HDK_Start_HomeSecurity_Bridge_FAIL_1) {
    int result;
    MBusObj_t* ccsp_bus = nullptr;

    result = HDK_Start_HomeSecurity_Bridge(ccsp_bus);

    EXPECT_EQ(result, -1);
}

TEST_F(CcspHomeSecurityHDKDeviceFixture, HDK_Start_HomeSecurity_Bridge_FAIL_2) {
    int result;
    MBusObj_t* ccsp_bus = (MBusObj_t*)malloc(sizeof(MBusObj_s));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, _, _, _))
    .Times(1).WillOnce(Return(1));

    result = HDK_Start_HomeSecurity_Bridge(ccsp_bus);

    EXPECT_EQ(result, -1);
}

TEST_F(CcspHomeSecurityHDKDeviceFixture, HDK_Start_HomeSecurity_Bridge_FAIL_3) {
    int result;
    char mockPath1[] = "Device.Bridging.Bridge.1";
    MBusObj_t* ccsp_bus = (MBusObj_t*)malloc(sizeof(MBusObj_s));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.PrimaryLANBridge"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPath1, mockPath1 + strlen(mockPath1) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.PrimaryLANBridgeHSPorts"), _, _))
    .Times(1).WillOnce(Return(1));

    result = HDK_Start_HomeSecurity_Bridge(ccsp_bus);

    EXPECT_EQ(result, -1);
}

TEST_F(CcspHomeSecurityHDKDeviceFixture, HDK_Start_HomeSecurity_Bridge_FAIL_4) {
    int result;
    char mockPath1[] = "Device.Bridging.Bridge.1";
    char mockPort1[] = "1";
    MBusObj_t* ccsp_bus = (MBusObj_t*)malloc(sizeof(MBusObj_s));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.PrimaryLANBridge"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPath1, mockPath1 + strlen(mockPath1) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.PrimaryLANBridgeHSPorts"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPort1, mockPort1 + strlen(mockPort1) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.Bridging.Bridge.1.Port.1.Enable"), _, _))
    .Times(1).WillOnce(Return(1));

    result = HDK_Start_HomeSecurity_Bridge(ccsp_bus);

    EXPECT_EQ(result, -1);
}

TEST_F(CcspHomeSecurityHDKDeviceFixture, HDK_Start_HomeSecurity_Bridge_FAIL_5) {
    int result;
    char mockPath1[] = "Device.Bridging.Bridge.1";
    char mockPort1[] = "1";
    char mockTrue[] = "true";
    MBusObj_t* ccsp_bus = (MBusObj_t*)malloc(sizeof(MBusObj_s));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.PrimaryLANBridge"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPath1, mockPath1 + strlen(mockPath1) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.PrimaryLANBridgeHSPorts"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPort1, mockPort1 + strlen(mockPort1) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.Bridging.Bridge.1.Port.1.Enable"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockTrue, mockTrue + strlen(mockTrue) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_SetParamVal(_, StrEq("Device.Bridging.Bridge.1.Port.1.Enable"), _, _, _))
    .Times(1).WillOnce(Return(1));

    result = HDK_Start_HomeSecurity_Bridge(ccsp_bus);

    EXPECT_EQ(result, -1);
}

TEST_F(CcspHomeSecurityHDKDeviceFixture, HDK_Start_HomeSecurity_Bridge_FAIL_6) {
    int result;
    char mockPath1[] = "Device.Bridging.Bridge.1";
    char mockPort1[] = "1";
    char mockTrue[] = "true";
    MBusObj_t* ccsp_bus = (MBusObj_t*)malloc(sizeof(MBusObj_s));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.PrimaryLANBridge"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPath1, mockPath1 + strlen(mockPath1) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.PrimaryLANBridgeHSPorts"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPort1, mockPort1 + strlen(mockPort1) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.Bridging.Bridge.1.Port.1.Enable"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockTrue, mockTrue + strlen(mockTrue) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_SetParamVal(_, StrEq("Device.Bridging.Bridge.1.Port.1.Enable"), _, _, _))
    .Times(1).WillOnce(Return(0));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityBridge"), _, _))
    .Times(1).WillOnce(Return(1));

    result = HDK_Start_HomeSecurity_Bridge(ccsp_bus);

    EXPECT_EQ(result, -1);
}

TEST_F(CcspHomeSecurityHDKDeviceFixture, HDK_Start_HomeSecurity_Bridge_FAIL_7) {
    int result;
    char mockPath1[] = "Device.Bridging.Bridge.1";
    char mockPort1[] = "1";
    char mockTrue[] = "true";
    char mockPath2[] = "Device.Bridging.Bridge.2";
    MBusObj_t* ccsp_bus = (MBusObj_t*)malloc(sizeof(MBusObj_s));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.PrimaryLANBridge"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPath1, mockPath1 + strlen(mockPath1) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.PrimaryLANBridgeHSPorts"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPort1, mockPort1 + strlen(mockPort1) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.Bridging.Bridge.1.Port.1.Enable"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockTrue, mockTrue + strlen(mockTrue) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_SetParamVal(_, StrEq("Device.Bridging.Bridge.1.Port.1.Enable"), _, _, _))
    .Times(1).WillOnce(Return(0));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityBridge"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPath2, mockPath2 + strlen(mockPath2) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityBridgePorts"), _, _))
    .Times(1).WillOnce(Return(1));

    result = HDK_Start_HomeSecurity_Bridge(ccsp_bus);

    EXPECT_EQ(result, -1);
}

TEST_F(CcspHomeSecurityHDKDeviceFixture, HDK_Start_HomeSecurity_Bridge_FAIL_8) {
    int result;
    char mockPath1[] = "Device.Bridging.Bridge.1";
    char mockPath2[] = "Device.Bridging.Bridge.2";
    char mockPort1[] = "1";
    char mockPort2[] = "2";
    char mockTrue[] = "true";
    MBusObj_t* ccsp_bus = (MBusObj_t*)malloc(sizeof(MBusObj_s));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.PrimaryLANBridge"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPath1, mockPath1 + strlen(mockPath1) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.PrimaryLANBridgeHSPorts"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPort1, mockPort1 + strlen(mockPort1) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.Bridging.Bridge.1.Port.1.Enable"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockTrue, mockTrue + strlen(mockTrue) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_SetParamVal(_, StrEq("Device.Bridging.Bridge.1.Port.1.Enable"), _, _, _))
    .Times(1).WillOnce(Return(0));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityBridge"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPath2, mockPath2 + strlen(mockPath2) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityBridgePorts"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPort2, mockPort2 + strlen(mockPort2) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.Bridging.Bridge.2.Port.2.Enable"), _, _))
    .Times(1).WillOnce(Return(1));

    result = HDK_Start_HomeSecurity_Bridge(ccsp_bus);

    EXPECT_EQ(result, -1);
}

TEST_F(CcspHomeSecurityHDKDeviceFixture, HDK_Start_HomeSecurity_Bridge_FAIL_9) {
    int result;
    char mockPath1[] = "Device.Bridging.Bridge.1";
    char mockPath2[] = "Device.Bridging.Bridge.2";
    char mockPort1[] = "1";
    char mockPort2[] = "2";
    char mockTrue[] = "true";
    char mockFalse[] = "false";
    MBusObj_t* ccsp_bus = (MBusObj_t*)malloc(sizeof(MBusObj_s));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.PrimaryLANBridge"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPath1, mockPath1 + strlen(mockPath1) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.PrimaryLANBridgeHSPorts"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPort1, mockPort1 + strlen(mockPort1) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.Bridging.Bridge.1.Port.1.Enable"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockTrue, mockTrue + strlen(mockTrue) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_SetParamVal(_, StrEq("Device.Bridging.Bridge.1.Port.1.Enable"), _, _, _))
    .Times(1).WillOnce(Return(0));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityBridge"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPath2, mockPath2 + strlen(mockPath2) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityBridgePorts"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPort2, mockPort2 + strlen(mockPort2) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.Bridging.Bridge.2.Port.2.Enable"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockFalse, mockFalse + strlen(mockFalse) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_SetParamVal(_, StrEq("Device.Bridging.Bridge.2.Port.2.Enable"), _, _, _))
    .Times(1).WillOnce(Return(1));

    result = HDK_Start_HomeSecurity_Bridge(ccsp_bus);

    EXPECT_EQ(result, -1);
}

TEST_F(CcspHomeSecurityHDKDeviceFixture, HDK_Device_SetValue_FAIL) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_PortMappings;
    HDK_Struct* pStruct = nullptr;

    mockDeviceCtx->mbus = nullptr;
    int result = HDK_Device_SetValue(mockDeviceCtx, eValue, pStruct);
    EXPECT_EQ(result, 0);
}

TEST_F(CcspHomeSecurityHDKDeviceFixture, HDK_Device_SetValue_DEFAULT) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue__UNKNOWN__;
    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    int result = HDK_Device_SetValue(mockDeviceCtx, eValue, pStruct);
    EXPECT_EQ(result, 0);
}

TEST_F(CcspHomeSecurityHDKDeviceFixture, HDK_Device_SetValue_PortMappings_SUCCESS_1) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_PortMappings;
    char mockIP[] = "172.16.12.1";
    char mockPort[] = "1";
    char mockProtocol[] = "UDP";
    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    HDK_Member__INT__* pMember1 = (HDK_Member__INT__*) malloc(sizeof(HDK_Member__INT__));
    ASSERT_NE(pMember1, nullptr);

    HDK_Member_IPAddress* pMember2 = (HDK_Member_IPAddress*) malloc(sizeof(HDK_Member_IPAddress));
    ASSERT_NE(pMember2, nullptr);

    HDK_Member__INT__* pMember3 = (HDK_Member__INT__*) malloc(sizeof(HDK_Member__INT__));
    ASSERT_NE(pMember3, nullptr);

    HDK_Member__INT__* pMember4 = (HDK_Member__INT__*) malloc(sizeof(HDK_Member__INT__));
    ASSERT_NE(pMember4, nullptr);

    HDK_Member__STRING__* pMember5 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember5, nullptr);

    pMember1->node.element = HDK_Element_PN_ExternalPort;
    pMember1->node.type = HDK_Type__INT__;
    pMember1->node.pNext = (HDK_Member*)pMember2;
    pMember1->iValue = 1;

    pMember2->node.element = HDK_Element_PN_InternalClient;
    pMember2->node.type = HDK_Type__IPADDRESS__;
    pMember2->node.pNext = (HDK_Member*)pMember3;
    pMember2->ipAddress.a = 172;
    pMember2->ipAddress.b = 16;
    pMember2->ipAddress.c = 12;
    pMember2->ipAddress.d = 111;

    pMember3->node.element = HDK_Element_PN_InternalPort;
    pMember3->node.type = HDK_Type__INT__;
    pMember3->node.pNext = (HDK_Member*)pMember4;
    pMember3->iValue = 1;

    pMember4->node.element = HDK_Element_PN_PortMappingProtocol;
    pMember4->node.type = HDK_Type_PN_IPProtocol;
    pMember4->node.pNext = (HDK_Member*)pMember5;
    pMember4->iValue = HDK_Enum_PN_IPProtocol_UDP;

    pMember5->node.element = HDK_Element_PN_PortMappingDescription;
    pMember5->node.type = HDK_Type__STRING__;
    pMember5->node.pNext = nullptr;
    pMember5->pszValue = strdup("Sample Port Mapping Description");

    pStruct->pHead = (HDK_Member*)pMember1;
    pStruct->pTail = (HDK_Member*)pMember5;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_FindObjectIns(_, _, _, _, _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
        testing::Invoke([&](MBusObj_t *, const char *, const char *, const char *, char insPath[][MAX_PATH_NAME], int *insNum) {
            strcpy(insPath[0], "Device.NAT.PortMapping.1.");
            *insNum = 1;
        }),
        Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.NAT.PortMapping.1.InternalClient"), _, _))
    .Times(2)
    .WillRepeatedly(testing::DoAll(
             testing::SetArrayArgument<2>(mockIP, mockIP + strlen(mockIP) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.NAT.PortMapping.1.ExternalPort"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPort, mockPort + strlen(mockPort) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.NAT.PortMapping.1.Protocol"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockProtocol, mockProtocol + strlen(mockProtocol) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.NAT.PortMapping.1.InternalPort"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPort, mockPort + strlen(mockPort) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_SetParamVect(_, _, _, _, _)).Times(1).WillOnce(Return(0));

    int result = HDK_Device_SetValue((void*)mockDeviceCtx, eValue, pStruct);
    EXPECT_EQ(result, 1);

    // Free the allocated memory
    free(pMember1);
    free(pMember2);
    free(pMember3);
    free(pMember4);
    free(pMember5);
    free(pStruct);
}

TEST_F(CcspHomeSecurityHDKDeviceFixture, HDK_Device_SetValue_PortMappings_SUCCESS_2) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_PortMappings;
    char mockIP[] = "172.16.12.1";
    char mockPort[] = "1";
    char mockProtocol[] = "IP";
    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    HDK_Member__INT__* pMember1 = (HDK_Member__INT__*) malloc(sizeof(HDK_Member__INT__));
    ASSERT_NE(pMember1, nullptr);

    HDK_Member_IPAddress* pMember2 = (HDK_Member_IPAddress*) malloc(sizeof(HDK_Member_IPAddress));
    ASSERT_NE(pMember2, nullptr);

    HDK_Member__INT__* pMember3 = (HDK_Member__INT__*) malloc(sizeof(HDK_Member__INT__));
    ASSERT_NE(pMember3, nullptr);

    HDK_Member__INT__* pMember4 = (HDK_Member__INT__*) malloc(sizeof(HDK_Member__INT__));
    ASSERT_NE(pMember4, nullptr);

    HDK_Member__STRING__* pMember5 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember5, nullptr);

    pMember1->node.element = HDK_Element_PN_ExternalPort;
    pMember1->node.type = HDK_Type__INT__;
    pMember1->node.pNext = (HDK_Member*)pMember2;
    pMember1->iValue = 1;

    pMember2->node.element = HDK_Element_PN_InternalClient;
    pMember2->node.type = HDK_Type__IPADDRESS__;
    pMember2->node.pNext = (HDK_Member*)pMember3;
    pMember2->ipAddress.a = 172;
    pMember2->ipAddress.b = 16;
    pMember2->ipAddress.c = 12;
    pMember2->ipAddress.d = 111;

    pMember3->node.element = HDK_Element_PN_InternalPort;
    pMember3->node.type = HDK_Type__INT__;
    pMember3->node.pNext = (HDK_Member*)pMember4;
    pMember3->iValue = 1;

    pMember4->node.element = HDK_Element_PN_PortMappingProtocol;
    pMember4->node.type = HDK_Type_PN_IPProtocol;
    pMember4->node.pNext = (HDK_Member*)pMember5;
    pMember4->iValue = HDK_Enum_PN_IPProtocol_UDP;

    pMember5->node.element = HDK_Element_PN_PortMappingDescription;
    pMember5->node.type = HDK_Type__STRING__;
    pMember5->node.pNext = nullptr;
    pMember5->pszValue = strdup("Sample Port Mapping Description");

    pStruct->pHead = (HDK_Member*)pMember1;
    pStruct->pTail = (HDK_Member*)pMember5;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_FindObjectIns(_, _, _, _, _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
        testing::Invoke([&](MBusObj_t *, const char *, const char *, const char *, char insPath[][MAX_PATH_NAME], int *insNum) {
            strcpy(insPath[0], "Device.NAT.PortMapping.1.");
            *insNum = 1;
        }),
        Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.NAT.PortMapping.1.InternalClient"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockIP, mockIP + strlen(mockIP) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.NAT.PortMapping.1.ExternalPort"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPort, mockPort + strlen(mockPort) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.NAT.PortMapping.1.Protocol"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockProtocol, mockProtocol + strlen(mockProtocol) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_AddObjectIns(_, _, _)).Times(1).WillOnce(Return(0));


    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_SetParamVect(_, _, _, _, _)).Times(1).WillOnce(Return(0));

    int result = HDK_Device_SetValue((void*)mockDeviceCtx, eValue, pStruct);
    EXPECT_EQ(result, 1);

    // Free the allocated memory
    free(pMember1);
    free(pMember2);
    free(pMember3);
    free(pMember4);
    free(pMember5);
    free(pStruct);
}

TEST_F(CcspHomeSecurityHDKDeviceFixture, HDK_Device_SetValue_PortMappings_FAIL_1) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_PortMappings;
    char mockIP[] = "172.16.12.1";
    char mockPort[] = "1";
    char mockProtocol[] = "IP";
    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    HDK_Member__INT__* pMember1 = (HDK_Member__INT__*) malloc(sizeof(HDK_Member__INT__));
    ASSERT_NE(pMember1, nullptr);

    HDK_Member_IPAddress* pMember2 = (HDK_Member_IPAddress*) malloc(sizeof(HDK_Member_IPAddress));
    ASSERT_NE(pMember2, nullptr);

    HDK_Member__INT__* pMember3 = (HDK_Member__INT__*) malloc(sizeof(HDK_Member__INT__));
    ASSERT_NE(pMember3, nullptr);

    HDK_Member__INT__* pMember4 = (HDK_Member__INT__*) malloc(sizeof(HDK_Member__INT__));
    ASSERT_NE(pMember4, nullptr);

    HDK_Member__STRING__* pMember5 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember5, nullptr);

    pMember1->node.element = HDK_Element_PN_ExternalPort;
    pMember1->node.type = HDK_Type__INT__;
    pMember1->node.pNext = (HDK_Member*)pMember2;
    pMember1->iValue = 1;

    pMember2->node.element = HDK_Element_PN_InternalClient;
    pMember2->node.type = HDK_Type__IPADDRESS__;
    pMember2->node.pNext = (HDK_Member*)pMember3;
    pMember2->ipAddress.a = 172;
    pMember2->ipAddress.b = 16;
    pMember2->ipAddress.c = 12;
    pMember2->ipAddress.d = 111;

    pMember3->node.element = HDK_Element_PN_InternalPort;
    pMember3->node.type = HDK_Type__INT__;
    pMember3->node.pNext = (HDK_Member*)pMember4;
    pMember3->iValue = 1;

    pMember4->node.element = HDK_Element_PN_PortMappingProtocol;
    pMember4->node.type = HDK_Type_PN_IPProtocol;
    pMember4->node.pNext = (HDK_Member*)pMember5;
    pMember4->iValue = HDK_Enum_PN_IPProtocol_UDP;

    pMember5->node.element = HDK_Element_PN_PortMappingDescription;
    pMember5->node.type = HDK_Type__STRING__;
    pMember5->node.pNext = nullptr;
    pMember5->pszValue = strdup("Sample Port Mapping Description");

    pStruct->pHead = (HDK_Member*)pMember1;
    pStruct->pTail = (HDK_Member*)pMember5;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_FindObjectIns(_, _, _, _, _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
        testing::Invoke([&](MBusObj_t *, const char *, const char *, const char *, char insPath[][MAX_PATH_NAME], int *insNum) {
            strcpy(insPath[0], "Device.NAT.PortMapping.1.");
            *insNum = 1;
        }),
        Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.NAT.PortMapping.1.InternalClient"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockIP, mockIP + strlen(mockIP) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.NAT.PortMapping.1.ExternalPort"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPort, mockPort + strlen(mockPort) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.NAT.PortMapping.1.Protocol"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockProtocol, mockProtocol + strlen(mockProtocol) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_AddObjectIns(_, _, _)).Times(1).WillOnce(Return(0));


    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_SetParamVect(_, _, _, _, _)).Times(1).WillOnce(Return(1));
    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_DelObjectIns(_, _, _)).Times(1).WillOnce(Return(0));

    int result = HDK_Device_SetValue((void*)mockDeviceCtx, eValue, pStruct);
    EXPECT_EQ(result, 0);

    // Free the allocated memory
    free(pMember1);
    free(pMember2);
    free(pMember3);
    free(pMember4);
    free(pMember5);
    free(pStruct);
}

TEST_F(CcspHomeSecurityHDKDeviceFixture, HDK_Device_SetValue_PortMappings_FAIL_2) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_PortMappings;
    char mockIP[] = "172.16.12.1";
    char mockPort[] = "1";
    char mockProtocol[] = "IP";
    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    HDK_Member__INT__* pMember1 = (HDK_Member__INT__*) malloc(sizeof(HDK_Member__INT__));
    ASSERT_NE(pMember1, nullptr);

    HDK_Member_IPAddress* pMember2 = (HDK_Member_IPAddress*) malloc(sizeof(HDK_Member_IPAddress));
    ASSERT_NE(pMember2, nullptr);

    pMember1->node.element = HDK_Element_PN_ExternalPort;
    pMember1->node.type = HDK_Type__INT__;
    pMember1->node.pNext = (HDK_Member*)pMember2;
    pMember1->iValue = 1;

    pMember2->node.element = HDK_Element_PN_InternalClient;
    pMember2->node.type = HDK_Type__IPADDRESS__;
    pMember2->node.pNext = nullptr;
    pMember2->ipAddress.a = 172;
    pMember2->ipAddress.b = 16;
    pMember2->ipAddress.c = 12;
    pMember2->ipAddress.d = 111;

    pStruct->pHead = (HDK_Member*)pMember1;
    pStruct->pTail = (HDK_Member*)pMember2;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_FindObjectIns(_, _, _, _, _, _)).Times(1).WillOnce(Return(1));

    int result = HDK_Device_SetValue((void*)mockDeviceCtx, eValue, pStruct);
    EXPECT_EQ(result, 0);

    // Free the allocated memory
    free(pMember1);
    free(pMember2);
    free(pStruct);
}

TEST_F(CcspHomeSecurityHDKDeviceFixture, HDK_Device_SetValue_WLanMode_1) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WLanMode;
    char mockPathVal[] = "Device.WiFi.Radio.1";
    char mockAlias[] = "Radio0";

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    HDK_Member__INT__* pMember1 = (HDK_Member__INT__*) malloc(sizeof(HDK_Member__INT__));
    ASSERT_NE(pMember1, nullptr);

    HDK_Member__STRING__* pMember2 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember2, nullptr);

    pMember1->node.element = HDK_Element_PN_Mode;
    pMember1->node.type = HDK_Type_PN_WiFiMode;
    pMember1->node.pNext = (HDK_Member*)pMember2;
    pMember1->iValue = HDK_Enum_PN_WiFiMode_802_11gn;

    pMember2->node.element = HDK_Element_PN_RadioID;
    pMember2->node.type = HDK_Type__STRING__;
    pMember2->node.pNext = nullptr;
    pMember2->pszValue = strdup("Radio0");

    pStruct->pHead = (HDK_Member*)pMember1;
    pStruct->pTail = (HDK_Member*)pMember2;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.WiFi.Radio.1.Alias"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockAlias, mockAlias + strlen(mockAlias) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_SetParamVal(_, StrEq("Device.WiFi.Radio.1.OperatingStandards"), _, _, _))
    .Times(1).WillOnce(Return(0));

    int result = HDK_Device_SetValue((void*)mockDeviceCtx, eValue, pStruct);
    EXPECT_EQ(result, 1);

    // Free the allocated memory
    free(pMember1);
    free(pMember2);
    free(pStruct);
}

TEST_F(CcspHomeSecurityHDKDeviceFixture, HDK_Device_SetValue_WLanMode_2) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WLanMode;
    char mockPathVal[] = "Device.WiFi.Radio.1";
    char mockAlias[] = "Radio0";

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    HDK_Member__INT__* pMember1 = (HDK_Member__INT__*) malloc(sizeof(HDK_Member__INT__));
    ASSERT_NE(pMember1, nullptr);

    HDK_Member__STRING__* pMember2 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember2, nullptr);

    pMember1->node.element = HDK_Element_PN_Mode;
    pMember1->node.type = HDK_Type_PN_WiFiMode;
    pMember1->node.pNext = (HDK_Member*)pMember2;
    pMember1->iValue = HDK_Enum_PN_WiFiMode_802_11a;

    pMember2->node.element = HDK_Element_PN_RadioID;
    pMember2->node.type = HDK_Type__STRING__;
    pMember2->node.pNext = nullptr;
    pMember2->pszValue = strdup("Radio0");

    pStruct->pHead = (HDK_Member*)pMember1;
    pStruct->pTail = (HDK_Member*)pMember2;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.WiFi.Radio.1.Alias"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockAlias, mockAlias + strlen(mockAlias) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_SetParamVal(_, StrEq("Device.WiFi.Radio.1.OperatingStandards"), _, _, _))
    .Times(1).WillOnce(Return(0));

    int result = HDK_Device_SetValue((void*)mockDeviceCtx, eValue, pStruct);
    EXPECT_EQ(result, 1);

    // Free the allocated memory
    free(pMember1);
    free(pMember2);
    free(pStruct);
}

TEST_F(CcspHomeSecurityHDKDeviceFixture, HDK_Device_SetValue_WLanMode_3) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WLanMode;
    char mockPathVal[] = "Device.WiFi.Radio.1";
    char mockAlias[] = "Radio0";

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    HDK_Member__INT__* pMember1 = (HDK_Member__INT__*) malloc(sizeof(HDK_Member__INT__));
    ASSERT_NE(pMember1, nullptr);

    HDK_Member__STRING__* pMember2 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember2, nullptr);

    pMember1->node.element = HDK_Element_PN_Mode;
    pMember1->node.type = HDK_Type_PN_WiFiMode;
    pMember1->node.pNext = (HDK_Member*)pMember2;
    pMember1->iValue = HDK_Enum_PN_WiFiMode_802_11b;

    pMember2->node.element = HDK_Element_PN_RadioID;
    pMember2->node.type = HDK_Type__STRING__;
    pMember2->node.pNext = nullptr;
    pMember2->pszValue = strdup("Radio0");

    pStruct->pHead = (HDK_Member*)pMember1;
    pStruct->pTail = (HDK_Member*)pMember2;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.WiFi.Radio.1.Alias"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockAlias, mockAlias + strlen(mockAlias) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_SetParamVal(_, StrEq("Device.WiFi.Radio.1.OperatingStandards"), _, _, _))
    .Times(1).WillOnce(Return(0));

    int result = HDK_Device_SetValue((void*)mockDeviceCtx, eValue, pStruct);
    EXPECT_EQ(result, 1);

    // Free the allocated memory
    free(pMember1);
    free(pMember2);
    free(pStruct);
}

TEST_F(CcspHomeSecurityHDKDeviceFixture, HDK_Device_SetValue_WLanMode_4) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WLanMode;
    char mockPathVal[] = "Device.WiFi.Radio.1";
    char mockAlias[] = "Radio0";

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    HDK_Member__INT__* pMember1 = (HDK_Member__INT__*) malloc(sizeof(HDK_Member__INT__));
    ASSERT_NE(pMember1, nullptr);

    HDK_Member__STRING__* pMember2 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember2, nullptr);

    pMember1->node.element = HDK_Element_PN_Mode;
    pMember1->node.type = HDK_Type_PN_WiFiMode;
    pMember1->node.pNext = (HDK_Member*)pMember2;
    pMember1->iValue = HDK_Enum_PN_WiFiMode_802_11g;

    pMember2->node.element = HDK_Element_PN_RadioID;
    pMember2->node.type = HDK_Type__STRING__;
    pMember2->node.pNext = nullptr;
    pMember2->pszValue = strdup("Radio0");

    pStruct->pHead = (HDK_Member*)pMember1;
    pStruct->pTail = (HDK_Member*)pMember2;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.WiFi.Radio.1.Alias"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockAlias, mockAlias + strlen(mockAlias) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_SetParamVal(_, StrEq("Device.WiFi.Radio.1.OperatingStandards"), _, _, _))
    .Times(1).WillOnce(Return(0));

    int result = HDK_Device_SetValue((void*)mockDeviceCtx, eValue, pStruct);
    EXPECT_EQ(result, 1);

    // Free the allocated memory
    free(pMember1);
    free(pMember2);
    free(pStruct);
}

TEST_F(CcspHomeSecurityHDKDeviceFixture, HDK_Device_SetValue_WLanMode_5) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WLanMode;
    char mockPathVal[] = "Device.WiFi.Radio.1";
    char mockAlias[] = "Radio0";

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    HDK_Member__INT__* pMember1 = (HDK_Member__INT__*) malloc(sizeof(HDK_Member__INT__));
    ASSERT_NE(pMember1, nullptr);

    HDK_Member__STRING__* pMember2 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember2, nullptr);

    pMember1->node.element = HDK_Element_PN_Mode;
    pMember1->node.type = HDK_Type_PN_WiFiMode;
    pMember1->node.pNext = (HDK_Member*)pMember2;
    pMember1->iValue = HDK_Enum_PN_WiFiMode_802_11n;

    pMember2->node.element = HDK_Element_PN_RadioID;
    pMember2->node.type = HDK_Type__STRING__;
    pMember2->node.pNext = nullptr;
    pMember2->pszValue = strdup("Radio0");

    pStruct->pHead = (HDK_Member*)pMember1;
    pStruct->pTail = (HDK_Member*)pMember2;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.WiFi.Radio.1.Alias"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockAlias, mockAlias + strlen(mockAlias) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_SetParamVal(_, StrEq("Device.WiFi.Radio.1.OperatingStandards"), _, _, _))
    .Times(1).WillOnce(Return(0));

    int result = HDK_Device_SetValue((void*)mockDeviceCtx, eValue, pStruct);
    EXPECT_EQ(result, 1);

    // Free the allocated memory
    free(pMember1);
    free(pMember2);
    free(pStruct);
}

TEST_F(CcspHomeSecurityHDKDeviceFixture, HDK_Device_SetValue_WLanMode_6) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WLanMode;
    char mockPathVal[] = "Device.WiFi.Radio.1";
    char mockAlias[] = "Radio0";

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    HDK_Member__INT__* pMember1 = (HDK_Member__INT__*) malloc(sizeof(HDK_Member__INT__));
    ASSERT_NE(pMember1, nullptr);

    HDK_Member__STRING__* pMember2 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember2, nullptr);

    pMember1->node.element = HDK_Element_PN_Mode;
    pMember1->node.type = HDK_Type_PN_WiFiMode;
    pMember1->node.pNext = (HDK_Member*)pMember2;
    pMember1->iValue = HDK_Enum_PN_WiFiMode_802_11an;

    pMember2->node.element = HDK_Element_PN_RadioID;
    pMember2->node.type = HDK_Type__STRING__;
    pMember2->node.pNext = nullptr;
    pMember2->pszValue = strdup("Radio0");

    pStruct->pHead = (HDK_Member*)pMember1;
    pStruct->pTail = (HDK_Member*)pMember2;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.WiFi.Radio.1.Alias"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockAlias, mockAlias + strlen(mockAlias) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_SetParamVal(_, StrEq("Device.WiFi.Radio.1.OperatingStandards"), _, _, _))
    .Times(1).WillOnce(Return(0));

    int result = HDK_Device_SetValue((void*)mockDeviceCtx, eValue, pStruct);
    EXPECT_EQ(result, 1);

    // Free the allocated memory
    free(pMember1);
    free(pMember2);
    free(pStruct);
}

TEST_F(CcspHomeSecurityHDKDeviceFixture, HDK_Device_SetValue_WLanMode_7) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WLanMode;
    char mockPathVal[] = "Device.WiFi.Radio.1";
    char mockAlias[] = "Radio0";

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    HDK_Member__INT__* pMember1 = (HDK_Member__INT__*) malloc(sizeof(HDK_Member__INT__));
    ASSERT_NE(pMember1, nullptr);

    HDK_Member__STRING__* pMember2 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember2, nullptr);

    pMember1->node.element = HDK_Element_PN_Mode;
    pMember1->node.type = HDK_Type_PN_WiFiMode;
    pMember1->node.pNext = (HDK_Member*)pMember2;
    pMember1->iValue = HDK_Enum_PN_WiFiMode_802_11bg;

    pMember2->node.element = HDK_Element_PN_RadioID;
    pMember2->node.type = HDK_Type__STRING__;
    pMember2->node.pNext = nullptr;
    pMember2->pszValue = strdup("Radio0");

    pStruct->pHead = (HDK_Member*)pMember1;
    pStruct->pTail = (HDK_Member*)pMember2;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.WiFi.Radio.1.Alias"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockAlias, mockAlias + strlen(mockAlias) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_SetParamVal(_, StrEq("Device.WiFi.Radio.1.OperatingStandards"), _, _, _))
    .Times(1).WillOnce(Return(0));

    int result = HDK_Device_SetValue((void*)mockDeviceCtx, eValue, pStruct);
    EXPECT_EQ(result, 1);

    // Free the allocated memory
    free(pMember1);
    free(pMember2);
    free(pStruct);
}

TEST_F(CcspHomeSecurityHDKDeviceFixture, HDK_Device_SetValue_WLanMode_8) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WLanMode;
    char mockPathVal[] = "Device.WiFi.Radio.1";
    char mockAlias[] = "Radio0";

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    HDK_Member__INT__* pMember1 = (HDK_Member__INT__*) malloc(sizeof(HDK_Member__INT__));
    ASSERT_NE(pMember1, nullptr);

    HDK_Member__STRING__* pMember2 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember2, nullptr);

    pMember1->node.element = HDK_Element_PN_Mode;
    pMember1->node.type = HDK_Type_PN_WiFiMode;
    pMember1->node.pNext = (HDK_Member*)pMember2;
    pMember1->iValue = HDK_Enum_PN_WiFiMode_802_11bn;

    pMember2->node.element = HDK_Element_PN_RadioID;
    pMember2->node.type = HDK_Type__STRING__;
    pMember2->node.pNext = nullptr;
    pMember2->pszValue = strdup("Radio0");

    pStruct->pHead = (HDK_Member*)pMember1;
    pStruct->pTail = (HDK_Member*)pMember2;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.WiFi.Radio.1.Alias"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockAlias, mockAlias + strlen(mockAlias) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_SetParamVal(_, StrEq("Device.WiFi.Radio.1.OperatingStandards"), _, _, _))
    .Times(1).WillOnce(Return(0));

    int result = HDK_Device_SetValue((void*)mockDeviceCtx, eValue, pStruct);
    EXPECT_EQ(result, 1);

    // Free the allocated memory
    free(pMember1);
    free(pMember2);
    free(pStruct);
}

TEST_F(CcspHomeSecurityHDKDeviceFixture, HDK_Device_SetValue_WLanMode_9) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WLanMode;
    char mockPathVal[] = "Device.WiFi.Radio.1";
    char mockAlias[] = "Radio0";

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    HDK_Member__INT__* pMember1 = (HDK_Member__INT__*) malloc(sizeof(HDK_Member__INT__));
    ASSERT_NE(pMember1, nullptr);

    HDK_Member__STRING__* pMember2 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember2, nullptr);

    pMember1->node.element = HDK_Element_PN_Mode;
    pMember1->node.type = HDK_Type_PN_WiFiMode;
    pMember1->node.pNext = (HDK_Member*)pMember2;
    pMember1->iValue = HDK_Enum_PN_WiFiMode_802_11bgn;

    pMember2->node.element = HDK_Element_PN_RadioID;
    pMember2->node.type = HDK_Type__STRING__;
    pMember2->node.pNext = nullptr;
    pMember2->pszValue = strdup("Radio0");

    pStruct->pHead = (HDK_Member*)pMember1;
    pStruct->pTail = (HDK_Member*)pMember2;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.WiFi.Radio.1.Alias"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockAlias, mockAlias + strlen(mockAlias) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_SetParamVal(_, StrEq("Device.WiFi.Radio.1.OperatingStandards"), _, _, _))
    .Times(1).WillOnce(Return(0));

    int result = HDK_Device_SetValue((void*)mockDeviceCtx, eValue, pStruct);
    EXPECT_EQ(result, 1);

    // Free the allocated memory
    free(pMember1);
    free(pMember2);
    free(pStruct);
}

TEST_F(CcspHomeSecurityHDKDeviceFixture, HDK_Device_SetValue_WLanMode_FAIL_1) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WLanMode;

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    HDK_Member__INT__* pMember1 = (HDK_Member__INT__*) malloc(sizeof(HDK_Member__INT__));
    ASSERT_NE(pMember1, nullptr);

    HDK_Member__STRING__* pMember2 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember2, nullptr);

    pMember1->node.element = HDK_Element_PN_Mode;
    pMember1->node.type = HDK_Type_PN_WiFiMode;
    pMember1->node.pNext = (HDK_Member*)pMember2;
    pMember1->iValue = HDK_Enum_PN_WiFiMode_802_11a;

    pMember2->node.element = HDK_Element_PN_RadioID;
    pMember2->node.type = HDK_Type__STRING__;
    pMember2->node.pNext = nullptr;
    pMember2->pszValue = strdup("Radio0");

    pStruct->pHead = (HDK_Member*)pMember1;
    pStruct->pTail = (HDK_Member*)pMember2;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .Times(1).WillOnce(Return(1));

    int result = HDK_Device_SetValue((void*)mockDeviceCtx, eValue, pStruct);
    EXPECT_EQ(result, 0);

    // Free the allocated memory
    free(pMember1);
    free(pMember2);
    free(pStruct);
}

TEST_F(CcspHomeSecurityHDKDeviceFixture, HDK_Device_SetValue_WLanMode_FAIL_2) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WLanMode;
    char mockPathVal[] = "Device.WiFi.Radio.1";
    char mockAlias[] = "Radio0";

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    HDK_Member__INT__* pMember1 = (HDK_Member__INT__*) malloc(sizeof(HDK_Member__INT__));
    ASSERT_NE(pMember1, nullptr);

    HDK_Member__STRING__* pMember2 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember2, nullptr);

    pMember1->node.element = HDK_Element_PN_Mode;
    pMember1->node.type = HDK_Type_PN_WiFiMode;
    pMember1->node.pNext = (HDK_Member*)pMember2;
    pMember1->iValue = HDK_Enum_PN_WiFiMode_802_11a;

    pMember2->node.element = HDK_Element_PN_RadioID;
    pMember2->node.type = HDK_Type__STRING__;
    pMember2->node.pNext = nullptr;
    pMember2->pszValue = strdup("Radio1");

    pStruct->pHead = (HDK_Member*)pMember1;
    pStruct->pTail = (HDK_Member*)pMember2;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.WiFi.Radio.1.Alias"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockAlias, mockAlias + strlen(mockAlias) + 1),
             Return(0)
    ));

    int result = HDK_Device_SetValue((void*)mockDeviceCtx, eValue, pStruct);
    EXPECT_EQ(result, 0);

    // Free the allocated memory
    free(pMember1);
    free(pMember2);
    free(pStruct);
}

TEST_F(CcspHomeSecurityHDKDeviceFixture, HDK_Device_SetValue_WLanEnabled_SUCCESS) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WLanEnabled;
    char mockPathVal[] = "Device.WiFi.Radio.1";
    char mockAlias[] = "Radio0";

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    HDK_Member__STRING__* pMember1 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember1, nullptr);

    HDK_Member__INT__* pMember2 = (HDK_Member__INT__*) malloc(sizeof(HDK_Member__INT__));
    ASSERT_NE(pMember2, nullptr);

    pMember1->node.element = HDK_Element_PN_RadioID;
    pMember1->node.type = HDK_Type__STRING__;
    pMember1->node.pNext = (HDK_Member*)pMember2;
    pMember1->pszValue = strdup("Radio0");

    pMember2->node.element = HDK_Element_PN_Enabled;
    pMember2->node.type = HDK_Type__BOOL__;
    pMember2->node.pNext = nullptr;
    pMember2->iValue = 1;

    pStruct->pHead = (HDK_Member*)pMember1;
    pStruct->pTail = (HDK_Member*)pMember2;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.WiFi.Radio.1.Alias"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockAlias, mockAlias + strlen(mockAlias) + 1),
             Return(0)
    ));


    int result = HDK_Device_SetValue((void*)mockDeviceCtx, eValue, pStruct);
    EXPECT_EQ(result, 1);

    // Free the allocated memory
    free(pMember1);
    free(pMember2);
    free(pStruct);
}

TEST_F(CcspHomeSecurityHDKDeviceFixture, HDK_Device_SetValue_WLanEnabled_FAIL_1) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WLanEnabled;

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    HDK_Member__STRING__* pMember1 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember1, nullptr);

    HDK_Member__INT__* pMember2 = (HDK_Member__INT__*) malloc(sizeof(HDK_Member__INT__));
    ASSERT_NE(pMember2, nullptr);

    pMember1->node.element = HDK_Element_PN_RadioID;
    pMember1->node.type = HDK_Type__STRING__;
    pMember1->node.pNext = (HDK_Member*)pMember2;
    pMember1->pszValue = strdup("Radio0");

    pMember2->node.element = HDK_Element_PN_Enabled;
    pMember2->node.type = HDK_Type__BOOL__;
    pMember2->node.pNext = nullptr;
    pMember2->iValue = 1;

    pStruct->pHead = (HDK_Member*)pMember1;
    pStruct->pTail = (HDK_Member*)pMember2;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .Times(1).WillOnce(Return(1));

    int result = HDK_Device_SetValue((void*)mockDeviceCtx, eValue, pStruct);
    EXPECT_EQ(result, 0);

    // Free the allocated memory
    free(pMember1);
    free(pMember2);
    free(pStruct);
}

TEST_F(CcspHomeSecurityHDKDeviceFixture, HDK_Device_SetValue_WLanEnabled_FAIL_2) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WLanEnabled;
    char mockPathVal[] = "Device.WiFi.Radio.1";
    char mockAlias[] = "Radio0";

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    HDK_Member__STRING__* pMember1 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember1, nullptr);

    HDK_Member__INT__* pMember2 = (HDK_Member__INT__*) malloc(sizeof(HDK_Member__INT__));
    ASSERT_NE(pMember2, nullptr);

    pMember1->node.element = HDK_Element_PN_RadioID;
    pMember1->node.type = HDK_Type__STRING__;
    pMember1->node.pNext = (HDK_Member*)pMember2;
    pMember1->pszValue = strdup("Radio1");

    pMember2->node.element = HDK_Element_PN_Enabled;
    pMember2->node.type = HDK_Type__BOOL__;
    pMember2->node.pNext = nullptr;
    pMember2->iValue = 1;

    pStruct->pHead = (HDK_Member*)pMember1;
    pStruct->pTail = (HDK_Member*)pMember2;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.WiFi.Radio.1.Alias"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockAlias, mockAlias + strlen(mockAlias) + 1),
             Return(0)
    ));

    int result = HDK_Device_SetValue((void*)mockDeviceCtx, eValue, pStruct);
    EXPECT_EQ(result, 0);

    // Free the allocated memory
    free(pMember1);
    free(pMember2);
    free(pStruct);
}

TEST_F(CcspHomeSecurityHDKDeviceFixture, HDK_Device_SetValue_WLanSSID_SUCCESS) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WLanSSID;
    char mockPathVal[] = "Device.WiFi.Radio.1";
    char mockSSIDPath[] = "Device.WiFi.SSID.3";
    char mockAlias[] = "Radio0";

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    HDK_Member__STRING__* pMember1 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember1, nullptr);

    HDK_Member__STRING__* pMember2 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember2, nullptr);

    pMember1->node.element = HDK_Element_PN_RadioID;
    pMember1->node.type = HDK_Type__STRING__;
    pMember1->node.pNext = (HDK_Member*)pMember2;
    pMember1->pszValue = strdup("Radio0");

    pMember2->node.element = HDK_Element_PN_SSID;
    pMember2->node.type = HDK_Type__STRING__;
    pMember2->node.pNext = nullptr;
    pMember2->pszValue = strdup("XHS-2.4G");

    pStruct->pHead = (HDK_Member*)pMember1;
    pStruct->pTail = (HDK_Member*)pMember2;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.WiFi.Radio.1.Alias"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockAlias, mockAlias + strlen(mockAlias) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiSsid"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockSSIDPath, mockSSIDPath + strlen(mockSSIDPath) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_SetParamVal(_, StrEq("Device.WiFi.SSID.3.SSID"), _, _, _))
    .Times(1).WillOnce(Return(0));

    int result = HDK_Device_SetValue((void*)mockDeviceCtx, eValue, pStruct);
    EXPECT_EQ(result, 1);

    // Free the allocated memory
    free(pMember1);
    free(pMember2);
    free(pStruct);
}

TEST_F(CcspHomeSecurityHDKDeviceFixture, HDK_Device_SetValue_WLanSSID_FAIL_1) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WLanSSID;

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    HDK_Member__STRING__* pMember1 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember1, nullptr);

    HDK_Member__STRING__* pMember2 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember2, nullptr);

    pMember1->node.element = HDK_Element_PN_RadioID;
    pMember1->node.type = HDK_Type__STRING__;
    pMember1->node.pNext = (HDK_Member*)pMember2;
    pMember1->pszValue = strdup("Radio0");

    pMember2->node.element = HDK_Element_PN_SSID;
    pMember2->node.type = HDK_Type__STRING__;
    pMember2->node.pNext = nullptr;
    pMember2->pszValue = strdup("XHS-2.4G");

    pStruct->pHead = (HDK_Member*)pMember1;
    pStruct->pTail = (HDK_Member*)pMember2;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .Times(1).WillOnce(Return(1));

    int result = HDK_Device_SetValue((void*)mockDeviceCtx, eValue, pStruct);
    EXPECT_EQ(result, 0);

    // Free the allocated memory
    free(pMember1);
    free(pMember2);
    free(pStruct);
}

TEST_F(CcspHomeSecurityHDKDeviceFixture, HDK_Device_SetValue_WLanSSID_FAIL_2) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WLanSSID;
    char mockPathVal[] = "Device.WiFi.Radio.1";
    char mockAlias[] = "Radio0";

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    HDK_Member__STRING__* pMember1 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember1, nullptr);

    HDK_Member__STRING__* pMember2 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember2, nullptr);

    pMember1->node.element = HDK_Element_PN_RadioID;
    pMember1->node.type = HDK_Type__STRING__;
    pMember1->node.pNext = (HDK_Member*)pMember2;
    pMember1->pszValue = strdup("Radio1");

    pMember2->node.element = HDK_Element_PN_SSID;
    pMember2->node.type = HDK_Type__STRING__;
    pMember2->node.pNext = nullptr;
    pMember2->pszValue = strdup("XHS-2.4G");

    pStruct->pHead = (HDK_Member*)pMember1;
    pStruct->pTail = (HDK_Member*)pMember2;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.WiFi.Radio.1.Alias"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockAlias, mockAlias + strlen(mockAlias) + 1),
             Return(0)
    ));

    int result = HDK_Device_SetValue((void*)mockDeviceCtx, eValue, pStruct);
    EXPECT_EQ(result, 0);

    // Free the allocated memory
    free(pMember1);
    free(pMember2);
    free(pStruct);
}

TEST_F(CcspHomeSecurityHDKDeviceFixture, HDK_Device_SetValue_WLanSSID_FAIL_3) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WLanSSID;
    char mockPathVal[] = "Device.WiFi.Radio.1";
    char mockAlias[] = "Radio0";

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    HDK_Member__STRING__* pMember1 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember1, nullptr);

    HDK_Member__STRING__* pMember2 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember2, nullptr);

    pMember1->node.element = HDK_Element_PN_RadioID;
    pMember1->node.type = HDK_Type__STRING__;
    pMember1->node.pNext = (HDK_Member*)pMember2;
    pMember1->pszValue = strdup("Radio0");

    pMember2->node.element = HDK_Element_PN_SSID;
    pMember2->node.type = HDK_Type__STRING__;
    pMember2->node.pNext = nullptr;
    pMember2->pszValue = strdup("XHS-2.4G");

    pStruct->pHead = (HDK_Member*)pMember1;
    pStruct->pTail = (HDK_Member*)pMember2;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.WiFi.Radio.1.Alias"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockAlias, mockAlias + strlen(mockAlias) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiSsid"), _, _))
    .Times(1).WillOnce(Return(1));

    int result = HDK_Device_SetValue((void*)mockDeviceCtx, eValue, pStruct);
    EXPECT_EQ(result, 0);

    // Free the allocated memory
    free(pMember1);
    free(pMember2);
    free(pStruct);
}

TEST_F(CcspHomeSecurityHDKDeviceFixture, HDK_Device_SetValue_WLanSSIDBroadcast_SUCCESS) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WLanSSIDBroadcast;
    char mockPathVal[] = "Device.WiFi.Radio.1";
    char mockApPathVal[] = "Device.WiFi.AccessPoint.3";
    char mockAlias[] = "Radio0";

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    HDK_Member__STRING__* pMember1 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember1, nullptr);

    HDK_Member__INT__* pMember2 = (HDK_Member__INT__*) malloc(sizeof(HDK_Member__INT__));
    ASSERT_NE(pMember2, nullptr);

    pMember1->node.element = HDK_Element_PN_RadioID;
    pMember1->node.type = HDK_Type__STRING__;
    pMember1->node.pNext = (HDK_Member*)pMember2;
    pMember1->pszValue = strdup("Radio0");

    pMember2->node.element = HDK_Element_PN_SSIDBroadcast;
    pMember2->node.type = HDK_Type__BOOL__;
    pMember2->node.pNext = nullptr;
    pMember2->iValue = 0;

    pStruct->pHead = (HDK_Member*)pMember1;
    pStruct->pTail = (HDK_Member*)pMember2;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.WiFi.Radio.1.Alias"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockAlias, mockAlias + strlen(mockAlias) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiAp"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    int result = HDK_Device_SetValue((void*)mockDeviceCtx, eValue, pStruct);
    EXPECT_EQ(result, 1);

    // Free the allocated memory
    free(pMember1);
    free(pMember2);
    free(pStruct);
}

TEST_F(CcspHomeSecurityHDKDeviceFixture, HDK_Device_SetValue_WLanSSIDBroadcast_FAIL_1) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WLanSSIDBroadcast;

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

     HDK_Member__STRING__* pMember1 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember1, nullptr);

    HDK_Member__INT__* pMember2 = (HDK_Member__INT__*) malloc(sizeof(HDK_Member__INT__));
    ASSERT_NE(pMember2, nullptr);

    pMember1->node.element = HDK_Element_PN_RadioID;
    pMember1->node.type = HDK_Type__STRING__;
    pMember1->node.pNext = (HDK_Member*)pMember2;
    pMember1->pszValue = strdup("Radio0");

    pMember2->node.element = HDK_Element_PN_SSIDBroadcast;
    pMember2->node.type = HDK_Type__BOOL__;
    pMember2->node.pNext = nullptr;
    pMember2->iValue = 0;

    pStruct->pHead = (HDK_Member*)pMember1;
    pStruct->pTail = (HDK_Member*)pMember2;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .Times(1).WillOnce(Return(1));

    int result = HDK_Device_SetValue((void*)mockDeviceCtx, eValue, pStruct);
    EXPECT_EQ(result, 0);

    // Free the allocated memory
    free(pMember1);
    free(pMember2);
    free(pStruct);
}

TEST_F(CcspHomeSecurityHDKDeviceFixture, HDK_Device_SetValue_WLanSSIDBroadcast_FAIL_2) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WLanSSIDBroadcast;
    char mockPathVal[] = "Device.WiFi.Radio.1";
    char mockAlias[] = "Radio0";

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    HDK_Member__STRING__* pMember1 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember1, nullptr);

    HDK_Member__INT__* pMember2 = (HDK_Member__INT__*) malloc(sizeof(HDK_Member__INT__));
    ASSERT_NE(pMember2, nullptr);

    pMember1->node.element = HDK_Element_PN_RadioID;
    pMember1->node.type = HDK_Type__STRING__;
    pMember1->node.pNext = (HDK_Member*)pMember2;
    pMember1->pszValue = strdup("Radio1");

    pMember2->node.element = HDK_Element_PN_SSIDBroadcast;
    pMember2->node.type = HDK_Type__BOOL__;
    pMember2->node.pNext = nullptr;
    pMember2->iValue = 0;

    pStruct->pHead = (HDK_Member*)pMember1;
    pStruct->pTail = (HDK_Member*)pMember2;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.WiFi.Radio.1.Alias"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockAlias, mockAlias + strlen(mockAlias) + 1),
             Return(0)
    ));

    int result = HDK_Device_SetValue((void*)mockDeviceCtx, eValue, pStruct);
    EXPECT_EQ(result, 0);

    // Free the allocated memory
    free(pMember1);
    free(pMember2);
    free(pStruct);
}

TEST_F(CcspHomeSecurityHDKDeviceFixture, HDK_Device_SetValue_WLanSSIDBroadcast_FAIL_3) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WLanSSIDBroadcast;
    char mockPathVal[] = "Device.WiFi.Radio.1";
    char mockAlias[] = "Radio0";

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    HDK_Member__STRING__* pMember1 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember1, nullptr);

    HDK_Member__INT__* pMember2 = (HDK_Member__INT__*) malloc(sizeof(HDK_Member__INT__));
    ASSERT_NE(pMember2, nullptr);

    pMember1->node.element = HDK_Element_PN_RadioID;
    pMember1->node.type = HDK_Type__STRING__;
    pMember1->node.pNext = (HDK_Member*)pMember2;
    pMember1->pszValue = strdup("Radio0");

    pMember2->node.element = HDK_Element_PN_SSIDBroadcast;
    pMember2->node.type = HDK_Type__BOOL__;
    pMember2->node.pNext = nullptr;
    pMember2->iValue = 0;

    pStruct->pHead = (HDK_Member*)pMember1;
    pStruct->pTail = (HDK_Member*)pMember2;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.WiFi.Radio.1.Alias"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockAlias, mockAlias + strlen(mockAlias) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiAp"), _, _))
    .Times(1).WillOnce(Return(1));

    int result = HDK_Device_SetValue((void*)mockDeviceCtx, eValue, pStruct);
    EXPECT_EQ(result, 0);

    // Free the allocated memory
    free(pMember1);
    free(pMember2);
    free(pStruct);
}

TEST_F(CcspHomeSecurityHDKDeviceFixture, HDK_Device_SetValue_WLanChannelWidth_SUCCESS_1) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WLanChannelWidth;
    char mockPathVal[] = "Device.WiFi.Radio.1";
    char mockAlias[] = "Radio0";

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    HDK_Member__STRING__* pMember1 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember1, nullptr);

    HDK_Member__INT__* pMember2 = (HDK_Member__INT__*) malloc(sizeof(HDK_Member__INT__));
    ASSERT_NE(pMember2, nullptr);

    HDK_Member__INT__* pMember3 = (HDK_Member__INT__*) malloc(sizeof(HDK_Member__INT__));
    ASSERT_NE(pMember3, nullptr);

    HDK_Member__INT__* pMember4 = (HDK_Member__INT__*) malloc(sizeof(HDK_Member__INT__));
    ASSERT_NE(pMember4, nullptr);

    pMember1->node.element = HDK_Element_PN_RadioID;
    pMember1->node.type = HDK_Type__STRING__;
    pMember1->node.pNext = (HDK_Member*)pMember2;
    pMember1->pszValue = strdup("Radio0");

    pMember2->node.element = HDK_Element_PN_ChannelWidth;
    pMember2->node.type = HDK_Type__INT__;
    pMember2->node.pNext = (HDK_Member*)pMember3;
    pMember2->iValue = 40;

    pMember3->node.element = HDK_Element_PN_SecondaryChannel;
    pMember3->node.type = HDK_Type__INT__;
    pMember3->node.pNext = (HDK_Member*)pMember4;
    pMember3->iValue = 40;

    pMember4->node.element = HDK_Element_PN_Channel;
    pMember4->node.type = HDK_Type__INT__;
    pMember4->node.pNext = nullptr;
    pMember4->iValue = 20;

    pStruct->pHead = (HDK_Member*)pMember1;
    pStruct->pTail = (HDK_Member*)pMember4;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.WiFi.Radio.1.Alias"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockAlias, mockAlias + strlen(mockAlias) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_SetParamVal(_, StrEq("Device.WiFi.Radio.1.OperatingChannelBandwidth"), _, _, _))
    .Times(1).WillOnce(Return(0));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_SetParamVal(_, StrEq("Device.WiFi.Radio.1.ExtensionChannel"), _, _, _))
    .Times(1).WillOnce(Return(0));

    int result = HDK_Device_SetValue((void*)mockDeviceCtx, eValue, pStruct);
    EXPECT_EQ(result, 1);

    // Free the allocated memory
    free(pMember1);
    free(pMember2);
    free(pMember3);
    free(pMember4);
    free(pStruct);
}

TEST_F(CcspHomeSecurityHDKDeviceFixture, HDK_Device_SetValue_WLanChannelWidth_SUCCESS_2) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WLanChannelWidth;
    char mockPathVal[] = "Device.WiFi.Radio.1";
    char mockAlias[] = "Radio0";

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    HDK_Member__STRING__* pMember1 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember1, nullptr);

    HDK_Member__INT__* pMember2 = (HDK_Member__INT__*) malloc(sizeof(HDK_Member__INT__));
    ASSERT_NE(pMember2, nullptr);

    HDK_Member__INT__* pMember3 = (HDK_Member__INT__*) malloc(sizeof(HDK_Member__INT__));
    ASSERT_NE(pMember3, nullptr);

    HDK_Member__INT__* pMember4 = (HDK_Member__INT__*) malloc(sizeof(HDK_Member__INT__));
    ASSERT_NE(pMember4, nullptr);

    pMember1->node.element = HDK_Element_PN_RadioID;
    pMember1->node.type = HDK_Type__STRING__;
    pMember1->node.pNext = (HDK_Member*)pMember2;
    pMember1->pszValue = strdup("Radio0");

    pMember2->node.element = HDK_Element_PN_ChannelWidth;
    pMember2->node.type = HDK_Type__INT__;
    pMember2->node.pNext = (HDK_Member*)pMember3;
    pMember2->iValue = 0;

    pMember3->node.element = HDK_Element_PN_SecondaryChannel;
    pMember3->node.type = HDK_Type__INT__;
    pMember3->node.pNext = (HDK_Member*)pMember4;
    pMember3->iValue = 0;

    pMember4->node.element = HDK_Element_PN_Channel;
    pMember4->node.type = HDK_Type__INT__;
    pMember4->node.pNext = nullptr;
    pMember4->iValue = 20;

    pStruct->pHead = (HDK_Member*)pMember1;
    pStruct->pTail = (HDK_Member*)pMember4;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.WiFi.Radio.1.Alias"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockAlias, mockAlias + strlen(mockAlias) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_SetParamVal(_, StrEq("Device.WiFi.Radio.1.OperatingChannelBandwidth"), _, _, _))
    .Times(1).WillOnce(Return(0));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_SetParamVal(_, StrEq("Device.WiFi.Radio.1.ExtensionChannel"), _, _, _))
    .Times(1).WillOnce(Return(0));

    int result = HDK_Device_SetValue((void*)mockDeviceCtx, eValue, pStruct);
    EXPECT_EQ(result, 1);

    // Free the allocated memory
    free(pMember1);
    free(pMember2);
    free(pMember3);
    free(pMember4);
    free(pStruct);
}

TEST_F(CcspHomeSecurityHDKDeviceFixture, HDK_Device_SetValue_WLanChannelWidth_SUCCESS_3) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WLanChannelWidth;
    char mockPathVal[] = "Device.WiFi.Radio.1";
    char mockAlias[] = "Radio0";

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    HDK_Member__STRING__* pMember1 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember1, nullptr);

    HDK_Member__INT__* pMember2 = (HDK_Member__INT__*) malloc(sizeof(HDK_Member__INT__));
    ASSERT_NE(pMember2, nullptr);

    HDK_Member__INT__* pMember3 = (HDK_Member__INT__*) malloc(sizeof(HDK_Member__INT__));
    ASSERT_NE(pMember3, nullptr);

    HDK_Member__INT__* pMember4 = (HDK_Member__INT__*) malloc(sizeof(HDK_Member__INT__));
    ASSERT_NE(pMember4, nullptr);

    pMember1->node.element = HDK_Element_PN_RadioID;
    pMember1->node.type = HDK_Type__STRING__;
    pMember1->node.pNext = (HDK_Member*)pMember2;
    pMember1->pszValue = strdup("Radio0");

    pMember2->node.element = HDK_Element_PN_ChannelWidth;
    pMember2->node.type = HDK_Type__INT__;
    pMember2->node.pNext = (HDK_Member*)pMember3;
    pMember2->iValue = 40;

    pMember3->node.element = HDK_Element_PN_SecondaryChannel;
    pMember3->node.type = HDK_Type__INT__;
    pMember3->node.pNext = (HDK_Member*)pMember4;
    pMember3->iValue = 10;

    pMember4->node.element = HDK_Element_PN_Channel;
    pMember4->node.type = HDK_Type__INT__;
    pMember4->node.pNext = nullptr;
    pMember4->iValue = 20;

    pStruct->pHead = (HDK_Member*)pMember1;
    pStruct->pTail = (HDK_Member*)pMember4;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.WiFi.Radio.1.Alias"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockAlias, mockAlias + strlen(mockAlias) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_SetParamVal(_, StrEq("Device.WiFi.Radio.1.OperatingChannelBandwidth"), _, _, _))
    .Times(1).WillOnce(Return(0));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_SetParamVal(_, StrEq("Device.WiFi.Radio.1.ExtensionChannel"), _, _, _))
    .Times(1).WillOnce(Return(0));

    int result = HDK_Device_SetValue((void*)mockDeviceCtx, eValue, pStruct);
    EXPECT_EQ(result, 1);

    // Free the allocated memory
    free(pMember1);
    free(pMember2);
    free(pMember3);
    free(pMember4);
    free(pStruct);
}

TEST_F(CcspHomeSecurityHDKDeviceFixture, HDK_Device_SetValue_WLanChannelWidth_FAIL_1) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WLanChannelWidth;

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

     HDK_Member__STRING__* pMember1 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember1, nullptr);

    pMember1->node.element = HDK_Element_PN_RadioID;
    pMember1->node.type = HDK_Type__STRING__;
    pMember1->node.pNext = nullptr;
    pMember1->pszValue = strdup("Radio0");

    pStruct->pHead = (HDK_Member*)pMember1;
    pStruct->pTail = (HDK_Member*)pMember1;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .Times(1).WillOnce(Return(1));

    int result = HDK_Device_SetValue((void*)mockDeviceCtx, eValue, pStruct);
    EXPECT_EQ(result, 0);

    // Free the allocated memory
    free(pMember1);
    free(pStruct);
}

TEST_F(CcspHomeSecurityHDKDeviceFixture, HDK_Device_SetValue_WLanChannelWidth_FAIL_2) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WLanChannelWidth;
    char mockPathVal[] = "Device.WiFi.Radio.1";
    char mockAlias[] = "Radio0";

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    HDK_Member__STRING__* pMember1 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember1, nullptr);

    pMember1->node.element = HDK_Element_PN_RadioID;
    pMember1->node.type = HDK_Type__STRING__;
    pMember1->node.pNext = nullptr;
    pMember1->pszValue = strdup("Radio1");

    pStruct->pHead = (HDK_Member*)pMember1;
    pStruct->pTail = (HDK_Member*)pMember1;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.WiFi.Radio.1.Alias"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockAlias, mockAlias + strlen(mockAlias) + 1),
             Return(0)
    ));

    int result = HDK_Device_SetValue((void*)mockDeviceCtx, eValue, pStruct);
    EXPECT_EQ(result, 0);

    // Free the allocated memory
    free(pMember1);
    free(pStruct);
}

TEST_F(CcspHomeSecurityHDKDeviceFixture, HDK_Device_SetValue_WLanChannelWidth_FAIL_3) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WLanChannelWidth;
    char mockPathVal[] = "Device.WiFi.Radio.1";
    char mockAlias[] = "Radio0";

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    HDK_Member__STRING__* pMember1 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember1, nullptr);

    pMember1->node.element = HDK_Element_PN_RadioID;
    pMember1->node.type = HDK_Type__STRING__;
    pMember1->node.pNext = nullptr;
    pMember1->pszValue = strdup("Radio0");

    pStruct->pHead = (HDK_Member*)pMember1;
    pStruct->pTail = (HDK_Member*)pMember1;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.WiFi.Radio.1.Alias"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockAlias, mockAlias + strlen(mockAlias) + 1),
             Return(0)
    ));

    int result = HDK_Device_SetValue((void*)mockDeviceCtx, eValue, pStruct);
    EXPECT_EQ(result, 0);

    // Free the allocated memory
    free(pMember1);
    free(pStruct);
}

TEST_F(CcspHomeSecurityHDKDeviceFixture, HDK_Device_SetValue_WLanChannel_SUCCESS_1) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WLanChannel;
    char mockPathVal[] = "Device.WiFi.Radio.1";
    char mockAlias[] = "Radio0";

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    HDK_Member__STRING__* pMember1 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember1, nullptr);

    HDK_Member__INT__* pMember2 = (HDK_Member__INT__*) malloc(sizeof(HDK_Member__INT__));
    ASSERT_NE(pMember2, nullptr);

    pMember1->node.element = HDK_Element_PN_RadioID;
    pMember1->node.type = HDK_Type__STRING__;
    pMember1->node.pNext = (HDK_Member*)pMember2;
    pMember1->pszValue = strdup("Radio0");

    pMember2->node.element = HDK_Element_PN_Channel;
    pMember2->node.type = HDK_Type__INT__;
    pMember2->node.pNext = nullptr;
    pMember2->iValue = 20;

    pStruct->pHead = (HDK_Member*)pMember1;
    pStruct->pTail = (HDK_Member*)pMember2;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.WiFi.Radio.1.Alias"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockAlias, mockAlias + strlen(mockAlias) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_SetParamVal(_, StrEq("Device.WiFi.Radio.1.Channel"), _, _, _))
    .Times(1).WillOnce(Return(0));

    int result = HDK_Device_SetValue((void*)mockDeviceCtx, eValue, pStruct);
    EXPECT_EQ(result, 1);

    // Free the allocated memory
    free(pMember1);
    free(pMember2);
    free(pStruct);
}

TEST_F(CcspHomeSecurityHDKDeviceFixture, HDK_Device_SetValue_WLanChannel_SUCCESS_2) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WLanChannel;
    char mockPathVal[] = "Device.WiFi.Radio.1";
    char mockAlias[] = "Radio0";

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    HDK_Member__STRING__* pMember1 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember1, nullptr);

    HDK_Member__INT__* pMember2 = (HDK_Member__INT__*) malloc(sizeof(HDK_Member__INT__));
    ASSERT_NE(pMember2, nullptr);

    pMember1->node.element = HDK_Element_PN_RadioID;
    pMember1->node.type = HDK_Type__STRING__;
    pMember1->node.pNext = (HDK_Member*)pMember2;
    pMember1->pszValue = strdup("Radio0");

    pMember2->node.element = HDK_Element_PN_Channel;
    pMember2->node.type = HDK_Type__INT__;
    pMember2->node.pNext = nullptr;
    pMember2->iValue = 0;

    pStruct->pHead = (HDK_Member*)pMember1;
    pStruct->pTail = (HDK_Member*)pMember2;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.WiFi.Radio.1.Alias"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockAlias, mockAlias + strlen(mockAlias) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_SetParamVal(_, StrEq("Device.WiFi.Radio.1.AutoChannelEnable"), _, _, _))
    .Times(1).WillOnce(Return(0));

    int result = HDK_Device_SetValue((void*)mockDeviceCtx, eValue, pStruct);
    EXPECT_EQ(result, 1);

    // Free the allocated memory
    free(pMember1);
    free(pMember2);
    free(pStruct);
}

TEST_F(CcspHomeSecurityHDKDeviceFixture, HDK_Device_SetValue_WLanChannel_FAIL_1) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WLanChannel;
    char mockPathVal[] = "Device.WiFi.Radio.1";
    char mockAlias[] = "Radio0";

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    HDK_Member__STRING__* pMember1 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember1, nullptr);

    pMember1->node.element = HDK_Element_PN_RadioID;
    pMember1->node.type = HDK_Type__STRING__;
    pMember1->node.pNext = nullptr;
    pMember1->pszValue = strdup("Radio1");

    pStruct->pHead = (HDK_Member*)pMember1;
    pStruct->pTail = (HDK_Member*)pMember1;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.WiFi.Radio.1.Alias"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockAlias, mockAlias + strlen(mockAlias) + 1),
             Return(0)
    ));

    int result = HDK_Device_SetValue((void*)mockDeviceCtx, eValue, pStruct);
    EXPECT_EQ(result, 0);

    // Free the allocated memory
    free(pMember1);
    free(pStruct);
}

TEST_F(CcspHomeSecurityHDKDeviceFixture, HDK_Device_SetValue_WLanChannel_FAIL_2) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WLanChannel;

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

     HDK_Member__STRING__* pMember1 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember1, nullptr);

    pMember1->node.element = HDK_Element_PN_RadioID;
    pMember1->node.type = HDK_Type__STRING__;
    pMember1->node.pNext = nullptr;
    pMember1->pszValue = strdup("Radio0");

    pStruct->pHead = (HDK_Member*)pMember1;
    pStruct->pTail = (HDK_Member*)pMember1;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .Times(1).WillOnce(Return(1));

    int result = HDK_Device_SetValue((void*)mockDeviceCtx, eValue, pStruct);
    EXPECT_EQ(result, 0);

    // Free the allocated memory
    free(pMember1);
    free(pStruct);
}

TEST_F(CcspHomeSecurityHDKDeviceFixture, HDK_Device_SetValue_WLanQoS_SUCCESS) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WLanQoS;
    char mockPathVal[] = "Device.WiFi.Radio.1";
    char mockAlias[] = "Radio0";

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    HDK_Member__STRING__* pMember1 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember1, nullptr);

    pMember1->node.element = HDK_Element_PN_RadioID;
    pMember1->node.type = HDK_Type__STRING__;
    pMember1->node.pNext = nullptr;
    pMember1->pszValue = strdup("Radio0");

    pStruct->pHead = (HDK_Member*)pMember1;
    pStruct->pTail = (HDK_Member*)pMember1;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.WiFi.Radio.1.Alias"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockAlias, mockAlias + strlen(mockAlias) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_Commit(_, StrEq("Device.WiFi.Radio.1."))).Times(1).WillOnce(Return(0));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_SetParamVal(_, StrEq("Device.WiFi.Radio.1.X_CISCO_COM_ApplySetting"), _, _, _))
    .Times(1).WillOnce(Return(0));

    int result = HDK_Device_SetValue((void*)mockDeviceCtx, eValue, pStruct);
    EXPECT_EQ(result, 1);

    // Free the allocated memory
    free(pMember1);
    free(pStruct);
}

TEST_F(CcspHomeSecurityHDKDeviceFixture, HDK_Device_SetValue_WLanQoS_FAIL_1) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WLanQoS;

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

     HDK_Member__STRING__* pMember1 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember1, nullptr);

    pMember1->node.element = HDK_Element_PN_RadioID;
    pMember1->node.type = HDK_Type__STRING__;
    pMember1->node.pNext = nullptr;
    pMember1->pszValue = strdup("Radio0");

    pStruct->pHead = (HDK_Member*)pMember1;
    pStruct->pTail = (HDK_Member*)pMember1;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .Times(1).WillOnce(Return(1));

    int result = HDK_Device_SetValue((void*)mockDeviceCtx, eValue, pStruct);
    EXPECT_EQ(result, 0);

    // Free the allocated memory
    free(pMember1);
    free(pStruct);
}

TEST_F(CcspHomeSecurityHDKDeviceFixture, HDK_Device_SetValue_WLanQoS_FAIL_2) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WLanQoS;
    char mockPathVal[] = "Device.WiFi.Radio.1";
    char mockAlias[] = "Radio0";

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    HDK_Member__STRING__* pMember1 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember1, nullptr);

    pMember1->node.element = HDK_Element_PN_RadioID;
    pMember1->node.type = HDK_Type__STRING__;
    pMember1->node.pNext = nullptr;
    pMember1->pszValue = strdup("Radio1");

    pStruct->pHead = (HDK_Member*)pMember1;
    pStruct->pTail = (HDK_Member*)pMember1;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.WiFi.Radio.1.Alias"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockAlias, mockAlias + strlen(mockAlias) + 1),
             Return(0)
    ));

    int result = HDK_Device_SetValue((void*)mockDeviceCtx, eValue, pStruct);
    EXPECT_EQ(result, 0);

    // Free the allocated memory
    free(pMember1);
    free(pStruct);
}

TEST_F(CcspHomeSecurityHDKDeviceFixture, HDK_Device_SetValue_WLanQoS_FAIL_3) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WLanQoS;
    char mockPathVal[] = "Device.WiFi.Radio.1";
    char mockAlias[] = "Radio0";

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    HDK_Member__STRING__* pMember1 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember1, nullptr);

    pMember1->node.element = HDK_Element_PN_RadioID;
    pMember1->node.type = HDK_Type__STRING__;
    pMember1->node.pNext = nullptr;
    pMember1->pszValue = strdup("Radio0");

    pStruct->pHead = (HDK_Member*)pMember1;
    pStruct->pTail = (HDK_Member*)pMember1;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.WiFi.Radio.1.Alias"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockAlias, mockAlias + strlen(mockAlias) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_Commit(_, StrEq("Device.WiFi.Radio.1."))).Times(1).WillOnce(Return(1));


    int result = HDK_Device_SetValue((void*)mockDeviceCtx, eValue, pStruct);
    EXPECT_EQ(result, 0);

    // Free the allocated memory
    free(pMember1);
    free(pStruct);
}

TEST_F(CcspHomeSecurityHDKDeviceFixture, HDK_Device_SetValue_WLanKeyRenewal_SUCCESS) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WLanKeyRenewal;
    char mockPathVal[] = "Device.WiFi.Radio.1";
    char mockApPathVal[] = "Device.WiFi.AccessPoint.3";
    char mockAlias[] = "Radio0";

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    HDK_Member__STRING__* pMember1 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember1, nullptr);

    HDK_Member__INT__* pMember2 = (HDK_Member__INT__*) malloc(sizeof(HDK_Member__INT__));
    ASSERT_NE(pMember2, nullptr);

    pMember1->node.element = HDK_Element_PN_RadioID;
    pMember1->node.type = HDK_Type__STRING__;
    pMember1->node.pNext = (HDK_Member*)pMember2;
    pMember1->pszValue = strdup("Radio0");

    pMember2->node.element = HDK_Element_PN_KeyRenewal;
    pMember2->node.type = HDK_Type__INT__;
    pMember2->node.pNext = nullptr;
    pMember2->iValue = 1;

    pStruct->pHead = (HDK_Member*)pMember1;
    pStruct->pTail = (HDK_Member*)pMember2;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.WiFi.Radio.1.Alias"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockAlias, mockAlias + strlen(mockAlias) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiAp"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockApPathVal, mockApPathVal + strlen(mockApPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_SetParamVal(_, StrEq("Device.WiFi.AccessPoint.3.Security.RekeyingInterval"), _, _, _))
    .Times(1).WillOnce(Return(0));

    int result = HDK_Device_SetValue((void*)mockDeviceCtx, eValue, pStruct);
    EXPECT_EQ(result, 1);

    // Free the allocated memory
    free(pMember1);
    free(pMember2);
    free(pStruct);
}

TEST_F(CcspHomeSecurityHDKDeviceFixture, HDK_Device_SetValue_WLanKeyRenewal_FAIL_1) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WLanKeyRenewal;

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

     HDK_Member__STRING__* pMember1 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember1, nullptr);

    pMember1->node.element = HDK_Element_PN_RadioID;
    pMember1->node.type = HDK_Type__STRING__;
    pMember1->node.pNext = nullptr;
    pMember1->pszValue = strdup("Radio0");

    pStruct->pHead = (HDK_Member*)pMember1;
    pStruct->pTail = (HDK_Member*)pMember1;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .Times(1).WillOnce(Return(1));

    int result = HDK_Device_SetValue((void*)mockDeviceCtx, eValue, pStruct);
    EXPECT_EQ(result, 0);

    // Free the allocated memory
    free(pMember1);
    free(pStruct);
}

TEST_F(CcspHomeSecurityHDKDeviceFixture, HDK_Device_SetValue_WLanKeyRenewal_FAIL_2) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WLanKeyRenewal;
    char mockPathVal[] = "Device.WiFi.Radio.1";
    char mockAlias[] = "Radio0";

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    HDK_Member__STRING__* pMember1 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember1, nullptr);

    pMember1->node.element = HDK_Element_PN_RadioID;
    pMember1->node.type = HDK_Type__STRING__;
    pMember1->node.pNext = nullptr;
    pMember1->pszValue = strdup("Radio1");

    pStruct->pHead = (HDK_Member*)pMember1;
    pStruct->pTail = (HDK_Member*)pMember1;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.WiFi.Radio.1.Alias"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockAlias, mockAlias + strlen(mockAlias) + 1),
             Return(0)
    ));

    int result = HDK_Device_SetValue((void*)mockDeviceCtx, eValue, pStruct);
    EXPECT_EQ(result, 0);

    // Free the allocated memory
    free(pMember1);
    free(pStruct);
}

TEST_F(CcspHomeSecurityHDKDeviceFixture, HDK_Device_SetValue_WLanKeyRenewal_FAIL_3) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WLanKeyRenewal;
    char mockPathVal[] = "Device.WiFi.Radio.1";
    char mockAlias[] = "Radio0";

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    HDK_Member__STRING__* pMember1 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember1, nullptr);

    HDK_Member__INT__* pMember2 = (HDK_Member__INT__*) malloc(sizeof(HDK_Member__INT__));
    ASSERT_NE(pMember2, nullptr);

    pMember1->node.element = HDK_Element_PN_RadioID;
    pMember1->node.type = HDK_Type__STRING__;
    pMember1->node.pNext = (HDK_Member*)pMember2;
    pMember1->pszValue = strdup("Radio0");

    pMember2->node.element = HDK_Element_PN_KeyRenewal;
    pMember2->node.type = HDK_Type__INT__;
    pMember2->node.pNext = nullptr;
    pMember2->iValue = 1;

    pStruct->pHead = (HDK_Member*)pMember1;
    pStruct->pTail = (HDK_Member*)pMember2;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.WiFi.Radio.1.Alias"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockAlias, mockAlias + strlen(mockAlias) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiAp"), _, _))
    .Times(1).WillOnce(Return(1));


    int result = HDK_Device_SetValue((void*)mockDeviceCtx, eValue, pStruct);
    EXPECT_EQ(result, 0);

    // Free the allocated memory
    free(pMember1);
    free(pMember2);
    free(pStruct);
}

TEST_F(CcspHomeSecurityHDKDeviceFixture, HDK_Device_SetValue_WLanRadiusIP1_SUCCESS) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WLanRadiusIP1;
    char mockPathVal[] = "Device.WiFi.Radio.1";
    char mockApPathVal[] = "Device.WiFi.AccessPoint.3";
    char mockAlias[] = "Radio0";

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    HDK_Member__STRING__* pMember1 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember1, nullptr);

    HDK_Member_IPAddress* pMember2 = (HDK_Member_IPAddress*) malloc(sizeof(HDK_Member_IPAddress));
    ASSERT_NE(pMember2, nullptr);

    HDK_Member__INT__* pMember3 = (HDK_Member__INT__*) malloc(sizeof(HDK_Member__INT__));
    ASSERT_NE(pMember3, nullptr);

    HDK_Member__STRING__* pMember4 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember4, nullptr);

    pMember1->node.element = HDK_Element_PN_RadioID;
    pMember1->node.type = HDK_Type__STRING__;
    pMember1->node.pNext = (HDK_Member*)pMember2;
    pMember1->pszValue = strdup("Radio0");

    pMember2->node.element = HDK_Element_PN_RadiusIP1;
    pMember2->node.type = HDK_Type__IPADDRESS__;
    pMember2->node.pNext = (HDK_Member*)pMember3;
    pMember2->ipAddress.a = 192;
    pMember2->ipAddress.b = 168;
    pMember2->ipAddress.c = 1;
    pMember2->ipAddress.d = 1;

    pMember3->node.element = HDK_Element_PN_RadiusPort1;
    pMember3->node.type = HDK_Type__INT__;
    pMember3->node.pNext = (HDK_Member*)pMember4;
    pMember3->iValue = 1;

    pMember4->node.element = HDK_Element_PN_RadiusSecret1;
    pMember4->node.type = HDK_Type__STRING__;
    pMember4->node.pNext = nullptr;
    pMember4->pszValue = strdup("Secret Value");

    pStruct->pHead = (HDK_Member*)pMember1;
    pStruct->pTail = (HDK_Member*)pMember4;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.WiFi.Radio.1.Alias"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockAlias, mockAlias + strlen(mockAlias) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiAp"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockApPathVal, mockApPathVal + strlen(mockApPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_SetParamVal(_, _, _, _, _)).WillRepeatedly(Return(0));

    int result = HDK_Device_SetValue((void*)mockDeviceCtx, eValue, pStruct);
    EXPECT_EQ(result, 1);

    // Free the allocated memory
    free(pMember1);
    free(pMember2);
    free(pMember3);
    free(pMember4);
    free(pStruct);
}

TEST_F(CcspHomeSecurityHDKDeviceFixture, HDK_Device_SetValue_WLanRadiusIP1_FAIL_1) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WLanRadiusIP1;

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

     HDK_Member__STRING__* pMember1 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember1, nullptr);

    pMember1->node.element = HDK_Element_PN_RadioID;
    pMember1->node.type = HDK_Type__STRING__;
    pMember1->node.pNext = nullptr;
    pMember1->pszValue = strdup("Radio0");

    pStruct->pHead = (HDK_Member*)pMember1;
    pStruct->pTail = (HDK_Member*)pMember1;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .Times(1).WillOnce(Return(1));

    int result = HDK_Device_SetValue((void*)mockDeviceCtx, eValue, pStruct);
    EXPECT_EQ(result, 0);

    // Free the allocated memory
    free(pMember1);
    free(pStruct);
}

TEST_F(CcspHomeSecurityHDKDeviceFixture, HDK_Device_SetValue_WLanRadiusIP1_FAIL_2) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WLanRadiusIP1;
    char mockPathVal[] = "Device.WiFi.Radio.1";
    char mockAlias[] = "Radio0";

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    HDK_Member__STRING__* pMember1 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember1, nullptr);

    pMember1->node.element = HDK_Element_PN_RadioID;
    pMember1->node.type = HDK_Type__STRING__;
    pMember1->node.pNext = nullptr;
    pMember1->pszValue = strdup("Radio1");

    pStruct->pHead = (HDK_Member*)pMember1;
    pStruct->pTail = (HDK_Member*)pMember1;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.WiFi.Radio.1.Alias"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockAlias, mockAlias + strlen(mockAlias) + 1),
             Return(0)
    ));

    int result = HDK_Device_SetValue((void*)mockDeviceCtx, eValue, pStruct);
    EXPECT_EQ(result, 0);

    // Free the allocated memory
    free(pMember1);
    free(pStruct);
}

TEST_F(CcspHomeSecurityHDKDeviceFixture, HDK_Device_SetValue_WLanRadiusIP1_FAIL_3) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WLanRadiusIP1;
    char mockPathVal[] = "Device.WiFi.Radio.1";
    char mockAlias[] = "Radio0";

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    HDK_Member__STRING__* pMember1 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember1, nullptr);

    pMember1->node.element = HDK_Element_PN_RadioID;
    pMember1->node.type = HDK_Type__STRING__;
    pMember1->node.pNext = nullptr;
    pMember1->pszValue = strdup("Radio0");

    pStruct->pHead = (HDK_Member*)pMember1;
    pStruct->pTail = (HDK_Member*)pMember1;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.WiFi.Radio.1.Alias"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockAlias, mockAlias + strlen(mockAlias) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiAp"), _, _))
    .Times(1).WillOnce(Return(1));


    int result = HDK_Device_SetValue((void*)mockDeviceCtx, eValue, pStruct);
    EXPECT_EQ(result, 0);

    // Free the allocated memory
    free(pMember1);
    free(pStruct);
}

TEST_F(CcspHomeSecurityHDKDeviceFixture, HDK_Device_SetValue_WLanSecurityEnabled_SUCCESS) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WLanSecurityEnabled;
    char mockPathVal[] = "Device.WiFi.Radio.1";
    char mockApPathVal[] = "Device.WiFi.AccessPoint.3";
    char mockAlias[] = "Radio0";

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    HDK_Member__STRING__* pMember1 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember1, nullptr);

    HDK_Member__INT__* pMember2 = (HDK_Member__INT__*) malloc(sizeof(HDK_Member__INT__));
    ASSERT_NE(pMember2, nullptr);

    pMember1->node.element = HDK_Element_PN_RadioID;
    pMember1->node.type = HDK_Type__STRING__;
    pMember1->node.pNext = (HDK_Member*)pMember2;
    pMember1->pszValue = strdup("Radio0");

    pMember2->node.element = HDK_Element_PN_Enabled;
    pMember2->node.type = HDK_Type__BOOL__;
    pMember2->node.pNext = nullptr;
    pMember2->iValue = 0;

    pStruct->pHead = (HDK_Member*)pMember1;
    pStruct->pTail = (HDK_Member*)pMember2;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.WiFi.Radio.1.Alias"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockAlias, mockAlias + strlen(mockAlias) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiAp"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockApPathVal, mockApPathVal + strlen(mockApPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_SetParamVal(_, StrEq("Device.WiFi.AccessPoint.3.Security.ModeEnabled"), _, _, _))
    .Times(1).WillOnce(Return(0));

    int result = HDK_Device_SetValue((void*)mockDeviceCtx, eValue, pStruct);
    EXPECT_EQ(result, 1);

    // Free the allocated memory
    free(pMember1);
    free(pMember2);
    free(pStruct);
}

TEST_F(CcspHomeSecurityHDKDeviceFixture, HDK_Device_SetValue_WLanSecurityEnabled_FAIL_1) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WLanSecurityEnabled;

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

     HDK_Member__STRING__* pMember1 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember1, nullptr);

    pMember1->node.element = HDK_Element_PN_RadioID;
    pMember1->node.type = HDK_Type__STRING__;
    pMember1->node.pNext = nullptr;
    pMember1->pszValue = strdup("Radio0");

    pStruct->pHead = (HDK_Member*)pMember1;
    pStruct->pTail = (HDK_Member*)pMember1;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .Times(1).WillOnce(Return(1));

    int result = HDK_Device_SetValue((void*)mockDeviceCtx, eValue, pStruct);
    EXPECT_EQ(result, 0);

    // Free the allocated memory
    free(pMember1);
    free(pStruct);
}

TEST_F(CcspHomeSecurityHDKDeviceFixture, HDK_Device_SetValue_WLanSecurityEnabled_FAIL_2) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WLanSecurityEnabled;
    char mockPathVal[] = "Device.WiFi.Radio.1";
    char mockAlias[] = "Radio0";

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    HDK_Member__STRING__* pMember1 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember1, nullptr);

    pMember1->node.element = HDK_Element_PN_RadioID;
    pMember1->node.type = HDK_Type__STRING__;
    pMember1->node.pNext = nullptr;
    pMember1->pszValue = strdup("Radio1");

    pStruct->pHead = (HDK_Member*)pMember1;
    pStruct->pTail = (HDK_Member*)pMember1;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.WiFi.Radio.1.Alias"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockAlias, mockAlias + strlen(mockAlias) + 1),
             Return(0)
    ));

    int result = HDK_Device_SetValue((void*)mockDeviceCtx, eValue, pStruct);
    EXPECT_EQ(result, 0);

    // Free the allocated memory
    free(pMember1);
    free(pStruct);
}

TEST_F(CcspHomeSecurityHDKDeviceFixture, HDK_Device_SetValue_WLanSecurityEnabled_FAIL_3) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WLanSecurityEnabled;
    char mockPathVal[] = "Device.WiFi.Radio.1";
    char mockAlias[] = "Radio0";

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    HDK_Member__STRING__* pMember1 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember1, nullptr);

    pMember1->node.element = HDK_Element_PN_RadioID;
    pMember1->node.type = HDK_Type__STRING__;
    pMember1->node.pNext = nullptr;
    pMember1->pszValue = strdup("Radio0");

    pStruct->pHead = (HDK_Member*)pMember1;
    pStruct->pTail = (HDK_Member*)pMember1;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.WiFi.Radio.1.Alias"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockAlias, mockAlias + strlen(mockAlias) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiAp"), _, _))
    .Times(1).WillOnce(Return(1));


    int result = HDK_Device_SetValue((void*)mockDeviceCtx, eValue, pStruct);
    EXPECT_EQ(result, 0);

    // Free the allocated memory
    free(pMember1);
    free(pStruct);
}

TEST_F(CcspHomeSecurityHDKDeviceFixture, HDK_Device_SetValue_WLanType_SUCCESS_1) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WLanType;
    char mockPathVal[] = "Device.WiFi.Radio.1";
    char mockApPathVal[] = "Device.WiFi.AccessPoint.3";
    char mockAlias[] = "Radio0";

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    HDK_Member__STRING__* pMember1 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember1, nullptr);

    HDK_Member__INT__* pMember2 = (HDK_Member__INT__*) malloc(sizeof(HDK_Member__INT__));
    ASSERT_NE(pMember2, nullptr);

    HDK_Member__INT__* pMember3 = (HDK_Member__INT__*) malloc(sizeof(HDK_Member__INT__));
    ASSERT_NE(pMember3, nullptr);

    HDK_Member__INT__* pMember4 = (HDK_Member__INT__*) malloc(sizeof(HDK_Member__INT__));
    ASSERT_NE(pMember4, nullptr);

    pMember1->node.element = HDK_Element_PN_RadioID;
    pMember1->node.type = HDK_Type__STRING__;
    pMember1->node.pNext = (HDK_Member*)pMember2;
    pMember1->pszValue = strdup("Radio0");

    pMember2->node.element = HDK_Element_PN_Enabled;
    pMember2->node.type = HDK_Type__BOOL__;
    pMember2->node.pNext = (HDK_Member*)pMember3;
    pMember2->iValue = 1;

    pMember3->node.element = HDK_Element_PN_Type;
    pMember3->node.type = HDK_Type_PN_WiFiSecurity;
    pMember3->node.pNext = (HDK_Member*)pMember4;
    pMember3->iValue = HDK_Enum_PN_WiFiSecurity_NONE;

    pMember4->node.element = HDK_Element_PN_Encryption;
    pMember4->node.type = HDK_Type_PN_WiFiEncryption;
    pMember4->node.pNext = nullptr;
    pMember4->iValue = HDK_Enum_PN_WiFiEncryption_AES;

    pStruct->pHead = (HDK_Member*)pMember1;
    pStruct->pTail = (HDK_Member*)pMember4;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.WiFi.Radio.1.Alias"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockAlias, mockAlias + strlen(mockAlias) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiAp"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockApPathVal, mockApPathVal + strlen(mockApPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_SetParamVal(_, StrEq("Device.WiFi.AccessPoint.3.Security.ModeEnabled"), _, _, _))
    .Times(1).WillOnce(Return(0));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_SetParamVal(_, StrEq("Device.WiFi.AccessPoint.3.Security.X_CISCO_COM_EncryptionMethod"), _, _, _))
    .Times(1).WillOnce(Return(0));

    int result = HDK_Device_SetValue((void*)mockDeviceCtx, eValue, pStruct);
    EXPECT_EQ(result, 1);

    // Free the allocated memory
    free(pMember1);
    free(pMember2);
    free(pMember3);
    free(pMember4);
    free(pStruct);
}

TEST_F(CcspHomeSecurityHDKDeviceFixture, HDK_Device_SetValue_WLanType_SUCCESS_2) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WLanType;
    char mockPathVal[] = "Device.WiFi.Radio.1";
    char mockApPathVal[] = "Device.WiFi.AccessPoint.3";
    char mockAlias[] = "Radio0";

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    HDK_Member__STRING__* pMember1 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember1, nullptr);

    HDK_Member__INT__* pMember2 = (HDK_Member__INT__*) malloc(sizeof(HDK_Member__INT__));
    ASSERT_NE(pMember2, nullptr);

    HDK_Member__INT__* pMember3 = (HDK_Member__INT__*) malloc(sizeof(HDK_Member__INT__));
    ASSERT_NE(pMember3, nullptr);

    HDK_Member__INT__* pMember4 = (HDK_Member__INT__*) malloc(sizeof(HDK_Member__INT__));
    ASSERT_NE(pMember4, nullptr);

    pMember1->node.element = HDK_Element_PN_RadioID;
    pMember1->node.type = HDK_Type__STRING__;
    pMember1->node.pNext = (HDK_Member*)pMember2;
    pMember1->pszValue = strdup("Radio0");

    pMember2->node.element = HDK_Element_PN_Enabled;
    pMember2->node.type = HDK_Type__BOOL__;
    pMember2->node.pNext = (HDK_Member*)pMember3;
    pMember2->iValue = 1;

    pMember3->node.element = HDK_Element_PN_Type;
    pMember3->node.type = HDK_Type_PN_WiFiSecurity;
    pMember3->node.pNext = (HDK_Member*)pMember4;
    pMember3->iValue = HDK_Enum_PN_WiFiSecurity_WEP_64;

    pMember4->node.element = HDK_Element_PN_Encryption;
    pMember4->node.type = HDK_Type_PN_WiFiEncryption;
    pMember4->node.pNext = nullptr;
    pMember4->iValue = HDK_Enum_PN_WiFiEncryption_TKIP;

    pStruct->pHead = (HDK_Member*)pMember1;
    pStruct->pTail = (HDK_Member*)pMember4;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.WiFi.Radio.1.Alias"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockAlias, mockAlias + strlen(mockAlias) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiAp"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockApPathVal, mockApPathVal + strlen(mockApPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_SetParamVal(_, StrEq("Device.WiFi.AccessPoint.3.Security.ModeEnabled"), _, _, _))
    .Times(1).WillOnce(Return(0));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_SetParamVal(_, StrEq("Device.WiFi.AccessPoint.3.Security.X_CISCO_COM_EncryptionMethod"), _, _, _))
    .Times(1).WillOnce(Return(0));

    int result = HDK_Device_SetValue((void*)mockDeviceCtx, eValue, pStruct);
    EXPECT_EQ(result, 1);

    // Free the allocated memory
    free(pMember1);
    free(pMember2);
    free(pMember3);
    free(pMember4);
    free(pStruct);
}

TEST_F(CcspHomeSecurityHDKDeviceFixture, HDK_Device_SetValue_WLanType_SUCCESS_3) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WLanType;
    char mockPathVal[] = "Device.WiFi.Radio.1";
    char mockApPathVal[] = "Device.WiFi.AccessPoint.3";
    char mockAlias[] = "Radio0";

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    HDK_Member__STRING__* pMember1 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember1, nullptr);

    HDK_Member__INT__* pMember2 = (HDK_Member__INT__*) malloc(sizeof(HDK_Member__INT__));
    ASSERT_NE(pMember2, nullptr);

    HDK_Member__INT__* pMember3 = (HDK_Member__INT__*) malloc(sizeof(HDK_Member__INT__));
    ASSERT_NE(pMember3, nullptr);

    HDK_Member__INT__* pMember4 = (HDK_Member__INT__*) malloc(sizeof(HDK_Member__INT__));
    ASSERT_NE(pMember4, nullptr);

    pMember1->node.element = HDK_Element_PN_RadioID;
    pMember1->node.type = HDK_Type__STRING__;
    pMember1->node.pNext = (HDK_Member*)pMember2;
    pMember1->pszValue = strdup("Radio0");

    pMember2->node.element = HDK_Element_PN_Enabled;
    pMember2->node.type = HDK_Type__BOOL__;
    pMember2->node.pNext = (HDK_Member*)pMember3;
    pMember2->iValue = 1;

    pMember3->node.element = HDK_Element_PN_Type;
    pMember3->node.type = HDK_Type_PN_WiFiSecurity;
    pMember3->node.pNext = (HDK_Member*)pMember4;
    pMember3->iValue = HDK_Enum_PN_WiFiSecurity_WEP_128;

    pMember4->node.element = HDK_Element_PN_Encryption;
    pMember4->node.type = HDK_Type_PN_WiFiEncryption;
    pMember4->node.pNext = nullptr;
    pMember4->iValue = HDK_Enum_PN_WiFiEncryption_TKIPORAES;

    pStruct->pHead = (HDK_Member*)pMember1;
    pStruct->pTail = (HDK_Member*)pMember4;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.WiFi.Radio.1.Alias"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockAlias, mockAlias + strlen(mockAlias) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiAp"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockApPathVal, mockApPathVal + strlen(mockApPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_SetParamVal(_, StrEq("Device.WiFi.AccessPoint.3.Security.ModeEnabled"), _, _, _))
    .Times(1).WillOnce(Return(0));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_SetParamVal(_, StrEq("Device.WiFi.AccessPoint.3.Security.X_CISCO_COM_EncryptionMethod"), _, _, _))
    .Times(1).WillOnce(Return(0));

    int result = HDK_Device_SetValue((void*)mockDeviceCtx, eValue, pStruct);
    EXPECT_EQ(result, 1);

    // Free the allocated memory
    free(pMember1);
    free(pMember2);
    free(pMember3);
    free(pMember4);
    free(pStruct);
}

TEST_F(CcspHomeSecurityHDKDeviceFixture, HDK_Device_SetValue_WLanType_SUCCESS_4) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WLanType;
    char mockPathVal[] = "Device.WiFi.Radio.1";
    char mockApPathVal[] = "Device.WiFi.AccessPoint.3";
    char mockAlias[] = "Radio0";

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    HDK_Member__STRING__* pMember1 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember1, nullptr);

    HDK_Member__INT__* pMember2 = (HDK_Member__INT__*) malloc(sizeof(HDK_Member__INT__));
    ASSERT_NE(pMember2, nullptr);

    HDK_Member__INT__* pMember3 = (HDK_Member__INT__*) malloc(sizeof(HDK_Member__INT__));
    ASSERT_NE(pMember3, nullptr);

    HDK_Member__INT__* pMember4 = (HDK_Member__INT__*) malloc(sizeof(HDK_Member__INT__));
    ASSERT_NE(pMember4, nullptr);

    pMember1->node.element = HDK_Element_PN_RadioID;
    pMember1->node.type = HDK_Type__STRING__;
    pMember1->node.pNext = (HDK_Member*)pMember2;
    pMember1->pszValue = strdup("Radio0");

    pMember2->node.element = HDK_Element_PN_Enabled;
    pMember2->node.type = HDK_Type__BOOL__;
    pMember2->node.pNext = (HDK_Member*)pMember3;
    pMember2->iValue = 1;

    pMember3->node.element = HDK_Element_PN_Type;
    pMember3->node.type = HDK_Type_PN_WiFiSecurity;
    pMember3->node.pNext = (HDK_Member*)pMember4;
    pMember3->iValue = HDK_Enum_PN_WiFiSecurity_WPA_Personal;

    pMember4->node.element = HDK_Element_PN_Encryption;
    pMember4->node.type = HDK_Type_PN_WiFiEncryption;
    pMember4->node.pNext = nullptr;
    pMember4->iValue = HDK_Enum_PN_WiFiEncryption_TKIPORAES;

    pStruct->pHead = (HDK_Member*)pMember1;
    pStruct->pTail = (HDK_Member*)pMember4;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.WiFi.Radio.1.Alias"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockAlias, mockAlias + strlen(mockAlias) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiAp"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockApPathVal, mockApPathVal + strlen(mockApPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_SetParamVal(_, StrEq("Device.WiFi.AccessPoint.3.Security.ModeEnabled"), _, _, _))
    .Times(1).WillOnce(Return(0));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_SetParamVal(_, StrEq("Device.WiFi.AccessPoint.3.Security.X_CISCO_COM_EncryptionMethod"), _, _, _))
    .Times(1).WillOnce(Return(0));

    int result = HDK_Device_SetValue((void*)mockDeviceCtx, eValue, pStruct);
    EXPECT_EQ(result, 1);

    // Free the allocated memory
    free(pMember1);
    free(pMember2);
    free(pMember3);
    free(pMember4);
    free(pStruct);
}

TEST_F(CcspHomeSecurityHDKDeviceFixture, HDK_Device_SetValue_WLanType_SUCCESS_5) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WLanType;
    char mockPathVal[] = "Device.WiFi.Radio.1";
    char mockApPathVal[] = "Device.WiFi.AccessPoint.3";
    char mockAlias[] = "Radio0";

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    HDK_Member__STRING__* pMember1 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember1, nullptr);

    HDK_Member__INT__* pMember2 = (HDK_Member__INT__*) malloc(sizeof(HDK_Member__INT__));
    ASSERT_NE(pMember2, nullptr);

    HDK_Member__INT__* pMember3 = (HDK_Member__INT__*) malloc(sizeof(HDK_Member__INT__));
    ASSERT_NE(pMember3, nullptr);

    HDK_Member__INT__* pMember4 = (HDK_Member__INT__*) malloc(sizeof(HDK_Member__INT__));
    ASSERT_NE(pMember4, nullptr);

    pMember1->node.element = HDK_Element_PN_RadioID;
    pMember1->node.type = HDK_Type__STRING__;
    pMember1->node.pNext = (HDK_Member*)pMember2;
    pMember1->pszValue = strdup("Radio0");

    pMember2->node.element = HDK_Element_PN_Enabled;
    pMember2->node.type = HDK_Type__BOOL__;
    pMember2->node.pNext = (HDK_Member*)pMember3;
    pMember2->iValue = 1;

    pMember3->node.element = HDK_Element_PN_Type;
    pMember3->node.type = HDK_Type_PN_WiFiSecurity;
    pMember3->node.pNext = (HDK_Member*)pMember4;
    pMember3->iValue = HDK_Enum_PN_WiFiSecurity_WPA2_Personal;

    pMember4->node.element = HDK_Element_PN_Encryption;
    pMember4->node.type = HDK_Type_PN_WiFiEncryption;
    pMember4->node.pNext = nullptr;
    pMember4->iValue = HDK_Enum_PN_WiFiEncryption_TKIPORAES;

    pStruct->pHead = (HDK_Member*)pMember1;
    pStruct->pTail = (HDK_Member*)pMember4;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.WiFi.Radio.1.Alias"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockAlias, mockAlias + strlen(mockAlias) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiAp"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockApPathVal, mockApPathVal + strlen(mockApPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_SetParamVal(_, StrEq("Device.WiFi.AccessPoint.3.Security.ModeEnabled"), _, _, _))
    .Times(1).WillOnce(Return(0));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_SetParamVal(_, StrEq("Device.WiFi.AccessPoint.3.Security.X_CISCO_COM_EncryptionMethod"), _, _, _))
    .Times(1).WillOnce(Return(0));

    int result = HDK_Device_SetValue((void*)mockDeviceCtx, eValue, pStruct);
    EXPECT_EQ(result, 1);

    // Free the allocated memory
    free(pMember1);
    free(pMember2);
    free(pMember3);
    free(pMember4);
    free(pStruct);
}

TEST_F(CcspHomeSecurityHDKDeviceFixture, HDK_Device_SetValue_WLanType_SUCCESS_6) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WLanType;
    char mockPathVal[] = "Device.WiFi.Radio.1";
    char mockApPathVal[] = "Device.WiFi.AccessPoint.3";
    char mockAlias[] = "Radio0";

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    HDK_Member__STRING__* pMember1 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember1, nullptr);

    HDK_Member__INT__* pMember2 = (HDK_Member__INT__*) malloc(sizeof(HDK_Member__INT__));
    ASSERT_NE(pMember2, nullptr);

    HDK_Member__INT__* pMember3 = (HDK_Member__INT__*) malloc(sizeof(HDK_Member__INT__));
    ASSERT_NE(pMember3, nullptr);

    HDK_Member__INT__* pMember4 = (HDK_Member__INT__*) malloc(sizeof(HDK_Member__INT__));
    ASSERT_NE(pMember4, nullptr);

    pMember1->node.element = HDK_Element_PN_RadioID;
    pMember1->node.type = HDK_Type__STRING__;
    pMember1->node.pNext = (HDK_Member*)pMember2;
    pMember1->pszValue = strdup("Radio0");

    pMember2->node.element = HDK_Element_PN_Enabled;
    pMember2->node.type = HDK_Type__BOOL__;
    pMember2->node.pNext = (HDK_Member*)pMember3;
    pMember2->iValue = 1;

    pMember3->node.element = HDK_Element_PN_Type;
    pMember3->node.type = HDK_Type_PN_WiFiSecurity;
    pMember3->node.pNext = (HDK_Member*)pMember4;
    pMember3->iValue = HDK_Enum_PN_WiFiSecurity_WPA_Enterprise;

    pMember4->node.element = HDK_Element_PN_Encryption;
    pMember4->node.type = HDK_Type_PN_WiFiEncryption;
    pMember4->node.pNext = nullptr;
    pMember4->iValue = HDK_Enum_PN_WiFiEncryption_TKIPORAES;

    pStruct->pHead = (HDK_Member*)pMember1;
    pStruct->pTail = (HDK_Member*)pMember4;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.WiFi.Radio.1.Alias"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockAlias, mockAlias + strlen(mockAlias) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiAp"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockApPathVal, mockApPathVal + strlen(mockApPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_SetParamVal(_, StrEq("Device.WiFi.AccessPoint.3.Security.ModeEnabled"), _, _, _))
    .Times(1).WillOnce(Return(0));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_SetParamVal(_, StrEq("Device.WiFi.AccessPoint.3.Security.X_CISCO_COM_EncryptionMethod"), _, _, _))
    .Times(1).WillOnce(Return(0));

    int result = HDK_Device_SetValue((void*)mockDeviceCtx, eValue, pStruct);
    EXPECT_EQ(result, 1);

    // Free the allocated memory
    free(pMember1);
    free(pMember2);
    free(pMember3);
    free(pMember4);
    free(pStruct);
}

TEST_F(CcspHomeSecurityHDKDeviceFixture, HDK_Device_SetValue_WLanType_SUCCESS_7) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WLanType;
    char mockPathVal[] = "Device.WiFi.Radio.1";
    char mockApPathVal[] = "Device.WiFi.AccessPoint.3";
    char mockAlias[] = "Radio0";

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    HDK_Member__STRING__* pMember1 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember1, nullptr);

    HDK_Member__INT__* pMember2 = (HDK_Member__INT__*) malloc(sizeof(HDK_Member__INT__));
    ASSERT_NE(pMember2, nullptr);

    HDK_Member__INT__* pMember3 = (HDK_Member__INT__*) malloc(sizeof(HDK_Member__INT__));
    ASSERT_NE(pMember3, nullptr);

    HDK_Member__INT__* pMember4 = (HDK_Member__INT__*) malloc(sizeof(HDK_Member__INT__));
    ASSERT_NE(pMember4, nullptr);

    pMember1->node.element = HDK_Element_PN_RadioID;
    pMember1->node.type = HDK_Type__STRING__;
    pMember1->node.pNext = (HDK_Member*)pMember2;
    pMember1->pszValue = strdup("Radio0");

    pMember2->node.element = HDK_Element_PN_Enabled;
    pMember2->node.type = HDK_Type__BOOL__;
    pMember2->node.pNext = (HDK_Member*)pMember3;
    pMember2->iValue = 1;

    pMember3->node.element = HDK_Element_PN_Type;
    pMember3->node.type = HDK_Type_PN_WiFiSecurity;
    pMember3->node.pNext = (HDK_Member*)pMember4;
    pMember3->iValue = HDK_Enum_PN_WiFiSecurity_WPA2_Enterprise;

    pMember4->node.element = HDK_Element_PN_Encryption;
    pMember4->node.type = HDK_Type_PN_WiFiEncryption;
    pMember4->node.pNext = nullptr;
    pMember4->iValue = HDK_Enum_PN_WiFiEncryption_TKIPORAES;

    pStruct->pHead = (HDK_Member*)pMember1;
    pStruct->pTail = (HDK_Member*)pMember4;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.WiFi.Radio.1.Alias"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockAlias, mockAlias + strlen(mockAlias) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiAp"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockApPathVal, mockApPathVal + strlen(mockApPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_SetParamVal(_, StrEq("Device.WiFi.AccessPoint.3.Security.ModeEnabled"), _, _, _))
    .Times(1).WillOnce(Return(0));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_SetParamVal(_, StrEq("Device.WiFi.AccessPoint.3.Security.X_CISCO_COM_EncryptionMethod"), _, _, _))
    .Times(1).WillOnce(Return(0));

    int result = HDK_Device_SetValue((void*)mockDeviceCtx, eValue, pStruct);
    EXPECT_EQ(result, 1);

    // Free the allocated memory
    free(pMember1);
    free(pMember2);
    free(pMember3);
    free(pMember4);
    free(pStruct);
}

TEST_F(CcspHomeSecurityHDKDeviceFixture, HDK_Device_SetValue_WLanType_SUCCESS_8) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WLanType;
    char mockPathVal[] = "Device.WiFi.Radio.1";
    char mockApPathVal[] = "Device.WiFi.AccessPoint.3";
    char mockAlias[] = "Radio0";

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    HDK_Member__STRING__* pMember1 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember1, nullptr);

    HDK_Member__INT__* pMember2 = (HDK_Member__INT__*) malloc(sizeof(HDK_Member__INT__));
    ASSERT_NE(pMember2, nullptr);

    HDK_Member__INT__* pMember3 = (HDK_Member__INT__*) malloc(sizeof(HDK_Member__INT__));
    ASSERT_NE(pMember3, nullptr);

    HDK_Member__INT__* pMember4 = (HDK_Member__INT__*) malloc(sizeof(HDK_Member__INT__));
    ASSERT_NE(pMember4, nullptr);

    pMember1->node.element = HDK_Element_PN_RadioID;
    pMember1->node.type = HDK_Type__STRING__;
    pMember1->node.pNext = (HDK_Member*)pMember2;
    pMember1->pszValue = strdup("Radio0");

    pMember2->node.element = HDK_Element_PN_Enabled;
    pMember2->node.type = HDK_Type__BOOL__;
    pMember2->node.pNext = (HDK_Member*)pMember3;
    pMember2->iValue = 1;

    pMember3->node.element = HDK_Element_PN_Type;
    pMember3->node.type = HDK_Type_PN_WiFiSecurity;
    pMember3->node.pNext = (HDK_Member*)pMember4;
    pMember3->iValue = HDK_Enum_PN_WiFiSecurity_WPA_WPA2_Enterprise;

    pMember4->node.element = HDK_Element_PN_Encryption;
    pMember4->node.type = HDK_Type_PN_WiFiEncryption;
    pMember4->node.pNext = nullptr;
    pMember4->iValue = HDK_Enum_PN_WiFiEncryption_TKIPORAES;

    pStruct->pHead = (HDK_Member*)pMember1;
    pStruct->pTail = (HDK_Member*)pMember4;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.WiFi.Radio.1.Alias"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockAlias, mockAlias + strlen(mockAlias) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiAp"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockApPathVal, mockApPathVal + strlen(mockApPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_SetParamVal(_, StrEq("Device.WiFi.AccessPoint.3.Security.ModeEnabled"), _, _, _))
    .Times(1).WillOnce(Return(0));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_SetParamVal(_, StrEq("Device.WiFi.AccessPoint.3.Security.X_CISCO_COM_EncryptionMethod"), _, _, _))
    .Times(1).WillOnce(Return(0));

    int result = HDK_Device_SetValue((void*)mockDeviceCtx, eValue, pStruct);
    EXPECT_EQ(result, 1);

    // Free the allocated memory
    free(pMember1);
    free(pMember2);
    free(pMember3);
    free(pMember4);
    free(pStruct);
}

TEST_F(CcspHomeSecurityHDKDeviceFixture, HDK_Device_SetValue_WLanType_SUCCESS_9) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WLanType;
    char mockPathVal[] = "Device.WiFi.Radio.1";
    char mockApPathVal[] = "Device.WiFi.AccessPoint.3";
    char mockAlias[] = "Radio0";

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    HDK_Member__STRING__* pMember1 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember1, nullptr);

    HDK_Member__INT__* pMember2 = (HDK_Member__INT__*) malloc(sizeof(HDK_Member__INT__));
    ASSERT_NE(pMember2, nullptr);

    HDK_Member__INT__* pMember3 = (HDK_Member__INT__*) malloc(sizeof(HDK_Member__INT__));
    ASSERT_NE(pMember3, nullptr);

    HDK_Member__INT__* pMember4 = (HDK_Member__INT__*) malloc(sizeof(HDK_Member__INT__));
    ASSERT_NE(pMember4, nullptr);

    pMember1->node.element = HDK_Element_PN_RadioID;
    pMember1->node.type = HDK_Type__STRING__;
    pMember1->node.pNext = (HDK_Member*)pMember2;
    pMember1->pszValue = strdup("Radio0");

    pMember2->node.element = HDK_Element_PN_Enabled;
    pMember2->node.type = HDK_Type__BOOL__;
    pMember2->node.pNext = (HDK_Member*)pMember3;
    pMember2->iValue = 1;

    pMember3->node.element = HDK_Element_PN_Type;
    pMember3->node.type = HDK_Type_PN_WiFiSecurity;
    pMember3->node.pNext = (HDK_Member*)pMember4;
    pMember3->iValue = HDK_Enum_PN_WiFiSecurity_WPA_WPA2_Personal;

    pMember4->node.element = HDK_Element_PN_Encryption;
    pMember4->node.type = HDK_Type_PN_WiFiEncryption;
    pMember4->node.pNext = nullptr;
    pMember4->iValue = HDK_Enum_PN_WiFiEncryption_TKIPORAES;

    pStruct->pHead = (HDK_Member*)pMember1;
    pStruct->pTail = (HDK_Member*)pMember4;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.WiFi.Radio.1.Alias"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockAlias, mockAlias + strlen(mockAlias) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiAp"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockApPathVal, mockApPathVal + strlen(mockApPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_SetParamVal(_, StrEq("Device.WiFi.AccessPoint.3.Security.ModeEnabled"), _, _, _))
    .Times(1).WillOnce(Return(0));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_SetParamVal(_, StrEq("Device.WiFi.AccessPoint.3.Security.X_CISCO_COM_EncryptionMethod"), _, _, _))
    .Times(1).WillOnce(Return(0));

    int result = HDK_Device_SetValue((void*)mockDeviceCtx, eValue, pStruct);
    EXPECT_EQ(result, 1);

    // Free the allocated memory
    free(pMember1);
    free(pMember2);
    free(pMember3);
    free(pMember4);
    free(pStruct);
}

TEST_F(CcspHomeSecurityHDKDeviceFixture, HDK_Device_SetValue_WLanType_FAIL_1) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WLanType;

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

     HDK_Member__STRING__* pMember1 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember1, nullptr);

    pMember1->node.element = HDK_Element_PN_RadioID;
    pMember1->node.type = HDK_Type__STRING__;
    pMember1->node.pNext = nullptr;
    pMember1->pszValue = strdup("Radio0");

    pStruct->pHead = (HDK_Member*)pMember1;
    pStruct->pTail = (HDK_Member*)pMember1;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .Times(1).WillOnce(Return(1));

    int result = HDK_Device_SetValue((void*)mockDeviceCtx, eValue, pStruct);
    EXPECT_EQ(result, 0);

    // Free the allocated memory
    free(pMember1);
    free(pStruct);
}

TEST_F(CcspHomeSecurityHDKDeviceFixture, HDK_Device_SetValue_WLanType_FAIL_2) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WLanType;
    char mockPathVal[] = "Device.WiFi.Radio.1";
    char mockAlias[] = "Radio0";

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    HDK_Member__STRING__* pMember1 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember1, nullptr);

    pMember1->node.element = HDK_Element_PN_RadioID;
    pMember1->node.type = HDK_Type__STRING__;
    pMember1->node.pNext = nullptr;
    pMember1->pszValue = strdup("Radio1");

    pStruct->pHead = (HDK_Member*)pMember1;
    pStruct->pTail = (HDK_Member*)pMember1;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.WiFi.Radio.1.Alias"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockAlias, mockAlias + strlen(mockAlias) + 1),
             Return(0)
    ));

    int result = HDK_Device_SetValue((void*)mockDeviceCtx, eValue, pStruct);
    EXPECT_EQ(result, 0);

    // Free the allocated memory
    free(pMember1);
    free(pStruct);
}

TEST_F(CcspHomeSecurityHDKDeviceFixture, HDK_Device_SetValue_WLanType_FAIL_3) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WLanType;
    char mockPathVal[] = "Device.WiFi.Radio.1";
    char mockAlias[] = "Radio0";

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    HDK_Member__STRING__* pMember1 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember1, nullptr);

    HDK_Member__INT__* pMember2 = (HDK_Member__INT__*) malloc(sizeof(HDK_Member__INT__));
    ASSERT_NE(pMember2, nullptr);

    HDK_Member__INT__* pMember3 = (HDK_Member__INT__*) malloc(sizeof(HDK_Member__INT__));
    ASSERT_NE(pMember3, nullptr);

    HDK_Member__INT__* pMember4 = (HDK_Member__INT__*) malloc(sizeof(HDK_Member__INT__));
    ASSERT_NE(pMember4, nullptr);

    pMember1->node.element = HDK_Element_PN_RadioID;
    pMember1->node.type = HDK_Type__STRING__;
    pMember1->node.pNext = (HDK_Member*)pMember2;
    pMember1->pszValue = strdup("Radio0");

    pMember2->node.element = HDK_Element_PN_Enabled;
    pMember2->node.type = HDK_Type__BOOL__;
    pMember2->node.pNext = nullptr;
    pMember2->iValue = 1;
    pStruct->pHead = (HDK_Member*)pMember1;
    pStruct->pTail = (HDK_Member*)pMember2;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.WiFi.Radio.1.Alias"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockAlias, mockAlias + strlen(mockAlias) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiAp"), _, _))
    .Times(1).WillOnce(Return(1));


    int result = HDK_Device_SetValue((void*)mockDeviceCtx, eValue, pStruct);
    EXPECT_EQ(result, 0);

    // Free the allocated memory
    free(pMember1);
    free(pMember2);
    free(pStruct);
}

TEST_F(CcspHomeSecurityHDKDeviceFixture, HDK_Device_SetValue_WLanType_FAIL_4) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WLanType;
    char mockPathVal[] = "Device.WiFi.Radio.1";
    char mockApPathVal[] = "Device.WiFi.AccessPoint.3";
    char mockAlias[] = "Radio0";

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    HDK_Member__STRING__* pMember1 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember1, nullptr);

    HDK_Member__INT__* pMember2 = (HDK_Member__INT__*) malloc(sizeof(HDK_Member__INT__));
    ASSERT_NE(pMember2, nullptr);

    HDK_Member__INT__* pMember3 = (HDK_Member__INT__*) malloc(sizeof(HDK_Member__INT__));
    ASSERT_NE(pMember3, nullptr);

    HDK_Member__INT__* pMember4 = (HDK_Member__INT__*) malloc(sizeof(HDK_Member__INT__));
    ASSERT_NE(pMember4, nullptr);

    pMember1->node.element = HDK_Element_PN_RadioID;
    pMember1->node.type = HDK_Type__STRING__;
    pMember1->node.pNext = (HDK_Member*)pMember2;
    pMember1->pszValue = strdup("Radio0");

    pMember2->node.element = HDK_Element_PN_Enabled;
    pMember2->node.type = HDK_Type__BOOL__;
    pMember2->node.pNext = (HDK_Member*)pMember3;
    pMember2->iValue = 1;

    pMember3->node.element = HDK_Element_PN_Type;
    pMember3->node.type = HDK_Type_PN_WiFiSecurity;
    pMember3->node.pNext = (HDK_Member*)pMember4;
    pMember3->iValue = HDK_Enum_PN_WiFiSecurity_WPA2_Personal;

    pMember4->node.element = HDK_Element_PN_Encryption;
    pMember4->node.type = HDK_Type_PN_WiFiEncryption;
    pMember4->node.pNext = nullptr;
    pMember4->iValue = HDK_Enum_PN_WiFiEncryption__UNKNOWN__;

    pStruct->pHead = (HDK_Member*)pMember1;
    pStruct->pTail = (HDK_Member*)pMember4;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.WiFi.Radio.1.Alias"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockAlias, mockAlias + strlen(mockAlias) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiAp"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockApPathVal, mockApPathVal + strlen(mockApPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_SetParamVal(_, StrEq("Device.WiFi.AccessPoint.3.Security.ModeEnabled"), _, _, _))
    .Times(1).WillOnce(Return(0));

    int result = HDK_Device_SetValue((void*)mockDeviceCtx, eValue, pStruct);
    EXPECT_EQ(result, 0);

    // Free the allocated memory
    free(pMember1);
    free(pMember2);
    free(pMember3);
    free(pMember4);
    free(pStruct);
}

TEST_F(CcspHomeSecurityHDKDeviceFixture, HDK_Device_SetValue_WLanKey_SUCCESS_1) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WLanKey;
    char mockPathVal[] = "Device.WiFi.Radio.1";
    char mockApPathVal[] = "Device.WiFi.AccessPoint.3";
    char mockAlias[] = "Radio0";

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    HDK_Member__STRING__* pMember1 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember1, nullptr);

    HDK_Member__INT__* pMember2 = (HDK_Member__INT__*) malloc(sizeof(HDK_Member__INT__));
    ASSERT_NE(pMember2, nullptr);

    HDK_Member__INT__* pMember3 = (HDK_Member__INT__*) malloc(sizeof(HDK_Member__INT__));
    ASSERT_NE(pMember3, nullptr);

    HDK_Member__STRING__* pMember4 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember4, nullptr);

    pMember1->node.element = HDK_Element_PN_RadioID;
    pMember1->node.type = HDK_Type__STRING__;
    pMember1->node.pNext = (HDK_Member*)pMember2;
    pMember1->pszValue = strdup("Radio0");

    pMember2->node.element = HDK_Element_PN_Enabled;
    pMember2->node.type = HDK_Type__BOOL__;
    pMember2->node.pNext = (HDK_Member*)pMember3;
    pMember2->iValue = 1;

    pMember3->node.element = HDK_Element_PN_Type;
    pMember3->node.type = HDK_Type_PN_WiFiSecurity;
    pMember3->node.pNext = (HDK_Member*)pMember4;
    pMember3->iValue = HDK_Enum_PN_WiFiSecurity_WEP_64;

    pMember4->node.element = HDK_Element_PN_Key;
    pMember4->node.type = HDK_Type__STRING__;
    pMember4->node.pNext = nullptr;
    pMember4->pszValue = strdup("WEP-Key");

    pStruct->pHead = (HDK_Member*)pMember1;
    pStruct->pTail = (HDK_Member*)pMember4;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .Times(2)
    .WillRepeatedly(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.WiFi.Radio.1.Alias"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockAlias, mockAlias + strlen(mockAlias) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiAp"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockApPathVal, mockApPathVal + strlen(mockApPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_SetParamVal(_, StrEq("Device.WiFi.AccessPoint.3.Security.X_CISCO_COM_WEPKey64Bit.1.WEPKey"), _, _, _))
    .Times(1).WillOnce(Return(0));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_Commit(_, _)).Times(1).WillOnce(Return(0));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_SetParamVal(_, StrEq("Device.WiFi.Radio.1.X_CISCO_COM_ApplySetting"), _, _, _))
    .Times(1).WillOnce(Return(0));

    int result = HDK_Device_SetValue((void*)mockDeviceCtx, eValue, pStruct);
    EXPECT_EQ(result, 1);

    // Free the allocated memory
    free(pMember1);
    free(pMember2);
    free(pMember3);
    free(pMember4);
    free(pStruct);
}

TEST_F(CcspHomeSecurityHDKDeviceFixture, HDK_Device_SetValue_WLanKey_SUCCESS_2) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WLanKey;
    char mockPathVal[] = "Device.WiFi.Radio.1";
    char mockApPathVal[] = "Device.WiFi.AccessPoint.3";
    char mockAlias[] = "Radio0";

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    HDK_Member__STRING__* pMember1 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember1, nullptr);

    HDK_Member__INT__* pMember2 = (HDK_Member__INT__*) malloc(sizeof(HDK_Member__INT__));
    ASSERT_NE(pMember2, nullptr);

    HDK_Member__INT__* pMember3 = (HDK_Member__INT__*) malloc(sizeof(HDK_Member__INT__));
    ASSERT_NE(pMember3, nullptr);

    HDK_Member__STRING__* pMember4 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember4, nullptr);

    pMember1->node.element = HDK_Element_PN_RadioID;
    pMember1->node.type = HDK_Type__STRING__;
    pMember1->node.pNext = (HDK_Member*)pMember2;
    pMember1->pszValue = strdup("Radio0");

    pMember2->node.element = HDK_Element_PN_Enabled;
    pMember2->node.type = HDK_Type__BOOL__;
    pMember2->node.pNext = (HDK_Member*)pMember3;
    pMember2->iValue = 1;

    pMember3->node.element = HDK_Element_PN_Type;
    pMember3->node.type = HDK_Type_PN_WiFiSecurity;
    pMember3->node.pNext = (HDK_Member*)pMember4;
    pMember3->iValue = HDK_Enum_PN_WiFiSecurity_WEP_128;

    pMember4->node.element = HDK_Element_PN_Key;
    pMember4->node.type = HDK_Type__STRING__;
    pMember4->node.pNext = nullptr;
    pMember4->pszValue = strdup("WEP-Key");

    pStruct->pHead = (HDK_Member*)pMember1;
    pStruct->pTail = (HDK_Member*)pMember4;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .Times(2)
    .WillRepeatedly(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.WiFi.Radio.1.Alias"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockAlias, mockAlias + strlen(mockAlias) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiAp"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockApPathVal, mockApPathVal + strlen(mockApPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_SetParamVal(_, StrEq("Device.WiFi.AccessPoint.3.Security.X_CISCO_COM_WEPKey128Bit.1.WEPKey"), _, _, _))
    .Times(1).WillOnce(Return(0));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_Commit(_, _)).Times(1).WillOnce(Return(0));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_SetParamVal(_, StrEq("Device.WiFi.Radio.1.X_CISCO_COM_ApplySetting"), _, _, _))
    .Times(1).WillOnce(Return(0));

    int result = HDK_Device_SetValue((void*)mockDeviceCtx, eValue, pStruct);
    EXPECT_EQ(result, 1);

    // Free the allocated memory
    free(pMember1);
    free(pMember2);
    free(pMember3);
    free(pMember4);
    free(pStruct);
}

TEST_F(CcspHomeSecurityHDKDeviceFixture, HDK_Device_SetValue_WLanKey_SUCCESS_3) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WLanKey;
    char mockPathVal[] = "Device.WiFi.Radio.1";
    char mockApPathVal[] = "Device.WiFi.AccessPoint.3";
    char mockAlias[] = "Radio0";

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    HDK_Member__STRING__* pMember1 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember1, nullptr);

    HDK_Member__INT__* pMember2 = (HDK_Member__INT__*) malloc(sizeof(HDK_Member__INT__));
    ASSERT_NE(pMember2, nullptr);

    HDK_Member__INT__* pMember3 = (HDK_Member__INT__*) malloc(sizeof(HDK_Member__INT__));
    ASSERT_NE(pMember3, nullptr);

    HDK_Member__STRING__* pMember4 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember4, nullptr);

    pMember1->node.element = HDK_Element_PN_RadioID;
    pMember1->node.type = HDK_Type__STRING__;
    pMember1->node.pNext = (HDK_Member*)pMember2;
    pMember1->pszValue = strdup("Radio0");

    pMember2->node.element = HDK_Element_PN_Enabled;
    pMember2->node.type = HDK_Type__BOOL__;
    pMember2->node.pNext = (HDK_Member*)pMember3;
    pMember2->iValue = 1;

    pMember3->node.element = HDK_Element_PN_Type;
    pMember3->node.type = HDK_Type_PN_WiFiSecurity;
    pMember3->node.pNext = (HDK_Member*)pMember4;
    pMember3->iValue = HDK_Enum_PN_WiFiSecurity_WPA_WPA2_Personal;

    pMember4->node.element = HDK_Element_PN_Key;
    pMember4->node.type = HDK_Type__STRING__;
    pMember4->node.pNext = nullptr;
    pMember4->pszValue = strdup("WPA-Key");

    pStruct->pHead = (HDK_Member*)pMember1;
    pStruct->pTail = (HDK_Member*)pMember4;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .Times(2)
    .WillRepeatedly(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.WiFi.Radio.1.Alias"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockAlias, mockAlias + strlen(mockAlias) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiAp"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockApPathVal, mockApPathVal + strlen(mockApPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_SetParamVal(_, StrEq("Device.WiFi.AccessPoint.3.Security.X_COMCAST-COM_KeyPassphrase"), _, _, _))
    .Times(1).WillOnce(Return(0));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_SetParamVal(_, StrEq("Device.WiFi.AccessPoint.4.Security.X_COMCAST-COM_KeyPassphrase"), _, _, _))
    .Times(1).WillOnce(Return(0));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_Commit(_, _)).Times(1).WillOnce(Return(0));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_SetParamVal(_, StrEq("Device.WiFi.Radio.1.X_CISCO_COM_ApplySetting"), _, _, _))
    .Times(1).WillOnce(Return(0));

    int result = HDK_Device_SetValue((void*)mockDeviceCtx, eValue, pStruct);
    EXPECT_EQ(result, 1);

    // Free the allocated memory
    free(pMember1);
    free(pMember2);
    free(pMember3);
    free(pMember4);
    free(pStruct);
}

TEST_F(CcspHomeSecurityHDKDeviceFixture, HDK_Device_SetValue_WLanKey_FAIL_1) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WLanKey;
    char mockPathVal[] = "Device.WiFi.Radio.1";
    char mockApPathVal[] = "Device.WiFi.AccessPoint.3";
    char mockAlias[] = "Radio0";

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    HDK_Member__STRING__* pMember1 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember1, nullptr);

    HDK_Member__INT__* pMember2 = (HDK_Member__INT__*) malloc(sizeof(HDK_Member__INT__));
    ASSERT_NE(pMember2, nullptr);

    HDK_Member__INT__* pMember3 = (HDK_Member__INT__*) malloc(sizeof(HDK_Member__INT__));
    ASSERT_NE(pMember3, nullptr);

    HDK_Member__STRING__* pMember4 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember4, nullptr);

    pMember1->node.element = HDK_Element_PN_RadioID;
    pMember1->node.type = HDK_Type__STRING__;
    pMember1->node.pNext = (HDK_Member*)pMember2;
    pMember1->pszValue = strdup("Radio0");

    pMember2->node.element = HDK_Element_PN_Enabled;
    pMember2->node.type = HDK_Type__BOOL__;
    pMember2->node.pNext = (HDK_Member*)pMember3;
    pMember2->iValue = 1;

    pMember3->node.element = HDK_Element_PN_Type;
    pMember3->node.type = HDK_Type_PN_WiFiSecurity;
    pMember3->node.pNext = (HDK_Member*)pMember4;
    pMember3->iValue = HDK_Enum_PN_WiFiSecurity_WPA_WPA2_Personal;

    pMember4->node.element = HDK_Element_PN_Key;
    pMember4->node.type = HDK_Type__STRING__;
    pMember4->node.pNext = nullptr;
    pMember4->pszValue = strdup("WEP-Key");

    pStruct->pHead = (HDK_Member*)pMember1;
    pStruct->pTail = (HDK_Member*)pMember4;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.WiFi.Radio.1.Alias"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockAlias, mockAlias + strlen(mockAlias) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiAp"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockApPathVal, mockApPathVal + strlen(mockApPathVal) + 1),
             Return(0)
    ));

    int result = HDK_Device_SetValue((void*)mockDeviceCtx, eValue, pStruct);
    EXPECT_EQ(result, 0);

    // Free the allocated memory
    free(pMember1);
    free(pMember2);
    free(pMember3);
    free(pMember4);
    free(pStruct);
}

TEST_F(CcspHomeSecurityHDKDeviceFixture, HDK_Device_SetValue_WLanKey_FAIL_2) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WLanKey;
    char mockPathVal[] = "Device.WiFi.Radio.1";
    char mockApPathVal[] = "Device.WiFi.AccessPoint.3";
    char mockAlias[] = "Radio0";

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    HDK_Member__STRING__* pMember1 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember1, nullptr);

    HDK_Member__INT__* pMember2 = (HDK_Member__INT__*) malloc(sizeof(HDK_Member__INT__));
    ASSERT_NE(pMember2, nullptr);

    HDK_Member__INT__* pMember3 = (HDK_Member__INT__*) malloc(sizeof(HDK_Member__INT__));
    ASSERT_NE(pMember3, nullptr);

    HDK_Member__STRING__* pMember4 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember4, nullptr);

    pMember1->node.element = HDK_Element_PN_RadioID;
    pMember1->node.type = HDK_Type__STRING__;
    pMember1->node.pNext = (HDK_Member*)pMember2;
    pMember1->pszValue = strdup("Radio0");

    pMember2->node.element = HDK_Element_PN_Enabled;
    pMember2->node.type = HDK_Type__BOOL__;
    pMember2->node.pNext = (HDK_Member*)pMember3;
    pMember2->iValue = 1;

    pMember3->node.element = HDK_Element_PN_Type;
    pMember3->node.type = HDK_Type_PN_WiFiSecurity;
    pMember3->node.pNext = (HDK_Member*)pMember4;
    pMember3->iValue = HDK_Enum_PN_WiFiSecurity_WEP_64;

    pMember4->node.element = HDK_Element_PN_Key;
    pMember4->node.type = HDK_Type__STRING__;
    pMember4->node.pNext = nullptr;
    pMember4->pszValue = strdup("WPA-Key");

    pStruct->pHead = (HDK_Member*)pMember1;
    pStruct->pTail = (HDK_Member*)pMember4;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.WiFi.Radio.1.Alias"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockAlias, mockAlias + strlen(mockAlias) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiAp"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockApPathVal, mockApPathVal + strlen(mockApPathVal) + 1),
             Return(0)
    ));

    int result = HDK_Device_SetValue((void*)mockDeviceCtx, eValue, pStruct);
    EXPECT_EQ(result, 0);

    // Free the allocated memory
    free(pMember1);
    free(pMember2);
    free(pMember3);
    free(pMember4);
    free(pStruct);
}

TEST_F(CcspHomeSecurityHDKDeviceFixture, HDK_Device_SetValue_WLanKey_FAIL_3) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WLanKey;
    char mockPathVal[] = "Device.WiFi.Radio.1";
    char mockApPathVal[] = "Device.WiFi.AccessPoint.3";
    char mockAlias[] = "Radio0";

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    HDK_Member__STRING__* pMember1 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember1, nullptr);

    HDK_Member__INT__* pMember2 = (HDK_Member__INT__*) malloc(sizeof(HDK_Member__INT__));
    ASSERT_NE(pMember2, nullptr);

    HDK_Member__INT__* pMember3 = (HDK_Member__INT__*) malloc(sizeof(HDK_Member__INT__));
    ASSERT_NE(pMember3, nullptr);

    HDK_Member__STRING__* pMember4 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember4, nullptr);

    pMember1->node.element = HDK_Element_PN_RadioID;
    pMember1->node.type = HDK_Type__STRING__;
    pMember1->node.pNext = (HDK_Member*)pMember2;
    pMember1->pszValue = strdup("Radio0");

    pMember2->node.element = HDK_Element_PN_Enabled;
    pMember2->node.type = HDK_Type__BOOL__;
    pMember2->node.pNext = (HDK_Member*)pMember3;
    pMember2->iValue = 1;

    pMember3->node.element = HDK_Element_PN_Type;
    pMember3->node.type = HDK_Type_PN_WiFiSecurity;
    pMember3->node.pNext = (HDK_Member*)pMember4;
    pMember3->iValue = HDK_Enum_PN_WiFiSecurity_WPA_WPA2_Personal;

    pMember4->node.element = HDK_Element_PN_Key;
    pMember4->node.type = HDK_Type__STRING__;
    pMember4->node.pNext = nullptr;
    pMember4->pszValue = strdup("WPA-Key");

    pStruct->pHead = (HDK_Member*)pMember1;
    pStruct->pTail = (HDK_Member*)pMember4;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.WiFi.Radio.1.Alias"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockAlias, mockAlias + strlen(mockAlias) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiAp"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockApPathVal, mockApPathVal + strlen(mockApPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_SetParamVal(_, StrEq("Device.WiFi.AccessPoint.3.Security.X_COMCAST-COM_KeyPassphrase"), _, _, _))
    .Times(1).WillOnce(Return(0));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_SetParamVal(_, StrEq("Device.WiFi.AccessPoint.4.Security.X_COMCAST-COM_KeyPassphrase"), _, _, _))
    .Times(1).WillOnce(Return(0));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_Commit(_, _)).Times(1).WillOnce(Return(1));

    int result = HDK_Device_SetValue((void*)mockDeviceCtx, eValue, pStruct);
    EXPECT_EQ(result, 0);

    // Free the allocated memory
    free(pMember1);
    free(pMember2);
    free(pMember3);
    free(pMember4);
    free(pStruct);
}

TEST_F(CcspHomeSecurityHDKDeviceFixture, HDK_Device_SetValue_WLanKey_FAIL_4) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WLanKey;
    char mockPathVal[] = "Device.WiFi.Radio.1";
    char mockApPathVal[] = "Device.WiFi.AccessPoint.3";
    char mockAlias[] = "Radio0";

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    HDK_Member__STRING__* pMember1 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember1, nullptr);

    HDK_Member__INT__* pMember2 = (HDK_Member__INT__*) malloc(sizeof(HDK_Member__INT__));
    ASSERT_NE(pMember2, nullptr);

    HDK_Member__INT__* pMember3 = (HDK_Member__INT__*) malloc(sizeof(HDK_Member__INT__));
    ASSERT_NE(pMember3, nullptr);

    HDK_Member__STRING__* pMember4 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember4, nullptr);

    pMember1->node.element = HDK_Element_PN_RadioID;
    pMember1->node.type = HDK_Type__STRING__;
    pMember1->node.pNext = (HDK_Member*)pMember2;
    pMember1->pszValue = strdup("Radio0");

    pMember2->node.element = HDK_Element_PN_Enabled;
    pMember2->node.type = HDK_Type__BOOL__;
    pMember2->node.pNext = (HDK_Member*)pMember3;
    pMember2->iValue = 1;

    pMember3->node.element = HDK_Element_PN_Type;
    pMember3->node.type = HDK_Type_PN_WiFiSecurity;
    pMember3->node.pNext = (HDK_Member*)pMember4;
    pMember3->iValue = HDK_Enum_PN_WiFiSecurity_WPA_WPA2_Personal;

    pMember4->node.element = HDK_Element_PN_Key;
    pMember4->node.type = HDK_Type__STRING__;
    pMember4->node.pNext = nullptr;
    pMember4->pszValue = strdup("WPA-Key");

    pStruct->pHead = (HDK_Member*)pMember1;
    pStruct->pTail = (HDK_Member*)pMember4;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .Times(2)
    .WillRepeatedly(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.WiFi.Radio.1.Alias"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockAlias, mockAlias + strlen(mockAlias) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiAp"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockApPathVal, mockApPathVal + strlen(mockApPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_SetParamVal(_, StrEq("Device.WiFi.AccessPoint.3.Security.X_COMCAST-COM_KeyPassphrase"), _, _, _))
    .Times(1).WillOnce(Return(0));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_SetParamVal(_, StrEq("Device.WiFi.AccessPoint.4.Security.X_COMCAST-COM_KeyPassphrase"), _, _, _))
    .Times(1).WillOnce(Return(0));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_Commit(_, _)).Times(1).WillOnce(Return(0));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_SetParamVal(_, StrEq("Device.WiFi.Radio.1.X_CISCO_COM_ApplySetting"), _, _, _))
    .Times(1).WillOnce(Return(1));

    int result = HDK_Device_SetValue((void*)mockDeviceCtx, eValue, pStruct);
    EXPECT_EQ(result, 0);

    // Free the allocated memory
    free(pMember1);
    free(pMember2);
    free(pMember3);
    free(pMember4);
    free(pStruct);
}

TEST_F(CcspHomeSecurityHDKDeviceFixture, HDK_Device_SetValue_WLanKey_FAIL_5) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WLanKey;
    char mockPathVal[] = "Device.WiFi.Radio.1";
    char mockApPathVal[] = "Device.WiFi.AccessPoint.3";
    char mockAlias[] = "Radio0";

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    HDK_Member__STRING__* pMember1 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember1, nullptr);

    HDK_Member__INT__* pMember2 = (HDK_Member__INT__*) malloc(sizeof(HDK_Member__INT__));
    ASSERT_NE(pMember2, nullptr);

    HDK_Member__INT__* pMember3 = (HDK_Member__INT__*) malloc(sizeof(HDK_Member__INT__));
    ASSERT_NE(pMember3, nullptr);

    HDK_Member__STRING__* pMember4 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember4, nullptr);

    pMember1->node.element = HDK_Element_PN_RadioID;
    pMember1->node.type = HDK_Type__STRING__;
    pMember1->node.pNext = (HDK_Member*)pMember2;
    pMember1->pszValue = strdup("Radio0");

    pMember2->node.element = HDK_Element_PN_Enabled;
    pMember2->node.type = HDK_Type__BOOL__;
    pMember2->node.pNext = (HDK_Member*)pMember3;
    pMember2->iValue = 1;

    pMember3->node.element = HDK_Element_PN_Type;
    pMember3->node.type = HDK_Type_PN_WiFiSecurity;
    pMember3->node.pNext = (HDK_Member*)pMember4;
    pMember3->iValue = HDK_Enum_PN_WiFiSecurity_WPA_WPA2_Personal;

    pMember4->node.element = HDK_Element_PN_Key;
    pMember4->node.type = HDK_Type__STRING__;
    pMember4->node.pNext = nullptr;
    pMember4->pszValue = strdup("WPA-Key");

    pStruct->pHead = (HDK_Member*)pMember1;
    pStruct->pTail = (HDK_Member*)pMember4;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .Times(2)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ))
    .WillOnce(Return(1));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.WiFi.Radio.1.Alias"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockAlias, mockAlias + strlen(mockAlias) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiAp"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockApPathVal, mockApPathVal + strlen(mockApPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_SetParamVal(_, StrEq("Device.WiFi.AccessPoint.3.Security.X_COMCAST-COM_KeyPassphrase"), _, _, _))
    .Times(1).WillOnce(Return(0));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_SetParamVal(_, StrEq("Device.WiFi.AccessPoint.4.Security.X_COMCAST-COM_KeyPassphrase"), _, _, _))
    .Times(1).WillOnce(Return(0));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_Commit(_, _)).Times(1).WillOnce(Return(0));

    int result = HDK_Device_SetValue((void*)mockDeviceCtx, eValue, pStruct);
    EXPECT_EQ(result, 0);

    // Free the allocated memory
    free(pMember1);
    free(pMember2);
    free(pMember3);
    free(pMember4);
    free(pStruct);
}

TEST_F(CcspHomeSecurityHDKDeviceFixture, HDK_Device_SetValue_WLanKey_FAIL_6) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WLanKey;

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

     HDK_Member__STRING__* pMember1 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember1, nullptr);

    pMember1->node.element = HDK_Element_PN_RadioID;
    pMember1->node.type = HDK_Type__STRING__;
    pMember1->node.pNext = nullptr;
    pMember1->pszValue = strdup("Radio0");

    pStruct->pHead = (HDK_Member*)pMember1;
    pStruct->pTail = (HDK_Member*)pMember1;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .Times(1).WillOnce(Return(1));

    int result = HDK_Device_SetValue((void*)mockDeviceCtx, eValue, pStruct);
    EXPECT_EQ(result, 0);

    // Free the allocated memory
    free(pMember1);
    free(pStruct);
}

TEST_F(CcspHomeSecurityHDKDeviceFixture, HDK_Device_SetValue_WLanKey_FAIL_7) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WLanKey;
    char mockPathVal[] = "Device.WiFi.Radio.1";
    char mockAlias[] = "Radio0";

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    HDK_Member__STRING__* pMember1 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember1, nullptr);

    pMember1->node.element = HDK_Element_PN_RadioID;
    pMember1->node.type = HDK_Type__STRING__;
    pMember1->node.pNext = nullptr;
    pMember1->pszValue = strdup("Radio1");

    pStruct->pHead = (HDK_Member*)pMember1;
    pStruct->pTail = (HDK_Member*)pMember1;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.WiFi.Radio.1.Alias"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockAlias, mockAlias + strlen(mockAlias) + 1),
             Return(0)
    ));

    int result = HDK_Device_SetValue((void*)mockDeviceCtx, eValue, pStruct);
    EXPECT_EQ(result, 0);

    // Free the allocated memory
    free(pMember1);
    free(pStruct);
}

TEST_F(CcspHomeSecurityHDKDeviceFixture, HDK_Device_SetValue_WLanKey_FAIL_8) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WLanKey;
    char mockPathVal[] = "Device.WiFi.Radio.1";
    char mockAlias[] = "Radio0";

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    HDK_Member__STRING__* pMember1 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember1, nullptr);

    pMember1->node.element = HDK_Element_PN_RadioID;
    pMember1->node.type = HDK_Type__STRING__;
    pMember1->node.pNext = nullptr;
    pMember1->pszValue = strdup("Radio0");

    pStruct->pHead = (HDK_Member*)pMember1;
    pStruct->pTail = (HDK_Member*)pMember1;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.WiFi.Radio.1.Alias"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockAlias, mockAlias + strlen(mockAlias) + 1),
             Return(0)
    ));

    int result = HDK_Device_SetValue((void*)mockDeviceCtx, eValue, pStruct);
    EXPECT_EQ(result, 0);

    // Free the allocated memory
    free(pMember1);
    free(pStruct);
}

TEST_F(CcspHomeSecurityHDKDeviceFixture, HDK_Device_SetValue_WLanKey_FAIL_9) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WLanKey;
    char mockPathVal[] = "Device.WiFi.Radio.1";
    char mockApPathVal[] = "Device.WiFi.AccessPoint.3";
    char mockAlias[] = "Radio0";

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    HDK_Member__STRING__* pMember1 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember1, nullptr);

    HDK_Member__INT__* pMember2 = (HDK_Member__INT__*) malloc(sizeof(HDK_Member__INT__));
    ASSERT_NE(pMember2, nullptr);

    HDK_Member__INT__* pMember3 = (HDK_Member__INT__*) malloc(sizeof(HDK_Member__INT__));
    ASSERT_NE(pMember3, nullptr);

    HDK_Member__STRING__* pMember4 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember4, nullptr);

    pMember1->node.element = HDK_Element_PN_RadioID;
    pMember1->node.type = HDK_Type__STRING__;
    pMember1->node.pNext = (HDK_Member*)pMember2;
    pMember1->pszValue = strdup("Radio0");

    pMember2->node.element = HDK_Element_PN_Enabled;
    pMember2->node.type = HDK_Type__BOOL__;
    pMember2->node.pNext = (HDK_Member*)pMember3;
    pMember2->iValue = 1;

    pMember3->node.element = HDK_Element_PN_Type;
    pMember3->node.type = HDK_Type_PN_WiFiSecurity;
    pMember3->node.pNext = (HDK_Member*)pMember4;
    pMember3->iValue = HDK_Enum_PN_WiFiSecurity_WPA_WPA2_Personal;

    pMember4->node.element = HDK_Element_PN_Key;
    pMember4->node.type = HDK_Type__STRING__;
    pMember4->node.pNext = nullptr;
    pMember4->pszValue = strdup("WPA-Key");

    pStruct->pHead = (HDK_Member*)pMember1;
    pStruct->pTail = (HDK_Member*)pMember4;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.WiFi.Radio.1.Alias"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockAlias, mockAlias + strlen(mockAlias) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiAp"), _, _))
    .Times(1).WillOnce(Return(1));

    int result = HDK_Device_SetValue((void*)mockDeviceCtx, eValue, pStruct);
    EXPECT_EQ(result, 0);

    // Free the allocated memory
    free(pMember1);
    free(pMember2);
    free(pMember3);
    free(pMember4);
    free(pStruct);
}

TEST_F(CcspHomeSecurityHDKDeviceFixture, HDK_Device_SetValue_WLanKey_FAIL_10) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WLanKey;
    char mockPathVal[] = "Device.WiFi.Radio.1";
    char mockApPathVal[] = "Device.WiFi.AccessPoint.3";
    char mockAlias[] = "Radio0";

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    HDK_Member__STRING__* pMember1 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember1, nullptr);

    HDK_Member__INT__* pMember2 = (HDK_Member__INT__*) malloc(sizeof(HDK_Member__INT__));
    ASSERT_NE(pMember2, nullptr);

    HDK_Member__INT__* pMember3 = (HDK_Member__INT__*) malloc(sizeof(HDK_Member__INT__));
    ASSERT_NE(pMember3, nullptr);

    HDK_Member__STRING__* pMember4 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember4, nullptr);

    pMember1->node.element = HDK_Element_PN_RadioID;
    pMember1->node.type = HDK_Type__STRING__;
    pMember1->node.pNext = (HDK_Member*)pMember2;
    pMember1->pszValue = strdup("Radio0");

    pMember2->node.element = HDK_Element_PN_Enabled;
    pMember2->node.type = HDK_Type__BOOL__;
    pMember2->node.pNext = (HDK_Member*)pMember3;
    pMember2->iValue = 1;

    pMember3->node.element = HDK_Element_PN_Type;
    pMember3->node.type = HDK_Type_PN_WiFiSecurity;
    pMember3->node.pNext = (HDK_Member*)pMember4;
    pMember3->iValue = HDK_Enum_PN_WiFiSecurity_NONE;

    pMember4->node.element = HDK_Element_PN_Key;
    pMember4->node.type = HDK_Type__STRING__;
    pMember4->node.pNext = nullptr;
    pMember4->pszValue = strdup("WPA-Key");

    pStruct->pHead = (HDK_Member*)pMember1;
    pStruct->pTail = (HDK_Member*)pMember4;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.WiFi.Radio.1.Alias"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockAlias, mockAlias + strlen(mockAlias) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_SetParamVal(_, _, _, _, _)).Times(1).WillOnce(Return(1));

    int result = HDK_Device_SetValue((void*)mockDeviceCtx, eValue, pStruct);
    EXPECT_EQ(result, 0);

    // Free the allocated memory
    free(pMember1);
    free(pMember2);
    free(pMember3);
    free(pMember4);
    free(pStruct);
}

TEST_F(CcspHomeSecurityHDKDeviceFixture, HDK_Device_SetValue_WLanKey_FAIL_11) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WLanKey;
    char mockPathVal[] = "Device.WiFi.Radio.1";
    char mockApPathVal[] = "Device.WiFi.AccessPoint.3";
    char mockAlias[] = "Radio0";

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    HDK_Member__STRING__* pMember1 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember1, nullptr);

    HDK_Member__INT__* pMember2 = (HDK_Member__INT__*) malloc(sizeof(HDK_Member__INT__));
    ASSERT_NE(pMember2, nullptr);

    pMember1->node.element = HDK_Element_PN_RadioID;
    pMember1->node.type = HDK_Type__STRING__;
    pMember1->node.pNext = (HDK_Member*)pMember2;
    pMember1->pszValue = strdup("Radio0");

    pMember2->node.element = HDK_Element_PN_Enabled;
    pMember2->node.type = HDK_Type__BOOL__;
    pMember2->node.pNext = nullptr;
    pMember2->iValue = 0;

    pStruct->pHead = (HDK_Member*)pMember1;
    pStruct->pTail = (HDK_Member*)pMember2;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.WiFi.Radio.1.Alias"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockAlias, mockAlias + strlen(mockAlias) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_SetParamVal(_, _, _, _, _)).Times(1).WillOnce(Return(1));

    int result = HDK_Device_SetValue((void*)mockDeviceCtx, eValue, pStruct);
    EXPECT_EQ(result, 0);

    // Free the allocated memory
    free(pMember1);
    free(pMember2);
    free(pStruct);
}

TEST_F(CcspHomeSecurityHDKDeviceFixture, HDK_Device_SetValue_RemotePort_SUCCESS_1) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_RemotePort;
    char mockVal[] = "true";

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    HDK_Member__INT__* pMember1 = (HDK_Member__INT__*) malloc(sizeof(HDK_Member__INT__));
    ASSERT_NE(pMember1, nullptr);

    pMember1->node.element = HDK_Element_PN_RemotePort;
    pMember1->node.type = HDK_Type__INT__;
    pMember1->node.pNext = nullptr;
    pMember1->iValue = 101;

    pStruct->pHead = (HDK_Member*)pMember1;
    pStruct->pTail = (HDK_Member*)pMember1;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.UserInterface.X_CISCO_COM_RemoteAccess.HttpEnable"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockVal, mockVal + strlen(mockVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_SetParamVal(_, StrEq("Device.UserInterface.X_CISCO_COM_RemoteAccess.HttpPort"), _, _, _))
    .Times(1).WillOnce(Return(0));

    int result = HDK_Device_SetValue((void*)mockDeviceCtx, eValue, pStruct);
    EXPECT_EQ(result, 1);

    free(pMember1);
    free(pStruct);
}

TEST_F(CcspHomeSecurityHDKDeviceFixture, HDK_Device_SetValue_RemotePort_SUCCESS_2) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_RemotePort;
    char mockVal[] = "false";

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    HDK_Member__INT__* pMember1 = (HDK_Member__INT__*) malloc(sizeof(HDK_Member__INT__));
    ASSERT_NE(pMember1, nullptr);

    pMember1->node.element = HDK_Element_PN_RemotePort;
    pMember1->node.type = HDK_Type__INT__;
    pMember1->node.pNext = nullptr;
    pMember1->iValue = 101;

    pStruct->pHead = (HDK_Member*)pMember1;
    pStruct->pTail = (HDK_Member*)pMember1;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.UserInterface.X_CISCO_COM_RemoteAccess.HttpEnable"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockVal, mockVal + strlen(mockVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.UserInterface.X_CISCO_COM_RemoteAccess.HttpsEnable"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockVal, mockVal + strlen(mockVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_SetParamVal(_, StrEq("Device.UserInterface.X_CISCO_COM_RemoteAccess.HttpPort"), _, _, _))
    .Times(1).WillOnce(Return(0));

    int result = HDK_Device_SetValue((void*)mockDeviceCtx, eValue, pStruct);
    EXPECT_EQ(result, 1);

    free(pMember1);
    free(pStruct);
}

TEST_F(CcspHomeSecurityHDKDeviceFixture, HDK_Device_SetValue_RemotePort_SUCCESS_3) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_RemotePort;
    char mockVal[] = "false";
    char mockVal2[] = "true";

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    HDK_Member__INT__* pMember1 = (HDK_Member__INT__*) malloc(sizeof(HDK_Member__INT__));
    ASSERT_NE(pMember1, nullptr);

    pMember1->node.element = HDK_Element_PN_RemotePort;
    pMember1->node.type = HDK_Type__INT__;
    pMember1->node.pNext = nullptr;
    pMember1->iValue = 101;

    pStruct->pHead = (HDK_Member*)pMember1;
    pStruct->pTail = (HDK_Member*)pMember1;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.UserInterface.X_CISCO_COM_RemoteAccess.HttpEnable"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockVal, mockVal + strlen(mockVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.UserInterface.X_CISCO_COM_RemoteAccess.HttpsEnable"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockVal2, mockVal2 + strlen(mockVal2) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_SetParamVal(_, StrEq("Device.UserInterface.X_CISCO_COM_RemoteAccess.HttpsPort"), _, _, _))
    .Times(1).WillOnce(Return(0));

    int result = HDK_Device_SetValue((void*)mockDeviceCtx, eValue, pStruct);
    EXPECT_EQ(result, 1);

    free(pMember1);
    free(pStruct);
}

TEST_F(CcspHomeSecurityHDKDeviceFixture, HDK_Device_SetValue_RemoteSSL_SUCCESS) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_RemoteSSL;

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    HDK_Member__INT__* pMember1 = (HDK_Member__INT__*) malloc(sizeof(HDK_Member__INT__));
    ASSERT_NE(pMember1, nullptr);

    pMember1->node.element = HDK_Element_PN_RemoteSSL;
    pMember1->node.type = HDK_Type__BOOL__;
    pMember1->node.pNext = nullptr;
    pMember1->iValue = 1;

    pStruct->pHead = (HDK_Member*)pMember1;
    pStruct->pTail = (HDK_Member*)pMember1;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_SetParamVal(_, StrEq("Device.UserInterface.X_CISCO_COM_RemoteAccess.HttpsEnable"), _, _, _))
    .Times(1).WillOnce(Return(0));

    int result = HDK_Device_SetValue((void*)mockDeviceCtx, eValue, pStruct);
    EXPECT_EQ(result, 1);

    free(pMember1);
    free(pStruct);
}

TEST_F(CcspHomeSecurityHDKDeviceFixture, HDK_Device_SetValue_ManageRemote_SUCCESS) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_ManageRemote;

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    HDK_Member__INT__* pMember1 = (HDK_Member__INT__*) malloc(sizeof(HDK_Member__INT__));
    ASSERT_NE(pMember1, nullptr);

    pMember1->node.element = HDK_Element_PN_ManageRemote;
    pMember1->node.type = HDK_Type__BOOL__;
    pMember1->node.pNext = nullptr;
    pMember1->iValue = 1;

    pStruct->pHead = (HDK_Member*)pMember1;
    pStruct->pTail = (HDK_Member*)pMember1;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_SetParamVal(_, StrEq("Device.UserInterface.X_CISCO_COM_RemoteAccess.HttpEnable"), _, _, _))
    .Times(1).WillOnce(Return(0));

    int result = HDK_Device_SetValue((void*)mockDeviceCtx, eValue, pStruct);
    EXPECT_EQ(result, 1);

    free(pMember1);
    free(pStruct);
}

TEST_F(CcspHomeSecurityHDKDeviceFixture, HDK_Device_SetValue_AutoAdjustDST_SUCCESS) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_AutoAdjustDST;

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    HDK_Member__INT__* pMember1 = (HDK_Member__INT__*) malloc(sizeof(HDK_Member__INT__));
    ASSERT_NE(pMember1, nullptr);

    pMember1->node.element = HDK_Element_PN_AutoAdjustDST;
    pMember1->node.type = HDK_Type__BOOL__;
    pMember1->node.pNext = nullptr;
    pMember1->iValue = 1;

    pStruct->pHead = (HDK_Member*)pMember1;
    pStruct->pTail = (HDK_Member*)pMember1;

    int result = HDK_Device_SetValue((void*)mockDeviceCtx, eValue, pStruct);
    EXPECT_EQ(result, 1);

    free(pMember1);
    free(pStruct);
}

TEST_F(CcspHomeSecurityHDKDeviceFixture, HDK_Device_SetValue_SSL_SUCCESS) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_SSL;

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    HDK_Member__INT__* pMember1 = (HDK_Member__INT__*) malloc(sizeof(HDK_Member__INT__));
    ASSERT_NE(pMember1, nullptr);

    pMember1->node.element = HDK_Element_PN_SSL;
    pMember1->node.type = HDK_Type__BOOL__;
    pMember1->node.pNext = nullptr;
    pMember1->iValue = 1;

    pStruct->pHead = (HDK_Member*)pMember1;
    pStruct->pTail = (HDK_Member*)pMember1;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_SetParamVal(_, StrEq("Device.UserInterface.X_CISCO_COM_RemoteAccess.HttpsEnable"), _, _, _))
    .Times(1).WillOnce(Return(0));

    int result = HDK_Device_SetValue((void*)mockDeviceCtx, eValue, pStruct);
    EXPECT_EQ(result, 1);

    free(pMember1);
    free(pStruct);
}

TEST_F(CcspHomeSecurityHDKDeviceFixture, HDK_Device_SetValue_Locale_SUCCESS) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_Locale;

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    HDK_Member__STRING__* pMember1 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember1, nullptr);

    pMember1->node.element = HDK_Element_PN_Locale;
    pMember1->node.type = HDK_Type__STRING__;
    pMember1->node.pNext = nullptr;
    pMember1->pszValue = strdup("US");

    pStruct->pHead = (HDK_Member*)pMember1;
    pStruct->pTail = (HDK_Member*)pMember1;

    int result = HDK_Device_SetValue((void*)mockDeviceCtx, eValue, pStruct);
    EXPECT_EQ(result, 1);

    free(pMember1);
    free(pStruct);
}

TEST_F(CcspHomeSecurityHDKDeviceFixture, HDK_Device_SetValue_AdminPassword_SUCCESS) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_AdminPassword;
    char mockPathVal[] = "Device.WiFi.Radio.1";
    char mockApPathVal[] = "Device.WiFi.AccessPoint.3";
    char mockAlias[] = "Radio0";

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    HDK_Member__STRING__* pMember1 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember1, nullptr);

    pMember1->node.element = HDK_Element_PN_AdminPassword;
    pMember1->node.type = HDK_Type__STRING__;
    pMember1->node.pNext = nullptr;
    pMember1->pszValue = strdup("password");

    pStruct->pHead = (HDK_Member*)pMember1;
    pStruct->pTail = (HDK_Member*)pMember1;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_FindObjectIns(_, StrEq("Device.Users.User."), _, _, _, _))
    .Times(1).WillOnce(Return(1));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_AddObjectIns(_, StrEq("Device.Users.User."), _))
    .Times(1)
    .WillRepeatedly(testing::DoAll(
        testing::WithArg<2>([&](int* newIns){
        *newIns = 2;
        }),
        Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_SetParamVal(_, _, _, _, _)).Times(2).WillRepeatedly(Return(0));

    int result = HDK_Device_SetValue((void*)mockDeviceCtx, eValue, pStruct);
    EXPECT_EQ(result, 1);

    // Free the allocated memory
    free(pMember1);
    free(pStruct);
}

TEST_F(CcspHomeSecurityHDKDeviceFixture, HDK_Device_SetValue_LanIPAddress_SUCCESS) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_LanIPAddress;
    char mockPathVal[] = "Device.DHCPv4.Server.Pool.2";

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    HDK_Member_IPAddress* pMember1 = (HDK_Member_IPAddress*) malloc(sizeof(HDK_Member_IPAddress));
    ASSERT_NE(pMember1, nullptr);

    pMember1->node.element = HDK_Element_PN_RouterIPAddress;
    pMember1->node.type = HDK_Type__IPADDRESS__;
    pMember1->node.pNext = nullptr;
    pMember1->ipAddress.a = 172;
    pMember1->ipAddress.b = 16;
    pMember1->ipAddress.c = 12;
    pMember1->ipAddress.d = 1;

    pStruct->pHead = (HDK_Member*)pMember1;
    pStruct->pTail = (HDK_Member*)pMember1;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityDHCPv4ServerPool"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_SetParamVal(_, StrEq("Device.DHCPv4.Server.Pool.2.IPRouters"), _, _, _))
    .Times(1).WillOnce(Return(0));

    int result = HDK_Device_SetValue((void*)mockDeviceCtx, eValue, pStruct);
    EXPECT_EQ(result, 1);

    free(pMember1);
    free(pStruct);
}

TEST_F(CcspHomeSecurityHDKDeviceFixture, HDK_Device_SetValue_LanIPAddress_FAIL) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_LanIPAddress;
    char mockPathVal[] = "Device.DHCPv4.Server.Pool.2";

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    HDK_Member_IPAddress* pMember1 = (HDK_Member_IPAddress*) malloc(sizeof(HDK_Member_IPAddress));
    ASSERT_NE(pMember1, nullptr);

    pMember1->node.element = HDK_Element_PN_RouterIPAddress;
    pMember1->node.type = HDK_Type__IPADDRESS__;
    pMember1->node.pNext = nullptr;
    pMember1->ipAddress.a = 172;
    pMember1->ipAddress.b = 16;
    pMember1->ipAddress.c = 12;
    pMember1->ipAddress.d = 1;

    pStruct->pHead = (HDK_Member*)pMember1;
    pStruct->pTail = (HDK_Member*)pMember1;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityDHCPv4ServerPool"), _, _))
    .Times(1)
    .WillOnce(Return(1));

    int result = HDK_Device_SetValue((void*)mockDeviceCtx, eValue, pStruct);
    EXPECT_EQ(result, 0);

    free(pMember1);
    free(pStruct);
}

TEST_F(CcspHomeSecurityHDKDeviceFixture, HDK_Device_SetValue_LanSubnetMask_SUCCESS) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_LanSubnetMask;
    char mockPathVal[] = "Device.DHCPv4.Server.Pool.2";

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    HDK_Member_IPAddress* pMember1 = (HDK_Member_IPAddress*) malloc(sizeof(HDK_Member_IPAddress));
    ASSERT_NE(pMember1, nullptr);

    pMember1->node.element = HDK_Element_PN_RouterSubnetMask;
    pMember1->node.type = HDK_Type__IPADDRESS__;
    pMember1->node.pNext = nullptr;
    pMember1->ipAddress.a = 255;
    pMember1->ipAddress.b = 255;
    pMember1->ipAddress.c = 255;
    pMember1->ipAddress.d = 0;

    pStruct->pHead = (HDK_Member*)pMember1;
    pStruct->pTail = (HDK_Member*)pMember1;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityDHCPv4ServerPool"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_SetParamVal(_, StrEq("Device.DHCPv4.Server.Pool.2.SubnetMask"), _, _, _))
    .Times(1).WillOnce(Return(0));

    int result = HDK_Device_SetValue((void*)mockDeviceCtx, eValue, pStruct);
    EXPECT_EQ(result, 1);

    free(pMember1);
    free(pStruct);
}

TEST_F(CcspHomeSecurityHDKDeviceFixture, HDK_Device_SetValue_LanSubnetMask_FAIL) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_LanSubnetMask;
    char mockPathVal[] = "Device.DHCPv4.Server.Pool.2";

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    HDK_Member_IPAddress* pMember1 = (HDK_Member_IPAddress*) malloc(sizeof(HDK_Member_IPAddress));
    ASSERT_NE(pMember1, nullptr);

    pMember1->node.element = HDK_Element_PN_RouterSubnetMask;
    pMember1->node.type = HDK_Type__IPADDRESS__;
    pMember1->node.pNext = nullptr;
    pMember1->ipAddress.a = 255;
    pMember1->ipAddress.b = 255;
    pMember1->ipAddress.c = 255;
    pMember1->ipAddress.d = 0;

    pStruct->pHead = (HDK_Member*)pMember1;
    pStruct->pTail = (HDK_Member*)pMember1;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityDHCPv4ServerPool"), _, _))
    .Times(1)
    .WillOnce(Return(1));

    int result = HDK_Device_SetValue((void*)mockDeviceCtx, eValue, pStruct);
    EXPECT_EQ(result, 0);

    free(pMember1);
    free(pStruct);
}

TEST_F(CcspHomeSecurityHDKDeviceFixture, HDK_Device_SetValue_DHCPEnabled_SUCCESS) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_DHCPEnabled;
    char mockPathVal[] = "Device.DHCPv4.Server.Pool.2";

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    HDK_Member_IPAddress* pMember1 = (HDK_Member_IPAddress*) malloc(sizeof(HDK_Member_IPAddress));
    ASSERT_NE(pMember1, nullptr);

    pMember1->node.element = HDK_Element_PN_IPAddressFirst;
    pMember1->node.type = HDK_Type__IPADDRESS__;
    pMember1->node.pNext = nullptr;
    pMember1->ipAddress.a = 172;
    pMember1->ipAddress.b = 16;
    pMember1->ipAddress.c = 12;
    pMember1->ipAddress.d = 100;

    pStruct->pHead = (HDK_Member*)pMember1;
    pStruct->pTail = (HDK_Member*)pMember1;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityDHCPv4ServerPool"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_SetParamVal(_, StrEq("Device.DHCPv4.Server.Pool.2.MinAddress"), _, _, _))
    .Times(1).WillOnce(Return(0));

    int result = HDK_Device_SetValue((void*)mockDeviceCtx, eValue, pStruct);
    EXPECT_EQ(result, 1);

    free(pMember1);
    free(pStruct);
}

TEST_F(CcspHomeSecurityHDKDeviceFixture, HDK_Device_SetValue_DHCPEnabled_FAIL) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_DHCPEnabled;
    char mockPathVal[] = "Device.DHCPv4.Server.Pool.2";

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    HDK_Member_IPAddress* pMember1 = (HDK_Member_IPAddress*) malloc(sizeof(HDK_Member_IPAddress));
    ASSERT_NE(pMember1, nullptr);

    pMember1->node.element = HDK_Element_PN_IPAddressFirst;
    pMember1->node.type = HDK_Type__IPADDRESS__;
    pMember1->node.pNext = nullptr;
    pMember1->ipAddress.a = 172;
    pMember1->ipAddress.b = 16;
    pMember1->ipAddress.c = 12;
    pMember1->ipAddress.d = 100;

    pStruct->pHead = (HDK_Member*)pMember1;
    pStruct->pTail = (HDK_Member*)pMember1;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityDHCPv4ServerPool"), _, _))
    .Times(1)
    .WillOnce(Return(1));

    int result = HDK_Device_SetValue((void*)mockDeviceCtx, eValue, pStruct);
    EXPECT_EQ(result, 0);

    free(pMember1);
    free(pStruct);
}

TEST_F(CcspHomeSecurityHDKDeviceFixture, HDK_Device_SetValue_DHCPLastIP_SUCCESS) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_DHCPLastIP;
    char mockPathVal[] = "Device.DHCPv4.Server.Pool.2";

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    HDK_Member_IPAddress* pMember1 = (HDK_Member_IPAddress*) malloc(sizeof(HDK_Member_IPAddress));
    ASSERT_NE(pMember1, nullptr);

    pMember1->node.element = HDK_Element_PN_IPAddressLast;
    pMember1->node.type = HDK_Type__IPADDRESS__;
    pMember1->node.pNext = nullptr;
    pMember1->ipAddress.a = 172;
    pMember1->ipAddress.b = 16;
    pMember1->ipAddress.c = 12;
    pMember1->ipAddress.d = 150;

    pStruct->pHead = (HDK_Member*)pMember1;
    pStruct->pTail = (HDK_Member*)pMember1;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityDHCPv4ServerPool"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_SetParamVal(_, StrEq("Device.DHCPv4.Server.Pool.2.MaxAddress"), _, _, _))
    .Times(1).WillOnce(Return(0));

    int result = HDK_Device_SetValue((void*)mockDeviceCtx, eValue, pStruct);
    EXPECT_EQ(result, 1);

    free(pMember1);
    free(pStruct);
}

TEST_F(CcspHomeSecurityHDKDeviceFixture, HDK_Device_SetValue_DHCPLastIP_FAIL) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_DHCPLastIP;
    char mockPathVal[] = "Device.DHCPv4.Server.Pool.2";

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    HDK_Member_IPAddress* pMember1 = (HDK_Member_IPAddress*) malloc(sizeof(HDK_Member_IPAddress));
    ASSERT_NE(pMember1, nullptr);

    pMember1->node.element = HDK_Element_PN_IPAddressLast;
    pMember1->node.type = HDK_Type__IPADDRESS__;
    pMember1->node.pNext = nullptr;
    pMember1->ipAddress.a = 172;
    pMember1->ipAddress.b = 16;
    pMember1->ipAddress.c = 12;
    pMember1->ipAddress.d = 150;

    pStruct->pHead = (HDK_Member*)pMember1;
    pStruct->pTail = (HDK_Member*)pMember1;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityDHCPv4ServerPool"), _, _))
    .Times(1)
    .WillOnce(Return(1));

    int result = HDK_Device_SetValue((void*)mockDeviceCtx, eValue, pStruct);
    EXPECT_EQ(result, 0);

    free(pMember1);
    free(pStruct);
}

TEST_F(CcspHomeSecurityHDKDeviceFixture, HDK_Device_SetValue_DHCPLeaseTime_SUCCESS) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_DHCPLeaseTime;
    char mockPathVal[] = "Device.DHCPv4.Server.Pool.2";

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    HDK_Member__INT__* pMember1 = (HDK_Member__INT__*) malloc(sizeof(HDK_Member__INT__));
    ASSERT_NE(pMember1, nullptr);

    pMember1->node.element = HDK_Element_PN_LeaseTime;
    pMember1->node.type = HDK_Type__INT__;
    pMember1->node.pNext = nullptr;
    pMember1->iValue = 86400;

    pStruct->pHead = (HDK_Member*)pMember1;
    pStruct->pTail = (HDK_Member*)pMember1;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityDHCPv4ServerPool"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_SetParamVal(_, StrEq("Device.DHCPv4.Server.Pool.2.LeaseTime"), _, _, _))
    .Times(1).WillOnce(Return(0));

    int result = HDK_Device_SetValue((void*)mockDeviceCtx, eValue, pStruct);
    EXPECT_EQ(result, 1);

    free(pMember1);
    free(pStruct);
}

TEST_F(CcspHomeSecurityHDKDeviceFixture, HDK_Device_SetValue_DHCPLeaseTime_FAIL) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_DHCPLeaseTime;
    char mockPathVal[] = "Device.DHCPv4.Server.Pool.2";

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    HDK_Member__INT__* pMember1 = (HDK_Member__INT__*) malloc(sizeof(HDK_Member__INT__));
    ASSERT_NE(pMember1, nullptr);

    pMember1->node.element = HDK_Element_PN_LeaseTime;
    pMember1->node.type = HDK_Type__INT__;
    pMember1->node.pNext = nullptr;
    pMember1->iValue = 86400;

    pStruct->pHead = (HDK_Member*)pMember1;
    pStruct->pTail = (HDK_Member*)pMember1;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityDHCPv4ServerPool"), _, _))
    .Times(1)
    .WillOnce(Return(1));

    int result = HDK_Device_SetValue((void*)mockDeviceCtx, eValue, pStruct);
    EXPECT_EQ(result, 0);

    free(pMember1);
    free(pStruct);
}

TEST_F(CcspHomeSecurityHDKDeviceFixture, HDK_Device_SetValue_DHCPReservations_FAIL_1) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_DHCPReservations;

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityDHCPv4ServerPool"), _, _))
    .Times(1).WillOnce(Return(1));

    int result = HDK_Device_SetValue((void*)mockDeviceCtx, eValue, pStruct);
    EXPECT_EQ(result, 0);

    free(pStruct);
}

TEST_F(CcspHomeSecurityHDKDeviceFixture, HDK_Device_SetValue_DHCPReservations_FAIL_2) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_DHCPReservations;
    char mockPathVal[] = "Device.DHCPv4.Server.Pool.2";

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    HDK_Member__INT__* pMember1 = (HDK_Member__INT__*) malloc(sizeof(HDK_Member__INT__));
    ASSERT_NE(pMember1, nullptr);

    pMember1->node.element = HDK_Element_PN_LeaseTime;
    pMember1->node.type = HDK_Type__INT__;
    pMember1->node.pNext = nullptr;
    pMember1->iValue = 86400;

    pStruct->pHead = (HDK_Member*)pMember1;
    pStruct->pTail = (HDK_Member*)pMember1;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityDHCPv4ServerPool"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
        testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
        Return(0)
    ));

    int result = HDK_Device_SetValue((void*)mockDeviceCtx, eValue, pStruct);
    EXPECT_EQ(result, 0);

    free(pMember1);
    free(pStruct);
}

TEST_F(CcspHomeSecurityHDKDeviceFixture, HDK_Device_SetValue_DHCPReservations_FAIL_3) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_DHCPReservations;

    char mockPathVal[] = "Device.DHCPv4.Server.Pool.2";
    char mockDeviceName[] = "testDevice";
    char mockIP[] = "192.168.0.1";
    char mockMAC[] = "00:00:00:00:00:00";

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    pStruct->pHead = nullptr;
    pStruct->pTail = nullptr;

    //Mock Calls for HDK_Device_GetValue to populate pStruct
    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityDHCPv4ServerPool"), _, _))
    .Times(2)
    .WillRepeatedly(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_FindObjectIns(_, _, _, _, _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
        testing::Invoke([&](MBusObj_t *, const char *, const char *, const char *, char insPath[][MAX_PATH_NAME], int *insNum) {
            strcpy(insPath[0], mockPathVal);
            strcpy(insPath[1], mockPathVal);
            *insNum = 1;
        }),
        Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("X_CISCO_COM_DeviceName"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockDeviceName, mockDeviceName + strlen(mockDeviceName) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("Yiaddr"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockIP, mockIP + strlen(mockIP) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("Chaddr"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockMAC, mockMAC + strlen(mockMAC) + 1),
             Return(0)
    ));

    int result = HDK_Device_GetValue(mockDeviceCtx, pStruct, eValue, pStruct);
    EXPECT_EQ(result, 1);

    //Mock calls for HDK_Device_SetValue
    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_AddObjectIns(_, _, _))
    .Times(1)
    .WillOnce(Return(0));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_SetParamVal(_, _, _, _, _)).WillRepeatedly(Return(0));
    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_Commit(_, _)).Times(1).WillOnce(Return(0));

    result = HDK_Device_SetValue((void*)mockDeviceCtx, eValue, pStruct);
    EXPECT_EQ(result, 1);

    free(pStruct);
}

TEST_F(CcspHomeSecurityHDKDeviceFixture, HDK_Device_SetValue_DHCPReservations_SUCCESS) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_DHCPReservations;

    char mockPathVal[] = "Device.DHCPv4.Server.Pool.2";
    char mockDeviceName[] = "testDevice";
    char mockIP[] = "192.168.0.1";
    char mockMAC[] = "00:00:00:00:00:00";

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    pStruct->pHead = nullptr;
    pStruct->pTail = nullptr;

    //Mock Calls for HDK_Device_GetValue to populate pStruct
    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityDHCPv4ServerPool"), _, _))
    .Times(2)
    .WillRepeatedly(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_FindObjectIns(_, _, _, _, _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
        testing::Invoke([&](MBusObj_t *, const char *, const char *, const char *, char insPath[][MAX_PATH_NAME], int *insNum) {
            strcpy(insPath[0], mockPathVal);
            strcpy(insPath[1], mockPathVal);
            *insNum = 1;
        }),
        Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("X_CISCO_COM_DeviceName"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockDeviceName, mockDeviceName + strlen(mockDeviceName) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("Yiaddr"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockIP, mockIP + strlen(mockIP) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("Chaddr"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockMAC, mockMAC + strlen(mockMAC) + 1),
             Return(0)
    ));

    int result = HDK_Device_GetValue(mockDeviceCtx, pStruct, eValue, pStruct);
    EXPECT_EQ(result, 1);

    //Mock calls for HDK_Device_SetValue
    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_AddObjectIns(_, _, _))
    .Times(1).WillOnce(Return(1));

    result = HDK_Device_SetValue((void*)mockDeviceCtx, eValue, pStruct);
    EXPECT_EQ(result, 0);

    free(pStruct);
}

TEST_F(CcspHomeSecurityHDKDeviceFixture, HDK_Device_SetValue_DHCPReservations_FAIL_4) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_DHCPReservations;

    char mockPathVal[] = "Device.DHCPv4.Server.Pool.2";
    char mockDeviceName[] = "testDevice";
    char mockIP[] = "192.168.0.1";
    char mockMAC[] = "00:00:00:00:00:00";

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    pStruct->pHead = nullptr;
    pStruct->pTail = nullptr;

    //Mock Calls for HDK_Device_GetValue to populate pStruct
    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityDHCPv4ServerPool"), _, _))
    .Times(2)
    .WillRepeatedly(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_FindObjectIns(_, _, _, _, _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
        testing::Invoke([&](MBusObj_t *, const char *, const char *, const char *, char insPath[][MAX_PATH_NAME], int *insNum) {
            strcpy(insPath[0], mockPathVal);
            strcpy(insPath[1], mockPathVal);
            *insNum = 1;
        }),
        Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("X_CISCO_COM_DeviceName"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockDeviceName, mockDeviceName + strlen(mockDeviceName) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("Yiaddr"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockIP, mockIP + strlen(mockIP) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("Chaddr"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockMAC, mockMAC + strlen(mockMAC) + 1),
             Return(0)
    ));

    int result = HDK_Device_GetValue(mockDeviceCtx, pStruct, eValue, pStruct);
    EXPECT_EQ(result, 1);

    //Mock calls for HDK_Device_SetValue
    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_AddObjectIns(_, _, _))
    .Times(1)
    .WillOnce(Return(0));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_SetParamVal(_, _, _, _, _)).WillRepeatedly(Return(0));
    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_Commit(_, _)).Times(1).WillOnce(Return(1));

    result = HDK_Device_SetValue((void*)mockDeviceCtx, eValue, pStruct);
    EXPECT_EQ(result, 0);

    free(pStruct);
}

TEST_F(CcspHomeSecurityHDKDeviceFixture, HDK_Device_SetValue_BridgeConnect_SUCCESS_1) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_BridgeConnect;

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    HDK_Member__INT__* pMember1 = (HDK_Member__INT__*) malloc(sizeof(HDK_Member__INT__));
    ASSERT_NE(pMember1, nullptr);

    HDK_Member__INT__* pMember2 = (HDK_Member__INT__*) malloc(sizeof(HDK_Member__INT__));
    ASSERT_NE(pMember2, nullptr);

    pMember1->node.element = HDK_Element_PN_EthernetPort;
    pMember1->node.type = HDK_Type__INT__;
    pMember1->node.pNext = (HDK_Member*)pMember2;
    pMember1->iValue = 0;

    pMember2->node.element = HDK_Element_PN_Minutes;
    pMember2->node.type = HDK_Type__INT__;
    pMember2->node.pNext = nullptr;
    pMember2->iValue = 10;

    pStruct->pHead = (HDK_Member*)pMember1;
    pStruct->pTail = (HDK_Member*)pMember2;

    EXPECT_CALL(*g_syscfgMock, syscfg_get(_, StrEq("HomeSecurityEthernet4Flag"),_, _))
    .Times(1).WillOnce(DoAll(SetArgPointee<2>(1), Return(0)));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, _, _, _))
    .Times(1).WillOnce(Return(1));

    int result = HDK_Device_SetValue((void*)mockDeviceCtx, eValue, pStruct);
    EXPECT_EQ(result, 1);

    free(pMember1);
    free(pMember2);
    free(pStruct);
}

TEST_F(CcspHomeSecurityHDKDeviceFixture, HDK_Device_SetValue_BridgeConnect_SUCCESS_2) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_BridgeConnect;

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    HDK_Member__INT__* pMember1 = (HDK_Member__INT__*) malloc(sizeof(HDK_Member__INT__));
    ASSERT_NE(pMember1, nullptr);

    HDK_Member__INT__* pMember2 = (HDK_Member__INT__*) malloc(sizeof(HDK_Member__INT__));
    ASSERT_NE(pMember2, nullptr);

    pMember1->node.element = HDK_Element_PN_EthernetPort;
    pMember1->node.type = HDK_Type__INT__;
    pMember1->node.pNext = (HDK_Member*)pMember2;
    pMember1->iValue = 0;

    pMember2->node.element = HDK_Element_PN_Minutes;
    pMember2->node.type = HDK_Type__INT__;
    pMember2->node.pNext = nullptr;
    pMember2->iValue = 0;

    pStruct->pHead = (HDK_Member*)pMember1;
    pStruct->pTail = (HDK_Member*)pMember2;

    EXPECT_CALL(*g_syscfgMock, syscfg_get(_, StrEq("HomeSecurityEthernet4Flag"),_, _))
    .Times(1).WillOnce(DoAll(SetArgPointee<2>(1), Return(0)));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, _, _, _))
    .Times(1).WillOnce(Return(1));

    int result = HDK_Device_SetValue((void*)mockDeviceCtx, eValue, pStruct);
    EXPECT_EQ(result, 1);

    free(pMember1);
    free(pMember2);
    free(pStruct);
}

TEST_F(CcspHomeSecurityHDKDeviceFixture, HDK_Device_SetValue_BridgeConnect_FAIL_1) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_BridgeConnect;

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    HDK_Member__INT__* pMember1 = (HDK_Member__INT__*) malloc(sizeof(HDK_Member__INT__));
    ASSERT_NE(pMember1, nullptr);

    pMember1->node.element = HDK_Element_PN_EthernetPort;
    pMember1->node.type = HDK_Type__INT__;
    pMember1->node.pNext = nullptr;
    pMember1->iValue = 1;

    pStruct->pHead = (HDK_Member*)pMember1;
    pStruct->pTail = (HDK_Member*)pMember1;

    int result = HDK_Device_SetValue((void*)mockDeviceCtx, eValue, pStruct);
    EXPECT_EQ(result, 0);

    free(pMember1);
    free(pStruct);
}


TEST_F(CcspHomeSecurityHDKDeviceFixture, HDK_Device_SetValue_BridgeConnect_FAIL_2) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_BridgeConnect;

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    HDK_Member__INT__* pMember1 = (HDK_Member__INT__*) malloc(sizeof(HDK_Member__INT__));
    ASSERT_NE(pMember1, nullptr);

    pMember1->node.element = HDK_Element_PN_EthernetPort;
    pMember1->node.type = HDK_Type__INT__;
    pMember1->node.pNext = nullptr;
    pMember1->iValue = 0;

    pStruct->pHead = (HDK_Member*)pMember1;
    pStruct->pTail = (HDK_Member*)pMember1;

    EXPECT_CALL(*g_syscfgMock, syscfg_get(_, StrEq("HomeSecurityEthernet4Flag"),_, _))
    .Times(1).WillOnce(DoAll(SetArgPointee<2>(1), Return(0)));

    int result = HDK_Device_SetValue((void*)mockDeviceCtx, eValue, pStruct);
    EXPECT_EQ(result, 0);

    free(pMember1);
    free(pStruct);
}

TEST_F(CcspHomeSecurityHDKDeviceFixture, HDK_Device_SetValue_BridgeConnect_FAIL_3) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_BridgeConnect;

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    HDK_Member__INT__* pMember1 = (HDK_Member__INT__*) malloc(sizeof(HDK_Member__INT__));
    ASSERT_NE(pMember1, nullptr);

    pMember1->node.element = HDK_Element_PN_EthernetPort;
    pMember1->node.type = HDK_Type__INT__;
    pMember1->node.pNext = nullptr;
    pMember1->iValue = 0;

    pStruct->pHead = (HDK_Member*)pMember1;
    pStruct->pTail = (HDK_Member*)pMember1;

    EXPECT_CALL(*g_syscfgMock, syscfg_get(_, StrEq("HomeSecurityEthernet4Flag"),_, _))
    .Times(1).WillOnce(DoAll(SetArgPointee<2>(10), Return(0)));

    int result = HDK_Device_SetValue((void*)mockDeviceCtx, eValue, pStruct);
    EXPECT_EQ(result, 0);

    free(pMember1);
    free(pStruct);
}
