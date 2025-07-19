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

class CcspHomeSecurityHDKEncodeTestFixture : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

TEST_F(CcspHomeSecurityHDKEncodeTestFixture, HDK_DecodeBase64Done) {
    int state = 0;

    int result = HDK_DecodeBase64Done(state);
    EXPECT_EQ(result, 0);
}

TEST_F(CcspHomeSecurityHDKEncodeTestFixture, HDK_EncodeToBuffer) {
    const char* input = "HelloWorld";
    unsigned int inputLen = strlen(input);

    char output[20] = {0};
    char* pEncodeCtx = output;

    int result = HDK_EncodeToBuffer(&pEncodeCtx, const_cast<char*>(input), inputLen);

    EXPECT_EQ(result, inputLen);

    EXPECT_STREQ(output, input);

    EXPECT_EQ(pEncodeCtx, output + inputLen);
}

TEST_F(CcspHomeSecurityHDKEncodeTestFixture, HDK_EncodeString_1) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    char pBuf[] = "<message>Special characters: \" & ' < ></message>";
    char outputString[] = "&lt;message&gt;Special characters: &quot; &amp; &apos; &lt; &gt;&lt;/message&gt;";
    
    int cbBuf = strlen(pBuf);

    HDK_WriteBuf_EncodeContext *encodeCtx = (HDK_WriteBuf_EncodeContext*)malloc(sizeof(HDK_WriteBuf_EncodeContext));
    encodeCtx->pDeviceCtx = mockDeviceCtx;
    encodeCtx->fNoWrite = 0;

    int result = HDK_EncodeString(HDK_WriteBuf_Encode, (void*)encodeCtx, pBuf, cbBuf);

    EXPECT_EQ(result, strlen(outputString));
}

TEST_F(CcspHomeSecurityHDKEncodeTestFixture, HDK_EncodeString) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    char pBuf[] = "HelloWorld";
    char outputString[] = "HelloWorld";
    
    int cbBuf = strlen(pBuf);

    HDK_WriteBuf_EncodeContext *encodeCtx = (HDK_WriteBuf_EncodeContext*)malloc(sizeof(HDK_WriteBuf_EncodeContext));
    encodeCtx->pDeviceCtx = mockDeviceCtx;
    encodeCtx->fNoWrite = 0;

    int result = HDK_EncodeString(HDK_WriteBuf_Encode, (void*)encodeCtx, pBuf, cbBuf);

    EXPECT_EQ(result, strlen(outputString));
}

TEST_F(CcspHomeSecurityHDKEncodeTestFixture, HDK_EncodeBase64_NoFunction) {
    char input[] = "empty_string";
    char encodedOutput[128] = {};
    int inputLen = strlen(input);
    int state = 0, prev = 0;

    int res = HDK_EncodeBase64(nullptr, &encodedOutput, input, inputLen, &state, &prev);

    const char* expectedEncodedOutput = "";

    EXPECT_STREQ(encodedOutput, expectedEncodedOutput);
}

TEST_F(CcspHomeSecurityHDKEncodeTestFixture, HDK_EncodeBase64Done)
{
    char encodedOutput[128] = {};
    void* pEncodeCtx = &encodedOutput;

    int state = 1;
    int prev = 19;

    int result = HDK_EncodeBase64Done(nullptr, pEncodeCtx, state, prev);

    EXPECT_EQ(result, 3);
}

TEST_F(CcspHomeSecurityHDKEncodeTestFixture, HDK_DecodeBase64) {
    char buffer[10] = {0};
    int state = 0;
    int prev = 0;

    // Base64 string: "SGVsbG8="
    // Decodes to: "Hello"
    char input[] = "SGVsbG8=";
    int expectedDecodedLength = 5;
    char expectedOutput[] = "Hello";

    char* pOutput = buffer;

    int result = HDK_DecodeBase64(HDK_EncodeToBuffer, &pOutput, input, sizeof(input) - 1, &state, &prev);

    EXPECT_EQ(result, expectedDecodedLength);
    EXPECT_STREQ(buffer, expectedOutput);
}
