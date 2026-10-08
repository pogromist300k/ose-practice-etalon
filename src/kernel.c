void loop();

void kernel_entry(void) {
    *((short int*) 0xB8900) = 0x0148;
    *((short int*) 0xB8902) = 0x0245;
    *((short int*) 0xB8904) = 0x034C;
    *((short int*) 0xB8906) = 0x044C;
    *((short int*) 0xB8908) = 0x054F;
    *((short int*) 0xB890A) = 0x0620;
    *((short int*) 0xB890C) = 0x0746;
    *((short int*) 0xB890E) = 0x0852;
    *((short int*) 0xB8910) = 0x094F;
    *((short int*) 0xB8912) = 0x0A4D;
    *((short int*) 0xB8914) = 0x0B20;
    *((short int*) 0xB8916) = 0x0C4B;
    *((short int*) 0xB8918) = 0x0D45;
    *((short int*) 0xB891A) = 0x0E52;
    *((short int*) 0xB891C) = 0x0F4E;
    *((short int*) 0xB891E) = 0x0145;
    *((short int*) 0xB8920) = 0x024C;
    *((short int*) 0xB8922) = 0x0320;
    *((short int*) 0xB8924) = 0x0E01;
    loop();
}
