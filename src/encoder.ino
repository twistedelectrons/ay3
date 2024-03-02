void encoderMoved(int dir)
{
    if (seqSetup == 0)
    {
        selectedStep += dir;
        byte max = writeBoardRevision ? 2 : 16;

        if (selectedStep > max-1)
            selectedStep = max-1;
        else if (selectedStep < 0)
            selectedStep = 0;

        if (selectedStep <= 7)
            ledNumber = selectedStep + 1;
        else
            ledNumber = selectedStep - 7;

        seqDisplayCounter = 0;

        switch (selectedStep)
        {

        case 0:
            ledMatrixPic[1] = B010000;
            ledMatrixPic[2] = B010000;
            ledMatrixPic[3] = B010000;
            ledMatrixPic[4] = B010000;
            ledMatrixPic[5] = B010000;
            break;

        case 1:
            ledMatrixPic[1] = B111000;
            ledMatrixPic[2] = B100000;
            ledMatrixPic[3] = B111000;
            ledMatrixPic[4] = B001000;
            ledMatrixPic[5] = B111000;
            break;

        case 2:
            ledMatrixPic[1] = B111000;
            ledMatrixPic[2] = B100000;
            ledMatrixPic[3] = B111000;
            ledMatrixPic[4] = B100000;
            ledMatrixPic[5] = B111000;
            break;

        case 3:
            ledMatrixPic[1] = B101000;
            ledMatrixPic[2] = B101000;
            ledMatrixPic[3] = B111000;
            ledMatrixPic[4] = B100000;
            ledMatrixPic[5] = B100000;
            break;

        case 4:
            ledMatrixPic[1] = B111000;
            ledMatrixPic[2] = B001000;
            ledMatrixPic[3] = B111000;
            ledMatrixPic[4] = B100000;
            ledMatrixPic[5] = B111000;
            break;

        case 5:
            ledMatrixPic[1] = B111000;
            ledMatrixPic[2] = B001000;
            ledMatrixPic[3] = B111000;
            ledMatrixPic[4] = B101000;
            ledMatrixPic[5] = B111000;
            break;

        case 6:
            ledMatrixPic[1] = B111000;
            ledMatrixPic[2] = B100000;
            ledMatrixPic[3] = B100000;
            ledMatrixPic[4] = B100000;
            ledMatrixPic[5] = B100000;
            break;

        case 7:
            ledMatrixPic[1] = B111000;
            ledMatrixPic[2] = B101000;
            ledMatrixPic[3] = B111000;
            ledMatrixPic[4] = B101000;
            ledMatrixPic[5] = B111000;
            break;

        case 8:
            ledMatrixPic[1] = B111000;
            ledMatrixPic[2] = B101000;
            ledMatrixPic[3] = B111000;
            ledMatrixPic[4] = B100000;
            ledMatrixPic[5] = B111000;
            break;

        case 9:
            ledMatrixPic[1] = B111001;
            ledMatrixPic[2] = B101001;
            ledMatrixPic[3] = B101001;
            ledMatrixPic[4] = B101001;
            ledMatrixPic[5] = B111001;
            break;

        case 10:
            ledMatrixPic[1] = B010001;
            ledMatrixPic[2] = B010001;
            ledMatrixPic[3] = B010001;
            ledMatrixPic[4] = B010001;
            ledMatrixPic[5] = B010001;
            break;

        case 11:
            ledMatrixPic[1] = B111001;
            ledMatrixPic[2] = B100001;
            ledMatrixPic[3] = B111001;
            ledMatrixPic[4] = B001001;
            ledMatrixPic[5] = B111001;
            break;

        case 12:
            ledMatrixPic[1] = B111001;
            ledMatrixPic[2] = B100001;
            ledMatrixPic[3] = B111001;
            ledMatrixPic[4] = B100001;
            ledMatrixPic[5] = B111001;
            break;

        case 13:
            ledMatrixPic[1] = B101001;
            ledMatrixPic[2] = B101001;
            ledMatrixPic[3] = B111001;
            ledMatrixPic[4] = B100001;
            ledMatrixPic[5] = B100001;
            break;

        case 14:
            ledMatrixPic[1] = B111001;
            ledMatrixPic[2] = B001001;
            ledMatrixPic[3] = B111001;
            ledMatrixPic[4] = B100001;
            ledMatrixPic[5] = B111001;
            break;

        case 15:
            ledMatrixPic[1] = B111001;
            ledMatrixPic[2] = B001001;
            ledMatrixPic[3] = B111001;
            ledMatrixPic[4] = B101001;
            ledMatrixPic[5] = B111001;
            break;
        }

        if (writeChannel)
            EEPROM.write(3802, selectedStep + 1);

        if (writeBoardRevision)
            EEPROM.write(3803, selectedStep + 1);
    }
    else
    {

        // not seqSetup
        if (pressedRow == 0)
        {
            if (mode == 1)
            {
                preset += dir;

                if (preset > 7)
                    preset = 7;
                else if (preset < 0)
                    preset = 0;

                ledNumber = preset + 1;
                load();
            }
            else if (mode == 2)
            {
                bank += dir;

                if (bank > 7)
                    bank = 7;
                else if (bank < 0)
                    bank = 0;

                ledNumber = bank + 1;
                load();
            }

            numberOld = ledNumber;
        } // PRESET CHANGE

        if (voiceMode < 3)
        {

            if (pressedRow == 1 && pressedCol == 1)
            {
                vol[pressedCol] += dir;

                if (vol[pressedCol] > 15)
                    vol[pressedCol] = 15;
                else if (vol[pressedCol] < 0)
                    vol[pressedCol] = 0;

                if (bitRead(ledMatrix[4], 0) == 1)
                    set_chA_amplitude(vol[pressedCol], true);
                else
                    set_chA_amplitude(vol[pressedCol], false);

                ledNumber = 1 + (vol[pressedCol] / 2);
            }
            else if (pressedRow == 1 && pressedCol == 2)
            {
                vol[pressedCol] += dir;

                if (vol[pressedCol] > 15)
                    vol[pressedCol] = 15;
                else if (vol[pressedCol] < 0)
                    vol[pressedCol] = 0;

                if (bitRead(ledMatrix[4], 1) == 1)
                    set_chB_amplitude(vol[pressedCol], true);
                else
                    set_chB_amplitude(vol[pressedCol], false);

                ledNumber = 1 + (vol[pressedCol] / 2);
            }
            else if (pressedRow == 1 && pressedCol == 3)
            {
                vol[pressedCol] += dir;

                if (vol[pressedCol] > 15)
                    vol[pressedCol] = 15;
                else if (vol[pressedCol] < 0)
                    vol[pressedCol] = 0;

                if (bitRead(ledMatrix[4], 2) == 1)
                    set_chC_amplitude(vol[pressedCol], true);
                else
                    set_chC_amplitude(vol[pressedCol], false);

                ledNumber = 1 + (vol[pressedCol] / 2);
            }
            else if (pressedRow == 1 && pressedCol == 4)
            {
                vol[pressedCol] += dir;

                if (vol[pressedCol] > 15)
                    vol[pressedCol] = 15;
                else if (vol[pressedCol] < 0)
                    vol[pressedCol] = 0;

                if (bitRead(ledMatrix[4], 3) == 1)
                    set_chD_amplitude(vol[pressedCol], true);
                else
                    set_chD_amplitude(vol[pressedCol], false);

                ledNumber = 1 + (vol[pressedCol] / 2);
            }
            else if (pressedRow == 1 && pressedCol == 5)
            {
                vol[pressedCol] += dir;

                if (vol[pressedCol] > 15)
                    vol[pressedCol] = 15;
                else if (vol[pressedCol] < 0)
                    vol[pressedCol] = 0;

                if (bitRead(ledMatrix[4], 4) == 1)
                    set_chE_amplitude(vol[pressedCol], true);
                else
                    set_chE_amplitude(vol[pressedCol], false);

                ledNumber = 1 + (vol[pressedCol] / 2);
            }
            else if (pressedRow == 1 && pressedCol == 6)
            {
                vol[pressedCol] += dir;

                if (vol[pressedCol] > 15)
                    vol[pressedCol] = 15;
                else if (vol[pressedCol] < 0)
                    vol[pressedCol] = 0;

                if (bitRead(ledMatrix[4], 5) == 1)
                    set_chF_amplitude(vol[pressedCol], true);
                else
                    set_chF_amplitude(vol[pressedCol], false);

                ledNumber = 1 + (vol[pressedCol] / 2);
            }
        }
        else if (voiceMode == 3)
        {

            if (pressedRow == 1 && pressedCol == 1)
            {
                presetTune[1] -= dir;

                if (presetTune[1] > 124)
                    presetTune[1] = 124;
                if (presetTune[1] < 76)
                    presetTune[1] = 76;

                if (!chord)
                    tune[1] = presetTune[1];
            }

            if (pressedRow == 1 && pressedCol == 2)
            {
                presetTune[2] -= dir;

                if (presetTune[2] > 124)
                    presetTune[2] = 124;
                if (presetTune[2] < 76)
                    presetTune[2] = 76;

                if (!chord)
                    tune[2] = presetTune[2];
            }

            if (pressedRow == 1 && pressedCol == 3)
            {
                presetTune[3] -= dir;
                if (presetTune[3] > 124)
                    presetTune[3] = 124;
                if (presetTune[3] < 76)
                    presetTune[3] = 76;

                if (!chord)
                    tune[3] = presetTune[3];
            }

            if (pressedRow == 1 && pressedCol == 4)
            {
                presetTune[4] -= dir;

                if (presetTune[4] > 124)
                    presetTune[4] = 124;
                if (presetTune[4] < 76)
                    presetTune[4] = 76;

                if (!chord)
                    tune[4] = presetTune[4];
            }

            if (pressedRow == 1 && pressedCol == 5)
            {
                presetTune[5] -= dir;

                if (presetTune[5] > 124)
                    presetTune[5] = 124;
                if (presetTune[5] < 76)
                    presetTune[5] = 76;

                if (!chord)
                    tune[5] = presetTune[5];
            }

            if (pressedRow == 1 && pressedCol == 6)
            {
                presetTune[6] -= dir;
                if (presetTune[6] > 124)
                    presetTune[6] = 124;
                if (presetTune[6] < 76)
                    presetTune[6] = 76;

                if (!chord)
                    tune[6] = presetTune[6];
            }
        }

        if (pressedRow == 2)
        {
            lfoShape += dir;

            if (lfoShape > 8)
                lfoShape -= 8;
            if (lfoShape < 1)
                lfoShape += 8;

            ledNumber = lfoShape;
        }

        if (pressedRow == 3)
        {
            if (!selectedChip)
            {
                noiseFreq1 -= dir;

                if (noiseFreq1 > 31)
                    noiseFreq1 = 31;
                else if (noiseFreq1 < 0)
                    noiseFreq1 = 0;

                AY3(6, noiseFreq1 + 1);
                if (noiseFreq1 < 31)
                {
                    ledNumber = 9 - (noiseFreq1 / 4);
                }
                else
                {
                    ledNumber = 9 - (1 + noiseFreq1 / 4);
                }
            }
            else
            {
                noiseFreq2 -= dir;

                if (noiseFreq2 > 31)
                    noiseFreq2 = 31;
                else if (noiseFreq2 < 0)
                    noiseFreq2 = 0;

                AY32(6, noiseFreq2);

                ledNumber = 9 - (1 + noiseFreq2 / 4);
            }
        }

        if (pressedRow == 4)
        {
            if (!selectedChip)
            {
                envNumber1 += dir;

                if (envNumber1 > 8)
                    envNumber1 -= 8;
                else if (envNumber1 < 1)
                    envNumber1 = 8;

                ledNumber = envNumber1;

                if (envNumber1 == 1)
                    envShape1 = 0;
                else if (envNumber1 == 2)
                    envShape1 = B0100;
                else if (envNumber1 == 3)
                    envShape1 = B1000;
                else if (envNumber1 == 4)
                    envShape1 = B1010;
                else if (envNumber1 == 5)
                    envShape1 = B1011;
                else if (envNumber1 == 6)
                    envShape1 = B1100;
                else if (envNumber1 == 7)
                    envShape1 = B1101;
                else if (envNumber1 == 8)
                    envShape1 = B1110;
            }
            else
            {
                envNumber2 += dir;

                if (envNumber2 > 8)
                    envNumber2 -= 8;
                else if (envNumber2 < 1)
                    envNumber2 = 8;

                ledNumber = envNumber2;

                if (envNumber2 == 1)
                    envShape2 = 0;
                else if (envNumber2 == 2)
                    envShape2 = B0100;
                else if (envNumber2 == 3)
                    envShape2 = B1000;
                else if (envNumber2 == 4)
                    envShape2 = B1010;
                else if (envNumber2 == 5)
                    envShape2 = B1011;
                else if (envNumber2 == 6)
                    envShape2 = B1100;
                else if (envNumber2 == 7)
                    envShape2 = B1101;
                else if (envNumber2 == 8)
                    envShape2 = B1110;
            }

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

            if (held > 0)
                triggerEnv();
        }
    }
}

void doEncoder()
{
    if (encTimer == 0)
    {

        // Read the current state of CLK
        int currentStateCLK = digitalRead(ENCPINA);

        // If last and current state of CLK are different, then pulse occurred
        // React to only 1 state change to avoid double count
        if (currentStateCLK != lastStateCLK && currentStateCLK == 1 && lastStateCLK != -1)
        {

            // If the DT state is different than the CLK state then
            // the encoder is rotating CCW so decrement
            if (digitalRead(ENCPINB) != currentStateCLK)
            {
                encTimer = 300;
                encoderMoved(-1);
            }
            else
            {
                // Encoder is rotating CW so increment
                encTimer = 300;
                encoderMoved(1);
            }
        }

        // Remember last CLK state
        lastStateCLK = currentStateCLK;
    }
    else
        encTimer--;
}