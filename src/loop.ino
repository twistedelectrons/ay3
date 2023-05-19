void tick()
{
    if (voicePressed) {
        if (millis() > resetCounter) {
            voicePressed=false;

            //reset 
            for (int i=1; i<7; i++) tune[i] = presetTune[i] = 100;
        }
    }

    if (encTimer > 0) encTimer--;
  
    if (seqDisplayCounter < 20000) {
        if (!writeChannel) seqDisplayCounter += 1;

        // Counter to wipe numbers on led matrix and revert back to stored led matrix
        if (seqDisplayCounter == 20000) {
            ledMatrix[1] = oldMatrix[1];
            ledMatrix[2] = oldMatrix[2];
            ledMatrix[3] = oldMatrix[3];
            ledMatrix[4] = oldMatrix[4];
            ledMatrix[5] = oldMatrix[5];
        }
    }

    //seqMode counter
    if (seqPressed == 1) {
        buttCounter2++;
        if (buttCounter2 > 2000) {
            buttCounter2 = 0;
            countDown--;
            ledNumber = countDown;

            if (countDown == 0) {
                seqSetup = !seqSetup;

                // silence voices, entering setup
                if (seqSetup == 0) { 
                    base[1] = 0;
                    base[2] = 0;
                    base[3] = 0;
                    base[4] = 0;
                    base[5] = 0;
                    base[6] = 0;

                    bitWrite(data7A, 0, 1);
                    bitWrite(data7A, 1, 1);
                    bitWrite(data7A, 2, 1);
                    bitWrite(data7B, 0, 1);
                    bitWrite(data7B, 1, 1);
                    bitWrite(data7B, 2, 1);

                    pressedRow = 0;

                }

                ledNumber = numberOld;
                encoderMoved(0);
            }
        }
    } else buttCounter2 = 0;
    
    // Save butt counter
    if (savePressed == 1) {
        buttCounter++;

        if (buttCounter > 1000) {
            buttCounter = 0;
            countDown--;
            ledNumber = countDown;

            //save preset
            if (countDown == 0) save();
        }
    } else buttCounter = 0;

    job++;
    if (job > 6) {
        job = 1;
        doLedMatrix();
    }

    switch (job) {

        case 1: doButtons();    break;
        case 2: doEncoder();    break;
        case 3: doLfo();        break;

        case 4: analogCounter++;
                if (analogCounter > 40) {
                    analogCounter = 0;
                    doPots();
                }
                break;

        case 6: if (seqDisplayCounter > 2999) {}
                break;
    }
}