void receivedNote(byte channel, int note, int vel)
{
    note++;

    if (channel == masterChannel && seqSetup == 0)
        seqNote[selectedStep] = note; // in setup mode, do the note thing

    if ((masterChannel == 1 && channel == 1) ||
        (masterChannel != 1 && channel == masterChannel))
    {

        if (chord == 8)
        {

            // polyphinc
            channel = 17;
            held = 0;

            // note on
            if (vel != 0)
            {

                // Look for free voice
                for (int i = 1; i < 7; i++)
                    if (slots[i] == 0)
                        temp = i;

                base[staggered[temp]] = note;
                slots[temp] = note;
                triggerEnv();

                // note off
            }
            else
            {

                // look for note in slot
                for (int i = 1; i < 7; i++)
                {
                    if (slots[i] == note)
                    {
                        slots[i] = 0;
                        base[staggered[i]] = 0;
                    }
                }
            }
        }

        if (channel < 17)
        {

            // omni chanel
            if (vel == 0)
            {

                if (held > 0)
                    held--;

                // remove note from noteMem
                for (int i = 0; i <= held + 1; i++)
                    if (noteMem[i] == note)
                        noteMem[i] = 00;

                isort(noteMem, held + 1);

                if (held <= 0)
                {
                    base[1] = 0;
                    base[2] = 0;
                    base[3] = 0;
                    base[4] = 0;
                    base[5] = 0;
                    base[6] = 0;

                    AY3(11, 255);
                    AY3(12, 255);

                    AY32(11, 255);
                    AY32(12, 255);

                    bitWrite(data7A, 0, 1);
                    bitWrite(data7A, 1, 1);
                    bitWrite(data7A, 2, 1);
                    bitWrite(data7B, 0, 1);
                    bitWrite(data7B, 1, 1);
                    bitWrite(data7B, 2, 1);
                }

                // play
            }
            else
            {

                key = note;

                held++;
                triggerEnv();
                envSpeed(lastEnvSpeed);

                // add note to mem
                if (held > 19)
                    held = 19;
                noteMem[held - 1] = note;
                isort(noteMem, held);

                if (retrig == 1)
                {
                    seqCounter = seqSpeed;
                    seqStep = 0;
                    doSeq();
                }

                base[1] = base[2] = base[3] = base[4] = base[5] = base[6] = note;
                handleBend(1, bender);

                if (held == 1)
                {
                    updatePitch();

                    if (base[1] != 0)
                        pitch[1] = destiPitch[1];
                    if (base[2] != 0)
                        pitch[2] = destiPitch[2];
                    if (base[3] != 0)
                        pitch[3] = destiPitch[3];
                    if (base[4] != 0)
                        pitch[4] = destiPitch[4];
                    if (base[5] != 0)
                        pitch[5] = destiPitch[5];
                    if (base[6] != 0)
                        pitch[6] = destiPitch[6];
                }
            }
        }
    }

    if (masterChannel == 1)
    {

        if (channel == 2)
        {

            // note on
            if (vel != 0)
            {

                held1++;
                triggerEnv();
                envSpeed(lastEnvSpeed);

                if (held1 > 19)
                    held1 = 19;
                noteMem1[held1 - 1] = note;
                isort(noteMem1, held1);

                base[1] = note;
                handleBend(1, bender);
                if (base[1] != 0)
                    pitch[1] = destiPitch[1];

                // note off
            }
            else
            {

                if (held1 > 0)
                    held1--;

                // remove note from noteMem
                for (int i = 0; i <= held1 + 1; i++)
                    if (noteMem1[i] == note)
                        noteMem1[i] = 00;

                isort(noteMem1, held1 + 1);
                if (held1 == 0)
                    base[1] = 0;
            }
        }

        if (channel == 3)
        {

            // note on
            if (vel != 0)
            {

                held2++;
                triggerEnv();
                envSpeed(lastEnvSpeed);

                if (held2 > 19)
                    held2 = 19;
                noteMem2[held2 - 1] = note;
                isort(noteMem2, held2);

                base[2] = note;
                handleBend(1, bender);
                if (base[2] != 0)
                    pitch[2] = destiPitch[2];

                // note off
            }
            else
            {

                if (held2 > 0)
                    held2--;

                // remove note from noteMem
                for (int i = 0; i <= held2 + 1; i++)
                    if (noteMem2[i] == note)
                        noteMem2[i] = 00;

                isort(noteMem2, held2 + 1);
                if (held2 == 0)
                    base[2] = 0;
            }
        }

        if (channel == 4)
        {

            // note on
            if (vel != 0)
            {

                held3++;
                triggerEnv();
                envSpeed(lastEnvSpeed);

                if (held3 > 19)
                    held3 = 19;
                noteMem3[held3 - 1] = note;
                isort(noteMem3, held3);

                base[3] = note;
                handleBend(1, bender);
                if (base[3] != 0)
                    pitch[3] = destiPitch[3];

                // note off
            }
            else
            {

                if (held3 > 0)
                    held3--;

                // remove note from noteMem
                for (int i = 0; i <= held3 + 1; i++)
                    if (noteMem3[i] == note)
                        noteMem3[i] = 00;

                isort(noteMem3, held3 + 1);
                if (held3 == 0)
                    base[3] = 0;
            }
        }

        if (channel == 5)
        {

            // note on
            if (vel != 0)
            {

                held4++;
                triggerEnv();
                envSpeed(lastEnvSpeed);

                if (held4 > 19)
                    held4 = 19;
                noteMem4[held4 - 1] = note;
                isort(noteMem4, held4);

                base[4] = note;
                handleBend(1, bender);
                if (base[4] != 0)
                    pitch[4] = destiPitch[4];

                // note off
            }
            else
            {

                if (held4 > 0)
                    held4--;

                // remove note from noteMem
                for (int i = 0; i <= held4 + 1; i++)
                    if (noteMem4[i] == note)
                        noteMem4[i] = 00;

                isort(noteMem4, held4 + 1);
                if (held4 == 0)
                    base[4] = 0;
            }
        }

        if (channel == 6)
        {

            // note on
            if (vel != 0)
            {

                held5++;
                triggerEnv();
                envSpeed(lastEnvSpeed);

                if (held5 > 19)
                    held5 = 19;
                noteMem5[held5 - 1] = note;
                isort(noteMem5, held5);

                base[5] = note;
                handleBend(1, bender);
                if (base[5] != 0)
                    pitch[5] = destiPitch[5];

                // note off
            }
            else
            {

                if (held5 > 0)
                    held5--;

                // remove note from noteMem
                for (int i = 0; i <= held5 + 1; i++)
                    if (noteMem5[i] == note)
                        noteMem5[i] = 00;

                isort(noteMem5, held5 + 1);
                if (held5 == 0)
                    base[5] = 0;
            }
        }

        if (channel == 7)
        {

            // note on
            if (vel != 0)
            {

                held6++;
                triggerEnv();
                envSpeed(lastEnvSpeed);

                if (held6 > 19)
                    held6 = 19;
                noteMem6[held6 - 1] = note;
                isort(noteMem6, held6);

                base[6] = note;
                handleBend(1, bender);
                if (base[6] != 0)
                    pitch[6] = destiPitch[6];

                // note off
            }
            else
            {

                if (held6 > 0)
                    held6--;

                // remove note from noteMem
                for (int i = 0; i <= held6 + 1; i++)
                    if (noteMem6[i] == note)
                        noteMem6[i] = 00;

                isort(noteMem6, held6 + 1);
                if (held6 == 0)
                    base[6] = 0;
            }
        }

        // trigger noise
        if (channel == 9)
        {
            if (vel == 0)
                bitWrite(ledMatrix[3], 0, 0);
            else
                bitWrite(ledMatrix[3], 0, 1);
        }
        if (channel == 10)
        {
            if (vel == 0)
                bitWrite(ledMatrix[3], 1, 0);
            else
                bitWrite(ledMatrix[3], 1, 1);
        }
        if (channel == 11)
        {
            if (vel == 0)
                bitWrite(ledMatrix[3], 2, 0);
            else
                bitWrite(ledMatrix[3], 2, 1);
        }
        if (channel == 12)
        {
            if (vel == 0)
                bitWrite(ledMatrix[3], 3, 0);
            else
                bitWrite(ledMatrix[3], 3, 1);
        }
        if (channel == 13)
        {
            if (vel == 0)
                bitWrite(ledMatrix[3], 4, 0);
            else
                bitWrite(ledMatrix[3], 4, 1);
        }
        if (channel == 14)
        {
            if (vel == 0)
                bitWrite(ledMatrix[3], 5, 0);
            else
                bitWrite(ledMatrix[3], 5, 1);
        }

        // Polyphonic, bitches!
        if (channel == 8)
        {

            held = 0;

            // note on
            if (vel != 0)
            {

                // Look for free voice
                for (int i = 1; i < 7; i++)
                    if (slots[i] == 0)
                        temp = i;

                base[staggered[temp]] = note;
                handleBend(1, bender);
                slots[temp] = note;
                triggerEnv();

                // note off
            }
            else
            {

                // look for note in slot
                for (int i = 1; i < 7; i++)
                {
                    if (slots[i] == note)
                    {
                        slots[i] = 0;
                        base[staggered[i]] = 0;
                    }
                }
            }
        }
    }
}