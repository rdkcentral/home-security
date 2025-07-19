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
    void SendHNAPResponse(void* pDeviceCtx, HDK_Struct* pStruct, HDK_Struct* pInputStruct, int fErrorOutput);
    void SendErrorResponse(void* pDeviceCtx, HDK_ParseError parseError);
    void ElementStartHandler(void* pDeviceCtx, const xmlChar* pszElement, const xmlChar* pszPrefix,
                            const xmlChar* pszNamespace, int nNamespaces, const xmlChar** ppszNamespaces,
                            int nAttributes, int nDefaulted, const xmlChar** ppszAttributes);
    void ElementEndHandler(void* pDeviceCtx, const xmlChar* pszElement, const xmlChar* pszPrefix, const xmlChar* pszNamespace);
    void ElementValueHandler(void* pDeviceCtx, const xmlChar* pValue, int cbValue);
}

class CcspHomeSecurityHDKFixture : public ::testing::Test {
protected:
    void SetUp() override {
        g_baseapiMock = new BaseAPIMock();
        g_libxmlMock = new libxmlMock();
        g_fileIOMock = new FileIOMock();
        g_HdkCcspMbusMock = new HdkCcspMbusMock();
    }

    void TearDown() override {
        delete g_baseapiMock;
        delete g_libxmlMock;
        delete g_fileIOMock;
        delete g_HdkCcspMbusMock;
        g_baseapiMock = nullptr;
        g_libxmlMock = nullptr;
        g_fileIOMock = nullptr;
        g_HdkCcspMbusMock = nullptr;
    }
};

extern HDK_Context* createMockHDK_Context();

TEST_F(CcspHomeSecurityHDKFixture, HDK_WriteBuf) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    char pBuf[] = "Data";
    int cbBuf = strlen(pBuf);

    int result = HDK_WriteBuf((void*)mockDeviceCtx, 0, pBuf, cbBuf);
    EXPECT_EQ(result, cbBuf);
}

TEST_F(CcspHomeSecurityHDKFixture, HDK_WriteBuf_Encode) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    char pBuf[] = "Data";
    int cbBuf = strlen(pBuf);

    HDK_WriteBuf_EncodeContext *encodeCtx = (HDK_WriteBuf_EncodeContext*)malloc(sizeof(HDK_WriteBuf_EncodeContext));
    encodeCtx->pDeviceCtx = mockDeviceCtx;
    encodeCtx->fNoWrite = 0;

    int result = HDK_WriteBuf_Encode((void*)encodeCtx, pBuf, cbBuf);
    EXPECT_EQ(result, cbBuf);
}

TEST_F(CcspHomeSecurityHDKFixture, HDK_Write) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    char pBuf[] = "Data";
    int cbBuf = strlen(pBuf);

    int result = HDK_Write((void*)mockDeviceCtx, 0, pBuf);
    EXPECT_EQ(result, cbBuf);
}

TEST_F(CcspHomeSecurityHDKFixture, HDK_Format) {
    int mockVal = 5;
    HDK_Context* pDeviceCtx = createMockHDK_Context();
    int fNoWrite = 0;
    char pBuf[] = "Value: %d\n";
    int size = strlen(pBuf) - 1;

    int result = HDK_Format(pDeviceCtx, fNoWrite, pBuf, mockVal);

    EXPECT_EQ(result, size);
}

TEST_F(CcspHomeSecurityHDKFixture, HDK_IsHNAPRequest) {
    char pszPath[] = "/HNAP1/";
    int result = HDK_IsHNAPRequest(pszPath);
    EXPECT_EQ(result, 1);
}

TEST_F(CcspHomeSecurityHDKFixture, HDK_RequiresAuth_1) {
    int fGet = 0;
    char pszSoapAction[] = "http://purenetworks.com/HNAP1/GetDeviceSettings";

    int result = HDK_RequiresAuth(fGet, pszSoapAction);
    EXPECT_EQ(result, 1);
}

TEST_F(CcspHomeSecurityHDKFixture, HDK_RequiresAuth_2) {
    int fGet = 0;
    char pszSoapAction[] = "empty_string";

    int result = HDK_RequiresAuth(fGet, pszSoapAction);
    EXPECT_EQ(result, 1);
}

TEST_F(CcspHomeSecurityHDKFixture, HDK_RequiresAuth_3) {
    int fGet = 1;
    char pszSoapAction[] = "http://purenetworks.com/HNAP1/GetDeviceSettings";

    int result = HDK_RequiresAuth(fGet, pszSoapAction);
    EXPECT_EQ(result, 0);
}

TEST_F(CcspHomeSecurityHDKFixture, SendHNAPResponse) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_Struct* pInputStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    int fErrorOutput = 0;

    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    ASSERT_NE(pStruct, nullptr);

    HDK_Member__INT__* pMember1 = (HDK_Member__INT__*) malloc(sizeof(HDK_Member__INT__));
    ASSERT_NE(pMember1, nullptr);

    pMember1->node.element = HDK_Element_PN_ExternalPort;
    pMember1->node.type = HDK_Type__INT__;
    pMember1->node.pNext = nullptr;
    pMember1->iValue = 1;

    pStruct->pHead = (HDK_Member*)pMember1;
    pStruct->pTail = (HDK_Member*)pMember1;

    SendHNAPResponse((void*)mockDeviceCtx, pStruct, pInputStruct, fErrorOutput);

    free(mockDeviceCtx);
    free(pMember1);
    free(pStruct);
    free(pInputStruct);
    mockDeviceCtx = nullptr;
    pMember1 = nullptr;
    pStruct = nullptr;
    pInputStruct = nullptr;
}

TEST_F(CcspHomeSecurityHDKFixture, SendErrorResponse_CASE_1) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_ParseError parseError = HDK_ParseError_500_NoInput;

    SendErrorResponse((void*)mockDeviceCtx, parseError);

    free(mockDeviceCtx);
    mockDeviceCtx = nullptr;
}

TEST_F(CcspHomeSecurityHDKFixture, SendErrorResponse_CASE_2) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_ParseError parseError = HDK_ParseError_500_UnexpectedError;

    SendErrorResponse((void*)mockDeviceCtx, parseError);

    free(mockDeviceCtx);
    mockDeviceCtx = nullptr;
}

TEST_F(CcspHomeSecurityHDKFixture, SendErrorResponse_CASE_3) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_ParseError parseError = HDK_ParseError_500_OutOfMemory;

    SendErrorResponse((void*)mockDeviceCtx, parseError);

    free(mockDeviceCtx);
    mockDeviceCtx = nullptr;
}

TEST_F(CcspHomeSecurityHDKFixture, SendErrorResponse_CASE_4) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_ParseError parseError = HDK_ParseError_500_IOError;

    SendErrorResponse((void*)mockDeviceCtx, parseError);

    free(mockDeviceCtx);
    mockDeviceCtx = nullptr;
}

TEST_F(CcspHomeSecurityHDKFixture, SendErrorResponse_CASE_5) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_ParseError parseError = HDK_ParseError_500_XMLInvalid;

    SendErrorResponse((void*)mockDeviceCtx, parseError);

    free(mockDeviceCtx);
    mockDeviceCtx = nullptr;
}

TEST_F(CcspHomeSecurityHDKFixture, SendErrorResponse_CASE_6) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_ParseError parseError = HDK_ParseError_500_XMLUnknownElement;

    SendErrorResponse((void*)mockDeviceCtx, parseError);

    free(mockDeviceCtx);
    mockDeviceCtx = nullptr;
}

TEST_F(CcspHomeSecurityHDKFixture, SendErrorResponse_CASE_7) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_ParseError parseError = HDK_ParseError_500_XMLUnexpectedElement;

    SendErrorResponse((void*)mockDeviceCtx, parseError);

    free(mockDeviceCtx);
    mockDeviceCtx = nullptr;
}

TEST_F(CcspHomeSecurityHDKFixture, SendErrorResponse_CASE_8) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_ParseError parseError = HDK_ParseError_500_XMLInvalidValue;

    SendErrorResponse((void*)mockDeviceCtx, parseError);

    free(mockDeviceCtx);
    mockDeviceCtx = nullptr;
}

TEST_F(CcspHomeSecurityHDKFixture, SendErrorResponse_CASE_9) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_ParseError parseError = HDK_ParseError_500_XMLInvalidResponse;

    SendErrorResponse((void*)mockDeviceCtx, parseError);

    free(mockDeviceCtx);
    mockDeviceCtx = nullptr;
}

TEST_F(CcspHomeSecurityHDKFixture, SendErrorResponse_CASE_10) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_ParseError parseError = HDK_ParseError_500_XMLInvalidRequest;

    SendErrorResponse((void*)mockDeviceCtx, parseError);

    free(mockDeviceCtx);
    mockDeviceCtx = nullptr;
}

TEST_F(CcspHomeSecurityHDKFixture, SendErrorResponse_CASE_11) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_ParseError parseError = HDK_ParseError_OK;

    SendErrorResponse((void*)mockDeviceCtx, parseError);

    free(mockDeviceCtx);
    mockDeviceCtx = nullptr;
}

TEST_F(CcspHomeSecurityHDKFixture, HDK_Parse_SUCCESS) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));

    xmlParserCtxtPtr pXMLParser = (xmlParserCtxtPtr)malloc(sizeof(xmlParserCtxtPtr));
    memset(pXMLParser, 0, sizeof(xmlParserCtxtPtr));

    const char* xmlContent =
        "<Request>\n"
        "    <Action>TestAction</Action>\n"
        "    <Parameter>Value</Parameter>\n"
        "</Request>\n";

    EXPECT_CALL(*g_fileIOMock, fread(_, 1, _, _))
    .Times(1)
    .WillOnce(testing::Invoke([xmlContent](void* ptr, size_t size, size_t count, FILE*) {
        size_t contentLength = strlen(xmlContent);
        if (count >= contentLength) {
            memcpy(ptr, xmlContent, contentLength);
            return static_cast<size_t>(contentLength);
        }
        return static_cast<size_t>(0);
    }));

    EXPECT_CALL(*g_libxmlMock, xmlCreatePushParserCtxt(_, _, _, _, _))
    .Times(1)
    .WillOnce(DoAll(
        testing::WithArg<1>([](void* context) {
            HDK_ParseContext* parseContext = static_cast<HDK_ParseContext*>(context);
            parseContext->fHaveInput = 1;
        }),
        Return(pXMLParser)
    ));

    EXPECT_CALL(*g_libxmlMock, xmlParseChunk(_, _, _, _)).Times(1).WillOnce(Return(XML_ERR_OK));

    EXPECT_CALL(*g_libxmlMock, xmlFreeParserCtxt(_)).Times(1);
    EXPECT_CALL(*g_libxmlMock, xmlCleanupParser()).Times(1);

    HDK_ParseError result = HDK_Parse((void*)mockDeviceCtx, pStruct, strlen(xmlContent));

    EXPECT_EQ(result, HDK_ParseError_OK);

    free(mockDeviceCtx);
    free(pStruct);
}

TEST_F(CcspHomeSecurityHDKFixture, HDK_Parse_FAIL_IOError) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));
    unsigned int cbContentLength = 10;

    xmlParserCtxtPtr pXMLParser = (xmlParserCtxtPtr)malloc(sizeof(xmlParserCtxtPtr));
    memset(pXMLParser, 0, sizeof(xmlParserCtxtPtr));

    EXPECT_CALL(*g_fileIOMock, fread(_, 1, _, _)).Times(1).WillOnce(Return(-1));

    EXPECT_CALL(*g_libxmlMock, xmlCreatePushParserCtxt(_, _, _, _, _)).Times(1)
    .WillOnce(Return(pXMLParser));

    EXPECT_CALL(*g_libxmlMock, xmlFreeParserCtxt(_)).Times(1);
    EXPECT_CALL(*g_libxmlMock, xmlCleanupParser()).Times(1);

    HDK_ParseError result = HDK_Parse((void*)mockDeviceCtx, pStruct, cbContentLength);

    EXPECT_EQ(result, HDK_ParseError_500_IOError);

    free(mockDeviceCtx);
    free(pStruct);
}

TEST_F(CcspHomeSecurityHDKFixture, HDK_Parse_FAIL_NoInput) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    HDK_Struct* pStruct = (HDK_Struct*)malloc(sizeof(HDK_Struct));

    xmlParserCtxtPtr pXMLParser = (xmlParserCtxtPtr)malloc(sizeof(xmlParserCtxtPtr));
    memset(pXMLParser, 0, sizeof(xmlParserCtxtPtr));

    const char* xmlContent =
        "<Request>\n"
        "    <Action>TestAction</Action>\n"
        "    <Parameter>Value</Parameter>\n"
        "</Request>\n";

    EXPECT_CALL(*g_fileIOMock, fread(_, 1, _, _))
    .Times(1)
    .WillOnce(testing::Invoke([xmlContent](void* ptr, size_t size, size_t count, FILE*) {
        size_t contentLength = strlen(xmlContent);
        if (count >= contentLength) {
            memcpy(ptr, xmlContent, contentLength);
            return static_cast<size_t>(contentLength);
        }
        return static_cast<size_t>(0);
    }));

    EXPECT_CALL(*g_libxmlMock, xmlCreatePushParserCtxt(_, _, _, _, _)).Times(1)
    .WillOnce(Return(pXMLParser));

    EXPECT_CALL(*g_libxmlMock, xmlParseChunk(_, _, _, _)).Times(1).WillOnce(Return(XML_ERR_OK));

    EXPECT_CALL(*g_libxmlMock, xmlFreeParserCtxt(_)).Times(1);
    EXPECT_CALL(*g_libxmlMock, xmlCleanupParser()).Times(1);

    HDK_ParseError result = HDK_Parse((void*)mockDeviceCtx, pStruct, strlen(xmlContent));

    EXPECT_EQ(result, HDK_ParseError_500_NoInput);

    free(mockDeviceCtx);
    free(pStruct);
}

TEST_F(CcspHomeSecurityHDKFixture, ElementStartHandler) {
    const xmlChar* pszElement = (const xmlChar*)"HDK_Element_PN_ExternalPort";
    const xmlChar* pszPrefix = (const xmlChar*)"";
    const xmlChar* pszNamespace = (const xmlChar*)"http://purenetworks.com/HNAP1/";
    int nNamespaces = 0;
    const xmlChar** ppszNamespaces = nullptr;
    int nAttributes = 0;
    int nDefaulted = 0;
    const xmlChar** ppszAttributes = nullptr;

    HDK_ParseContext* mockParseCtx = (HDK_ParseContext*)malloc(sizeof(HDK_ParseContext));
    memset(mockParseCtx, 0, sizeof(HDK_ParseContext));
    mockParseCtx->parseError = HDK_ParseError_OK;
    mockParseCtx->ixElement = 46;
    mockParseCtx->pXMLParser = (void*)1;

    EXPECT_CALL(*g_libxmlMock, xmlStopParser(_)).WillRepeatedly(Return());

    ElementStartHandler((void*)mockParseCtx, pszElement, pszPrefix, pszNamespace, nNamespaces, ppszNamespaces, nAttributes, nDefaulted, ppszAttributes);
    free(mockParseCtx);
}

TEST_F(CcspHomeSecurityHDKFixture, ElementEndHandler) {
    const xmlChar* pszElement = (const xmlChar*)"HDK_Element_PN_ExternalPort";
    const xmlChar* pszPrefix = (const xmlChar*)"";
    const xmlChar* pszNamespace = (const xmlChar*)"http://purenetworks.com/HNAP1/";

    HDK_ParseContext* mockParseCtx = (HDK_ParseContext*)malloc(sizeof(HDK_ParseContext));
    memset(mockParseCtx, 0, sizeof(HDK_ParseContext));
    mockParseCtx->parseError = HDK_ParseError_OK;
    mockParseCtx->ixElement = 46;
    mockParseCtx->pXMLParser = (void*)1;

    EXPECT_CALL(*g_libxmlMock, xmlStopParser(_)).WillRepeatedly(Return());

    ElementEndHandler((void*)mockParseCtx, pszElement, pszPrefix, pszNamespace);
    free(mockParseCtx);
}

TEST_F(CcspHomeSecurityHDKFixture, ElementValueHandler) {
    const xmlChar* pValue = (const xmlChar*)"HDK_Element_PN_ExternalPort";
    int cbValue = strlen((const char*)pValue);

    HDK_ParseContext* mockParseCtx = (HDK_ParseContext*)malloc(sizeof(HDK_ParseContext));
    memset(mockParseCtx, 0, sizeof(HDK_ParseContext));
    mockParseCtx->parseError = HDK_ParseError_OK;
    mockParseCtx->ixElement = 46;
    mockParseCtx->pXMLParser = (void*)1;

    ElementValueHandler((void*)mockParseCtx, pValue, cbValue);

    free(mockParseCtx);
}

TEST_F(CcspHomeSecurityHDKFixture, HDK_HandleRequest) {
    HDK_Context* mockDeviceCtx = createMockHDK_Context();
    int fGet = 0;
    unsigned int cbContentLength = 10;
    char pszSoapAction[] = "http://purenetworks.com/HNAP1/GetDeviceSettings";

    //HDK_Parse Mock
    xmlParserCtxtPtr pXMLParser = (xmlParserCtxtPtr)malloc(sizeof(xmlParserCtxtPtr));
    memset(pXMLParser, 0, sizeof(xmlParserCtxtPtr));

    const char* xmlContent =
        "<Request>\n"
        "    <Action>TestAction</Action>\n"
        "    <Parameter>Value</Parameter>\n"
        "</Request>\n";

    EXPECT_CALL(*g_fileIOMock, fread(_, 1, _, _))
    .Times(1)
    .WillOnce(testing::Invoke([xmlContent](void* ptr, size_t size, size_t count, FILE*) {
        size_t contentLength = strlen(xmlContent);
        if (count >= contentLength) {
            memcpy(ptr, xmlContent, contentLength);
            return static_cast<size_t>(contentLength);
        }
        return static_cast<size_t>(0);
    }));

    EXPECT_CALL(*g_libxmlMock, xmlCreatePushParserCtxt(_, _, _, _, _))
    .Times(1)
    .WillOnce(DoAll(
        testing::WithArg<1>([](void* context) {
            HDK_ParseContext* parseContext = static_cast<HDK_ParseContext*>(context);
            parseContext->fHaveInput = 1;
        }),
        Return(pXMLParser)
    ));
    EXPECT_CALL(*g_libxmlMock, xmlFreeParserCtxt(_)).Times(1);
    EXPECT_CALL(*g_libxmlMock, xmlCleanupParser()).Times(1);

    HDK_Enum_Result result = HDK_HandleRequest((void*)mockDeviceCtx, fGet, cbContentLength, pszSoapAction);
    EXPECT_EQ(result, HDK_Enum_Result_ERROR);
}
