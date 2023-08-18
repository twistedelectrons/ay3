void doGlide()
{
    // glide
    for (int i = 1; i < 7; i++)
    {

        // limit pitches
        if (destiPitch[i] > 15289)
            destiPitch[i] = 15289;
        else if (destiPitch[i] < 0)
            destiPitch[i] = 0;

        // Glide
        if (base[i] != 0)
        {
            if (destiPitch[i] + bend[i] > pitch[i])
            {
                pitch[i] += glider;
                if (pitch[i] > destiPitch[i] + bend[i])
                    pitch[i] = destiPitch[i] + bend[i];
            }
            else if (destiPitch[i] + bend[i] < pitch[i])
            {
                pitch[i] -= glider;
                if (pitch[i] < destiPitch[i] + bend[i])
                    pitch[i] = destiPitch[i] + bend[i];
            }
        }

        if (glider > 45 || chord == 8)
            if (base[i] != 0)
                pitch[i] = destiPitch[i] + bend[i];
    }

    // update registers

    // pitch
    if (pitchLast[1] != pitch[1])
    {
        pitchLast[1] = pitch[1];
        AY3(0x00, pitch[1] & 0xff);
        AY3(0x01, (pitch[1] >> 8) & 0x0f);
    }

    if (pitchLast[2] != pitch[2])
    {
        pitchLast[2] = pitch[2];
        AY3(0x02, pitch[2] & 0xff);
        AY3(0x03, (pitch[2] >> 8) & 0x0f);
    }

    if (pitchLast[3] != pitch[3])
    {
        pitchLast[3] = pitch[3];
        AY3(0x04, pitch[3] & 0xff);
        AY3(0x05, (pitch[3] >> 8) & 0x0f);
    }

    if (pitchLast[4] != pitch[4])
    {
        pitchLast[4] = pitch[4];
        AY32(0x00, pitch[4] & 0xff);
        AY32(0x01, (pitch[4] >> 8) & 0x0f);
    }

    if (pitchLast[5] != pitch[5])
    {
        pitchLast[5] = pitch[5];
        AY32(0x02, pitch[5] & 0xff);
        AY32(0x03, (pitch[5] >> 8) & 0x0f);
    }

    if (pitchLast[6] != pitch[6])
    {
        pitchLast[6] = pitch[6];
        AY32(0x04, pitch[6] & 0xff);
        AY32(0x05, (pitch[6] >> 8) & 0x0f);
    }
}