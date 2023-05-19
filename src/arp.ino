void doArpMaster() {

    if (lfoShape == 6) {
        lfo = 0;

        arpStep++;
        if (arpStep > held) {
            arpStep = 1;
            arpOct++;

            if(arpOct > arpRange) arpOct = 0;
        }

        if (bitRead(ledMatrix[2], 0) == 1) base[1]=noteMem[arpStep-1]+(arpOct*12);
        if (bitRead(ledMatrix[2], 1) == 1) base[2]=noteMem[arpStep-1]+(arpOct*12);
        if (bitRead(ledMatrix[2], 2) == 1) base[3]=noteMem[arpStep-1]+(arpOct*12);
        if (bitRead(ledMatrix[2], 3) == 1) base[4]=noteMem[arpStep-1]+(arpOct*12);
        if (bitRead(ledMatrix[2], 4) == 1) base[5]=noteMem[arpStep-1]+(arpOct*12);
        if (bitRead(ledMatrix[2], 5) == 1) base[6]=noteMem[arpStep-1]+(arpOct*12);

    } else if (lfoShape == 5) {
        lfo = 0;

        arpStep--;
        if (arpStep < 1) {
            arpStep = held;
            arpOct++;

            if(arpOct > arpRange) arpOct = 0;
        }

        if (bitRead(ledMatrix[2], 0) == 1) base[1]=noteMem[arpStep-1]+(arpOct*12);
        if (bitRead(ledMatrix[2], 1) == 1) base[2]=noteMem[arpStep-1]+(arpOct*12);
        if (bitRead(ledMatrix[2], 2) == 1) base[3]=noteMem[arpStep-1]+(arpOct*12);
        if (bitRead(ledMatrix[2], 3) == 1) base[4]=noteMem[arpStep-1]+(arpOct*12);
        if (bitRead(ledMatrix[2], 4) == 1) base[5]=noteMem[arpStep-1]+(arpOct*12);
        if (bitRead(ledMatrix[2], 5) == 1) base[6]=noteMem[arpStep-1]+(arpOct*12);

    } else if (lfoShape == 7) {
        lfo = 0;

        arpStep++;
        if (arpStep > (held*2)-2) {
            arpStep = 1;
            arpOct++;

            if(arpOct > arpRange) arpOct = 0;
        }

        if(arpStep <= held) {
            if (bitRead(ledMatrix[2], 0) == 1) base[1]=noteMem[arpStep-1]+(arpOct*12);
            if (bitRead(ledMatrix[2], 1) == 1) base[2]=noteMem[arpStep-1]+(arpOct*12);
            if (bitRead(ledMatrix[2], 2) == 1) base[3]=noteMem[arpStep-1]+(arpOct*12);
            if (bitRead(ledMatrix[2], 3) == 1) base[4]=noteMem[arpStep-1]+(arpOct*12);
            if (bitRead(ledMatrix[2], 4) == 1) base[5]=noteMem[arpStep-1]+(arpOct*12);
            if (bitRead(ledMatrix[2], 5) == 1) base[6]=noteMem[arpStep-1]+(arpOct*12);
        } else {
            if (bitRead(ledMatrix[2], 0) == 1) base[1]=noteMem[(held*2)-arpStep-1]+(arpOct*12);
            if (bitRead(ledMatrix[2], 1) == 1) base[2]=noteMem[(held*2)-arpStep-1]+(arpOct*12);
            if (bitRead(ledMatrix[2], 2) == 1) base[3]=noteMem[(held*2)-arpStep-1]+(arpOct*12);
            if (bitRead(ledMatrix[2], 3) == 1) base[4]=noteMem[(held*2)-arpStep-1]+(arpOct*12);
            if (bitRead(ledMatrix[2], 4) == 1) base[5]=noteMem[(held*2)-arpStep-1]+(arpOct*12);
            if (bitRead(ledMatrix[2], 5) == 1) base[6]=noteMem[(held*2)-arpStep-1]+(arpOct*12);
        }

    } else if(lfoShape == 8) {
        lfo = 0;

        if (bitRead(ledMatrix[2], 0) == 1) base[1]=noteMem[random(held)]+(random(arpRange)*12);
        if (bitRead(ledMatrix[2], 1) == 1) base[2]=noteMem[random(held)]+(random(arpRange)*12);
        if (bitRead(ledMatrix[2], 2) == 1) base[3]=noteMem[random(held)]+(random(arpRange)*12);
        if (bitRead(ledMatrix[2], 3) == 1) base[4]=noteMem[random(held)]+(random(arpRange)*12);
        if (bitRead(ledMatrix[2], 4) == 1) base[5]=noteMem[random(held)]+(random(arpRange)*12);
        if (bitRead(ledMatrix[2], 5) == 1) base[6]=noteMem[random(held)]+(random(arpRange)*12);
    }
}

void doArp1(){

    if (lfoShape == 6) {
        lfo = 0;

        arpStep1++;
        if (arpStep1 > held1) {
            arpStep1 = 1;
            arpOct1++;

            if (arpOct1 > arpRange) arpOct1 = 0;
        }

        if (bitRead(ledMatrix[2], 0) == 1) base[1]=noteMem1[arpStep1-1]+(arpOct1*12);
    
    } else if (lfoShape == 5) {
        lfo = 0;

        arpStep1--;
        if (arpStep1 < 1) {
            arpStep1 = held1;
            arpOct1++;

            if (arpOct1 > arpRange) arpOct1 = 0;
        }

        if (bitRead(ledMatrix[2], 0) == 1) base[1]=noteMem1[arpStep1-1]+(arpOct1*12);

    } else if (lfoShape == 7) {
        lfo = 0;

        arpStep1++;
        if (arpStep1 > (held1*2)-2) {
            arpStep1 = 1;
            arpOct1++;
            if (arpOct1 > arpRange) arpOct1 = 0;
        }

        if(arpStep1 <= held1) {
            if (bitRead(ledMatrix[2], 0) == 1) base[1]=noteMem1[arpStep1-1]+(arpOct1*12);
        } else {
            if (bitRead(ledMatrix[2], 0) == 1) base[1]=noteMem1[(held1*2)-arpStep1-1]+(arpOct1*12);
        }

    } else if (lfoShape == 8) {
        lfo = 0;

        if (bitRead(ledMatrix[2], 0) == 1) base[1]=noteMem1[random(held1)]+(random(arpRange)*12);
    }
}

void doArp2(){
  
    if (lfoShape == 6) {
        lfo = 0;

        arpStep2++;
        if (arpStep2 > held2) {
            arpStep2 = 1;
            arpOct2++;
            if (arpOct2 > arpRange) arpOct2 = 0;
        }

        if (bitRead(ledMatrix[2], 1) == 1) base[2]=noteMem2[arpStep2-1]+(arpOct2*12);
    
    } else if (lfoShape == 5) {
        lfo = 0;

        arpStep2--;
        if (arpStep2 < 1) {
            arpStep2 = held2;
            arpOct2++;
            if (arpOct2 > arpRange) arpOct2  =0;
        }

        if (bitRead(ledMatrix[2], 1) == 1) base[2]=noteMem2[arpStep2-1]+(arpOct2*12);

    } else if (lfoShape == 7) {
        lfo = 0;

        arpStep2++;
        if (arpStep2 > (held2*2)-2) {
            arpStep2 = 1;
            arpOct2++;
            if (arpOct2 > arpRange) arpOct2 = 0;
        }

        if (arpStep2<=held2) {
            if (bitRead(ledMatrix[2], 1) == 1) base[2]=noteMem2[arpStep2-1]+(arpOct2*12);
        } else {
            if (bitRead(ledMatrix[2], 1) == 1) base[2]=noteMem2[(held2*2)-arpStep2-1]+(arpOct2*12);
        }

    } else if (lfoShape == 8) {
        lfo = 0;

        if (bitRead(ledMatrix[2], 1) == 1) base[2]=noteMem2[random(held2)]+(random(arpRange)*12);
    } 
}

void doArp3(){

    if (lfoShape == 6) {
        lfo = 0;

        arpStep3++;
        if (arpStep3 > held3) {
            arpStep3 = 1;
            arpOct3++;
            if (arpOct3 > arpRange) arpOct3 = 0;
        }

        if (bitRead(ledMatrix[2], 2) == 1) base[3]=noteMem3[arpStep3-1]+(arpOct3*12);

    } else if (lfoShape == 5) {
        lfo = 0;

        arpStep3--;
        if (arpStep3 < 1) {
            arpStep3 = held3;
            arpOct3++;
            if (arpOct3 > arpRange) arpOct3 = 0;
        }

        if (bitRead(ledMatrix[2], 2) == 1) base[3]=noteMem3[arpStep3-1]+(arpOct3*12);
    
    } else if (lfoShape == 7){
        lfo = 0;

        arpStep3++;
        if (arpStep3 > (held3*2)-2) {
            arpStep3 = 1;
            arpOct3++;
            if (arpOct3 > arpRange) arpOct3 = 0;
        }

        if (arpStep3 <= held3) {
            if (bitRead(ledMatrix[2], 2) == 1) base[3]=noteMem3[arpStep3-1]+(arpOct3*12);
        } else {
            if (bitRead(ledMatrix[2], 2) == 1) base[3]=noteMem3[(held3*2)-arpStep3-1]+(arpOct3*12);
        }

    } else if (lfoShape == 8){
        lfo = 0;

        if (bitRead(ledMatrix[2], 2) == 1) base[3]=noteMem3[random(held3)]+(random(arpRange)*12); 
    } 
}

void doArp4(){
  
    if (lfoShape == 6) {
        lfo = 0;

        arpStep4++;
        if (arpStep4 > held4) {
            arpStep4 = 1;
            arpOct4++;
            if (arpOct4 > arpRange) arpOct4=0;
        }
        if (bitRead(ledMatrix[2], 3) == 1) base[4]=noteMem4[arpStep4-1]+(arpOct4*12);

    } else if (lfoShape == 5) {
        lfo = 0;

        arpStep4--;
        if (arpStep4 < 1) {
            arpStep4 = held4;
            arpOct4++;
            if (arpOct4 > arpRange) arpOct4 = 0;
        }

        if (bitRead(ledMatrix[2], 4) == 1) base[4]=noteMem4[arpStep4-1]+(arpOct4*12); // RIO: not fixed but bitRead 2nd arg: 3 instead 4?

    } else if (lfoShape == 7) {
        lfo = 0;

        arpStep4++;
        if (arpStep4 > (held4*2)-2) {
            arpStep4 = 1;
            arpOct4++;
            if (arpOct4 > arpRange) arpOct4 = 0;
        }
  
        if (arpStep4 <= held4){
            if (bitRead(ledMatrix[2], 3) == 1) base[4]=noteMem4[arpStep4-1]+(arpOct4*12);
        } else {
            if (bitRead(ledMatrix[2], 3) == 1) base[4]=noteMem4[(held4*2)-arpStep4-1]+(arpOct4*12);
        }

    } else if (lfoShape == 8) {
        lfo = 0;

        if (bitRead(ledMatrix[2], 3) == 1) base[4]=noteMem4[random(held4)]+(random(arpRange)*12);
    } 
}

void doArp5(){

    if (lfoShape == 6) {
        lfo = 0;

        arpStep5++;
        if (arpStep5 > held5) {
            arpStep5 = 1;
            arpOct5++;
            if (arpOct5 > arpRange) arpOct5 = 0;
        }

        if (bitRead(ledMatrix[2], 4) == 1) base[5]=noteMem5[arpStep5-1]+(arpOct5*12);

    } else if(lfoShape == 5){
        lfo = 0;

        arpStep5--;
        if (arpStep5 < 1) {
            arpStep5 = held5;
            arpOct5++;
            if (arpOct5 > arpRange) arpOct5 = 0;
        }

        if (bitRead(ledMatrix[2], 4) == 1) base[5]=noteMem5[arpStep5-1]+(arpOct5*12);
    
    } else if(lfoShape == 7) {
        lfo = 0;

        arpStep5++;
        if (arpStep5 > (held5*2)-2) {
            arpStep5 = 1;
            arpOct5++;
            if (arpOct5 > arpRange) arpOct5 = 0;
        }

        if (arpStep5 <= held5) {
            if (bitRead(ledMatrix[2], 4) == 1) base[5]=noteMem5[arpStep5-1]+(arpOct5*12);
        } else {
            if (bitRead(ledMatrix[2], 4) == 1) base[5]=noteMem5[(held5*2)-arpStep5-1]+(arpOct5*12);
        }

    } else if(lfoShape == 8){
        lfo = 0;

        if (bitRead(ledMatrix[2], 4) == 1) base[5]=noteMem5[random(held5)]+(random(arpRange)*12);
    } 
}

void doArp6(){

    if (lfoShape == 6){
        lfo = 0;
     
        arpStep6++;
        if (arpStep6 > held6) {
            arpStep6 = 1;
            arpOct6++;
            if (arpOct6 > arpRange) arpOct6 = 0;
        }

        if (bitRead(ledMatrix[2], 5) == 1) base[6]=noteMem6[arpStep6-1]+(arpOct6*12);

    } else if (lfoShape == 5) {   // RIO: fixed from 6 to 5
        lfo = 0;

        arpStep6--;
        if (arpStep6 < 1) {
            arpStep6 = held6;
            arpOct6++;
            if(arpOct6 > arpRange) arpOct6 = 0;
        }

        if (bitRead(ledMatrix[2], 5) == 1) base[6]=noteMem6[arpStep6-1]+(arpOct6*12);
    
    } else if (lfoShape == 7) {
        lfo = 0;

        arpStep6++;
        if (arpStep6 > (held6*2)-2) {
            arpStep6 = 1;
            arpOct6++;
            if (arpOct6 > arpRange) arpOct6 = 0;
        }

        if (arpStep6 <= held6) {
            if (bitRead(ledMatrix[2], 5) == 1) base[6]=noteMem6[arpStep6-1]+(arpOct6*12);
        } else {
            if (bitRead(ledMatrix[2], 5) == 1) base[6]=noteMem6[(held6*2)-arpStep6-1]+(arpOct6*12);
        }

    } else if (lfoShape == 8){
        lfo = 0;

        if (bitRead(ledMatrix[2], 5) == 1) base[6]=noteMem6[random(held6)]+(random(arpRange)*12);
    }
}