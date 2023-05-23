void doPots()
{
    potJob++;
    if (potJob > 5)
        potJob = 1;

    switch (potJob)
    {
    case 1:
        analogTemp = analogRead(A4) >> 2;
        if (analogTemp > (potLast[0] + 1) || analogTemp < (potLast[0] - 1))
        {
            lfoSpeed = analogTemp;
            potLast[0] = analogTemp;
            arpSpeed = 256 - analogTemp;
        }
        break;

    case 2:
        analogTemp = analogRead(A5) >> 2;
        if (analogTemp > (potLast[1] + 1) || analogTemp < (potLast[1] - 1))
        {
            lfoDepth = analogTemp;
            potLast[1] = analogTemp;
            arpRange = lfoDepth >> 6;
        }
        break;

    case 3:
        analogTemp = analogRead(A7) >> 6;
        if (analogTemp > (potLast[3] + 1) || analogTemp < (potLast[3] - 1))
        {
            glider = (16 - analogTemp) << 2;
            potLast[3] = analogTemp;
        }
        break;

    case 4:
        analogTemp = analogRead(A6) >> 2;
        if (analogTemp > (potLast[4] + 1) || analogTemp < (potLast[4] - 1))
        {
            detune = analogTemp;
            doDetune(detune);

            if (potLast[4] > -1)
            {
                if (detune < 127)
                    ledNumber = numberOld;
                else
                    ledNumber = chord;
            }

            potLast[4] = analogTemp;
        }
        break;

    case 5:
        analogTemp = analogRead(A0) >> 2;
        if (analogTemp > (potLast[2] + 1) || analogTemp < (potLast[2] - 1))
        {
            seqSpeed = 16 - (analogTemp >> 4);
            lastEnvSpeed = analogTemp;
            envSpeed(analogTemp);
            potLast[2] = analogTemp;
        }
        break;
    }
}