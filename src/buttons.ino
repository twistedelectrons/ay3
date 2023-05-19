int buttPhase = 0;

void doButtons()
{
    PORTB = B11111111;
    // Butt Matrix

    buttPhase++;
    if (buttPhase > 4)
        buttPhase = 0;

    switch (buttPhase)
    {

    // Phase 1
    case 0:
        PORTA &= ~_BV(1); // digitalWrite (A1-25, LOW);
        PORTA |= _BV(2);  // digitalWrite (A2, HIGH);
        PORTA |= _BV(3);  // digitalWrite (A3, HIGH);
        PORTC |= _BV(0);  // digitalWrite (16, HIGH);

        butt[1] = digitalRead(5); // ENCODER SWITCH
        butt[2] = digitalRead(6); // CHANNEL: b
        butt[3] = digitalRead(7); // CHANNEL: f

        if (butt[1] != buttLast[1])
            buttPressed(1, butt[1]);
        if (butt[2] != buttLast[2])
            buttPressed(2, butt[2]);
        if (butt[3] != buttLast[3])
            buttPressed(3, butt[3]);
        break;

    // Phase 2
    case 1:
        PORTA |= _BV(1);  // digitalWrite (A1-25, HIGH);
        PORTA &= ~_BV(2); // digitalWrite (A2-26, LOW);
        PORTA |= _BV(3);  // digitalWrite (A3-27, HIGH);
        PORTC |= _BV(0);  // digitalWrite (16, HIGH);

        butt[4] = digitalRead(5); // ROW 5: SEQ
        butt[5] = digitalRead(6); // ROW 2: LFO/ARP
        butt[6] = digitalRead(7); // CHANNEL: c

        if (butt[4] != buttLast[4])
            buttPressed(4, butt[4]);
        if (butt[5] != buttLast[5])
            buttPressed(5, butt[5]);
        if (butt[6] != buttLast[6])
            buttPressed(6, butt[6]);
        break;

    // Phase 3
    case 2:
        PORTA |= _BV(1);  // digitalWrite (A1-25, HIGH);
        PORTA |= _BV(2);  // digitalWrite (A2-26, HIGH);
        PORTA &= ~_BV(3); // digitalWrite (A3-27, LOW);
        PORTC |= _BV(0);  // digitalWrite (16, HIGH);

        butt[7] = digitalRead(5); // ROW 4: ENV
        butt[8] = digitalRead(6); // ROW 1: VOICE
        butt[9] = digitalRead(7); // CHANNEL: d

        if (butt[7] != buttLast[7])
            buttPressed(7, butt[7]);
        if (butt[8] != buttLast[8])
            buttPressed(8, butt[8]);
        if (butt[9] != buttLast[9])
            buttPressed(9, butt[9]);
        break;

    // Phase 4
    case 3:
        PORTA |= _BV(1);  // digitalWrite (A1-25, HIGH);
        PORTA |= _BV(2);  // digitalWrite (A2-26, HIGH);
        PORTA |= _BV(3);  // digitalWrite (A3-27, HIGH);
        PORTC &= ~_BV(0); // digitalWrite (16, LOW);

        butt[10] = digitalRead(5); // ROW 3: NOISE
        butt[11] = digitalRead(6); // CHANNEL: a
        butt[12] = digitalRead(7); // CHANNEL: e

        if (butt[10] != buttLast[10])
            buttPressed(10, butt[10]);
        if (butt[11] != buttLast[11])
            buttPressed(11, butt[11]);
        if (butt[12] != buttLast[12])
            buttPressed(12, butt[12]);
        break;

    } // End buttMatrix
}

void buttPressed(int pin, int state)
{
    buttLast[pin] = state;

    if (pin == 4)
    {
        if (state == 1)
        {
            seqPressed = 0;
            ledNumber = numberOld;
        }
    }

    if (pin == 1)
    {
        if (state == 1)
        {
            savePressed = 0;
            ledNumber = numberOld;
            pressedRow = 0;
            encoderMoved(0);
        }
        else
        {

            if (mode == 1)
            {
                mode = 2;
                ledNumber = bank + 1;
            }
            else
            {
                mode = 1;
                ledNumber = preset + 1;
            }

            pressedRow = 0;
            savePressed = 1;
            countDown = 9;
            numberOld = ledNumber;
        }
    } // Preset/Bank

    // pressed
    if (state == 0)
    {

        // RIO: RELEASE SELECTED ROW
        if ((pressedRow == 1 && pin == 8 && voiceMode == 1) || // [V T E release]
            (pressedRow == 2 && pin == 5) ||
            (pressedRow == 3 && pin == 10) ||
            (pressedRow == 4 && pin == 7) ||
            (pressedRow == 5 && pin == 4))
        {

            pressedRow = 0;
            ledNumber = numberOld;

            return;
        }

        if (pin == 8)
        {
            pressedRow = 1;

            voicePressed = true;

            resetCounter = millis() + 4000;

            if (seqSetup == 1)
                encoderMoved(0);
            if (seqSetup == 0)
                seqVoice[selectedStep] = !seqVoice[selectedStep];
            else
            {

                if (seqDisplayCounter > 5999)
                {
                    numberOld = ledNumber;

                    oldMatrix[1] = ledMatrix[1];
                    oldMatrix[2] = ledMatrix[2];
                    oldMatrix[3] = ledMatrix[3];
                    oldMatrix[4] = ledMatrix[4];
                    oldMatrix[5] = ledMatrix[5];
                }

                voiceMode++;
                if (voiceMode > 3)
                    voiceMode = 1;

                seqDisplayCounter = 0;

                if (voiceMode == 1)
                {                              // enable
                    ledMatrixPic[1] = B011110; // RIO: Changed Char E
                    ledMatrixPic[2] = B000011;
                    ledMatrixPic[3] = B001111;
                    ledMatrixPic[4] = B000011;
                    ledMatrixPic[5] = B011110;
                }

                if (voiceMode == 2)
                {                              // vol
                    ledMatrixPic[1] = B110011; // RIO: Changed Char V
                    ledMatrixPic[2] = B110011;
                    ledMatrixPic[3] = B110011;
                    ledMatrixPic[4] = B011110;
                    ledMatrixPic[5] = B001100;
                }

                if (voiceMode == 3)
                {                              // tune
                    ledMatrixPic[1] = B111111; // RIO: Changed Char T
                    ledMatrixPic[2] = B111111;
                    ledMatrixPic[3] = B001100;
                    ledMatrixPic[4] = B001100;
                    ledMatrixPic[5] = B001100;
                }
            }
        } // vol

        if (pin == 10)
        {
            pressedRow = 3;
            if (seqSetup == 1)
                encoderMoved(0);
            if (seqSetup == 0)
                seqNoise[selectedStep] = !seqNoise[selectedStep];
        } // noise

        if (seqSetup == 1)
        {
            if (pin == 5)
            {
                pressedRow = 2;
                encoderMoved(0);
            } // lfo pitch
            if (pin == 7)
            {
                pressedRow = 4;
                encoderMoved(0);
            } // env
        }

        if (pin == 4)
        {
            numberOld = ledNumber;
            seqPressed = 1;
            countDown = 9;
            pressedRow = 5;

            oldMatrix[1] = ledMatrix[1];
            oldMatrix[2] = ledMatrix[2];
            oldMatrix[3] = ledMatrix[3];
            oldMatrix[4] = ledMatrix[4];
            oldMatrix[5] = ledMatrix[5];
            encoderMoved(0);
        } // seq

        if (pin == 11)
        {
            pressedCol = 1;
            selectedChip = false;
        }
        else if (pin == 2)
        {
            pressedCol = 2;
            selectedChip = false;
        }
        else if (pin == 6)
        {
            pressedCol = 3;
            selectedChip = false;
        }
        else if (pin == 9)
        {
            pressedCol = 4;
            selectedChip = true;
        }
        else if (pin == 12)
        {
            pressedCol = 5;
            selectedChip = true;
        }
        else if (pin == 3)
        {
            pressedCol = 6;
            selectedChip = true;
        }

        if (pressedRow != 1)
        {
            voiceMode = 1; // RIO: reset voiceMode
            if (pin == 11)
                bitWrite(ledMatrix[pressedRow], pressedCol - 1, !bitRead(ledMatrix[pressedRow], pressedCol - 1));
            else if (pin == 2)
                bitWrite(ledMatrix[pressedRow], pressedCol - 1, !bitRead(ledMatrix[pressedRow], pressedCol - 1));
            else if (pin == 6)
                bitWrite(ledMatrix[pressedRow], pressedCol - 1, !bitRead(ledMatrix[pressedRow], pressedCol - 1));
            else if (pin == 9)
                bitWrite(ledMatrix[pressedRow], pressedCol - 1, !bitRead(ledMatrix[pressedRow], pressedCol - 1));
            else if (pin == 12)
                bitWrite(ledMatrix[pressedRow], pressedCol - 1, !bitRead(ledMatrix[pressedRow], pressedCol - 1));
            else if (pin == 3)
                bitWrite(ledMatrix[pressedRow], pressedCol - 1, !bitRead(ledMatrix[pressedRow], pressedCol - 1));
        }

        // only do led thingy if in voice enable mode
        if (pressedRow == 1 && voiceMode == 1)
        {
            if (pin == 11)
                bitWrite(ledMatrix[pressedRow], pressedCol - 1, !bitRead(ledMatrix[pressedRow], pressedCol - 1));
            else if (pin == 2)
                bitWrite(ledMatrix[pressedRow], pressedCol - 1, !bitRead(ledMatrix[pressedRow], pressedCol - 1));
            else if (pin == 6)
                bitWrite(ledMatrix[pressedRow], pressedCol - 1, !bitRead(ledMatrix[pressedRow], pressedCol - 1));
            else if (pin == 9)
                bitWrite(ledMatrix[pressedRow], pressedCol - 1, !bitRead(ledMatrix[pressedRow], pressedCol - 1));
            else if (pin == 12)
                bitWrite(ledMatrix[pressedRow], pressedCol - 1, !bitRead(ledMatrix[pressedRow], pressedCol - 1));
            else if (pin == 3)
                bitWrite(ledMatrix[pressedRow], pressedCol - 1, !bitRead(ledMatrix[pressedRow], pressedCol - 1));
        }

        if (pin == 11 || pin == 2 || pin == 6 || pin == 9 || pin == 12 || pin == 3)
        {

            // RIO: fixed representation of noise level
            if (pressedRow == 1 ||
                pressedRow == 3 ||
                pressedRow == 4)
                encoderMoved(0);
        }
    }
    else
    {

        // released
        if (pin == 8)
            voicePressed = false;
    }
}