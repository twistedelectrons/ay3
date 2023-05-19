void envSpeed(int speeed)
{
    speeed = map(speeed, 0, 255, 0, 120);
    speeed = envTp[speeed] << 4;

    //  byte LSB = 0;
    //  byte MSB = 0;

    //  LSB=speeed;
    //  MSB=speeed>>8;

    //AY3(11, LSB);
    //AY3(12, MSB); 

    //AY32(11, LSB);
    //AY32(12, MSB);

    AY3(11, speeed);
    AY3(12, speeed >> 8); 

    AY32(11, speeed);
    AY32(12, speeed >> 8);
}