void SimpleLinkPingReport(SlPingReport_t* pPingReport)
{
    SET_STATUS_BIT(g_Status, STATUS_BIT_PING_DONE);
    g_PingPacketsRecv = pPingReport->PacketsReceived;
}

int pingTargetHost(_u32 ip)
{
    ip = g_GatewayIP;
    CLR_STATUS_BIT(g_Status, STATUS_BIT_PING_DONE);
    g_PingPacketsRecv = 0;

    SlPingStartCommand_t pingParams = {
        .Ip = ip,
        .TotalNumberOfAttempts = 3,
        .PingSize = 1472, // bytes
        .PingIntervalTime = 1, // msecs
        .PingRequestTimeout = 300, // msecs
        .Flags = 0,
    };

    SlPingReport_t pingReport = {
        0,
    };
    int retVal = sl_NetAppPingStart((SlPingStartCommand_t*)&pingParams,
        SL_AF_INET,
        (SlPingReport_t*)&pingReport,
        SimpleLinkPingReport);
    CHECK_ERROR(retVal < 0);

    while (!IS_PING_DONE(g_Status)) {
        _SlNonOsMainLoopTask();
    }

    if (g_PingPacketsRecv == 0) {
        return -1;
    }

    return 0;
}

