void save()
{
    if (!writeChannel) {
        memPointer = (preset * 60) + ((bank * 60) * 8);

        //transfer seq notes
        for (int i=0; i<16; i++) writey(seqNote[i]);
        for (int i=1; i<7; i++) {
            writey(ledMatrix[i]);   // RIO: todo: fix loop cursor, 1 entry wasted
            writey(tune[i]);
            writey(vol[i]);
        }

        writey(arpSpeed);
        writey(lfoShape);
        writey(int(lfoSpeed));
        writey(lfoDepth);
        writey(envNumber1);
        writey(envSpd);
        writey(seqSpeed);
        writey(detune);
        writey(glide);
        writey(noiseFreq1);

        for (int i=0; i<8; i++) {
            bitWrite(seqNoise1,i,seqNoise[i]);
            bitWrite(seqNoise2,i,seqNoise[i+8]);

            bitWrite(seqVoice1,i,seqVoice[i]);
            bitWrite(seqVoice2,i,seqVoice[i+8]);
        }

        writey(seqNoise1);
        writey(seqNoise2);
        writey(seqVoice1);
        writey(seqVoice2);

        writey(envNumber2);
        writey(noiseFreq2);
    }
}

void writey(int data)
{
    EEPROM.write(memPointer,data);memPointer++;
}

int readey()
{
    memPointer++;
    return EEPROM.read(memPointer - 1); 
}

void load()
{
    EEPROM.write(3800, preset);
    EEPROM.write(3801, bank);

    memPointer = (preset * 60) + ((bank * 60) *8);

    //transfer seq notes
    for (int i=0; i<16; i++) seqNote[i] = readey();

    for (int i=1; i<7; i++) {

        ledMatrix[i] = readey();        // RIO: todo: fix loop cursor, 1 entry wasted
        bitWrite(ledMatrix[i], 6, 0);   // RIO: todo: fix loop cursor, 1 entry wasted
        bitWrite(ledMatrix[i], 7, 0);   // RIO: todo: fix loop cursor, 1 entry wasted

        presetTune[i] = readey();
        vol[i] = readey();
    } // 37

    arpSpeed = readey();
    lfoShape = readey();
    lfoSpeed = readey();
    lfoDepth = readey();
    envNumber1 = readey();
 
    if      (envNumber1 == 1) envShape1 = 0;
    else if (envNumber1 == 2) envShape1 = B0100;
    else if (envNumber1 == 3) envShape1 = B1000;
    else if (envNumber1 == 4) envShape1 = B1010;
    else if (envNumber1 == 5) envShape1 = B1011;
    else if (envNumber1 == 6) envShape1 = B1100;
    else if (envNumber1 == 7) envShape1 = B1101;
    else if (envNumber1 == 8) envShape1 = B1110;
    triggerEnv();

    envSpd = readey();
    envSpeed(envSpd);
    seqSpeed = readey();
    detune = readey();
    doDetune(detune);
    glide = readey();
    glider = map(glide, 0, 256, 50, 1);
    noiseFreq1 = readey();

    //update register
    AY3(6, noiseFreq1+1);

    data7ALast = 0;
    data7BLast = 0;

    if (bitRead(ledMatrix[4], 0) == 1) set_chA_amplitude(vol[1], true); else set_chA_amplitude(vol[1], false);
    if (bitRead(ledMatrix[4], 1) == 1) set_chB_amplitude(vol[2], true); else set_chB_amplitude(vol[2], false);
    if (bitRead(ledMatrix[4], 2) == 1) set_chC_amplitude(vol[3], true); else set_chC_amplitude(vol[3], false);
    if (bitRead(ledMatrix[4], 3) == 1) set_chD_amplitude(vol[4], true); else set_chD_amplitude(vol[4], false);
    if (bitRead(ledMatrix[4], 4) == 1) set_chE_amplitude(vol[5], true); else set_chE_amplitude(vol[5], false);
    if (bitRead(ledMatrix[4], 5) == 1) set_chF_amplitude(vol[6], true); else set_chF_amplitude(vol[6], false);

    updatePitch();

    arpRange = map(lfoDepth, 0, 256, 0, 6);

    seqNoise1 = readey();
    seqNoise2 = readey();
    seqVoice1 = readey();
    seqVoice2 = readey();

    for(int i=0; i<8; i++) {
        seqNoise[i]     = bitRead(seqNoise1,i);
        seqNoise[i+8]   = bitRead(seqNoise2,i);

        seqVoice[i]     = bitRead(seqVoice1,i);
        seqVoice[i+8]   = bitRead(seqVoice2,i);
    }

    envNumber2 = readey();
    if (envNumber2 > 8) envNumber2 = envNumber1;
    if (envNumber2 == 1) envShape2 = 0;
    if (envNumber2 == 2) envShape2 = B0100;
    if (envNumber2 == 3) envShape2 = B1000;
    if (envNumber2 == 4) envShape2 = B1010;
    if (envNumber2 == 5) envShape2 = B1011;
    if (envNumber2 == 6) envShape2 = B1100;
    if (envNumber2 == 7) envShape2 = B1101;
    if (envNumber2 == 8) envShape2 = B1110;

    noiseFreq2 = readey();
    if (noiseFreq2 > 15) noiseFreq2 = noiseFreq1;
    
    AY32(6, noiseFreq2);
}