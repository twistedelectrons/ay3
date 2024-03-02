int matrixFlasher;
boolean flippedS = false;
boolean flippedN = false;
int alternator = 0;
int temp2;

void doLedMatrix()
{
    // 1 = 1,6
    // 2 = 2,6
    // 3 = 3,6
    // 4 = 4,6
    // 5 = 5,6
    // 6 = 1,7
    // 7 = 2,7
    // 8 = 3,7
    // bank = 4,7
    // preset = 5,7

    matrixFlasher += 3;
    if (matrixFlasher > 4000)
    {
        matrixFlasher = 0;
        mainCounter++;
    }

    if (seqDisplayCounter > 5999)
    {
        if (matrixFlasher > 1000)
            flippedN = true;
        else
            flippedN = false; // Normal
        if (mainCounter % 8 == 0)
            flippedS = true;
        else
            flippedS = false; // Slow
    }
    else
        flippedS = flippedN = false;

    // display ledNumber
    if (alternator == 1)
    {

        temp2 = B01000000;

        if (ledNumber == 2)
        {
            temp = B11111101;
        }
        if (ledNumber == 1)
        {
            temp = B11111110;
        }
        if (ledNumber == 3)
        {
            temp = B11111011;
        }
        if (ledNumber == 4)
        {
            temp = B11110111;
        }
        if (ledNumber == 5)
        {
            temp = B11101111;
        }
        if (ledNumber == 7)
        {
            temp = B11111101;
            temp2 = B10000000;
        }
        if (ledNumber == 6)
        {
            temp = B11111110;
            temp2 = B10000000;
        }
        if (ledNumber == 8)
        {
            temp = B11111011;
            temp2 = B10000000;
        }

        PORTB = temp;
        PORTC = temp2;
        miniDelay();

        temp = 255;
        if (mode == 1)
            bitWrite(temp, 4, 0);
        if (mode == 2)
            bitWrite(temp, 3, 0);

        PORTB = temp;
        PORTC = B10000000;
        miniDelay();
    }
    else
    { // display ledMatrix

        if (flippedN && pressedRow == 2)
        {
            if (ledMatrix[2] != 0)
                temp = 0;
            else
                temp = B00111111;
        }
        else
            temp = ledMatrix[2];

        if (seqDisplayCounter < 6000)
            temp = ledMatrixPic[2];

        PORTB = B11111101;
        PORTC = temp;
        miniDelay();

        // voice states (bit 0..5)
        temp = ledMatrix[1];

        if (flippedN && pressedRow == 1)
        {

            // has actives
            if (temp)
            {

                // selected voice
                if (pressedCol < 7)
                {

                    // slow 8x
                    if (flippedS)
                        temp = B00000000; // clr all

                    // normal 1x  00XXXXXn clr voice n = 0, <<, cleanup (1: B00111110 ..)
                    else
                        temp &= B00111111 & ~(1 << (pressedCol - 1));

                    // no selection
                }
                else
                    temp = B00000000; // clr all

                // none actives
            }
            else
                temp = B00111111; // none --> set all
        }

        if (seqSetup == 0 && !writeChannel && !writeBoardRevision && seqDisplayCounter > 5999)
        {
            if (seqVoice[selectedStep] == 1)
                temp = B00111111;
            else
                temp = 0;
        }

        if (seqDisplayCounter < 6000)
            temp = ledMatrixPic[1];

        PORTB = B11111110;
        PORTC = temp;
        miniDelay();

        // noise with 3 states (0, 1, 2 selection)
        temp = ledMatrix[3];

        if (flippedN && pressedRow == 3)
        {

            // 1st chip noise selection
            if (!selectedChip && pressedCol < 4)
            {

                // slow 8x
                if (flippedS)
                {
                    if (temp)
                        temp = B00000000; // clr
                    else
                        temp |= B00111000; // set 1st bitblock

                    // normal 1x
                }
                else
                {
                    if (temp)
                        temp &= B00111000; // get 1st bitblock
                    else
                        temp = B00111111; // set all
                }

                // 2nd chip noise selection
            }
            else if (selectedChip && pressedCol > 3 && pressedCol < 7)
            {

                // slow 8x
                if (flippedS)
                {
                    if (temp)
                        temp = B00000000; // clr
                    else
                        temp |= B00000111; // set 2nd bitblock

                    // normal 1x
                }
                else
                {
                    if (temp)
                        temp &= B00000111; // get 2nd bitblock
                    else
                        temp = B00111111; // set all
                }

                // no chip selection
            }
            else
            {

                if (temp)
                    temp = B00000000; // all ---> clr
                else
                    temp = B00111111; // none --> set all
            }
        }

        if (seqSetup == 0 && !writeChannel && !writeBoardRevision && seqDisplayCounter > 5999)
        {
            if (seqNoise[selectedStep] == 1)
                temp = B00111111;
            else
                temp = 0;
        }

        if (seqDisplayCounter < 6000)
            temp = ledMatrixPic[3];

        PORTB = B11111011;
        PORTC = temp;
        miniDelay();

        if (flippedN && pressedRow == 4)
        {
            if (ledMatrix[4] != 0)
                temp = 0;
            else
                temp = B00111111;
        }
        else
            temp = ledMatrix[4];

        if (seqDisplayCounter < 6000)
            temp = ledMatrixPic[4];

        PORTB = B11110111;
        PORTC = temp;
        miniDelay();

        if (flippedN && pressedRow == 5)
        {
            if (ledMatrix[5] != 0)
                temp = 0;
            else
                temp = B00111111;
        }
        else
            temp = ledMatrix[5];

        if (seqDisplayCounter < 6000)
            temp = ledMatrixPic[5];

        PORTB = B11101111;
        PORTC = temp;
        miniDelay();
    }

    if (!writeChannel && !writeBoardRevision)
        alternator = !alternator;
}