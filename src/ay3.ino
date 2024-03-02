void AY3(byte address, byte data)
{
    ay3Reg1[address] = data;
}

void updateEnv()
{
    if (bitRead(ledMatrix[4], 0) == 1)
        set_chA_amplitude(vol[1], true);
    else
        set_chA_amplitude(vol[1], false);
    if (bitRead(ledMatrix[4], 1) == 1)
        set_chB_amplitude(vol[2], true);
    else
        set_chB_amplitude(vol[2], false);
    if (bitRead(ledMatrix[4], 2) == 1)
        set_chC_amplitude(vol[3], true);
    else
        set_chC_amplitude(vol[3], false);
    if (bitRead(ledMatrix[4], 3) == 1)
        set_chD_amplitude(vol[4], true);
    else
        set_chD_amplitude(vol[4], false);
    if (bitRead(ledMatrix[4], 4) == 1)
        set_chE_amplitude(vol[5], true);
    else
        set_chE_amplitude(vol[5], false);
    if (bitRead(ledMatrix[4], 5) == 1)
        set_chF_amplitude(vol[6], true);
    else
        set_chF_amplitude(vol[6], false);
}

void AY32(byte address, byte data)
{
    ay3Reg2[address] = data;
}

int addressCounter;

void updateAy3()
{
    addressCounter++;
    if (addressCounter > 17)
        addressCounter = 0;

    if (ay3Reg1[addressCounter] != ay3Reg1Last[addressCounter])
    {
        send1(addressCounter, ay3Reg1[addressCounter]);
        ay3Reg1Last[addressCounter] = ay3Reg1[addressCounter];
    }

    if (ay3Reg2[17 - addressCounter] != ay3Reg2Last[17 - addressCounter])
    {
        send2(17 - addressCounter, ay3Reg2[17 - addressCounter]);
        ay3Reg2Last[17 - addressCounter] = ay3Reg2[17 - addressCounter];
    }
}

void mode_latch1()
{
    PORTD |= _BV(4); // digitalWrite (12, HIGH);
    PORTD |= _BV(5); // digitalWrite (13, HIGH);
    delayMicroseconds(chipDelay);
}

void mode_write1()
{
    PORTD &= ~_BV(4); // digitalWrite (12, LOW);
    PORTD |= _BV(5);  // digitalWrite (13, HIGH);
}

void mode_inactive1()
{
    PORTD &= ~_BV(4); // digitalWrite (12, LOW);
    PORTD &= ~_BV(5); // digitalWrite (13, LOW);
}

void send1(unsigned char address, unsigned char data)
{
    // we "clean" all previous sent data
    mode_inactive1();
    PORTC = address;
    delayMicroseconds(chipDelay);

    // and finish the write
    mode_latch1();
    mode_inactive1();

    // write data
    mode_write1();
    PORTC = data;
    delayMicroseconds(chipDelay);

    // we latch off, to indicate to AY that the data transmission is over
    mode_inactive1();
}

void mode_latch2()
{
    PORTD |= _BV(4); // digitalWrite (12, HIGH);
    PORTD |= _BV(6+boardRevision); // digitalWrite (14/15, HIGH);
    delayMicroseconds(chipDelay);
}

void mode_write2()
{
    PORTD &= ~_BV(4); // digitalWrite (12, LOW);
    PORTD |= _BV(6+boardRevision);  // digitalWrite (14, HIGH);
}

void mode_inactive2()
{
    PORTD &= ~_BV(4); // digitalWrite (12, LOW);
    PORTD &= ~_BV(6+boardRevision); // digitalWrite (14, LOW);
}

void send2(unsigned char address, unsigned char data)
{
    // we "clean" all previous sent data
    mode_inactive2();
    PORTC = address;
    delayMicroseconds(chipDelay);

    // and finish the write
    mode_latch2();
    mode_inactive2();

    // write data
    mode_write2();
    PORTC = data;
    delayMicroseconds(chipDelay);

    // we latch off, to indicate to AY that the data transmission is over
    mode_inactive2();
}

void init2MhzClock()
{
    if (!boardRevision) {

        // PWM 500Khz (17 cycles), Timer 2A
        TCCR2A = 
          1 << COM2A0 |   // TOGGLE A
          1 << WGM21;     // CTC (OCR2A = TOP)
        TCCR2B = 
          1 << CS20;      // NO PRESCALE = 1
        TIMSK2 = 0;       // NO ISRs
        OCR2A = 16;       // 17 cycles

    } else {

        // PWM 500Khz (17 cycles), Timer 2B
        TCCR2A = 
          1 << COM2B0 |   // TOGGLE B
          1 << WGM21;     // CTC (OCR2A = TOP)
        TCCR2B = 
          1 << CS20;      // NO PRESCALE = 1
        TIMSK2 = 0;       // NO ISRs
        OCR2A = 16;       // 17 cycles
    }
}

void set_chA_amplitude(int amplitude, boolean useEnvelope)
{
    AY3(8, (amplitude & 0xf) | (useEnvelope != true ? 0 : B00010000));
}

void set_chB_amplitude(int amplitude, boolean useEnvelope)
{
    AY3(9, (amplitude & 0xf) | (useEnvelope != true ? 0 : B00010000));
}

void set_chC_amplitude(int amplitude, boolean useEnvelope)
{
    AY3(10, (amplitude & 0xf) | (useEnvelope != true ? 0 : B00010000));
}

void set_chD_amplitude(int amplitude, boolean useEnvelope)
{
    AY32(8, (amplitude & 0xf) | (useEnvelope != true ? 0 : B00010000));
}

void set_chE_amplitude(int amplitude, boolean useEnvelope)
{
    AY32(9, (amplitude & 0xf) | (useEnvelope != true ? 0 : B00010000));
}

void set_chF_amplitude(int amplitude, boolean useEnvelope)
{
    AY32(10, (amplitude & 0xf) | (useEnvelope != true ? 0 : B00010000));
}