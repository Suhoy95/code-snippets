int connectToAP(_i8* SSID, unsigned char secureType, _i8* password)
{
    int retVal;
    /*
     * Device in station-mode. Disconnect previous connection if any
     * The function returns 0 if 'Disconnected done', negative number if already disconnected
     * Wait for 'disconnection' event if 0 is returned, Ignore other return-codes
     */
    retVal = sl_WlanDisconnect();
    if (retVal == 0) {
        while (IS_CONNECTED(g_Status)) {
            _SlNonOsMainLoopTask();
        }
    }

    SlVersionFull ver;
    _u8 pConfigLen = sizeof(ver);
    _u8 pConfigOpt = SL_DEVICE_GENERAL_VERSION;
    retVal = sl_DevGet(SL_DEVICE_GENERAL_CONFIGURATION, &pConfigOpt, &pConfigLen, (_u8*)(&ver));
    CHECK_ERROR(retVal < 0);

    _u8 val = 1;
    retVal = sl_NetCfgSet(SL_IPV4_STA_P2P_CL_DHCP_ENABLE, 1, 1, &val);
    CHECK_ERROR(retVal < 0);

    SlSecParams_t secParams = {
        .Key = password,
        .KeyLen = strlen((char*)password),
        .Type = secureType,
    };

    retVal = sl_WlanConnect(SSID, strlen((char*)SSID), 0, &secParams, 0);
    CHECK_ERROR(retVal < 0);

    while (!IS_CONNECTED(g_Status) || !IS_IP_ACQUIRED(g_Status)) {
        _SlNonOsMainLoopTask();
    }

    return 0;
}

int try_send_data(char* data, _u32 len)
{
    int sockId = sl_Socket(SL_AF_INET, SL_SOCK_STREAM, SL_IPPROTO_TCP);

    SlSockAddrIn_t addr = {
        .sin_family = SL_AF_INET,
        .sin_port = sl_Htons(8080),
        .sin_addr.s_addr = sl_Htonl(
            g_GatewayIP
            // 0xC0A80064 // 192.168.0.100
            // 0xC0A80067 // 192.168.0.103
            // 0xC0A82B48 // 192.168.43.72
            ),
    };

    int status = sl_Connect(sockId, (SlSockAddr_t*)&addr, sizeof(SlSockAddrIn_t));
    if (status < 0) {
        status = sl_Close(sockId);
        CHECK_ERROR(status < 0);
        return -1;
    }

    // status = sl_Send(sockId, data, len, 0);
    // CHECK_ERROR(status < 0);
    char kilobyte[] = {
        0x5C, 0xC9, 0x6E, 0x75, 0xB7, 0x43, 0xAF, 0x39, 0x34, 0x95, 0x2A, 0xFF, 0xBE, 0x1C, 0xE7, 0xD0,
        0x45, 0x73, 0xBA, 0x60, 0x56, 0x0D, 0x88, 0x66, 0xF1, 0x02, 0x7C, 0x6F, 0x26, 0x93, 0x5C, 0x43,
        0x47, 0x07, 0xBA, 0x80, 0x4A, 0xAB, 0x12, 0xC1, 0x0A, 0x71, 0x9A, 0x7D, 0x00, 0x4D, 0x85, 0x58,
        0x07, 0x74, 0xF8, 0xDD, 0x44, 0x6F, 0x20, 0x6E, 0x96, 0x09, 0xC6, 0xC7, 0xC6, 0xD4, 0x82, 0xA6,
        0x0F, 0x9A, 0xF4, 0xF4, 0x46, 0xAC, 0x80, 0x6E, 0x2B, 0xF3, 0xA1, 0x1B, 0xC2, 0x48, 0x95, 0x40,
        0x29, 0xAF, 0x96, 0xBA, 0xDE, 0xC6, 0x58, 0x6D, 0xBE, 0x53, 0xD3, 0x40, 0xCD, 0x01, 0xB4, 0xC5,
        0xF4, 0x5C, 0x83, 0x2D, 0xA3, 0x0B, 0x89, 0x74, 0xDB, 0xE3, 0x2D, 0x89, 0x44, 0x60, 0x03, 0x03,
        0xD8, 0xE3, 0xFA, 0x70, 0x05, 0x36, 0x17, 0x61, 0xEC, 0x69, 0xC9, 0x00, 0xFA, 0xC5, 0xD7, 0xD7,
        0x40, 0x42, 0x94, 0x51, 0x30, 0x94, 0x05, 0x74, 0xCB, 0x7B, 0xFC, 0xC2, 0xF5, 0x98, 0x4C, 0xFD,
        0x65, 0x54, 0xBE, 0xA1, 0x58, 0x38, 0x47, 0x16, 0x9D, 0xD0, 0xE0, 0xBC, 0x7E, 0x95, 0x5D, 0x76,
        0x9F, 0xE1, 0xA8, 0xDB, 0xB2, 0x8F, 0xFA, 0x5C, 0xB5, 0x99, 0x4F, 0x5E, 0x71, 0xB0, 0x7E, 0x75,
        0x55, 0xD0, 0xA4, 0x48, 0xF1, 0xC9, 0xBD, 0x79, 0x7B, 0x4F, 0x55, 0xF9, 0x6C, 0xE5, 0xBA, 0xE4,
        0x00, 0x68, 0x39, 0x0F, 0xCA, 0xF7, 0x2C, 0xED, 0x17, 0x0B, 0x82, 0xE0, 0x12, 0xD2, 0xE4, 0x2C,
        0x12, 0x9D, 0x0D, 0xC4, 0x1D, 0xBD, 0xDA, 0xFA, 0xF2, 0xFB, 0xAD, 0xD9, 0xD1, 0x03, 0x1F, 0x3D,
        0x26, 0x7E, 0xEF, 0x20, 0x49, 0x1F, 0xEE, 0x59, 0xA4, 0x4C, 0xC1, 0xBB, 0xFF, 0xE2, 0x7F, 0xD8,
        0xBE, 0x56, 0xBE, 0x20, 0x79, 0x55, 0x0B, 0x13, 0x53, 0xE0, 0x54, 0x4A, 0x8B, 0xE0, 0x58, 0x91,
        0x05, 0xAC, 0x4B, 0x46, 0xFC, 0x55, 0x2A, 0x76, 0xA9, 0xCD, 0xA4, 0x0C, 0x84, 0x6C, 0xCB, 0x03,
        0x32, 0x40, 0x0C, 0x30, 0x35, 0x4E, 0x57, 0xB2, 0xC1, 0x4C, 0xDC, 0x63, 0x01, 0xDF, 0x18, 0x39,
        0x19, 0x0F, 0x23, 0xF2, 0x2C, 0x09, 0x47, 0x32, 0x0C, 0x20, 0x00, 0xE8, 0x30, 0x57, 0xB2, 0xF5,
        0x19, 0xE8, 0xD7, 0x4D, 0x06, 0x08, 0xD9, 0x8E, 0x9E, 0x53, 0x49, 0xBB, 0xC6, 0xDC, 0xEF, 0xC8,
        0x2D, 0x87, 0x46, 0x2D, 0x0D, 0x66, 0x7E, 0x08, 0x99, 0x71, 0x5D, 0xFC, 0x16, 0x2F, 0xD4, 0xF2,
        0x74, 0xEF, 0x13, 0xFC, 0x1D, 0x57, 0x0E, 0xB7, 0x1B, 0x62, 0xF2, 0x81, 0xC1, 0xA5, 0x74, 0x84,
        0x9D, 0xA6, 0x09, 0x21, 0xD2, 0xF3, 0x23, 0x8A, 0xE6, 0x72, 0x83, 0xD3, 0x35, 0xBA, 0xD8, 0x92,
        0xAC, 0x19, 0xFA, 0xB6, 0xC0, 0xF1, 0xF4, 0xFA, 0x04, 0x5B, 0xB0, 0xC9, 0x64, 0x71, 0x55, 0xB7,
        0x20, 0x07, 0x15, 0xFC, 0x11, 0x1C, 0xE9, 0x96, 0x22, 0xFE, 0x5F, 0xFF, 0x52, 0xA0, 0xFA, 0x95,
        0x90, 0x47, 0x88, 0x4E, 0x0C, 0x3F, 0x2E, 0xB5, 0xFB, 0x94, 0xFE, 0xE2, 0xCE, 0x64, 0x23, 0x95,
        0xFA, 0x6D, 0x48, 0x61, 0x8F, 0x04, 0x88, 0xCC, 0xD2, 0xF7, 0x6E, 0xC0, 0x0C, 0x51, 0xEF, 0x42,
        0x67, 0x8D, 0xEF, 0x8F, 0x78, 0xB6, 0x58, 0xE7, 0xD5, 0xE9, 0x27, 0x19, 0x11, 0x0E, 0xE5, 0x84,
        0xC7, 0x36, 0xC1, 0x0C, 0xA6, 0x58, 0x49, 0x3D, 0x63, 0xED, 0x9F, 0x7F, 0xB8, 0x8C, 0x7C, 0xB2,
        0x91, 0x2F, 0x31, 0xFE, 0xA8, 0x56, 0xBB, 0x57, 0xBD, 0x51, 0xE3, 0xD3, 0x0D, 0xE7, 0x79, 0xF6,
        0x4D, 0xDE, 0xC4, 0xE6, 0x17, 0x3E, 0xEF, 0xA1, 0x6F, 0x29, 0x3D, 0xBA, 0xE5, 0x57, 0xFD, 0xF8,
        0x05, 0xF6, 0x8C, 0xA1, 0xB8, 0x94, 0x87, 0x80, 0xFC, 0x83, 0x11, 0xEC, 0x5F, 0xC2, 0x29, 0xCE,
        0x35, 0x19, 0x81, 0x08, 0xEB, 0x88, 0x86, 0x6C, 0xED, 0x95, 0xD1, 0xC0, 0x79, 0x61, 0xC9, 0x62,
        0x4A, 0xCF, 0xF0, 0x3F, 0x0E, 0xB4, 0x4A, 0xE8, 0xE1, 0x16, 0xE1, 0x48, 0xBB, 0x21, 0xB6, 0xB5,
        0x62, 0x58, 0x09, 0x90, 0xAF, 0x03, 0x70, 0x3A, 0xBE, 0xB5, 0xD4, 0xF2, 0x3E, 0x1A, 0x54, 0xF4,
        0x1D, 0x0D, 0x4C, 0xF6, 0xC6, 0xED, 0xB7, 0x3B, 0x2F, 0x1E, 0x41, 0x82, 0xCB, 0xBD, 0xA4, 0x77,
        0x5A, 0x92, 0x96, 0x0F, 0x79, 0x56, 0xA3, 0x5C, 0x3C, 0x61, 0xC4, 0xD4, 0x79, 0x54, 0xB5, 0x6A,
        0x50, 0x0E, 0xE8, 0x3E, 0x82, 0xDE, 0x70, 0xBE, 0x8A, 0x6E, 0x5E, 0xBB, 0xDA, 0x66, 0x70, 0x94,
        0x50, 0x86, 0x93, 0x2B, 0x28, 0x01, 0x5E, 0xC0, 0x9C, 0xFB, 0xA2, 0x44, 0xE3, 0x0C, 0xC9, 0x02,
        0xED, 0xF2, 0x29, 0xF0, 0x58, 0xFE, 0xC6, 0x2A, 0xE6, 0x60, 0x5E, 0x32, 0x26, 0x0B, 0x0C, 0xD3,
        0xC0, 0x3A, 0x1E, 0x6D, 0x2F, 0xCB, 0xB7, 0xBA, 0x4A, 0xD9, 0xE6, 0x3B, 0xDD, 0xDB, 0x31, 0x90,
        0x9B, 0x27, 0xAA, 0x62, 0x93, 0xC9, 0xDF, 0x6F, 0x36, 0x26, 0x4D, 0x20, 0x83, 0x35, 0xE1, 0x08,
        0x7B, 0x6B, 0xE6, 0xC0, 0xB6, 0x53, 0x37, 0xDF, 0xF3, 0xE3, 0xD4, 0x8A, 0x8C, 0x8A, 0x0F, 0x25,
        0x16, 0xEB, 0x4F, 0xDE, 0xDC, 0xF4, 0xF3, 0xE5, 0xF9, 0x40, 0x30, 0xEF, 0x14, 0x5B, 0x3A, 0xB4,
        0x6C, 0x7A, 0x4F, 0x0B, 0x5F, 0xA1, 0x37, 0x96, 0xDE, 0xD4, 0x26, 0xAF, 0x28, 0x6D, 0xB7, 0x8E,
        0xFA, 0x22, 0xD1, 0x35, 0xD9, 0x31, 0x7B, 0x21, 0x0C, 0x52, 0x86, 0xF2, 0x17, 0xC6, 0xB1, 0x4B,
        0x96, 0x88, 0xB3, 0xD4, 0x09, 0x4B, 0x9D, 0x94, 0x15, 0xFD, 0x9A, 0x62, 0x20, 0xBF, 0x0F, 0xD7,
        0x53, 0x4E, 0x9E, 0xCD, 0x59, 0xB4, 0x99, 0x7E, 0x4E, 0x3B, 0x7F, 0xA6, 0x89, 0xB1, 0xCF, 0x8E,
        0x74, 0x7E, 0x6B, 0xCD, 0x5B, 0x68, 0xFC, 0x48, 0xAE, 0xA6, 0x52, 0x58, 0xE4, 0xD1, 0x87, 0x50,
        0xF5, 0x74, 0x7B, 0x8D, 0xDF, 0x7A, 0x69, 0x76, 0x68, 0x70, 0x98, 0x54, 0xDD, 0x52, 0x8A, 0xDE,
        0x4C, 0x13, 0x46, 0x2B, 0x9D, 0x10, 0x29, 0xA8, 0xC1, 0x75, 0x80, 0x0C, 0x6A, 0x4C, 0x2C, 0xD2,
        0xD1, 0xF1, 0x68, 0x48, 0x45, 0x95, 0x03, 0x95, 0x2E, 0xB6, 0xCA, 0x98, 0x5C, 0x5C, 0x2F, 0x3B,
        0x93, 0x1A, 0x6F, 0xB2, 0x15, 0xD4, 0xEF, 0x4E, 0x77, 0x33, 0x24, 0x34, 0x9C, 0xBB, 0xF6, 0x30,
        0x15, 0xDB, 0x2F, 0x6F, 0xD3, 0x5F, 0xE9, 0xDC, 0x30, 0x4A, 0xC3, 0x97, 0xA5, 0x2D, 0x60, 0x8D,
        0x0C, 0xCD, 0xBF, 0xC2, 0x15, 0xD8, 0xC1, 0x84, 0x02, 0xF6, 0x11, 0x71, 0x65, 0xBC, 0x3A, 0xB8,
        0x37, 0x8F, 0xF6, 0xB4, 0x74, 0x28, 0x60, 0x5A, 0xD7, 0x66, 0xE4, 0x89, 0xDC, 0xDA, 0xB9, 0x4B,
        0xA7, 0x51, 0x2A, 0x55, 0x51, 0xE1, 0xB0, 0xCC, 0xC6, 0x81, 0x53, 0x6A, 0xA5, 0xCC, 0x6B, 0x75,
        0x25, 0xAF, 0xFC, 0x9E, 0x0A, 0x49, 0xFE, 0xF0, 0xE3, 0x3B, 0x65, 0x8C, 0x6A, 0x30, 0x73, 0xE3,
        0x0B, 0x12, 0x9A, 0x51, 0x37, 0xEC, 0xC4, 0xE8, 0x2D, 0x36, 0x82, 0xA7, 0x98, 0x1A, 0xB0, 0xAF,
        0x20, 0x57, 0xED, 0x99, 0x50, 0x17, 0x82, 0xA3, 0x20, 0x5E, 0xC3, 0x74, 0xB2, 0xA2, 0x77, 0x7E,
        0x54, 0xAC, 0xED, 0x54, 0x72, 0xD4, 0x96, 0xC5, 0x5A, 0xEA, 0x21, 0x63, 0x4D, 0x7E, 0xB0, 0xEB,
        0xDB, 0xCF, 0x3F, 0x74, 0xB6, 0xC6, 0xE8, 0x44, 0x5B, 0x10, 0x8D, 0xFA, 0x81, 0x48, 0xBB, 0x0F,
        0x8E, 0xF7, 0xCD, 0xF8, 0xA1, 0x9C, 0x90, 0xB3, 0x8D, 0x53, 0xBC, 0x81, 0xBF, 0xCC, 0x8E, 0x0B,
        0x86, 0x9B, 0x4A, 0x47, 0x91, 0x53, 0xA4, 0x4B, 0x68, 0x69, 0xE3, 0xD5, 0x34, 0x4C, 0x80, 0x73,
    };
    for (int j = 0; j < 50; j++) {
        for (long i = 0; i < 1024; i++) {
            status = sl_Send(sockId, kilobyte, 1024, 0);
            if (status < 0) {
                asm("nop;");
            }
        }
    }
    // char buf[200];
    // int recvlen = sl_Recv(sockId, buf, 200, 0);
    // CHECK_ERROR(recvlen < 0);

    status = sl_Close(sockId);
    CHECK_ERROR(status < 0);

    return 0;
}