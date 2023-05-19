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
    PORTD |= _BV(6); // digitalWrite (14, HIGH);
    delayMicroseconds(chipDelay);
}

void mode_write2()
{
    PORTD &= ~_BV(4); // digitalWrite (12, LOW);
    PORTD |= _BV(6);  // digitalWrite (14, HIGH);
}

void mode_inactive2()
{
    PORTD &= ~_BV(4); // digitalWrite (12, LOW);
    PORTD &= ~_BV(6); // digitalWrite (14, LOW);
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
    // Set Timer 2 CTC mode with no prescaling.  OC2A toggles on compare match
    //
    // WGM22:0 = 010: CTC Mode, toggle OC
    // WGM2 bits 1 and 0 are in TCCR2A,
    // WGM2 bit 2 is in TCCR2B
    // COM2A0 sets OC2A (arduino pin 11 on Uno or Duemilanove) to toggle on compare match
    //
    TCCR2A = ((1 << WGM21) | (1 << COM2A0));

    // Set Timer 2  No prescaling  (i.e. prescale division = 1)
    //
    // CS22:0 = 001: Use CPU clock with no prescaling
    // CS2 bits 2:0 are all in TCCR2B
    TCCR2B = (1 << CS20);

    // Make sure Compare-match register A interrupt for timer2 is disabled
    TIMSK2 = 0;
    // This value determines the output frequency
    OCR2A = ocr2aval;
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