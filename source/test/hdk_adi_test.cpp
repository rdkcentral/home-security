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

extern "C" {

}

class CcspHomeSecurityHDKAdiFixture : public ::testing::Test {
protected:
    void SetUp() override {
        g_HdkCcspMbusMock = new HdkCcspMbusMock();
    }

    void TearDown() override {
        delete g_HdkCcspMbusMock;
        g_HdkCcspMbusMock = nullptr;
    }
};

TEST_F(CcspHomeSecurityHDKAdiFixture, HDK_Method_PN_SetBridgeConnect) {
    printf("HDK_Method_PN_SetBridgeConnect\n");
    HDK_Context* mockCtx = createMockHDK_Context();
    ASSERT_NE(mockCtx, nullptr);

    HDK_Struct* pInput = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pInput, nullptr);
    memset(pInput, 0, sizeof(HDK_Struct));

    HDK_Struct* pOutput = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pOutput, nullptr);
    memset(pOutput, 0, sizeof(HDK_Struct));

    HDK_Member__INT__* pMember1 = (HDK_Member__INT__*) malloc(sizeof(HDK_Member__INT__));
    ASSERT_NE(pMember1, nullptr);

    pMember1->node.element = HDK_Element_PN_EthernetPort;
    pMember1->node.type = HDK_Type__INT__;
    pMember1->node.pNext = nullptr;
    pMember1->iValue = 1;

    pInput->pHead = (HDK_Member*)pMember1;
    pInput->pTail = (HDK_Member*)pMember1;

    printf("Calling HDK_Method_PN_SetBridgeConnect\n");

    HDK_Method_PN_SetBridgeConnect(mockCtx, pInput, pOutput);

    printf("HDK_Method_PN_SetBridgeConnect completed\n");

    free(pMember1);
    free(pInput);
    free(pOutput);
    free(mockCtx);
}

TEST_F(CcspHomeSecurityHDKAdiFixture, HDK_Method_PN_GetDeviceSettings_CASE_1) {
    HDK_Context* mockCtx = createMockHDK_Context();
    HDK_Struct* pInput = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pInput, nullptr);
    HDK_Struct* pOutput = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pOutput, nullptr);

    pOutput->pHead = nullptr;
    pOutput->pTail = nullptr;

    char mockDeviceName[] = "test_device";
    char mockVendorName[] = "test_vendor";
    char mockDescription[] = "test_description";
    char mockFirmwareVersion[] = "test_firmware_version";
    char mockPathVal[] = "Device.DHCPv4.Server.Pool.1";
    char mockURL[] = "10.0.0.1";

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.DeviceInfo.ModelName"), _, _))
    .WillRepeatedly(testing::DoAll(
             testing::SetArrayArgument<2>(mockDeviceName, mockDeviceName + strlen(mockDeviceName) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.DeviceInfo.Manufacturer"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockVendorName, mockVendorName + strlen(mockVendorName) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.DeviceInfo.Description"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockDescription, mockDescription + strlen(mockDescription) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.DeviceInfo.X_CISCO_COM_FirmwareName"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockFirmwareVersion, mockFirmwareVersion + strlen(mockFirmwareVersion) + 1),
             Return(0)
    ));

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

    HDK_Method_PN_GetDeviceSettings((void*)mockCtx, pInput, pOutput);

    free(pInput);
    free(pOutput);
    free(mockCtx);
}

TEST_F(CcspHomeSecurityHDKAdiFixture, HDK_Method_PN_GetDeviceSettings_CASE_2) {
    HDK_Context* mockCtx = createMockHDK_Context();
    HDK_Struct* pInput = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pInput, nullptr);
    HDK_Struct* pOutput = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pOutput, nullptr);

    pOutput->pHead = nullptr;
    pOutput->pTail = nullptr;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.DeviceInfo.ModelName"), _, _))
    .Times(1).WillOnce(Return(1));

    HDK_Method_PN_GetDeviceSettings((void*)mockCtx, pInput, pOutput);

    free(pInput);
    free(pOutput);
    free(mockCtx);
}

TEST_F(CcspHomeSecurityHDKAdiFixture, HDK_Method_PN_SetRouterSettings_CASE_1) {
    HDK_Context* mockCtx = createMockHDK_Context();
    HDK_Struct* pInput = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pInput, nullptr);
    HDK_Struct* pOutput = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pOutput, nullptr);

    pOutput->pHead = nullptr;
    pOutput->pTail = nullptr;

    HDK_Member__STRING__* pMember1 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember1, nullptr);

    pMember1->node.element = HDK_Element_PN_DomainName;
    pMember1->node.type = HDK_Type__STRING__;
    pMember1->node.pNext = nullptr;
    pMember1->pszValue = strdup(".com");

    pInput->pHead = (HDK_Member*)pMember1;
    pInput->pTail = (HDK_Member*)pMember1;

    HDK_Method_PN_SetRouterSettings((void*)mockCtx, pInput, pOutput);
    free(pInput);
    free(pOutput);
    free(mockCtx);
}

TEST_F(CcspHomeSecurityHDKAdiFixture, HDK_Method_PN_SetRouterSettings_CASE_2) {
    HDK_Context* mockCtx = createMockHDK_Context();
    HDK_Struct* pInput = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pInput, nullptr);
    HDK_Struct* pOutput = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pOutput, nullptr);

    pOutput->pHead = nullptr;
    pOutput->pTail = nullptr;

    HDK_Member__STRING__* pMember1 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember1, nullptr);

    HDK_Member__INT__* pMember2 = (HDK_Member__INT__*) malloc(sizeof(HDK_Member__INT__));
    ASSERT_NE(pMember2, nullptr);

    pMember1->node.element = HDK_Element_PN_DomainName;
    pMember1->node.type = HDK_Type__STRING__;
    pMember1->node.pNext = (HDK_Member*)pMember2;
    pMember1->pszValue = strdup("");

    pMember2->node.element = HDK_Element_PN_Enabled;
    pMember2->node.type = HDK_Type__BOOL__;
    pMember2->node.pNext = nullptr;
    pMember2->iValue = 0;

    pInput->pHead = (HDK_Member*)pMember1;
    pInput->pTail = (HDK_Member*)pMember2;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_SetParamVal(_, _, _, _, _)).WillRepeatedly(Return(1));

    HDK_Method_PN_SetRouterSettings((void*)mockCtx, pInput, pOutput);
    free(pMember1);
    free(pMember2);
    free(pInput);
    free(pOutput);
    free(mockCtx);
}

TEST_F(CcspHomeSecurityHDKAdiFixture, HDK_Method_PN_SetRouterSettings_CASE_3) {
    HDK_Context* mockCtx = createMockHDK_Context();
    HDK_Struct* pInput = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pInput, nullptr);
    HDK_Struct* pOutput = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pOutput, nullptr);

    pOutput->pHead = nullptr;
    pOutput->pTail = nullptr;

    HDK_Member__STRING__* pMember1 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember1, nullptr);

    HDK_Member__INT__* pMember2 = (HDK_Member__INT__*) malloc(sizeof(HDK_Member__INT__));
    ASSERT_NE(pMember2, nullptr);

    HDK_Member__INT__* pMember3 = (HDK_Member__INT__*) malloc(sizeof(HDK_Member__INT__));
    ASSERT_NE(pMember3, nullptr);

    HDK_Member__INT__* pMember4 = (HDK_Member__INT__*) malloc(sizeof(HDK_Member__INT__));
    ASSERT_NE(pMember4, nullptr);

    HDK_Member__INT__* pMember5 = (HDK_Member__INT__*) malloc(sizeof(HDK_Member__INT__));
    ASSERT_NE(pMember5, nullptr);

    pMember1->node.element = HDK_Element_PN_DomainName;
    pMember1->node.type = HDK_Type__STRING__;
    pMember1->node.pNext = (HDK_Member*)pMember2;
    pMember1->pszValue = strdup("");

    pMember2->node.element = HDK_Element_PN_Enabled;
    pMember2->node.type = HDK_Type__BOOL__;
    pMember2->node.pNext = (HDK_Member*)pMember3;
    pMember2->iValue = 0;

    pMember3->node.element = HDK_Element_PN_ManageRemote;
    pMember3->node.type = HDK_Type__BOOL__;
    pMember3->node.pNext = (HDK_Member*)pMember4;
    pMember3->iValue = 1;

    pMember4->node.element = HDK_Element_PN_RemoteSSL;
    pMember4->node.type = HDK_Type__BOOL__;
    pMember4->node.pNext = (HDK_Member*)pMember5;
    pMember4->iValue = 1;

    pMember5->node.element = HDK_Element_PN_RemotePort;
    pMember5->node.type = HDK_Type__INT__;
    pMember5->node.pNext = nullptr;
    pMember5->iValue = 101;

    pInput->pHead = (HDK_Member*)pMember1;
    pInput->pTail = (HDK_Member*)pMember5;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_SetParamVal(_, StrEq("Device.UserInterface.X_CISCO_COM_RemoteAccess.HttpEnable"), _, _, _))
    .Times(1).WillOnce(Return(0));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_SetParamVal(_, StrEq("Device.UserInterface.X_CISCO_COM_RemoteAccess.HttpsEnable"), _, _, _))
    .Times(1).WillOnce(Return(0));

    char mockVal[] = "true";
    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.UserInterface.X_CISCO_COM_RemoteAccess.HttpEnable"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockVal, mockVal + strlen(mockVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_SetParamVal(_, StrEq("Device.UserInterface.X_CISCO_COM_RemoteAccess.HttpPort"), _, _, _))
    .Times(1).WillOnce(Return(0));

    HDK_Method_PN_SetRouterSettings((void*)mockCtx, pInput, pOutput);
    free(pMember1);
    free(pMember2);
    free(pMember3);
    free(pMember4);
    free(pMember5);
    free(pInput);
    free(pOutput);
    free(mockCtx);
}

TEST_F(CcspHomeSecurityHDKAdiFixture, HDK_Method_PN_SetDeviceSettings2) {
    HDK_Context* mockCtx = createMockHDK_Context();
    HDK_Struct* pInput = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pInput, nullptr);
    HDK_Struct* pOutput = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pOutput, nullptr);

    pOutput->pHead = nullptr;
    pOutput->pTail = nullptr;

    HDK_Member__STRING__* pMember1 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember1, nullptr);

    HDK_Member__STRING__* pMember2 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember2, nullptr);

    pMember1->node.element = HDK_Element_PN_TimeZone;
    pMember1->node.type = HDK_Type__STRING__;
    pMember1->node.pNext = (HDK_Member*)pMember2;
    pMember1->pszValue = strdup("");

    pMember2->node.element = HDK_Element_PN_Username;
    pMember2->node.type = HDK_Type__STRING__;
    pMember2->node.pNext = nullptr;
    pMember2->pszValue = strdup("admin");

    pInput->pHead = (HDK_Member*)pMember1;
    pInput->pTail = (HDK_Member*)pMember2;

    char mockTimeZone[] = "";
    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.Time.LocalTimeZone"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockTimeZone, mockTimeZone + strlen(mockTimeZone) + 1),
             Return(0)
    ));

    HDK_Method_PN_SetDeviceSettings2((void*)mockCtx, pInput, pOutput);
    free(pInput);
    free(pOutput);
    free(mockCtx);
}

TEST_F(CcspHomeSecurityHDKAdiFixture, HDK_Method_PN_GetWLanRadioSettings_CASE1) {
    HDK_Context* mockCtx = createMockHDK_Context();
    HDK_Struct* pInput = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pInput, nullptr);

    HDK_Struct* pOutput = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pOutput, nullptr);

    //Mock for HDK_Device_GetValue(pDeviceCtx, pOutput, HDK_DeviceValue_WLanEnabled, pInput)
    HDK_Member__STRING__* pMember1 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember1, nullptr);

    pMember1->node.element = HDK_Element_PN_RadioID;
    pMember1->node.type = HDK_Type__STRING__;
    pMember1->node.pNext = nullptr;
    pMember1->pszValue = strdup("Radio0");

    pInput->pHead = (HDK_Member*)pMember1;
    pInput->pTail = (HDK_Member*)pMember1;

    pOutput->pHead = nullptr;
    pOutput->pTail = nullptr;

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

    HDK_Method_PN_GetWLanRadioSettings(mockCtx, pInput, pOutput);

    free(pMember1->pszValue);
    free(pMember1);
    free(pInput);
    free(pOutput);
    free(mockCtx);
}

TEST_F(CcspHomeSecurityHDKAdiFixture, HDK_Method_PN_GetWLanRadioSettings_CASE2) {
    HDK_Context* mockCtx = createMockHDK_Context();
    HDK_Struct* pInput = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pInput, nullptr);

    HDK_Struct* pOutput = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pOutput, nullptr);

    //Mock for HDK_Device_GetValue(pDeviceCtx, pOutput, HDK_DeviceValue_WLanEnabled, pInput)
    HDK_Member__STRING__* pMember1 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember1, nullptr);

    pMember1->node.element = HDK_Element_PN_RadioID;
    pMember1->node.type = HDK_Type__STRING__;
    pMember1->node.pNext = nullptr;
    pMember1->pszValue = strdup("Radio0");

    pInput->pHead = (HDK_Member*)pMember1;
    pInput->pTail = (HDK_Member*)pMember1;

    pOutput->pHead = nullptr;
    pOutput->pTail = nullptr;

    //mock for HDK_Device_GetValue(pDeviceCtx, &sTemp, HDK_DeviceValue_RadioInfos, 0)
    char mockPathVal[] = "Device.WiFi.Radio.1";
    char mockAlias[] = "Radio0";
    char mockOpStd[] = "2.4GHz";
    char mockSupportedStandards[] = "a,b,g,n";
    char mockPossibleChannels[] = "1,2,3,4,5,6,7,8,9,10,11";
    char mockApPathVal[] = "Device.WiFi.AccessPoint.3";
    char mockSupportedModes[] = "None,WEP-64,WEP-128,WPA-Personal,WPA2-Personal,WPA-WPA2-Personal,WPA-Enterprise,WPA2-Enterprise,WPA-WPA2-Enterprise";
    char mockOpStds[] = "a";
    char mockTrue[] = "true";

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_FindObjectIns(_, _, _, _, _, _))
    .WillRepeatedly(testing::DoAll(
        testing::Invoke([&](MBusObj_t *, const char *, const char *, const char *, char insPath[][MAX_PATH_NAME], int *insNum) {
            strcpy(insPath[0], "Device.WiFi.Radio.1.");
            *insNum = 1;
        }),
        Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .WillRepeatedly(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("Alias"), _, _))
    .WillRepeatedly(testing::DoAll(
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

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("Enable"), _, _))
    .Times(1).WillOnce(Return(1));

    HDK_Method_PN_GetWLanRadioSettings(mockCtx, pInput, pOutput);

    free(pMember1->pszValue);
    free(pMember1);
    free(pInput);
    free(pOutput);
    free(mockCtx);
}

TEST_F(CcspHomeSecurityHDKAdiFixture, HDK_Method_PN_GetWLanRadioSettings_CASE3) {
    HDK_Context* mockCtx = createMockHDK_Context();
    HDK_Struct* pInput = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pInput, nullptr);

    HDK_Struct* pOutput = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pOutput, nullptr);

    //Mock for HDK_Device_GetValue(pDeviceCtx, pOutput, HDK_DeviceValue_WLanEnabled, pInput)
    HDK_Member__STRING__* pMember1 = (HDK_Member__STRING__*) malloc(sizeof(HDK_Member__STRING__));
    ASSERT_NE(pMember1, nullptr);

    pMember1->node.element = HDK_Element_PN_RadioID;
    pMember1->node.type = HDK_Type__STRING__;
    pMember1->node.pNext = nullptr;
    pMember1->pszValue = strdup("Radio0");

    pInput->pHead = (HDK_Member*)pMember1;
    pInput->pTail = (HDK_Member*)pMember1;

    pOutput->pHead = nullptr;
    pOutput->pTail = nullptr;

    //mock for HDK_Device_GetValue(pDeviceCtx, &sTemp, HDK_DeviceValue_RadioInfos, 0)
    char mockPathVal[] = "Device.WiFi.Radio.1";
    char mockAlias[] = "Radio0";
    char mockOpStd[] = "2.4GHz";
    char mockSupportedStandards[] = "a,b,g,n";
    char mockPossibleChannels[] = "1,2,3,4,5,6,7,8,9,10,11";
    char mockApPathVal[] = "Device.WiFi.AccessPoint.3";
    char mockSupportedModes[] = "None,WEP-64,WEP-128,WPA-Personal,WPA2-Personal,WPA-WPA2-Personal,WPA-Enterprise,WPA2-Enterprise,WPA-WPA2-Enterprise";
    char mockOpStds[] = "a";
    char mockTrue[] = "true";
    char mockMAC[] = "00:00:00:00:00:00";
    char mockSSID[] = "test_SSID";
    char mockChannelBW[] = "20MHz";
    char mockChannel[] = "1";
    char mockSecChnl[] = "AboveControlChannel";

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_FindObjectIns(_, _, _, _, _, _))
    .WillRepeatedly(testing::DoAll(
        testing::Invoke([&](MBusObj_t *, const char *, const char *, const char *, char insPath[][MAX_PATH_NAME], int *insNum) {
            strcpy(insPath[0], "Device.WiFi.Radio.1.");
            *insNum = 1;
        }),
        Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, StrEq("Device.X_CISCO_COM_MultiLAN.HomeSecurityWiFiRadio"), _, _))
    .WillRepeatedly(testing::DoAll(
             testing::SetArrayArgument<2>(mockPathVal, mockPathVal + strlen(mockPathVal) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("Alias"), _, _))
    .WillRepeatedly(testing::DoAll(
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

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("Enable"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockTrue, mockTrue + strlen(mockTrue) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("OperatingStandards"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockOpStds, mockOpStds + strlen(mockOpStds) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("MACAddress"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockMAC, mockMAC + strlen(mockMAC) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("SSID"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockSSID, mockSSID + strlen(mockSSID) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("SSIDAdvertisementEnabled"), _, _))
    .Times(1)
    .WillOnce(testing::DoAll(
             testing::SetArrayArgument<2>(mockTrue, mockTrue + strlen(mockTrue) + 1),
             Return(0)
    ));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("OperatingChannelBandwidth"), _, _))
    .Times(1).WillOnce(Return(1));

    // EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("OperatingChannelBandwidth"), _, _))
    // .Times(testing::AtLeast(1))
    // .WillRepeatedly(testing::DoAll(
    //     testing::SetArrayArgument<2>(mockChannelBW, mockChannelBW + strlen(mockChannelBW) + 1),
    //     Return(0)
    // ));


    // EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("Channel"), _, _))
    // .Times(1)
    // .WillOnce(testing::DoAll(
    //          testing::SetArrayArgument<2>(mockChannel, mockChannel + strlen(mockChannel) + 1),
    //          Return(0)
    // ));

    // EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("ExtensionChannel"), _, _))
    // .Times(1)
    // .WillOnce(testing::DoAll(
    //          testing::SetArrayArgument<2>(mockSecChnl, mockSecChnl + strlen(mockSecChnl) + 1),
    //          Return(0)
    // ));

    // EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, HasSubstr("WMMEnable"), _, _))
    // .Times(1)
    // .WillOnce(testing::DoAll(
    //          testing::SetArrayArgument<2>(mockTrue, mockTrue + strlen(mockTrue) + 1),
    //          Return(0)
    // ));

    HDK_Method_PN_GetWLanRadioSettings(mockCtx, pInput, pOutput);

    free(pMember1->pszValue);
    free(pMember1);
    free(pInput);
    free(pOutput);
    free(mockCtx);
}
