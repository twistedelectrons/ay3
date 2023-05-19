void seqTick()
{
    doGlide();

    if (seqSetup == 1)
        if (sync == 0) seqCounter++;
}

void doSeq()
{
    // mixer

    if (seqSetup == 1 && seqDisplayCounter > 2999) {

        data7A = B11111111;

        bitWrite(data7A, 0,!bitRead(ledMatrix[1], 1-1)); //
        bitWrite(data7A, 1,!bitRead(ledMatrix[1], 2-1)); //
        bitWrite(data7A, 2,!bitRead(ledMatrix[1], 3-1)); //

        bitWrite(data7A, 3,!bitRead(ledMatrix[3], 1-1)); // A
        bitWrite(data7A, 4,!bitRead(ledMatrix[3], 2-1)); // B
        bitWrite(data7A, 5,!bitRead(ledMatrix[3], 3-1)); // C

        // Sequencer 
        if (bitRead(ledMatrix[5],0) == 1 && base[1] != 0) {
            bitWrite(data7A, 0, !seqVoice[seqStep]);
            bitWrite(data7A, 3, !seqNoise[seqStep]);
        }

        if (bitRead(ledMatrix[5],1) == 1 && base[2] != 0) {
            bitWrite(data7A, 1, !seqVoice[seqStep]);
            bitWrite(data7A, 4, !seqNoise[seqStep]);
        }

        if (bitRead(ledMatrix[5],2) == 1 && base[3] != 0) {
            bitWrite(data7A, 2, !seqVoice[seqStep]);
            bitWrite(data7A, 5, !seqNoise[seqStep]);
        }

        if (data7A != data7ALast) {
            data7ALast = data7A;
            AY3(7, data7A);
        }


        data7B=B11111111;

        bitWrite(data7B, 0, !bitRead(ledMatrix[1], 4-1)); // D
        bitWrite(data7B, 1, !bitRead(ledMatrix[1], 5-1)); // E
        bitWrite(data7B, 2, !bitRead(ledMatrix[1], 6-1)); // F

        bitWrite(data7B, 3, !bitRead(ledMatrix[3], 4-1)); // D
        bitWrite(data7B, 4, !bitRead(ledMatrix[3], 5-1)); // E
        bitWrite(data7B, 5, !bitRead(ledMatrix[3], 6-1)); // F

        //Sequencer
        if (bitRead(ledMatrix[5], 3) == 1 && base[4] != 0) {
            bitWrite(data7B, 0, !seqVoice[seqStep]);
            bitWrite(data7B, 3, !seqNoise[seqStep]);
        }

        if (bitRead(ledMatrix[5], 4) == 1 && base[5] != 0) {
            bitWrite(data7B, 1, !seqVoice[seqStep]);
            bitWrite(data7B, 4, !seqNoise[seqStep]);
        }

        if (bitRead(ledMatrix[5], 5) == 1 && base[6] != 0) {
            bitWrite(data7B, 2, !seqVoice[seqStep]);
            bitWrite(data7B, 5, !seqNoise[seqStep]);
        }

        if (data7B != data7BLast) {
            data7BLast = data7B;
            AY32(7, data7B);
        }
    }

    ///////
  
    if (pressedRow == 5 && seqPressed == 0) {
        if (seqStep <= 7)   ledNumber = seqStep+1;
        else                ledNumber = seqStep-7;
    }

    seqCounter=0;
    seqStep++;

    if (seqStep > 15) {
        if (seqLoop == 1)   seqStep=0;
        else                seqStep=15;
    }

    seq=seqNote[seqStep];
}