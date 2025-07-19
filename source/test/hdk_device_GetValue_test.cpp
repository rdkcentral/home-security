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

extern HDK_Context* createMockHDK_Context();

class CcspHomeSecurityHDKDeviceGetValueFixture : public ::testing::Test {
protected:
    void SetUp() override {
        g_HdkCcspMbusMock = new HdkCcspMbusMock();
    }

    void TearDown() override {
        delete g_HdkCcspMbusMock;
        g_HdkCcspMbusMock = nullptr;
    }
};

TEST_F(CcspHomeSecurityHDKDeviceGetValueFixture, HDK_Device_GetValue_FAIL) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_PortMappings;
    HDK_Struct* pStruct = nullptr;

    mockDeviceCtx->mbus = nullptr;
    int result = HDK_Device_GetValue(mockDeviceCtx, pStruct, eValue, pStruct);
    EXPECT_EQ(result, 0);
}

TEST_F(CcspHomeSecurityHDKDeviceGetValueFixture, HDK_Device_GetValue_DEFAULT) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue__UNKNOWN__;
    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    int result = HDK_Device_GetValue(mockDeviceCtx, pStruct, eValue, pStruct);
    EXPECT_EQ(result, 0);

    free(pStruct);
    pStruct = nullptr;
}

TEST_F(CcspHomeSecurityHDKDeviceGetValueFixture, HDK_Device_GetValue_ManageRemote_SUCCESS_1) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_ManageRemote;
    char mockVal[] = "true";
    char mockPort[] = "80";
    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    pStruct->pHead = nullptr;
    pStruct->pTail = nullptr;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.UserInterface.X_CISCO_COM_RemoteAccess.HttpEnable"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockVal, mockVal + strlen(mockVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.UserInterface.X_CISCO_COM_RemoteAccess.HttpPort"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPort, mockPort + strlen(mockPort) + 1),
             Return(0)
    ));

    int result = HDK_Device_GetValue(mockDeviceCtx, pStruct, eValue, pStruct);
    EXPECT_EQ(result, 1);

    free(pStruct);
    pStruct = nullptr;
}

TEST_F(CcspHomeSecurityHDKDeviceGetValueFixture, HDK_Device_GetValue_ManageRemote_SUCCESS_2) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_ManageRemote;
    char mockTrue[] = "true";
    char mockFalse[] = "false";
    char mockPort[] = "443";
    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    pStruct->pHead = nullptr;
    pStruct->pTail = nullptr;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.UserInterface.X_CISCO_COM_RemoteAccess.HttpEnable"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockFalse, mockFalse + strlen(mockFalse) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.UserInterface.X_CISCO_COM_RemoteAccess.HttpsEnable"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockTrue, mockTrue + strlen(mockTrue) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.UserInterface.X_CISCO_COM_RemoteAccess.HttpsPort"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPort, mockPort + strlen(mockPort) + 1),
             Return(0)
    ));

    int result = HDK_Device_GetValue(mockDeviceCtx, pStruct, eValue, pStruct);
    EXPECT_EQ(result, 1);

    free(pStruct);
    pStruct = nullptr;
}

TEST_F(CcspHomeSecurityHDKDeviceGetValueFixture, HDK_Device_GetValue_ManageRemote_SUCCESS_3) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_ManageRemote;
    char mockTrue[] = "true";
    char mockFalse[] = "false";
    char mockPort[] = "443";
    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    pStruct->pHead = nullptr;
    pStruct->pTail = nullptr;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.UserInterface.X_CISCO_COM_RemoteAccess.HttpEnable"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockFalse, mockFalse + strlen(mockFalse) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.UserInterface.X_CISCO_COM_RemoteAccess.HttpsEnable"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockFalse, mockFalse + strlen(mockFalse) + 1),
             Return(0)
    ));

    int result = HDK_Device_GetValue(mockDeviceCtx, pStruct, eValue, pStruct);
    EXPECT_EQ(result, 1);

    free(pStruct);
    pStruct = nullptr;
}

TEST_F(CcspHomeSecurityHDKDeviceGetValueFixture, HDK_Device_GetValue_ManageWireless_SUCCESS) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_ManageWireless;

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    pStruct->pHead = nullptr;
    pStruct->pTail = nullptr;

    int result = HDK_Device_GetValue(mockDeviceCtx, pStruct, eValue, pStruct);
    EXPECT_EQ(result, 1);

    free(pStruct);
    pStruct = nullptr;
}

TEST_F(CcspHomeSecurityHDKDeviceGetValueFixture, HDK_Device_GetValue_DomainName_SUCCESS) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_DomainName;
    char mockPathVal[] = "Device.DHCPv4.Server.Pool.2";
    char mockDomainName[] = "test.com";

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    pStruct->pHead = nullptr;
    pStruct->pTail = nullptr;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityDHCPv4ServerPool"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.DHCPv4.Server.Pool.2.DomainName"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockDomainName, mockDomainName + strlen(mockDomainName) + 1),
             Return(0)
    ));

    int result = HDK_Device_GetValue(mockDeviceCtx, pStruct, eValue, pStruct);
    EXPECT_EQ(result, 1);

    free(pStruct);
    pStruct = nullptr;
}

TEST_F(CcspHomeSecurityHDKDeviceGetValueFixture, HDK_Device_GetValue_DomainName_FAIL) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_DomainName;
    char mockPathVal[] = "Device.DHCPv4.Server.Pool.2";

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    pStruct->pHead = nullptr;
    pStruct->pTail = nullptr;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityDHCPv4ServerPool"), _, _))
    .Times(1).WillOnce(Return(1));

    int result = HDK_Device_GetValue(mockDeviceCtx, pStruct, eValue, pStruct);
    EXPECT_EQ(result, 0);

    free(pStruct);
    pStruct = nullptr;
}

TEST_F(CcspHomeSecurityHDKDeviceGetValueFixture, HDK_Device_GetValue_WiredQoS_SUCCESS) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WiredQoS;

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    pStruct->pHead = nullptr;
    pStruct->pTail = nullptr;

    int result = HDK_Device_GetValue(mockDeviceCtx, pStruct, eValue, pStruct);
    EXPECT_EQ(result, 1);

    free(pStruct);
    pStruct = nullptr;
}

TEST_F(CcspHomeSecurityHDKDeviceGetValueFixture, HDK_Device_GetValue_WPSPin_SUCCESS) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WPSPin;
    char mockPathVal[] = "Device.WiFi.AccessPoint.3";
    char mockPIN[] = "valid_pin";

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    pStruct->pHead = nullptr;
    pStruct->pTail = nullptr;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiAp"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.WiFi.AccessPoint.3.WPS.X_CISCO_COM_Pin"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPIN, mockPIN + strlen(mockPIN) + 1),
             Return(0)
    ));

    int result = HDK_Device_GetValue(mockDeviceCtx, pStruct, eValue, pStruct);
    EXPECT_EQ(result, 1);

    free(pStruct);
    pStruct = nullptr;
}

TEST_F(CcspHomeSecurityHDKDeviceGetValueFixture, HDK_Device_GetValue_WPSPin_FAIL) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WPSPin;

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    pStruct->pHead = nullptr;
    pStruct->pTail = nullptr;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiAp"), _, _))
    .Times(1).WillOnce(Return(1));

    int result = HDK_Device_GetValue(mockDeviceCtx, pStruct, eValue, pStruct);
    EXPECT_EQ(result, 0);

    free(pStruct);
    pStruct = nullptr;
}

TEST_F(CcspHomeSecurityHDKDeviceGetValueFixture, HDK_Device_GetValue_UserName_SUCCESS) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_Username;

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    pStruct->pHead = nullptr;
    pStruct->pTail = nullptr;

    int result = HDK_Device_GetValue(mockDeviceCtx, pStruct, eValue, pStruct);
    EXPECT_EQ(result, 1);

    free(pStruct);
    pStruct = nullptr;
}

TEST_F(CcspHomeSecurityHDKDeviceGetValueFixture, HDK_Device_GetValue_AdminPassword_SUCCESS) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_AdminPassword;
    char mockPwd[] = "invalid_pwd";

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    pStruct->pHead = nullptr;
    pStruct->pTail = nullptr;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_FindObjectIns(_, _, _, _, _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
        testing::Invoke([&](MBusObj_t *, const char *, const char *, const char *, char insPath[][MAX_PATH_NAME], int *insNum) {
            strcpy(insPath[0], "Device.Users.User.1.");
            *insNum = 1;
        }),
        Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.Users.User.1.X_CISCO_COM_Password"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPwd, mockPwd + strlen(mockPwd) + 1),
             Return(0)
    ));

    int result = HDK_Device_GetValue(mockDeviceCtx, pStruct, eValue, pStruct);
    EXPECT_EQ(result, 1);

    free(pStruct);
    pStruct = nullptr;
}

TEST_F(CcspHomeSecurityHDKDeviceGetValueFixture, HDK_Device_GetValue_DeviceType_SUCCESS) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_DeviceType;

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    pStruct->pHead = nullptr;
    pStruct->pTail = nullptr;

    int result = HDK_Device_GetValue(mockDeviceCtx, pStruct, eValue, pStruct);
    EXPECT_EQ(result, 1);

    free(pStruct);
    pStruct = nullptr;
}

TEST_F(CcspHomeSecurityHDKDeviceGetValueFixture, HDK_Device_GetValue_DeviceName_SUCCESS) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_DeviceName;
    char mockDeviceName[] = "test_device";

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    pStruct->pHead = nullptr;
    pStruct->pTail = nullptr;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.DeviceInfo.ModelName"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockDeviceName, mockDeviceName + strlen(mockDeviceName) + 1),
             Return(0)
    ));

    int result = HDK_Device_GetValue(mockDeviceCtx, pStruct, eValue, pStruct);
    EXPECT_EQ(result, 1);

    free(pStruct);
    pStruct = nullptr;
}

TEST_F(CcspHomeSecurityHDKDeviceGetValueFixture, HDK_Device_GetValue_VendorName_SUCCESS) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_VendorName;
    char mockVendorName[] = "test_vendor";

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    pStruct->pHead = nullptr;
    pStruct->pTail = nullptr;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.DeviceInfo.Manufacturer"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockVendorName, mockVendorName + strlen(mockVendorName) + 1),
             Return(0)
    ));

    int result = HDK_Device_GetValue(mockDeviceCtx, pStruct, eValue, pStruct);
    EXPECT_EQ(result, 1);

    free(pStruct);
    pStruct = nullptr;
}

TEST_F(CcspHomeSecurityHDKDeviceGetValueFixture, HDK_Device_GetValue_ModelDescription_SUCCESS) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_ModelDescription;
    char mockDescription[] = "test_description";

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    pStruct->pHead = nullptr;
    pStruct->pTail = nullptr;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.DeviceInfo.Description"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockDescription, mockDescription + strlen(mockDescription) + 1),
             Return(0)
    ));

    int result = HDK_Device_GetValue(mockDeviceCtx, pStruct, eValue, pStruct);
    EXPECT_EQ(result, 1);

    free(pStruct);
    pStruct = nullptr;
}

TEST_F(CcspHomeSecurityHDKDeviceGetValueFixture, HDK_Device_GetValue_ModelName_SUCCESS) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_ModelName;
    char mockDeviceName[] = "test_device";

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    pStruct->pHead = nullptr;
    pStruct->pTail = nullptr;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.DeviceInfo.ModelName"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockDeviceName, mockDeviceName + strlen(mockDeviceName) + 1),
             Return(0)
    ));

    int result = HDK_Device_GetValue(mockDeviceCtx, pStruct, eValue, pStruct);
    EXPECT_EQ(result, 1);

    free(pStruct);
    pStruct = nullptr;
}

TEST_F(CcspHomeSecurityHDKDeviceGetValueFixture, HDK_Device_GetValue_FirmwareVersion_SUCCESS) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_FirmwareVersion;
    char mockFirmwareVersion[] = "test_firmware_version";

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    pStruct->pHead = nullptr;
    pStruct->pTail = nullptr;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.DeviceInfo.X_CISCO_COM_FirmwareName"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockFirmwareVersion, mockFirmwareVersion + strlen(mockFirmwareVersion) + 1),
             Return(0)
    ));

    int result = HDK_Device_GetValue(mockDeviceCtx, pStruct, eValue, pStruct);
    EXPECT_EQ(result, 1);

    free(pStruct);
    pStruct = nullptr;
}

TEST_F(CcspHomeSecurityHDKDeviceGetValueFixture, HDK_Device_GetValue_PresentationURL_SUCCESS) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_PresentationURL;
    char mockPathVal[] = "Device.DHCPv4.Server.Pool.1";
    char mockURL[] = "10.0.0.1"; 
    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    pStruct->pHead = nullptr;
    pStruct->pTail = nullptr;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.PrimaryLANDHCPv4ServerPool"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.DHCPv4.Server.Pool.1.IPRouters"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    int result = HDK_Device_GetValue(mockDeviceCtx, pStruct, eValue, pStruct);
    EXPECT_EQ(result, 1);

    free(pStruct);
    pStruct = nullptr;
}

TEST_F(CcspHomeSecurityHDKDeviceGetValueFixture, HDK_Device_GetValue_PresentationURL_FAIL) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_PresentationURL;

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    pStruct->pHead = nullptr;
    pStruct->pTail = nullptr;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.PrimaryLANDHCPv4ServerPool"), _, _))
    .Times(1)
    .WillOnce(Return(1));

    int result = HDK_Device_GetValue(mockDeviceCtx, pStruct, eValue, pStruct);
    EXPECT_EQ(result, 0);

    free(pStruct);
    pStruct = nullptr;
}

TEST_F(CcspHomeSecurityHDKDeviceGetValueFixture, HDK_Device_GetValue_SubDeviceURLs_SUCCESS) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_SubDeviceURLs;

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    pStruct->pHead = nullptr;
    pStruct->pTail = nullptr;

    int result = HDK_Device_GetValue(mockDeviceCtx, pStruct, eValue, pStruct);
    EXPECT_EQ(result, 1);

    free(pStruct);
    pStruct = nullptr;
}

TEST_F(CcspHomeSecurityHDKDeviceGetValueFixture, HDK_Device_GetValue_Tasks_SUCCESS) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_Tasks;

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    pStruct->pHead = nullptr;
    pStruct->pTail = nullptr;

    int result = HDK_Device_GetValue(mockDeviceCtx, pStruct, eValue, pStruct);
    EXPECT_EQ(result, 1);

    free(pStruct);
    pStruct = nullptr;
}

TEST_F(CcspHomeSecurityHDKDeviceGetValueFixture, HDK_Device_GetValue_TimeZone_SUCCESS) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_TimeZone;
    char mockTimeZone[] = "UTC";

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    pStruct->pHead = nullptr;
    pStruct->pTail = nullptr;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.Time.LocalTimeZone"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockTimeZone, mockTimeZone + strlen(mockTimeZone) + 1),
             Return(0)
    ));

    int result = HDK_Device_GetValue(mockDeviceCtx, pStruct, eValue, pStruct);
    EXPECT_EQ(result, 1);

    free(pStruct);
    pStruct = nullptr;
}

TEST_F(CcspHomeSecurityHDKDeviceGetValueFixture, HDK_Device_GetValue_AutoAdjustDST_SUCCESS_1) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_AutoAdjustDST;
    char mockVal[] = "true";

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    pStruct->pHead = nullptr;
    pStruct->pTail = nullptr;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.Time.X_CISCO_COM_DaylightSavingAutoAdjust"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockVal, mockVal + strlen(mockVal) + 1),
             Return(0)
    ));

    int result = HDK_Device_GetValue(mockDeviceCtx, pStruct, eValue, pStruct);
    EXPECT_EQ(result, 1);

    free(pStruct);
    pStruct = nullptr;
}

TEST_F(CcspHomeSecurityHDKDeviceGetValueFixture, HDK_Device_GetValue_AutoAdjustDST_SUCCESS_2) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_AutoAdjustDST;
    char mockVal[] = "false";

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    pStruct->pHead = nullptr;
    pStruct->pTail = nullptr;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.Time.X_CISCO_COM_DaylightSavingAutoAdjust"), _, _))
    .Times(1)
    .WillOnce(Return(1));

    int result = HDK_Device_GetValue(mockDeviceCtx, pStruct, eValue, pStruct);
    EXPECT_EQ(result, 1);

    free(pStruct);
    pStruct = nullptr;
}

TEST_F(CcspHomeSecurityHDKDeviceGetValueFixture, HDK_Device_GetValue_Locale_SUCCESS) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_Locale;
    char mockVal[] = "en-US";

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    pStruct->pHead = nullptr;
    pStruct->pTail = nullptr;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.UserInterface.CurrentLanguage"), _, _))
    .Times(1).WillOnce(Return(1));

    int result = HDK_Device_GetValue(mockDeviceCtx, pStruct, eValue, pStruct);
    EXPECT_EQ(result, 1);

    free(pStruct);
    pStruct = nullptr;
}

TEST_F(CcspHomeSecurityHDKDeviceGetValueFixture, HDK_Device_GetValue_SSL_SUCCESS) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_SSL;
    char mockVal[] = "true";

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    pStruct->pHead = nullptr;
    pStruct->pTail = nullptr;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.UserInterface.X_CISCO_COM_RemoteAccess.HttpsEnable"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockVal, mockVal + strlen(mockVal) + 1),
             Return(0)
    ));

    int result = HDK_Device_GetValue(mockDeviceCtx, pStruct, eValue, pStruct);
    EXPECT_EQ(result, 1);

    free(pStruct);
    pStruct = nullptr;
}

TEST_F(CcspHomeSecurityHDKDeviceGetValueFixture, HDK_Device_GetValue_RemoteSSL_SUCCESS) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_RemoteSSL;
    char mockVal[] = "false";

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    pStruct->pHead = nullptr;
    pStruct->pTail = nullptr;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.UserInterface.X_CISCO_COM_RemoteAccess.HttpsEnable"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockVal, mockVal + strlen(mockVal) + 1),
             Return(0)
    ));

    int result = HDK_Device_GetValue(mockDeviceCtx, pStruct, eValue, pStruct);
    EXPECT_EQ(result, 1);

    free(pStruct);
    pStruct = nullptr;
}

TEST_F(CcspHomeSecurityHDKDeviceGetValueFixture, HDK_Device_GetValue_IsDeviceReady_SUCCESS) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_IsDeviceReady;

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    pStruct->pHead = nullptr;
    pStruct->pTail = nullptr;

    int result = HDK_Device_GetValue(mockDeviceCtx, pStruct, eValue, pStruct);
    EXPECT_EQ(result, 1);

    free(pStruct);
    pStruct = nullptr;
}

TEST_F(CcspHomeSecurityHDKDeviceGetValueFixture, HDK_Device_GetValue_LanIPAddress_SUCCESS) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_LanIPAddress;
    char mockPathVal[] = "Device.DHCPv4.Server.Pool.2";
    char mockURL[] = "10.0.0.1";

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    pStruct->pHead = nullptr;
    pStruct->pTail = nullptr;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityDHCPv4ServerPool"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.DHCPv4.Server.Pool.2.IPRouters"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockURL, mockURL + strlen(mockURL) + 1),
             Return(0)
    ));

    int result = HDK_Device_GetValue(mockDeviceCtx, pStruct, eValue, pStruct);
    EXPECT_EQ(result, 1);

    free(pStruct);
    pStruct = nullptr;
}

TEST_F(CcspHomeSecurityHDKDeviceGetValueFixture, HDK_Device_GetValue_LanIPAddress_FAIL_1) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_LanIPAddress;

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    pStruct->pHead = nullptr;
    pStruct->pTail = nullptr;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityDHCPv4ServerPool"), _, _))
    .Times(1).WillOnce(Return(1));

    int result = HDK_Device_GetValue(mockDeviceCtx, pStruct, eValue, pStruct);
    EXPECT_EQ(result, 0);

    free(pStruct);
    pStruct = nullptr;
}

TEST_F(CcspHomeSecurityHDKDeviceGetValueFixture, HDK_Device_GetValue_LanIPAddress_FAIL_2) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_LanIPAddress;
    char mockPathVal[] = "Device.DHCPv4.Server.Pool.2";

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    pStruct->pHead = nullptr;
    pStruct->pTail = nullptr;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityDHCPv4ServerPool"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.DHCPv4.Server.Pool.2.IPRouters"), _, _))
    .Times(1).WillOnce(Return(1));

    int result = HDK_Device_GetValue(mockDeviceCtx, pStruct, eValue, pStruct);
    EXPECT_EQ(result, 0);

    free(pStruct);
    pStruct = nullptr;
}

TEST_F(CcspHomeSecurityHDKDeviceGetValueFixture, HDK_Device_GetValue_LanSubnetMask_SUCCESS) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_LanSubnetMask;
    char mockPathVal[] = "Device.DHCPv4.Server.Pool.2";
    char mockURL[] = "255.255.255.0";

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    pStruct->pHead = nullptr;
    pStruct->pTail = nullptr;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityDHCPv4ServerPool"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.DHCPv4.Server.Pool.2.SubnetMask"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockURL, mockURL + strlen(mockURL) + 1),
             Return(0)
    ));

    int result = HDK_Device_GetValue(mockDeviceCtx, pStruct, eValue, pStruct);
    EXPECT_EQ(result, 1);

    free(pStruct);
    pStruct = nullptr;
}

TEST_F(CcspHomeSecurityHDKDeviceGetValueFixture, HDK_Device_GetValue_LanSubnetMask_FAIL_1) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_LanSubnetMask;

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    pStruct->pHead = nullptr;
    pStruct->pTail = nullptr;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityDHCPv4ServerPool"), _, _))
    .Times(1).WillOnce(Return(1));

    int result = HDK_Device_GetValue(mockDeviceCtx, pStruct, eValue, pStruct);
    EXPECT_EQ(result, 0);

    free(pStruct);
    pStruct = nullptr;
}

TEST_F(CcspHomeSecurityHDKDeviceGetValueFixture, HDK_Device_GetValue_LanIPSubnetMask_FAIL_2) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_LanSubnetMask;
    char mockPathVal[] = "Device.DHCPv4.Server.Pool.2";

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    pStruct->pHead = nullptr;
    pStruct->pTail = nullptr;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityDHCPv4ServerPool"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.DHCPv4.Server.Pool.2.SubnetMask"), _, _))
    .Times(1).WillOnce(Return(1));

    int result = HDK_Device_GetValue(mockDeviceCtx, pStruct, eValue, pStruct);
    EXPECT_EQ(result, 0);

    free(pStruct);
    pStruct = nullptr;
}

TEST_F(CcspHomeSecurityHDKDeviceGetValueFixture, HDK_Device_GetValue_DHCPEnabled_SUCCESS_1) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_DHCPEnabled;
    char mockPathVal[] = "Device.DHCPv4.Server.Pool.2";
    char mockVal[] = "true";

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    pStruct->pHead = nullptr;
    pStruct->pTail = nullptr;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityDHCPv4ServerPool"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.DHCPv4.Server.Pool.2.Enable"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockVal, mockVal + strlen(mockVal) + 1),
             Return(0)
    ));

    int result = HDK_Device_GetValue(mockDeviceCtx, pStruct, eValue, pStruct);
    EXPECT_EQ(result, 1);

    free(pStruct);
    pStruct = nullptr;
}

TEST_F(CcspHomeSecurityHDKDeviceGetValueFixture, HDK_Device_GetValue_DHCPEnabled_SUCCESS_2) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_DHCPEnabled;
    char mockPathVal[] = "Device.DHCPv4.Server.Pool.2";
    char mockVal[] = "false";

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    pStruct->pHead = nullptr;
    pStruct->pTail = nullptr;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityDHCPv4ServerPool"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.DHCPv4.Server.Pool.2.Enable"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockVal, mockVal + strlen(mockVal) + 1),
             Return(0)
    ));

    int result = HDK_Device_GetValue(mockDeviceCtx, pStruct, eValue, pStruct);
    EXPECT_EQ(result, 1);

    free(pStruct);
    pStruct = nullptr;
}

TEST_F(CcspHomeSecurityHDKDeviceGetValueFixture, HDK_Device_GetValue_DHCPEnabled_FAIL_1) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_DHCPEnabled;

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    pStruct->pHead = nullptr;
    pStruct->pTail = nullptr;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityDHCPv4ServerPool"), _, _))
    .Times(1).WillOnce(Return(1));

    int result = HDK_Device_GetValue(mockDeviceCtx, pStruct, eValue, pStruct);
    EXPECT_EQ(result, 0);

    free(pStruct);
    pStruct = nullptr;
}

TEST_F(CcspHomeSecurityHDKDeviceGetValueFixture, HDK_Device_GetValue_DHCPEnabled_FAIL_2) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_DHCPEnabled;
    char mockPathVal[] = "Device.DHCPv4.Server.Pool.2";

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    pStruct->pHead = nullptr;
    pStruct->pTail = nullptr;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityDHCPv4ServerPool"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.DHCPv4.Server.Pool.2.Enable"), _, _))
    .Times(1).WillOnce(Return(1));

    int result = HDK_Device_GetValue(mockDeviceCtx, pStruct, eValue, pStruct);
    EXPECT_EQ(result, 0);

    free(pStruct);
    pStruct = nullptr;
}

TEST_F(CcspHomeSecurityHDKDeviceGetValueFixture, HDK_Device_GetValue_DHCPFirstIP_SUCCESS) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_DHCPFirstIP;
    char mockPathVal[] = "Device.DHCPv4.Server.Pool.2";
    char mockURL[] = "172.16.12.100";

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    pStruct->pHead = nullptr;
    pStruct->pTail = nullptr;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityDHCPv4ServerPool"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.DHCPv4.Server.Pool.2.MinAddress"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockURL, mockURL + strlen(mockURL) + 1),
             Return(0)
    ));

    int result = HDK_Device_GetValue(mockDeviceCtx, pStruct, eValue, pStruct);
    EXPECT_EQ(result, 1);

    free(pStruct);
    pStruct = nullptr;
}

TEST_F(CcspHomeSecurityHDKDeviceGetValueFixture, HDK_Device_GetValue_DHCPFirstIP_FAIL_1) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_DHCPFirstIP;

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    pStruct->pHead = nullptr;
    pStruct->pTail = nullptr;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityDHCPv4ServerPool"), _, _))
    .Times(1).WillOnce(Return(1));

    int result = HDK_Device_GetValue(mockDeviceCtx, pStruct, eValue, pStruct);
    EXPECT_EQ(result, 0);

    free(pStruct);
    pStruct = nullptr;
}

TEST_F(CcspHomeSecurityHDKDeviceGetValueFixture, HDK_Device_GetValue_DHCPFirstIP_FAIL_2) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_DHCPFirstIP;
    char mockPathVal[] = "Device.DHCPv4.Server.Pool.2";

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    pStruct->pHead = nullptr;
    pStruct->pTail = nullptr;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityDHCPv4ServerPool"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.DHCPv4.Server.Pool.2.MinAddress"), _, _))
    .Times(1).WillOnce(Return(1));

    int result = HDK_Device_GetValue(mockDeviceCtx, pStruct, eValue, pStruct);
    EXPECT_EQ(result, 0);

    free(pStruct);
    pStruct = nullptr;
}

TEST_F(CcspHomeSecurityHDKDeviceGetValueFixture, HDK_Device_GetValue_DHCPLastIP_SUCCESS) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_DHCPLastIP;
    char mockPathVal[] = "Device.DHCPv4.Server.Pool.2";
    char mockURL[] = "172.16.12.150";

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    pStruct->pHead = nullptr;
    pStruct->pTail = nullptr;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityDHCPv4ServerPool"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.DHCPv4.Server.Pool.2.MaxAddress"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockURL, mockURL + strlen(mockURL) + 1),
             Return(0)
    ));

    int result = HDK_Device_GetValue(mockDeviceCtx, pStruct, eValue, pStruct);
    EXPECT_EQ(result, 1);

    free(pStruct);
    pStruct = nullptr;
}

TEST_F(CcspHomeSecurityHDKDeviceGetValueFixture, HDK_Device_GetValue_DHCPLastIP_FAIL_1) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_DHCPLastIP;

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    pStruct->pHead = nullptr;
    pStruct->pTail = nullptr;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityDHCPv4ServerPool"), _, _))
    .Times(1).WillOnce(Return(1));

    int result = HDK_Device_GetValue(mockDeviceCtx, pStruct, eValue, pStruct);
    EXPECT_EQ(result, 0);

    free(pStruct);
    pStruct = nullptr;
}

TEST_F(CcspHomeSecurityHDKDeviceGetValueFixture, HDK_Device_GetValue_DHCPLastIP_FAIL_2) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_DHCPLastIP;
    char mockPathVal[] = "Device.DHCPv4.Server.Pool.2";

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    pStruct->pHead = nullptr;
    pStruct->pTail = nullptr;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityDHCPv4ServerPool"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.DHCPv4.Server.Pool.2.MaxAddress"), _, _))
    .Times(1).WillOnce(Return(1));

    int result = HDK_Device_GetValue(mockDeviceCtx, pStruct, eValue, pStruct);
    EXPECT_EQ(result, 0);

    free(pStruct);
    pStruct = nullptr;
}

TEST_F(CcspHomeSecurityHDKDeviceGetValueFixture, HDK_Device_GetValue_DHCPLeaseTime_SUCCESS) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_DHCPLeaseTime;
    char mockPathVal[] = "Device.DHCPv4.Server.Pool.2";
    char mockVal[]= "86400";

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    pStruct->pHead = nullptr;
    pStruct->pTail = nullptr;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityDHCPv4ServerPool"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.DHCPv4.Server.Pool.2.LeaseTime"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockVal, mockVal + strlen(mockVal) + 1),
             Return(0)
    ));

    int result = HDK_Device_GetValue(mockDeviceCtx, pStruct, eValue, pStruct);
    EXPECT_EQ(result, 1);

    free(pStruct);
    pStruct = nullptr;
}

TEST_F(CcspHomeSecurityHDKDeviceGetValueFixture, HDK_Device_GetValue_DHCPLeaseTime_FAIL_1) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_DHCPLeaseTime;

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    pStruct->pHead = nullptr;
    pStruct->pTail = nullptr;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityDHCPv4ServerPool"), _, _))
    .Times(1).WillOnce(Return(1));

    int result = HDK_Device_GetValue(mockDeviceCtx, pStruct, eValue, pStruct);
    EXPECT_EQ(result, 0);

    free(pStruct);
    pStruct = nullptr;
}

TEST_F(CcspHomeSecurityHDKDeviceGetValueFixture, HDK_Device_GetValue_DHCPLeaseTime_FAIL_2) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_DHCPLeaseTime;
    char mockPathVal[] = "Device.DHCPv4.Server.Pool.2";

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    pStruct->pHead = nullptr;
    pStruct->pTail = nullptr;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityDHCPv4ServerPool"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.DHCPv4.Server.Pool.2.LeaseTime"), _, _))
    .Times(1).WillOnce(Return(1));

    int result = HDK_Device_GetValue(mockDeviceCtx, pStruct, eValue, pStruct);
    EXPECT_EQ(result, 0);

    free(pStruct);
    pStruct = nullptr;
}

TEST_F(CcspHomeSecurityHDKDeviceGetValueFixture, HDK_Device_GetValue_DHCPReservations_SUCCESS) {
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

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityDHCPv4ServerPool"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
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

    free(pStruct);
    pStruct = nullptr;
}

TEST_F(CcspHomeSecurityHDKDeviceGetValueFixture, HDK_Device_GetValue_DHCPReservations_FAIL_1) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_DHCPReservations;

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    pStruct->pHead = nullptr;
    pStruct->pTail = nullptr;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityDHCPv4ServerPool"), _, _))
    .Times(1).WillOnce(Return(1));

    int result = HDK_Device_GetValue(mockDeviceCtx, pStruct, eValue, pStruct);
    EXPECT_EQ(result, 0);

    free(pStruct);
    pStruct = nullptr;
}

TEST_F(CcspHomeSecurityHDKDeviceGetValueFixture, HDK_Device_GetValue_PortMappings_SUCCESS_1) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_PortMappings;
    char mockPort[]= "80";
    char mockIP[] = "172.16.12.1";
    char mockProtocol[] = "UDP";
    char mockDescription[] = "testPortMapping";

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    pStruct->pHead = nullptr;
    pStruct->pTail = nullptr;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_FindObjectIns(_, _, _, _, _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
        testing::Invoke([&](MBusObj_t *, const char *, const char *, const char *, char insPath[][MAX_PATH_NAME], int *insNum) {
            strcpy(insPath[0], "Device.NAT.PortMapping.1.");
            *insNum = 1;
        }),
        Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("InternalPort"), _, _))
    .Times(2)
    .WillRepeatedly(testing::DoAll(
             testing::SetArrayArgument<2>(mockPort, mockPort + strlen(mockPort) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("InternalClient"), _, _))
    .Times(2)
    .WillRepeatedly(testing::DoAll(
             testing::SetArrayArgument<2>(mockIP, mockIP + strlen(mockIP) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("Protocol"), _, _))
    .Times(2)
    .WillRepeatedly(testing::DoAll(
             testing::SetArrayArgument<2>(mockProtocol, mockProtocol + strlen(mockProtocol) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("Description"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockDescription, mockDescription + strlen(mockDescription) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("ExternalPort"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPort, mockPort + strlen(mockPort) + 1),
             Return(0)
    ));

    int result = HDK_Device_GetValue(mockDeviceCtx, pStruct, eValue, pStruct);
    EXPECT_EQ(result, 1);

    free(pStruct);
    pStruct = nullptr;
}

TEST_F(CcspHomeSecurityHDKDeviceGetValueFixture, HDK_Device_GetValue_PortMappings_SUCCESS_2) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_PortMappings;
    char mockPort[]= "80";
    char mockIP[] = "172.16.12.1";
    char mockProtocol[] = "TCP";
    char mockDescription[] = "testPortMapping";

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    pStruct->pHead = nullptr;
    pStruct->pTail = nullptr;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_FindObjectIns(_, _, _, _, _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
        testing::Invoke([&](MBusObj_t *, const char *, const char *, const char *, char insPath[][MAX_PATH_NAME], int *insNum) {
            strcpy(insPath[0], "Device.NAT.PortMapping.1.");
            *insNum = 1;
        }),
        Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("InternalPort"), _, _))
    .Times(2)
    .WillRepeatedly(testing::DoAll(
             testing::SetArrayArgument<2>(mockPort, mockPort + strlen(mockPort) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("InternalClient"), _, _))
    .Times(2)
    .WillRepeatedly(testing::DoAll(
             testing::SetArrayArgument<2>(mockIP, mockIP + strlen(mockIP) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("Protocol"), _, _))
    .Times(2)
    .WillRepeatedly(testing::DoAll(
             testing::SetArrayArgument<2>(mockProtocol, mockProtocol + strlen(mockProtocol) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("Description"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockDescription, mockDescription + strlen(mockDescription) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("ExternalPort"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPort, mockPort + strlen(mockPort) + 1),
             Return(0)
    ));

    int result = HDK_Device_GetValue(mockDeviceCtx, pStruct, eValue, pStruct);
    EXPECT_EQ(result, 1);

    free(pStruct);
    pStruct = nullptr;
}

TEST_F(CcspHomeSecurityHDKDeviceGetValueFixture, HDK_Device_GetValue_PortMappings_SUCCESS_3) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_PortMappings;

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    pStruct->pHead = nullptr;
    pStruct->pTail = nullptr;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_FindObjectIns(_, _, _, _, _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
        testing::Invoke([&](MBusObj_t *, const char *, const char *, const char *, char insPath[][MAX_PATH_NAME], int *insNum) {
            strcpy(insPath[0], "Device.NAT.PortMapping.1.");
            *insNum = 0;
        }),
        Return(0)
    ));

    int result = HDK_Device_GetValue(mockDeviceCtx, pStruct, eValue, pStruct);
    EXPECT_EQ(result, 1);

    free(pStruct);
    pStruct = nullptr;
}

TEST_F(CcspHomeSecurityHDKDeviceGetValueFixture, HDK_Device_GetValue_PortMappings_FAIL) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_PortMappings;

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    pStruct->pHead = nullptr;
    pStruct->pTail = nullptr;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_FindObjectIns(_, _, _, _, _, _)).Times(1).WillOnce(Return(1));

    int result = HDK_Device_GetValue(mockDeviceCtx, pStruct, eValue, pStruct);
    EXPECT_EQ(result, 0);

    free(pStruct);
    pStruct = nullptr;
}

TEST_F(CcspHomeSecurityHDKDeviceGetValueFixture, HDK_Device_GetValue_ConnectedClients_SUCCESS_1) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_ConnectedClients;
    char mockPathVal[] = "Device.DHCPv4.Server.Pool.2";
    char mockinsNum[] = "2";
    char mockMAC[] = "00:00:00:00:00:00";
    char mockHostName[] = "testDevice";
    char mockInterface[] = "erouter0";
    char mockVal[] = "true";

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    pStruct->pHead = nullptr;
    pStruct->pTail = nullptr;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityDHCPv4ServerPool"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("ClientNumberOfEntries"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockinsNum, mockinsNum + strlen(mockinsNum) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("Chaddr"), _, _))
    .Times(2)
    .WillRepeatedly(testing::DoAll(
             testing::SetArrayArgument<2>(mockMAC, mockMAC + strlen(mockMAC) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("X_CISCO_COM_HostName"), _, _))
    .Times(2)
    .WillRepeatedly(testing::DoAll(
             testing::SetArrayArgument<2>(mockHostName, mockHostName + strlen(mockHostName) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("X_CISCO_COM_Interface"), _, _))
    .Times(2)
    .WillRepeatedly(testing::DoAll(
             testing::SetArrayArgument<2>(mockInterface, mockInterface + strlen(mockInterface) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("Active"), _, _))
    .Times(2)
    .WillRepeatedly(testing::DoAll(
             testing::SetArrayArgument<2>(mockVal, mockVal + strlen(mockVal) + 1),
             Return(0)
    ));

    int result = HDK_Device_GetValue(mockDeviceCtx, pStruct, eValue, pStruct);
    EXPECT_EQ(result, 1);

    free(pStruct);
    pStruct = nullptr;
}

TEST_F(CcspHomeSecurityHDKDeviceGetValueFixture, HDK_Device_GetValue_ConnectedClients_SUCCESS_2) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_ConnectedClients;
    char mockPathVal[] = "Device.DHCPv4.Server.Pool.2";
    char mockinsNum[] = "2";
    char mockMAC[] = "00:00:00:00:00:00";
    char mockHostName[] = "testDevice";
    char mockInterface[] = "erouter0";
    char mockVal[] = "false";

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    pStruct->pHead = nullptr;
    pStruct->pTail = nullptr;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityDHCPv4ServerPool"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("ClientNumberOfEntries"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockinsNum, mockinsNum + strlen(mockinsNum) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("Chaddr"), _, _))
    .Times(2)
    .WillRepeatedly(testing::DoAll(
             testing::SetArrayArgument<2>(mockMAC, mockMAC + strlen(mockMAC) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("X_CISCO_COM_HostName"), _, _))
    .Times(2)
    .WillRepeatedly(testing::DoAll(
             testing::SetArrayArgument<2>(mockHostName, mockHostName + strlen(mockHostName) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("X_CISCO_COM_Interface"), _, _))
    .Times(2)
    .WillRepeatedly(testing::DoAll(
             testing::SetArrayArgument<2>(mockInterface, mockInterface + strlen(mockInterface) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("Active"), _, _))
    .Times(2)
    .WillRepeatedly(testing::DoAll(
             testing::SetArrayArgument<2>(mockVal, mockVal + strlen(mockVal) + 1),
             Return(0)
    ));

    int result = HDK_Device_GetValue(mockDeviceCtx, pStruct, eValue, pStruct);
    EXPECT_EQ(result, 1);

    free(pStruct);
    pStruct = nullptr;
}

TEST_F(CcspHomeSecurityHDKDeviceGetValueFixture, HDK_Device_GetValue_ConnectedClients_FAIL) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_ConnectedClients;
    char mockPathVal[] = "Device.DHCPv4.Server.Pool.2";
    char mockinsNum[] = "2";
    char mockMAC[] = "00:00:00:00:00:00";
    char mockHostName[] = "testDevice";
    char mockInterface[] = "erouter0";
    char mockVal[] = "false";

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    pStruct->pHead = nullptr;
    pStruct->pTail = nullptr;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityDHCPv4ServerPool"), _, _))
    .Times(1).WillOnce(Return(1));

    int result = HDK_Device_GetValue(mockDeviceCtx, pStruct, eValue, pStruct);
    EXPECT_EQ(result, 0);

    free(pStruct);
    pStruct = nullptr;
}

TEST_F(CcspHomeSecurityHDKDeviceGetValueFixture, HDK_Device_GetValue_RadioInfos_SUCCESS_1) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_RadioInfos;
    char mockPathVal[] = "Device.WiFi.Radio.1";
    char mockAlias[] = "Radio1";
    char mockOpStd[] = "2.4GHz";
    char mockSupportedStandards[] = "a,b,g,n";
    char mockPossibleChannels[] = "1,2,3,4,5,6,7,8,9,10,11";
    char mockApPathVal[] = "Device.WiFi.AccessPoint.3";
    char mockSupportedModes[] = "None,WEP-64,WEP-128,WPA-Personal,WPA2-Personal,WPA-WPA2-Personal,WPA-Enterprise,WPA2-Enterprise,WPA-WPA2-Enterprise";

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    pStruct->pHead = nullptr;
    pStruct->pTail = nullptr;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_FindObjectIns(_, _, _, _, _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
        testing::Invoke([&](MBusObj_t *, const char *, const char *, const char *, char insPath[][MAX_PATH_NAME], int *insNum) {
            strcpy(insPath[0], "Device.WiFi.Radio.1.");
            *insNum = 1;
        }),
        Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("Alias"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockAlias, mockAlias + strlen(mockAlias) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("OperatingFrequencyBand"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockOpStd, mockOpStd + strlen(mockOpStd) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("SupportedStandards"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockSupportedStandards, mockSupportedStandards + strlen(mockSupportedStandards) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("PossibleChannels"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPossibleChannels, mockPossibleChannels + strlen(mockPossibleChannels) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiAp"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockApPathVal, mockApPathVal + strlen(mockApPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("Security.ModesSupported"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockSupportedModes, mockSupportedModes + strlen(mockSupportedModes) + 1),
             Return(0)
    ));

    int result = HDK_Device_GetValue(mockDeviceCtx, pStruct, eValue, pStruct);
    EXPECT_EQ(result, 1);

    free(pStruct);
    pStruct = nullptr;
}

TEST_F(CcspHomeSecurityHDKDeviceGetValueFixture, HDK_Device_GetValue_RadioInfos_SUCCESS_2) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_RadioInfos;
    char mockPathVal[] = "Device.WiFi.Radio.1";
    char mockAlias[] = "Radio1";
    char mockOpStd[] = "5GHz";
    char mockSupportedStandards[] = "b,g,n";
    char mockPossibleChannels[] = "1-11";
    char mockApPathVal[] = "Device.WiFi.AccessPoint.3";
    char mockSupportedModes[] = "WEP-64,None,WEP-128,WPA-Personal,WPA2-Personal,WPA-WPA2-Personal,WPA-Enterprise,WPA2-Enterprise,WPA-WPA2-Enterprise";

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    pStruct->pHead = nullptr;
    pStruct->pTail = nullptr;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_FindObjectIns(_, _, _, _, _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
        testing::Invoke([&](MBusObj_t *, const char *, const char *, const char *, char insPath[][MAX_PATH_NAME], int *insNum) {
            strcpy(insPath[0], "Device.WiFi.Radio.1.");
            *insNum = 1;
        }),
        Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("Alias"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockAlias, mockAlias + strlen(mockAlias) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("OperatingFrequencyBand"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockOpStd, mockOpStd + strlen(mockOpStd) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("SupportedStandards"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockSupportedStandards, mockSupportedStandards + strlen(mockSupportedStandards) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("PossibleChannels"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPossibleChannels, mockPossibleChannels + strlen(mockPossibleChannels) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiAp"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockApPathVal, mockApPathVal + strlen(mockApPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("Security.ModesSupported"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockSupportedModes, mockSupportedModes + strlen(mockSupportedModes) + 1),
             Return(0)
    ));

    int result = HDK_Device_GetValue(mockDeviceCtx, pStruct, eValue, pStruct);
    EXPECT_EQ(result, 1);

    free(pStruct);
    pStruct = nullptr;
}

TEST_F(CcspHomeSecurityHDKDeviceGetValueFixture, HDK_Device_GetValue_RadioInfos_SUCCESS_3) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_RadioInfos;
    char mockPathVal[] = "Device.WiFi.Radio.1";
    char mockAlias[] = "Radio1";
    char mockOpStd[] = "2.4GHz";
    char mockSupportedStandards[] = "n,a";
    char mockPossibleChannels[] = "1,2,3,4,5,6,7,8,9,10,11";
    char mockApPathVal[] = "Device.WiFi.AccessPoint.3";
    char mockSupportedModes[] = "WEP-128,WPA-Personal,WPA2-Personal,WPA-WPA2-Personal,WPA-Enterprise,WPA2-Enterprise,WPA-WPA2-Enterprise";

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    pStruct->pHead = nullptr;
    pStruct->pTail = nullptr;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_FindObjectIns(_, _, _, _, _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
        testing::Invoke([&](MBusObj_t *, const char *, const char *, const char *, char insPath[][MAX_PATH_NAME], int *insNum) {
            strcpy(insPath[0], "Device.WiFi.Radio.1.");
            *insNum = 1;
        }),
        Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("Alias"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockAlias, mockAlias + strlen(mockAlias) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("OperatingFrequencyBand"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockOpStd, mockOpStd + strlen(mockOpStd) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("SupportedStandards"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockSupportedStandards, mockSupportedStandards + strlen(mockSupportedStandards) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("PossibleChannels"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPossibleChannels, mockPossibleChannels + strlen(mockPossibleChannels) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiAp"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockApPathVal, mockApPathVal + strlen(mockApPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("Security.ModesSupported"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockSupportedModes, mockSupportedModes + strlen(mockSupportedModes) + 1),
             Return(0)
    ));

    int result = HDK_Device_GetValue(mockDeviceCtx, pStruct, eValue, pStruct);
    EXPECT_EQ(result, 1);

    free(pStruct);
    pStruct = nullptr;
}

TEST_F(CcspHomeSecurityHDKDeviceGetValueFixture, HDK_Device_GetValue_RadioInfos_SUCCESS_4) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_RadioInfos;
    char mockPathVal[] = "Device.WiFi.Radio.1";
    char mockAlias[] = "Radio1";
    char mockOpStd[] = "2.4GHz";
    char mockSupportedStandards[] = "g,b";
    char mockPossibleChannels[] = "1,2,3,4,5,6,7,8,9,10,11";
    char mockApPathVal[] = "Device.WiFi.AccessPoint.3";
    char mockSupportedModes[] = "WPA-Personal,WPA2-Personal,WPA-WPA2-Personal,WPA-Enterprise,WPA2-Enterprise,WPA-WPA2-Enterprise";

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    pStruct->pHead = nullptr;
    pStruct->pTail = nullptr;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_FindObjectIns(_, _, _, _, _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
        testing::Invoke([&](MBusObj_t *, const char *, const char *, const char *, char insPath[][MAX_PATH_NAME], int *insNum) {
            strcpy(insPath[0], "Device.WiFi.Radio.1.");
            *insNum = 1;
        }),
        Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("Alias"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockAlias, mockAlias + strlen(mockAlias) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("OperatingFrequencyBand"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockOpStd, mockOpStd + strlen(mockOpStd) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("SupportedStandards"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockSupportedStandards, mockSupportedStandards + strlen(mockSupportedStandards) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("PossibleChannels"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPossibleChannels, mockPossibleChannels + strlen(mockPossibleChannels) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiAp"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockApPathVal, mockApPathVal + strlen(mockApPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("Security.ModesSupported"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockSupportedModes, mockSupportedModes + strlen(mockSupportedModes) + 1),
             Return(0)
    ));

    int result = HDK_Device_GetValue(mockDeviceCtx, pStruct, eValue, pStruct);
    EXPECT_EQ(result, 1);

    free(pStruct);
    pStruct = nullptr;
}

TEST_F(CcspHomeSecurityHDKDeviceGetValueFixture, HDK_Device_GetValue_RadioInfos_SUCCESS_5) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_RadioInfos;
    char mockPathVal[] = "Device.WiFi.Radio.1";
    char mockAlias[] = "Radio1";
    char mockOpStd[] = "2.4GHz";
    char mockSupportedStandards[] = "n,b";
    char mockPossibleChannels[] = "1,2,3,4,5,6,7,8,9,10,11";
    char mockApPathVal[] = "Device.WiFi.AccessPoint.3";
    char mockSupportedModes[] = "WPA2-Personal,WPA-WPA2-Personal,WPA-Enterprise,WPA2-Enterprise,WPA-WPA2-Enterprise";

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    pStruct->pHead = nullptr;
    pStruct->pTail = nullptr;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_FindObjectIns(_, _, _, _, _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
        testing::Invoke([&](MBusObj_t *, const char *, const char *, const char *, char insPath[][MAX_PATH_NAME], int *insNum) {
            strcpy(insPath[0], "Device.WiFi.Radio.1.");
            *insNum = 1;
        }),
        Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("Alias"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockAlias, mockAlias + strlen(mockAlias) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("OperatingFrequencyBand"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockOpStd, mockOpStd + strlen(mockOpStd) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("SupportedStandards"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockSupportedStandards, mockSupportedStandards + strlen(mockSupportedStandards) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("PossibleChannels"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPossibleChannels, mockPossibleChannels + strlen(mockPossibleChannels) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiAp"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockApPathVal, mockApPathVal + strlen(mockApPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("Security.ModesSupported"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockSupportedModes, mockSupportedModes + strlen(mockSupportedModes) + 1),
             Return(0)
    ));

    int result = HDK_Device_GetValue(mockDeviceCtx, pStruct, eValue, pStruct);
    EXPECT_EQ(result, 1);

    free(pStruct);
    pStruct = nullptr;
}

TEST_F(CcspHomeSecurityHDKDeviceGetValueFixture, HDK_Device_GetValue_RadioInfos_SUCCESS_6) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_RadioInfos;
    char mockPathVal[] = "Device.WiFi.Radio.1";
    char mockAlias[] = "Radio1";
    char mockOpStd[] = "2.4GHz";
    char mockSupportedStandards[] = "g,n";
    char mockPossibleChannels[] = "1,2,3,4,5,6,7,8,9,10,11";
    char mockApPathVal[] = "Device.WiFi.AccessPoint.3";
    char mockSupportedModes[] = "WPA-WPA2-Personal,WPA-Enterprise,WPA2-Enterprise,WPA-WPA2-Enterprise";

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    pStruct->pHead = nullptr;
    pStruct->pTail = nullptr;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_FindObjectIns(_, _, _, _, _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
        testing::Invoke([&](MBusObj_t *, const char *, const char *, const char *, char insPath[][MAX_PATH_NAME], int *insNum) {
            strcpy(insPath[0], "Device.WiFi.Radio.1.");
            *insNum = 1;
        }),
        Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("Alias"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockAlias, mockAlias + strlen(mockAlias) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("OperatingFrequencyBand"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockOpStd, mockOpStd + strlen(mockOpStd) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("SupportedStandards"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockSupportedStandards, mockSupportedStandards + strlen(mockSupportedStandards) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("PossibleChannels"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPossibleChannels, mockPossibleChannels + strlen(mockPossibleChannels) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiAp"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockApPathVal, mockApPathVal + strlen(mockApPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("Security.ModesSupported"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockSupportedModes, mockSupportedModes + strlen(mockSupportedModes) + 1),
             Return(0)
    ));

    int result = HDK_Device_GetValue(mockDeviceCtx, pStruct, eValue, pStruct);
    EXPECT_EQ(result, 1);

    free(pStruct);
    pStruct = nullptr;
}

TEST_F(CcspHomeSecurityHDKDeviceGetValueFixture, HDK_Device_GetValue_RadioInfos_SUCCESS_7) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_RadioInfos;
    char mockPathVal[] = "Device.WiFi.Radio.1";
    char mockAlias[] = "Radio1";
    char mockOpStd[] = "2.4GHz";
    char mockSupportedStandards[] = "a";
    char mockPossibleChannels[] = "1,2,3,4,5,6,7,8,9,10,11";
    char mockApPathVal[] = "Device.WiFi.AccessPoint.3";
    char mockSupportedModes[] = "WPA-Enterprise,WPA2-Enterprise,WPA-WPA2-Enterprise";

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    pStruct->pHead = nullptr;
    pStruct->pTail = nullptr;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_FindObjectIns(_, _, _, _, _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
        testing::Invoke([&](MBusObj_t *, const char *, const char *, const char *, char insPath[][MAX_PATH_NAME], int *insNum) {
            strcpy(insPath[0], "Device.WiFi.Radio.1.");
            *insNum = 1;
        }),
        Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("Alias"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockAlias, mockAlias + strlen(mockAlias) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("OperatingFrequencyBand"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockOpStd, mockOpStd + strlen(mockOpStd) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("SupportedStandards"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockSupportedStandards, mockSupportedStandards + strlen(mockSupportedStandards) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("PossibleChannels"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPossibleChannels, mockPossibleChannels + strlen(mockPossibleChannels) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiAp"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockApPathVal, mockApPathVal + strlen(mockApPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("Security.ModesSupported"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockSupportedModes, mockSupportedModes + strlen(mockSupportedModes) + 1),
             Return(0)
    ));

    int result = HDK_Device_GetValue(mockDeviceCtx, pStruct, eValue, pStruct);
    EXPECT_EQ(result, 1);

    free(pStruct);
    pStruct = nullptr;
}

TEST_F(CcspHomeSecurityHDKDeviceGetValueFixture, HDK_Device_GetValue_RadioInfos_SUCCESS_8) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_RadioInfos;
    char mockPathVal[] = "Device.WiFi.Radio.1";
    char mockAlias[] = "Radio1";
    char mockOpStd[] = "2.4GHz";
    char mockSupportedStandards[] = "b";
    char mockPossibleChannels[] = "1,2,3,4,5,6,7,8,9,10,11";
    char mockApPathVal[] = "Device.WiFi.AccessPoint.3";
    char mockSupportedModes[] = "WPA2-Enterprise,WPA-WPA2-Enterprise";

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    pStruct->pHead = nullptr;
    pStruct->pTail = nullptr;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_FindObjectIns(_, _, _, _, _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
        testing::Invoke([&](MBusObj_t *, const char *, const char *, const char *, char insPath[][MAX_PATH_NAME], int *insNum) {
            strcpy(insPath[0], "Device.WiFi.Radio.1.");
            *insNum = 1;
        }),
        Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("Alias"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockAlias, mockAlias + strlen(mockAlias) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("OperatingFrequencyBand"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockOpStd, mockOpStd + strlen(mockOpStd) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("SupportedStandards"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockSupportedStandards, mockSupportedStandards + strlen(mockSupportedStandards) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("PossibleChannels"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPossibleChannels, mockPossibleChannels + strlen(mockPossibleChannels) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiAp"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockApPathVal, mockApPathVal + strlen(mockApPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("Security.ModesSupported"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockSupportedModes, mockSupportedModes + strlen(mockSupportedModes) + 1),
             Return(0)
    ));

    int result = HDK_Device_GetValue(mockDeviceCtx, pStruct, eValue, pStruct);
    EXPECT_EQ(result, 1);

    free(pStruct);
    pStruct = nullptr;
}

TEST_F(CcspHomeSecurityHDKDeviceGetValueFixture, HDK_Device_GetValue_RadioInfos_SUCCESS_9) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_RadioInfos;
    char mockPathVal[] = "Device.WiFi.Radio.1";
    char mockAlias[] = "Radio1";
    char mockOpStd[] = "2.4GHz";
    char mockSupportedStandards[] = "g";
    char mockPossibleChannels[] = "1,2,3,4,5,6,7,8,9,10,11";
    char mockApPathVal[] = "Device.WiFi.AccessPoint.3";
    char mockSupportedModes[] = "WPA-WPA2-Enterprise";

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    pStruct->pHead = nullptr;
    pStruct->pTail = nullptr;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_FindObjectIns(_, _, _, _, _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
        testing::Invoke([&](MBusObj_t *, const char *, const char *, const char *, char insPath[][MAX_PATH_NAME], int *insNum) {
            strcpy(insPath[0], "Device.WiFi.Radio.1.");
            *insNum = 1;
        }),
        Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("Alias"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockAlias, mockAlias + strlen(mockAlias) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("OperatingFrequencyBand"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockOpStd, mockOpStd + strlen(mockOpStd) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("SupportedStandards"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockSupportedStandards, mockSupportedStandards + strlen(mockSupportedStandards) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("PossibleChannels"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPossibleChannels, mockPossibleChannels + strlen(mockPossibleChannels) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiAp"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockApPathVal, mockApPathVal + strlen(mockApPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("Security.ModesSupported"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockSupportedModes, mockSupportedModes + strlen(mockSupportedModes) + 1),
             Return(0)
    ));

    int result = HDK_Device_GetValue(mockDeviceCtx, pStruct, eValue, pStruct);
    EXPECT_EQ(result, 1);

    free(pStruct);
    pStruct = nullptr;
}

TEST_F(CcspHomeSecurityHDKDeviceGetValueFixture, HDK_Device_GetValue_RadioInfos_SUCCESS_10) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_RadioInfos;
    char mockPathVal[] = "Device.WiFi.Radio.1";
    char mockAlias[] = "Radio1";
    char mockOpStd[] = "2.4GHz";
    char mockSupportedStandards[] = "n";
    char mockPossibleChannels[] = "1,2,3,4,5,6,7,8,9,10,11";
    char mockApPathVal[] = "Device.WiFi.AccessPoint.3";
    char mockSupportedModes[] = "WPA-WPA2-Enterprise";

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    pStruct->pHead = nullptr;
    pStruct->pTail = nullptr;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_FindObjectIns(_, _, _, _, _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
        testing::Invoke([&](MBusObj_t *, const char *, const char *, const char *, char insPath[][MAX_PATH_NAME], int *insNum) {
            strcpy(insPath[0], "Device.WiFi.Radio.1.");
            *insNum = 1;
        }),
        Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("Alias"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockAlias, mockAlias + strlen(mockAlias) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("OperatingFrequencyBand"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockOpStd, mockOpStd + strlen(mockOpStd) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("SupportedStandards"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockSupportedStandards, mockSupportedStandards + strlen(mockSupportedStandards) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("PossibleChannels"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPossibleChannels, mockPossibleChannels + strlen(mockPossibleChannels) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiAp"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockApPathVal, mockApPathVal + strlen(mockApPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("Security.ModesSupported"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockSupportedModes, mockSupportedModes + strlen(mockSupportedModes) + 1),
             Return(0)
    ));

    int result = HDK_Device_GetValue(mockDeviceCtx, pStruct, eValue, pStruct);
    EXPECT_EQ(result, 1);

    free(pStruct);
    pStruct = nullptr;
}

TEST_F(CcspHomeSecurityHDKDeviceGetValueFixture, HDK_Device_GetValue_RadioInfos_FAIL_1) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_RadioInfos;
    char mockPathVal[] = "Device.WiFi.Radio.1";
    char mockAlias[] = "Radio1";

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    pStruct->pHead = nullptr;
    pStruct->pTail = nullptr;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_FindObjectIns(_, _, _, _, _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
        testing::Invoke([&](MBusObj_t *, const char *, const char *, const char *, char insPath[][MAX_PATH_NAME], int *insNum) {
            strcpy(insPath[0], "Device.WiFi.Radio.1.");
            *insNum = 1;
        }),
        Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .Times(1).WillOnce(Return(1));

    int result = HDK_Device_GetValue(mockDeviceCtx, pStruct, eValue, pStruct);
    EXPECT_EQ(result, 0);

    free(pStruct);
    pStruct = nullptr;
}

TEST_F(CcspHomeSecurityHDKDeviceGetValueFixture, HDK_Device_GetValue_RadioInfos_FAIL_2) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_RadioInfos;
    char mockPathVal[] = "Device.WiFi.Radio.1";
    char mockAlias[] = "Radio1";
    char mockOpStd[] = "2.4GHz";
    char mockSupportedStandards[] = "a,b,g,n";
    char mockPossibleChannels[] = "1,2,3,4,5,6,7,8,9,10,11";
    char mockApPathVal[] = "Device.WiFi.AccessPoint.3";
    char mockSupportedModes[] = "None,WEP-64,WEP-128,WPA-Personal,WPA2-Personal,WPA-WPA2-Personal,WPA-Enterprise,WPA2-Enterprise,WPA-WPA2-Enterprise";

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    pStruct->pHead = nullptr;
    pStruct->pTail = nullptr;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_FindObjectIns(_, _, _, _, _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
        testing::Invoke([&](MBusObj_t *, const char *, const char *, const char *, char insPath[][MAX_PATH_NAME], int *insNum) {
            strcpy(insPath[0], "Device.WiFi.Radio.1.");
            *insNum = 1;
        }),
        Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("Alias"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockAlias, mockAlias + strlen(mockAlias) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("OperatingFrequencyBand"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockOpStd, mockOpStd + strlen(mockOpStd) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("SupportedStandards"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockSupportedStandards, mockSupportedStandards + strlen(mockSupportedStandards) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("PossibleChannels"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPossibleChannels, mockPossibleChannels + strlen(mockPossibleChannels) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiAp"), _, _))
    .Times(1).WillOnce(Return(1));

    int result = HDK_Device_GetValue(mockDeviceCtx, pStruct, eValue, pStruct);
    EXPECT_EQ(result, 0);

    free(pStruct);
    pStruct = nullptr;
}

TEST_F(CcspHomeSecurityHDKDeviceGetValueFixture, HDK_Device_GetValue_WLanSecurityEnabled_SUCCESS_1) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WLanSecurityEnabled;
    char mockPathVal[] = "Device.WiFi.Radio.1";
    char mockAlias[] = "Radio0";
    char mockApPathVal[] = "Device.WiFi.AccessPoint.3";
    char mockEnabledMode[] = "None";
    char mockVal[] = "1800";
    char mockKeyPhrase[] = "12345678";

    HDK_Struct* pInput = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pInput, nullptr);

    HDK_Member__STRING__* pMember1 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember1, nullptr);

    pMember1->node.element = HDK_Element_PN_RadioID;
    pMember1->node.type = HDK_Type__STRING__;
    pMember1->node.pNext = nullptr;
    pMember1->pszValue = strdup("Radio0");

    pInput->pHead = (HDK_Member*)pMember1;
    pInput->pTail = (HDK_Member*)pMember1;

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    pStruct->pHead = nullptr;
    pStruct->pTail = nullptr;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("Alias"), _, _))
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

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("Security.ModeEnabled"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockEnabledMode, mockEnabledMode + strlen(mockEnabledMode) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("Security.RekeyingInterval"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockVal, mockVal + strlen(mockVal) + 1),
             Return(0)
    ));

    int result = HDK_Device_GetValue(mockDeviceCtx, pStruct, eValue, pInput);
    EXPECT_EQ(result, 1);

    free(pMember1);
    free(pStruct);
    free(pInput);
    pMember1 = nullptr;
    pStruct = nullptr;
    pInput = nullptr;
}

TEST_F(CcspHomeSecurityHDKDeviceGetValueFixture, HDK_Device_GetValue_WLanSecurityEnabled_SUCCESS_2) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WLanSecurityEnabled;
    char mockPathVal[] = "Device.WiFi.Radio.1";
    char mockAlias[] = "Radio0";
    char mockApPathVal[] = "Device.WiFi.AccessPoint.3";
    char mockEnabledMode[] = "WEP-64";
    char mockVal[] = "1800";
    char mockKeyPhrase[] = "12345678";

    HDK_Struct* pInput = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pInput, nullptr);

    HDK_Member__STRING__* pMember1 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember1, nullptr);

    pMember1->node.element = HDK_Element_PN_RadioID;
    pMember1->node.type = HDK_Type__STRING__;
    pMember1->node.pNext = nullptr;
    pMember1->pszValue = strdup("Radio0");

    pInput->pHead = (HDK_Member*)pMember1;
    pInput->pTail = (HDK_Member*)pMember1;

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    pStruct->pHead = nullptr;
    pStruct->pTail = nullptr;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("Alias"), _, _))
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

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("Security.ModeEnabled"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockEnabledMode, mockEnabledMode + strlen(mockEnabledMode) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("Security.X_CISCO_COM_WEPKey64Bit.1.WEPKey"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockKeyPhrase, mockKeyPhrase + strlen(mockKeyPhrase) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("Security.RekeyingInterval"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockVal, mockVal + strlen(mockVal) + 1),
             Return(0)
    ));

    int result = HDK_Device_GetValue(mockDeviceCtx, pStruct, eValue, pInput);
    EXPECT_EQ(result, 1);

    free(pMember1);
    free(pStruct);
    free(pInput);
    pMember1 = nullptr;
    pStruct = nullptr;
    pInput = nullptr;
}

TEST_F(CcspHomeSecurityHDKDeviceGetValueFixture, HDK_Device_GetValue_WLanSecurityEnabled_SUCCESS_3) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WLanSecurityEnabled;
    char mockPathVal[] = "Device.WiFi.Radio.1";
    char mockAlias[] = "Radio0";
    char mockApPathVal[] = "Device.WiFi.AccessPoint.3";
    char mockEnabledMode[] = "WEP-128";
    char mockVal[] = "1800";
    char mockKeyPhrase[] = "12345678";

    HDK_Struct* pInput = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pInput, nullptr);

    HDK_Member__STRING__* pMember1 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember1, nullptr);

    pMember1->node.element = HDK_Element_PN_RadioID;
    pMember1->node.type = HDK_Type__STRING__;
    pMember1->node.pNext = nullptr;
    pMember1->pszValue = strdup("Radio0");

    pInput->pHead = (HDK_Member*)pMember1;
    pInput->pTail = (HDK_Member*)pMember1;

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    pStruct->pHead = nullptr;
    pStruct->pTail = nullptr;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("Alias"), _, _))
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

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("Security.ModeEnabled"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockEnabledMode, mockEnabledMode + strlen(mockEnabledMode) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("Security.X_CISCO_COM_WEPKey128Bit.1.WEPKey"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockKeyPhrase, mockKeyPhrase + strlen(mockKeyPhrase) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("Security.RekeyingInterval"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockVal, mockVal + strlen(mockVal) + 1),
             Return(0)
    ));

    int result = HDK_Device_GetValue(mockDeviceCtx, pStruct, eValue, pInput);
    EXPECT_EQ(result, 1);

    free(pMember1);
    free(pStruct);
    free(pInput);
    pMember1 = nullptr;
    pStruct = nullptr;
    pInput = nullptr;
}

TEST_F(CcspHomeSecurityHDKDeviceGetValueFixture, HDK_Device_GetValue_WLanSecurityEnabled_SUCCESS_4) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WLanSecurityEnabled;
    char mockPathVal[] = "Device.WiFi.Radio.1";
    char mockAlias[] = "Radio0";
    char mockApPathVal[] = "Device.WiFi.AccessPoint.3";
    char mockEnabledMode[] = "WPA-Personal";
    char mockVal[] = "1800";
    char mockKeyPhrase[] = "12345678";

    HDK_Struct* pInput = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pInput, nullptr);

    HDK_Member__STRING__* pMember1 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember1, nullptr);

    pMember1->node.element = HDK_Element_PN_RadioID;
    pMember1->node.type = HDK_Type__STRING__;
    pMember1->node.pNext = nullptr;
    pMember1->pszValue = strdup("Radio0");

    pInput->pHead = (HDK_Member*)pMember1;
    pInput->pTail = (HDK_Member*)pMember1;

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    pStruct->pHead = nullptr;
    pStruct->pTail = nullptr;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("Alias"), _, _))
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

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("Security.ModeEnabled"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockEnabledMode, mockEnabledMode + strlen(mockEnabledMode) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("Security.X_COMCAST-COM_KeyPassphrase"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockKeyPhrase, mockKeyPhrase + strlen(mockKeyPhrase) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("Security.RekeyingInterval"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockVal, mockVal + strlen(mockVal) + 1),
             Return(0)
    ));

    int result = HDK_Device_GetValue(mockDeviceCtx, pStruct, eValue, pInput);
    EXPECT_EQ(result, 1);

    free(pMember1);
    free(pStruct);
    free(pInput);
    pMember1 = nullptr;
    pStruct = nullptr;
    pInput = nullptr;
}

TEST_F(CcspHomeSecurityHDKDeviceGetValueFixture, HDK_Device_GetValue_WLanSecurityEnabled_SUCCESS_5) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WLanSecurityEnabled;
    char mockPathVal[] = "Device.WiFi.Radio.1";
    char mockAlias[] = "Radio0";
    char mockApPathVal[] = "Device.WiFi.AccessPoint.3";
    char mockEnabledMode[] = "WPA2-Personal";
    char mockVal[] = "1800";
    char mockKeyPhrase[] = "12345678";

    HDK_Struct* pInput = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pInput, nullptr);

    HDK_Member__STRING__* pMember1 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember1, nullptr);

    pMember1->node.element = HDK_Element_PN_RadioID;
    pMember1->node.type = HDK_Type__STRING__;
    pMember1->node.pNext = nullptr;
    pMember1->pszValue = strdup("Radio0");

    pInput->pHead = (HDK_Member*)pMember1;
    pInput->pTail = (HDK_Member*)pMember1;

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    pStruct->pHead = nullptr;
    pStruct->pTail = nullptr;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("Alias"), _, _))
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

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("Security.ModeEnabled"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockEnabledMode, mockEnabledMode + strlen(mockEnabledMode) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("Security.X_COMCAST-COM_KeyPassphrase"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockKeyPhrase, mockKeyPhrase + strlen(mockKeyPhrase) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("Security.RekeyingInterval"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockVal, mockVal + strlen(mockVal) + 1),
             Return(0)
    ));

    int result = HDK_Device_GetValue(mockDeviceCtx, pStruct, eValue, pInput);
    EXPECT_EQ(result, 1);

    free(pMember1);
    free(pStruct);
    free(pInput);
    pMember1 = nullptr;
    pStruct = nullptr;
    pInput = nullptr;
}


TEST_F(CcspHomeSecurityHDKDeviceGetValueFixture, HDK_Device_GetValue_WLanSecurityEnabled_SUCCESS_6) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WLanSecurityEnabled;
    char mockPathVal[] = "Device.WiFi.Radio.1";
    char mockAlias[] = "Radio0";
    char mockApPathVal[] = "Device.WiFi.AccessPoint.3";
    char mockEnabledMode[] = "WPA-WPA2-Personal";
    char mockVal[] = "1800";
    char mockKeyPhrase[] = "12345678";

    HDK_Struct* pInput = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pInput, nullptr);

    HDK_Member__STRING__* pMember1 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember1, nullptr);

    pMember1->node.element = HDK_Element_PN_RadioID;
    pMember1->node.type = HDK_Type__STRING__;
    pMember1->node.pNext = nullptr;
    pMember1->pszValue = strdup("Radio0");

    pInput->pHead = (HDK_Member*)pMember1;
    pInput->pTail = (HDK_Member*)pMember1;

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    pStruct->pHead = nullptr;
    pStruct->pTail = nullptr;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("Alias"), _, _))
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

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("Security.ModeEnabled"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockEnabledMode, mockEnabledMode + strlen(mockEnabledMode) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("Security.X_COMCAST-COM_KeyPassphrase"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockKeyPhrase, mockKeyPhrase + strlen(mockKeyPhrase) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("Security.RekeyingInterval"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockVal, mockVal + strlen(mockVal) + 1),
             Return(0)
    ));

    int result = HDK_Device_GetValue(mockDeviceCtx, pStruct, eValue, pInput);
    EXPECT_EQ(result, 1);

    free(pMember1);
    free(pStruct);
    free(pInput);
    pMember1 = nullptr;
    pStruct = nullptr;
    pInput = nullptr;
}

TEST_F(CcspHomeSecurityHDKDeviceGetValueFixture, HDK_Device_GetValue_WLanSecurityEnabled_SUCCESS_7) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WLanSecurityEnabled;
    char mockPathVal[] = "Device.WiFi.Radio.1";
    char mockAlias[] = "Radio0";
    char mockApPathVal[] = "Device.WiFi.AccessPoint.3";
    char mockEnabledMode[] = "WPA-Enterprise";
    char mockVal[] = "1800";
    char mockKeyPhrase[] = "12345678";

    HDK_Struct* pInput = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pInput, nullptr);

    HDK_Member__STRING__* pMember1 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember1, nullptr);

    pMember1->node.element = HDK_Element_PN_RadioID;
    pMember1->node.type = HDK_Type__STRING__;
    pMember1->node.pNext = nullptr;
    pMember1->pszValue = strdup("Radio0");

    pInput->pHead = (HDK_Member*)pMember1;
    pInput->pTail = (HDK_Member*)pMember1;

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    pStruct->pHead = nullptr;
    pStruct->pTail = nullptr;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("Alias"), _, _))
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

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("Security.ModeEnabled"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockEnabledMode, mockEnabledMode + strlen(mockEnabledMode) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("Security.X_COMCAST-COM_KeyPassphrase"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockKeyPhrase, mockKeyPhrase + strlen(mockKeyPhrase) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("Security.RekeyingInterval"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockVal, mockVal + strlen(mockVal) + 1),
             Return(0)
    ));

    int result = HDK_Device_GetValue(mockDeviceCtx, pStruct, eValue, pInput);
    EXPECT_EQ(result, 1);

    free(pMember1);
    free(pStruct);
    free(pInput);
    pMember1 = nullptr;
    pStruct = nullptr;
    pInput = nullptr;
}

TEST_F(CcspHomeSecurityHDKDeviceGetValueFixture, HDK_Device_GetValue_WLanSecurityEnabled_SUCCESS_8) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WLanSecurityEnabled;
    char mockPathVal[] = "Device.WiFi.Radio.1";
    char mockAlias[] = "Radio0";
    char mockApPathVal[] = "Device.WiFi.AccessPoint.3";
    char mockEnabledMode[] = "WPA2-Enterprise";
    char mockVal[] = "1800";
    char mockKeyPhrase[] = "12345678";

    HDK_Struct* pInput = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pInput, nullptr);

    HDK_Member__STRING__* pMember1 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember1, nullptr);

    pMember1->node.element = HDK_Element_PN_RadioID;
    pMember1->node.type = HDK_Type__STRING__;
    pMember1->node.pNext = nullptr;
    pMember1->pszValue = strdup("Radio0");

    pInput->pHead = (HDK_Member*)pMember1;
    pInput->pTail = (HDK_Member*)pMember1;

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    pStruct->pHead = nullptr;
    pStruct->pTail = nullptr;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("Alias"), _, _))
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

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("Security.ModeEnabled"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockEnabledMode, mockEnabledMode + strlen(mockEnabledMode) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("Security.X_COMCAST-COM_KeyPassphrase"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockKeyPhrase, mockKeyPhrase + strlen(mockKeyPhrase) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("Security.RekeyingInterval"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockVal, mockVal + strlen(mockVal) + 1),
             Return(0)
    ));

    int result = HDK_Device_GetValue(mockDeviceCtx, pStruct, eValue, pInput);
    EXPECT_EQ(result, 1);

    free(pMember1);
    free(pStruct);
    free(pInput);
    pMember1 = nullptr;
    pStruct = nullptr;
    pInput = nullptr;
}

TEST_F(CcspHomeSecurityHDKDeviceGetValueFixture, HDK_Device_GetValue_WLanSecurityEnabled_SUCCESS_9) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WLanSecurityEnabled;
    char mockPathVal[] = "Device.WiFi.Radio.1";
    char mockAlias[] = "Radio0";
    char mockApPathVal[] = "Device.WiFi.AccessPoint.3";
    char mockEnabledMode[] = "WPA-WPA2-Enterprise";
    char mockVal[] = "1800";
    char mockKeyPhrase[] = "12345678";

    HDK_Struct* pInput = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pInput, nullptr);

    HDK_Member__STRING__* pMember1 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember1, nullptr);

    pMember1->node.element = HDK_Element_PN_RadioID;
    pMember1->node.type = HDK_Type__STRING__;
    pMember1->node.pNext = nullptr;
    pMember1->pszValue = strdup("Radio0");

    pInput->pHead = (HDK_Member*)pMember1;
    pInput->pTail = (HDK_Member*)pMember1;

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    pStruct->pHead = nullptr;
    pStruct->pTail = nullptr;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("Alias"), _, _))
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

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("Security.ModeEnabled"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockEnabledMode, mockEnabledMode + strlen(mockEnabledMode) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("Security.X_COMCAST-COM_KeyPassphrase"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockKeyPhrase, mockKeyPhrase + strlen(mockKeyPhrase) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("Security.RekeyingInterval"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockVal, mockVal + strlen(mockVal) + 1),
             Return(0)
    ));

    int result = HDK_Device_GetValue(mockDeviceCtx, pStruct, eValue, pInput);
    EXPECT_EQ(result, 1);

    free(pMember1);
    free(pStruct);
    free(pInput);
    pMember1 = nullptr;
    pStruct = nullptr;
    pInput = nullptr;
}

TEST_F(CcspHomeSecurityHDKDeviceGetValueFixture, HDK_Device_GetValue_WLanSecurityEnabled_FAIL_1) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WLanSecurityEnabled;

    HDK_Struct* pInput = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pInput, nullptr);

    HDK_Member__STRING__* pMember1 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember1, nullptr);

    pMember1->node.element = HDK_Element_PN_RadioID;
    pMember1->node.type = HDK_Type__STRING__;
    pMember1->node.pNext = nullptr;
    pMember1->pszValue = strdup("Radio0");

    pInput->pHead = (HDK_Member*)pMember1;
    pInput->pTail = (HDK_Member*)pMember1;

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    pStruct->pHead = nullptr;
    pStruct->pTail = nullptr;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .Times(1).WillOnce(Return(1));

    int result = HDK_Device_GetValue(mockDeviceCtx, pStruct, eValue, pInput);
    EXPECT_EQ(result, 0);

    free(pMember1);
    free(pStruct);
    free(pInput);
    pMember1 = nullptr;
    pStruct = nullptr;
    pInput = nullptr;
}

TEST_F(CcspHomeSecurityHDKDeviceGetValueFixture, HDK_Device_GetValue_WLanSecurityEnabled_FAIL_2) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WLanSecurityEnabled;
    char mockPathVal[] = "Device.WiFi.Radio.1";
    char mockAlias[] = "Radio1";

    HDK_Struct* pInput = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pInput, nullptr);

    HDK_Member__STRING__* pMember1 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember1, nullptr);

    pMember1->node.element = HDK_Element_PN_RadioID;
    pMember1->node.type = HDK_Type__STRING__;
    pMember1->node.pNext = nullptr;
    pMember1->pszValue = strdup("Radio0");

    pInput->pHead = (HDK_Member*)pMember1;
    pInput->pTail = (HDK_Member*)pMember1;

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    pStruct->pHead = nullptr;
    pStruct->pTail = nullptr;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("Alias"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockAlias, mockAlias + strlen(mockAlias) + 1),
             Return(0)
    ));
    int result = HDK_Device_GetValue(mockDeviceCtx, pStruct, eValue, pInput);
    EXPECT_EQ(result, 0);

    free(pMember1);
    free(pStruct);
    free(pInput);
    pMember1 = nullptr;
    pStruct = nullptr;
    pInput = nullptr;
}

TEST_F(CcspHomeSecurityHDKDeviceGetValueFixture, HDK_Device_GetValue_WLanSecurityEnabled_FAIL_3) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WLanSecurityEnabled;
    char mockPathVal[] = "Device.WiFi.Radio.1";
    char mockAlias[] = "Radio0";

    HDK_Struct* pInput = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pInput, nullptr);

    HDK_Member__STRING__* pMember1 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember1, nullptr);

    pMember1->node.element = HDK_Element_PN_RadioID;
    pMember1->node.type = HDK_Type__STRING__;
    pMember1->node.pNext = nullptr;
    pMember1->pszValue = strdup("Radio0");

    pInput->pHead = (HDK_Member*)pMember1;
    pInput->pTail = (HDK_Member*)pMember1;

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    pStruct->pHead = nullptr;
    pStruct->pTail = nullptr;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("Alias"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockAlias, mockAlias + strlen(mockAlias) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiAp"), _, _))
    .Times(1).WillOnce(Return(1));

    int result = HDK_Device_GetValue(mockDeviceCtx, pStruct, eValue, pInput);
    EXPECT_EQ(result, 0);

    free(pMember1);
    free(pStruct);
    free(pInput);
    pMember1 = nullptr;
    pStruct = nullptr;
    pInput = nullptr;
}

TEST_F(CcspHomeSecurityHDKDeviceGetValueFixture, HDK_Device_GetValue_WLanEncryption_SUCCESS_1) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WLanEncryption;
    char mockPathVal[] = "Device.WiFi.Radio.1";
    char mockAlias[] = "Radio0";
    char mockApPathVal[] = "Device.WiFi.AccessPoint.3";
    char mockEnabledMode[] = "WPA-Personal";
    char mockEncrytionMethod[] = "AES";

    HDK_Struct* pInput = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pInput, nullptr);

    HDK_Member__STRING__* pMember1 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember1, nullptr);

    pMember1->node.element = HDK_Element_PN_RadioID;
    pMember1->node.type = HDK_Type__STRING__;
    pMember1->node.pNext = nullptr;
    pMember1->pszValue = strdup("Radio0");

    pInput->pHead = (HDK_Member*)pMember1;
    pInput->pTail = (HDK_Member*)pMember1;

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    pStruct->pHead = nullptr;
    pStruct->pTail = nullptr;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("Alias"), _, _))
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

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("Security.ModeEnabled"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockEnabledMode, mockEnabledMode + strlen(mockEnabledMode) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("Security.X_CISCO_COM_EncryptionMethod"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockEncrytionMethod, mockEncrytionMethod + strlen(mockEncrytionMethod) + 1),
             Return(0)
    ));

    int result = HDK_Device_GetValue(mockDeviceCtx, pStruct, eValue, pInput);
    EXPECT_EQ(result, 1);

    free(pMember1);
    free(pStruct);
    free(pInput);
    pMember1 = nullptr;
    pStruct = nullptr;
    pInput = nullptr;
}

TEST_F(CcspHomeSecurityHDKDeviceGetValueFixture, HDK_Device_GetValue_WLanEncryption_SUCCESS_2) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WLanEncryption;
    char mockPathVal[] = "Device.WiFi.Radio.1";
    char mockAlias[] = "Radio0";
    char mockApPathVal[] = "Device.WiFi.AccessPoint.3";
    char mockEnabledMode[] = "WPA-Personal";
    char mockEncrytionMethod[] = "TKIP";

    HDK_Struct* pInput = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pInput, nullptr);

    HDK_Member__STRING__* pMember1 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember1, nullptr);

    pMember1->node.element = HDK_Element_PN_RadioID;
    pMember1->node.type = HDK_Type__STRING__;
    pMember1->node.pNext = nullptr;
    pMember1->pszValue = strdup("Radio0");

    pInput->pHead = (HDK_Member*)pMember1;
    pInput->pTail = (HDK_Member*)pMember1;

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    pStruct->pHead = nullptr;
    pStruct->pTail = nullptr;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("Alias"), _, _))
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

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("Security.ModeEnabled"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockEnabledMode, mockEnabledMode + strlen(mockEnabledMode) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("Security.X_CISCO_COM_EncryptionMethod"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockEncrytionMethod, mockEncrytionMethod + strlen(mockEncrytionMethod) + 1),
             Return(0)
    ));

    int result = HDK_Device_GetValue(mockDeviceCtx, pStruct, eValue, pInput);
    EXPECT_EQ(result, 1);

    free(pMember1);
    free(pStruct);
    free(pInput);
    pMember1 = nullptr;
    pStruct = nullptr;
    pInput = nullptr;
}

TEST_F(CcspHomeSecurityHDKDeviceGetValueFixture, HDK_Device_GetValue_WLanEncryption_SUCCESS_3) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WLanEncryption;
    char mockPathVal[] = "Device.WiFi.Radio.1";
    char mockAlias[] = "Radio0";
    char mockApPathVal[] = "Device.WiFi.AccessPoint.3";
    char mockEnabledMode[] = "WPA-Personal";
    char mockEncrytionMethod[] = "AES+TKIP";

    HDK_Struct* pInput = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pInput, nullptr);

    HDK_Member__STRING__* pMember1 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember1, nullptr);

    pMember1->node.element = HDK_Element_PN_RadioID;
    pMember1->node.type = HDK_Type__STRING__;
    pMember1->node.pNext = nullptr;
    pMember1->pszValue = strdup("Radio0");

    pInput->pHead = (HDK_Member*)pMember1;
    pInput->pTail = (HDK_Member*)pMember1;

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    pStruct->pHead = nullptr;
    pStruct->pTail = nullptr;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("Alias"), _, _))
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

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("Security.ModeEnabled"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockEnabledMode, mockEnabledMode + strlen(mockEnabledMode) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("Security.X_CISCO_COM_EncryptionMethod"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockEncrytionMethod, mockEncrytionMethod + strlen(mockEncrytionMethod) + 1),
             Return(0)
    ));

    int result = HDK_Device_GetValue(mockDeviceCtx, pStruct, eValue, pInput);
    EXPECT_EQ(result, 1);

    free(pMember1);
    free(pStruct);
    free(pInput);
    pMember1 = nullptr;
    pStruct = nullptr;
    pInput = nullptr;
}

TEST_F(CcspHomeSecurityHDKDeviceGetValueFixture, HDK_Device_GetValue_WLanEncryption_SUCCESS_4) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WLanEncryption;
    char mockPathVal[] = "Device.WiFi.Radio.1";
    char mockAlias[] = "Radio0";
    char mockApPathVal[] = "Device.WiFi.AccessPoint.3";
    char mockEnabledMode[] = "None";

    HDK_Struct* pInput = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pInput, nullptr);

    HDK_Member__STRING__* pMember1 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember1, nullptr);

    pMember1->node.element = HDK_Element_PN_RadioID;
    pMember1->node.type = HDK_Type__STRING__;
    pMember1->node.pNext = nullptr;
    pMember1->pszValue = strdup("Radio0");

    pInput->pHead = (HDK_Member*)pMember1;
    pInput->pTail = (HDK_Member*)pMember1;

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    pStruct->pHead = nullptr;
    pStruct->pTail = nullptr;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("Alias"), _, _))
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

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("Security.ModeEnabled"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockEnabledMode, mockEnabledMode + strlen(mockEnabledMode) + 1),
             Return(0)
    ));

    int result = HDK_Device_GetValue(mockDeviceCtx, pStruct, eValue, pInput);
    EXPECT_EQ(result, 1);

    free(pMember1);
    free(pStruct);
    free(pInput);
    pMember1 = nullptr;
    pStruct = nullptr;
    pInput = nullptr;
}

TEST_F(CcspHomeSecurityHDKDeviceGetValueFixture, HDK_Device_GetValue_WLanEncryption_FAIL_1) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WLanEncryption;

    HDK_Struct* pInput = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pInput, nullptr);

    HDK_Member__STRING__* pMember1 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember1, nullptr);

    pMember1->node.element = HDK_Element_PN_RadioID;
    pMember1->node.type = HDK_Type__STRING__;
    pMember1->node.pNext = nullptr;
    pMember1->pszValue = strdup("Radio0");

    pInput->pHead = (HDK_Member*)pMember1;
    pInput->pTail = (HDK_Member*)pMember1;

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    pStruct->pHead = nullptr;
    pStruct->pTail = nullptr;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .Times(1).WillOnce(Return(1));

    int result = HDK_Device_GetValue(mockDeviceCtx, pStruct, eValue, pInput);
    EXPECT_EQ(result, 0);

    free(pMember1);
    free(pStruct);
    free(pInput);
    pMember1 = nullptr;
    pStruct = nullptr;
    pInput = nullptr;
}

TEST_F(CcspHomeSecurityHDKDeviceGetValueFixture, HDK_Device_GetValue_WLanEncryption_FAIL_2) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WLanEncryption;
    char mockPathVal[] = "Device.WiFi.Radio.1";
    char mockAlias[] = "Radio1";

    HDK_Struct* pInput = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pInput, nullptr);

    HDK_Member__STRING__* pMember1 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember1, nullptr);

    pMember1->node.element = HDK_Element_PN_RadioID;
    pMember1->node.type = HDK_Type__STRING__;
    pMember1->node.pNext = nullptr;
    pMember1->pszValue = strdup("Radio0");

    pInput->pHead = (HDK_Member*)pMember1;
    pInput->pTail = (HDK_Member*)pMember1;

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    pStruct->pHead = nullptr;
    pStruct->pTail = nullptr;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("Alias"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockAlias, mockAlias + strlen(mockAlias) + 1),
             Return(0)
    ));
    int result = HDK_Device_GetValue(mockDeviceCtx, pStruct, eValue, pInput);
    EXPECT_EQ(result, 0);

    free(pMember1);
    free(pStruct);
    free(pInput);
    pMember1 = nullptr;
    pStruct = nullptr;
    pInput = nullptr;
}

TEST_F(CcspHomeSecurityHDKDeviceGetValueFixture, HDK_Device_GetValue_WLanEncryption_FAIL_3) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WLanEncryption;
    char mockPathVal[] = "Device.WiFi.Radio.1";
    char mockAlias[] = "Radio0";

    HDK_Struct* pInput = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pInput, nullptr);

    HDK_Member__STRING__* pMember1 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember1, nullptr);

    pMember1->node.element = HDK_Element_PN_RadioID;
    pMember1->node.type = HDK_Type__STRING__;
    pMember1->node.pNext = nullptr;
    pMember1->pszValue = strdup("Radio0");

    pInput->pHead = (HDK_Member*)pMember1;
    pInput->pTail = (HDK_Member*)pMember1;

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    pStruct->pHead = nullptr;
    pStruct->pTail = nullptr;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("Alias"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockAlias, mockAlias + strlen(mockAlias) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiAp"), _, _))
    .Times(1).WillOnce(Return(1));

    int result = HDK_Device_GetValue(mockDeviceCtx, pStruct, eValue, pInput);
    EXPECT_EQ(result, 0);

    free(pMember1);
    free(pStruct);
    free(pInput);
    pMember1 = nullptr;
    pStruct = nullptr;
    pInput = nullptr;
}

TEST_F(CcspHomeSecurityHDKDeviceGetValueFixture, HDK_Device_GetValue_WLanRadiusIP1_SUCCESS_1) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WLanRadiusIP1;
    char mockPathVal[] = "Device.WiFi.Radio.1";
    char mockAlias[] = "Radio0";
    char mockApPathVal[] = "Device.WiFi.AccessPoint.3";
    char mockEnabledMode[] = "WPA-Personal";

    HDK_Struct* pInput = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pInput, nullptr);

    HDK_Member__STRING__* pMember1 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember1, nullptr);

    pMember1->node.element = HDK_Element_PN_RadioID;
    pMember1->node.type = HDK_Type__STRING__;
    pMember1->node.pNext = nullptr;
    pMember1->pszValue = strdup("Radio0");

    pInput->pHead = (HDK_Member*)pMember1;
    pInput->pTail = (HDK_Member*)pMember1;

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    pStruct->pHead = nullptr;
    pStruct->pTail = nullptr;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("Alias"), _, _))
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

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("Security.ModeEnabled"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockEnabledMode, mockEnabledMode + strlen(mockEnabledMode) + 1),
             Return(0)
    ));

    int result = HDK_Device_GetValue(mockDeviceCtx, pStruct, eValue, pInput);
    EXPECT_EQ(result, 1);

    free(pMember1);
    free(pStruct);
    free(pInput);
    pMember1 = nullptr;
    pStruct = nullptr;
    pInput = nullptr;
}

TEST_F(CcspHomeSecurityHDKDeviceGetValueFixture, HDK_Device_GetValue_WLanRadiusIP1_SUCCESS_2) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WLanRadiusIP1;
    char mockPathVal[] = "Device.WiFi.Radio.1";
    char mockAlias[] = "Radio0";
    char mockApPathVal[] = "Device.WiFi.AccessPoint.3";
    char mockEnabledMode[] = "WPA-Enterprise";
    char mockIP[] = "172.16.12.1";
    char mockPort[] = "8080";
    char mockSecret[] = "test1234";

    HDK_Struct* pInput = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pInput, nullptr);

    HDK_Member__STRING__* pMember1 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember1, nullptr);

    pMember1->node.element = HDK_Element_PN_RadioID;
    pMember1->node.type = HDK_Type__STRING__;
    pMember1->node.pNext = nullptr;
    pMember1->pszValue = strdup("Radio0");

    pInput->pHead = (HDK_Member*)pMember1;
    pInput->pTail = (HDK_Member*)pMember1;

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    pStruct->pHead = nullptr;
    pStruct->pTail = nullptr;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("Alias"), _, _))
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

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("Security.ModeEnabled"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockEnabledMode, mockEnabledMode + strlen(mockEnabledMode) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("Security.RadiusServerIPAddr"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockIP, mockIP + strlen(mockIP) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("Security.RadiusServerPort"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPort, mockPort + strlen(mockPort) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("Security.RadiusSecret"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockSecret, mockSecret + strlen(mockSecret) + 1),
             Return(0)
    ));

    int result = HDK_Device_GetValue(mockDeviceCtx, pStruct, eValue, pInput);
    EXPECT_EQ(result, 1);

    free(pMember1);
    free(pStruct);
    free(pInput);
    pMember1 = nullptr;
    pStruct = nullptr;
    pInput = nullptr;
}

TEST_F(CcspHomeSecurityHDKDeviceGetValueFixture, HDK_Device_GetValue_WLanRadiusIP1_FAIL) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WLanRadiusIP1;

    HDK_Struct* pInput = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pInput, nullptr);

    HDK_Member__STRING__* pMember1 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember1, nullptr);

    pMember1->node.element = HDK_Element_PN_RadioID;
    pMember1->node.type = HDK_Type__STRING__;
    pMember1->node.pNext = nullptr;
    pMember1->pszValue = strdup("Radio0");

    pInput->pHead = (HDK_Member*)pMember1;
    pInput->pTail = (HDK_Member*)pMember1;

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    pStruct->pHead = nullptr;
    pStruct->pTail = nullptr;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .Times(1).WillOnce(Return(1));

    int result = HDK_Device_GetValue(mockDeviceCtx, pStruct, eValue, pInput);
    EXPECT_EQ(result, 0);

    free(pMember1);
    free(pStruct);
    free(pInput);
    pMember1 = nullptr;
    pStruct = nullptr;
    pInput = nullptr;
}

TEST_F(CcspHomeSecurityHDKDeviceGetValueFixture, HDK_Device_GetValue_WLanRadiusPort1_FAIL) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WLanRadiusPort1;
    char mockPathVal[] = "Device.WiFi.Radio.1";
    char mockAlias[] = "Radio1";

    HDK_Struct* pInput = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pInput, nullptr);

    HDK_Member__STRING__* pMember1 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember1, nullptr);

    pMember1->node.element = HDK_Element_PN_RadioID;
    pMember1->node.type = HDK_Type__STRING__;
    pMember1->node.pNext = nullptr;
    pMember1->pszValue = strdup("Radio0");

    pInput->pHead = (HDK_Member*)pMember1;
    pInput->pTail = (HDK_Member*)pMember1;

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    pStruct->pHead = nullptr;
    pStruct->pTail = nullptr;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("Alias"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockAlias, mockAlias + strlen(mockAlias) + 1),
             Return(0)
    ));
    int result = HDK_Device_GetValue(mockDeviceCtx, pStruct, eValue, pInput);
    EXPECT_EQ(result, 0);

    free(pMember1);
    free(pStruct);
    free(pInput);
    pMember1 = nullptr;
    pStruct = nullptr;
    pInput = nullptr;
}

TEST_F(CcspHomeSecurityHDKDeviceGetValueFixture, HDK_Device_GetValue_WLanRadiusSecret1_FAIL) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WLanRadiusSecret1;
    char mockPathVal[] = "Device.WiFi.Radio.1";
    char mockAlias[] = "Radio0";

    HDK_Struct* pInput = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pInput, nullptr);

    HDK_Member__STRING__* pMember1 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember1, nullptr);

    pMember1->node.element = HDK_Element_PN_RadioID;
    pMember1->node.type = HDK_Type__STRING__;
    pMember1->node.pNext = nullptr;
    pMember1->pszValue = strdup("Radio0");

    pInput->pHead = (HDK_Member*)pMember1;
    pInput->pTail = (HDK_Member*)pMember1;

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    pStruct->pHead = nullptr;
    pStruct->pTail = nullptr;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("Alias"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockAlias, mockAlias + strlen(mockAlias) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiAp"), _, _))
    .Times(1).WillOnce(Return(1));

    int result = HDK_Device_GetValue(mockDeviceCtx, pStruct, eValue, pInput);
    EXPECT_EQ(result, 0);

    free(pMember1);
    free(pStruct);
    free(pInput);
    pMember1 = nullptr;
    pStruct = nullptr;
    pInput = nullptr;
}

TEST_F(CcspHomeSecurityHDKDeviceGetValueFixture, HDK_Device_GetValue_WLanEnabled_SUCCESS_1) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WLanEnabled;
    char mockPathVal[] = "Device.WiFi.Radio.1";
    char mockAlias[] = "Radio0";
    char mockVal[] = "true";

    HDK_Struct* pInput = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pInput, nullptr);

    HDK_Member__STRING__* pMember1 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember1, nullptr);

    pMember1->node.element = HDK_Element_PN_RadioID;
    pMember1->node.type = HDK_Type__STRING__;
    pMember1->node.pNext = nullptr;
    pMember1->pszValue = strdup("Radio0");

    pInput->pHead = (HDK_Member*)pMember1;
    pInput->pTail = (HDK_Member*)pMember1;

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    pStruct->pHead = nullptr;
    pStruct->pTail = nullptr;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_FindObjectIns(_, _, _, _, _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
        testing::Invoke([&](MBusObj_t *, const char *, const char *, const char *, char insPath[][MAX_PATH_NAME], int *insNum) {
            strcpy(insPath[0], "Device.WiFi.Radio.1.");
            *insNum = 1;
        }),
        Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("Alias"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockAlias, mockAlias + strlen(mockAlias) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("Enable"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockVal, mockVal + strlen(mockVal) + 1),
             Return(0)
    ));

    int result = HDK_Device_GetValue(mockDeviceCtx, pStruct, eValue, pInput);
    EXPECT_EQ(result, 1);

    free(pMember1);
    free(pStruct);
    free(pInput);
    pMember1 = nullptr;
    pStruct = nullptr;
    pInput = nullptr;
}

TEST_F(CcspHomeSecurityHDKDeviceGetValueFixture, HDK_Device_GetValue_WLanEnabled_SUCCESS_2) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WLanEnabled;
    char mockPathVal[] = "Device.WiFi.Radio.1";
    char mockAlias[] = "Radio0";
    char mockVal[] = "false";

    HDK_Struct* pInput = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pInput, nullptr);

    HDK_Member__STRING__* pMember1 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember1, nullptr);

    pMember1->node.element = HDK_Element_PN_RadioID;
    pMember1->node.type = HDK_Type__STRING__;
    pMember1->node.pNext = nullptr;
    pMember1->pszValue = strdup("Radio0");

    pInput->pHead = (HDK_Member*)pMember1;
    pInput->pTail = (HDK_Member*)pMember1;

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    pStruct->pHead = nullptr;
    pStruct->pTail = nullptr;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_FindObjectIns(_, _, _, _, _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
        testing::Invoke([&](MBusObj_t *, const char *, const char *, const char *, char insPath[][MAX_PATH_NAME], int *insNum) {
            strcpy(insPath[0], "Device.WiFi.Radio.1.");
            *insNum = 1;
        }),
        Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("Alias"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockAlias, mockAlias + strlen(mockAlias) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("Enable"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockVal, mockVal + strlen(mockVal) + 1),
             Return(0)
    ));

    int result = HDK_Device_GetValue(mockDeviceCtx, pStruct, eValue, pInput);
    EXPECT_EQ(result, 1);

    free(pMember1);
    free(pStruct);
    free(pInput);
    pMember1 = nullptr;
    pStruct = nullptr;
    pInput = nullptr;
}

TEST_F(CcspHomeSecurityHDKDeviceGetValueFixture, HDK_Device_GetValue_WLanEnabled_FAIL_1) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WLanEnabled;

    HDK_Struct* pInput = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pInput, nullptr);

    HDK_Member__STRING__* pMember1 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember1, nullptr);

    pMember1->node.element = HDK_Element_PN_RadioID;
    pMember1->node.type = HDK_Type__STRING__;
    pMember1->node.pNext = nullptr;
    pMember1->pszValue = strdup("Radio0");

    pInput->pHead = (HDK_Member*)pMember1;
    pInput->pTail = (HDK_Member*)pMember1;

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    pStruct->pHead = nullptr;
    pStruct->pTail = nullptr;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_FindObjectIns(_, _, _, _, _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
        testing::Invoke([&](MBusObj_t *, const char *, const char *, const char *, char insPath[][MAX_PATH_NAME], int *insNum) {
            strcpy(insPath[0], "Device.WiFi.Radio.1.");
            *insNum = 1;
        }),
        Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .Times(1).WillOnce(Return(1));

    int result = HDK_Device_GetValue(mockDeviceCtx, pStruct, eValue, pInput);
    EXPECT_EQ(result, 0);

    free(pMember1);
    free(pStruct);
    free(pInput);
    pMember1 = nullptr;
    pStruct = nullptr;
    pInput = nullptr;
}

TEST_F(CcspHomeSecurityHDKDeviceGetValueFixture, HDK_Device_GetValue_WLanEnabled_FAIL_2) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WLanEnabled;
    char mockPathVal[] = "Device.WiFi.Radio.1";
    char mockAlias[] = "Radio1";

    HDK_Struct* pInput = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pInput, nullptr);

    HDK_Member__STRING__* pMember1 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember1, nullptr);

    pMember1->node.element = HDK_Element_PN_RadioID;
    pMember1->node.type = HDK_Type__STRING__;
    pMember1->node.pNext = nullptr;
    pMember1->pszValue = strdup("Radio0");

    pInput->pHead = (HDK_Member*)pMember1;
    pInput->pTail = (HDK_Member*)pMember1;

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    pStruct->pHead = nullptr;
    pStruct->pTail = nullptr;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_FindObjectIns(_, _, _, _, _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
        testing::Invoke([&](MBusObj_t *, const char *, const char *, const char *, char insPath[][MAX_PATH_NAME], int *insNum) {
            strcpy(insPath[0], "Device.WiFi.Radio.1.");
            *insNum = 1;
        }),
        Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("Alias"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockAlias, mockAlias + strlen(mockAlias) + 1),
             Return(0)
    ));
    int result = HDK_Device_GetValue(mockDeviceCtx, pStruct, eValue, pInput);
    EXPECT_EQ(result, 0);

    free(pMember1);
    free(pStruct);
    free(pInput);
    pMember1 = nullptr;
    pStruct = nullptr;
    pInput = nullptr;
}

TEST_F(CcspHomeSecurityHDKDeviceGetValueFixture, HDK_Device_GetValue_WLanMode_SUCCESS_1) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WLanMode;
    char mockPathVal[] = "Device.WiFi.Radio.1";
    char mockAlias[] = "Radio0";
    char mockVal[] = "true";
    char mockOpStds[] = "a";

    HDK_Struct* pInput = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pInput, nullptr);

    HDK_Member__STRING__* pMember1 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember1, nullptr);

    pMember1->node.element = HDK_Element_PN_RadioID;
    pMember1->node.type = HDK_Type__STRING__;
    pMember1->node.pNext = nullptr;
    pMember1->pszValue = strdup("Radio0");

    pInput->pHead = (HDK_Member*)pMember1;
    pInput->pTail = (HDK_Member*)pMember1;

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    pStruct->pHead = nullptr;
    pStruct->pTail = nullptr;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_FindObjectIns(_, _, _, _, _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
        testing::Invoke([&](MBusObj_t *, const char *, const char *, const char *, char insPath[][MAX_PATH_NAME], int *insNum) {
            strcpy(insPath[0], "Device.WiFi.Radio.1.");
            *insNum = 1;
        }),
        Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("Alias"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockAlias, mockAlias + strlen(mockAlias) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("OperatingStandards"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockOpStds, mockOpStds + strlen(mockOpStds) + 1),
             Return(0)
    ));

    int result = HDK_Device_GetValue(mockDeviceCtx, pStruct, eValue, pInput);
    EXPECT_EQ(result, 1);

    free(pMember1);
    free(pStruct);
    free(pInput);
    pMember1 = nullptr;
    pStruct = nullptr;
    pInput = nullptr;
}

TEST_F(CcspHomeSecurityHDKDeviceGetValueFixture, HDK_Device_GetValue_WLanMode_SUCCESS_2) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WLanMode;
    char mockPathVal[] = "Device.WiFi.Radio.1";
    char mockAlias[] = "Radio0";
    char mockVal[] = "true";
    char mockOpStds[] = "b";

    HDK_Struct* pInput = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pInput, nullptr);

    HDK_Member__STRING__* pMember1 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember1, nullptr);

    pMember1->node.element = HDK_Element_PN_RadioID;
    pMember1->node.type = HDK_Type__STRING__;
    pMember1->node.pNext = nullptr;
    pMember1->pszValue = strdup("Radio0");

    pInput->pHead = (HDK_Member*)pMember1;
    pInput->pTail = (HDK_Member*)pMember1;

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    pStruct->pHead = nullptr;
    pStruct->pTail = nullptr;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_FindObjectIns(_, _, _, _, _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
        testing::Invoke([&](MBusObj_t *, const char *, const char *, const char *, char insPath[][MAX_PATH_NAME], int *insNum) {
            strcpy(insPath[0], "Device.WiFi.Radio.1.");
            *insNum = 1;
        }),
        Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("Alias"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockAlias, mockAlias + strlen(mockAlias) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("OperatingStandards"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockOpStds, mockOpStds + strlen(mockOpStds) + 1),
             Return(0)
    ));

    int result = HDK_Device_GetValue(mockDeviceCtx, pStruct, eValue, pInput);
    EXPECT_EQ(result, 1);

    free(pMember1);
    free(pStruct);
    free(pInput);
    pMember1 = nullptr;
    pStruct = nullptr;
    pInput = nullptr;
}

TEST_F(CcspHomeSecurityHDKDeviceGetValueFixture, HDK_Device_GetValue_WLanMode_SUCCESS_3) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WLanMode;
    char mockPathVal[] = "Device.WiFi.Radio.1";
    char mockAlias[] = "Radio0";
    char mockVal[] = "true";
    char mockOpStds[] = "g";

    HDK_Struct* pInput = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pInput, nullptr);

    HDK_Member__STRING__* pMember1 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember1, nullptr);

    pMember1->node.element = HDK_Element_PN_RadioID;
    pMember1->node.type = HDK_Type__STRING__;
    pMember1->node.pNext = nullptr;
    pMember1->pszValue = strdup("Radio0");

    pInput->pHead = (HDK_Member*)pMember1;
    pInput->pTail = (HDK_Member*)pMember1;

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    pStruct->pHead = nullptr;
    pStruct->pTail = nullptr;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_FindObjectIns(_, _, _, _, _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
        testing::Invoke([&](MBusObj_t *, const char *, const char *, const char *, char insPath[][MAX_PATH_NAME], int *insNum) {
            strcpy(insPath[0], "Device.WiFi.Radio.1.");
            *insNum = 1;
        }),
        Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("Alias"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockAlias, mockAlias + strlen(mockAlias) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("OperatingStandards"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockOpStds, mockOpStds + strlen(mockOpStds) + 1),
             Return(0)
    ));

    int result = HDK_Device_GetValue(mockDeviceCtx, pStruct, eValue, pInput);
    EXPECT_EQ(result, 1);

    free(pMember1);
    free(pStruct);
    free(pInput);
    pMember1 = nullptr;
    pStruct = nullptr;
    pInput = nullptr;
}

TEST_F(CcspHomeSecurityHDKDeviceGetValueFixture, HDK_Device_GetValue_WLanMode_SUCCESS_4) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WLanMode;
    char mockPathVal[] = "Device.WiFi.Radio.1";
    char mockAlias[] = "Radio0";
    char mockVal[] = "true";
    char mockOpStds[] = "n";

    HDK_Struct* pInput = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pInput, nullptr);

    HDK_Member__STRING__* pMember1 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember1, nullptr);

    pMember1->node.element = HDK_Element_PN_RadioID;
    pMember1->node.type = HDK_Type__STRING__;
    pMember1->node.pNext = nullptr;
    pMember1->pszValue = strdup("Radio0");

    pInput->pHead = (HDK_Member*)pMember1;
    pInput->pTail = (HDK_Member*)pMember1;

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    pStruct->pHead = nullptr;
    pStruct->pTail = nullptr;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_FindObjectIns(_, _, _, _, _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
        testing::Invoke([&](MBusObj_t *, const char *, const char *, const char *, char insPath[][MAX_PATH_NAME], int *insNum) {
            strcpy(insPath[0], "Device.WiFi.Radio.1.");
            *insNum = 1;
        }),
        Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("Alias"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockAlias, mockAlias + strlen(mockAlias) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("OperatingStandards"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockOpStds, mockOpStds + strlen(mockOpStds) + 1),
             Return(0)
    ));

    int result = HDK_Device_GetValue(mockDeviceCtx, pStruct, eValue, pInput);
    EXPECT_EQ(result, 1);

    free(pMember1);
    free(pStruct);
    free(pInput);
    pMember1 = nullptr;
    pStruct = nullptr;
    pInput = nullptr;
}

TEST_F(CcspHomeSecurityHDKDeviceGetValueFixture, HDK_Device_GetValue_WLanMode_SUCCESS_5) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WLanMode;
    char mockPathVal[] = "Device.WiFi.Radio.1";
    char mockAlias[] = "Radio0";
    char mockVal[] = "true";
    char mockOpStds[] = "n,a";

    HDK_Struct* pInput = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pInput, nullptr);

    HDK_Member__STRING__* pMember1 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember1, nullptr);

    pMember1->node.element = HDK_Element_PN_RadioID;
    pMember1->node.type = HDK_Type__STRING__;
    pMember1->node.pNext = nullptr;
    pMember1->pszValue = strdup("Radio0");

    pInput->pHead = (HDK_Member*)pMember1;
    pInput->pTail = (HDK_Member*)pMember1;

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    pStruct->pHead = nullptr;
    pStruct->pTail = nullptr;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_FindObjectIns(_, _, _, _, _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
        testing::Invoke([&](MBusObj_t *, const char *, const char *, const char *, char insPath[][MAX_PATH_NAME], int *insNum) {
            strcpy(insPath[0], "Device.WiFi.Radio.1.");
            *insNum = 1;
        }),
        Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("Alias"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockAlias, mockAlias + strlen(mockAlias) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("OperatingStandards"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockOpStds, mockOpStds + strlen(mockOpStds) + 1),
             Return(0)
    ));

    int result = HDK_Device_GetValue(mockDeviceCtx, pStruct, eValue, pInput);
    EXPECT_EQ(result, 1);

    free(pMember1);
    free(pStruct);
    free(pInput);
    pMember1 = nullptr;
    pStruct = nullptr;
    pInput = nullptr;
}

TEST_F(CcspHomeSecurityHDKDeviceGetValueFixture, HDK_Device_GetValue_WLanMode_SUCCESS_6) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WLanMode;
    char mockPathVal[] = "Device.WiFi.Radio.1";
    char mockAlias[] = "Radio0";
    char mockVal[] = "true";
    char mockOpStds[] = "g,n";

    HDK_Struct* pInput = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pInput, nullptr);

    HDK_Member__STRING__* pMember1 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember1, nullptr);

    pMember1->node.element = HDK_Element_PN_RadioID;
    pMember1->node.type = HDK_Type__STRING__;
    pMember1->node.pNext = nullptr;
    pMember1->pszValue = strdup("Radio0");

    pInput->pHead = (HDK_Member*)pMember1;
    pInput->pTail = (HDK_Member*)pMember1;

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    pStruct->pHead = nullptr;
    pStruct->pTail = nullptr;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_FindObjectIns(_, _, _, _, _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
        testing::Invoke([&](MBusObj_t *, const char *, const char *, const char *, char insPath[][MAX_PATH_NAME], int *insNum) {
            strcpy(insPath[0], "Device.WiFi.Radio.1.");
            *insNum = 1;
        }),
        Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("Alias"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockAlias, mockAlias + strlen(mockAlias) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("OperatingStandards"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockOpStds, mockOpStds + strlen(mockOpStds) + 1),
             Return(0)
    ));

    int result = HDK_Device_GetValue(mockDeviceCtx, pStruct, eValue, pInput);
    EXPECT_EQ(result, 1);

    free(pMember1);
    free(pStruct);
    free(pInput);
    pMember1 = nullptr;
    pStruct = nullptr;
    pInput = nullptr;
}

TEST_F(CcspHomeSecurityHDKDeviceGetValueFixture, HDK_Device_GetValue_WLanMode_SUCCESS_7) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WLanMode;
    char mockPathVal[] = "Device.WiFi.Radio.1";
    char mockAlias[] = "Radio0";
    char mockVal[] = "true";
    char mockOpStds[] = "b,g,n";

    HDK_Struct* pInput = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pInput, nullptr);

    HDK_Member__STRING__* pMember1 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember1, nullptr);

    pMember1->node.element = HDK_Element_PN_RadioID;
    pMember1->node.type = HDK_Type__STRING__;
    pMember1->node.pNext = nullptr;
    pMember1->pszValue = strdup("Radio0");

    pInput->pHead = (HDK_Member*)pMember1;
    pInput->pTail = (HDK_Member*)pMember1;

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    pStruct->pHead = nullptr;
    pStruct->pTail = nullptr;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_FindObjectIns(_, _, _, _, _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
        testing::Invoke([&](MBusObj_t *, const char *, const char *, const char *, char insPath[][MAX_PATH_NAME], int *insNum) {
            strcpy(insPath[0], "Device.WiFi.Radio.1.");
            *insNum = 1;
        }),
        Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("Alias"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockAlias, mockAlias + strlen(mockAlias) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("OperatingStandards"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockOpStds, mockOpStds + strlen(mockOpStds) + 1),
             Return(0)
    ));

    int result = HDK_Device_GetValue(mockDeviceCtx, pStruct, eValue, pInput);
    EXPECT_EQ(result, 1);

    free(pMember1);
    free(pStruct);
    free(pInput);
    pMember1 = nullptr;
    pStruct = nullptr;
    pInput = nullptr;
}

TEST_F(CcspHomeSecurityHDKDeviceGetValueFixture, HDK_Device_GetValue_WLanMode_SUCCESS_8) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WLanMode;
    char mockPathVal[] = "Device.WiFi.Radio.1";
    char mockAlias[] = "Radio0";
    char mockVal[] = "true";
    char mockOpStds[] = "n,b";

    HDK_Struct* pInput = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pInput, nullptr);

    HDK_Member__STRING__* pMember1 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember1, nullptr);

    pMember1->node.element = HDK_Element_PN_RadioID;
    pMember1->node.type = HDK_Type__STRING__;
    pMember1->node.pNext = nullptr;
    pMember1->pszValue = strdup("Radio0");

    pInput->pHead = (HDK_Member*)pMember1;
    pInput->pTail = (HDK_Member*)pMember1;

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    pStruct->pHead = nullptr;
    pStruct->pTail = nullptr;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_FindObjectIns(_, _, _, _, _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
        testing::Invoke([&](MBusObj_t *, const char *, const char *, const char *, char insPath[][MAX_PATH_NAME], int *insNum) {
            strcpy(insPath[0], "Device.WiFi.Radio.1.");
            *insNum = 1;
        }),
        Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("Alias"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockAlias, mockAlias + strlen(mockAlias) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("OperatingStandards"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockOpStds, mockOpStds + strlen(mockOpStds) + 1),
             Return(0)
    ));

    int result = HDK_Device_GetValue(mockDeviceCtx, pStruct, eValue, pInput);
    EXPECT_EQ(result, 1);

    free(pMember1);
    free(pStruct);
    free(pInput);
    pMember1 = nullptr;
    pStruct = nullptr;
    pInput = nullptr;
}

TEST_F(CcspHomeSecurityHDKDeviceGetValueFixture, HDK_Device_GetValue_WLanMode_SUCCESS_9) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WLanMode;
    char mockPathVal[] = "Device.WiFi.Radio.1";
    char mockAlias[] = "Radio0";
    char mockVal[] = "true";
    char mockOpStds[] = "g,b";

    HDK_Struct* pInput = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pInput, nullptr);

    HDK_Member__STRING__* pMember1 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember1, nullptr);

    pMember1->node.element = HDK_Element_PN_RadioID;
    pMember1->node.type = HDK_Type__STRING__;
    pMember1->node.pNext = nullptr;
    pMember1->pszValue = strdup("Radio0");

    pInput->pHead = (HDK_Member*)pMember1;
    pInput->pTail = (HDK_Member*)pMember1;

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    pStruct->pHead = nullptr;
    pStruct->pTail = nullptr;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_FindObjectIns(_, _, _, _, _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
        testing::Invoke([&](MBusObj_t *, const char *, const char *, const char *, char insPath[][MAX_PATH_NAME], int *insNum) {
            strcpy(insPath[0], "Device.WiFi.Radio.1.");
            *insNum = 1;
        }),
        Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("Alias"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockAlias, mockAlias + strlen(mockAlias) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("OperatingStandards"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockOpStds, mockOpStds + strlen(mockOpStds) + 1),
             Return(0)
    ));

    int result = HDK_Device_GetValue(mockDeviceCtx, pStruct, eValue, pInput);
    EXPECT_EQ(result, 1);

    free(pMember1);
    free(pStruct);
    free(pInput);
    pMember1 = nullptr;
    pStruct = nullptr;
    pInput = nullptr;
}

TEST_F(CcspHomeSecurityHDKDeviceGetValueFixture, HDK_Device_GetValue_WLanMode_SUCCESS_10) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WLanMode;
    char mockPathVal[] = "Device.WiFi.Radio.1";
    char mockAlias[] = "Radio0";
    char mockVal[] = "true";
    char mockOpStds[] = "g,n,ax";

    HDK_Struct* pInput = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pInput, nullptr);

    HDK_Member__STRING__* pMember1 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember1, nullptr);

    pMember1->node.element = HDK_Element_PN_RadioID;
    pMember1->node.type = HDK_Type__STRING__;
    pMember1->node.pNext = nullptr;
    pMember1->pszValue = strdup("Radio0");

    pInput->pHead = (HDK_Member*)pMember1;
    pInput->pTail = (HDK_Member*)pMember1;

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    pStruct->pHead = nullptr;
    pStruct->pTail = nullptr;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_FindObjectIns(_, _, _, _, _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
        testing::Invoke([&](MBusObj_t *, const char *, const char *, const char *, char insPath[][MAX_PATH_NAME], int *insNum) {
            strcpy(insPath[0], "Device.WiFi.Radio.1.");
            *insNum = 1;
        }),
        Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("Alias"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockAlias, mockAlias + strlen(mockAlias) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("OperatingStandards"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockOpStds, mockOpStds + strlen(mockOpStds) + 1),
             Return(0)
    ));

    int result = HDK_Device_GetValue(mockDeviceCtx, pStruct, eValue, pInput);
    EXPECT_EQ(result, 1);

    free(pMember1);
    free(pStruct);
    free(pInput);
    pMember1 = nullptr;
    pStruct = nullptr;
    pInput = nullptr;
}

TEST_F(CcspHomeSecurityHDKDeviceGetValueFixture, HDK_Device_GetValue_WLanMode_FAIL_1) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WLanMode;

    HDK_Struct* pInput = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pInput, nullptr);

    HDK_Member__STRING__* pMember1 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember1, nullptr);

    pMember1->node.element = HDK_Element_PN_RadioID;
    pMember1->node.type = HDK_Type__STRING__;
    pMember1->node.pNext = nullptr;
    pMember1->pszValue = strdup("Radio0");

    pInput->pHead = (HDK_Member*)pMember1;
    pInput->pTail = (HDK_Member*)pMember1;

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    pStruct->pHead = nullptr;
    pStruct->pTail = nullptr;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_FindObjectIns(_, _, _, _, _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
        testing::Invoke([&](MBusObj_t *, const char *, const char *, const char *, char insPath[][MAX_PATH_NAME], int *insNum) {
            strcpy(insPath[0], "Device.WiFi.Radio.1.");
            *insNum = 1;
        }),
        Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .Times(1).WillOnce(Return(1));

    int result = HDK_Device_GetValue(mockDeviceCtx, pStruct, eValue, pInput);
    EXPECT_EQ(result, 0);

    free(pMember1);
    free(pStruct);
    free(pInput);
    pMember1 = nullptr;
    pStruct = nullptr;
    pInput = nullptr;
}

TEST_F(CcspHomeSecurityHDKDeviceGetValueFixture, HDK_Device_GetValue_WLanMode_FAIL_2) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WLanMode;
    char mockPathVal[] = "Device.WiFi.Radio.1";
    char mockAlias[] = "Radio1";

    HDK_Struct* pInput = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pInput, nullptr);

    HDK_Member__STRING__* pMember1 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember1, nullptr);

    pMember1->node.element = HDK_Element_PN_RadioID;
    pMember1->node.type = HDK_Type__STRING__;
    pMember1->node.pNext = nullptr;
    pMember1->pszValue = strdup("Radio0");

    pInput->pHead = (HDK_Member*)pMember1;
    pInput->pTail = (HDK_Member*)pMember1;

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    pStruct->pHead = nullptr;
    pStruct->pTail = nullptr;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_FindObjectIns(_, _, _, _, _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
        testing::Invoke([&](MBusObj_t *, const char *, const char *, const char *, char insPath[][MAX_PATH_NAME], int *insNum) {
            strcpy(insPath[0], "Device.WiFi.Radio.1.");
            *insNum = 1;
        }),
        Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("Alias"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockAlias, mockAlias + strlen(mockAlias) + 1),
             Return(0)
    ));
    int result = HDK_Device_GetValue(mockDeviceCtx, pStruct, eValue, pInput);
    EXPECT_EQ(result, 0);

    free(pMember1);
    free(pStruct);
    free(pInput);
    pMember1 = nullptr;
    pStruct = nullptr;
    pInput = nullptr;
}

TEST_F(CcspHomeSecurityHDKDeviceGetValueFixture, HDK_Device_GetValue_WANMacAddress_SUCCESS) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WANMacAddress;
    char mockMAC[] = "00:00:00:00:00:00";

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    pStruct->pHead = nullptr;
    pStruct->pTail = nullptr;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.DeviceInfo.X_CISCO_COM_BaseMacAddress"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockMAC, mockMAC + strlen(mockMAC) + 1),
             Return(0)
    ));

    int result = HDK_Device_GetValue(mockDeviceCtx, pStruct, eValue, pStruct);
    EXPECT_EQ(result, 1);

    free(pStruct);
    pStruct = nullptr;
}

TEST_F(CcspHomeSecurityHDKDeviceGetValueFixture, HDK_Device_GetValue_MacAddress_SUCCESS) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_MacAddress;
    char mockPathVal[] = "Device.WiFi.Radio.1";
    char mockAlias[] = "Radio0";
    char mockMAC[] = "00:00:00:00:00:00";

    HDK_Struct* pInput = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pInput, nullptr);

    HDK_Member__STRING__* pMember1 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember1, nullptr);

    pMember1->node.element = HDK_Element_PN_RadioID;
    pMember1->node.type = HDK_Type__STRING__;
    pMember1->node.pNext = nullptr;
    pMember1->pszValue = strdup("Radio0");

    pInput->pHead = (HDK_Member*)pMember1;
    pInput->pTail = (HDK_Member*)pMember1;

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    pStruct->pHead = nullptr;
    pStruct->pTail = nullptr;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_FindObjectIns(_, _, _, _, _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
        testing::Invoke([&](MBusObj_t *, const char *, const char *, const char *, char insPath[][MAX_PATH_NAME], int *insNum) {
            strcpy(insPath[0], "Device.WiFi.Radio.1.");
            *insNum = 1;
        }),
        Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("Alias"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockAlias, mockAlias + strlen(mockAlias) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("MACAddress"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockMAC, mockMAC + strlen(mockMAC) + 1),
             Return(0)
    ));

    int result = HDK_Device_GetValue(mockDeviceCtx, pStruct, eValue, pInput);
    EXPECT_EQ(result, 1);

    free(pMember1);
    free(pStruct);
    free(pInput);
    pMember1 = nullptr;
    pStruct = nullptr;
    pInput = nullptr;
}

TEST_F(CcspHomeSecurityHDKDeviceGetValueFixture, HDK_Device_GetValue_MacAddress_FAIL_1) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_MacAddress;
    char mockPathVal[] = "Device.WiFi.Radio.1";

    HDK_Struct* pInput = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pInput, nullptr);

    HDK_Member__STRING__* pMember1 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember1, nullptr);

    pMember1->node.element = HDK_Element_PN_RadioID;
    pMember1->node.type = HDK_Type__STRING__;
    pMember1->node.pNext = nullptr;
    pMember1->pszValue = strdup("Radio0");

    pInput->pHead = (HDK_Member*)pMember1;
    pInput->pTail = (HDK_Member*)pMember1;

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    pStruct->pHead = nullptr;
    pStruct->pTail = nullptr;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_FindObjectIns(_, _, _, _, _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
        testing::Invoke([&](MBusObj_t *, const char *, const char *, const char *, char insPath[][MAX_PATH_NAME], int *insNum) {
            strcpy(insPath[0], "Device.WiFi.Radio.1.");
            *insNum = 1;
        }),
        Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .Times(1).WillOnce(Return(1));

    int result = HDK_Device_GetValue(mockDeviceCtx, pStruct, eValue, pInput);
    EXPECT_EQ(result, 0);

    free(pMember1);
    free(pStruct);
    free(pInput);
    pMember1 = nullptr;
    pStruct = nullptr;
    pInput = nullptr;
}

TEST_F(CcspHomeSecurityHDKDeviceGetValueFixture, HDK_Device_GetValue_MacAddress_FAIL_2) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_MacAddress;
    char mockPathVal[] = "Device.WiFi.Radio.1";
    char mockAlias[] = "Radio1";
    char mockMAC[] = "00:00:00:00:00:00";

    HDK_Struct* pInput = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pInput, nullptr);

    HDK_Member__STRING__* pMember1 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember1, nullptr);

    pMember1->node.element = HDK_Element_PN_RadioID;
    pMember1->node.type = HDK_Type__STRING__;
    pMember1->node.pNext = nullptr;
    pMember1->pszValue = strdup("Radio0");

    pInput->pHead = (HDK_Member*)pMember1;
    pInput->pTail = (HDK_Member*)pMember1;

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    pStruct->pHead = nullptr;
    pStruct->pTail = nullptr;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_FindObjectIns(_, _, _, _, _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
        testing::Invoke([&](MBusObj_t *, const char *, const char *, const char *, char insPath[][MAX_PATH_NAME], int *insNum) {
            strcpy(insPath[0], "Device.WiFi.Radio.1.");
            *insNum = 1;
        }),
        Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("Alias"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockAlias, mockAlias + strlen(mockAlias) + 1),
             Return(0)
    ));

    int result = HDK_Device_GetValue(mockDeviceCtx, pStruct, eValue, pInput);
    EXPECT_EQ(result, 0);

    free(pMember1);
    free(pStruct);
    free(pInput);
    pMember1 = nullptr;
    pStruct = nullptr;
    pInput = nullptr;
}

TEST_F(CcspHomeSecurityHDKDeviceGetValueFixture, HDK_Device_GetValue_WLanSSID_SUCCESS) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WLanSSID;
    char mockPathVal[] = "Device.WiFi.Radio.1";
    char mockAlias[] = "Radio0";
    char mockSSID[] = "test_SSID";

    HDK_Struct* pInput = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pInput, nullptr);

    HDK_Member__STRING__* pMember1 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember1, nullptr);

    pMember1->node.element = HDK_Element_PN_RadioID;
    pMember1->node.type = HDK_Type__STRING__;
    pMember1->node.pNext = nullptr;
    pMember1->pszValue = strdup("Radio0");

    pInput->pHead = (HDK_Member*)pMember1;
    pInput->pTail = (HDK_Member*)pMember1;

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    pStruct->pHead = nullptr;
    pStruct->pTail = nullptr;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_FindObjectIns(_, _, _, _, _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
        testing::Invoke([&](MBusObj_t *, const char *, const char *, const char *, char insPath[][MAX_PATH_NAME], int *insNum) {
            strcpy(insPath[0], "Device.WiFi.Radio.1.");
            *insNum = 1;
        }),
        Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("Alias"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockAlias, mockAlias + strlen(mockAlias) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("SSID"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockSSID, mockSSID + strlen(mockSSID) + 1),
             Return(0)
    ));

    int result = HDK_Device_GetValue(mockDeviceCtx, pStruct, eValue, pInput);
    EXPECT_EQ(result, 1);

    free(pMember1);
    free(pStruct);
    free(pInput);
    pMember1 = nullptr;
    pStruct = nullptr;
    pInput = nullptr;
}

TEST_F(CcspHomeSecurityHDKDeviceGetValueFixture, HDK_Device_GetValue_WLanSSID_FAIL_1) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WLanSSID;
    char mockPathVal[] = "Device.WiFi.Radio.1";

    HDK_Struct* pInput = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pInput, nullptr);

    HDK_Member__STRING__* pMember1 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember1, nullptr);

    pMember1->node.element = HDK_Element_PN_RadioID;
    pMember1->node.type = HDK_Type__STRING__;
    pMember1->node.pNext = nullptr;
    pMember1->pszValue = strdup("Radio0");

    pInput->pHead = (HDK_Member*)pMember1;
    pInput->pTail = (HDK_Member*)pMember1;

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    pStruct->pHead = nullptr;
    pStruct->pTail = nullptr;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_FindObjectIns(_, _, _, _, _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
        testing::Invoke([&](MBusObj_t *, const char *, const char *, const char *, char insPath[][MAX_PATH_NAME], int *insNum) {
            strcpy(insPath[0], "Device.WiFi.Radio.1.");
            *insNum = 1;
        }),
        Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .Times(1).WillOnce(Return(1));

    int result = HDK_Device_GetValue(mockDeviceCtx, pStruct, eValue, pInput);
    EXPECT_EQ(result, 0);

    free(pMember1);
    free(pStruct);
    free(pInput);
    pMember1 = nullptr;
    pStruct = nullptr;
    pInput = nullptr;
}

TEST_F(CcspHomeSecurityHDKDeviceGetValueFixture, HDK_Device_GetValue_WLanSSID_FAIL_2) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WLanSSID;
    char mockPathVal[] = "Device.WiFi.Radio.1";
    char mockAlias[] = "Radio1";
    char mockMAC[] = "00:00:00:00:00:00";

    HDK_Struct* pInput = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pInput, nullptr);

    HDK_Member__STRING__* pMember1 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember1, nullptr);

    pMember1->node.element = HDK_Element_PN_RadioID;
    pMember1->node.type = HDK_Type__STRING__;
    pMember1->node.pNext = nullptr;
    pMember1->pszValue = strdup("Radio0");

    pInput->pHead = (HDK_Member*)pMember1;
    pInput->pTail = (HDK_Member*)pMember1;

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    pStruct->pHead = nullptr;
    pStruct->pTail = nullptr;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_FindObjectIns(_, _, _, _, _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
        testing::Invoke([&](MBusObj_t *, const char *, const char *, const char *, char insPath[][MAX_PATH_NAME], int *insNum) {
            strcpy(insPath[0], "Device.WiFi.Radio.1.");
            *insNum = 1;
        }),
        Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("Alias"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockAlias, mockAlias + strlen(mockAlias) + 1),
             Return(0)
    ));

    int result = HDK_Device_GetValue(mockDeviceCtx, pStruct, eValue, pInput);
    EXPECT_EQ(result, 0);

    free(pMember1);
    free(pStruct);
    free(pInput);
    pMember1 = nullptr;
    pStruct = nullptr;
    pInput = nullptr;
}

TEST_F(CcspHomeSecurityHDKDeviceGetValueFixture, HDK_Device_GetValue_WLanSSIDBroadcast_SUCCESS_1) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WLanSSIDBroadcast;
    char mockPathVal[] = "Device.WiFi.Radio.1";
    char mockAlias[] = "Radio0";
    char mockVal[] = "true";

    HDK_Struct* pInput = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pInput, nullptr);

    HDK_Member__STRING__* pMember1 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember1, nullptr);

    pMember1->node.element = HDK_Element_PN_RadioID;
    pMember1->node.type = HDK_Type__STRING__;
    pMember1->node.pNext = nullptr;
    pMember1->pszValue = strdup("Radio0");

    pInput->pHead = (HDK_Member*)pMember1;
    pInput->pTail = (HDK_Member*)pMember1;

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    pStruct->pHead = nullptr;
    pStruct->pTail = nullptr;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_FindObjectIns(_, _, _, _, _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
        testing::Invoke([&](MBusObj_t *, const char *, const char *, const char *, char insPath[][MAX_PATH_NAME], int *insNum) {
            strcpy(insPath[0], "Device.WiFi.Radio.1.");
            *insNum = 1;
        }),
        Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("Alias"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockAlias, mockAlias + strlen(mockAlias) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("SSIDAdvertisementEnabled"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockVal, mockVal + strlen(mockVal) + 1),
             Return(0)
    ));

    int result = HDK_Device_GetValue(mockDeviceCtx, pStruct, eValue, pInput);
    EXPECT_EQ(result, 1);

    free(pMember1);
    free(pStruct);
    free(pInput);
    pMember1 = nullptr;
    pStruct = nullptr;
    pInput = nullptr;
}

TEST_F(CcspHomeSecurityHDKDeviceGetValueFixture, HDK_Device_GetValue_WLanSSIDBroadcast_SUCCESS_2) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WLanSSIDBroadcast;
    char mockPathVal[] = "Device.WiFi.Radio.1";
    char mockAlias[] = "Radio0";
    char mockVal[] = "false";

    HDK_Struct* pInput = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pInput, nullptr);

    HDK_Member__STRING__* pMember1 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember1, nullptr);

    pMember1->node.element = HDK_Element_PN_RadioID;
    pMember1->node.type = HDK_Type__STRING__;
    pMember1->node.pNext = nullptr;
    pMember1->pszValue = strdup("Radio0");

    pInput->pHead = (HDK_Member*)pMember1;
    pInput->pTail = (HDK_Member*)pMember1;

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    pStruct->pHead = nullptr;
    pStruct->pTail = nullptr;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_FindObjectIns(_, _, _, _, _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
        testing::Invoke([&](MBusObj_t *, const char *, const char *, const char *, char insPath[][MAX_PATH_NAME], int *insNum) {
            strcpy(insPath[0], "Device.WiFi.Radio.1.");
            *insNum = 1;
        }),
        Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("Alias"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockAlias, mockAlias + strlen(mockAlias) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("SSIDAdvertisementEnabled"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockVal, mockVal + strlen(mockVal) + 1),
             Return(0)
    ));

    int result = HDK_Device_GetValue(mockDeviceCtx, pStruct, eValue, pInput);
    EXPECT_EQ(result, 1);

    free(pMember1);
    free(pStruct);
    free(pInput);
    pMember1 = nullptr;
    pStruct = nullptr;
    pInput = nullptr;
}

TEST_F(CcspHomeSecurityHDKDeviceGetValueFixture, HDK_Device_GetValue_WLanSSIDBroadcast_FAIL_1) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WLanSSIDBroadcast;
    char mockPathVal[] = "Device.WiFi.Radio.1";

    HDK_Struct* pInput = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pInput, nullptr);

    HDK_Member__STRING__* pMember1 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember1, nullptr);

    pMember1->node.element = HDK_Element_PN_RadioID;
    pMember1->node.type = HDK_Type__STRING__;
    pMember1->node.pNext = nullptr;
    pMember1->pszValue = strdup("Radio0");

    pInput->pHead = (HDK_Member*)pMember1;
    pInput->pTail = (HDK_Member*)pMember1;

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    pStruct->pHead = nullptr;
    pStruct->pTail = nullptr;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_FindObjectIns(_, _, _, _, _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
        testing::Invoke([&](MBusObj_t *, const char *, const char *, const char *, char insPath[][MAX_PATH_NAME], int *insNum) {
            strcpy(insPath[0], "Device.WiFi.Radio.1.");
            *insNum = 1;
        }),
        Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .Times(1).WillOnce(Return(1));

    int result = HDK_Device_GetValue(mockDeviceCtx, pStruct, eValue, pInput);
    EXPECT_EQ(result, 0);

    free(pMember1);
    free(pStruct);
    free(pInput);
    pMember1 = nullptr;
    pStruct = nullptr;
    pInput = nullptr;
}

TEST_F(CcspHomeSecurityHDKDeviceGetValueFixture, HDK_Device_GetValue_WLanSSIDBroadcast_FAIL_2) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WLanSSIDBroadcast;
    char mockPathVal[] = "Device.WiFi.Radio.1";
    char mockAlias[] = "Radio1";
    char mockMAC[] = "00:00:00:00:00:00";

    HDK_Struct* pInput = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pInput, nullptr);

    HDK_Member__STRING__* pMember1 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember1, nullptr);

    pMember1->node.element = HDK_Element_PN_RadioID;
    pMember1->node.type = HDK_Type__STRING__;
    pMember1->node.pNext = nullptr;
    pMember1->pszValue = strdup("Radio0");

    pInput->pHead = (HDK_Member*)pMember1;
    pInput->pTail = (HDK_Member*)pMember1;

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    pStruct->pHead = nullptr;
    pStruct->pTail = nullptr;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_FindObjectIns(_, _, _, _, _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
        testing::Invoke([&](MBusObj_t *, const char *, const char *, const char *, char insPath[][MAX_PATH_NAME], int *insNum) {
            strcpy(insPath[0], "Device.WiFi.Radio.1.");
            *insNum = 1;
        }),
        Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("Alias"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockAlias, mockAlias + strlen(mockAlias) + 1),
             Return(0)
    ));

    int result = HDK_Device_GetValue(mockDeviceCtx, pStruct, eValue, pInput);
    EXPECT_EQ(result, 0);

    free(pMember1);
    free(pStruct);
    free(pInput);
    pMember1 = nullptr;
    pStruct = nullptr;
    pInput = nullptr;
}

TEST_F(CcspHomeSecurityHDKDeviceGetValueFixture, HDK_Device_GetValue_WLanChannelWidth_SUCCESS_1) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WLanChannelWidth;
    char mockPathVal[] = "Device.WiFi.Radio.1";
    char mockAlias[] = "Radio0";
    char mockChannelBW[] = "20MHz";

    HDK_Struct* pInput = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pInput, nullptr);

    HDK_Member__STRING__* pMember1 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember1, nullptr);

    pMember1->node.element = HDK_Element_PN_RadioID;
    pMember1->node.type = HDK_Type__STRING__;
    pMember1->node.pNext = nullptr;
    pMember1->pszValue = strdup("Radio0");

    pInput->pHead = (HDK_Member*)pMember1;
    pInput->pTail = (HDK_Member*)pMember1;

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    pStruct->pHead = nullptr;
    pStruct->pTail = nullptr;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_FindObjectIns(_, _, _, _, _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
        testing::Invoke([&](MBusObj_t *, const char *, const char *, const char *, char insPath[][MAX_PATH_NAME], int *insNum) {
            strcpy(insPath[0], "Device.WiFi.Radio.1.");
            *insNum = 1;
        }),
        Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("Alias"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockAlias, mockAlias + strlen(mockAlias) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("OperatingChannelBandwidth"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockChannelBW, mockChannelBW + strlen(mockChannelBW) + 1),
             Return(0)
    ));

    int result = HDK_Device_GetValue(mockDeviceCtx, pStruct, eValue, pInput);
    EXPECT_EQ(result, 1);

    free(pMember1);
    free(pStruct);
    free(pInput);
    pMember1 = nullptr;
    pStruct = nullptr;
    pInput = nullptr;
}

TEST_F(CcspHomeSecurityHDKDeviceGetValueFixture, HDK_Device_GetValue_WLanChannelWidth_SUCCESS_2) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WLanChannelWidth;
    char mockPathVal[] = "Device.WiFi.Radio.1";
    char mockAlias[] = "Radio0";
    char mockChannelBW[] = "40MHz";

    HDK_Struct* pInput = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pInput, nullptr);

    HDK_Member__STRING__* pMember1 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember1, nullptr);

    pMember1->node.element = HDK_Element_PN_RadioID;
    pMember1->node.type = HDK_Type__STRING__;
    pMember1->node.pNext = nullptr;
    pMember1->pszValue = strdup("Radio0");

    pInput->pHead = (HDK_Member*)pMember1;
    pInput->pTail = (HDK_Member*)pMember1;

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    pStruct->pHead = nullptr;
    pStruct->pTail = nullptr;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_FindObjectIns(_, _, _, _, _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
        testing::Invoke([&](MBusObj_t *, const char *, const char *, const char *, char insPath[][MAX_PATH_NAME], int *insNum) {
            strcpy(insPath[0], "Device.WiFi.Radio.1.");
            *insNum = 1;
        }),
        Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("Alias"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockAlias, mockAlias + strlen(mockAlias) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("OperatingChannelBandwidth"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockChannelBW, mockChannelBW + strlen(mockChannelBW) + 1),
             Return(0)
    ));

    int result = HDK_Device_GetValue(mockDeviceCtx, pStruct, eValue, pInput);
    EXPECT_EQ(result, 1);

    free(pMember1);
    free(pStruct);
    free(pInput);
    pMember1 = nullptr;
    pStruct = nullptr;
    pInput = nullptr;
}

TEST_F(CcspHomeSecurityHDKDeviceGetValueFixture, HDK_Device_GetValue_WLanChannelWidth_SUCCESS_3) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WLanChannelWidth;
    char mockPathVal[] = "Device.WiFi.Radio.1";
    char mockAlias[] = "Radio0";
    char mockChannelBW[] = "Auto";

    HDK_Struct* pInput = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pInput, nullptr);

    HDK_Member__STRING__* pMember1 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember1, nullptr);

    pMember1->node.element = HDK_Element_PN_RadioID;
    pMember1->node.type = HDK_Type__STRING__;
    pMember1->node.pNext = nullptr;
    pMember1->pszValue = strdup("Radio0");

    pInput->pHead = (HDK_Member*)pMember1;
    pInput->pTail = (HDK_Member*)pMember1;

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    pStruct->pHead = nullptr;
    pStruct->pTail = nullptr;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_FindObjectIns(_, _, _, _, _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
        testing::Invoke([&](MBusObj_t *, const char *, const char *, const char *, char insPath[][MAX_PATH_NAME], int *insNum) {
            strcpy(insPath[0], "Device.WiFi.Radio.1.");
            *insNum = 1;
        }),
        Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("Alias"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockAlias, mockAlias + strlen(mockAlias) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("OperatingChannelBandwidth"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockChannelBW, mockChannelBW + strlen(mockChannelBW) + 1),
             Return(0)
    ));

    int result = HDK_Device_GetValue(mockDeviceCtx, pStruct, eValue, pInput);
    EXPECT_EQ(result, 1);

    free(pMember1);
    free(pStruct);
    free(pInput);
    pMember1 = nullptr;
    pStruct = nullptr;
    pInput = nullptr;
}

TEST_F(CcspHomeSecurityHDKDeviceGetValueFixture, HDK_Device_GetValue_WLanChannelWidth_FAIL_1) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WLanChannelWidth;
    char mockPathVal[] = "Device.WiFi.Radio.1";

    HDK_Struct* pInput = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pInput, nullptr);

    HDK_Member__STRING__* pMember1 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember1, nullptr);

    pMember1->node.element = HDK_Element_PN_RadioID;
    pMember1->node.type = HDK_Type__STRING__;
    pMember1->node.pNext = nullptr;
    pMember1->pszValue = strdup("Radio0");

    pInput->pHead = (HDK_Member*)pMember1;
    pInput->pTail = (HDK_Member*)pMember1;

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    pStruct->pHead = nullptr;
    pStruct->pTail = nullptr;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_FindObjectIns(_, _, _, _, _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
        testing::Invoke([&](MBusObj_t *, const char *, const char *, const char *, char insPath[][MAX_PATH_NAME], int *insNum) {
            strcpy(insPath[0], "Device.WiFi.Radio.1.");
            *insNum = 1;
        }),
        Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .Times(1).WillOnce(Return(1));

    int result = HDK_Device_GetValue(mockDeviceCtx, pStruct, eValue, pInput);
    EXPECT_EQ(result, 0);

    free(pMember1);
    free(pStruct);
    free(pInput);
    pMember1 = nullptr;
    pStruct = nullptr;
    pInput = nullptr;
}

TEST_F(CcspHomeSecurityHDKDeviceGetValueFixture, HDK_Device_GetValue_WLanChannelWidth_FAIL_2) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WLanChannelWidth;
    char mockPathVal[] = "Device.WiFi.Radio.1";
    char mockAlias[] = "Radio1";
    char mockMAC[] = "00:00:00:00:00:00";

    HDK_Struct* pInput = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pInput, nullptr);

    HDK_Member__STRING__* pMember1 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember1, nullptr);

    pMember1->node.element = HDK_Element_PN_RadioID;
    pMember1->node.type = HDK_Type__STRING__;
    pMember1->node.pNext = nullptr;
    pMember1->pszValue = strdup("Radio0");

    pInput->pHead = (HDK_Member*)pMember1;
    pInput->pTail = (HDK_Member*)pMember1;

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    pStruct->pHead = nullptr;
    pStruct->pTail = nullptr;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_FindObjectIns(_, _, _, _, _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
        testing::Invoke([&](MBusObj_t *, const char *, const char *, const char *, char insPath[][MAX_PATH_NAME], int *insNum) {
            strcpy(insPath[0], "Device.WiFi.Radio.1.");
            *insNum = 1;
        }),
        Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("Alias"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockAlias, mockAlias + strlen(mockAlias) + 1),
             Return(0)
    ));

    int result = HDK_Device_GetValue(mockDeviceCtx, pStruct, eValue, pInput);
    EXPECT_EQ(result, 0);

    free(pMember1);
    free(pStruct);
    free(pInput);
    pMember1 = nullptr;
    pStruct = nullptr;
    pInput = nullptr;
}

TEST_F(CcspHomeSecurityHDKDeviceGetValueFixture, HDK_Device_GetValue_WLanChannel_SUCCESS) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WLanChannel;
    char mockPathVal[] = "Device.WiFi.Radio.1";
    char mockAlias[] = "Radio0";
    char mockVal[] = "1";

    HDK_Struct* pInput = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pInput, nullptr);

    HDK_Member__STRING__* pMember1 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember1, nullptr);

    pMember1->node.element = HDK_Element_PN_RadioID;
    pMember1->node.type = HDK_Type__STRING__;
    pMember1->node.pNext = nullptr;
    pMember1->pszValue = strdup("Radio0");

    pInput->pHead = (HDK_Member*)pMember1;
    pInput->pTail = (HDK_Member*)pMember1;

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    pStruct->pHead = nullptr;
    pStruct->pTail = nullptr;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_FindObjectIns(_, _, _, _, _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
        testing::Invoke([&](MBusObj_t *, const char *, const char *, const char *, char insPath[][MAX_PATH_NAME], int *insNum) {
            strcpy(insPath[0], "Device.WiFi.Radio.1.");
            *insNum = 1;
        }),
        Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("Alias"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockAlias, mockAlias + strlen(mockAlias) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("Channel"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockVal, mockVal + strlen(mockVal) + 1),
             Return(0)
    ));

    int result = HDK_Device_GetValue(mockDeviceCtx, pStruct, eValue, pInput);
    EXPECT_EQ(result, 1);

    free(pMember1);
    free(pStruct);
    free(pInput);
    pMember1 = nullptr;
    pStruct = nullptr;
    pInput = nullptr;
}

TEST_F(CcspHomeSecurityHDKDeviceGetValueFixture, HDK_Device_GetValue_WLanChannel_FAIL_1) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WLanChannel;
    char mockPathVal[] = "Device.WiFi.Radio.1";

    HDK_Struct* pInput = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pInput, nullptr);

    HDK_Member__STRING__* pMember1 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember1, nullptr);

    pMember1->node.element = HDK_Element_PN_RadioID;
    pMember1->node.type = HDK_Type__STRING__;
    pMember1->node.pNext = nullptr;
    pMember1->pszValue = strdup("Radio0");

    pInput->pHead = (HDK_Member*)pMember1;
    pInput->pTail = (HDK_Member*)pMember1;

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    pStruct->pHead = nullptr;
    pStruct->pTail = nullptr;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_FindObjectIns(_, _, _, _, _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
        testing::Invoke([&](MBusObj_t *, const char *, const char *, const char *, char insPath[][MAX_PATH_NAME], int *insNum) {
            strcpy(insPath[0], "Device.WiFi.Radio.1.");
            *insNum = 1;
        }),
        Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .Times(1).WillOnce(Return(1));

    int result = HDK_Device_GetValue(mockDeviceCtx, pStruct, eValue, pInput);
    EXPECT_EQ(result, 0);

    free(pMember1);
    free(pStruct);
    free(pInput);
    pMember1 = nullptr;
    pStruct = nullptr;
    pInput = nullptr;
}

TEST_F(CcspHomeSecurityHDKDeviceGetValueFixture, HDK_Device_GetValue_WLanChannel_FAIL_2) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WLanChannel;
    char mockPathVal[] = "Device.WiFi.Radio.1";
    char mockAlias[] = "Radio1";
    char mockMAC[] = "00:00:00:00:00:00";

    HDK_Struct* pInput = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pInput, nullptr);

    HDK_Member__STRING__* pMember1 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember1, nullptr);

    pMember1->node.element = HDK_Element_PN_RadioID;
    pMember1->node.type = HDK_Type__STRING__;
    pMember1->node.pNext = nullptr;
    pMember1->pszValue = strdup("Radio0");

    pInput->pHead = (HDK_Member*)pMember1;
    pInput->pTail = (HDK_Member*)pMember1;

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    pStruct->pHead = nullptr;
    pStruct->pTail = nullptr;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_FindObjectIns(_, _, _, _, _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
        testing::Invoke([&](MBusObj_t *, const char *, const char *, const char *, char insPath[][MAX_PATH_NAME], int *insNum) {
            strcpy(insPath[0], "Device.WiFi.Radio.1.");
            *insNum = 1;
        }),
        Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("Alias"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockAlias, mockAlias + strlen(mockAlias) + 1),
             Return(0)
    ));

    int result = HDK_Device_GetValue(mockDeviceCtx, pStruct, eValue, pInput);
    EXPECT_EQ(result, 0);

    free(pMember1);
    free(pStruct);
    free(pInput);
    pMember1 = nullptr;
    pStruct = nullptr;
    pInput = nullptr;
}

TEST_F(CcspHomeSecurityHDKDeviceGetValueFixture, HDK_Device_GetValue_WLanSecondaryChannel_SUCCESS_1) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WLanSecondaryChannel;
    char mockPathVal[] = "Device.WiFi.Radio.1";
    char mockAlias[] = "Radio0";
    char mockVal[] = "AboveControlChannel";

    HDK_Struct* pInput = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pInput, nullptr);

    HDK_Member__STRING__* pMember1 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember1, nullptr);

    pMember1->node.element = HDK_Element_PN_RadioID;
    pMember1->node.type = HDK_Type__STRING__;
    pMember1->node.pNext = nullptr;
    pMember1->pszValue = strdup("Radio0");

    pInput->pHead = (HDK_Member*)pMember1;
    pInput->pTail = (HDK_Member*)pMember1;

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    pStruct->pHead = nullptr;
    pStruct->pTail = nullptr;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_FindObjectIns(_, _, _, _, _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
        testing::Invoke([&](MBusObj_t *, const char *, const char *, const char *, char insPath[][MAX_PATH_NAME], int *insNum) {
            strcpy(insPath[0], "Device.WiFi.Radio.1.");
            *insNum = 1;
        }),
        Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("Alias"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockAlias, mockAlias + strlen(mockAlias) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("ExtensionChannel"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockVal, mockVal + strlen(mockVal) + 1),
             Return(0)
    ));

    int result = HDK_Device_GetValue(mockDeviceCtx, pStruct, eValue, pInput);
    EXPECT_EQ(result, 1);

    free(pMember1);
    free(pStruct);
    free(pInput);
    pMember1 = nullptr;
    pStruct = nullptr;
    pInput = nullptr;
}

TEST_F(CcspHomeSecurityHDKDeviceGetValueFixture, HDK_Device_GetValue_WLanSecondaryChannel_SUCCESS_2) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WLanSecondaryChannel;
    char mockPathVal[] = "Device.WiFi.Radio.1";
    char mockAlias[] = "Radio0";
    char mockVal[] = "BelowControlChannel";

    HDK_Struct* pInput = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pInput, nullptr);

    HDK_Member__STRING__* pMember1 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember1, nullptr);

    pMember1->node.element = HDK_Element_PN_RadioID;
    pMember1->node.type = HDK_Type__STRING__;
    pMember1->node.pNext = nullptr;
    pMember1->pszValue = strdup("Radio0");

    pInput->pHead = (HDK_Member*)pMember1;
    pInput->pTail = (HDK_Member*)pMember1;

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    pStruct->pHead = nullptr;
    pStruct->pTail = nullptr;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_FindObjectIns(_, _, _, _, _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
        testing::Invoke([&](MBusObj_t *, const char *, const char *, const char *, char insPath[][MAX_PATH_NAME], int *insNum) {
            strcpy(insPath[0], "Device.WiFi.Radio.1.");
            *insNum = 1;
        }),
        Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("Alias"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockAlias, mockAlias + strlen(mockAlias) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("ExtensionChannel"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockVal, mockVal + strlen(mockVal) + 1),
             Return(0)
    ));

    int result = HDK_Device_GetValue(mockDeviceCtx, pStruct, eValue, pInput);
    EXPECT_EQ(result, 1);

    free(pMember1);
    free(pStruct);
    free(pInput);
    pMember1 = nullptr;
    pStruct = nullptr;
    pInput = nullptr;
}

TEST_F(CcspHomeSecurityHDKDeviceGetValueFixture, HDK_Device_GetValue_WLanSecondaryChannel_SUCCESS_3) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WLanSecondaryChannel;
    char mockPathVal[] = "Device.WiFi.Radio.1";
    char mockAlias[] = "Radio0";
    char mockVal[] = "Auto";

    HDK_Struct* pInput = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pInput, nullptr);

    HDK_Member__STRING__* pMember1 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember1, nullptr);

    pMember1->node.element = HDK_Element_PN_RadioID;
    pMember1->node.type = HDK_Type__STRING__;
    pMember1->node.pNext = nullptr;
    pMember1->pszValue = strdup("Radio0");

    pInput->pHead = (HDK_Member*)pMember1;
    pInput->pTail = (HDK_Member*)pMember1;

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    pStruct->pHead = nullptr;
    pStruct->pTail = nullptr;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_FindObjectIns(_, _, _, _, _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
        testing::Invoke([&](MBusObj_t *, const char *, const char *, const char *, char insPath[][MAX_PATH_NAME], int *insNum) {
            strcpy(insPath[0], "Device.WiFi.Radio.1.");
            *insNum = 1;
        }),
        Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("Alias"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockAlias, mockAlias + strlen(mockAlias) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("ExtensionChannel"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockVal, mockVal + strlen(mockVal) + 1),
             Return(0)
    ));

    int result = HDK_Device_GetValue(mockDeviceCtx, pStruct, eValue, pInput);
    EXPECT_EQ(result, 1);

    free(pMember1);
    free(pStruct);
    free(pInput);
    pMember1 = nullptr;
    pStruct = nullptr;
    pInput = nullptr;
}

TEST_F(CcspHomeSecurityHDKDeviceGetValueFixture, HDK_Device_GetValue_WLanSecondaryChannel_FAIL_1) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WLanSecondaryChannel;
    char mockPathVal[] = "Device.WiFi.Radio.1";

    HDK_Struct* pInput = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pInput, nullptr);

    HDK_Member__STRING__* pMember1 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember1, nullptr);

    pMember1->node.element = HDK_Element_PN_RadioID;
    pMember1->node.type = HDK_Type__STRING__;
    pMember1->node.pNext = nullptr;
    pMember1->pszValue = strdup("Radio0");

    pInput->pHead = (HDK_Member*)pMember1;
    pInput->pTail = (HDK_Member*)pMember1;

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    pStruct->pHead = nullptr;
    pStruct->pTail = nullptr;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_FindObjectIns(_, _, _, _, _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
        testing::Invoke([&](MBusObj_t *, const char *, const char *, const char *, char insPath[][MAX_PATH_NAME], int *insNum) {
            strcpy(insPath[0], "Device.WiFi.Radio.1.");
            *insNum = 1;
        }),
        Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .Times(1).WillOnce(Return(1));

    int result = HDK_Device_GetValue(mockDeviceCtx, pStruct, eValue, pInput);
    EXPECT_EQ(result, 0);

    free(pMember1);
    free(pStruct);
    free(pInput);
    pMember1 = nullptr;
    pStruct = nullptr;
    pInput = nullptr;
}

TEST_F(CcspHomeSecurityHDKDeviceGetValueFixture, HDK_Device_GetValue_WLanSecondaryChannel_FAIL_2) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WLanSecondaryChannel;
    char mockPathVal[] = "Device.WiFi.Radio.1";
    char mockAlias[] = "Radio1";
    char mockMAC[] = "00:00:00:00:00:00";

    HDK_Struct* pInput = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pInput, nullptr);

    HDK_Member__STRING__* pMember1 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember1, nullptr);

    pMember1->node.element = HDK_Element_PN_RadioID;
    pMember1->node.type = HDK_Type__STRING__;
    pMember1->node.pNext = nullptr;
    pMember1->pszValue = strdup("Radio0");

    pInput->pHead = (HDK_Member*)pMember1;
    pInput->pTail = (HDK_Member*)pMember1;

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    pStruct->pHead = nullptr;
    pStruct->pTail = nullptr;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_FindObjectIns(_, _, _, _, _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
        testing::Invoke([&](MBusObj_t *, const char *, const char *, const char *, char insPath[][MAX_PATH_NAME], int *insNum) {
            strcpy(insPath[0], "Device.WiFi.Radio.1.");
            *insNum = 1;
        }),
        Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("Alias"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockAlias, mockAlias + strlen(mockAlias) + 1),
             Return(0)
    ));

    int result = HDK_Device_GetValue(mockDeviceCtx, pStruct, eValue, pInput);
    EXPECT_EQ(result, 0);

    free(pMember1);
    free(pStruct);
    free(pInput);
    pMember1 = nullptr;
    pStruct = nullptr;
    pInput = nullptr;
}

TEST_F(CcspHomeSecurityHDKDeviceGetValueFixture, HDK_Device_GetValue_WLanQoS_SUCCESS_1) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WLanQoS;
    char mockPathVal[] = "Device.WiFi.Radio.1";
    char mockApPathVal[] = "Device.WiFi.AccessPoint.3";
    char mockAlias[] = "Radio0";
    char mockVal[] = "true";

    HDK_Struct* pInput = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pInput, nullptr);

    HDK_Member__STRING__* pMember1 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember1, nullptr);

    pMember1->node.element = HDK_Element_PN_RadioID;
    pMember1->node.type = HDK_Type__STRING__;
    pMember1->node.pNext = nullptr;
    pMember1->pszValue = strdup("Radio0");

    pInput->pHead = (HDK_Member*)pMember1;
    pInput->pTail = (HDK_Member*)pMember1;

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    pStruct->pHead = nullptr;
    pStruct->pTail = nullptr;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_FindObjectIns(_, _, _, _, _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
        testing::Invoke([&](MBusObj_t *, const char *, const char *, const char *, char insPath[][MAX_PATH_NAME], int *insNum) {
            strcpy(insPath[0], "Device.WiFi.Radio.1.");
            *insNum = 1;
        }),
        Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("Alias"), _, _))
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

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("WMMEnable"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockVal, mockVal + strlen(mockVal) + 1),
             Return(0)
    ));

    int result = HDK_Device_GetValue(mockDeviceCtx, pStruct, eValue, pInput);
    EXPECT_EQ(result, 1);

    free(pMember1);
    free(pStruct);
    free(pInput);
    pMember1 = nullptr;
    pStruct = nullptr;
    pInput = nullptr;
}

TEST_F(CcspHomeSecurityHDKDeviceGetValueFixture, HDK_Device_GetValue_WLanQoS_SUCCESS_2) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WLanQoS;
    char mockPathVal[] = "Device.WiFi.Radio.1";
    char mockApPathVal[] = "Device.WiFi.AccessPoint.3";
    char mockAlias[] = "Radio0";
    char mockVal[] = "false";

    HDK_Struct* pInput = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pInput, nullptr);

    HDK_Member__STRING__* pMember1 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember1, nullptr);

    pMember1->node.element = HDK_Element_PN_RadioID;
    pMember1->node.type = HDK_Type__STRING__;
    pMember1->node.pNext = nullptr;
    pMember1->pszValue = strdup("Radio0");

    pInput->pHead = (HDK_Member*)pMember1;
    pInput->pTail = (HDK_Member*)pMember1;

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    pStruct->pHead = nullptr;
    pStruct->pTail = nullptr;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_FindObjectIns(_, _, _, _, _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
        testing::Invoke([&](MBusObj_t *, const char *, const char *, const char *, char insPath[][MAX_PATH_NAME], int *insNum) {
            strcpy(insPath[0], "Device.WiFi.Radio.1.");
            *insNum = 1;
        }),
        Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("Alias"), _, _))
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

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("WMMEnable"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockVal, mockVal + strlen(mockVal) + 1),
             Return(0)
    ));

    int result = HDK_Device_GetValue(mockDeviceCtx, pStruct, eValue, pInput);
    EXPECT_EQ(result, 1);

    free(pMember1);
    free(pStruct);
    free(pInput);
    pMember1 = nullptr;
    pStruct = nullptr;
    pInput = nullptr;
}

TEST_F(CcspHomeSecurityHDKDeviceGetValueFixture, HDK_Device_GetValue_WLanQoS_FAIL_1) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WLanQoS;
    char mockPathVal[] = "Device.WiFi.Radio.1";

    HDK_Struct* pInput = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pInput, nullptr);

    HDK_Member__STRING__* pMember1 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember1, nullptr);

    pMember1->node.element = HDK_Element_PN_RadioID;
    pMember1->node.type = HDK_Type__STRING__;
    pMember1->node.pNext = nullptr;
    pMember1->pszValue = strdup("Radio0");

    pInput->pHead = (HDK_Member*)pMember1;
    pInput->pTail = (HDK_Member*)pMember1;

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    pStruct->pHead = nullptr;
    pStruct->pTail = nullptr;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_FindObjectIns(_, _, _, _, _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
        testing::Invoke([&](MBusObj_t *, const char *, const char *, const char *, char insPath[][MAX_PATH_NAME], int *insNum) {
            strcpy(insPath[0], "Device.WiFi.Radio.1.");
            *insNum = 1;
        }),
        Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .Times(1).WillOnce(Return(1));

    int result = HDK_Device_GetValue(mockDeviceCtx, pStruct, eValue, pInput);
    EXPECT_EQ(result, 0);

    free(pMember1);
    free(pStruct);
    free(pInput);
    pMember1 = nullptr;
    pStruct = nullptr;
    pInput = nullptr;
}

TEST_F(CcspHomeSecurityHDKDeviceGetValueFixture, HDK_Device_GetValue_WLanQoS_FAIL_2) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WLanQoS;
    char mockPathVal[] = "Device.WiFi.Radio.1";
    char mockAlias[] = "Radio1";
    char mockMAC[] = "00:00:00:00:00:00";

    HDK_Struct* pInput = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pInput, nullptr);

    HDK_Member__STRING__* pMember1 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember1, nullptr);

    pMember1->node.element = HDK_Element_PN_RadioID;
    pMember1->node.type = HDK_Type__STRING__;
    pMember1->node.pNext = nullptr;
    pMember1->pszValue = strdup("Radio0");

    pInput->pHead = (HDK_Member*)pMember1;
    pInput->pTail = (HDK_Member*)pMember1;

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    pStruct->pHead = nullptr;
    pStruct->pTail = nullptr;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_FindObjectIns(_, _, _, _, _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
        testing::Invoke([&](MBusObj_t *, const char *, const char *, const char *, char insPath[][MAX_PATH_NAME], int *insNum) {
            strcpy(insPath[0], "Device.WiFi.Radio.1.");
            *insNum = 1;
        }),
        Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("Alias"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockAlias, mockAlias + strlen(mockAlias) + 1),
             Return(0)
    ));

    int result = HDK_Device_GetValue(mockDeviceCtx, pStruct, eValue, pInput);
    EXPECT_EQ(result, 0);

    free(pMember1);
    free(pStruct);
    free(pInput);
    pMember1 = nullptr;
    pStruct = nullptr;
    pInput = nullptr;
}

TEST_F(CcspHomeSecurityHDKDeviceGetValueFixture, HDK_Device_GetValue_WLanQoS_FAIL_3) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WLanQoS;
    char mockPathVal[] = "Device.WiFi.Radio.1";
    char mockAlias[] = "Radio0";
    char mockMAC[] = "00:00:00:00:00:00";

    HDK_Struct* pInput = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pInput, nullptr);

    HDK_Member__STRING__* pMember1 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember1, nullptr);

    pMember1->node.element = HDK_Element_PN_RadioID;
    pMember1->node.type = HDK_Type__STRING__;
    pMember1->node.pNext = nullptr;
    pMember1->pszValue = strdup("Radio0");

    pInput->pHead = (HDK_Member*)pMember1;
    pInput->pTail = (HDK_Member*)pMember1;

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    pStruct->pHead = nullptr;
    pStruct->pTail = nullptr;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_FindObjectIns(_, _, _, _, _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
        testing::Invoke([&](MBusObj_t *, const char *, const char *, const char *, char insPath[][MAX_PATH_NAME], int *insNum) {
            strcpy(insPath[0], "Device.WiFi.Radio.1.");
            *insNum = 1;
        }),
        Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("Alias"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockAlias, mockAlias + strlen(mockAlias) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiAp"), _, _))
    .Times(1).WillOnce(Return(1));

    int result = HDK_Device_GetValue(mockDeviceCtx, pStruct, eValue, pInput);
    EXPECT_EQ(result, 0);

    free(pMember1);
    free(pStruct);
    free(pInput);
    pMember1 = nullptr;
    pStruct = nullptr;
    pInput = nullptr;
}

TEST_F(CcspHomeSecurityHDKDeviceGetValueFixture, HDK_Device_GetValue_WanType_SUCCESS) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WanType;

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    pStruct->pHead = nullptr;
    pStruct->pTail = nullptr;

    int result = HDK_Device_GetValue(mockDeviceCtx, pStruct, eValue, pStruct);
    EXPECT_EQ(result, 1);

    free(pStruct);
    pStruct = nullptr;
}

TEST_F(CcspHomeSecurityHDKDeviceGetValueFixture, HDK_Device_GetValue_WanUserName_SUCCESS) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WanUsername;

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    pStruct->pHead = nullptr;
    pStruct->pTail = nullptr;

    int result = HDK_Device_GetValue(mockDeviceCtx, pStruct, eValue, pStruct);
    EXPECT_EQ(result, 1);

    free(pStruct);
    pStruct = nullptr;
}

TEST_F(CcspHomeSecurityHDKDeviceGetValueFixture, HDK_Device_GetValue_WanPassword_SUCCESS) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WanPassword;

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    pStruct->pHead = nullptr;
    pStruct->pTail = nullptr;

    int result = HDK_Device_GetValue(mockDeviceCtx, pStruct, eValue, pStruct);
    EXPECT_EQ(result, 1);

    free(pStruct);
    pStruct = nullptr;
}

TEST_F(CcspHomeSecurityHDKDeviceGetValueFixture, HDK_Device_GetValue_WanMaxIdleTime_SUCCESS) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WanMaxIdleTime;

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    pStruct->pHead = nullptr;
    pStruct->pTail = nullptr;

    int result = HDK_Device_GetValue(mockDeviceCtx, pStruct, eValue, pStruct);
    EXPECT_EQ(result, 1);

    free(pStruct);
    pStruct = nullptr;
}

TEST_F(CcspHomeSecurityHDKDeviceGetValueFixture, HDK_Device_GetValue_WanAutoReconnect_SUCCESS) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WanAutoReconnect;

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    pStruct->pHead = nullptr;
    pStruct->pTail = nullptr;

    int result = HDK_Device_GetValue(mockDeviceCtx, pStruct, eValue, pStruct);
    EXPECT_EQ(result, 1);

    free(pStruct);
    pStruct = nullptr;
}

TEST_F(CcspHomeSecurityHDKDeviceGetValueFixture, HDK_Device_GetValue_WanAuthService_SUCCESS) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WanAuthService;

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    pStruct->pHead = nullptr;
    pStruct->pTail = nullptr;

    int result = HDK_Device_GetValue(mockDeviceCtx, pStruct, eValue, pStruct);
    EXPECT_EQ(result, 1);

    free(pStruct);
    pStruct = nullptr;
}

TEST_F(CcspHomeSecurityHDKDeviceGetValueFixture, HDK_Device_GetValue_WanLoginService_SUCCESS) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WanLoginService;

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    pStruct->pHead = nullptr;
    pStruct->pTail = nullptr;

    int result = HDK_Device_GetValue(mockDeviceCtx, pStruct, eValue, pStruct);
    EXPECT_EQ(result, 1);

    free(pStruct);
    pStruct = nullptr;
}

TEST_F(CcspHomeSecurityHDKDeviceGetValueFixture, HDK_Device_GetValue_WanIP_SUCCESS) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WanIP;
    char mockIP[] = "192.168.1.1";

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    pStruct->pHead = nullptr;
    pStruct->pTail = nullptr;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_FindObjectIns(_, _, _, _, _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
        testing::Invoke([&](MBusObj_t *, const char *, const char *, const char *, char insPath[][MAX_PATH_NAME], int *insNum) {
            strcpy(insPath[0], "Device.DHCPv4.Client.1.");
            *insNum = 1;
        }),
        Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("IPAddress"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockIP, mockIP + strlen(mockIP) + 1),
             Return(0)
    ));

    int result = HDK_Device_GetValue(mockDeviceCtx, pStruct, eValue, pStruct);
    EXPECT_EQ(result, 1);

    free(pStruct);
    pStruct = nullptr;
}

TEST_F(CcspHomeSecurityHDKDeviceGetValueFixture, HDK_Device_GetValue_WanSubnetMask_SUCCESS) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WanSubnetMask;
    char mockIP[] = "255.255.255.0";

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    pStruct->pHead = nullptr;
    pStruct->pTail = nullptr;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_FindObjectIns(_, _, _, _, _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
        testing::Invoke([&](MBusObj_t *, const char *, const char *, const char *, char insPath[][MAX_PATH_NAME], int *insNum) {
            strcpy(insPath[0], "Device.DHCPv4.Client.1.");
            *insNum = 1;
        }),
        Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("SubnetMask"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockIP, mockIP + strlen(mockIP) + 1),
             Return(0)
    ));

    int result = HDK_Device_GetValue(mockDeviceCtx, pStruct, eValue, pStruct);
    EXPECT_EQ(result, 1);

    free(pStruct);
    pStruct = nullptr;
}

TEST_F(CcspHomeSecurityHDKDeviceGetValueFixture, HDK_Device_GetValue_WanGateway_SUCCESS) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WanGateway;
    char mockIP[] = "";

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    pStruct->pHead = nullptr;
    pStruct->pTail = nullptr;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_FindObjectIns(_, _, _, _, _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
        testing::Invoke([&](MBusObj_t *, const char *, const char *, const char *, char insPath[][MAX_PATH_NAME], int *insNum) {
            strcpy(insPath[0], "Device.DHCPv4.Client.1.");
            *insNum = 1;
        }),
        Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("IPRouters"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockIP, mockIP + strlen(mockIP) + 1),
             Return(0)
    ));

    int result = HDK_Device_GetValue(mockDeviceCtx, pStruct, eValue, pStruct);
    EXPECT_EQ(result, 1);

    free(pStruct);
    pStruct = nullptr;
}

TEST_F(CcspHomeSecurityHDKDeviceGetValueFixture, HDK_Device_GetValue_WanDNSSettings_SUCCESS_1) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WanDNSSettings;
    char mockInsNum[] = "3";
    char mockIP[] = "";
    char mockType[] = "DHCPv4";
    char mockTypev6[] = "DHCPv6";

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    pStruct->pHead = nullptr;
    pStruct->pTail = nullptr;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.DNS.Client.ServerNumberOfEntries"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockInsNum, mockInsNum + strlen(mockInsNum) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("Type"), _, _))
    .Times(3)
    .WillRepeatedly(testing::DoAll(
             testing::SetArrayArgument<2>(mockType, mockType + strlen(mockType) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("DNSServer"), _, _))
    .Times(3)
    .WillRepeatedly(testing::DoAll(
             testing::SetArrayArgument<2>(mockIP, mockIP + strlen(mockIP) + 1),
             Return(0)
    ));

    int result = HDK_Device_GetValue(mockDeviceCtx, pStruct, eValue, pStruct);
    EXPECT_EQ(result, 1);

    free(pStruct);
    pStruct = nullptr;
}

TEST_F(CcspHomeSecurityHDKDeviceGetValueFixture, HDK_Device_GetValue_WanDNSSettings_SUCCESS_2) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WanDNSSettings;
    char mockInsNum[] = "0";

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    pStruct->pHead = nullptr;
    pStruct->pTail = nullptr;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.DNS.Client.ServerNumberOfEntries"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockInsNum, mockInsNum + strlen(mockInsNum) + 1),
             Return(0)
    ));

    int result = HDK_Device_GetValue(mockDeviceCtx, pStruct, eValue, pStruct);
    EXPECT_EQ(result, 1);

    free(pStruct);
    pStruct = nullptr;
}

TEST_F(CcspHomeSecurityHDKDeviceGetValueFixture, HDK_Device_GetValue_WanMTU_SUCCESS) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_DeviceValue eValue = HDK_DeviceValue_WanMTU;
    char mockMTUSize[] = "1500";

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    pStruct->pHead = nullptr;
    pStruct->pTail = nullptr;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("com.cisco.spvtg.ccsp.pam.Helper.FirstUpstreamIpInteface.MaxMTUSize"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockMTUSize, mockMTUSize + strlen(mockMTUSize) + 1),
             Return(0)
    ));

    int result = HDK_Device_GetValue(mockDeviceCtx, pStruct, eValue, pStruct);
    EXPECT_EQ(result, 1);

    free(pStruct);
    pStruct = nullptr;
}
