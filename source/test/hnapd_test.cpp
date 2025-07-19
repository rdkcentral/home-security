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
    int CcspHomeSecurity_main(int argc, char *argv[]);
    void HTTP_ParseHeaders(FILE* pfh, char* pszBuf, unsigned int cbBuf, int* pGet, char** ppszLocation,
                              unsigned int* pContentLength, char** ppszSoapAction, char** ppszAuth);
    int HTTP_AuthDecode(char* pszHTTPAuth, char* pszAuthBuf, unsigned int cbAuthBuf,
                              char** ppszUsername, char** ppszPassword);
    void HTTP_HandleRequest(FILE* pfhRead, FILE* pfhWrite);
    void alarm_handler(int signal);
}

class CcspHomeSecurityHnapdTestFixture : public ::testing::Test {
protected:
    void SetUp() override {
        g_syscfgMock = new SyscfgMock();
        g_securewrapperMock = new SecureWrapperMock();
        g_socketMock = new SocketMock();
        g_fileIOMock = new FileIOMock();
        g_HdkCcspMbusMock = new HdkCcspMbusMock();
    }

    void TearDown() override {
        delete g_syscfgMock;
        delete g_securewrapperMock;
        delete g_socketMock;
        delete g_fileIOMock;
        delete g_HdkCcspMbusMock;
        g_syscfgMock = nullptr;
        g_securewrapperMock = nullptr;
        g_socketMock = nullptr;
        g_fileIOMock = nullptr;
        g_HdkCcspMbusMock = nullptr;
    }
};

// Helper function to write the HTTP headers to a file
void WriteMockHttpHeaders(FILE* file, const char* headers) {
    if (file == NULL || headers == NULL) {
        return;
    }

    fwrite(headers, 1, strlen(headers), file);
    fflush(file);
    rewind(file);  // Reset file pointer to the beginning
}

TEST_F(CcspHomeSecurityHnapdTestFixture, HTTP_ParseHeaders) {
    FILE* file = tmpfile();
    ASSERT_NE(file, nullptr);
    const char headers[] =
    "GET /test/path HTTP/1.1\r\n"
    "Content-Length: 123\r\n"
    "Authorization: Basic YWxhZGRpbjpvcGVuc2VzYW1l\r\n"
    "SOAPAction: \"urn:test:action\"\r\n"
    "\r\n";
    WriteMockHttpHeaders(file, headers);

    char buffer[512];
    int isGet = 0;
    char* location = nullptr;
    unsigned int contentLength = 0;
    char* soapAction = nullptr;
    char* auth = nullptr;

    EXPECT_CALL(*g_fileIOMock, fread(_, 1, 1, _))
    .Times(testing::AtLeast(1))
    .WillRepeatedly(testing::Invoke([headers](void* ptr, size_t size, size_t count, FILE*) {
        static size_t index = 0;
        if (index < sizeof(headers) - 1) {
            *(static_cast<char*>(ptr)) = headers[index];
            index++;
            return 1;
        }
        return 0;
    }));

    EXPECT_CALL(*g_fileIOMock, fclose(_)).WillRepeatedly(Return(0));

    HTTP_ParseHeaders(file, buffer, sizeof(buffer), &isGet, &location, &contentLength, &soapAction, &auth);

    EXPECT_EQ(isGet, 1);
    EXPECT_STREQ(location, "/test/path");
    EXPECT_EQ(contentLength, 123);
    EXPECT_STREQ(soapAction, "urn:test:action");
    EXPECT_STREQ(auth, "Basic YWxhZGRpbjpvcGVuc2VzYW1l");

    fclose(file);
}

TEST_F(CcspHomeSecurityHnapdTestFixture, HTTP_AuthDecode) {
    char authBuffer[64];
    char* username;
    char* password;
    const char* authString = "Basic YWRtaW46cGFzc3dvcmQ=";  // "admin:password" encoded in Base64

    memset(authBuffer, 0, sizeof(authBuffer));
    username = nullptr;
    password = nullptr;

    int result = HTTP_AuthDecode(const_cast<char*>(authString), authBuffer, sizeof(authBuffer), &username, &password);

    EXPECT_EQ(result, 1);
    EXPECT_STREQ(username, "admin");
    EXPECT_STREQ(password, "password");
}

TEST_F(CcspHomeSecurityHnapdTestFixture, alarm_handler) {
    int signum = SIGALRM;
    char buf[] = "2";

    EXPECT_CALL(*g_syscfgMock, syscfg_get(_, StrEq("HomeSecurityEthernet4Flag"), _, _))
        .Times(1)
        .WillOnce(DoAll(testing::SetArrayArgument<2>(buf, buf + sizeof(buf)), Return(0)));

    alarm_handler(signum);
}

TEST_F(CcspHomeSecurityHnapdTestFixture, HTTP_HandleRequest_CASE_1) {
    FILE* pfhRead = tmpfile();
    FILE* pfhWrite = tmpfile();
    ASSERT_NE(pfhRead, nullptr);
    ASSERT_NE(pfhWrite, nullptr);
    const char headers[] =
    "GET /test/path HTTP/1.1\r\n"
    "Content-Length: 123\r\n"
    "Authorization: Basic YWxhZGRpbjpvcGVuc2VzYW1l\r\n"
    "\r\n";
    WriteMockHttpHeaders(pfhRead, headers);

    EXPECT_CALL(*g_fileIOMock, fread(_, 1, 1, _))
    .Times(testing::AtLeast(1))
    .WillRepeatedly(testing::Invoke([headers](void* ptr, size_t size, size_t count, FILE*) {
        static size_t index = 0;
        if (index < sizeof(headers) - 1) {
            *(static_cast<char*>(ptr)) = headers[index];
            index++;
            return 1;
        }
        return 0;
    }));

    EXPECT_CALL(*g_fileIOMock, fclose(_)).WillRepeatedly(Return(0));

    HTTP_HandleRequest(pfhRead, pfhWrite);

    fclose(pfhRead);
    fclose(pfhWrite);
}

TEST_F(CcspHomeSecurityHnapdTestFixture, HTTP_HandleRequest_CASE_2) {
    FILE* pfhRead = tmpfile();
    FILE* pfhWrite = tmpfile();
    ASSERT_NE(pfhRead, nullptr);
    ASSERT_NE(pfhWrite, nullptr);

    const char headers[] =
    "GET /HNAP1/ HTTP/1.1\r\n"
    "Content-Length: 123\r\n"
    "Authorization: Basic YWxhZGRpbjpvcGVuc2VzYW1l\r\n"
    "SOAPAction: \"http://purenetworks.com/HNAP1/GetDeviceSettings\"\r\n"
    "\r\n";
    WriteMockHttpHeaders(pfhRead, headers);

    EXPECT_CALL(*g_fileIOMock, fread(_, 1, 1, _))
    .Times(testing::AtLeast(1))
    .WillRepeatedly(testing::Invoke([headers](void* ptr, size_t size, size_t count, FILE*) {
        static size_t index = 0;
        if (index < sizeof(headers) - 1) {
            *(static_cast<char*>(ptr)) = headers[index];
            index++;
            return 1; // Return 1 byte read successfully
        }
        return 0; // Return 0 when end of headers is reached (EOF)
    }));

    EXPECT_CALL(*g_fileIOMock, fclose(_)).WillRepeatedly(Return(0));

    HTTP_HandleRequest(pfhRead, pfhWrite);

    fclose(pfhRead);
    fclose(pfhWrite);
}

TEST_F(CcspHomeSecurityHnapdTestFixture, CcspHomeSecurity_main_FAIL_1) {
    char arg1[] = "CcspHomeSecurity";
    char arg2[] = "8081";
    char *argv[] = {arg1, arg2};
    int argc = 1;

    int result = CcspHomeSecurity_main(argc, argv);
    EXPECT_EQ(result, 1);
}

TEST_F(CcspHomeSecurityHnapdTestFixture, CcspHomeSecurity_main_FAIL_2) {
    char arg1[] = "CcspHomeSecurity";
    char arg2[] = "8081";
    char *argv[] = {arg1, arg2};
    int argc = 2;

    EXPECT_CALL(*g_syscfgMock, syscfg_init()).WillOnce(Return(0));
    EXPECT_CALL(*g_socketMock, socket(_, _, _)).WillOnce(Return(-1));

    int result = CcspHomeSecurity_main(argc, argv);
    EXPECT_EQ(result, 1);
}

TEST_F(CcspHomeSecurityHnapdTestFixture, CcspHomeSecurity_main_FAIL_3) {
    char arg1[] = "CcspHomeSecurity";
    char arg2[] = "8081";
    char *argv[] = {arg1, arg2};
    int argc = 2;
    char mockIP[] = "172.16.12.1\n";

    EXPECT_CALL(*g_syscfgMock, syscfg_init()).Times(1).WillOnce(Return(0));
    EXPECT_CALL(*g_socketMock, socket(_, _, _)).Times(1).WillOnce(Return(1));
    EXPECT_CALL(*g_securewrapperMock, v_secure_popen(_, HasSubstr("ifconfig brlan1") , _)).Times(1).WillOnce(Return((FILE*)0x1));
    EXPECT_CALL(*g_fileIOMock, fgets(_, _, _))
        .Times(1)
        .WillOnce(testing::DoAll(
             testing::SetArrayArgument<0>(mockIP, mockIP + strlen(mockIP) + 1),
            Return(static_cast<char*>(mockIP))
        ));
    EXPECT_CALL(*g_securewrapperMock, v_secure_pclose(_)).WillRepeatedly(Return(1));

    int result = CcspHomeSecurity_main(argc, argv);
    EXPECT_EQ(result, 1);
}

TEST_F(CcspHomeSecurityHnapdTestFixture, CcspHomeSecurity_main_FAIL_4) {
    char arg1[] = "CcspHomeSecurity";
    char arg2[] = "8081";
    char *argv[] = {arg1, arg2};
    int argc = 2;
    char mockIP[] = "172.16.12.266";

    EXPECT_CALL(*g_syscfgMock, syscfg_init()).Times(1).WillOnce(Return(0));
    EXPECT_CALL(*g_socketMock, socket(_, _, _)).Times(1).WillOnce(Return(1));
    EXPECT_CALL(*g_securewrapperMock, v_secure_popen(_, HasSubstr("ifconfig brlan1") , _)).Times(1).WillOnce(Return((FILE*)0x1));
    EXPECT_CALL(*g_fileIOMock, fgets(_, _, _))
        .Times(1)
        .WillOnce(testing::DoAll(
             testing::SetArrayArgument<0>(mockIP, mockIP + strlen(mockIP) + 1),
            Return(static_cast<char*>(mockIP))
        ));
    EXPECT_CALL(*g_securewrapperMock, v_secure_pclose(_)).WillRepeatedly(Return(-1));

    int result = CcspHomeSecurity_main(argc, argv);
    EXPECT_EQ(result, 1);
}

TEST_F(CcspHomeSecurityHnapdTestFixture, CcspHomeSecurity_main_FAIL_5) {
    char arg1[] = "CcspHomeSecurity";
    char arg2[] = "8081";
    char *argv[] = {arg1, arg2};
    int argc = 2;

    EXPECT_CALL(*g_syscfgMock, syscfg_init()).Times(1).WillOnce(Return(0));
    EXPECT_CALL(*g_socketMock, socket(_, _, _)).Times(1).WillOnce(Return(1));
    EXPECT_CALL(*g_securewrapperMock, v_secure_popen(_, HasSubstr("ifconfig brlan1") , _)).Times(1).WillOnce(Return((FILE*)0x1));
    EXPECT_CALL(*g_fileIOMock, fgets(_, _, _)).Times(1).WillOnce(Return(nullptr));
    EXPECT_CALL(*g_securewrapperMock, v_secure_pclose(_)).WillRepeatedly(Return(1));

    int result = CcspHomeSecurity_main(argc, argv);
    EXPECT_EQ(result, 1);
}

TEST_F(CcspHomeSecurityHnapdTestFixture, CcspHomeSecurity_main_FAIL_6) {
    char arg1[] = "CcspHomeSecurity";
    char arg2[] = "8081";
    char *argv[] = {arg1, arg2};
    int argc = 2;

    EXPECT_CALL(*g_syscfgMock, syscfg_init()).Times(1).WillOnce(Return(0));
    EXPECT_CALL(*g_socketMock, socket(_, _, _)).Times(1).WillOnce(Return(1));
    EXPECT_CALL(*g_securewrapperMock, v_secure_popen(_, HasSubstr("ifconfig brlan1") , _)).Times(1).WillOnce(Return(nullptr));

    int result = CcspHomeSecurity_main(argc, argv);
    EXPECT_EQ(result, 1);
}
