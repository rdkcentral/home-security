/*
 * If not stated otherwise in this file or this component's Licenses.txt file the
 * following copyright and licenses apply:
 *
 * Copyright 2015 RDK Management
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

/**********************************************************************
   Copyright [2014] [Cisco Systems, Inc.]
 
   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at
 
       http://www.apache.org/licenses/LICENSE-2.0
 
   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
**********************************************************************/

/*
 * hdk_context.c - Sample device context
 */

#include "hdk_adi.h"
#include "hdk_context.h"
#include "chs_log.h"
#include <unistd.h>

#include <stdlib.h>
#include <string.h>
#include "ccsp_base_api.h"
#include "hdk_ccsp_mbus.h"
#include "ansc_platform.h"
#include "secure_wrapper.h"
#ifdef LIBRDKCONFIG_BUILD
#include "rdkconfig.h"
#endif
//#ifdef defined(_COSA_DRG_CNS_) || defined(_COSA_DRG_TPG_)
#if 1
#define MBUS_COMPID_HDK         "eRT.com.cisco.spvtg.ccsp.HNAP"
#define MBUS_COMPID_CR          "eRT.com.cisco.spvtg.ccsp.CR"
#else
#define MBUS_COMPID_HDK         "com.cisco.spvtg.ccsp.HDK"
#define MBUS_COMPID_CR          "com.cisco.spvtg.ccsp.CR"
#endif

#define MBUS_CONF_FILE          CCSP_MSG_BUS_CFG
#define MBUS_SUBSYSTEM          ""

#ifdef HDK_EMULATOR
/* Emulator state file */
#ifndef HDK_EMULATOR_STATE_FILE
#define HDK_EMULATOR_STATE_FILE "emulator.ds"
#endif
#endif
static MBusObj_t *ccsp_bus = NULL;
extern int HDK_Stop_HomeSecurity_Bridge(MBusObj_t *ccsp_bus);

MBusObj_t * mbus_init()
{
	MBusObj_t *mbus = NULL;

	mbus =  MBus_Create(MBUS_SUBSYSTEM, MBUS_CONF_FILE, MBUS_COMPID_HDK, MBUS_COMPID_CR);

	while (!mbus)
	{
		log_printf(LOG_ERR, "Create mbus failed, retry after 3s\n");
		sleep(3);
		mbus =  MBus_Create(MBUS_SUBSYSTEM, MBUS_CONF_FILE, MBUS_COMPID_HDK, MBUS_COMPID_CR);
	}

	ccsp_bus = mbus;
	return mbus;
}

void homesecurity_timeout_handler()
{
	if(HDK_Stop_HomeSecurity_Bridge(ccsp_bus))
		log_printf(LOG_ERR, "stop ethernet port 4 home security vlan failed\n");
}

/*
 * HDK_Context_Init - Initialize the device context
 *
 * Return: Non-zero for success, zero otherwise
 */
int HDK_Context_Init(void** ppCtx, FILE* pfhRead, FILE* pfhWrite)
{
    int fResult = 0;

#ifdef HDK_EMULATOR
    /* Allocate the device context */
    HDK_Context* pCtx = (HDK_Context*)malloc(sizeof(HDK_Context));
    *ppCtx = pCtx;
    if (pCtx)
    {
        /* Initialize the emulator context */
        HDK_Emulator_Init(pCtx);

        /* Read the state file */
        fResult = HDK_Emulator_ReadState(pCtx, HDK_EMULATOR_STATE_FILE);

        /* Set the request/response file handles */
        pCtx->fhRequest = pfhRead;
        pCtx->fhResponse = pfhWrite;
    }
#else
    /* Allocate the device context */
    HDK_Context* pCtx = (HDK_Context*)malloc(sizeof(HDK_Context));
    *ppCtx = pCtx;
    if (pCtx)
    {
        fResult = 1;
        pCtx->fhRequest = pfhRead;
        pCtx->fhResponse = pfhWrite;
        pCtx->fReboot = 0;
        pCtx->mbus = ccsp_bus;               
    }
#endif

    return fResult;
}

/*
 * HNAP_Context_Free - Free the device context
 */
void HDK_Context_Free(void* pCtx, int fCommit)
{
#ifdef HDK_EMULATOR
    if (pCtx)
    {
        /* Write out the emulator state */
        if (fCommit)
        {
            HDK_Emulator_WriteState((HDK_Context*)pCtx, HDK_EMULATOR_STATE_FILE);
        }

        /* Free the emulator */
        HDK_Emulator_Free((EmulatorContext*)pCtx);

        /* Free the device context */
        free(pCtx);
    }
#else
    HDK_Context *hdkCtx = (HDK_Context *)pCtx;

    /* Unused parameters */
    (void)fCommit;

    if (!hdkCtx)
        return;

    //MBus_Destroy(hdkCtx->mbus);

    /* Free the device context */
    free(pCtx);
#endif
}

#define TEMP_FILE "/tmp/hnap-file1"

int ValidatSecuredPassword(char *pszPassword)
{
#ifdef LIBRDKCONFIG_BUILD
    uint8_t *retpwd=NULL;
    int status=1;
    size_t retpwdsize;
    if(rdkconfig_get(&retpwd, &retpwdsize, TEMP_FILE))
    {
    	log_printf(LOG_ERR, "%s, Extraction failure for validation value\n",__FUNCTION__);
    	return 1;
    }
    if(strncmp(pszPassword, (char *)retpwd,retpwdsize) == 0)
    {
       status=0;
    }else{
       log_printf(LOG_ERR, "ValidateHnapFile failed\n");
       status=1;
    }
    if (rdkconfig_free(&retpwd, retpwdsize)  == RDKCONFIG_FAIL) {
        log_printf(LOG_ERR, "%s, Memory deallocation for validation value failed \n",__FUNCTION__);
    }
    return status;
#else
    FILE *fp = NULL;
    char buf[50] = {0};
    char retPassword[50] = {0};
    int pwdlen = 0;
    int sscanf_ret = 0;

    v_secure_system("GetConfigFile " TEMP_FILE);
    if ( (fp=fopen(TEMP_FILE, "r")) == NULL )
    {
        log_printf(LOG_ERR, "ValidateHnapFile failed: file not present\n");
        v_secure_system("rm -f " TEMP_FILE);
        return 1;
    }
    while ( fgets(buf, sizeof(buf), fp)!= NULL )
    {
        /* CID 57191 Calling risky function */
        sscanf_ret = sscanf(buf,"%49s",retPassword);
        if (sscanf_ret == 1)
        {
            pwdlen = strlen(retPassword);
            if(strncmp(pszPassword, retPassword,pwdlen) == 0)
            {
                fclose(fp);
                v_secure_system("rm -f " TEMP_FILE);
                return 0;
            }
        }
    }
    v_secure_system("rm -f " TEMP_FILE);
    log_printf(LOG_ERR, "ValidateHnapFile failed\n");
    fclose(fp);
    return 1;
#endif
}

/*
 * HDK_Context_Authenticate - Authenticate the request
 */
int HDK_Context_Authenticate(void* pCtx, char* pszUsername, char* pszPassword)
{
    int fResult = 0;
    /* CID 71414 Structurally dead code */
    (void)pCtx;

    fResult = strcmp(pszUsername, "hnapadmin") == 0 && ValidatSecuredPassword(pszPassword) == 0;
    return fResult;

    /*
    // Get the Username/Password from the device state
    HDK_Struct sTemp;
    HDK_Struct_Init(&sTemp);
    if (HDK_Device_GetValue(pCtx, &sTemp, HDK_DeviceValue_Username, 0) &&
        HDK_Device_GetValue(pCtx, &sTemp, HDK_DeviceValue_AdminPassword, 0))
    {
        // Compare the credentials
        fResult = strcmp(pszUsername, HDK_Get_String(&sTemp, HDK_Element_PN_Username)) == 0 &&
            strcmp(pszPassword, HDK_Get_String(&sTemp, HDK_Element_PN_AdminPassword)) == 0;
    }
    HDK_Struct_Free(&sTemp);

    return fResult;
    */
}

int HDK_Signal_Hander(int signal)
{
        UNREFERENCED_PARAMETER(signal);
	return HDK_Stop_HomeSecurity_Bridge(ccsp_bus);
}
