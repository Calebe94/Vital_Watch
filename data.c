#include"HeartBeat.h"
int main(void){
	struct sMALE male[6];
	struct sFEMALE female[6];

	male[0].Excellent = 49;
	male[0].VerryGood = 56;
	male[0].Good = 62;
	male[0].AboveAverage = 66;
	male[0].Average = 70;
	male[0].BelowAverage = 74;
	male[0].Bad = 82;

	male[1].Excellent = 49;
	male[1].VerryGood = 55;
	male[1].Good = 62;
	male[1].AboveAverage = 67;
	male[1].Average = 71;
	male[1].BelowAverage = 75;
	male[1].Bad = 82;

	male[2].Excellent = 50;
	male[2].VerryGood = 55;
	male[2].Good = 62;
	male[2].AboveAverage = 67;
	male[2].Average = 71;
	male[2].BelowAverage = 76;
	male[2].Bad = 83;

	male[3].Excellent = 50;
	male[3].VerryGood = 58;
	male[3].Good = 64;
	male[3].AboveAverage = 68;
	male[3].Average = 72;
	male[3].BelowAverage = 76;
	male[3].Bad = 84;

	male[4].Excellent = 51;
	male[4].VerryGood = 57;
	male[4].Good = 62;
	male[4].AboveAverage = 68;
	male[4].Average = 72;
	male[4].BelowAverage = 76;
	male[4].Bad = 82;

	male[5].Excellent = 50;
	male[5].VerryGood = 56;
	male[5].Good = 62;
	male[5].AboveAverage = 66;
	male[5].Average = 70;
	male[5].BelowAverage = 74;
	male[5].Bad = 80;



	female[0].Excellent = 54;
	female[0].VerryGood = 61;
	female[0].Good = 66;
	female[0].AboveAverage = 70;
	female[0].Average = 74;
	female[0].BelowAverage = 79;
	female[0].Bad = 85;

	female[1].Excellent = 54;
	female[1].VerryGood = 60;
	female[1].Good = 65;
	female[1].AboveAverage = 69;
	female[1].Average = 73;
	female[1].BelowAverage = 77;
	female[1].Bad = 83;

	female[2].Excellent = 54;
	female[2].VerryGood = 60;
	female[2].Good = 65;
	female[2].AboveAverage = 70;
	female[2].Average = 74;
	female[2].BelowAverage = 79;
	female[2].Bad = 85;

	female[3].Excellent = 54;
	female[3].VerryGood = 61;
	female[3].Good = 66;
	female[3].AboveAverage = 70;
	female[3].Average = 74;
	female[3].BelowAverage = 78;
	female[3].Bad = 84;

	female[4].Excellent = 54;
	female[4].VerryGood = 60;
	female[4].Good = 65;
	female[4].AboveAverage = 69;
	female[4].Average = 74;
	female[4].BelowAverage = 78;
	female[4].Bad = 84;

	female[5].Excellent = 54;
	female[5].VerryGood = 60;
	female[5].Good = 65;
	female[5].AboveAverage = 69;
	female[5].Average = 73;
	female[5].BelowAverage = 77;
	female[5].Bad = 84;
	
	FILE *fMale,*fFemale;
	fMale = fopen("data_male.bin","w");
	if(fMale == NULL)	printf("Deu Bode!\n");
	fFemale = fopen("data_female.bin","w");
	if(fFemale == NULL)	printf("Deu Bode!\n");
	for(register unsigned int cont = 0; cont < 6;cont++){
		fwrite(&male[cont],sizeof(struct sMALE),1,fMale);
		fwrite(&female[cont],sizeof(struct sFEMALE),1,fFemale);
	}
	fclose(fMale);
	fclose(fFemale);
		
}
