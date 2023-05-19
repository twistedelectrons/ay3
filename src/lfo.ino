float phaseTemp;

void doLfo()
{
    // LFO
    if (lfoShape == 1) {
        phaseTemp = lfoDepth;
        phaseTemp = phaseTemp / 1023;

        if (!sync) {
            lfoPhase += (0.0001 + (lfoSpeed / 20000));
            if (lfoPhase > 1) lfoPhase -= 1;
        }

        lfo = (lfoPhase - 0.5) * 2 * phaseTemp * lfoMax;

    } else if (lfoShape == 2) {
        phaseTemp = lfoDepth;
        phaseTemp = phaseTemp / 1023;
        
        if (!sync) {
            lfoPhase -= (0.0001 + (lfoSpeed / 20000));
            if (lfoPhase < 0) lfoPhase += 1;
        }

        lfo = (lfoPhase - 0.5) * 2 * phaseTemp * lfoMax;

    } else if (lfoShape == 3) { // RIO: note: identical with lfoShape 1
        phaseTemp = lfoDepth;
        phaseTemp = phaseTemp / 1023;

        if (!sync) {
            lfoPhase += (0.0001 + (lfoSpeed / 20000));
            if (lfoPhase > 1) lfoPhase -= 1;
        }

        lfo = (lfoPhase - 0.5) * 2 * phaseTemp * lfoMax;

    } else if (lfoShape == 4) {
        phaseTemp = lfoDepth;
        phaseTemp = phaseTemp / 1023;

        if (!sync) {
            lfoPhase += (0.0001 + (lfoSpeed / 20000));
            if (lfoPhase > 1) lfoPhase -= 1;
        }

        if      (lfoPhase <= 0.2)                   lfo = lfoPhase              * 5 * phaseTemp * lfoMax;
        else if (lfoPhase > 0.2 && lfoPhase <= 0.4) lfo = (1-(lfoPhase - 0.2))  * 5 * phaseTemp * lfoMax;
        else if (lfoPhase > 0.4 && lfoPhase <= 0.6) lfo = (lfoPhase - 0.4)      * 5 * phaseTemp * lfoMax;
        else if (lfoPhase > 0.6 && lfoPhase <= 0.8) lfo = (1-(lfoPhase - 0.6))  * 5 * phaseTemp * lfoMax;
        else if (lfoPhase > 0.8)                    lfo = (lfoPhase - 0.8)      * 5 * phaseTemp * lfoMax;

        lfo = (lfo - 0.5) * 2;
    }

    //ARP
    if (!sync) {
        arpCounter++;
        if (arpCounter > arpSpeed * 4) {
            arpCounter = 0;

            if (held  > 0)  if (sync == 0) doArpMaster();
            if (held1 > 0)  if (sync == 0) doArp1();
            if (held2 > 0)  if (sync == 0) doArp2();
            if (held3 > 0)  if (sync == 0) doArp3();
            if (held4 > 0)  if (sync == 0) doArp4();
            if (held5 > 0)  if (sync == 0) doArp5();
            if (held6 > 0)  if (sync == 0) doArp6();
        }
    }

    updatePitch();
}