static void set_DMA_recive(int size, uint8_t *StartAddr)
{
    DMACTL1 = DMA2TSEL_19; // DMA2 - UCB0TXIFG
    DMACTL0 = DMA1TSEL_18; // DMA1 - UCB0RXIFG

    DMA2CTL = DMASBDB + DMALEVEL;                // передатчикDMASRCINCR_3+DMAIE
    DMA1CTL = DMADSTINCR_3 + DMASBDB + DMALEVEL; //+DMAIE;  // приемник

    DMA1SZ = size; // Block size
    DMA2SZ = size; // Block size

    // Setup DMA1 (приемник)
    __data16_write_addr((unsigned short)&DMA1SA, (unsigned long)&UCB0RXBUF);
    // Source block address
    __data16_write_addr((unsigned short)&DMA1DA, (unsigned long)StartAddr);

    // Destination single address
    // Setup DMA1 (передатчик)
    __data16_write_addr((unsigned short)&DMA2SA, (unsigned long)&FF_Buf);
    // Source block address
    __data16_write_addr((unsigned short)&DMA2DA, (unsigned long)&UCB0TXBUF);
    // Destination single address

    DMA1CTL |= DMAEN; // DMA1 Enable
    DMA2CTL |= DMAEN; // DMA0 Enable
    while (DMA2CTL & DMAEN) {
        ;
    }
}
