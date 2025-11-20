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
    int ValidatSecuredPassword(char *pszPassword);
    int HDK_Signal_Hander(int signal);
}

class CcspHomeSecurityHDKContextTestFixture : public ::testing::Test {
protected:
    void SetUp() override {
        g_rdkconfigMock = new rdkconfigMock();
        g_HdkCcspMbusMock = new HdkCcspMbusMock();
    }

    void TearDown() override {
        delete g_rdkconfigMock;
        delete g_HdkCcspMbusMock;
        g_rdkconfigMock = nullptr;
        g_HdkCcspMbusMock = nullptr;
    }
};

TEST_F(CcspHomeSecurityHDKContextTestFixture, mbus_init) {
    MBusObj_t *obj1 = nullptr;
    MBusObj_t *obj2 = (MBusObj_t*)malloc(sizeof(MBusObj_s));

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_Create(_, _, _, _)).Times(2)
    .WillOnce(Return(obj1))
    .WillOnce(Return(obj2));
    printf("Create mbus failed, retry after 3s\n");

    MBusObj_t *expObj = mbus_init();
    EXPECT_EQ(expObj, obj2);
    free(obj2);
    obj2 = nullptr;
}

TEST_F(CcspHomeSecurityHDKContextTestFixture, homesecurity_timeout_handler) {
    
    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, _, _, _)).Times(1).WillOnce(Return(1));

    homesecurity_timeout_handler();
}

TEST_F(CcspHomeSecurityHDKContextTestFixture, HDK_Context_Init) {
    void* pCtx;
    FILE* pfhRead = tmpfile();
    FILE* pfhWrite = tmpfile();

    int result = HDK_Context_Init(&pCtx, pfhRead, pfhWrite);
    EXPECT_EQ(result, 1);
}

TEST_F(CcspHomeSecurityHDKContextTestFixture, HDK_Signal_Hander) {
    int result;

    EXPECT_CALL(*g_HdkCcspMbusMock, MBus_GetParamVal(_, _, _, _)).Times(1).WillOnce(Return(1));

    result = HDK_Signal_Hander(1);
    EXPECT_EQ(result, -1);
}

TEST_F(CcspHomeSecurityHDKContextTestFixture, HDK_Context_Free_nullptr) {
    HDK_Context* mockContext = nullptr;
    int fCommit = 0;

    HDK_Context_Free((void*)mockContext, fCommit);
}

TEST_F(CcspHomeSecurityHDKContextTestFixture, HDK_Context_Free_ValidPtr) {
    HDK_Context* mockContext = createMockHDK_Context();
    int fCommit = 0;

    HDK_Context_Free((void*)mockContext, fCommit);
}

TEST_F(CcspHomeSecurityHDKContextTestFixture, ValidatSecuredPassword_validPwd) {
    int result;
    char mockPwd[64] = "password";

    /*EXPECT_CALL(*g_rdkconfigMock, rdkconfig_get(_, _, _))
        .Times(1)
        .WillOnce(testing::DoAll(
            testing::Invoke([&](uint8_t** sbuff, size_t* sbuffsz, const char* refname) {
                const char* mockPassword = "password";
                // Allocate memory for the password and copy it
                *sbuff = reinterpret_cast<uint8_t*>(malloc(strlen(mockPassword) + 1));
                strcpy(reinterpret_cast<char*>(*sbuff), mockPassword);
                *sbuffsz = strlen(mockPassword);
            }),
            Return(0)
        ));

    EXPECT_CALL(*g_rdkconfigMock, rdkconfig_free(_, _))
        .Times(1)
        .WillOnce(testing::Invoke([](uint8_t** sbuff, size_t sbuffsz) {
            // Free the allocated memory
            free(*sbuff);
            *sbuff = nullptr;
            return RDKCONFIG_OK;
        }));*/

    result = ValidatSecuredPassword(mockPwd);
    EXPECT_EQ(result, 1);
}

TEST_F(CcspHomeSecurityHDKContextTestFixture, ValidatSecuredPassword_invalidPwd) {
    int result;
    char mockPwd[64] = "passwrd";

    /*EXPECT_CALL(*g_rdkconfigMock, rdkconfig_get(_, _, _))
        .Times(1)
        .WillOnce(testing::DoAll(
            testing::Invoke([&](uint8_t** sbuff, size_t* sbuffsz, const char* refname) {
                const char* mockPassword = "password";
                // Allocate memory for the password and copy it
                *sbuff = reinterpret_cast<uint8_t*>(malloc(strlen(mockPassword) + 1));
                strcpy(reinterpret_cast<char*>(*sbuff), mockPassword);
                *sbuffsz = strlen(mockPassword);
            }),
            Return(0)
        ));

    EXPECT_CALL(*g_rdkconfigMock, rdkconfig_free(_, _))
        .Times(1)
        .WillOnce(testing::Invoke([](uint8_t** sbuff, size_t sbuffsz) {
            // Free the allocated memory
            free(*sbuff);
            *sbuff = nullptr;
            return RDKCONFIG_FAIL;
        }));*/

    result = ValidatSecuredPassword(mockPwd);
    EXPECT_EQ(result, 1);
}

TEST_F(CcspHomeSecurityHDKContextTestFixture, HDK_Context_Authenticate) {
    char pszUsername[64] = "hnapadmin";
    char pszPassword[64] = "password";

    /*EXPECT_CALL(*g_rdkconfigMock, rdkconfig_get(_, _, _))
        .Times(1)
        .WillOnce(testing::DoAll(
            testing::Invoke([&](uint8_t** sbuff, size_t* sbuffsz, const char* refname) {
                const char* mockPassword = "password";
                // Allocate memory for the password and copy it
                *sbuff = reinterpret_cast<uint8_t*>(malloc(strlen(mockPassword) + 1));
                strcpy(reinterpret_cast<char*>(*sbuff), mockPassword);
                *sbuffsz = strlen(mockPassword);
            }),
            Return(0)
        ));

    EXPECT_CALL(*g_rdkconfigMock, rdkconfig_free(_, _))
        .Times(1)
        .WillOnce(testing::Invoke([](uint8_t** sbuff, size_t sbuffsz) {
            // Free the allocated memory
            free(*sbuff);
            *sbuff = nullptr;
            return RDKCONFIG_OK;
        }));*/

    int result = HDK_Context_Authenticate(nullptr, pszUsername, pszPassword);
    EXPECT_EQ(result, 0);
}
