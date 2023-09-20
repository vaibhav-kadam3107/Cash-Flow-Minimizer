#include <stdio.h>
#include <stdlib.h>
#include<string.h>
int adjmat[10][10];
struct banks
{
    int netAmount;
    char name;
    int types[3];
};


struct BankAndType {
    int bankIndex;
    int paymentType;
};
struct BankAndType ansGraph[10][10];
int GetMinIndex(struct banks listOfAmounts[],int numBanks)
{
     //printf("hello world  min ");
    int min=INT_MAX,minIndex=-1;
    for(int i=0;i<numBanks;i++)
    {
        if(listOfAmounts[i].netAmount==0)
            continue;
        if(listOfAmounts[i].netAmount < min)
        {
            minIndex=i;
            min=listOfAmounts[i].netAmount;
        }
    }
   // printf("\n%d :",minIndex);
    return minIndex;
}
//define function for getting max credtior banks index
int getSimpleMaxIndex(struct banks listOfNetAmounts[],int numBanks){
    int max=INT_MIN, maxIndex=-1;
    for(int i=0;i<numBanks;i++){
        if(listOfNetAmounts[i].netAmount == 0) continue;

        if(listOfNetAmounts[i].netAmount > max){
            maxIndex = i;
            max = listOfNetAmounts[i].netAmount;
        }
    }
    return maxIndex;
}
struct BankAndType getMaxIndex(struct banks listOfNetAmounts[], int numBanks, int minIndex, struct banks input[]) {
    int max = INT_MIN;
    int maxIndex = -1;
    int matchingType = -1;

    for (int i = 0; i < numBanks; i++) {
        if (listOfNetAmounts[i].netAmount == 0 || listOfNetAmounts[i].netAmount < 0) {
            continue;
        }

        for (int j = 0; j < 3; j++) {
            int currentType = listOfNetAmounts[i].types[j];

            for (int k = 0; k < numBanks; k++) {
                if (listOfNetAmounts[k].netAmount == 0 || listOfNetAmounts[k].netAmount <  0) {
                    continue;
                }

                for (int l = 0; l < 3; l++) {
                    if (listOfNetAmounts[k].types[l] == currentType) {
                        if (listOfNetAmounts[i].netAmount > max) {
                            max = listOfNetAmounts[i].netAmount;
                            maxIndex = i;
                            matchingType = currentType;
                        }
                    }
                }
            }
        }
    }

   //  printf("\n%d  %c :", maxIndex,matchingType);

    struct BankAndType result = { maxIndex, matchingType };
    return result;
}
void printAns(int numBanks, struct banks input[]) {
    printf("\nThe transactions for minimum cash flow are as follows:\n\n");

    for (int i = 0; i < numBanks; i++) {
        for (int j = 0; j < numBanks; j++) {
            if (i == j) continue;

            if (ansGraph[i][j].bankIndex != 0 && ansGraph[j][i].bankIndex != 0) {
                if (ansGraph[i][j].bankIndex == ansGraph[j][i].bankIndex) {
                    ansGraph[i][j].bankIndex = 0;
                    ansGraph[j][i].bankIndex = 0;
                } else if (ansGraph[i][j].bankIndex > ansGraph[j][i].bankIndex) {
                    ansGraph[i][j].bankIndex -= ansGraph[j][i].bankIndex;
                    ansGraph[j][i].bankIndex = 0;

                    printf("%c pays Rs %d to %c via %d\n", input[i].name, ansGraph[i][j].bankIndex, input[j].name, ansGraph[i][j].paymentType);
                } else {
                    ansGraph[j][i].bankIndex -= ansGraph[i][j].bankIndex;
                    ansGraph[i][j].bankIndex = 0;

                    printf("%c pays Rs %d to %c via %d\n", input[j].name, ansGraph[j][i].bankIndex, input[i].name, ansGraph[j][i].paymentType);
                }
            } else if (ansGraph[i][j].bankIndex != 0) {
                printf("%c pays Rs %d to %c\n", input[i].name, ansGraph[i][j].bankIndex, input[j].name);
            } else if (ansGraph[j][i].bankIndex != 0) {
                printf("%c receives Rs %d from %c\n", input[i].name, ansGraph[j][i].bankIndex, input[j].name);
            }

            ansGraph[i][j].bankIndex = 0;
            ansGraph[j][i].bankIndex = 0;
        }
    }

    printf("\n");
}

void Minimizecashflow(int numBanks,struct banks input[20],char aindexOf[20],int numTras,int maxTypes)
{
   struct banks listOfNetAmounts[numBanks];
   for(int b=0;b<numBanks;b++)
   {
       listOfNetAmounts[b].name=input[b].name;
       for(int i=0;i<numBanks;i++)
       {
            listOfNetAmounts[b].types[i]=input[b].types[i];
       }
       int amount=0;
       for(int i=0;i<numBanks;i++){
            amount += (adjmat[i][b]);
        }
       for(int j=0;j<numBanks;j++){
            amount += ((-1) * adjmat[b][j]);
        }
        listOfNetAmounts[b].netAmount = amount;
       // printf("\n%d  %d netamount:",amount,listOfNetAmounts[b].netAmount);
   }
  // struct BankAndType  ansGraph[numBanks][numBanks];
   int numZeroNetAmounts=0;
   int maxIndex=0;

    for(int i=0;i<numBanks;i++){
        if(listOfNetAmounts[i].netAmount == 0)
            numZeroNetAmounts++;
    }
    while(numZeroNetAmounts!=numBanks){
            printf("\n%d ",numZeroNetAmounts);

        int minIndex=GetMinIndex(listOfNetAmounts, numBanks);
       // printf("\nminindex %d",minIndex);
        struct BankAndType maxAns = getMaxIndex(listOfNetAmounts, numBanks, minIndex,input);
        int maxIndex = maxAns.bankIndex;
       // printf("\nmaxindex %d",maxIndex);
       if(maxIndex == -1){
            (ansGraph[minIndex][0].bankIndex) += abs(listOfNetAmounts[minIndex].netAmount);
            strcpy(ansGraph[minIndex][0].paymentType, input[minIndex].types[0]);
            int simpleMaxIndex = getSimpleMaxIndex(listOfNetAmounts, numBanks);
            (ansGraph[0][simpleMaxIndex].bankIndex) += abs(listOfNetAmounts[minIndex].netAmount);
           strcpy(ansGraph[0][simpleMaxIndex].paymentType, input[simpleMaxIndex].types[0]);
            listOfNetAmounts[simpleMaxIndex].netAmount += listOfNetAmounts[minIndex].netAmount;
            listOfNetAmounts[minIndex].netAmount = 0;
            if(listOfNetAmounts[minIndex].netAmount == 0) numZeroNetAmounts++;
            if(listOfNetAmounts[simpleMaxIndex].netAmount == 0) numZeroNetAmounts++;
        }
        else{
            int transactionAmount;
            if(abs(listOfNetAmounts[minIndex].netAmount) < listOfNetAmounts[maxIndex].netAmount)
            {
                 transactionAmount=abs(listOfNetAmounts[minIndex].netAmount);
            }
            else
            {
                 transactionAmount=listOfNetAmounts[maxIndex].netAmount;
            }
           // printf("%d transactionamount:",transactionAmount);
            (ansGraph[minIndex][maxIndex].bankIndex) += (transactionAmount);
           (ansGraph[minIndex][maxIndex].paymentType) = maxAns.paymentType;
           //printf("%d transactionamount:",ansGraph[minIndex][maxIndex].bankIndex);
            listOfNetAmounts[minIndex].netAmount += transactionAmount;
            listOfNetAmounts[maxIndex].netAmount -= transactionAmount;
            if(listOfNetAmounts[minIndex].netAmount == 0) numZeroNetAmounts++;
            if(listOfNetAmounts[maxIndex].netAmount == 0) numZeroNetAmounts++;
        }
    }
   printAns(numBanks,input);
}
int main() {
    printf("\n-----------------------------------------------------------------------------------------------\n");
    printf("\t\t\tWelcome to the Cash Flow Minimizer System\n");
    printf("-----------------------------------------------------------------------------------------------\n\n");

    int numBanks;
    printf("Enter the number of banks: ");
    scanf("%d", &numBanks);
    printf("-----------------------------------------------------------------------------------------------\n\n");

    struct banks input[numBanks];
    char aindexOf[numBanks];
    int maxTypes;

    printf("Enter the details of the banks and transactions as stated:\n\n");
    printf("Bank Name, Number of Payment Modes, and the Payment Modes.\n\n");
    printf("-----------------------------------------------------------------------------------------------\n\n");

    for (int i = 0; i < numBanks; i++) {
        if (i == 0) {
            printf("World Bank:\n");
        } else {
            printf("Bank %d:\n", i);
        }
        fflush(stdin);
        printf("Enter name of bank: ");
        fflush(stdin);
        scanf("%c", &input[i].name);
        aindexOf[i] = input[i].name;
        fflush(stdin);
        printf("Enter number of modes: ");
        int numTypes;
        scanf("%d", &numTypes);
        printf("\nClick:\nPhone Pay - 1\nPaytm - 2\nGoogle Pay - 3\n");
        if (i == 0) {
            maxTypes = numTypes;
        }
        int inputTypesOfPayment;
        input[i].types[0] = 0; // Phone Pay
        input[i].types[1] = 0; // Paytm
        input[i].types[2] = 0; // Google Pay
        while (numTypes--) {
            scanf("%d", &inputTypesOfPayment);
            input[i].types[inputTypesOfPayment - 1] = 1;
        }
        printf("-----------------------------------------------------------------------------------------------\n\n");
    }

    printf("Enter the number of transactions: ");
    int numTras;
    scanf("%d", &numTras);

    int adjmat[numBanks][numBanks];
    for (int i = 0; i < numBanks; i++) {
        for (int j = 0; j < numBanks; j++) {
            adjmat[i][j] = 0;
        }
    }

    printf("Debtor Bank, Creditor Bank, and Amount:\n");
    for (int i = 0; i < numTras; i++) {
        printf("%dth Transaction: ", i + 1);
        fflush(stdin);
        char fBank, sBank;
        int amount;
        fflush(stdin);
        scanf("%c %c", &fBank, &sBank);
        fflush(stdin);
        scanf("%d", &amount);
        fflush(stdin);
        int retIndf = 0;
        int retInds = 0;
        for (int i = 0; i < numBanks; i++) {
            if (aindexOf[i] == fBank) {
                retIndf = i;
            }
            if (aindexOf[i] == sBank) {
                retInds = i;
            }
        }
        adjmat[retIndf][retInds] = amount;
    }

    Minimizecashflow(numBanks, input, aindexOf, numTras, maxTypes);

    return 0;
}
