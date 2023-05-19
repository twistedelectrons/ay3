byte incomingByte;
byte note;
byte velocity;
boolean noteDown;
int state = 0; // state machine variable 0 = command waiting : 1 = note waitin : 2 = velocity waiting
byte channel;

void readMidi()
{
    while (MIDI.read())
    {
        switch (MIDI.getType())
        {
        case ControlChange:
            HandleControlChange(MIDI.getChannel(), MIDI.getData1(), MIDI.getData2());
            break;
        case NoteOn:
            HandleNoteOn(MIDI.getChannel(), MIDI.getData1(), MIDI.getData2());
            break;
        case NoteOff:
            HandleNoteOff(MIDI.getChannel(), MIDI.getData1(), MIDI.getData2());
            break;
        case Clock:
            HandleClock();
            break;
        case Stop:
            HandleStop();
            break;
        case Start:
            HandleStart();
            break;
        case PitchBend:
            handleBend(MIDI.getChannel(), MIDI.getData2());
            break;
        case ProgramChange:
            handleProgramChange(MIDI.getChannel(), MIDI.getData1(), MIDI.getData2());
            break; // RIO: fixed by a break (PC is handled and shouldn't go default)
        default:
            break;
        }
    }
}

void HandleNoteOn(byte channel, byte note, byte velocity)
{
    if (velocity != 0)
        receivedNote(channel, note, 127);
    else
        receivedNote(channel, note, 0);
}

void handleBend(byte channel, int value)
{
    bender = value;
    bend[1] = bend[2] = bend[3] = bend[4] = bend[5] = bend[6] = 0;

    if (value > 64)
    {
        bend[1] = map(value, 65, 127, 0, tp[base[1] + (100 - tune[1]) + offsetNote[1] + 2] - tp[base[1] + (100 - tune[1]) + offsetNote[1]]);
        bend[2] = map(value, 65, 127, 0, tp[base[2] + (100 - tune[2]) + offsetNote[2] + 2] - tp[base[2] + (100 - tune[2]) + offsetNote[2]]);
        bend[3] = map(value, 65, 127, 0, tp[base[3] + (100 - tune[3]) + offsetNote[3] + 2] - tp[base[3] + (100 - tune[3]) + offsetNote[3]]);
        bend[4] = map(value, 65, 127, 0, tp[base[4] + (100 - tune[4]) + offsetNote[4] + 2] - tp[base[4] + (100 - tune[4]) + offsetNote[4]]);
        bend[5] = map(value, 65, 127, 0, tp[base[5] + (100 - tune[5]) + offsetNote[5] + 2] - tp[base[5] + (100 - tune[5]) + offsetNote[5]]);
        bend[6] = map(value, 65, 127, 0, tp[base[6] + (100 - tune[6]) + offsetNote[6] + 2] - tp[base[6] + (100 - tune[6]) + offsetNote[6]]);
    }

    if (value < 64)
    {
        bend[1] = -map(value, 0, 63, tp[base[1] + (100 - tune[1]) + offsetNote[1]] - tp[base[1] + (100 - tune[1]) + offsetNote[1] - 2], 0);
        bend[2] = -map(value, 0, 63, tp[base[2] + (100 - tune[2]) + offsetNote[2]] - tp[base[2] + (100 - tune[2]) + offsetNote[2] - 2], 0);
        bend[3] = -map(value, 0, 63, tp[base[3] + (100 - tune[3]) + offsetNote[3]] - tp[base[3] + (100 - tune[3]) + offsetNote[3] - 2], 0);
        bend[4] = -map(value, 0, 63, tp[base[4] + (100 - tune[4]) + offsetNote[4]] - tp[base[4] + (100 - tune[4]) + offsetNote[4] - 2], 0);
        bend[5] = -map(value, 0, 63, tp[base[5] + (100 - tune[5]) + offsetNote[5]] - tp[base[5] + (100 - tune[5]) + offsetNote[5] - 2], 0);
        bend[6] = -map(value, 0, 63, tp[base[6] + (100 - tune[6]) + offsetNote[6]] - tp[base[6] + (100 - tune[6]) + offsetNote[6] - 2], 0);
    }
}

void HandleProgramChange(byte channel, byte value)
{
}

void HandleNoteOff(byte channel, byte note, byte velocity)
{
    receivedNote(channel, note, 0);
}

void HandleControlChange(byte channel, byte number, byte value)
{
    if (channel == masterChannel)
        receivedCC(number, value);
}

float lfoIncrements[] = {0.01041, 0.01388, 0.02083, 0.04166, 0.08333, 0.16666, 0.33333, 0.5};

void HandleClock()
{
    lfoPhase += lfoIncrements[int(lfoSpeed) >> 5];
    if (lfoPhase > 1)
        lfoPhase -= 1;

    seqCounter++;
    if (seqCounter >= clockSpeeds[seqSpeed])
        doSeq();

    if (held > 0)
    {
        arpCounter++;
        if (arpCounter >= clockSpeeds[map(lfoSpeed, 0, 256, 7, 0)])
        {
            arpCounter = 0;
            doArpMaster();
        }
    }
}

void HandleStart()
{
    sync = 1;
    seqCounter = 0;
    lfoPhase = 0;
}

void HandleContinue()
{
}

void HandleStop()
{
    sync = 0;
}

void receivedCC(int number, int value)
{
    switch (number)
    {

    case 2:
        analogTemp = value * 8;
        lfoSpeed = value * 2;
        arpSpeed = (1024 - analogTemp) >> 2;
        break;

    case 3:
        lfoDepth = value * 2;
        arpRange = map(lfoDepth, 0, 256, 0, 6);
        break;

    case 7:
        glide = value * 2;
        glider = map(glide, 0, 256, 50, 1);
        break;

    case 8:
        seqSpeed = envSpd = value * 2;
        envSpeed(envSpd);
        break;

    case 6:
        detune = value * 2;
        doDetune(detune);
        if (chord > 0)
            ledNumber = chord;
        break;

    case 9:
        noiseFreq1 = noiseFreq2 = value * 8;
        AY3(6, noiseFreq1 + 1);
        AY32(6, noiseFreq2);
        break;

    case 10:
        noiseFreq1 = value * 8;
        AY3(6, noiseFreq1);
        break;

    case 11:
        noiseFreq2 = value * 8;
        AY32(6, noiseFreq2);
        break;

    case 12:
        tune[1] = map(value, 0, 127, 124, 76);
        break;
    case 13:
        tune[2] = map(value, 0, 127, 124, 76);
        break;
    case 14:
        tune[3] = map(value, 0, 127, 124, 76);
        break;
    case 15:
        tune[4] = map(value, 0, 127, 124, 76);
        break;
    case 16:
        tune[5] = map(value, 0, 127, 124, 76);
        break;
    case 17:
        tune[6] = map(value, 0, 127, 124, 76);
        break;

    case 18:
        vol[0] = map(value, 0, 127, 0, 15);
        if (bitRead(ledMatrix[4], 0) == 1)
            set_chA_amplitude(vol[0], true);
        else
            set_chA_amplitude(vol[0], false);
        break;

    case 19:
        vol[1] = map(value, 0, 127, 0, 15);
        if (bitRead(ledMatrix[4], 1) == 1)
            set_chB_amplitude(vol[1], true);
        else
            set_chB_amplitude(vol[1], false);
        break;

    case 20:
        vol[2] = map(value, 0, 127, 0, 15);
        if (bitRead(ledMatrix[4], 2) == 1)
            set_chC_amplitude(vol[2], true);
        else
            set_chC_amplitude(vol[2], false);
        break;

    case 21:
        vol[3] = map(value, 0, 127, 0, 15);
        if (bitRead(ledMatrix[4], 3) == 1)
            set_chD_amplitude(vol[3], true);
        else
            set_chD_amplitude(vol[3], false);
        break;

    case 22:
        vol[4] = map(value, 0, 127, 0, 15);
        if (bitRead(ledMatrix[4], 4) == 1)
            set_chE_amplitude(vol[4], true);
        else
            set_chE_amplitude(vol[4], false);
        break;

    case 23:
        vol[5] = map(value, 0, 127, 0, 15);
        if (bitRead(ledMatrix[4], 5) == 1)
            set_chF_amplitude(vol[5], true);
        else
            set_chF_amplitude(vol[5], false);
        break;

    case 24:
        bitWrite(ledMatrix[1], 0, value >> 6);
        break;
    case 25:
        bitWrite(ledMatrix[1], 1, value >> 6);
        break;
    case 26:
        bitWrite(ledMatrix[1], 2, value >> 6);
        break;
    case 27:
        bitWrite(ledMatrix[1], 3, value >> 6);
        break;
    case 28:
        bitWrite(ledMatrix[1], 4, value >> 6);
        break;
    case 29:
        bitWrite(ledMatrix[1], 5, value >> 6);
        break;

    case 30:
        bitWrite(ledMatrix[3], 0, value >> 6);
        break;
    case 31:
        bitWrite(ledMatrix[3], 1, value >> 6);
        break;
    case 32:
        bitWrite(ledMatrix[3], 2, value >> 6);
        break;
    case 33:
        bitWrite(ledMatrix[3], 3, value >> 6);
        break;
    case 34:
        bitWrite(ledMatrix[3], 4, value >> 6);
        break;
    case 35:
        bitWrite(ledMatrix[3], 5, value >> 6);
        break;

    case 36:
        bitWrite(ledMatrix[2], 0, value >> 6);
        break;
    case 37:
        bitWrite(ledMatrix[2], 1, value >> 6);
        break;
    case 38:
        bitWrite(ledMatrix[2], 2, value >> 6);
        break;
    case 39:
        bitWrite(ledMatrix[2], 3, value >> 6);
        break;
    case 40:
        bitWrite(ledMatrix[2], 4, value >> 6);
        break;
    case 41:
        bitWrite(ledMatrix[2], 5, value >> 6);
        break;

    case 42:
        bitWrite(ledMatrix[4], 0, value >> 6);
        updateEnv();
        break;
    case 43:
        bitWrite(ledMatrix[4], 1, value >> 6);
        updateEnv();
        break;
    case 44:
        bitWrite(ledMatrix[4], 2, value >> 6);
        updateEnv();
        break;
    case 45:
        bitWrite(ledMatrix[4], 3, value >> 6);
        updateEnv();
        break;
    case 46:
        bitWrite(ledMatrix[4], 4, value >> 6);
        updateEnv();
        break;
    case 47:
        bitWrite(ledMatrix[4], 5, value >> 6);
        updateEnv();
        break;

    case 48:
        bitWrite(ledMatrix[5], 0, value >> 6);
        break;
    case 49:
        bitWrite(ledMatrix[5], 1, value >> 6);
        break;
    case 50:
        bitWrite(ledMatrix[5], 2, value >> 6);
        break;
    case 51:
        bitWrite(ledMatrix[5], 3, value >> 6);
        break;
    case 52:
        bitWrite(ledMatrix[5], 4, value >> 6);
        break;
    case 53:
        bitWrite(ledMatrix[5], 5, value >> 6);
        break;
    }
}

void handleProgramChange(int channel, int number1, int number2)
{
    if (channel == masterChannel)
    {
        if (number1 < 65)
        {
            bank = preset = 0;

            while (number1 > 8)
            {
                number1 -= 8;
                bank++;
            }

            preset = number1;
            encoderMoved(0);
            load();
        }
    }
}

byte dump;
int dumpCounter;
byte val[] = {0, 128};

void receiveDump() // RIO: fixed typo
{
    alternator = 0;

    byte flash[4000];

    while (dump != 247)
    {

        if (!dumpCounter)
        {
            PORTB = 0;
            PORTC = 255;
            delay(100);

            PORTB = 0;
            PORTC = 0;
            delay(100);
        }

        if (Serial.available() > 0)
        {
            dump = Serial.read();

            // must be sysex or cancel
            if (dumpCounter == 0)
            {
                if (dump == 240)
                    dumpCounter++;
                else
                    dumpCounter = 247;

                // must be 100 manuCode or cancel
            }
            else if (dumpCounter == 1)
            {
                if (dump == 100)
                    dumpCounter++;
                else
                    dumpCounter = 247;
            }
            else
            {

                alternator = !alternator;

                if (alternator)
                    flash[dumpCounter - 2] = dump;
                else
                {
                    flash[dumpCounter - 2] += val[dump];
                    dumpCounter++; // RIO: dumpCounter dec inside or outside?
                }
            }
        }
    }

    // byte cc; // RIO: unused, removed

    for (int i = 0; i < 4000; i++)
    {
        PORTB = 0;
        PORTC = 255;
        delay(1);

        PORTB = 0;
        PORTC = 0;
        delay(1);

        EEPROM.write(i, flash[i]);
    }

    while (1)
    {
    } // RIO: endless loop to avoid ending?...maybe replaced by a condition in main loop?
}